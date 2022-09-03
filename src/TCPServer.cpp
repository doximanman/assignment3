#include <sys/socket.h>
#include <functional>
#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include "SocketIO.hpp"
#include "CLI.hpp"
#include "TCPServer.hpp"

#define TIMEOUT_SECONDS 300

using namespace std;

TCPServer::TCPServer(int port) : _timeout(false), _stop(false), _port(port), _threads(),
                                 _sock(socket(AF_INET, SOCK_STREAM, 0)) {
    if (_sock < 0) {
        perror("Error creating socket");
    }
    // tries to bind the socket to the port.
    struct sockaddr_in sin{AF_INET, htons(_port), INADDR_ANY};
    if (bind(_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("Error binding socket");
    }
}

void TCPServer::newClient(int client_sock) {
    SocketIO sio{client_sock};
    cout << "New client joined on socket: " + to_string(client_sock) << endl;
    CLI cli{sio};
    cli.start();
    cout << "Client disconnected on socket: " + to_string(client_sock) << endl;
}

void TCPServer::timeoutEnforcer() {
    int timePassed = 0;
    int currentLen = (int) _threads.size();
    while (true) {
        // counts how many seconds have passed since the last client joined.
        while (timePassed < TIMEOUT_SECONDS && _threads.size() == currentLen) {
            sleep(1);
            timePassed++;
        }
        if (_threads.size() != currentLen) {
            // new client joined. resets the timer.
            timePassed = 0;
            currentLen = (int) _threads.size();
        } else {
            // timeout reached. notifies server to stop accepting new clients and wait for clients to finish.
            _timeout = true;
            cout <<"Server timed out. Waiting for all clients to finish." << endl;
            // waits for clients to finish.
            for (thread &thr: _threads) {
                thr.join();
            }
            _stop = true;
            // exits the main thread from the 'accept' call.
            int sock = socket(AF_INET, SOCK_STREAM, 0);
            sockaddr_in sin{AF_INET, htons(_port), inet_addr("127.0.0.1")};
            if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
                perror("Failed to stop server");
            }
            return;
        }
    }
}

void TCPServer::start() {
    int client_sock;
    thread timeoutThread{&TCPServer::timeoutEnforcer, this};
    timeoutThread.detach();
    // starts listening to the socket.
    if (listen(_sock, 5) < 0) {
        perror("Error listening to a socket");
    }
    cout <<"Server is open. Accepting clients." << endl;
    while (!_stop) {
        struct sockaddr_in _client_sin{};
        unsigned int addr_len = sizeof(_client_sin);
        client_sock = accept(_sock, (struct sockaddr *) &_client_sin, &addr_len);
        if (_timeout) {
            // server reached timeout.
            if (_stop) {
                // all clients finished. closes the server.
                close(_sock);
                cout <<"Server closed." << endl;
            } else {
                // clients haven't yet finished. notifies the new client that the server isn't accepting new clients.
                SocketIO sio{client_sock};
                sio.write("printServer is closing. Not accepting new clients.\n");
                sio.write("end");
            }
        } else {
            if (client_sock < 0) {
                perror("Error accepting client");
            } else {
                // new client.
                thread newThread(&TCPServer::newClient, client_sock);
                _threads.push_back(std::move(newThread));
            }
        }
    }
}