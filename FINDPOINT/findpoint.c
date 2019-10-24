/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: findpoint.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 19-Sep-2019 17:22:53
 */

/* Include Files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "findpoint.h"
#include "findpoint_emxutil.h"
#include "findpeaks.h"

/* Function Definitions */

/*
 * FINDPOINT find the inflection point.
 * Arguments    : const double data[2000]
 *                emxArray_real_T *P
 * Return Type  : void
 */
void findpoint(const double data[2000], emxArray_real_T *P)
{
  double smo_y[1921];
  int i;
  double s;
  int ixLead;
  int iyLead;
  emxArray_int16_T *point1;
  double tmp2;
  emxArray_int16_T *point2;
  emxArray_int16_T *point3;
  double b_y1[1920];
  emxArray_real_T *P3;
  int P1;
  int P2;
  int i0;
  int sign1;
  int sign2;
  int sign3;
  emxArray_real_T *c_y1;
  emxArray_real_T *value_P;
  emxArray_real_T *index_P;
  boolean_T exitg1;
  emxArray_boolean_T *index_maxP;

  /*  Step1: Smooth data using moving average filter */
  /*   */
  /*  smo_y2 = smooth(x, y, 0.1, 'rloess');  */
  memset(&smo_y[0], 0, 1921U * sizeof(double));
  for (i = 0; i < 2000; i++) {
    s = 0.0;
    if (1 + i < 10) {
      ixLead = 1;
      for (iyLead = 0; iyLead <= i; iyLead++) {
        ixLead = iyLead + 1;
        s += data[i + iyLead];
      }

      smo_y[i] = s / (double)ixLead;
    } else if (1 + i > 1991) {
      abort();
    } else {
      for (ixLead = 0; ixLead < 9; ixLead++) {
        s = (s + data[(i - ixLead) - 1]) + data[(i + ixLead) + 1];
      }

      s += data[i];
      smo_y[i] = s / 19.0;
    }
  }

  /*  using moving average filter with a span of  */
  /*  19 to smooth data */
  /*  plot(x,smo_y,'k',x,smo_y2,'r') */
  /*  Step2: Make a difference */
  ixLead = 1;
  iyLead = 0;
  s = smo_y[0];
  for (i = 0; i < 1920; i++) {
    tmp2 = s;
    s = smo_y[ixLead];
    b_y1[iyLead] = smo_y[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  emxInit_int16_T(&point1, 2);
  emxInit_int16_T(&point2, 2);
  emxInit_int16_T(&point3, 2);
  emxInit_real_T(&P3, 1);

  /*  Draw plot of diff_smo_y  */
  /*  figure */
  /*  subplot(2, 1, 1) */
  /*  plot(x(1:length(diff_smo_y)), diff_smo_y, 'r', x(1:length(diff_smo_y)), ... */
  /*  zeros(length(diff_smo_y),1),'k') */
  /*  legend('5点差分','0点') */
  /*  Step3: According to the difference of data, judge the inflection point */
  /*  within three classification */
  point1->size[0] = 1;
  point1->size[1] = 0;
  point2->size[0] = 1;
  point2->size[1] = 0;
  point3->size[0] = 1;
  point3->size[1] = 0;
  P1 = 0;
  P2 = 0;
  i0 = P3->size[0];
  P3->size[0] = 1;
  emxEnsureCapacity_real_T(P3, i0);
  P3->data[0] = 0.0;
  i0 = P->size[0];
  P->size[0] = 1;
  emxEnsureCapacity_real_T(P, i0);
  P->data[0] = 0.0;
  sign1 = 0;
  sign2 = 0;
  sign3 = 0;
  for (i = 0; i < 1918; i++) {
    /*  Situation a: If the inflection point is a valley, find the point close to 0 */
    s = b_y1[i + 1];
    if ((b_y1[i] <= s) && (s <= 0.0)) {
      tmp2 = b_y1[i + 2];
      if ((s <= tmp2) && (tmp2 >= 0.0)) {
        i0 = point1->size[1];
        ixLead = point1->size[0] * point1->size[1];
        point1->size[1] = i0 + 1;
        emxEnsureCapacity_int16_T(point1, ixLead);
        point1->data[i0] = (short)(2 + i);
        sign1 = 1;
        P1 = point1->data[0];

        /*  Outliers in this case is that the first point is  */
        /*  not the large-scale valley. Further research can be done using */
        /*  filloutliers function. */
      }
    }

    /*  Situation b: If the inflection point  */
    if ((b_y1[i] <= s) && (s <= 0.0)) {
      if (fabs(s) <= 0.02) {
        i0 = point2->size[1];
        ixLead = point2->size[0] * point2->size[1];
        point2->size[1] = i0 + 1;
        emxEnsureCapacity_int16_T(point2, ixLead);
        point2->data[i0] = (short)(2 + i);
        sign2 = 2;
        P2 = point2->data[0];
      } else {
        i0 = point3->size[1];
        ixLead = point3->size[0] * point3->size[1];
        point3->size[1] = i0 + 1;
        emxEnsureCapacity_int16_T(point3, ixLead);
        point3->data[i0] = (short)(2 + i);
        sign3 = 3;
      }
    }
  }

  emxFree_int16_T(&point2);
  emxFree_int16_T(&point1);
  if (sign3 != 0) {
    if (point3->size[1] >= 3) {
      emxInit_real_T(&c_y1, 1);
      i0 = c_y1->size[0];
      c_y1->size[0] = point3->size[1];
      emxEnsureCapacity_real_T(c_y1, i0);
      ixLead = point3->size[1];
      for (i0 = 0; i0 < ixLead; i0++) {
        c_y1->data[i0] = b_y1[point3->data[i0] - 1];
      }

      emxInit_real_T(&value_P, 1);
      emxInit_real_T(&index_P, 1);
      findpeaks(c_y1, value_P, index_P);
      iyLead = value_P->size[0];
      emxFree_real_T(&c_y1);
      if (value_P->size[0] <= 2) {
        if (value_P->size[0] == 1) {
          s = value_P->data[0];
        } else if ((value_P->data[0] < value_P->data[1]) || (rtIsNaN
                    (value_P->data[0]) && (!rtIsNaN(value_P->data[1])))) {
          s = value_P->data[1];
        } else {
          s = value_P->data[0];
        }
      } else {
        if (!rtIsNaN(value_P->data[0])) {
          ixLead = 1;
        } else {
          ixLead = 0;
          i = 2;
          exitg1 = false;
          while ((!exitg1) && (i <= value_P->size[0])) {
            if (!rtIsNaN(value_P->data[i - 1])) {
              ixLead = i;
              exitg1 = true;
            } else {
              i++;
            }
          }
        }

        if (ixLead == 0) {
          s = value_P->data[0];
        } else {
          s = value_P->data[ixLead - 1];
          i0 = ixLead + 1;
          for (i = i0; i <= iyLead; i++) {
            if (s < value_P->data[i - 1]) {
              s = value_P->data[i - 1];
            }
          }
        }
      }

      emxInit_boolean_T(&index_maxP, 1);
      i0 = index_maxP->size[0];
      index_maxP->size[0] = value_P->size[0];
      emxEnsureCapacity_boolean_T(index_maxP, i0);
      ixLead = value_P->size[0];
      for (i0 = 0; i0 < ixLead; i0++) {
        index_maxP->data[i0] = (value_P->data[i0] == s);
      }

      emxFree_real_T(&value_P);
      iyLead = index_maxP->size[0] - 1;
      ixLead = 0;
      for (i = 0; i <= iyLead; i++) {
        if (index_maxP->data[i]) {
          ixLead++;
        }
      }

      i0 = P3->size[0];
      P3->size[0] = ixLead;
      emxEnsureCapacity_real_T(P3, i0);
      ixLead = 0;
      for (i = 0; i <= iyLead; i++) {
        if (index_maxP->data[i]) {
          P3->data[ixLead] = index_P->data[i];
          ixLead++;
        }
      }

      emxFree_real_T(&index_P);
      emxFree_boolean_T(&index_maxP);
    } else {
      i0 = P3->size[0];
      P3->size[0] = 1;
      emxEnsureCapacity_real_T(P3, i0);
      P3->data[0] = point3->data[0];
    }
  }

  emxFree_int16_T(&point3);
  if (sign2 == 2) {
    /*      disp('Suspicious points：') */
    /*      disp(point1) */
    /*      disp('Judgement: 2') */
    i0 = P->size[0];
    P->size[0] = 1;
    emxEnsureCapacity_real_T(P, i0);
    P->data[0] = P2; 
  } else if (sign3 == 3) {
    /*      disp('Suspicious points：') */
    /*      disp(point3) */
    /*      disp('Judgement: 3') */
    i0 = P->size[0];
    P->size[0] = P3->size[0];
    emxEnsureCapacity_real_T(P, i0);
    ixLead = P3->size[0];
    for (i0 = 0; i0 < ixLead; i0++) {
      P->data[i0] = P3->data[i0];
    }
  } else {
    if (sign1 == 1) {
      /*      disp('Suspicious points：') */
      /*      disp(point1) */
      /*      disp('Judgement: 1') */
      i0 = P->size[0];
      P->size[0] = 1;
      emxEnsureCapacity_real_T(P, i0);
      P->data[0] = P1;
    }
  }

  emxFree_real_T(&P3);

  /*  fprintf('Infleciton Point：%d\n', P) */
  /*  subplot(2, 1, 2) */
  /*  plot(x, y, 'k', x, smo_y, 'r',x(P),y(P),'*') */
  /*  legend('原始数据','10% robust local regression滤波','凝血点') */
  /*  text(x(P),y(P),['(',num2str(x(P)),',',num2str(y(P)),')'],'color','b') */
}

/*
 * File trailer for findpoint.c
 *
 * [EOF]
 */
