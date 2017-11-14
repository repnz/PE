#pragma once
#include <cstdint>
#include <Pack.h>
#include <Headers/SectionCharacteristics.h>

namespace Headers
{
	PACK(struct SectionHeader
	{
		uint8_t Name[8];
		union
		{
			uint32_t PhysicalAddress;
			uint32_t VirtualSize;
		} Misc;
		uint32_t VirtualAddress;
		uint32_t SizeOfRawData;
		uint32_t PointerToRawData;
		uint32_t PointerToRelocations;
		uint32_t PointerToLinenumbers;
		uint16_t NumberOfRelocations;
		uint16_t NumberOfLinenumbers;
		SectionCharacteristic Characteristics;
	});
}
