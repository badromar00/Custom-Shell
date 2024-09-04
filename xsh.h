/*
xsh.h
xsh header file for Experimental Shell
CS 480, Summer 2024
Assignment #2, Experimental Shell
Omar Badr (cssc4448) (827991496), Isabelle Bernal (cssc4464) (826779532)
*/

#ifndef XSH_H
#define XSH_H

#include <string>
#include <vector>

//function makes sure the the file is executable
bool is_executable(const std::string& file);

//function checks if command is built in
bool is_builtin(const std::string& cmd);

//function executes the built in command
void execute_builtin(const std::vector<std::string>& command);

//function finds path of command
std::string find_executable(const std::string& command);

//function gathers commands and arguments that are parsed in user input
std::vector<std::vector<std::string> > parse_input(const std::string& input);

//function executes single command
void execute_command(const std::vector<std::string>& command);

//function executes pipeline commands
void execute_pipeline(const std::vector<std::vector<std::string> >& commands);

#endif
