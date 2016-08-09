# CRC
Universal CRC16 and CRC32 functions

To take advantage of a specific embodiment crc instead of the last argument you can insert the appropriate macros.

Example of use: unsigned crc = crc16(data, size, CRC16_XMODEM);

Parameter values are taken from here:
http://reveng.sourceforge.net/crc-catalogue/16.htm#crc.cat-bits.16
http://reveng.sourceforge.net/crc-catalogue/17plus.htm#crc.cat-bits.32
