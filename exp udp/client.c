#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    struct sockaddr_in client;
    int sd=socket(AF_INET,SOCK_DGRAM,0);
    if (sd<0)
    printf("error in socket");

    char b[100];
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=3003;

    fgets(b,100,stdin);
    if(sendto(sd,b,100,0,(struct sockaddr *)&client,sizeof(client))<0)
        printf("error in sending");
    return 0;

}