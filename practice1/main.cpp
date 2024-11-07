#include "parser.hpp"
#include "insert.hpp"
#include "delete.hpp"
#include "select.hpp"

int main() {
    TableJson tableJS;
    parsing(tableJS);

    string command;
    while (true) {
        cout << ">>> ";
        getline(cin, command);
        if (command == "") {
            continue;
        }
        if (command == "EXIT") {
            return 0;
        }
        else if (command.find("INSERT") == 0) {
            insert(command, tableJS);
        }
        else if (command.find("DELETE") == 0) {
            del(command, tableJS);
        }
        else if (command.find("SELECT") == 0) {
            select(command, tableJS);
        }
        else {
            cerr << "Incorrect command.\n";
        }
    }
    return 0;
}