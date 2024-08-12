#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

class UDPServer
{
public:
    UDPServer(int port = 12345);
    ~UDPServer();

    bool initialize();
    std::string receiveMessage();                 // Method to receive a message
    void sendMessage(const std::string &message); // Method to send a message to all clients

private:
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len;
    int port;
    static const int BUFLEN = 512;
    char buffer[BUFLEN];

    // Vector to store the clients' addresses
    std::vector<struct sockaddr_in> clients;

    bool isNewClient(struct sockaddr_in &client);
};

UDPServer::UDPServer(int port) : port(port), sockfd(-1)
{
    memset(&servaddr, 0, sizeof(servaddr));
}

UDPServer::~UDPServer()
{
    if (sockfd != -1)
    {
        close(sockfd);
    }
}

bool UDPServer::initialize()
{
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        return false;
    }

    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        sockfd = -1;
        return false;
    }

    len = sizeof(servaddr);
    return true;
}

std::string UDPServer::receiveMessage()
{
    struct sockaddr_in cliaddr;
    int n = recvfrom(sockfd, (char *)buffer, BUFLEN, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    if (n > 0)
    {
        buffer[n] = '\0';
        std::cout << "Received: " << buffer << std::endl;

        // Check if this is a new client
        if (isNewClient(cliaddr))
        {
            clients.push_back(cliaddr);
            std::cout << "New client added: " << inet_ntoa(cliaddr.sin_addr) << std::endl;
        }

        return std::string(buffer);
    }
    return "";
}

void UDPServer::sendMessage(const std::string &message)
{
    for (const auto &client : clients)
    {
        sendto(sockfd, message.c_str(), message.size(), MSG_CONFIRM, (const struct sockaddr *)&client, len);
    }
    std::cout << "Sent Message to all clients: " << message << std::endl;
}

bool UDPServer::isNewClient(struct sockaddr_in &client)
{
    // Check if the client address is already in the list
    return std::find_if(clients.begin(), clients.end(), [&](const struct sockaddr_in &c)
                        { return c.sin_addr.s_addr == client.sin_addr.s_addr && c.sin_port == client.sin_port; }) == clients.end();
}
