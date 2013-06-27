LM4F-MSC-BASE
===================

INSTALLATION:

* install the openocd from git to have the icdi interface
    for arch users found at <https://aur.archlinux.org/packages/openocd-git/>
* install the arm-none-eabi toolchain and add it to your path
    for arch users found in at <https://aur.archlinux.org/packages/arm-none-eabi-gcc/>
    and at <https://aur.archlinux.org/packages/arm-none-eabi-gdb/>
* Run make
* Run make flash
* Run make gdb to get a debugging terminal
* add a udev rule to /etc/udev/rule.d/ call it 75-lm4f.rules
    containing code:
    ```
    ATTRS{idVendor}=="1cbe", ATTRS{idProduct}=="00fd", MODE="0666", SYMLINK+="lm4f"
    ```
    this will link your ek-lm4f120 as /dev/lm4f and enable the make uart target, which requires screen

StellarisWare:

* download Stellarisware: <http://www.ti.com/tool/sw-lm3s>  
* compile StellarisWare as a library.
* tell the makefile where the library is with the 'STELLARISWARE_LIBS' variable
* tell the makefile where the header files are with the 'SELLARISWARE_INC' variable
