#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

int welcomeSocket, newSocket, nBytes;


int main() {
  srand(time(NULL));
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  char buffer[1024];

  welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
  serverAddr.sin_port = htons(4444);

  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  if (listen(welcomeSocket, 5) == 0) {
    printf(GRN "Success" RESET " - Listening...\n");
  } else {
    printf(RED "Error" RESET " - Unable to start server.\n");
    exit(0);
  }

  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  if(newSocket<0){
    printf(RED "Error" RESET " - Error on binding!\n");
    exit(0);
  }
  else{
    printf(GRN "Success" RESET " - Client Attached.\n");
    char game[9];
    game[9] = '\0';
    recv(newSocket, game, 9, 0);
    printf("Message: %s\n", game);
    if (game[7] == '1'){
      printf(YEL "Info" RESET " - Player must go first.\n");
    } else {
      printf(YEL "Info" RESET " - Bot must go first.\n");
    }

  }
  printf(YEL "Info" RESET " - Ending Session\n");
  sleep(1);
  close(newSocket);
  close(welcomeSocket);
  return 0;
}
