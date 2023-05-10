#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <chrono>

using std::vector;
using std::cout;
using std::swap;

void swap_rows(vector<vector<double>>& matrix, size_t row1, size_t row2);

// subtracts row 1, multiplied by factor, from row 2
void subtract_rows(vector<vector<double>>& matrix, size_t row1, size_t row2, double factor);

// makes matrix upper-triangular in O(n^3)
// to be used only for computing the determinant
void gaussian_elimination(vector<vector<double>>& matrix);

// computes the determinant of upper-triangular matrix in O(n)
double compute_determinant(const vector<vector<double>>& matrix);

// for testing the other functions
void print_matrix(const vector<vector<double>>& matrix);

vector<vector<double>> generate_random_matrix(const vector<vector<long long>>& matrix)
{
    size_t n = matrix.size();

    vector<vector<double>> random_matrix(n, vector<double>(n));

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            double sign = (rand() % 2 ? -1 : 1);
            random_matrix[i][j] = sign*sqrt(matrix[i][j]);
        }
    }

    return random_matrix;
}

double compute_permanent(const vector<vector<long long>>& matrix, int t)
{
    double result = 0;

    for (int i = 1; i <= t; ++i)
    {
        vector<vector<double>> random_matrix = generate_random_matrix(matrix);
        gaussian_elimination(random_matrix);
        double det = compute_determinant(random_matrix);
        result += (det*det)/t;
    }

    return result;
}

int main()
{
    srand(time(NULL));

    vector<vector<long long>> matrix1 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 13, 31, 6}, {13, 2, 2, 7}};
    vector<vector<long long>> matrix2 = {{12, 21, 13, 4, 67}, {15, 26, 17, 8, 14}, {9, 13, 31, 6, 12}, {13, 2, 2, 7, 8}, {22, 11, 20, 20, 0}};

    // permanent of matrix1 = 39470
    // permanent of matrix2 = 73166432

    cout << "PERMANENT TEST:\n";
    cout << round(compute_permanent(matrix1, 100)) << '\n';
    cout << round(compute_permanent(matrix2, 100));

    return 0;
}

// helper functions
void swap_rows(vector<vector<double>>& matrix, size_t row1, size_t row2)
{
    size_t n = matrix.size();

    for (size_t i = 0; i < n; ++i)
        swap(matrix[row1][i], matrix[row2][i]);
}

void subtract_rows(vector<vector<double>>& matrix, size_t row1, size_t row2, double factor)
{
    size_t n = matrix.size();

    for (size_t i = 0; i < n; ++i)
        matrix[row2][i] -= factor*matrix[row1][i];
}

void gaussian_elimination(vector<vector<double>>& matrix)
{
    size_t n = matrix.size();

    for (size_t i = 0; i < n - 1; ++i)
    {
        if (matrix[i][i] == 0)
        {
            for (size_t j = i + 1; j < n; ++j)
            {
                if (matrix[j][i] != 0)
                {
                    swap_rows(matrix, i, j);
                    matrix[i][i] *= -1;
                    break;
                }
            }
        }

        // determinant is 0
        // no need to work more
        if (matrix[i][i] == 0)
            return;

        for (size_t j = i + 1; j < n; ++j)
        {
            if (matrix[j][i] != 0)
                subtract_rows(matrix, i, j, matrix[j][i]/matrix[i][i]);
        }
    }
}

double compute_determinant(const vector<vector<double>>& matrix)
{
    size_t n = matrix.size();

    double det = 1;

    for (size_t i = 0; i < n; ++i)
        det *= matrix[i][i];

    return det;
}

void print_matrix(const vector<vector<double>>& matrix)
{
    size_t n = matrix.size();

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            cout << matrix[i][j] << ' ';
        }
        cout << '\n';
    }
}
