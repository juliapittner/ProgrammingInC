
#Julia Pittner 

#Makefile for lab 1-4.  You need to add you name to this file in the comments
# You will need to add a entry to create your zip file

#change the last dependency for each new lab
all:  tags headers lab2

#this entry has to change for lab 2 - 4
# NEVER compile .c files with this rule - it lacks needed compile time flags
# There is an entry below that turns .c files into .o files


lab4: lab4.o output.o motion.o code.o memory.o actions.o functions.o linkedlist.o reliable.o libinvaders.a
	gcc -g -o $@ $^ -L. -linvaders -lncurses

lab4u: lab4.o output.o motion.o code.o memory.o actions.o functions.o linkedlist.o unreliable.o
	gcc -g -o $@ $^ -L. -linvaders -lncurses

#Prototype 1 - grade this.  Opens 2fast.sa file.
proto1: open_file.c
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -o $@ $^


#Prototype 2 - grade this. Opens a file using command line arg.
proto2: open_close_args.c
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -o $@ $^


#Prototype 3 - grade this. Inserts a node into a linked list.
proto3: insert_test.c
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -o $@ -lm $^ 

#Prototype 4 - grade this. Allocates memory using altmem.h.
proto4: allocate_test.o memory.o reliable.o
	gcc -g -o $@ $^

#this is where you create an entry to build yuour zip file
#it will also update with new labs
lab4.zip:	makefile *.c *.h *.a README_LAB4
	zip $@ $^

#this entry stays for C code labs
tags: *.c
	ctags -R .

# this entry stays for C code labs
headers: *.c tags
	headers.sh

# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@




	

