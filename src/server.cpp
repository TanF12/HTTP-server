#include "server.hpp"
#include "utils.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CONNECTIONS 10

SimpleWebServer::SimpleWebServer(int port) : port(port) 
{
    setupSocket();
}

SimpleWebServer::~SimpleWebServer() 
{
    close(server_socket);
}

void SimpleWebServer::setupSocket() 
{
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        handle_error("Erro ao criar socket");
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0) 
    {
        handle_error("Erro ao vincular o socket");
    }

    if (listen(server_socket, MAX_CONNECTIONS) < 0) 
    {
        handle_error("Erro ao escutar por conexões");
    }

    std::cout << "Servidor escutando na porta " << port << "...\n";
}

void SimpleWebServer::start() 
{
    sockaddr_in client_addr;
    socklen_t addr_size = sizeof(client_addr);
    char buffer[1024] = {0};
    char* response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nHello, world!";

    while(1) 
    {
        int new_socket;
        if((new_socket = accept(server_socket, reinterpret_cast<struct sockaddr*>(&client_addr), &addr_size)) < 0) 
        {
            handle_error("Erro ao aceitar conexão");
        }

        read(new_socket, buffer, sizeof(buffer));
        std::cout << "Requisição recebida:\n" << buffer << std::endl;

        write(new_socket, response, strlen(response));
        std::cout << "Resposta enviada:\n" << response << std::endl;

        close(new_socket);
    }
}
