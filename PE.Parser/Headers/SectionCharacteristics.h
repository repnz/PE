#pragma once
#include <cstdint>


namespace Headers
{
	typedef uint32_t  SectionCharacteristic;

	namespace SectionCharacteristics
	{
		const SectionCharacteristic TYPE_NO_PAD = 0x00000008;  // Reserved.
		const SectionCharacteristic TYPE_COPY = 0x00000010;  // Reserved.

		const SectionCharacteristic CNT_CODE = 0x00000020;  // Section contains code.
		const SectionCharacteristic CNT_INITIALIZED_DATA = 0x00000040;  // Section contains initialized data.
		const SectionCharacteristic CNT_UNINITIALIZED_DATA = 0x00000080;  // Section contains uninitialized data.
		
		const SectionCharacteristic LNK_OTHER = 0x00000100;  // Reserved.
		const SectionCharacteristic LNK_INFO = 0x00000200;  // Section contains comments or some other type of information.
		const SectionCharacteristic TYPE_OVER = 0x00000400;  // Reserved.
		const SectionCharacteristic LNK_REMOVE = 0x00000800;  // Section contents will not become part of image.
		const SectionCharacteristic LNK_COMDAT = 0x00001000;  // Section contents comdat.

		const SectionCharacteristic MEM_PROTECTED = 0x00004000; // Obsolete
		const SectionCharacteristic NO_DEFER_SPEC_EXC = 0x00004000;  // Reset speculative exceptions handling bits in the TLB entries for this section.
		const SectionCharacteristic GPREL = 0x00008000;  // Section content can be accessed relative to GP
		const SectionCharacteristic MEM_FARDATA = 0x00008000;
		const SectionCharacteristic MEM_SYSHEAP = 0x00010000; //Obsolete 
		const SectionCharacteristic MEM_PURGEABLE = 0x00020000;
		const SectionCharacteristic MEM_16BIT = 0x00020000;
		const SectionCharacteristic MEM_LOCKED = 0x00040000;
		const SectionCharacteristic MEM_PRELOAD = 0x00080000;

		const SectionCharacteristic ALIGN_1BYTES = 0x00100000;  //
		const SectionCharacteristic ALIGN_2BYTES = 0x00200000;  //
		const SectionCharacteristic ALIGN_4BYTES = 0x00300000;  //
		const SectionCharacteristic ALIGN_8BYTES = 0x00400000;  //
		const SectionCharacteristic ALIGN_16BYTES = 0x00500000;  // Default alignment if no others are specified.
		const SectionCharacteristic ALIGN_32BYTES = 0x00600000;  //
		const SectionCharacteristic ALIGN_64BYTES = 0x00700000;  //
		const SectionCharacteristic ALIGN_128BYTES = 0x00800000;  //
		const SectionCharacteristic ALIGN_256BYTES = 0x00900000;  //
		const SectionCharacteristic ALIGN_512BYTES = 0x00A00000;  //
		const SectionCharacteristic ALIGN_1024BYTES = 0x00B00000;  //
		const SectionCharacteristic ALIGN_2048BYTES = 0x00C00000;  //
		const SectionCharacteristic ALIGN_4096BYTES = 0x00D00000;  //
		const SectionCharacteristic ALIGN_8192BYTES = 0x00E00000;  //
		const SectionCharacteristic ALIGN_MASK = 0x00F00000;

		const SectionCharacteristic LNK_NRELOC_OVFL = 0x01000000;  // Section contains extended relocations.
		const SectionCharacteristic MEM_DISCARDABLE = 0x02000000;  // Section can be discarded.
		const SectionCharacteristic MEM_NOT_CACHED = 0x04000000;  // Section is not cachable.
		const SectionCharacteristic MEM_NOT_PAGED = 0x08000000;  // Section is not pageable.
		const SectionCharacteristic MEM_SHARED = 0x10000000;  // Section is shareable.
		const SectionCharacteristic MEM_EXECUTE = 0x20000000;  // Section is executable.
		const SectionCharacteristic MEM_READ = 0x40000000;  // Section is readable.
		const SectionCharacteristic MEM_WRITE = 0x80000000;  // Section is writeable.

	}
}
