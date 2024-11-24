###################################################
#
# file: Makefile
#
# @Author:   Ioannis Chatziantwoiou
# @Version:  24-3-2024
# @email:    csd5193@csd.uoc.gr
#
# Makefile
#
####################################################

all: listtest hashtest

listtest: testsymtab.o symtablelist.o
        gcc testsymtab.o symtablelist.o -o listtest

hashtest: testsymtab.o symtablehash.o
        gcc testsymtab.o symtablehash.o -o hashtest



testsymtab.o : testsymtab.c symtable.h
        gcc -ansi -Wall -pedantic -c testsymtab.o

symtablelist.o : symtablelist.c symtable.h
        gcc -ansi -Wall -pedantic -c symtablelist.c

symtablehash.o: symtablehash.c symtable.h
        gcc -ansi -Wall -pedantic -c symtablehash.c



clean :
        rm -f *.o
        rn -f list hash

