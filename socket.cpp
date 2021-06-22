#include <iostream>
#include <string>
#include <sys/socket.h>
using namespace std;

// Socket function
// will be used to create all the sockets later on
int createSocket(string host,int port){
	socket(AF_INET, SOCK_STREAM, 0);
	if (socket(AF_INET, SOCK_STREAM, 0) < 0){
		cout << "[!] Socket failed to be created \n Exiting... \n";
		exit(1);
	}
	else {
		cout << "[*] Socket has been created \n";
	};
	return 0;
};

// MAIN
int main(){
	createSocket("kristofhracza.com",443);
	return 0;
}
