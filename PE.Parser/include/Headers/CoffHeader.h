#pragma once
#include <cstdint>
#include <Pack.h>
#include <Headers/MachineType.h>
#include <Headers/ImageCharacteristics.h>

namespace Headers
{
	PACK(struct COFFHeader
	{
		MachineType Machine;
		uint16_t NumberOfSections;
		uint32_t TimeDateStamp;
		uint32_t PointerToSymbolTable;
		uint32_t NumberOfSymbols;
		uint16_t SizeOfOptionalHeader;
		ImageCharacteristic Characteristics;
	});

}
