#include "../TCPClient.hpp"

using namespace std;
using namespace Networking;

 /**
  * Creates a TCP client, and connects to the server.
  * @return
  */
int main() {
    const int port = 12346;
    TCPClient client(port, "127.0.0.1");
    client.connectToServer();
}
