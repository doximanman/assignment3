#ifndef SIMPLE_EXAMPLE_SOCKETIO_HPP
#define SIMPLE_EXAMPLE_SOCKETIO_HPP

#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "DefaultIO.hpp"

class SocketIO : public DefaultIO {
private:
    int _client_sock;
public:
    /**
     * @param sock socket to read from and write to.
     */
    explicit SocketIO(int sock);
    /**
     * writes the message to the socket.
     * @param message string to write.
     */
    void write(const std::string &message) override;
    /**
     * reads from the socket.
     * @return the message that was read.
     */
    std::string read() override;
    /**
     * closes the socket.
     */
    ~SocketIO();

};


#endif //SIMPLE_EXAMPLE_SOCKETIO_HPP
