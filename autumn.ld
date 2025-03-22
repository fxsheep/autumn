OUTPUT_ARCH(arm)
ENTRY(reset)

SECTIONS
{
    . = 0x00000000; /* ROM start address */
    .text : {
        _stext = ABSOLUTE(.);
        KEEP(*(vectors))
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata.*) /* Capture all rodata subsections */
        _etext = ABSOLUTE(.);
    }

    _eronly = _etext; /* ROM address where .data is stored */

    . = 0xE0000000; /* Start of SRAM */
    .data : AT(_eronly) {
        _sdata = .;
        *(.data)
        CONSTRUCTORS
        _edata = .;
    }

    .bss : {
        _sbss = .;
        *(.bss)
        *(COMMON)
        _ebss = .;
    }
}
