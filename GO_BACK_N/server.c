#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<time.h>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<signal.h>

int main(){
    int sockfd,connfd;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len;
    char buff[1024];
    time_t ticks;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        printf("socket creation failed...\n");
        exit(0);
    }else{
        printf("Socket successfully created..\n");
    }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(5000);
    if((bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)))!=0){
        printf("socket bind failed...\n");
        exit(0);
    }else{
        printf("Socket successfully binded..\n");
    }
    if((listen(sockfd,5))!=0){
        printf("Listen failed...\n");
        exit(0);
    }else{
        printf("Server listening..\n");
    }
    len = sizeof(cliaddr);
    connfd = accept(sockfd,(struct sockaddr*)&cliaddr,&len);
    if(connfd<0){
        printf("server acccept failed...\n");
        exit(0);
    }else{
        printf("server acccept the client...\n");
    }
    while(1){
        bzero(buff,sizeof(buff));
        read(connfd,buff,sizeof(buff));
        printf("From client: %s\t To client : ",buff);
        bzero(buff,sizeof(buff));
        n=0;
        while((buff[n++]=getchar())!='\n');
        write(connfd,buff,sizeof(buff));
        if(strncmp("exit",buff,4)==0){
            printf("Server Exit...\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}