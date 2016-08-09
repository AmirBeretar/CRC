# CRC
Universal CRC16 and CRC32 functions

To take advantage of a specific embodiment crc instead of the last argument you can insert the appropriate macros.

Example of use:

char data[] = "123456789";

unsigned size = 9;

unsigned crc = crc16(data, size, CRC16_XMODEM);


List of macros:

CRC16_ARC

CRC16_AUG_CCITT

CRC16_BUYPASS

CRC16_CCITT_FALSE

CRC16_CDMA2000

CRC16_DDS_110

CRC16_DECT_R

CRC16_DECT_X

CRC16_DNP

CRC16_EN_13757

CRC16_GENIBUS

CRC16_MAXIM

CRC16_MCRF4XX

CRC16_RIELLO

CRC16_T10_DIF

CRC16_TELEDISK

CRC16_TMS37157

CRC16_USB

CRC16_A

CRC16_KERMIT

CRC16_MODBUS

CRC16_X_25

CRC16_XMODEM


CRC32

CRC32_BZIP2

CRC32_C

CRC32_D

CRC32_MPEG_2

CRC32_POSIX

CRC32_Q

CRC32_JAMCRC

CRC32_XFER


Parameter values are taken from here:

http://reveng.sourceforge.net/crc-catalogue/16.htm#crc.cat-bits.16

http://reveng.sourceforge.net/crc-catalogue/17plus.htm#crc.cat-bits.32

