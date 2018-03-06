#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

enum class DebugEntryType
{
	Unknown = 0,
	Coff = 1, 
	CodeView = 2,
	FPO = 3, // frame pointer omission information
	Misc = 4,
	Exception = 5,
	FixUp = 6,
	OMapToSource= 7,
	OMapFromSource = 8,
	Borland = 9,
	Reserved10 = 10,
	Clsid = 11,
	Repro = 16

};

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

PACK(struct FPO_DATA
{
	uint32_t StartOffset;
	uint32_t FunctionSize;
	uint32_t LocalVarBytes;
	uint16_t ParametersBytes;
	uint16_t PrologBytes : 8;
	uint16_t RegsSaved : 3;
	uint16_t HasSEH : 1;
	uint16_t UseBP : 1;
	uint16_t Reserved : 1;
	uint16_t FrameType : 2;
});