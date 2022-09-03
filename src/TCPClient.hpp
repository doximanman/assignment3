#ifndef SIMPLE_EXAMPLE_TCPCLIENT_HPP
#define SIMPLE_EXAMPLE_TCPCLIENT_HPP

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <cstring>

namespace Networking {
    class TCPClient {
    private:
        /**
         * Socket number.
         */
        int _sock;

        /**
         * IP address number.
         */
        std::string _ip_address;
        static void toFile(std::string data,std::string path);
    public:
        /**
         * Port number.
         */
        const int port;

        /**
         * Constructor of a new Client.
         */
        TCPClient(int port, std::string  ip_address);

        /**
         * Connects the server and send it the unclassifiedDataPath;
         */
        void connectToServer() const;
        /**
         * sends the message to the server.
         * @param message message to send.
         */
        void sendMessage(const std::string& message) const;
        /**
         * reads a message from the server.
         * @return the message that was read.
         */
        std::string readMessage() const;
    };
}
#endif //SIMPLE_EXAMPLE_TCPCLIENT_HPP
