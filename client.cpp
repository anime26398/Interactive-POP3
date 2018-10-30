#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <netdb.h>

using namespace std;

void receiver(int client)
{
    bool isExit = false;
    int bufsize = 1024;
    // char buffer[bufsize];
    char buffer[bufsize];
    int x =-1;
        x = recv(client, buffer, bufsize, 0);
        cout << buffer;
        memset(buffer, 0, sizeof(buffer));
        cout << endl;
        cout<<endl;
    
}
int main(int argc, char *argv[])
{

    int client;
    int portNum = atoi(argv[1]); // NOTE that the port number is same for both client and server
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char *ip = "127.0.0.1";

    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0)
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    cout << "\n client socket created" << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portNum);

    if (connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "Connect to server with port number: " << portNum << endl;

    //cout << "=> Awaiting confirmation from the server..." << endl; //line 40
    cout<<"[Server] : ";
        receiver(client);
        cout<<endl<<"[Client] : ";

    // enter user-name
    char sendbuff[1024];
    cin.getline(sendbuff, 1024);
    send(client, sendbuff, 1024, 0);
    cout<<"[Server] : ";
        receiver(client);
        cout<<endl<<"[Client] : ";

    int x=0;
    while(x!=-1){
        memset(sendbuff,0,1024);
        cin.getline(sendbuff, 1024);
        //cout<<sendbuff<<endl;
        //if(sendbuff[0]=='Q')x=-1;
        send(client, sendbuff, 1024, 0);
        cout<<"[Server] : ";
        receiver(client);
        cout<<endl<<"[Client] : ";
    }
    close(client);
    
    
    return 0;
}
