#include "../include/err.h"

#include <stdio.h>
/*
    error codes -----

    LA_SUCCESS
    LA_ERR_ZERO_LENGTH
    LA_ERR_INVALID_DIM
    LA_ERR_INVALID_AXIS,
    LA_ERR_MEMORY_ALLOCATION
    LA_ERR_INVALID_PTR
    LA_ERR_ZERO_DIV
    LA_ERR_NOT_3D_OBJ
    LA_UK_ERROR
*/
void la_err_print(la_err error_code)
{
    switch (error_code)
    {
        case LA_SUCCESS:
            printf("Success\n");
            break;
        case LA_ERR_ZERO_LENGTH:
            printf("Cannot work with object below 1 dimension\n");
            break;
        case LA_ERR_INVALID_DIM:
            printf("Object of invalid dimensions passed\n");
            break;
        case LA_ERR_INVALID_AXIS:
            printf("Invalid axis specifier passed\n");
            break;
        case LA_ERR_MEMORY_ALLOCATION:
            printf("Failed to allocate memory\n");
            break;
        case LA_ERR_INVALID_PTR:
            printf("Invalid pointer passed\n");
            break;
        case LA_ERR_ZERO_DIV:
            printf("Math zero division error\n");
            break;
        case LA_ERR_NOT_3D_OBJ:
            printf("Operation is invalid for object of more or less than 3 dimensions");
            break;
        case LA_UK_ERROR:
            printf("Unknown error occurred\n");
            break;
        default:
            printf("Unknown error occurred\n");
            break;
    }
}

const char* la_error_message(la_err error_code)
{
    switch (error_code)
    {
        case LA_SUCCESS:
            return "Success\n";
            break;
        case LA_ERR_ZERO_LENGTH:
            return "Cannot work with object below 1 dimension\n";
            break;
        case LA_ERR_INVALID_DIM:
            return "Object of invalid dimensions passed\n";
            break;
        case LA_ERR_INVALID_AXIS:
            return "Invalid axis specifier passed\n";
            break;
        case LA_ERR_MEMORY_ALLOCATION:
            return "Failed to allocate memory\n";
            break;
        case LA_ERR_INVALID_PTR:
            return "Invalid pointer passed\n";
            break;
        case LA_ERR_ZERO_DIV:
            return "Math zero division error\n";
            break;
        case LA_ERR_NOT_3D_OBJ:
            return "Operation is invalid for object of more or less than 3 dimensions\n";
            break;
        case LA_UK_ERROR:
            return "Unknown error occurred\n";
            break;
        default:
            return "Unknown error occurred\n";
            break;
    }
}