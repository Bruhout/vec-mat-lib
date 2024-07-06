#ifndef MAT_H
#define MAT_H

#include <stdio.h>
#include "vec.h"
#include "err.h"

typedef struct mat
{
    double* array;
    int n_rows;
    int n_cols;
}mat;

static inline int matrix_size(mat* matrix) { return matrix->n_rows * matrix->n_cols; }
static inline int index_matrix(int n_cols , int index_row , int index_col) { return (n_cols * index_row) + index_col; }

// MATRIX CREATION FUNCTIONS
la_err laNewMat(int n_rows , int n_cols , mat** out_mat);
la_err laMatFromArray(double* array , int n_rows , int n_cols , mat** out_mat);

// MATRIX ALGEBRA FUNCTIONS
la_err laVecMatMul(vec* in_vec , mat* transform_mat , vec** out_vec);
la_err laMatMul(mat* mat1 , mat* mat2 , mat** out_mat); // matrices are multiplied in the order they are passed

// 3D TRANSFORMATION FUNCTIONS
// These funcs need 3D coords to work
la_err laTranslateMat(mat* matrix , vec* trans_vec , mat** out_mat);
la_err laRotateMat(mat* matrix , double theta , axis ax , mat** out_mat);

// UTILITY FUNCTIONS
la_err laFreeMat(mat** matrix);
la_err laPrintMat(mat* matrix);

//==================================================================================================================
// IN PLACE EDITING FUNCTIONS
// These functions will just write the result vector to the first vector/matrix that is passed

// MATRIX ALGEBRA FUNCTIONS
la_err laVecMatMulInPlace(vec* in_vec , mat* transform_mat);
la_err laMatMulInPlace(mat* mat1 , mat* mat2);

// 3D TRANSFORMATION FUNCTIONS
la_err laTranslateMatInPlace(mat* matrix , vec* trans_vec);
la_err laRotateMatInPlace(mat* matrix , double theta , axis ax);
la_err laRotateXInPlace(mat* matrix , double theta);
la_err laRotateYInPlace(mat* matrix , double theta);
la_err laRotateZInPlace(mat* matrix , double theta);

#endif