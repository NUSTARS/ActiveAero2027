# Autocode Instructions

### Pre-Requisites
- Download the current [NUStars ActiveAero build](https://github.com/NUSTARS/ActiveAero2027)
- Download the current [NUStars Avionics Firmware](https://github.com/NUSTARS/AvionicsBoard2027/tree/main/AvionicsBoardV1)
    - In the future, this should be added as a submodule of ActiveAero, or vice-versa
- Install [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html), used to compile autocode libraries for the Cortex-M7
- Install MATLAB and Simulink
- Install the Following MATLAB Addons
    - Aerospace Blockset
    - Aerospace Toolbox
    - Control Systems Toolbox
    - Embedded Coder
    - Embedded Coder Support Package for ARM Cortex-M Processors
    - MATLAB Coder
    - MATLAB Compiler
    - Navigation Toolbox
    - Simulink Coder
    - Simulink Compiler
    - Simulinkk Control Design
    - STM32 Microcontroller Blockset
    - Variant Manager for Simulink

### Instructions
1. Change directory into the cloned ActiveAero build, then run setupPaths to configure data directories and model linkings
2. Change into the subdirectory scripts, then run buildModels. This file should build models and configure entrypoints for model initialization
    - After code generation, ensure each generated `.c` file is in `CM7/Debug/Src/subdir.mk` (`C_SRCS`, `OBJS`, and `C_DEPS`) and `CM7/Debug/objects.list`, then rebuild `autocodeLib_CM7` before building the board firmware. The current model requires `BINARYSEARCH_real_T.c` and `LookUp_real_T_real_T.c`. The board build tracks the archive through `AvionicsBoardV1/CM7/makefile.targets`, so a normal build relinks the firmware after the archive changes.
3. In STM32CubeIDE, open the following projects:
    - The generated STM32 libary in the root directory of ActiveAero
    - The current NUStars Avionics Firmware
4. In STM32CubeIDE, change the following compilation settings for Avionics Firmware:
    - In AvionicsBoardV1 -> Properties -> Project References, ensure that AvionicsBoardV1_CM7 is enabled
    - In AvionicsBoardV1_CM7 -> Properties -> Project References, ensure that autocodeLib_CM7 is enabled
    - In AvionicsBoardV1_CM7 -> Properties -> C/C++ Build -> Settings -> MCU/MPU GCC Compiler -> Include paths, add the Inc directory from AvionicsBoardV1_CM7
    - In AvionicsBoardV1_CM7 -> Properties -> C/C++ Build -> Settings -> MCU/CPU GCC Linker -> Libraries, add:
        - Under Libraries (-l), add the library autocodeLib_CM7
        - Under Library search path (-L), Add the Debug directory from autocodeLib_CM7
            - This may not be present at first. If not, build the library to create a .a file in Debug
5. Avionics board should now compile while referencing the Autocode library. Functions to initialize models may be found in autocodeModel_initalize.{c,h}