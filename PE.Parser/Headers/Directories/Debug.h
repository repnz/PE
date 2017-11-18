#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

PACK(struct DebugDirectoryEntry
{
	uint32_t Characteristics; // zero
	uint32_t TimeDateStamp;
	uint16_t MajorVersion;
	uint16_t MinorVersion;
	uint32_t Type;
	uint32_t SizeOfData;
	uint32_t AddressOfRawData;
	uint32_t PointerToRawData;
});
