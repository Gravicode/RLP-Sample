/**************************************/
/* Copyright (c) GHI Electronics, LLC */
/**************************************/

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY
{
	SDRAM (wx) : ORIGIN = 0xA0F00000, LENGTH = 0x000FFFFC
}

SECTIONS
{
		. = ALIGN(4);
		.text : 
		{ 
			*(.text)
		}
		
		. = ALIGN(4);
		.rodata : 
		{ 
		*(.rodata )
		}
		
		. = ALIGN(4);
		.data : 
		{ 
			*(.data)
		}
		
		. = ALIGN(4);
		.bss : 
		{
			__bss_start__ = .;
			*(.bss)
			__bss_end__ = .;
		}   
}

end = .;
