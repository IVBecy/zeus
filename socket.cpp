#include <iostream>
#include <string>
#include <sys/socket.h>
using namespace std;

// Socket function
// will be used to create all the sockets later on
void createSocket(string host,int port){
	socket(AF_INET, SOCK_STREAM, 0);
};

// MAIN
int main(){
	createSocket("kristofhracza.com",443);
	return 0;
}
