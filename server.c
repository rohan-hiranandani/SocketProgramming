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
//concurrent server


 
void *func(void *arg)
{


  char secondbuf[1024];
  char arrt[1024] = "/proc/";
  int pid;
  int ff;
  int n;
  int ser_socket = *((int *)arg);
  
  memset(secondbuf,'\0',sizeof secondbuf);
  read(ser_socket , secondbuf, 1024);
printf("client value of N: %s\n",secondbuf);

  for(pid = 1; pid<123456; pid++)
    {
	char ab[1000000];
	sprintf(ab, "%d", pid);
	
        strcat(arrt, ab);
	strcat(arrt, "/stat");
        ff = open(arrt, O_RDONLY);
        if(ff != -1)
        {
         //n = read(ff, secondbuf, 1024);  
	 char* tok = strtok(secondbuf, " ");
	 int sp = 0;
	 
	 while(tok != NULL)
	 {
          sp++;
    
          
         }
	     
	}

    }
  
}



int main()
{
  char buffer[1024];
  pthread_t childpid; 

 	struct sockaddr_in serverAddr;
 	struct sockaddr_in newAddr;

  int sockfd;
  int ret;
  int newSocket;

  sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (sockfd == -1)
    {
        printf("Socket creation failed\n");
        exit(1);
    }
    printf("Server Socket created successfully!\n");


    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(SERVER_PORT);


	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));     

		if(ret < 0)
		{
			printf("Binding Failed!\n");
    		exit(1);
        }
        printf("Binding to port %d successful!\n", 4444);


		
		if(listen(sockfd, 15) == 0){
			printf("Listening..\n");
		}
		else{
			printf("Error in binding and unable to listen!\n");
		}


pthread_t thd[100];

int i = 0;

while(1)
{
	int s_size = sizeof(newAddr);
	newSocket = accept(sockfd, (struct sockaddr*)&newAddr, (socklen_t*)&s_size);
	
	if(newSocket<0){
		exit(1);
	}
	printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

	
	if(pthread_create(&thd[i++], NULL, func, &newSocket) != 0){
	
	
		continue;
		//close(sockfd);???
	/*
		while(1){
			recv(newSocket, buffer, 1024, 0);//recv works for integer values only ig
			if(strcmp(buffer, ":exit") == 0)
			{
				printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
				break;
			}
			else
			{
				printf("Client has provided: %s\n", buffer);
				bzero(buffer, sizeof(buffer));
			}
		}
		*/
	}
	
}

close(newSocket);

return 0;


}
