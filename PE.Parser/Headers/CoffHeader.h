#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>
#include <PE.Parser/Headers/MachineType.h>
#include <PE.Parser/Headers/ImageCharacteristics.h>

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
