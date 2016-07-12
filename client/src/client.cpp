#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define port_no 65000

using namespace std;

const char* IP_ADDRESS = "172.19.23.32";
char *msg="wtf";
int sock;


void CleanUp(void){
	close(sock);
}

int main(){

	struct sockaddr_in server;
	char server_reply[2000];

	atexit(CleanUp);

	//----------------------------------------------

	cout<<"CLIENT: Creating socket"<<endl;
	sock=socket(AF_INET, SOCK_STREAM, 0);
	if(sock==-1){
		perror("Can't create socket");
		 fflush(stdout);
	}

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(IP_ADDRESS);
	server.sin_port=htons(port_no);

	//-------------------------------------------------

	cout<<"CLIENT: Connecting to Server..."<<endl;

	if(connect(sock,(struct sockaddr *)&server,sizeof(server))<0){
		perror("Can't connect");
		return 1;
	}
	cout<<"CLIENT: Connected"<<endl;

	while(1){

		cout<<"CLIENT: Sending mesage to server"<<endl;

		if(send(sock, msg, strlen(msg),0)<0){
			perror("Sending failed");
			break;
		}

		cout<<"CLIENT: Waiting for message from server..."<<endl;

		if(recv(sock,server_reply,2000,0)<0){
			perror("Receiving failed");
			break;
		}
		cout<<"CLIENT: Message from server:"<<server_reply<<endl;

	}

	return 0;
}
