#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#include <string>
#include <iostream>

int main() {
    int addrlen = sizeof(address);
    char buffer[1025] = {0};
    char *hello = "Hello from server";

    // IPV6, TCP, IP
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);


    if (server_fd == 0) {
        std::cout << "couldn't create the socket" << std::endl;
        return 1;
    }


    int opt = 1;

    int set_sockopt_return = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt));

    if (set_sockopt_return != 0) {
        std::cout << "couldn't set socket options: " << set_sockopt_return << std::endl;
        return 1;
    }


    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( 8080 );

    int bind_ret = bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address));
    if (bind_ret != 0) {
        std::cout << "couldn't bind: " << bind_ret << std::endl;
        return 1;
    }

    int listen_ret = listen(server_fd, 10);

    if (listen_ret != 0) {
        std::cout << "couldn't listen: " << listen_ret << std::endl;
        return 1;
    }


    std::vector<int> open_sockets;

    while (true) {
        while(true) {
            new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen);
            if (new_socket < 0) {
                break;
            }
            open_sockets.push_back(new_socket);
        }

        for (int socket : open_sockets) {
            int valread = read(socket, buffer, 1024);
            if (valread <= 0) {
                continue;
            }
            buffer[valread] = '\0';
            std::cout << buffer << std::endl;
        }

    }

}