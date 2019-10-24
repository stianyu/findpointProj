/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_findpoint_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 19-Sep-2019 17:22:53
 */

#ifndef _CODER_FINDPOINT_API_H
#define _CODER_FINDPOINT_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_findpoint_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void findpoint(real_T data[2000], emxArray_real_T *P);
extern void findpoint_api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[1]);
extern void findpoint_atexit(void);
extern void findpoint_initialize(void);
extern void findpoint_terminate(void);
extern void findpoint_xil_terminate(void);

#endif

/*
 * File trailer for _coder_findpoint_api.h
 *
 * [EOF]
 */
