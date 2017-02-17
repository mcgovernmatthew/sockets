#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "libft.h"
int       main(int argc, char **argv)
{
  int     sock;
  struct  sockaddr_in server;
  int     mysock;
  char    buff[1024];
  int     rval;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  argc = 0;
  argv = NULL;
  if(sock < 0)
  {
    perror("Failed to create socket.");
    exit(1);
  }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(5000);


  if (bind(sock, (struct sockaddr *)&server, sizeof(server)))
  {
    perror("Failed to bind");
    exit(1);
  }

  listen(sock, 1);

while (1)
  {
    mysock = accept(sock, (struct sockaddr *) 0, 0);
    if (mysock == -1)
      perror("Failed to accept");
    else
    {
      memset(buff, 0, sizeof(buff));
      if ((rval = recv(mysock, buff, sizeof(buff), 0)) < 0)
      {
        perror("Failed to read message stream");
        exit(1);
      }
      else if (rval == 0)
      {
        printf("%s\n", "Closing connection\n");
        exit(1);
      }
      else
        printf("%s\n", buff);
      printf("Message received: \n (rval = %d)\n", rval);
      close(mysock);
    }
}
    return (0);
}
