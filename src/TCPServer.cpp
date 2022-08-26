#include "TCPServer.hpp"
#include <string>
#include <utility>
#include <sstream>
#include "fileHandler.hpp"
#include "KNearestNeighbors.hpp"
#include "CSVManagement.hpp"
#include "Point.hpp"
#include "Distance/EuclideanDistance.hpp"

using namespace files;
using namespace std;
using namespace CSV;
using namespace Networking;
using namespace Geometry;

TCPServer::TCPServer(int port, string dataPath) : port(port), _dataPath(std::move(dataPath)) {
    // creates socket
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0) {
        perror("Error creating socket");
    }
    // tries to bind the socket to the port.
    struct sockaddr_in sin{AF_INET, htons(this->port), INADDR_ANY};
    if (bind(_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("Error binding socket");
    }
    // starts listening to the socket.
    if (listen(_sock, 5) < 0) {
        perror("Error listening to a socket");
    }
}

void TCPServer::handleClient() {
    // K of the K nearest neighbors algorithm.
    const int K = 3;
    // accepts the client.
    struct sockaddr_in client_sin{};
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(_sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("Error accepting client");
    }
    // receives messages from the client.
    char buffer[4096]={0};
    char toSend[4096]={0};
    int j = 0;
    int expected_data_len = sizeof(buffer);
    int read_bytes = (int) recv(client_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        cout << "Connection terminated" << endl;
        close(_sock);
        return;
    } else if (read_bytes < 0) {
        perror("Error reading client message");
    } else {
        // processing of client data.
        // client sends the server the input path.
        string unclassifiedPointsString(buffer);
        vector<string> unclassifiedPoints{};
        stringstream str(unclassifiedPointsString);
        string currentPoint;
        while(getline(str,currentPoint)){
            unclassifiedPoints.push_back(currentPoint);
        }
        // classifies the data using euclidean distance.
        map<string,vector<Point>> data = CSVManagement::getClassifiedData(fileHandler::getLines(_dataPath));
        vector<Point> unclassified=CSVManagement::getUnclassifiedData(unclassifiedPoints);
        KNearestNeighbors knn(data,K,"EUC");
        vector<string> classifiedData = knn.classifyData(unclassified);
        //combines the classified data into one string (with ' ' (space) as separation between classifications).
        for (int i = 0; i < classifiedData.size(); i++) {
            if (i == 0) {
                for (auto c: classifiedData.at(0)) {
                    toSend[j] = c;
                    j++;
                }
            } else {
                toSend[j]='\n';
                j++;
                for (auto c: classifiedData.at(i)) {
                    toSend[j] = c;
                    j++;
                }
            }
        }

    }
    //sends the combined string of the classifications.
    int sent_bytes = (int) send(client_sock, toSend, read_bytes, 0);
    if (sent_bytes < 0) {
        perror("Error sending to client");
    }
    close(_sock);
}