#ifndef ATMOS_DEFINE
#define PRESSURE0                      101325.0                  /*  N/m^2                  */
#define TEMPERATURE0                   288.15                    /*  K                      */
#define GRAV_CONST                     9.80665                   /*  m/s^2                  */
#define MOL_WT                         28.9644                   /*  kg/kgmol (air)         */
#define R_HAT                          8314.32                   /*  J/kgmol.K (gas const.) */
#define GAMMA                          1.4                       /*  (specific heat ratio) */
#define GMR                            ( GRAV_CONST * MOL_WT / R_HAT )
#define ATMOS_DEFINE
#endif                                 /* ATMOS_DEFINE */
