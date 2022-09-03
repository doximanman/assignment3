#include "SocketIO.hpp"


SocketIO::SocketIO(int client_sock) :_client_sock(client_sock){
}

std::string SocketIO::read() {
    // reads from the socket using a buffer.
    char buffer[8192] = {0};
    int expected_data_len = sizeof(buffer);
    int bytes_received = (int) recv(_client_sock, buffer, expected_data_len, 0);
    if (bytes_received == 0) {
        return "";
    } else if (bytes_received < 0) {
        perror("Error reading client message");
    }
    return {buffer};
}

void SocketIO::write(const std::string &message) {
    // writes to the socket.
    int sent_bytes = (int) send(_client_sock, message.c_str(), message.size(), 0);
    if (sent_bytes < 0) {
        perror("Error sending to client");
    }
}

SocketIO::~SocketIO() {
    close(_client_sock);
}