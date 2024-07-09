#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define PORT 5035
#define MAX 60

int main(){

       int sockfd, newsockfd, clength;
       char buff[4096]={0};
       FILE *f1;
       struct sockaddr_in serv_addr,cli_addr;
       char str[MAX] = {0};

       sockfd=socket(AF_INET, SOCK_STREAM,0);
       serv_addr.sin_family=AF_INET;
       serv_addr.sin_addr.s_addr=INADDR_ANY;
       serv_addr.sin_port=PORT;

       printf("\nBinded");
       bind(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
       printf("\nListening...");
       listen(sockfd, 5);
       clength=sizeof(cli_addr);
       newsockfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clength);
       read(newsockfd, str, MAX);   
       printf("\nClient message\n File Name : %s\n", str);
       f1=fopen(str, "r");
       while(fgets(buff, 4096, f1)!=NULL)
       {
            write(newsockfd, buff,MAX);
            printf("\n");
       }
       fclose(f1);
       close(sockfd);
       printf("\nFile Transferred\n");
       
       return 0;
}