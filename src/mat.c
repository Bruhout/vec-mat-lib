#include "../include/vec.h"
#include "../include/mat.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//===========================================================================================================
// MATRIX CREATION FUNCTIONS
la_err laNewMat(int n_rows , int n_cols , mat** out_mat)
{
    if (n_cols < 1 || n_rows < 1) { return LA_ERR_ZERO_LENGTH; }

    mat* new_mat = (mat*)malloc(sizeof(mat));
    if (new_mat == NULL) { return LA_ERR_MEMORY_ALLOCATION; }

    double* array = (double*)malloc(sizeof(double) * n_cols * n_rows);
    if (array == NULL) { return LA_ERR_MEMORY_ALLOCATION; }

    for (int i=0 ; i<n_rows*n_cols ; i++) {
        array[i] = 0;
    }

    new_mat->n_rows = n_rows;
    new_mat->n_cols = n_cols;
    new_mat->array = array;

    *out_mat = new_mat;
    return LA_SUCCESS;
}

la_err laMatFromArray(double* array , int n_rows , int n_cols , mat** out_mat)
{
    if (n_rows < 0 || n_cols < 0) { return LA_ERR_ZERO_LENGTH; }

    mat* new_mat;
    la_err new_mat_err = laNewMat(n_rows , n_cols , &new_mat);
    if (new_mat == NULL) { return new_mat_err; }

    for (int i=0 ; i<n_rows * n_cols ; i++) {
        new_mat->array[i] = array[i];
    }

    *out_mat = new_mat;
    return LA_SUCCESS;
}
//===========================================================================================================




//===========================================================================================================
// MATRIX ALGEBRA FUNCTIONS
la_err laVecMatMul(vec* in_vec , mat* transform_mat , vec** out_vec)
{
    if (in_vec->n != transform_mat->n_rows) { return LA_ERR_INVALID_DIM; }

    vec* new_vec;
    la_err new_vec_err = laNewVec(transform_mat->n_cols , &new_vec);
    if (new_vec == NULL) { return new_vec_err; }

    for (int i=0 ; i<transform_mat->n_cols ; i++)
    {
        double sum = 0;
        for (int j=0 ; j<transform_mat->n_rows ; j++)
        {
            sum += in_vec->array[j] * transform_mat->array[transform_mat->n_cols*j + i];
        }
        new_vec->array[i] = sum;
    }

    *out_vec = new_vec;

    return LA_SUCCESS;
}

la_err laMatMul(mat* mat1 , mat* mat2 , mat** out_mat)
{
    if (mat1->n_cols != mat2->n_rows) { return LA_ERR_INVALID_DIM; }

    mat* new_mat;
    la_err new_mat_err = laNewMat(mat1->n_rows , mat2->n_cols , &new_mat);
    if (new_mat == NULL) { return new_mat_err; }

    for (int i=0 ; i<mat1->n_rows ; i++)
    {
        for (int j=0 ; j<mat2->n_cols ; j++)
        {
            double sum = 0;
            for (int p=0 ; p<mat2->n_cols ; p++)
            {
                sum += mat1->array[i*mat1->n_cols + p] * mat2->array[p*mat2->n_cols + j];
            }
            new_mat->array[i*new_mat->n_cols + j] = sum;
        }
    }

    *out_mat = new_mat;

    return LA_SUCCESS; 
}

//===========================================================================================================





//===========================================================================================================
// 3D TRANSFORMATION FUNCTIONS
// These funcs need 3D coords to work
la_err laTranslateMat(mat* matrix , vec* trans_vec , mat** out_mat)
{
    if (matrix->n_cols != 4 || matrix->n_rows != 4) { return LA_ERR_NOT_3D_OBJ; }
    if (trans_vec->n != 4 && trans_vec->n != 3) { return LA_ERR_NOT_3D_OBJ; }

    mat* new_mat;
    la_err error_code = laNewMat(4 , 4 , &new_mat);
    if (error_code != LA_SUCCESS) { return error_code; }

    new_mat->array[12 + 0] += trans_vec->array[0];
    new_mat->array[12 + 1] += trans_vec->array[1];
    new_mat->array[12 + 2] += trans_vec->array[2];

    *out_mat = new_mat;

    return LA_SUCCESS;
}

la_err laRotateMat(mat* matrix , double theta , axis ax , mat** out_mat)
{
    if (matrix->n_rows != matrix->n_cols) { return LA_ERR_INVALID_DIM; }
    if (matrix->n_rows < 3 || matrix->n_rows > 4) {return LA_ERR_NOT_3D_OBJ; }
    if (ax < LA_X_AXIS || ax >= LA_X_AXIS + NUM_AXES) { return LA_ERR_INVALID_AXIS; }
    
    mat* new_mat;
    la_err error_code = laNewMat(matrix->n_rows , matrix->n_cols , &new_mat);
    if (error_code != LA_SUCCESS) { return error_code; }

    if (ax == LA_X_AXIS) {
        error_code = laRotateXInPlace(new_mat , theta);
        return error_code;
    } else if (ax == LA_Y_AXIS) {
        error_code = laRotateYInPlace(new_mat , theta);
        return error_code;
    } else if (ax == LA_Z_AXIS) {
        error_code = laRotateZInPlace(new_mat , theta);
        return error_code;
    }

    *out_mat = new_mat;

    return LA_SUCCESS;
}
//===========================================================================================================




//===========================================================================================================
// UTILITY FUNCTIONS
la_err laFreeMat(mat** matrix)
{
    if (*matrix == NULL) { return LA_ERR_INVALID_PTR; }
    if ((*matrix)->array == NULL) { return LA_ERR_INVALID_PTR; }

    free((*matrix)->array);
    free(*matrix);

    *matrix = NULL;
    
    return LA_SUCCESS;
}

la_err laPrintMat(mat* matrix)
{
    double current_row_array[matrix->n_cols];

    printf("{\n");
    for(int i=0 ; i<matrix->n_rows ; i++)
    {
        for(int j=0 ; j<matrix->n_cols ; j++)
        {
            current_row_array[j] = matrix->array[i*matrix->n_cols + j];
        }
        vec* current_row_vec;
        la_err current_row_vec_err = laVecFromArray(current_row_array , matrix->n_cols , &current_row_vec);
        if (current_row_vec_err != LA_SUCCESS) {return current_row_vec_err; }
        printf("    ");
        laPrintVec(current_row_vec);
        laFreeVec(&current_row_vec);
    }
    printf("}\n");

    return LA_SUCCESS;
}
//========================================================================================================













//========================================================================================================
// IN PLACE EDITING FUNCTIONS

// MATRIX ALGEBRA FUNCTIONS
la_err laVecMatMulInPlace(vec* in_vec , mat* transform_mat)
{
    if (in_vec->n != transform_mat->n_rows) { return LA_ERR_INVALID_DIM; }

    double matmul_array[transform_mat->n_cols];

    for (int i=0 ; i<transform_mat->n_cols ; i++)
    {
        double sum = 0;
        for (int j=0 ; j<transform_mat->n_rows ; j++)
        {
            sum += in_vec->array[j] * transform_mat->array[transform_mat->n_cols*j + i];
        }
        matmul_array[i] = sum;
    }

    for (int i=0 ; i<in_vec->n ; i++) {
        in_vec->array[i] = matmul_array[i];
    }
    in_vec->n = transform_mat->n_cols;

    return LA_SUCCESS;
}

la_err laMatMulInPlace(mat* mat1 , mat* mat2)
{
    if (mat1->n_cols != mat2->n_rows) { return LA_ERR_INVALID_DIM; }

    double matmul_array[mat1->n_rows * mat2->n_cols];

    for (int i=0 ; i<mat1->n_rows ; i++)
    {
        for (int j=0 ; j<mat2->n_cols ; j++)
        {
            double sum = 0;
            for (int p=0 ; p<mat2->n_cols ; p++)
            {
                sum += mat1->array[i*mat1->n_cols + p] * mat2->array[p*mat2->n_cols + j];
            }
            matmul_array[i*mat2->n_cols + j] = sum;
        }
    }

    for (int i=0 ; i<mat1->n_rows * mat2->n_cols ; i++) {
        mat1->array[i] = matmul_array[i];
    }
    mat1->n_cols = mat2->n_cols; 

    return LA_SUCCESS; 
}
//========================================================================================================




//========================================================================================================
// 3D TRANSFORMATION FUNCTIONS
la_err laTranslateMatInPlace(mat* matrix , vec* trans_vec)
{
    if (matrix->n_cols != 4 || matrix->n_rows != 4) { return LA_ERR_NOT_3D_OBJ; }
    if (trans_vec->n != 4 && trans_vec->n != 3) { return LA_ERR_NOT_3D_OBJ; }

    matrix->array[3*matrix->n_cols + 0] += trans_vec->array[0];
    matrix->array[3*matrix->n_cols + 1] += trans_vec->array[1];
    matrix->array[3*matrix->n_cols + 2] += trans_vec->array[2];

    return LA_SUCCESS;
}

la_err laRotateMatInPlace(mat* matrix , double theta , axis ax)
{
    if (matrix->n_rows != matrix->n_cols) { return LA_ERR_INVALID_DIM; }
    if (matrix->n_rows < 3 || matrix->n_rows > 4) {return LA_ERR_NOT_3D_OBJ; }
    if (ax < LA_X_AXIS || ax >= LA_X_AXIS + NUM_AXES) { return LA_ERR_INVALID_AXIS; }
    
    la_err error_code;
    if (ax == LA_X_AXIS) {
        error_code = laRotateXInPlace(matrix , theta);
        return error_code;
    } else if (ax == LA_Y_AXIS) {
        error_code = laRotateYInPlace(matrix , theta);
        return error_code;
    } else if (ax == LA_Z_AXIS) {
        error_code = laRotateZInPlace(matrix , theta);
        return error_code;
    }

    return LA_SUCCESS;
}

la_err laRotateXInPlace(mat* matrix , double theta)
{
    matrix->array[matrix->n_cols + 1] = cos(theta);
    matrix->array[matrix->n_cols + 2] = -sin(theta);
    matrix->array[(matrix->n_cols)*2 + 1] = sin(theta);
    matrix->array[(matrix->n_cols)*2 + 2] = cos(theta);

    return LA_SUCCESS;
}

la_err laRotateYInPlace(mat* matrix , double theta)
{
    matrix->array[0] = cos(theta);
    matrix->array[2] = sin(theta);
    matrix->array[(matrix->n_cols)*2 + 0] = -sin(theta);
    matrix->array[(matrix->n_cols)*2 + 2] = cos(theta);

    return LA_SUCCESS;
}

la_err laRotateZInPlace(mat* matrix , double theta)
{
    matrix->array[0] = cos(theta);
    matrix->array[1] = -sin(theta);
    matrix->array[matrix->n_cols + 0] = sin(theta);
    matrix->array[matrix->n_cols + 1] = cos(theta);

    return LA_SUCCESS;
}
//========================================================================================================