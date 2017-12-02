#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

PACK(struct ImportDescriptor
{
	uint32_t ImportLookupTableRVA;
	uint32_t TimeDateStamp;
	uint32_t ForwarderChain;
	uint32_t NameRVA;
	uint32_t ImportAddressTableRVA;

	bool IsNullDescriptor()
	{
		return ImportLookupTableRVA == 0;
	}
});

PACK(struct ImportLookupTableEntry32
{
	uint32_t Value;

	bool IsOrdinal() const { return Value & 0x80000000; }

	uint32_t ActualValue() const { return Value & 0x7FFFFFFF; }
});

PACK(struct ImportLookupTableEntry64
{
	uint64_t Value;

	bool IsOrdinal() const { return Value & 0x8000000000000000; }

	uint64_t ActualValue() const { return Value & 0x7FFFFFFFFFFFFFFF; }
});