INCLUDE settings.ld

/* f256k uses first 16 bytes of ZP for mmu control? */
__rc0 = 0x10;
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0x10, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x2f, "Inconsistent zero page map.")


MEMORY {
    /* kernel uses 0xf0-0xff for parameter passing */
    zp : ORIGIN = __rc31 + 1, LENGTH = 0xF0 - (__rc31 + 1)
    ram (rw) : ORIGIN = __f256_start, LENGTH = 0xC000-__f256_start
}


REGION_ALIAS("c_readonly", ram)
REGION_ALIAS("c_writeable", ram)


/* NOTE: c.ld has zp.ld before text.ld.
 * If the compiler decides to put data into the zeropage (.zp.data),
 * then it would appear in our output binary before the .text section.
 * And because the text section is our starting point, the zeropage
 * data pushes our _start address up by some indeterminate amount, which
 * is a pain.
 * So, here I've just done the same as c.ld, but reordered things so the
 * .zp data appears _after_ our .text section.
 * (the zeropage data copied into the zeropage at startup by the crt
 * copy-zp-data, I think) 
 */
SECTIONS {
    INCLUDE text.ld
    INCLUDE zp.ld
    INCLUDE rodata.ld
    INCLUDE data.ld
    INCLUDE bss.ld
    INCLUDE noinit.ld
}


/* Set initial soft stack address to just above last ram address. (It grows down.) */
__stack = ORIGIN(ram) + LENGTH(ram);


/* Bare Binary */
OUTPUT_FORMAT {
    TRIM(ram)
}
