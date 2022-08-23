#include "TCPClient.hpp"
#include "fileHandler.hpp"
#include <string>
#include <utility>
#include <sstream>

using namespace std;
using namespace Networking;
using namespace files;

TCPClient::TCPClient(std::string unclassifiedDataPath, std::string classifiedDataPath, int port, const char *ip_adress)
        :
        port(port), _ip_address(ip_adress),
        _unclassifiedDataPath(std::move(unclassifiedDataPath)),
        _classifiedDataPath(std::move(classifiedDataPath)) {
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin{AF_INET,htons(this->port),inet_addr(_ip_address)};

    if (connect(_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
}

void TCPClient::connectToServer() {
    char data[4096]={0};
    int data_len=sizeof(data);
    std::strcpy(data, fileHandler::getString(_unclassifiedDataPath).c_str());
    int sent_bytes = (int)send(_sock, data, data_len, 0);

    if (sent_bytes < 0) {
        cout << "Error sending the data to the server" << endl;
    }

    char buffer[4096]={0};
    int expected_data_len = sizeof(buffer);
    int read_bytes = (int)recv(_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        cout << "Connection terminated" << endl;
        close(_sock);
        return;
    } else if (read_bytes < 0) {
        perror("Error reading client message");
    } else {
        // convert buffer to type string
        string classificationStrings(buffer);
        stringstream str(classificationStrings);
        string currentClassification;
        // classified string vector
        vector<string> classifications;
        // saves each current classification into the vector
        while(getline(str,currentClassification)){
            classifications.push_back(currentClassification);
        }
        // save the classified data in the given classifiedData output path
        fileHandler::linesToFile(classifications, _classifiedDataPath);
    }
    close(_sock);
}


