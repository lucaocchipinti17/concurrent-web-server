#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd>   

class Socket() {
    private:
        int sockfd;
        int clientfd;
        sockaddr_in server_addr;

    public:
        Socket() {
            // create socket
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0) {
                std::cerr << "Error creating socket" << std::endl;
                exit(EXIT_FAILURE);
            }


        }
}

