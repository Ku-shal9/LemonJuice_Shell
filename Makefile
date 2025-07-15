#defining compiler
CC = gcc #CC is a variable that stores the name of the compiler

#compiler flags
CCFLAGS = -Wall -Wextra 
# -Wall -> enables warning messages
# -Wextra -> enables other warnings (makes catching bugs easier)

#executable
TARGET = wonder_shell #final executable file

#Sources
SRCS = main.c input.c loop.c executor.c #list of files containing code

#object files
OBJS = $(SRCS:.c=.o) #pattern substution rule
# main.c -> main.o, input.c -> input.o and so on...

#default rule
all: $(TARGET) # TARGET -> wonder_shell

#Linking
$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^
#links all object file to the final executable
# $@ refers to to the TARGET -> wonder_shell
# $^ refers to the dependencies  (all object files, main.o input.o executor.o loop.o)

#compiling 
%.o: %.c
	$(CC) $(CCFLAG) -c $< -o $@
# %.o: %.c is called a pattern rule (wildcard rule)
# $< is the source file name (.c file)
# $@ is the output file name (.o file)

#cleaning
clean: 
	rm -f $(OBJS) $(TARGET)
