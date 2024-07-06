#include <stdio.h>
#include "../include/mat.h"
#include "../include/vec.h"
#include "../include/err.h"

la_err vector_from_array_test();
la_err vecmatmul_test();

int main(void)
{
    la_err_print(vector_from_array_test());
    la_err_print(vecmatmul_test());
}

la_err vector_from_array_test()
{
    double array[] = {
        1 , 1 , 1 ,
        1 , 1 , 1 , 
        0 , 1 , 0 ,
        4 , 3 , 9 
    };

    vec** vector_array;
    la_err error_code = laVecsFromArray(array , 3 , 4 , &vector_array);
    if (error_code != LA_SUCCESS) { return error_code; }

    for (int i=0 ; i<4 ; i++) {
        laPrintVec(vector_array[i]);
        laFreeVec(&vector_array[i]);
    }

    return LA_SUCCESS;
}

la_err vecmatmul_test()
{
    double vec_[] = {1 , 2 , 3 , 4};
    vec* vector;
    la_err error_code = laVecFromArray(vec_ , 4 , &vector);
    if (error_code != LA_SUCCESS) { return error_code; }

    double mat_[] = {
        1 , 2 ,
        3 , 4 ,
        5 , 6 ,
        7 , 8
    };
    mat* matrix;
    error_code = laMatFromArray(mat_ , 4 , 2 , &matrix);
    if (error_code != LA_SUCCESS) { return error_code; }

    vec* new_vec;
    error_code = laVecMatMul(vector , matrix , &new_vec);
    if (error_code != LA_SUCCESS) { return error_code; }
    laPrintVec(new_vec);

    laVecMatMulInPlace(vector , matrix);
    laPrintVec(vector);

    return LA_SUCCESS;
}