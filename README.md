LM4F-MSC-BASE
===================

INSTALLATION:

* install the openocd from git to have the icdi interface
* install the arm-none-eabi toolchain and add it to your path
* Run make
* Run make flash
* Run make gdb to get a debugging terminal
* add a udev rule to /etc/udev/rule.d/ call it 75-lm4f.rules
    containing code:
    ```
    ATTRS{idVendor}=="1cbe", ATTRS{idProduct}=="00fd", MODE="0666", SYMLINK+="lm4f"
    ```
    this will link your ek-lm4f120 as /dev/lm4f and enable the make uart target, which requires screen
