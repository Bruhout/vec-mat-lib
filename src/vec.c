#include "../include/vec.h"
#include "../include/err.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//========================================================================================================
// VECTOR CREATION FUNCTIONS
la_err laNewVec(int n , vec** out_vec)
{
    if (n < 1) { return LA_ERR_ZERO_LENGTH; }

    vec* new_vec = (vec*)malloc(sizeof(vec));
    if (new_vec == NULL) { return LA_ERR_MEMORY_ALLOCATION; }

    new_vec->n = n;
    double* array = (double*)malloc(sizeof(double) * n);
    
    if (array == NULL) { return LA_ERR_MEMORY_ALLOCATION; }

    for (int i=0 ; i<n ; i++) {
        array[i] = 0;
    }

    new_vec->array = array;
    *out_vec = new_vec;

    return LA_SUCCESS;
}

la_err laVecFromArray(double* array, int n , vec** out_vec)
{
    if (n < 1) { return LA_ERR_ZERO_LENGTH; }

    vec* new_vec;
    la_err error_code = laNewVec(n , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }
    
    for (int i=0 ; i<n ; i++) {
        new_vec->array[i] = array[i];
    }

    *out_vec = new_vec;
    return LA_SUCCESS;
}

la_err laVecsFromArray(double* array , int n , int vector_count , vec*** out_vec_arr)
{
    if (vector_count < 1) { return LA_UK_ERROR; }
    if (n < 1) { return LA_ERR_ZERO_LENGTH; }

    vec** output_array = (vec**)malloc(sizeof(vec*) * vector_count);
    if (output_array == NULL) { return LA_ERR_MEMORY_ALLOCATION; }

    for (int i=0 ; i<vector_count ; i++)
    {
        vec* new_vec;
        la_err error_code = laNewVec(n , &new_vec);
        if (error_code != LA_SUCCESS) { return error_code; }

        for (int j=0 ; j<n ; j++) {
            new_vec->array[j] = array[n*i + j];
        }
        output_array[i] = new_vec;
    }

    *out_vec_arr = output_array;

    return LA_SUCCESS;
}

//========================================================================================================




//========================================================================================================
// VECTOR ALGEBRA FUNCTIONS
la_err laVecSum(vec* vec1, vec* vec2 , vec** out_vec)
{
    if (vec1->n != vec2->n) { return LA_ERR_INVALID_DIM; }

    vec* new_vec;
    la_err error_code = laNewVec(vec1->n , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    for (int i=0 ; i<vec1->n ; i++) {
        new_vec->array[i] = vec1->array[i] + vec2->array[i];
    }

    *out_vec = new_vec;

    return LA_SUCCESS;
}

la_err laVecDiff(vec* vec1 , vec* vec2 , vec** out_vec)
{
    if (vec1->n != vec2->n) { return LA_ERR_INVALID_DIM; }

    vec* new_vec;
    la_err error_code = laNewVec(vec1->n , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    for (int i=0 ; i<vec1->n ; i++) {
        new_vec->array[i] = vec1->array[i] - vec2->array[i];
    }

    *out_vec = new_vec;

    return LA_SUCCESS;
}

la_err laVecScale(vec* vec1, double factor , vec** out_vec)
{
    vec* new_vec;
    la_err error_code = laNewVec(vec1->n , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    for (int i=0 ; i<vec1->n ; i++) {
        new_vec->array[i] = vec1->array[i] * factor;
    }

    *out_vec = new_vec;

    return LA_SUCCESS;
}

la_err laMag(vec* in_vec , double* out_ptr)
{
    double sum = 0;
    for (int i=0 ; i<in_vec->n ; i++) {
        sum += in_vec->array[i] * in_vec->array[i];
    }

    *out_ptr = pow(sum , 0.5);

    return LA_SUCCESS;
}

la_err laMagSq(vec* in_vec , double* out_ptr)
{
    double sum = 0;
    for (int i=0 ; i<in_vec->n ; i++) {
        sum += in_vec->array[i] * in_vec->array[i];
    }

    *out_ptr = sum;

    return LA_SUCCESS;
}

la_err laDist(vec* vec1 , vec* vec2 , double* out_ptr)
{
    if (vec1->n != vec2->n) { return LA_ERR_INVALID_DIM; }

    double sum = 0;
    for (int i=0 ; i<vec1->n ; i++) {
        sum += (vec2->array[i] - vec1->array[i]) * (vec2->array[i] - vec1->array[i]);
    }

    *out_ptr = sum; 

    return LA_SUCCESS;
}

la_err laCrossProd3D(vec* vec1, vec* vec2 , vec** out_vec)
{
    if (vec1->n != vec2->n) { return LA_ERR_INVALID_DIM; }
    if (vec1->n != 3 && vec2->n != 4) { return LA_ERR_NOT_3D_OBJ; }

    vec* new_vec;
    la_err error_code = laNewVec(vec1->n , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    new_vec->array[0] = vec1->array[1] * vec2->array[2] - vec1->array[2] * vec2->array[1];
    new_vec->array[1] = vec1->array[2] * vec2->array[0] - vec1->array[0] * vec2->array[2];
    new_vec->array[2] = vec1->array[0] * vec2->array[1] - vec1->array[1] * vec2->array[0];

    *out_vec = new_vec;

    return LA_SUCCESS;
}

la_err laDotProd(vec* vec1, vec* vec2 , double* out_ptr)
{
    if (vec1->n != vec2->n) { return LA_ERR_INVALID_DIM; }

    double sum = 0;
    for (int i=0 ; i<vec1->n ; i++) {
        sum += vec1->array[i] * vec2->array[i];
    }

    *out_ptr = sum;

    return LA_SUCCESS;
}

la_err laUnitVec(vec* in_vec , vec** out_vec)
{
    vec* new_vec;
    la_err error_code = laNewVec(in_vec->n , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    double mag;
    error_code = laMag(in_vec , &mag);
    if (error_code != LA_SUCCESS) {return error_code; }

    for (int i=0 ; i<in_vec->n ; i++) {
        new_vec->array[i] = in_vec->array[i] / mag; 
    }

    *out_vec = new_vec;

    return LA_SUCCESS;
}

la_err laProjectOnto(vec* proj_vec , vec* onto_vec , vec** out_vec)
{
    if (proj_vec->n != onto_vec->n) { return LA_ERR_INVALID_DIM; }

    double onto_vec_mag;
    la_err error_code = laMag(onto_vec , &onto_vec_mag);
    if (error_code != LA_SUCCESS) { return error_code; }

    double dot;
    error_code = laDotProd(proj_vec , onto_vec , &dot);
    if (error_code != LA_SUCCESS) { return error_code; }

    double mag_projected_vec = dot / onto_vec_mag;

    vec* onto_unit;
    error_code = laUnitVec(onto_vec , &onto_unit);
    if (error_code != LA_SUCCESS) { return error_code; }

    vec* projected_vec;
    error_code = laVecScale(onto_unit , mag_projected_vec , &projected_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    *out_vec = projected_vec;

    laFreeVec(&onto_unit);

    return LA_SUCCESS;
}

//========================================================================================================




//========================================================================================================
// UTILITY FUNCTIONS
la_err laFreeVec(vec** vector)
{
    if (*vector == NULL) { return LA_ERR_INVALID_PTR; }
    if ((*vector)->array == NULL) { return LA_ERR_INVALID_PTR; }

    free((*vector)->array);
    free(*vector);

    *vector = NULL;

    return LA_SUCCESS;
}

la_err laPrintVec(vec* in_vec)
{
    printf("{");
    for (int i=0 ; i<in_vec->n-1 ; i++) {
        printf("%f, " , in_vec->array[i]);
    }
    printf("%f}\n" , in_vec->array[in_vec->n - 1]);

    return LA_SUCCESS;
}
//========================================================================================================




//========================================================================================================
// RASTER FUNCTIONS
// take pixel coordinates to normal screen coords
la_err laNormalize(vec* in_vec, int width, int height , vec** out_vec)
{
    if (in_vec->n < 2) { return LA_ERR_INVALID_DIM; }

    vec* new_vec;
    la_err error_code = laNewVec(in_vec->n , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    new_vec->array[0] = in_vec->array[0] / (double)width;
    new_vec->array[1] = in_vec->array[1] / (double)height;

    *out_vec = new_vec;

    return LA_SUCCESS;
}

la_err laNormalizeRev(vec* in_vec , int width , int height , vec** out_vec)
{
    if (in_vec->n < 2) { return LA_ERR_INVALID_DIM; }

    vec* new_vec;
    la_err error_code = laNewVec(in_vec->n , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    new_vec->array[0] = in_vec->array[0] * width;
    new_vec->array[1] = in_vec->array[1] * height;

    *out_vec = new_vec;

    return LA_SUCCESS;
}

la_err laImageToAxes(vec* in_vec , vec** out_vec)
{
    if (in_vec->n < 2) { return LA_ERR_INVALID_DIM; }
    
    vec* new_vec;
    la_err error_code = laNewVec(in_vec->n , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    for (int i=0 ; i<in_vec->n ; i++) {
        new_vec->array[i] = in_vec->array[i];
    }

    new_vec->array[0] = in_vec->array[0] * 2;
    new_vec->array[1] = in_vec->array[1] * 2;

    new_vec->array[0] -= 1;
    new_vec->array[1] -= 1;

    *out_vec = new_vec;

    return LA_SUCCESS;
}

la_err laAxesToImage(vec* in_vec , vec** out_vec)
{
    if (in_vec->n < 2) { return LA_ERR_INVALID_DIM; }
    
    vec* new_vec;
    la_err error_code = laNewVec(in_vec->n , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    for (int i=0 ; i<in_vec->n ; i++) {
        new_vec->array[i] = in_vec->array[i];
    }

    new_vec->array[0] = in_vec->array[0] * 0.5;
    new_vec->array[1] = in_vec->array[1] * 0.5;

    new_vec->array[0] += 0.5;
    new_vec->array[1] += 0.5;

    *out_vec = new_vec;

    return LA_SUCCESS;
}
//========================================================================================================













//========================================================================================================
// IN PLACE EDITING FUNCTIONS

// VECTOR ALBEGRA FUNCTIONS
la_err laVecSumInPlace(vec* vec1, vec* vec2)
{
    if (vec1->n != vec2->n) { return LA_ERR_INVALID_DIM; }

    for (int i=0 ; i<vec1->n ; i++) {
        vec1->array[i] += vec2->array[i];
    }

    return LA_SUCCESS;
}

la_err laVecDiffInPlace(vec* vec1 , vec* vec2)
{
    if (vec1->n != vec2->n) { return LA_ERR_INVALID_DIM; }

    for (int i=0 ; i<vec1->n ; i++) {
        vec1->array[i] -= vec2->array[i];
    }

    return LA_SUCCESS;
}

la_err laVecScaleInPlace(vec* vec1, double factor)
{
    for (int i=0 ; i<vec1->n ; i++) {
        vec1->array[i] *= factor;
    }

    return LA_SUCCESS;
}

la_err laCrossProd3DInPlace(vec* vec1, vec* vec2)
{
    if (vec1->n != vec2->n) { return LA_UK_ERROR; }
    if (vec1->n != 3 && vec2->n != 4) { return LA_ERR_NOT_3D_OBJ; }

    double c_prod_arr[vec1->n];

    c_prod_arr[0] = vec1->array[1] * vec2->array[2] - vec1->array[2] * vec2->array[1];
    c_prod_arr[1] = vec1->array[2] * vec2->array[0] - vec1->array[0] * vec2->array[2];
    c_prod_arr[2] = vec1->array[0] * vec2->array[1] - vec1->array[1] * vec2->array[0];

    for (int i=0 ; i<vec1->n ; i++) {
        vec1->array[i] = c_prod_arr[i];
    }

    return LA_SUCCESS;
}

la_err laUnitVecInPlace(vec* in_vec)
{
    double mag;
    la_err error_code = laMag(in_vec , &mag);
    if (error_code != LA_SUCCESS) {return error_code; }

    for (int i=0 ; i<in_vec->n ; i++) {
        in_vec->array[i] /= mag; 
    }

    return LA_SUCCESS;
}

la_err laProjectOntoInPlace(vec* proj_vec , vec* onto_vec)
{
    if (proj_vec->n != onto_vec->n) { return LA_ERR_INVALID_DIM; }

    double onto_vec_mag;
    la_err error_code = laMag(onto_vec , &onto_vec_mag);
    if (error_code != LA_SUCCESS) { return error_code; }

    double dot;
    error_code = laDotProd(proj_vec , onto_vec , &dot);
    if (error_code != LA_SUCCESS) { return error_code; }

    double mag_projected_vec = dot / onto_vec_mag;

    proj_vec = onto_vec;
    error_code = laUnitVecInPlace(proj_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    error_code = laVecScaleInPlace(proj_vec , mag_projected_vec);
    if (error_code != LA_SUCCESS) { return error_code; }

    return LA_SUCCESS;
}
//========================================================================================================




//========================================================================================================
// RASTER FUNCTIONS / SCREEN FUNCTIONS
la_err laNormalizeInPlace(vec* in_vec, int width, int height)
{
    if (in_vec->n < 2) { return LA_ERR_INVALID_DIM; }

    in_vec->array[0] /= (double)width;
    in_vec->array[1] /= (double)height;

    return LA_SUCCESS;
}

la_err laNormalizeRevInPlace(vec* in_vec , int width , int height)
{
    if (in_vec->n < 2) { return LA_ERR_INVALID_DIM; }

    in_vec->array[0] *= width;
    in_vec->array[1] *= height;

    return LA_SUCCESS;
}

la_err laImageToAxesInPlace(vec* in_vec)
{
    if (in_vec->n < 2) { return LA_ERR_INVALID_DIM; }
    
    in_vec->array[0] *= 2;
    in_vec->array[1] *= 2;

    in_vec->array[0] -= 1;
    in_vec->array[1] -= 1;

    return LA_SUCCESS;
}

la_err laAxesToImageInPlace(vec* in_vec)
{
    if (in_vec->n < 2) { return LA_ERR_INVALID_DIM; }

    in_vec->array[0] *= 0.5;
    in_vec->array[1] *= 0.5;

    in_vec->array[0] += 0.5;
    in_vec->array[1] += 0.5;

    return LA_SUCCESS;
}
//========================================================================================================