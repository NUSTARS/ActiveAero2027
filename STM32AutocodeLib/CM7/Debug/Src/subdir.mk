################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/autocodeLib_CM7.c \
../Src/autocodeModel.c \
../Src/autocodeModel_data.c \
../Src/autocodeModel_initialize.c \
../Src/autocodePlant.c \
../Src/autocodePlant_data.c \
../Src/autocodePlant_initialize.c \
../Src/BINARYSEARCH_real_T.c \
../Src/binsearch_u32d.c \
../Src/binsearch_u32d_prevIdx.c \
../Src/const_params_autocodeModel.c \
../Src/const_params_autocodePlant.c \
../Src/intrp2d_la_pw.c \
../Src/intrp3d_l_pw.c \
../Src/look1_binlcpw.c \
../Src/look2_binlcpw.c \
../Src/look2_binlxpw.c \
../Src/LookUp_real_T_real_T.c \
../Src/mul_s32_sat.c \
../Src/mul_wide_s32.c \
../Src/plook_bincpa.c \
../Src/plook_binx.c \
../Src/rtGetInf.c \
../Src/rtGetNaN.c \
../Src/rt_atan2d_snf.c \
../Src/rt_mldivide_U1d3x3_U2d_9O8lG8ax.c \
../Src/rt_modd_snf.c \
../Src/rt_nonfinite.c \
../Src/rt_nrand_Upu32_Yd_f_pw_snf.c \
../Src/rt_powd_snf.c \
../Src/rt_remd_snf.c \
../Src/rt_urand_Upu32_Yd_f_pw_snf.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/autocodeLib_CM7.o \
./Src/autocodeModel.o \
./Src/autocodeModel_data.o \
./Src/autocodeModel_initialize.o \
./Src/autocodePlant.o \
./Src/autocodePlant_data.o \
./Src/autocodePlant_initialize.o \
./Src/BINARYSEARCH_real_T.o \
./Src/binsearch_u32d.o \
./Src/binsearch_u32d_prevIdx.o \
./Src/const_params_autocodeModel.o \
./Src/const_params_autocodePlant.o \
./Src/intrp2d_la_pw.o \
./Src/intrp3d_l_pw.o \
./Src/look1_binlcpw.o \
./Src/look2_binlcpw.o \
./Src/look2_binlxpw.o \
./Src/LookUp_real_T_real_T.o \
./Src/mul_s32_sat.o \
./Src/mul_wide_s32.o \
./Src/plook_bincpa.o \
./Src/plook_binx.o \
./Src/rtGetInf.o \
./Src/rtGetNaN.o \
./Src/rt_atan2d_snf.o \
./Src/rt_mldivide_U1d3x3_U2d_9O8lG8ax.o \
./Src/rt_modd_snf.o \
./Src/rt_nonfinite.o \
./Src/rt_nrand_Upu32_Yd_f_pw_snf.o \
./Src/rt_powd_snf.o \
./Src/rt_remd_snf.o \
./Src/rt_urand_Upu32_Yd_f_pw_snf.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/autocodeLib_CM7.d \
./Src/autocodeModel.d \
./Src/autocodeModel_data.d \
./Src/autocodeModel_initialize.d \
./Src/autocodePlant.d \
./Src/autocodePlant_data.d \
./Src/autocodePlant_initialize.d \
./Src/BINARYSEARCH_real_T.d \
./Src/binsearch_u32d.d \
./Src/binsearch_u32d_prevIdx.d \
./Src/const_params_autocodeModel.d \
./Src/const_params_autocodePlant.d \
./Src/intrp2d_la_pw.d \
./Src/intrp3d_l_pw.d \
./Src/look1_binlcpw.d \
./Src/look2_binlcpw.d \
./Src/look2_binlxpw.d \
./Src/LookUp_real_T_real_T.d \
./Src/mul_s32_sat.d \
./Src/mul_wide_s32.d \
./Src/plook_bincpa.d \
./Src/plook_binx.d \
./Src/rtGetInf.d \
./Src/rtGetNaN.d \
./Src/rt_atan2d_snf.d \
./Src/rt_mldivide_U1d3x3_U2d_9O8lG8ax.d \
./Src/rt_modd_snf.d \
./Src/rt_nonfinite.d \
./Src/rt_nrand_Upu32_Yd_f_pw_snf.d \
./Src/rt_powd_snf.d \
./Src/rt_remd_snf.d \
./Src/rt_urand_Upu32_Yd_f_pw_snf.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32H755ZITx -DSTM32 -DSTM32H7DUAL -DSTM32H7 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/autocodeLib_CM7.cyclo ./Src/autocodeLib_CM7.d ./Src/autocodeLib_CM7.o ./Src/autocodeLib_CM7.su ./Src/autocodeModel.cyclo ./Src/autocodeModel.d ./Src/autocodeModel.o ./Src/autocodeModel.su ./Src/autocodeModel_data.cyclo ./Src/autocodeModel_data.d ./Src/autocodeModel_data.o ./Src/autocodeModel_data.su ./Src/autocodeModel_initialize.cyclo ./Src/autocodeModel_initialize.d ./Src/autocodeModel_initialize.o ./Src/autocodeModel_initialize.su ./Src/autocodePlant.cyclo ./Src/autocodePlant.d ./Src/autocodePlant.o ./Src/autocodePlant.su ./Src/autocodePlant_data.cyclo ./Src/autocodePlant_data.d ./Src/autocodePlant_data.o ./Src/autocodePlant_data.su ./Src/autocodePlant_initialize.cyclo ./Src/autocodePlant_initialize.d ./Src/autocodePlant_initialize.o ./Src/autocodePlant_initialize.su ./Src/binsearch_u32d.cyclo ./Src/binsearch_u32d.d ./Src/binsearch_u32d.o ./Src/binsearch_u32d.su ./Src/binsearch_u32d_prevIdx.cyclo ./Src/binsearch_u32d_prevIdx.d ./Src/binsearch_u32d_prevIdx.o ./Src/binsearch_u32d_prevIdx.su ./Src/const_params_autocodeModel.cyclo ./Src/const_params_autocodeModel.d ./Src/const_params_autocodeModel.o ./Src/const_params_autocodeModel.su ./Src/const_params_autocodePlant.cyclo ./Src/const_params_autocodePlant.d ./Src/const_params_autocodePlant.o ./Src/const_params_autocodePlant.su ./Src/intrp2d_la_pw.cyclo ./Src/intrp2d_la_pw.d ./Src/intrp2d_la_pw.o ./Src/intrp2d_la_pw.su ./Src/intrp3d_l_pw.cyclo ./Src/intrp3d_l_pw.d ./Src/intrp3d_l_pw.o ./Src/intrp3d_l_pw.su ./Src/look1_binlcpw.cyclo ./Src/look1_binlcpw.d ./Src/look1_binlcpw.o ./Src/look1_binlcpw.su ./Src/look2_binlcpw.cyclo ./Src/look2_binlcpw.d ./Src/look2_binlcpw.o ./Src/look2_binlcpw.su ./Src/look2_binlxpw.cyclo ./Src/look2_binlxpw.d ./Src/look2_binlxpw.o ./Src/look2_binlxpw.su ./Src/mul_s32_sat.cyclo ./Src/mul_s32_sat.d ./Src/mul_s32_sat.o ./Src/mul_s32_sat.su ./Src/mul_wide_s32.cyclo ./Src/mul_wide_s32.d ./Src/mul_wide_s32.o ./Src/mul_wide_s32.su ./Src/plook_bincpa.cyclo ./Src/plook_bincpa.d ./Src/plook_bincpa.o ./Src/plook_bincpa.su ./Src/plook_binx.cyclo ./Src/plook_binx.d ./Src/plook_binx.o ./Src/plook_binx.su ./Src/rtGetInf.cyclo ./Src/rtGetInf.d ./Src/rtGetInf.o ./Src/rtGetInf.su ./Src/rtGetNaN.cyclo ./Src/rtGetNaN.d ./Src/rtGetNaN.o ./Src/rtGetNaN.su ./Src/rt_atan2d_snf.cyclo ./Src/rt_atan2d_snf.d ./Src/rt_atan2d_snf.o ./Src/rt_atan2d_snf.su ./Src/rt_mldivide_U1d3x3_U2d_9O8lG8ax.cyclo ./Src/rt_mldivide_U1d3x3_U2d_9O8lG8ax.d ./Src/rt_mldivide_U1d3x3_U2d_9O8lG8ax.o ./Src/rt_mldivide_U1d3x3_U2d_9O8lG8ax.su ./Src/rt_modd_snf.cyclo ./Src/rt_modd_snf.d ./Src/rt_modd_snf.o ./Src/rt_modd_snf.su ./Src/rt_nonfinite.cyclo ./Src/rt_nonfinite.d ./Src/rt_nonfinite.o ./Src/rt_nonfinite.su ./Src/rt_nrand_Upu32_Yd_f_pw_snf.cyclo ./Src/rt_nrand_Upu32_Yd_f_pw_snf.d ./Src/rt_nrand_Upu32_Yd_f_pw_snf.o ./Src/rt_nrand_Upu32_Yd_f_pw_snf.su ./Src/rt_powd_snf.cyclo ./Src/rt_powd_snf.d ./Src/rt_powd_snf.o ./Src/rt_powd_snf.su ./Src/rt_remd_snf.cyclo ./Src/rt_remd_snf.d ./Src/rt_remd_snf.o ./Src/rt_remd_snf.su ./Src/rt_urand_Upu32_Yd_f_pw_snf.cyclo ./Src/rt_urand_Upu32_Yd_f_pw_snf.d ./Src/rt_urand_Upu32_Yd_f_pw_snf.o ./Src/rt_urand_Upu32_Yd_f_pw_snf.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su
	-$(RM) ./Src/BINARYSEARCH_real_T.cyclo ./Src/BINARYSEARCH_real_T.d ./Src/BINARYSEARCH_real_T.o ./Src/BINARYSEARCH_real_T.su ./Src/LookUp_real_T_real_T.cyclo ./Src/LookUp_real_T_real_T.d ./Src/LookUp_real_T_real_T.o ./Src/LookUp_real_T_real_T.su

.PHONY: clean-Src

