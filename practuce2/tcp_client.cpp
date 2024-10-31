#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

int main(int argc, char *argv[]){
    int sockfd, port_number; // сокет и номер порта

    if (argc < 3) {
        std::cout << "No port number\n"; // проверка наличия порта
        return 1;
    }
    port_number = atoi(argv[2]);   // забираем порт

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // создание tcp сокета

    if (sockfd < 0) {
        std::cout << "ERROR opening socket"; // если сокет не создан
        return 1;
    }

    struct sockaddr_in serv_addr;                 // структура с адресом
    memset(&serv_addr, 0, sizeof(serv_addr));     // убираем мусор(ут.заполнение памяти)
    serv_addr.sin_family = AF_INET;               // семейство адресов
    serv_addr.sin_port = htons(port_number);      // преобразование хоста в сеть

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) { // если адрес некорректен(ут.127.0.0.0)
        std::cout << "ERROR invalid address";
        return 1;
    }
        
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) { // если соединение не установлено
        std::cout << "ERROR connecting";
        return 1;
    }

    while (true) {
        std::cout << ">>> ";
        std::string command;
        char c;
        while (std::cin.get(c)){
            if (c == '\n' && command[command.size() - 1] == '\n'){
                command += c;
                break;
            }
            command += c;
        }
        if (command == "EXIT"){
            break;
        }
        send(sockfd, command.c_str(), command.size(), 0);
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        read(sockfd, buffer, sizeof(buffer));
        std::cout << buffer << std::endl;
    }

    return 0;
}