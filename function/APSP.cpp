#include "APSP.h"

void print_matrix(Matrix& matrix){
    for (auto row : matrix){
        for (auto element : row){
            if (element == inf) {
                std::cout << "inf ";
                continue;
            }

            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

Matrix matrix_multiply(Matrix& a, Matrix& b){
    int n = a.size();

    Matrix c(n,std::vector<int>(n, 0));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return c;
}

Matrix matrix_extend(Matrix& d, Matrix& w){
    int n = d.size();

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            //d[i][j] = inf;
            for (int k = 0; k < n; k++){
                d[i][j] = std::min(d[i][j], d[i][k] + w[k][j]);
            }
            
            if (d[j][j] < 0){
                throw std::out_of_range("Negative cycle detected!");
            }
        }
    }

    return d;
}

Matrix APSP(Matrix& matrix){
    int n = matrix.size();

    Matrix d = matrix;

    for (int i = 1; i < n -1; i++){
        print_matrix(d);
        std::cout << "\n";
        d = matrix_extend(d, matrix);
    }

    return d;
}

Matrix APSP_starting_from(Matrix& matrix, VertexID id){
    int n = matrix.size();

    Matrix d = matrix;
    Matrix c(n,std::vector<int>(n - 1, 0));

    //c[0] = d[id];
    for (int j = 0; j < n; j++){
        c[j][0] = d[id][j];
    }

    for (int i = 1; i < n -1; i++){
        //print_matrix(d);
        //std::cout << "\n";
        d = matrix_extend(d, matrix);
        //c[i] = d[id];
        for (int j = 0; j < n; j++){
            c[j][i] = d[id][j];
        }
    }

    return c;
}