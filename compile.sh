#!/usr/bin/sh

g++ -fdiagnostics-color=always -g ./domain/Elements.cpp ./domain/Graph.cpp ./domain/Iterators.cpp ./ui/UI.cpp ./main.cpp -o ./main
valgrind --leak-check=full ./main
