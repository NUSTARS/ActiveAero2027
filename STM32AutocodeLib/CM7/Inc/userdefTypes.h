/*
 *
 * Types copied from the main STM32 project, needed for wrapper
 * declarations
 *
 */

#ifndef userdefTypes
#define userdefTypes

#ifndef AVIONICS_VECTOR3F_T_DEFINED
#define AVIONICS_VECTOR3F_T_DEFINED
typedef struct {
    double x;
    double y;
    double z;
} Vector3f_t;
#endif

#endif
