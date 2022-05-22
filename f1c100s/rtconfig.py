import os
import platform
# toolchains options
ARCH        ='arm'
CPU         ='R6'
CROSS_TOOL  ='gcc'

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = r'../'

RTT_ROOT = r'../'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    EXEC_PATH   = r'/usr/bin'
else:
    print ("Please make sure your toolchains is GNU GCC!")
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'release'
# BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX  = 'arm-none-eabi-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'g++'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'
    STRIP = PREFIX + 'strip'

    DEVICE  = ' -mcpu=arm926ej-s -ffunction-sections -fdata-sections'# -std=gnu99'
    CFLAGS  = DEVICE + ' -Wall' + ' -DUSBH_IRQHandler=USBH_IRQHandler' + ' -DUSBD_IRQHandler=USBD_IRQHandler'
    AFLAGS  = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS  = DEVICE + ' -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,system_vectors -T link.lds'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS

    # module setting
    CXXFLAGS = DEVICE + ' -fno-exceptions -fno-rtti '
    M_CFLAGS = CFLAGS + ' -mlong-calls -fPIC '
    M_CXXFLAGS = CXXFLAGS + ' -mlong-calls -fPIC'
    M_LFLAGS = CXXFLAGS + ' -Wl,--gc-sections,-z,max-page-size=0x4' +\
                                    ' -shared -fPIC -nostartfiles -static-libgcc'
    M_POST_ACTION = STRIP + ' -R .hash $TARGET\n' + SIZE + ' $TARGET \n'

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

POST_ACTION += '@cmd /c compress.exe rtthread.bin fw_compress.bin \n'
POST_ACTION += '@cmd /c rt_ota_packaging_tool_cli.exe -f fw_compress.bin -v 1.5.0_1212 -p app -s aes -i usguJdWWUugadheA -k qnbGbxjnxtwaPqjuntaZyQvZepywimdg \n'
POST_ACTION += '@cmd /c echo File generated successfully. \n'
