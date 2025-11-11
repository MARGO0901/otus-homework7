#include "context.h"

#include <stdexcept>
#include <cstring>
#include <string>

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    if (argv[1] == nullptr || strlen(argv[1]) == 0) {
        std::cout << "Empty argument" << std::endl;
        return 1;
    }

    int number;
    std::string programName = "bulk";

    try {
        number = std::stoi(argv[1]);
    } catch(const std::invalid_argument& e) {
        std::cout << "Invalid argument" << std::endl;
    } catch(const std::out_of_range& e) {
        std::cout << "Too laught number" << std::endl;
    }

    StateContext sc(std::move(programName), number);
    std::string line;

    while (std::getline(std::cin, line)) {
        sc.ProcessLine(line);
    }

    if(std::cin.eof()) {
        sc.ProcessEnd();
    }
    return 0;
}