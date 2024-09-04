/*
xsh.cpp
xsh c++ file that conatains functionality for Experimental Shell
CS 480, Summer 2024
Assignment #2, Experimental Shell
Omar Badr (cssc4448) (827991496), Isabelle Bernal (cssc4464) (826779532)
*/

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include "xsh.h"

// Function to check if a file is executable
bool is_executable(const std::string& file) {
    struct stat sb;
    // Check if file exists and is executable by the user
    return (stat(file.c_str(), &sb) == 0 && sb.st_mode & S_IXUSR);
}

// Function to check if a command is a built-in command
bool is_builtin(const std::string& cmd) {
    // Currently, only 'cd' is considered a built-in command
    return (cmd == "cd");
}

// Function to execute built-in commands
void execute_builtin(const std::vector<std::string>& command) {
    if (command[0] == "cd") {
        // Check if argument is provided for 'cd'
        if (command.size() < 2) {
            std::cerr << "cd: missing argument" << std::endl;
        } else {
            // Change directory and handle errors
            if (chdir(command[1].c_str()) != 0) {
                perror("cd");
            }
        }
    }
}

// Function to find an executable in the system's PATH
std::string find_executable(const std::string& command) {
    // If command contains a slash, assume it's a path and return it
    if (command.find('/') != std::string::npos) {
        return command;
    }

    // Get the PATH environment variable
    const char* path = getenv("PATH");
    if (!path) {
        return "";
    }

    // Split the PATH into individual directories
    std::istringstream path_stream(path);
    std::string path_segment;
    while (std::getline(path_stream, path_segment, ':')) {
        // Construct the full path to the executable
        std::string full_path = path_segment + "/" + command;
        // Check if the constructed path is executable
        if (is_executable(full_path)) {
            return full_path;
        }
    }

    // Return an empty string if the executable is not found
    return "";
}

// Function to parse the input line into commands and arguments
std::vector<std::vector<std::string>> parse_input(const std::string& input) {
    std::vector<std::vector<std::string>> commands;
    std::istringstream stream(input);
    std::string segment;
    std::vector<std::string> command;

    // Split the input by '|' to separate commands in a pipeline
    while (std::getline(stream, segment, '|')) {
        std::istringstream cmdstream(segment);
        std::string token;
        // Split each command segment into individual tokens
        while (cmdstream >> token) {
            command.push_back(token);
        }
        // Add the parsed command to the list of commands
        commands.push_back(command);
        command.clear();
    }
    return commands;
}

// Function to execute a single command
void execute_command(const std::vector<std::string>& command) {
    // Find the executable for the command
    std::string executable = find_executable(command[0]);
    if (executable.empty()) {
        std::cerr << "Error: " << command[0] << " is not executable or not found." << std::endl;
        exit(EXIT_FAILURE); // Exit child process with failure
    }

    // Prepare arguments for execvp
    std::vector<char*> args;
    args.push_back(const_cast<char*>(executable.c_str()));
    for (size_t i = 1; i < command.size(); ++i) {
        args.push_back(const_cast<char*>(command[i].c_str()));
    }
    args.push_back(nullptr);

    // Replace current process with the executable
    execvp(args[0], args.data());

    // If execvp fails, print error and exit
    perror("execvp");
    exit(EXIT_FAILURE);
}

// Function to handle the piping mechanism
void execute_pipeline(const std::vector<std::vector<std::string>>& commands) {
    int num_commands = commands.size();
    int pipe_fds[2 * (num_commands - 1)];
    pid_t pid;

    // Create all necessary pipes
    for (int i = 0; i < num_commands - 1; ++i) {
        if (pipe(pipe_fds + i * 2) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Fork processes for each command in the pipeline
    for (int i = 0; i < num_commands; ++i) {
        pid = fork();
        if (pid == 0) {
            // Child process
            // Redirect input if not the first command
            if (i > 0) {
                dup2(pipe_fds[(i - 1) * 2], 0);
            }
            // Redirect output if not the last command
            if (i < num_commands - 1) {
                dup2(pipe_fds[i * 2 + 1], 1);
            }
            // Close all pipe file descriptors
            for (int j = 0; j < 2 * (num_commands - 1); ++j) {
                close(pipe_fds[j]);
            }
            // Execute the command
            execute_command(commands[i]);
        } else if (pid < 0) {
            // Fork failed
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process
    // Close all pipe file descriptors
    for (int i = 0; i < 2 * (num_commands - 1); ++i) {
        close(pipe_fds[i]);
    }

    // Wait for all child processes to finish
    for (int i = 0; i < num_commands; ++i) {
        wait(nullptr);
    }
}
