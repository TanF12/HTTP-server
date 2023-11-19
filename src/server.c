#include "server.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CONNECTIONS 10

void start_server(int port) {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    char buffer[1024] = {0};
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nHello, world!";

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        handle_error("Erro ao criar socket");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
  
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        handle_error("Erro ao vincular o socket");
    }

    if (listen(server_socket, MAX_CONNECTIONS) < 0) {
        handle_error("Erro ao procurar por conexões");
    }

    printf("Servidor aberto na porta %d...\n", port);

    while (1) {
        if ((new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size)) < 0) {
            handle_error("Erro ao aceitar conexão");
        }

        read(new_socket, buffer, sizeof(buffer));
        printf("Requisição recebida:\n%s\n", buffer);

        write(new_socket, response, strlen(response));
        printf("Resposta enviada:\n%s\n", response);

        close(new_socket);
    }
}
