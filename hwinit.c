#include <stdint.h>
#include "memio.h"

void timer_delay_9600(void)
{
    writel(0, 0xC0C8200C);
    writel(0, 0xC0C82008);
    writel(0, 0xC0C82010);
    writel(1, 0xC0C8200C);

    while ( readl(0xC0C82008) < 9600 );
}

void timer_delay_96000(void)
{
    writel(0, 0xC0C8200C);
    writel(0, 0xC0C82008);
    writel(0, 0xC0C82010);
    writel(1, 0xC0C8200C);

    while ( readl(0xC0C82008) < 96000 );
}

void timer_delay_288000(void)
{
    writel(0, 0xC0C8200C);
    writel(0, 0xC0C82008);
    writel(0, 0xC0C82010);
    writel(1, 0xC0C8200C);

    while ( readl(0xC0C82008) < 288000 );
}

void hw_init_coldboot(void)
{
    writel(1, 0xC0C88024);
    writel(1, 0xC0C88058);
    writel(0x1F, 0xC0C82100);
    writel((readl(0xC0101000) >> 2) << 2, 0xC0101000);
    writel((readl(0xC0101000) >> 2) << 2, 0xC0101000);
    writel(0x10001, 0xC0100000);
    timer_delay_9600();
    writel(0x2143, 0xC0100004);
    timer_delay_9600();
    writel(readl(0xC0100000) & 0xFFFEFFFE, 0xC0100000);
    do
        timer_delay_96000();
    while ( (readl(0xC0100000) & 0x80008000) != 0x80008000 );
    writel(readl(0xC0100000) | 2, 0xC0100000);

    writel(0, 0xC0101024);
    writel(readl(0xC0101124) | 0x4012121, 0xC0101124);

    writel(0x1102512, 0xC0101000);
    writel(1, 0xC0101004);
    writel(0, 0xC010100C);
    writel(0, 0xC0101024);
    writel(0, 0xC010102C);
    writel(0, 0xC0101034);
    writel(1, 0xC010105C);
    writel(0x53F2A, 0xC0101100);
    writel(1, 0xC0101104);
    writel(1, 0xC0101108);
    writel(0, 0xC010110C);
    writel(1, 0xC0101110);
    writel(0, 0xC0101124);
    writel(0, 0xC010112C);
    writel(0, 0xC0101134);
    writel(3, 0xC0101144);
    writel(1, 0xC0101158);
    writel(1, 0xC010115C);
    writel(0x10F, 0xC0102004);
    writel(5, 0xC0101214);
    writel(5, 0xC0101218);
    writel(5, 0xC010121C);
    writel(5, 0xC0101220);
    writel(5, 0xC0101224);
    writel(5, 0xC0101228);
    writel(5, 0xC010122C);
    timer_delay_288000();
    writel(2, 0xC0101000);
    writel(1, 0xC0101004);
    writel(0, 0xC010100C);
    writel(0, 0xC0101024);
    writel(0, 0xC010102C);
    writel(0, 0xC0101034);
    writel(1, 0xC010105C);
    writel(0x53F2A, 0xC0101100);
    writel(1, 0xC0101104);
    writel(1, 0xC0101108);
    writel(2, 0xC010110C);
    writel(1, 0xC0101110);
    writel(0xD0727A7, 0xC0101124);
    writel(0x311, 0xC010112C);
    writel(0x107, 0xC0101134);
    writel(3, 0xC0101144);
    writel(1, 0xC0101158);
    writel(1, 0xC010115C);
    writel(0x17F, 0xC0102004);
    writel(5, 0xC0101214);
    writel(5, 0xC0101218);
    writel(5, 0xC010121C);
    writel(5, 0xC0101220);
    writel(5, 0xC0101224);
    writel(5, 0xC0101228);
    writel(5, 0xC010122C);
    writel(0xFFFFFFFF, 0xC0101200);

    writel(3, 0xC0C81000);
    writel(0, 0xC0C81008);
    writel(0, 0xC0C81004);
}

void hw_init_warmboot(void) {

}

