#ifndef ERR_H
#define ERR_H

typedef enum {
    LA_TRUE = 0,
    LA_FALSE = 1
}la_bool;

typedef enum {
    LA_SUCCESS = 15,
    LA_ERR_ZERO_LENGTH = 16,
    LA_ERR_INVALID_DIM = 17,
    LA_ERR_INVALID_AXIS = 18,
    LA_ERR_MEMORY_ALLOCATION = 19,
    LA_ERR_INVALID_PTR = 20,
    LA_ERR_ZERO_DIV = 21,
    LA_ERR_NOT_3D_OBJ = 22, // A 3D object is a vector or matrix of 1x3 or 3x3 dimensions. 1x4 and 4x4 is valid for homogeneous coordinates
    LA_UK_ERROR = 23
}la_err;


void la_err_print(la_err error_code);
const char* la_error_message(la_err error_code);

#endif