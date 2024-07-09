#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <arpa/inet.h>

#define PORT 5035
#define MAX 60
int main()
{
       int sockfd,n;
       struct sockaddr_in serv_addr;
       char send[MAX],recvline[MAX];
       sockfd=socket(AF_INET,SOCK_STREAM,0);
       serv_addr.sin_family=AF_INET;
       serv_addr.sin_addr.s_addr=INADDR_ANY;
       serv_addr.sin_port=PORT;

       connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
       printf("\nEnter the source file name : \n");
       scanf("%s",send);

       write(sockfd,send,strlen(send));
       
       while((n=read(sockfd,recvline,MAX))!=0)
       {
          printf("%s",recvline);
       }
       close(sockfd);
       return 0;
}

/*
output:

client.c
Enter the source file name: demo.txt
This is the file to be tansfered
server.c
Binding...
Listening...
client message 
File name :demo.txt
File transfered

*/