#!/usr/bin/sh

g++ -fdiagnostics-color=always -g ./domain/Elements.cpp ./domain/Graph.cpp ./domain/Iterators.cpp ./ui/UI.cpp ./main_testing.cpp -o ./main_testing
valgrind --leak-check=full ./main_testing
