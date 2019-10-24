/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: findpeaks.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 19-Sep-2019 17:22:53
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "findpoint.h"
#include "findpeaks.h"
#include "findpoint_emxutil.h"
#include "eml_setop.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *Yin
 *                emxArray_real_T *Ypk
 *                emxArray_real_T *Xpk
 * Return Type  : void
 */
void findpeaks(const emxArray_real_T *Yin, emxArray_real_T *Ypk, emxArray_real_T
               *Xpk)
{
  emxArray_uint32_T *x;
  unsigned int Yin_idx_0;
  int i1;
  int ny;
  emxArray_int32_T *idx;
  emxArray_int32_T *iFinite;
  emxArray_int32_T *iInfinite;
  int nPk;
  int nInf;
  char dir;
  int kfirst;
  double ykfirst;
  boolean_T isinfykfirst;
  int k;
  double yk;
  boolean_T isinfyk;
  emxArray_int32_T *iPk;
  char previousdir;
  emxArray_int32_T *c;
  emxArray_int32_T *y;
  emxInit_uint32_T(&x, 1);
  Yin_idx_0 = (unsigned int)Yin->size[0];
  i1 = x->size[0];
  x->size[0] = (int)Yin_idx_0;
  emxEnsureCapacity_uint32_T(x, i1);
  ny = (int)Yin_idx_0 - 1;
  for (i1 = 0; i1 <= ny; i1++) {
    x->data[i1] = 1U + i1;
  }

  emxInit_int32_T(&idx, 1);
  emxInit_int32_T(&iFinite, 1);
  emxInit_int32_T(&iInfinite, 1);
  Yin_idx_0 = (unsigned int)Yin->size[0];
  i1 = iFinite->size[0];
  iFinite->size[0] = (int)Yin_idx_0;
  emxEnsureCapacity_int32_T(iFinite, i1);
  Yin_idx_0 = (unsigned int)Yin->size[0];
  i1 = iInfinite->size[0];
  iInfinite->size[0] = (int)Yin_idx_0;
  emxEnsureCapacity_int32_T(iInfinite, i1);
  ny = Yin->size[0];
  nPk = 0;
  nInf = 0;
  dir = 'n';
  kfirst = 0;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 1; k <= ny; k++) {
    yk = Yin->data[k - 1];
    if (rtIsNaN(Yin->data[k - 1])) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(Yin->data[k - 1]) && (Yin->data[k - 1] > 0.0)) {
      isinfyk = true;
      nInf++;
      iInfinite->data[nInf - 1] = k;
    } else {
      isinfyk = false;
    }

    if (yk != ykfirst) {
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
      } else if (yk < ykfirst) {
        dir = 'd';
        if (('d' != previousdir) && (previousdir == 'i')) {
          nPk++;
          iFinite->data[nPk - 1] = kfirst;
        }
      } else {
        dir = 'i';
      }

      ykfirst = yk;
      kfirst = k;
      isinfykfirst = isinfyk;
    }
  }

  if (1 > nPk) {
    i1 = 0;
  } else {
    i1 = nPk;
  }

  ny = iFinite->size[0];
  iFinite->size[0] = i1;
  emxEnsureCapacity_int32_T(iFinite, ny);
  emxInit_int32_T(&iPk, 1);
  ny = iInfinite->size[0];
  if (1 > nInf) {
    iInfinite->size[0] = 0;
  } else {
    iInfinite->size[0] = nInf;
  }

  emxEnsureCapacity_int32_T(iInfinite, ny);
  ny = iPk->size[0];
  iPk->size[0] = iFinite->size[0];
  emxEnsureCapacity_int32_T(iPk, ny);
  nPk = 0;
  for (k = 0; k < i1; k++) {
    ny = iFinite->data[k];
    if (Yin->data[ny - 1] > rtMinusInf) {
      if ((Yin->data[ny - 2] > Yin->data[ny]) || rtIsNaN(Yin->data[ny])) {
        ykfirst = Yin->data[ny - 2];
      } else {
        ykfirst = Yin->data[ny];
      }

      if (Yin->data[ny - 1] - ykfirst >= 0.0) {
        nPk++;
        iPk->data[nPk - 1] = iFinite->data[k];
      }
    }
  }

  emxInit_int32_T(&c, 1);
  emxInit_int32_T(&y, 2);
  i1 = iPk->size[0];
  if (1 > nPk) {
    iPk->size[0] = 0;
  } else {
    iPk->size[0] = nPk;
  }

  emxEnsureCapacity_int32_T(iPk, i1);
  do_vectors(iPk, iInfinite, c, idx, iFinite);
  ny = c->size[0];
  emxFree_int32_T(&iInfinite);
  emxFree_int32_T(&iFinite);
  if (ny < 1) {
    kfirst = 0;
  } else {
    kfirst = ny;
  }

  i1 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = kfirst;
  emxEnsureCapacity_int32_T(y, i1);
  if (kfirst > 0) {
    y->data[0] = 1;
    ny = 1;
    for (k = 2; k <= kfirst; k++) {
      ny++;
      y->data[k - 1] = ny;
    }
  }

  i1 = idx->size[0];
  idx->size[0] = y->size[1];
  emxEnsureCapacity_int32_T(idx, i1);
  ny = y->size[1];
  for (i1 = 0; i1 < ny; i1++) {
    idx->data[i1] = y->data[i1];
  }

  emxFree_int32_T(&y);
  if (idx->size[0] > Yin->size[0]) {
    i1 = idx->size[0];
    idx->size[0] = Yin->size[0];
    emxEnsureCapacity_int32_T(idx, i1);
  }

  i1 = iPk->size[0];
  iPk->size[0] = idx->size[0];
  emxEnsureCapacity_int32_T(iPk, i1);
  ny = idx->size[0];
  for (i1 = 0; i1 < ny; i1++) {
    iPk->data[i1] = c->data[idx->data[i1] - 1];
  }

  emxFree_int32_T(&c);
  emxFree_int32_T(&idx);
  i1 = Ypk->size[0];
  Ypk->size[0] = iPk->size[0];
  emxEnsureCapacity_real_T(Ypk, i1);
  ny = iPk->size[0];
  for (i1 = 0; i1 < ny; i1++) {
    Ypk->data[i1] = Yin->data[iPk->data[i1] - 1];
  }

  i1 = Xpk->size[0];
  Xpk->size[0] = iPk->size[0];
  emxEnsureCapacity_real_T(Xpk, i1);
  ny = iPk->size[0];
  for (i1 = 0; i1 < ny; i1++) {
    Xpk->data[i1] = x->data[iPk->data[i1] - 1];
  }

  emxFree_uint32_T(&x);
  emxFree_int32_T(&iPk);
}

/*
 * File trailer for findpeaks.c
 *
 * [EOF]
 */
