The following is an implementation of simplified and interactive POP3 client server. The output of the server to client request is shown on client terminal.

Complile the server program using 	g++ functions.cpp server1.cpp -o server  -pthread
Run the server program using 		./server (port-number)

Complile the client program using 	g++ -pthread -o client client.cpp
Run the client program using 		./client (port-number of server)

The commands can be executed in the following way:
1. User command : USER <username><CRLF>  eg. USER Dakshit<CRLF>
2. Password command : PASS <password><CRLF>  eg. PASS abc<CRLF>
3. Stat command (to show number of mails and total size) : STAT <CRLF>
4. List command (lists all the mails with size of each) : LIST <CRLF>
5. Return command (Displays entire mail) : RETR <filename><CRLF>  eg. RETR 1.txt<CRLF>
6. Delete command (Deletes a particular mail) : DELE <filename><CRLF>  eg. DELE 1<CRLF>
7. Quit command (Closes the client-server connection) : QUIT <CRLF>
 
The USER command has to executed first after the connection of client with server. 
The 2nd command has to be password else the rest of the commands will not work (cliet has to be autheticated) .
