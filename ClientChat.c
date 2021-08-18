#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAXLINE 4096

void * Receive_message(void * sockID){

	int clientSocket = *((int *) sockID);

	while(1){

		char data[MAXLINE];
		int read = recv(clientSocket,data,MAXLINE,0);
		data[read] = '\0';
		printf("%s\n",data);

	}

}

int main(){

	int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) return 0;

	printf("Connection established\n");

	pthread_t thread;
	pthread_create(&thread, NULL, Receive_message, (void *) &clientSocket );

	while(1){

		char input[MAXLINE];
		scanf("%s",input);

		if(strcmp(input,"LIST") == 0){

			send(clientSocket,input,MAXLINE,0);

		}
		if(strcmp(input,"SEND") == 0){

			send(clientSocket,input,MAXLINE,0);
			
			scanf("%s",input);
			send(clientSocket,input,MAXLINE,0);
			
			scanf("%[^\n]s",input);
			send(clientSocket,input,MAXLINE,0);

		}

	}


}