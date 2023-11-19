#ifndef SERVER_HPP
#define SERVER_HPP

class SimpleWebServer {
public:
    SimpleWebServer(int port);
    ~SimpleWebServer();

    void start();

private:
    int server_socket;
    int port;

    void setupSocket();
};

#endif
