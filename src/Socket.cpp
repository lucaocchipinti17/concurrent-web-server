#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>   
#include <cstdlib>
#include <netinet/in.h>

class Socket {
    private:
        int sockfd = -1;
        int port;

    public:
        explicit Socket(int port) : port(port) {
            // create socket
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0) {
                throw std::runtime_error("Error creating socket");
            }

            // Avoid "Address already in use" on restart
            int opt = 1;
            setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));


            // set server address
            server_addr.sin_family = AF_INET;
            server_addr.sin_addr.s_addr = INADDR_ANY;
            server_addr.sin_port = htons(port);

            // bind socket
            if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
                throw std::runtime_error("Error binding socket");
            }

            // listen for connections
            if (listen(sockfd, 5) < 0) {
                throw std::runtime_error("Error listening on socket");
            }

              
        }
        ~Socket() {
            if (sockfd >= 0) {
                close(sockfd);
            }
        }

        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

        int acceptConnection() {
            sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);

            int clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
            if (clientfd < 0) {
                throw std::runtime_error("Error accepting connection");
            }
            return clientfd;
        }
};

