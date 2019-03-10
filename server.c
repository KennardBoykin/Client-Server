/* Compilation: gcc -o server server.cExecution  : ./server 5000*/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int sockfd, newsockfd, portno, clilen, n;
  struct sockaddr_in serv_addr, cli_addr;
  char buffer[256]; //date from the message
  char vStr[256]; //vowel string
  char cmd[]= "Bye\n"; //command sent from client to close connection

  if(argc < 2){ //port number argument
    printf("\nPort number is missing...\n");exit(0);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0); //type of socket
  if (sockfd < 0)
  error(EXIT_FAILURE, 0, "ERROR opening socket");

  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;

serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);
if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
error(EXIT_FAILURE, 0, "ERROR binding");
printf("\nServer Started and listening to the port %d\n", portno);
listen(sockfd, 1);

while(1){
  //Connecting with the client
  clilen=sizeof(cli_addr);
  newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
  if (newsockfd < 0)
    error(EXIT_FAILURE, 0, "ERROR on accept");

int connected = 1;
  printf("\nClient is connected...\n");
  //send and recieve while loop
while(connected){
  //Receiving the message from the client
  bzero(buffer,256);
  n = read(newsockfd,buffer,255);

  if(n < 0)
  error(EXIT_FAILURE, 0, "ERROR reading from socket");
  else{
        printf("\nClient has sent: %s\n", buffer);
        if(strcmp(buffer, cmd) == 0 ){//returns zero if the string matches "Bye"
           //close connection
           connected = 0; //closes the while
             printf("\nGoodbye!\n"); //prints goodbye
             close(newsockfd); //closes socket
             break; // breaks inner while
           }
    else{
    int i = 0;
    int vCount = 0;
        while(buffer[i] != '\0'){ //loop until the end of the string character
          if(buffer[i] == 'a'|| buffer[i] == 'A' || buffer[i]=='e'|| buffer[i] == 'E' || buffer[i] =='i'|| buffer[i] == 'I' || buffer[i] =='o'|| buffer[i] == 'O' || buffer[i] == 'u' || buffer[i] == 'U'){
            //printf("VOWELS");
            vCount++; //increase the amount of vowels
          }
            i++; //increment through the message
        } //end string while
//         printf("\nYou have this many vowels: %d\n", vCount);
//	printf("Sending Message");
	//convert int to a string which can be sent
          sprintf(vStr, "%d", vCount);

         }
            //Sending the message to the client
            bzero(buffer,256);
  //                  printf("\nSending message... ");
            //      scanf("%s", buffer);
            n = write(newsockfd, vStr, strlen(vStr));

                       //Closing the connection
                       //close(newsockfd);
        }
} //end connected while

    }//end big while
          return 0;
  }//end main
