#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/select.h>
#include <poll.h>

#include "parser.hpp"
#include "insert.hpp"
#include "delete.hpp"
#include "select.hpp"

#define PORT 7432
#define MAX_CLIENTS 2
#define BUFFER_SIZE 1024

void hendle_client(char *buffer, TableJson &tableJS)
{
    std::istringstream iss(buffer);
    string command;
    cout << ">>> ";
    getline(iss, command);

    if (command.find("INSERT") == 0)
    {
        string answer;
        memset(buffer, 0, BUFFER_SIZE); // очистка буфера
        if (insert(command, tableJS) == 1)
        {
            answer = "Inserted badly, think about it again and question from server\n";
            strcpy(buffer, answer.c_str());
        }
        else{
            answer = "Inserted successfully!\n";
            strcpy(buffer, answer.c_str());
        }
        return;
    }
    else if (command.find("DELETE") == 0)
    {
        string answer;
        memset(buffer, 0, BUFFER_SIZE); // очистка буфера
        if (del(command, tableJS) == 1){
            answer = "Deleted badly, think about it again\n";
            strcpy(buffer, answer.c_str());
        }
        else {
            answer = "Deleted successfully!\n";
            strcpy(buffer, answer.c_str());
        }
        return;
    }
    else if (command.find("SELECT") == 0)
    {
        string answer;
        if (select(buffer, BUFFER_SIZE, tableJS) == 1){
            answer = "Selected badly, think about it again\n";
            strcpy(buffer, answer.c_str());
        }
        else {
            answer = "Selected successfully!\n";
        }
        return;
    }
    else
    {
        string answer = "Incorrect command.\n";
        strcpy(buffer, answer.c_str());
        return;
    }
}

int main()
{
    TableJson tableJS;
    parsing(tableJS);

    char buffer[BUFFER_SIZE];
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cout << "Server socket cant be created";
        return 1;
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) //привязать сокет
    {
        std::cout << "Can't bind server socket";
        return 1;
    }

    if (listen(server_socket, MAX_CLIENTS) == -1)
    {
        std::cout << "Can't listen on port";
        return 1;
    }

    struct pollfd server_fds[MAX_CLIENTS + 1]; // чекаем не только тех кто работают, но и кто приперся
    memset(server_fds, 0, sizeof(server_fds));
    server_fds[0].fd = server_socket;
    server_fds[0].events = POLLIN; // событие на чтении
    for (nfds_t clientsSocketNumber = 1; clientsSocketNumber <= MAX_CLIENTS; clientsSocketNumber++)
    {
        server_fds[clientsSocketNumber].fd = -1;         // не читаем в poll
        server_fds[clientsSocketNumber].events = POLLIN; // ждем события
    }

    nfds_t clientCounter = 0;
    nfds_t currentSockets = 1;
    int serverIsFull = 0;
    std::cout << "Server started. Listen on port 7432...\n";

    while (1)
    {
        if (poll((struct pollfd *)&server_fds[serverIsFull], currentSockets, -1) == -1)
        {
            std::cout << "Can't using poll";
            return 1;
        }

        if ((server_fds[0].revents & POLLIN) && (serverIsFull == 0)) // (пр.битовая маска)
        {
            int clientFd; //нови клиенти
            if ((clientFd = accept(server_socket, NULL, NULL)) == -1)
            {
                std::cout <<"Can't accept";
                exit(1);
            }
            std::cout << "New client\n";
            clientCounter++;
            server_fds[clientCounter].fd = clientFd;
            currentSockets++;
            if (clientCounter == MAX_CLIENTS)
            {
                serverIsFull = 1;
            }
        }
        //сделано для того, чтобы пришел и написал
        poll((struct pollfd *)&server_fds[serverIsFull], currentSockets, -1);
        for (nfds_t clientSocketNumber = 1; clientSocketNumber <= clientCounter; clientSocketNumber++)
        {
            if (server_fds[clientSocketNumber].revents & POLLIN) //нам пишут - можем делать read, не блокируемся 
            {   
                // в буфер инфу читаем
                size_t readed_bytes = read(server_fds[clientSocketNumber].fd, buffer, BUFFER_SIZE); 
                if (readed_bytes == 0)
                {
                    cout << "Delete client\n";
                    close(server_fds[clientSocketNumber].fd);
                    server_fds[clientSocketNumber].fd = server_fds[clientCounter].fd;
                    server_fds[clientCounter].fd = -1;
                    clientCounter--;
                    currentSockets--;
                    serverIsFull = 0;
                    continue;
                }
                std::string message(buffer, readed_bytes);
                cout << "Client: " << message << "\n";
                hendle_client(buffer, tableJS);
                write(server_fds[clientSocketNumber].fd, buffer, BUFFER_SIZE);
                memset(buffer, 0, BUFFER_SIZE);
            }
        }
    }

    return 0;
}
