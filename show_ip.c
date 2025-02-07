#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
        struct addrinfo hints;
        struct addrinfo *res;
        struct addrinfo *p;
        int status;
        char ipstr[INET6_ADDRSTRLEN];
        if (argc != 2)
        {
                fprintf(stderr, "usage : show ip address");
                return 1;
        }
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        status = getaddrinfo(argv[1], NULL, &hints, &res);
        if (status != 0)
        {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
                return 2;
        }
        p = res;
        while (p)
        {
                void *addr;
                char *ip_type;
                if (p->ai_family == AF_INET)
                {
                        // ipv4
                        struct sockaddr_in *ip4 = (struct sockaddr_in *)p->ai_addr;
                        addr = &ip4->sin_addr;
                        ip_type = "ipv4";
                }else{
                        
                }
                p = p->ai_next;
        }
}