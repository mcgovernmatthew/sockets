#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "libft.h"

int                   main(int argc, char **argv)
{
  int                 sock;
  struct  sockaddr_in server;
  struct  hostent     *hp;

  argc = 2;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    perror("Failed to socket rubies");
    close(sock);
    exit(1);
  }

  server.sin_family = AF_INET;

  hp = gethostbyname(argv[1]);
  if (hp == 0)
    {
      perror("Failed to identify host by name");
      close(sock);
      exit(1);
    }
  memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
  server.sin_port = htons(5000);

  if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
  {
    perror("Failed to connect");
    close(sock);
    exit(1);
  }
  if (send(sock, argv[2], (strlen(argv[2]) * sizeof(char)), 0) < 0)
  {
    perror("Failed to send data");
    close(sock);
    exit(1);
  }
  printf("Sent: %s\n", argv[2]);
  close(sock);
  return (0);
}
