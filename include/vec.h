#ifndef VEC_H
#define VEC_H

#include <stdio.h>
#include "err.h"

#define NUM_AXES 3
typedef enum {
    LA_X_AXIS = 10,
    LA_Y_AXIS = 11,
    LA_Z_AXIS = 12
}axis;

#define HOMOG_COORDS_FALSE 3
#define HOMOG_COORDS_TRUE 4

typedef struct vec
{
    double* array;
    int n; // dimension of the vector
} vec;


// VECTOR CREATION FUNCTIONS
la_err laNewVec(int n , vec** out_vec);
la_err laVecFromArray(double* array, int n , vec** out_vec);
la_err laVecsFromArray(double* array , int n , int vector_count , vec*** out_vec_arr);

// VECTOR ALBEGRA FUNCTIONS
la_err laVecSum(vec* vec1, vec* vec2 , vec** out_vec);
la_err laVecDiff(vec* vec1 , vec* vec2 , vec** out_vec);
la_err laVecScale(vec* vec1, double factor , vec** out_vec);
la_err laMag(vec* in_vec , double* out_ptr);
la_err laMagSq(vec* in_vec , double* out_ptr);
la_err laDist(vec* vec1 , vec* vec2 , double* out_ptr);
la_err laCrossProd3D(vec* vec1, vec* vec2 , vec** out_vec);
la_err laDotProd(vec* vec1, vec* vec2 , double* out_ptr);
la_err laUnitVec(vec* in_vec , vec** out_vec);
la_err laProjectOnto(vec* proj_vec , vec* onto_vec , vec** out_vec);

// UTILITY FUNCTIONS
la_err laFreeVec(vec** vector);
la_err laPrintVec(vec* in_vec);

// RASTER FUNCTIONS / SCREEN FUNCTIONS
la_err laNormalize(vec* in_vec, int width, int height , vec** out_vec);
la_err laNormalizeRev(vec* in_vec , int width , int height , vec** out_vec);
la_err laImageToAxes(vec* in_vec , vec** out_vec);
la_err laAxesToImage(vec* in_vec , vec** out_vec);

//==================================================================================================================
// IN PLACE EDITING FUNCTIONS
// These functions will just write the result vector to the first vector that is passed

// VECTOR ALBEGRA FUNCTIONS
la_err laVecSumInPlace(vec* vec1, vec* vec2);
la_err laVecDiffInPlace(vec* vec1 , vec* vec2);
la_err laVecScaleInPlace(vec* vec1, double factor);
la_err laCrossProd3DInPlace(vec* vec1, vec* vec2);
la_err laUnitVecInPlace(vec* in_vec);
la_err laProjectOntoInPlace(vec* proj_vec , vec* onto_vec);

// RASTER FUNCTIONS / SCREEN FUNCTIONS
la_err laNormalizeInPlace(vec* in_vec, int width, int height);
la_err laNormalizeRevInPlace(vec* in_vec , int width , int height);
la_err laImageToAxesInPlace(vec* in_vec);
la_err laAxesToImageInPlace(vec* in_vec);


#endif // VEC_H
