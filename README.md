## KNN Classifier Server

The KNN Classifier Server has a server that allows multiple clients to join, upload their data, and get information about their data relating to the K-Nearest-Neighbors algorithm.
The server allowes the clients to run commands that analyses their data in different ways, and it allows them to change the KNN algorithm settings.

# Server capabilities

- The server can handle multiple clients at once.
- The server times out after no client joined in the past 5 minutes.
- When the server times out, it waits for all the clients that already joined to finish before closing. New connections are automatically rejected after the server times out.

# The Commands

The KNN classifier server has a command line interface that allows the client to perform certain commands:
- **upload an unclassified csv data file:**
asks the client to provide a train csv file that contains a list of points and their classifications. points from this file will be used in the KNN algorithm to classify points. Then, it asks the client to upload a test csv file that contains a list of points without classifications. these points will be then classified (in a different command) by the KNN algorithm.
- **algorithm settings:** 
shows the client the parameters of the KNN algorithm, and gives them an option to change them. After shown the settings, the client can either not provide new parameters by pressing the enter key, or provide new parameters by typing them in the form: "X Y", where X is a number between 1 and 10 and Y is the name of a known distance function. Currently the known distances are: EUC - Euclidean distance, MAN - Manhattan distance, CHE - Chebyshev distance. If the client tries to provide parameters but does so in the wrong format, the command will keep asking for parameters until valid ones are given (in this mode the 'enter' key doesn't exit the function. new parameters must be given after the first try failed).
- **classify data:**
simply classifies the data using the KNN algorithm, and the data provided at the upload command. If the upload command wasn't used yet, it will tell the client to use the upload command first, and nothing will be changed or classified.
- **display results:**
shows the client the results of the classification. If the 'classify data' command wasn't used yet, it will tell the client to use the classify command first. If the KNN settings changed after the last classify data command was used, the old classifications will be shown (the classifications with the old parameters).
- **download results:**
downloads the results of the classification to a path the client provides. If the 'classify data' command wasn't used yet, it will tell the client to use the classify command first. If the KNN settings changed after the last classify data command was used, the old classifications will be downloaded (the classifications with the old parameters).
- **display algorithm confusion matrix:**
uses the points given in the train csv file to show an approximation of the algorithm's accuracy. it shows a matrix of size NxN where N is the number of data types, and the position of row i column j shows how many of type i were identified by the KNN algorithm as type j.

# How we implemented it

Server: 
- A TCP Server that has the main thread accepting clients, a thread for counting how much time passed since the last client joined, and a collection of threads, each of which handles a client that joined.
- The client-server communication is done via the SocketIO class: a class that reads from and writes to a socket of a client. Implements an abstract class 'DefaultIO' that allows for reading and writing.
- The Command Line Interface is done via the CLI class: a class that has a set of default commands - the ones shown above - and it uses a DefaultIO for reading and writing (the server provides CLI with a SocketIO). Each command is provided the DefaultIO held by the CLI class, and it sends certain messages to let the client know how to respond. for example, if a command wants the client to simply print something to the console, the message will start with 'print', and the client will print everything past the 'print' part. If the command wants the client to provide the contents of a file, the message will start with 'getFile' and the client will get a path from the console and send the server its contents. More examples are shown in the code.

Client:
- A TCP Client that has one thread receiving and sending messages to the server. 
- Once a message from the server is received, it is analyzed according to its prefix ('print','getFile',...) and responds accordingly.
- When the client is asked to save something to a file, the writing to the file is done in a different thread to allow the client to keep querying the server without having to wait for the file to download.

# How we divided the work

We divided it into 2 parts: The 1-6 commands portion, and the SocketIO + threads portion. Yoav did the 1-6 commands portion, and Einat did the SocketIO and threads portion.
We feel this is fair because writing the commands takes a long time, but so does learning how to use threads (the timeout portion took about a day!) and integrating sockets into the project. So we though the commands part is about equal, effort/time wise, to learning threads and doing the SocketIO integration.

# How to run

First, compile using:
```
g++ -std=c++11 src/*.cpp src/Commands/*.cpp src/Distance/*.cpp src/Server/Server.cpp -pthread -o Server.out
g++ -std=c++11 src/*.cpp src/Commands/*.cpp src/Distance/*.cpp src/Client/Client.cpp -pthread -o Client.out
```
then, run the server using:
```
./Server.out
```
then, in other terminals (as many as you'd like), run the clients using:
```
./Client.out
```
After that, on the client side you can run any set of commands you want. A set of commands that tests everything that will always work is:
```
1
inputFiles/train.csv
inputFiles/test.csv
2
3 MAN
3
4
5
outputFiles/classified.csv
6
7

```
lines 1-3 will upload the train and test csv files. lines 4-5 will change the algorithm parameter, line 6 will classify the data, line 7 will show the data to the console, lines 8-9 will download the data to outputFiles/classified.csv, line 10 will print the confusion matrix, and line 7 will exit.
