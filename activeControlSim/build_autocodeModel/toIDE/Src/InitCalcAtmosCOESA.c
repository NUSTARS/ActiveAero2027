/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: InitCalcAtmosCOESA.c
 *
 * Code generated for Simulink model 'autocodeModel'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Tue Nov  3 18:52:24 2026
 */

#include "InitCalcAtmosCOESA.h"
#include "COESA76DATA_MACRO.h"
#include "COESAATMOS_MACRO.h"
#include <math.h>
#include "rtwtypes.h"

/*         Initialize pressure and temperature tables. */
void InitCalcAtmosCOESA(real_T *temperature76, real_T *pressureRatio76)
{
  if (temperature76[0] != TEMPERATURE0 ) {
    int_T k;
    temperature76[0] = TEMPERATURE0;
    pressureRatio76[0] = 1.0;

    /* set up the data at the 1976 altitude breakpoints */
    for (k=0; k<(NUM1976PTS-1); k++) {
      if (tempGradient76[k] != 0.0) {
        temperature76[k+1] = temperature76[k] +
          tempGradient76[k]*(altitude76[k+1] - altitude76[k]);
        pressureRatio76[k+1] = pressureRatio76[k] *
          exp(log(temperature76[k]/temperature76[k+1]) * GMR/tempGradient76[k]);
      } else {
        temperature76[k+1] = temperature76[k];
        pressureRatio76[k+1] = pressureRatio76[k] *
          exp((-GMR)*(altitude76[k+1] - altitude76[k])/temperature76[k]);
      }
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
