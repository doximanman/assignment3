#include "TCPClient.hpp"
#include "fileHandler.hpp"
#include <string>
#include <utility>
#include <sstream>

using namespace std;
using namespace Networking;
using namespace files;

TCPClient::TCPClient(int port, string ip_address) : port(port), _ip_address(std::move(ip_address)) {
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin{AF_INET, htons(this->port), inet_addr(_ip_address.c_str())};

    if (connect(_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
}

std::string TCPClient::readMessage() const {
    // reads from the server.
    char buffer[4096] = {0};
    int expected_data_len = sizeof(buffer);
    int read_bytes = (int) recv(_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        return "";
    } else if (read_bytes < 0) {
        perror("Error reading client message");
    }
    return {buffer};
}

void TCPClient::sendMessage(const std::string &message) const {
    int sent_bytes = (int) send(_sock, message.c_str(), message.length(), 0);

    if (sent_bytes < 0) {
        cout << "Error sending the data to the server" << endl;
    }
}

void TCPClient::toFile(string data,string path) {
    // writes data to path.
    vector<string> lines = files::fileHandler::stringToLines(data, '@');
    files::fileHandler::linesToFile(lines, path);
    pthread_exit(nullptr);
}

void TCPClient::connectToServer() const {
    // receive message.
    while (true) {
        string wholeMessage = readMessage();
        // messages are separated by \n.
        vector<string> messages = files::fileHandler::stringToLines(wholeMessage);
        for (int i = 0; i < messages.size(); i++) {
            int len = (int) messages[i].length();
            if (len > 5 && messages[i].substr(0, 5) == "print") {
                // simply print the message.
                cout << messages[i].substr(5, messages[i].length()) << endl;
            } else if (len > 5 && messages[i].substr(0, 5) == "write") {
                // print the message and send console input.
                cout << messages[i].substr(5, messages[i].length()) << endl;
                string toSend{};
                getline(cin, toSend);
                if (toSend.empty()) {
                    toSend = "empty";
                }
                sendMessage(toSend);
            } else if (len > 6 && messages[i].substr(0, 6) == "toFile") {
                // prints the message, and writes the data received with it to a file given by console input,
                // on a different thread.
                cout << messages[i].substr(6, messages[i].length()) << endl;
                string path;
                getline(cin, path);
                bool err = files::fileHandler::validPath(path);
                while (!err) {
                    cout << "invalid path" << endl;
                    getline(cin, path);
                    err = files::fileHandler::validPath(path);
                }
                // i+1 exists because toFile messages are sent in chunks of 2 lines at once.
                thread writingThread{&TCPClient::toFile,messages[i+1],path};
                writingThread.detach();
            } else if (len > 7 && messages[i].substr(0, 7) == "getFile") {
                // prints the message, gets a file from the console (gets the path and then reads it) and sends
                // it to the server.
                cout << messages[i].substr(7, messages[i].length()) << endl;
                string path;
                getline(cin, path);
                int err;
                string data = files::fileHandler::getString(path, &err);
                while (err < 0) {
                    cout << "invalid path" << endl;
                    getline(cin, path);
                    data = files::fileHandler::getString(path, &err);
                }
                sendMessage(data);
            } else if (len > 2 && messages[i] == "end") {
                // connection has ended.
                close(_sock);
                return;
            }
        }
    }
}


