#include <stdarg.h>

#include <mini-printf.h>

#include "debug.h"
#include "pl011-uart.h"

void debug_printf(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    debug_vprintf(fmt, va);
    va_end(va);
}

void debug_vprintf(const char *fmt, va_list ap)
{
    int size;
    uint8_t buf[2048];
    size = mini_vsnprintf((char *)buf, sizeof buf, fmt, ap);

    for (int i = 0; i < size; i++) {
        uart0_putc(buf[i]);
    }

    uart0_putc('\n');
}

void debug_exception(uint32_t type, uint32_t lr)
{
    debug_printf("!!! Fatal exception !!! %u 0x%08x", type, lr);
}

void debug_gothere(void)
{
    debug_printf("Made it here?");
}

void debug_dumpreg(uint32_t reg)
{
    debug_printf("Dump reg: %08x", reg);
}

void debug_hexdump(const uint8_t *data, size_t len)
{
    debug_printf("Begin hex dump");
    while (len >= 16) {
        debug_printf("%02x%02x%02x%02x "
                     "%02x%02x%02x%02x "
                     "%02x%02x%02x%02x "
                     "%02x%02x%02x%02x",
                     data[0],
                     data[1],
                     data[2],
                     data[3],
                     data[4],
                     data[5],
                     data[6],
                     data[7],
                     data[8],
                     data[9],
                     data[10],
                     data[11],
                     data[12],
                     data[13],
                     data[14],
                     data[15]);
        data += 16;
        len -= 16;
    }
}
