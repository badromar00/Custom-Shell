/*
dsh.cpp
dsh c++ file for Experimental Shell
CS 480, Summer 2024
Assignment #2, Experimental Shell
Omar Badr (cssc4448) (827991496), Isabelle Bernal (cssc4464) (826779532)
*/

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include "xsh.h"

const std::string username = "cssc4464% ";

int main() {
    std::string input; // String to store user input

    while (true) { 
        std::cout << username; // Print username
        if (!std::getline(std::cin, input)) { // Get user input
            break;
        }

        if (input == "exit") { // If command is "exit", then exit
            break; 
        }

        // Split the input into commands or arguments
        std::vector<std::vector<std::string>> commands = parse_input(input);

        if (commands.empty()) { // Skip if input is empty
            continue;
        }

        // Check if the first command is a built-in command
        if (is_builtin(commands[0][0])) {
            execute_builtin(commands[0]); // Execute the built-in command
            continue; // Skip further processing
        }

        // If there is only one command (no pipes)
        if (commands.size() == 1) {
            pid_t pid = fork(); // Create a new process
            if (pid == 0) {
                execute_command(commands[0]); // Execute the command in the child process
            } else if (pid < 0) {
                perror("fork"); // Print error message if fork fails
            } else {
                wait(nullptr); // Parent process waits for the child to complete
            }
        } else {
            // Handle piped commands
            execute_pipeline(commands);
        }
    }

    return 0;
}
