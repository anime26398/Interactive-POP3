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
using namespace std;

//CHECK IF FILE OR FOLDER EXIST
bool fexists(const string &filename);

//USER COMMAND
int User(int client, char user[1024], int& state);

//PASS COMMAND
int Pass(int client, char user[1024], char pass[1024], int& state);

//STAT COMMAND
std::ifstream::pos_type filesize(const string filename);

int getdir (string dir, vector<string> &files);

int Stat(int client, char user[1024]);


//LIST COMMAND
//LIST COMMAND
int List(int client, char user[1024]);

//RETR COMMAND
int Retr(int client, char user[1024], char id[1024]);

//DELE COMMAND
int Delete(int client, char user[1024], char file[500]);


//QUIT COMMAND
int Quit(int client);