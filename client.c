#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define SERVER_PORT 4444
#define NUM_THREAD 100

int main()
{
	int clientSocket;
	int ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1)
    {
        printf("Socket creation failed\n");
        exit(1);
    }
    printf("Client Socket created successfully!\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(SERVER_PORT);

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));     

		if(ret < 0)
		{
			printf("Error in connection\n");
    		exit(1);
        }
        printf("successfully Connected!");



while(1)
{

		printf("Please provide required value N: \t");
		scanf("%s", buffer);
		send(clientSocket, buffer, strlen(buffer), 0);

		if(strcmp(buffer, ":exit") == 0){
			close(clientSocket);
			printf("Disconnected from server\n");
			exit(1);
		}

		if(recv(clientSocket, buffer, 1024, 0) < 0){
			printf("Error in receiving data.\n");
		}
		else{
			printf("Server: \t%s\n", buffer);
		}
}


return 0;
}
