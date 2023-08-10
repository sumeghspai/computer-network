#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    struct sockaddr_in server,client;
    int sd=socket(AF_INET,SOCK_DGRAM,0);
    if(sd<0)
        printf("Error in socket creation");
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=3003;
    if(bind(sd,(struct sockaddr *)&server,sizeof(server))<0)
        printf("error in binding");
    
    char b[100];
    socklen_t len= sizeof(server);
    printf("server waiting\n");
 
    if(recvfrom(sd,b,100,0,(struct sockaddr *)&server,&len)<0);
        printf("error in recieving");
    printf("%s",b);
    return 0;





}
