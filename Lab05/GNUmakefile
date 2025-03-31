# @file		GNUmakefile
#
# Makefile for ECE013 - Lab05
#
# @author	HARE Lab
# @author	jLab
# @version	1.0.0
#
# @date		21 Oct 2024

## Defining variables in Makefiles
#
# Makefiles can easily become bulky and hard to read/edit. This is somewhat counter
# to the purpose of Makefiles as tools that make code compilation, debugging, and 
# cleanup easier. To improve code readability, you can define variables in any
# Makefile with the following syntax:
common=../Common
include_dirs=-I$(common)

all: Lab05

Lab05: Lab05_main.c rpn.o stack.o
	gcc $(include_dirs) -Wall Lab05_main.c $(common)/BOARD.c rpn.o stack.o -o Lab05

stack_test: stack_test.c stack.o 
	gcc $(include_dirs) -Wall stack_test.c $(common)/BOARD.c stack.o -o stack_test

rpn_test: rpn_test.c rpn.o stack.o
	gcc $(include_dirs) -Wall rpn_test.c $(common)/BOARD.c rpn.o stack.o -o rpn_test

stack.o: stack.c
	gcc $(include_dirs) -Wall -c stack.c

rpn.o: rpn.c
	gcc $(include_dirs) -Wall -c rpn.c

