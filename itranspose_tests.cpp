//
//  In-place transpose of rectangular matrices (For inclusion in Armadillo C++ linear algebra library)
//
//  Inspired by : Gustavson, F. G., & Swirszcz, T. (2007). In-place transposition of rectangular matrices.
//                In Applied Parallel Computing. State of the Art in Scientific Computing (pp. 560-569).
//                Springer Berlin Heidelberg.
//
//  Created by : Alexandre Drouin
//  Date : 2013-09-30
//
//  Make with : g++ itranspose_tests.cpp -o tests -lboost_unit_test_framework-mt

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "C++ Unit Tests for in-place transposition of rectangular matrices"

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <armadillo>


using namespace arma;
using namespace std;

template<class TYPE>
void itranspose(Mat<TYPE>& A)
{
    const unsigned int m = A.n_rows;
    const unsigned int n = A.n_cols;
    
    if (m == n) {
        for (int i = 0; i < m - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                TYPE tmp = A(j, i);
                A(j, i) = A(i, j);
                A(i, j) = tmp;
            }
        }
    }
    else
    {
        A.set_size(A.n_cols, A.n_rows);
        
        vector<bool> visited(A.n_cols * A.n_rows);
        
        for (int row = 0; row < n; row++) {
            for (unsigned int col = 0; col < m; col++) {
                
                unsigned int pos = col * n + row;
                
                if (!visited[pos]) {
                    unsigned int curr_pos = pos;
                    
                    TYPE val = A(row, col);
                    
                    while (!visited[curr_pos]) {
                        visited[curr_pos] = true;
                        
                        unsigned int A_j = curr_pos / m;
                        unsigned int A_i = curr_pos - m * A_j;
                        
                        TYPE tmp = A(A_j, A_i);
                        A(A_j, A_i) = val;
                        val = tmp;
                        
                        curr_pos = A_i*n + A_j;
                    }
                }
            }
        }
    }
}

BOOST_AUTO_TEST_CASE( transpose_column_matrix )
{
    const unsigned int m = 1000;
    const unsigned int n = 300;
    
    fmat A(m, n);
    A.randu();
    
    fmat B = A.t();
    
    itranspose(A);
    
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            BOOST_CHECK_CLOSE(B(i,j), A(i,j), 0.0001);
        }
    }
}

BOOST_AUTO_TEST_CASE( transpose_row_matrix )
{
    const unsigned int m = 300;
    const unsigned int n = 1000;
    
    fmat A(m, n);
    A.randu();
    
    fmat B = A.t();
    
    itranspose(A);
    
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            BOOST_CHECK_CLOSE(B(i,j), A(i,j), 0.0001);
        }
    }
}

BOOST_AUTO_TEST_CASE( transpose_square_matrix )
{
    const unsigned int m = 333;
    const unsigned int n = 333;
    
    fmat A(m, n);
    A.randu();
    
    fmat B = A.t();
    
    itranspose(A);
    
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            BOOST_CHECK_CLOSE(B(i,j), A(i,j), 0.0001);
        }
    }
}
