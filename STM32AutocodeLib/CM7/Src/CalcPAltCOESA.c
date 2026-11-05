/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CalcPAltCOESA.c
 *
 * Code generated for Simulink model 'autocodeModel'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Tue Nov  3 18:52:24 2026
 */

#include "CalcPAltCOESA.h"
#include "COESA76DATA_MACRO.h"
#include "COESAATMOS_MACRO.h"
#include "rt_powd_snf.h"
#include <math.h>
#include "rtwtypes.h"

/*
 *         Using cached pressure and Altitude tables, find the working interval
 *         and perform logarithmic interpolation.
 */
void CalcPAltCOESA(const real_T *pressure, real_T *altitude, real_T
                   *temperature76, real_T *pressureRatio76, int_T numPoints)
{
  int_T i;
  real_T ptemp;
  for (i=0; i<numPoints; i++) {
    int_T bottom = 0;
    int_T top = NUM1976PTS-1;
    int_T idx;

    /* Find altitude interval using binary search
     *
     * Deal with the extreme cases first:
     *   if pressure >= pressureRatio76[bottom]*PRESSURE0
     *   then return idx = bottom
     *
     *   if pressure <= pressureRatio76[top]*PRESSURE0
     *   then return idx = top
     */
    if (pressure[i] >= pressureRatio76[bottom]*PRESSURE0) {
      idx = bottom;
    } else if (pressure[i] <= pressureRatio76[top]*PRESSURE0) {
      idx = NUM1976PTS-2;
    } else {
      for (;;) {
        idx = (bottom + top)/2;
        if (pressure[i] > pressureRatio76[idx]*PRESSURE0) {
          top = idx - 1;
        } else if (pressure[i] <= pressureRatio76[idx+1]*PRESSURE0) {
          bottom = idx + 1;
        } else {
          /* we have pressureRatio76[idx]*PRESSURE0 >= pressure[i] >
           *                          pressureRatio76[idx+1]*PRESSURE0,
           * so break and just use idx
           */
          break;
        }
      }
    }

    /* Interval has been obtained, now do log altitude interpolation.
     */
    if (pressure[i] == (PRESSURE0 * pressureRatio76[idx])) {
      altitude[i] = altitude76[idx];
    } else {
      if (tempGradient76[idx] != 0.0 ) {
        ptemp = (rt_powd_snf(pressure[i]/(PRESSURE0 * pressureRatio76[idx]),
                             (tempGradient76[idx]/GMR)));
        altitude[i] = altitude76[idx] + ((1.0 - ptemp)/
          (tempGradient76[idx] * ptemp))*temperature76[idx];
      } else {
        altitude[i] = altitude76[idx]-((temperature76[idx]/GMR)*
          log(pressure[i]/(PRESSURE0 * pressureRatio76[idx])));
      }
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
