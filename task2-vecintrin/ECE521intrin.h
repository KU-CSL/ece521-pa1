// Define vector unit width here
#define VECTOR_WIDTH 4

#ifndef ECE521INTRIN_H_
#define ECE521INTRIN_H_

#include <cstdlib>
#include <cmath>
#include "logger.h"

//*******************
//* Type Definition *
//*******************

extern Logger ECE521Logger;

template <typename T>
struct __ece521_vec {
  T value[VECTOR_WIDTH];
};

// Declare a mask with __ece521_mask
struct __ece521_mask : __ece521_vec<bool> {};

// Declare a floating point vector register with __ece521_vec_float
#define __ece521_vec_float __ece521_vec<float>

// Declare an integer vector register with __ece521_vec_int
#define __ece521_vec_int   __ece521_vec<int>

//***********************
//* Function Definition *
//***********************

// Return a mask initialized to 1 in the first N lanes and 0 in the others
__ece521_mask _ece521_init_ones(int first = VECTOR_WIDTH);

// Return the inverse of maska
__ece521_mask _ece521_mask_not(__ece521_mask &maska);

// Return (maska | maskb)
__ece521_mask _ece521_mask_or(__ece521_mask &maska, __ece521_mask &maskb);

// Return (maska & maskb)
__ece521_mask _ece521_mask_and(__ece521_mask &maska, __ece521_mask &maskb);

// Count the number of 1s in maska
int _ece521_cntbits(__ece521_mask &maska);

// Set register to value if vector lane is active
//  otherwise keep the old value
void _ece521_vset_float(__ece521_vec_float &vecResult, float value, __ece521_mask &mask);
void _ece521_vset_int(__ece521_vec_int &vecResult, int value, __ece521_mask &mask);
// For user's convenience, returns a vector register with all lanes initialized to value
__ece521_vec_float _ece521_vset_float(float value);
__ece521_vec_int _ece521_vset_int(int value);

// Copy values from vector register src to vector register dest if vector lane active
// otherwise keep the old value
void _ece521_vmove_float(__ece521_vec_float &dest, __ece521_vec_float &src, __ece521_mask &mask);
void _ece521_vmove_int(__ece521_vec_int &dest, __ece521_vec_int &src, __ece521_mask &mask);

// Load values from array src to vector register dest if vector lane active
//  otherwise keep the old value
void _ece521_vload_float(__ece521_vec_float &dest, float* src, __ece521_mask &mask);
void _ece521_vload_int(__ece521_vec_int &dest, int* src, __ece521_mask &mask);

// Store values from vector register src to array dest if vector lane active
//  otherwise keep the old value
void _ece521_vstore_float(float* dest, __ece521_vec_float &src, __ece521_mask &mask);
void _ece521_vstore_int(int* dest, __ece521_vec_int &src, __ece521_mask &mask);

// Return calculation of (veca + vecb) if vector lane active
//  otherwise keep the old value
void _ece521_vadd_float(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
void _ece521_vadd_int(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

// Return calculation of (veca - vecb) if vector lane active
//  otherwise keep the old value
void _ece521_vsub_float(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
void _ece521_vsub_int(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

// Return calculation of (veca * vecb) if vector lane active
//  otherwise keep the old value
void _ece521_vmult_float(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
void _ece521_vmult_int(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

// Return calculation of (veca / vecb) if vector lane active
//  otherwise keep the old value
void _ece521_vdiv_float(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
void _ece521_vdiv_int(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);


// Return calculation of absolute value abs(veca) if vector lane active
//  otherwise keep the old value
void _ece521_vabs_float(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_mask &mask);
void _ece521_vabs_int(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_mask &mask);

// Return a mask of (veca > vecb) if vector lane active
//  otherwise keep the old value
void _ece521_vgt_float(__ece521_mask &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
void _ece521_vgt_int(__ece521_mask &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

// Return a mask of (veca < vecb) if vector lane active
//  otherwise keep the old value
void _ece521_vlt_float(__ece521_mask &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
void _ece521_vlt_int(__ece521_mask &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

// Return a mask of (veca == vecb) if vector lane active
//  otherwise keep the old value
void _ece521_veq_float(__ece521_mask &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
void _ece521_veq_int(__ece521_mask &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

// Adds up adjacent pairs of elements, so
//  [0 1 2 3] -> [0+1 0+1 2+3 2+3]
void _ece521_hadd_float(__ece521_vec_float &vecResult, __ece521_vec_float &vec);

// Performs an even-odd interleaving where all even-indexed elements move to front half
//  of the array and odd-indexed to the back half, so
//  [0 1 2 3 4 5 6 7] -> [0 2 4 6 1 3 5 7]
void _ece521_interleave_float(__ece521_vec_float &vecResult, __ece521_vec_float &vec);

// Add a customized log to help debugging
void addUserLog(const char * logStr);

#endif
