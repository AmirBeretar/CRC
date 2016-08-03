#include <iostream>

unsigned reverse(unsigned n, unsigned level)
{
    if(level&0x1){ n = (n&0x55555555)<<1  | (n&0xAAAAAAAA)>>1 ;
                   n = (n&0x33333333)<<2  | (n&0xCCCCCCCC)>>2 ;
                   n = (n&0x0F0F0F0F)<<4  | (n&0xF0F0F0F0)>>4 ; }
    if(level&0x2)  n = (n&0x00FF00FF)<<8  | (n&0xFF00FF00)>>8 ;
    if(level&0x4)  n = (n&0x0000FFFF)<<16 | (n&0xFFFF0000)>>16;
    return n;
}

unsigned crc16(char* data, int size, unsigned poly, unsigned init, bool RefIn, bool RefOut, unsigned XorOut)
{
    unsigned crc = init;
    while(--size >= 0){
        crc ^= reverse(*data++, RefIn ? 1 : 0) << 8;
        for(int i = 0; i < 8; ++i)
            crc = (crc&0x8000) ? crc<<1 ^ poly : crc<<1;
    }
    crc ^= XorOut;
    return reverse(crc, RefOut ? 3 : 0) & 0x0000FFFF;
}

unsigned crc32(char* data, int size, unsigned poly, unsigned init, bool RefIn, bool RefOut, unsigned XorOut)
{
    unsigned crc = init;
    while(--size >= 0){
        crc ^= reverse(*data++, RefIn ? 1 : 0) << 24;
        for(int i = 0; i < 8; ++i)
            crc = (crc&0x80000000) ? crc<<1 ^ poly : crc<<1;
    }
    crc ^= XorOut;
    return reverse(crc, RefOut ? 7 : 0);
}

//      Name                Poly          Init            RefIn   RefOut      XorOut
#define CRC16_ARC           0x8005      , 0             , true  , true      , 0
#define CRC16_AUG_CCITT 	0x1021      , 0x1D0F        , false , false     , 0
#define CRC16_BUYPASS       0x8005      , 0             , false , false     , 0
#define CRC16_CCITT_FALSE 	0x1021      , 0xFFFF        , false , false     , 0
#define CRC16_CDMA2000      0xC867      , 0xFFFF        , false , false     , 0
#define CRC16_DDS_110       0x8005      , 0x800D        , false , false     , 0
#define CRC16_DECT_R        0x589       , 0             , false , false     , 0x1
#define CRC16_DECT_X        0x589       , 0             , false , false     , 0
#define CRC16_DNP           0x3D65      , 0             , true  , true      , 0xFFFF
#define CRC16_EN_13757      0x3D65      , 0             , false , false     , 0xFFFF
#define CRC16_GENIBUS       0x1021      , 0xFFFF        , false , false     , 0xFFFF
#define CRC16_MAXIM         0x8005      , 0             , true  , true      , 0xFFFF
#define CRC16_MCRF4XX       0x1021      , 0xFFFF        , true  , true      , 0
#define CRC16_RIELLO        0x1021      , 0xB2AA        , true  , true      , 0
#define CRC16_T10_DIF       0x8BB7      , 0             , false , false     , 0
#define CRC16_TELEDISK      0xA097      , 0             , false , false     , 0
#define CRC16_TMS37157  	0x1021      , 0x89EC        , true  , true      , 0
#define CRC16_USB           0x8005      , 0xFFFF        , true  , true      , 0xFFFF
#define CRC16_A             0x1021      , 0xC6C6        , true  , true      , 0
#define CRC16_KERMIT        0x1021      , 0             , true  , true      , 0
#define CRC16_MODBUS        0x8005      , 0xFFFF        , true  , true      , 0
#define CRC16_X_25          0x1021      , 0xFFFF        , true  , true      , 0xFFFF
#define CRC16_XMODEM        0x1021      , 0             , false , false     , 0

#define CRC32               0x4C11DB7 	, 0xFFFFFFFF 	, true 	, true      , 0xFFFFFFFF
#define CRC32_BZIP2         0x4C11DB7 	, 0xFFFFFFFF 	, false , false     , 0xFFFFFFFF
#define CRC32_C             0x1EDC6F41 	, 0xFFFFFFFF 	, true 	, true      , 0xFFFFFFFF
#define CRC32_D             0xA833982B 	, 0xFFFFFFFF 	, true 	, true      , 0xFFFFFFFF
#define CRC32_MPEG_2        0x4C11DB7 	, 0xFFFFFFFF 	, false , false     , 0
#define CRC32_POSIX         0x4C11DB7 	, 0             , false , false     , 0xFFFFFFFF
#define CRC32_Q             0x814141AB 	, 0             , false , false     , 0
#define CRC32_JAMCRC        0x4C11DB7 	, 0xFFFFFFFF 	, true 	, true      , 0
#define CRC32_XFER          0xAF        , 0             , false , false     , 0

int main()
{
    char data[] = "123456789";

#define TEST_CRC16(crc_type, val) \
    std::cout << #crc_type << '\t' << (crc16(data, 9, crc_type)==val) << '\n';

    TEST_CRC16(CRC16_ARC        , 0xBB3D);
    TEST_CRC16(CRC16_AUG_CCITT  , 0xE5CC);
    TEST_CRC16(CRC16_BUYPASS    , 0xFEE8);
    TEST_CRC16(CRC16_CCITT_FALSE, 0x29B1);
    TEST_CRC16(CRC16_CDMA2000   , 0x4C06);
    TEST_CRC16(CRC16_DDS_110    , 0x9ECF);
    TEST_CRC16(CRC16_DECT_R     , 0x007E);
    TEST_CRC16(CRC16_DECT_X     , 0x007F);
    TEST_CRC16(CRC16_DNP        , 0xEA82);
    TEST_CRC16(CRC16_EN_13757   , 0xC2B7);
    TEST_CRC16(CRC16_GENIBUS    , 0xD64E);
    TEST_CRC16(CRC16_MAXIM      , 0x44C2);
    TEST_CRC16(CRC16_MCRF4XX    , 0x6F91);
    TEST_CRC16(CRC16_RIELLO     , 0x63D0);
    TEST_CRC16(CRC16_T10_DIF    , 0xD0DB);
    TEST_CRC16(CRC16_TELEDISK   , 0x0FB3);
    TEST_CRC16(CRC16_TMS37157   , 0x26B1);
    TEST_CRC16(CRC16_USB        , 0xB4C8);
    TEST_CRC16(CRC16_A          , 0xBF05);
    TEST_CRC16(CRC16_KERMIT     , 0x2189);
    TEST_CRC16(CRC16_MODBUS     , 0x4B37);
    TEST_CRC16(CRC16_X_25       , 0x906E);
    TEST_CRC16(CRC16_XMODEM     , 0x31C3);

#define TEST_CRC32(crc_type, val) \
    std::cout << #crc_type << '\t' << (crc32(data, 9, crc_type)==val) << '\n';

    TEST_CRC32(CRC32       , 0xCBF43926);
    TEST_CRC32(CRC32_BZIP2 , 0xFC891918);
    TEST_CRC32(CRC32_C     , 0xE3069283);
    TEST_CRC32(CRC32_D     , 0x87315576);
    TEST_CRC32(CRC32_MPEG_2, 0x376E6E7 );
    TEST_CRC32(CRC32_POSIX , 0x765E7680);
    TEST_CRC32(CRC32_Q     , 0x3010BF7F);
    TEST_CRC32(CRC32_JAMCRC, 0x340BC6D9);
    TEST_CRC32(CRC32_XFER  , 0xBD0BE338);

    return 0;
}
