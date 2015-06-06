# m35080_Read_BitBang
Arduino sketch for dumping data from the registers of the m35080 eeprom throught the bitbang method.


ISSUES:

The dump from the incremental registers, is for demo purposes, as this sketch can only read 1 byte and the incremental registers are 2 bytes.

The datasheet doesn´t provide instruction for reading incremental registers, so only half of the register could be read.

TODO:

-Adding user friendly UI.
-Code optimizartions
