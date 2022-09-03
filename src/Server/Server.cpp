#include "../TCPServer.hpp"

int main() {
    TCPServer server(12346);
    server.start();
}
