#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>
#include <PE.Parser/Headers/SectionCharacteristics.h>

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

		bool IsInSection(const uint32_t address) const
		{
			return address >= VirtualAddress && address < (VirtualAddress + SizeOfRawData);
		}

		uint32_t GetFilePointer(const uint32_t rva) const
		{
			return rva - VirtualAddress + PointerToRawData;
		}
	});
}
