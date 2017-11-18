#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

PACK(
struct AuxilaryFunctionRecord
{
	uint32_t TagIndex;
	uint32_t TotalSize;
	uint32_t PointerToLinenumber;
	uint32_t PointerToNextFunction;
	uint16_t Unused;
});

PACK(struct AuxilaryBFEFRecord
{
	uint32_t Unused1;
	uint16_t Linenumber;
	uint8_t Unused2[6];
	uint32_t PointerToNextFunction; // bf only
	uint16_t Unused;
});

PACK(struct AuxilaryExternalRecord
{
	uint32_t TagIndex;
	uint32_t Characteristics;
	uint8_t Unused[10];
});

// source code files
PACK(struct AuxilaryFileRecord
{
	uint8_t FileName[18];
});

PACK(struct AuxilarySectionRecord
{
	uint32_t Length;
	uint16_t NumberOfRelocations;
	uint16_t NumberOfLinenumbers;
	uint32_t CheckSum;
	uint16_t Number;
	uint8_t Selection;
	uint8_t Unused[3];
});