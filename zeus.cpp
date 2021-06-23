#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

// Socket
int socketOps(string target,int port){
	// Creation
	struct sockaddr_in host;
	int s,conn;
	inet_pton(AF_INET,"127.0.0.1",&host.sin_addr);
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
	return 0;
};

// MAIN
int main(){
	socketOps("kristofhracza.com",8080);
	return 0;
}
