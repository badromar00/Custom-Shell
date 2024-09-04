README
• Our Information:
README file for Experimental Shell “XSH” program
CS 480, Summer 2024
Assignment #2, Experimental Shell “XSH”
Omar Badr (cssc4448) (827991496), Isabelle Bernal (cssc4464) (826779532)

• Identifying Contribution to Program:
- Omar: coded xsh.cpp, xsh.h, and in the README.txt wrote design description, extra features, any known bugs, and lesson learned
- Isabelle: coded dsh.cpp, makefile, and in the README.txt wrote file manifest, compile instructions, and operating instructions
- We technically both contributed to all the files regardless on who primarly coded which file because of troubleshooting and bouncing ideas off each other on how to approach 
a particular part in the code
- everything was done 50/50

• File manifest:

1. 'README.md': This readme file with project information.
2. 'dsh.cpp': main c++ file having main() function for the Experimental Shell "XSH" program.
3. 'xsh.cpp': c++ file the implements core functions of the Experimental Shell "XSH" program.
4. 'xsh.h': header file containing declared program's functions for the Experimental Shell "XSH" program which serves as an interface between 'dsh.cpp' and 
   'xsh.cpp'.
5. 'Makefile': makefile to compile the project.

• Compile instructions:

1. 'cd ~/a2': Navigate into the directory
2. 'make': will compile 'dsh.cpp' and 'xsh.cpp' into object files 'dsh.o' and 'xsh.o',
    and link the object files together to create the executable named 'dsh'. At the end removes object files for proper clean up.
3. 'make clean': cleans up build artifacts if needed.

• Operating instructions:

1. './dsh': after ensuring the program has compiled, this command will run the Experimental Shell 'dsh' and then will display the prompt with my username       'cssc4464%'.                                                                     
2. Command Line options/arguments/required input:
   - ls  (Command: `executablefilename`, Required Input: name of executable file)
   - ls -l  (Command: `executablefilename argument`, Required Input: name of executable file and one argument)
   - ls | sort (Command: `executablefilename1 | executablefilename2`, Required Input: two executable files that are seperated by a pipe '|')
   - ls | sort | grep `executable file name` (ex. xsh.cpp) (Command: `executablefilename1 | executablefilename2 | executablefilename3`, Required Input: multuple executable files that are seperated by a pipe '|')
   - exit (Command: exit, Required Input: none)
3. Error Handling:
   -   if unknown command or filename it will give: 'Error: *invalid command* is not executable or not found.`
4. 'exit': if needed, this command will terminate the program cleanly

• List/description of novel/significant design decisions
- We divided the program into multiple source files (dsh.cpp, xsh.cpp) and a header file (xsh.h). This modular structure helps in organizing the code, making it easier to manage, maintain, and extend.
-  This spliiting of files ensures that the main loop of the shell (dsh.cpp) remains clean and concise, while xsh.cpp handles the core functionalities like command execution and pipeline management. This format enhances code readability and facilitates debugging and testing.
-  Implemented the find_executable function to dynamically search for executables in the system’s PATH. This design decision allows the shell to run any executable found in the user's PATH environment variable, making it versatile and capable of running various commands without hardcoding paths. It also supports both absolute and relative paths, enhancing usability.
-  Utilized fork, execvp, and wait system calls for process creation and synchronization. Using these system calls ensures that each command runs in a separate process, closely mimicking the behavior of traditional shells. It allows concurrent execution and proper resource management, ensuring that the shell can handle multiple processes simultaneously.

• List/description of any extra features/algorithms/functionality you included which were not required
No extra features were implemented.

• List/description of all known deficiencies or bugs
There are no known bugs/deficiencies at the moment.

• Lessons Learned
- We learned how to create processes and inter-process communication using pipes.
- We learned how to validate user input for commands and how to deal with error handling to create a robust program.
- We learnt how to parse user input using std::istringstream to tokenize commands and arguments was an effective way to handle input. This allowed us to break down complex input strings into manageable components.
- We learned how to split input based on the pipe (|) character, and were able to construct pipelines dynamically, supporting an arbitrary number of piped commands.
