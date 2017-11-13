#pragma once
#include <cstdint>
#include <Pack.h>

template <typename PointerSize>
PACK(struct TLSDirectory
{
	PointerSize RawDataStart;
	PointerSize RawDataEnd;
	PointerSize AddressOfIndex;
	PointerSize AddressOfCallbacks;
	uint32_t SizeOfZeroFills;
	uint32_t Characteristics; // Reserved
});
