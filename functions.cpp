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

//CHECK IF FILE OR FOLDER EXIST
bool fexists(const string &filename){
    ifstream ifile(filename.c_str());
    return (bool)ifile;
}

//USER COMMAND
int User(int client, char user[1024], int& state){
    char buff[1024];
    char sendbuff[1024];
    sprintf(buff, "./clients/%s",user);
    //cout<<"OK\n";
    if(fexists(buff)){
        sprintf(sendbuff,"+OK Hello %s- Send PASS<CRLF>",user);
        state = 1;
    }
    else {
        strcpy(sendbuff,"-ERR...Send Username again<CRLF>");
    }
    send(client, sendbuff, 1024,0);
    return 0;
}

//PASS COMMAND
int Pass(int client, char user[1024], char pass[1024], int& state){
    char buff[1024];
    char sendbuff[1024];
    sprintf(buff, "./clients/%s/%s.pwd",user, pass);
    //cout<<"OK\n";
    if(fexists(buff)){
        sprintf(sendbuff,"+OK %s- Welcome and Proceed<CRLF>",user);
        state = 2;
    }
    else {
        strcpy(sendbuff,"-ERR...Try again<CRLF>");

    }
    send(client, sendbuff, 1024,0);
    return 0;
}

//STAT COMMAND
std::ifstream::pos_type filesize(const string filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int Stat(int client, char user[1024]){
    string user_name = user;
    string dir = "./clients/"+user_name+"/mails";
    //sprintf(dir,"./%s",user_name);
    vector<string> files = vector<string>();

    getdir(dir,files);

    int total_size = 0;
    for (int i = 0;i < files.size()-2;i++) {

        total_size += filesize(dir+"/"+files[i]);
    }
    char message[1024];
    sprintf(message,"+OK %d %d\n",(int)files.size()-2,total_size);
    send(client,message,1024,0);
    return 0;
}


//LIST COMMAND
//LIST COMMAND
int List(int client, char user[1024]){
    string user_name = user;
    string dir = "./clients/"+user_name+"/mails";

    vector<string> files = vector<string>();

    getdir(dir,files);

    int file_size = 0;
    string message ="";
    char out[1024];
    for (int i = 0; i < files.size()-2; i++) {
        file_size = filesize(dir+"/"+files[i]);
/*        char temp[60];
        sprintf(temp,"%s %d\n",files[i],file_size);
*/        string temp = files[i]+" "+to_string(file_size)+"\n";
        message += temp;
    }
    strcpy(out, message.c_str()); 
    send(client,out,1024,0);
    return 0;
}


//RETR COMMAND
int Retr(int client, char user[1024], char id[1024]){

    char path[120];
    sprintf(path,"./clients/%s/mails/%s",user,id);
    char out[1024];
    string t="Error: invalid file\n";
    strcpy(out, t.c_str()); 
    if(fexists(path))
    { 
      std::ifstream in(path);
      std::string contents((std::istreambuf_iterator<char>(in)), 
      std::istreambuf_iterator<char>());
      //cout<<contents.c_str();
      send(client,contents.c_str(),1024,0);
    }
    
    else
    {
      send(client,out,1024,0);
    }
    return 0;
}


//DELE COMMAND
int Delete(int client, char user[1024], char file[500]){
    char buff[500];
    char sendbuff[1024];
    sprintf(buff, "./clients/%s/mails/%s.txt", user, file);
    int temp=remove(buff);
    if(temp!=0){
        strcpy(sendbuff,"-ERR deleting file<CRLF>");
        send(client, sendbuff, 1024, 0);
    }
    else{
        strcpy(sendbuff,"+OK file deleted<CRLF>");
        send(client, sendbuff, 1024, 0);
    }
    return 0;
}

//QUIT COMMAND
int Quit(int client){
    char buff[1024];
    sprintf(buff, "+Exiting");
    send(client, buff, 1024, 0);
    return 0;
}
