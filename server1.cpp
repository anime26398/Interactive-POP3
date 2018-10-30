
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "functions.h"

using namespace std;

void checkCommand(int client, char user[1024], char command[1024], char buffer[1024], int& state){
    int x=0;

    if(strcmp(command, "USER")==0){
        x=User(client, user,state);
        return ;
    }

    if(state==0)
    {
        string alert = "First enter the username\n";
        send(client,alert.c_str(),1024,0);
    }
    else
    {
        if(strcmp(command, "PASS")==0){
            x=Pass(client, user, buffer,state);
        }

        if(state!=2)
        {   
            string alert = "Incorrent username or password\n";
            send(client,alert.c_str(),1024,0);
        }
        else
        {
            if(strcmp(command, "STAT")==0){
                x=Stat(client, user);
            }
            if(strcmp(command, "LIST")==0){
                x=List(client, user);
            }
            if(strcmp(command, "RETR")==0){
                x=Retr(client, user, buffer);
            }
            if(strcmp(command, "DELE")==0){
                x=Delete(client, user, buffer);
            }
            if(strcmp(command, "QUIT")==0){
                x=Quit(client);
                state = 0;
            }
        }
    }
}


void connectClient(int client)
{
    int bufsize = 1024;
    char user[1024];
    char sendbuff[1024];
    char recvbuff[1024];
    char command[1024];
    char buffer[1024];
    int state = 0;

    //acknowledge for successful connection
    strcpy(buffer, "=> Server connected...\n");
    send(client, buffer, bufsize, 0);
    memset(buffer, 0, bufsize);

    //receive username
    recv(client, buffer, bufsize, 0);
    int temp=0;
    //char user[1024];
    int i=0;
    for(i=0;i<1024;i++){
        if(buffer[i]==' ')break;
        else{
            command[i]=buffer[i];
        }
    }
    //cout<<command<<endl;
    int k=0;
    i++;
    while(buffer[i]!='<'){
        user[k]=buffer[i];
        i++;
        k++;
    }
    checkCommand(client, user, command, buffer,state);
    int x=0;
    while(x!=-1){
        memset(buffer,0,1024);
        memset(sendbuff, 0, 1024);
        memset(recvbuff, 0, 1024);
        memset(command, 0, 1024);
        recv(client, buffer, 1024, 0);
        //cout<<buffer<<endl;

        i=0;
        for(i=0;i<1024;i++){
            if(buffer[i]==' ')break;
            else{
                command[i]=buffer[i];
            }
        }

        // if(strcmp(command, "QUIT")==0){
        //     x=-1;
        //     continue;
        // }

        //if(strcmp(command,"USER")==0||strcmp(command,"PASS")==0||strcmp(command,"RETR")==0||strcmp(command,"DELE")==0){
        k=0;
        i++;
        while(buffer[i]!='<'){
            recvbuff[k]=buffer[i];
            i++;
            k++;
        }
        //}
        cout<<command<<endl;
        checkCommand(client, user, command, recvbuff,state);

    }
}

int main(int argc, char *argv[])
{
    int server;
    int portNum = atoi(argv[1]); // NOTE that the port number is same for both client and server

    bool isExit = false;
    int client;
    int bufsize = 1024;
    char buffer[bufsize];
    struct sockaddr_in server_addr;
    socklen_t size;

    server = socket(AF_INET, SOCK_STREAM, 0);

    if (server < 0)
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket server created" << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portNum);

    if ((bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0)
    {
        cout << "=> Error binding connection, Socket alreadyv in use" << endl;
        return -1;
    }

    size = sizeof(server_addr);
    cout << "Looking for clients..." << endl;

    /* ------------- LISTENING CALL ------------- */
    /* ---------------- listen() ---------------- */

    listen(server, 1);
    // first check if it is valid or not

    while (client = accept(server, (struct sockaddr *)&server_addr, &size))
    {
        thread th1(connectClient, client);
        th1.detach();
        cout<<"\n New client connected";
    }

    close(server);
    return 0;
}
