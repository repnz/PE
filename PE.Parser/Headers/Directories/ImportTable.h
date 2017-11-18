#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

PACK(struct ImportDirectoryTable
{
	uint32_t ImportLookupTable;
	uint32_t TimeDateStamp;
	uint32_t ForwarderChain;
	uint32_t Name;
	uint32_t ImportAddressTable;
});

PACK(struct ImportLookupTableEntry32
{
	uint32_t Value;

	bool IsOrdinal() const { return Value & 0x80000000; }

	uint32_t OrdinalNumber() const { return Value & 0x7FFFFFFF; }
	uint32_t HintNameTableRVA() const { return Value & 0x7FFFFFFF; }
});

PACK(struct ImportLookupTableEntry64
{
	uint64_t Value;

	bool IsOrdinal() const { return Value & 0x8000000000000000; }

	uint64_t OrdinalNumber() const { return Value & 0x7FFFFFFFFFFFFFFF; }
	uint64_t HintNameTableRVA() const { return Value & 0x7FFFFFFFFFFFFFFF; }
});