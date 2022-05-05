#pragma once

#include "../domain/Graph.h"

#include <vector>
#include <iostream>



void print_matrix(Matrix& matrix);

Matrix matrix_multiply(Matrix& a, Matrix& b);

Matrix APSP(Matrix& matrix);

Matrix APSP_starting_from(Matrix& matrix, VertexID id);