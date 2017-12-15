#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

PACK(struct ImportDescriptor
{
	union
	{
		uint32_t Characteristics;
		uint32_t OriginalFirstThunk;
	};
	
	uint32_t TimeDateStamp;
	uint32_t ForwarderChain;
	uint32_t NameRVA;
	uint32_t FirstThunk;

	bool IsNullDescriptor()
	{
		return NameRVA == 0;
	}
});

PACK(struct ImportThunk32
{
	uint32_t Value;

	bool IsOrdinal() const { return Value & 0x80000000; }

	uint32_t ActualValue() const { return Value & 0x7FFFFFFF; }
});

PACK(struct ImportThunk64
{
	uint64_t Value;

	bool IsOrdinal() const { return Value & 0x8000000000000000; }

	uint64_t ActualValue() const { return Value & 0x7FFFFFFFFFFFFFFF; }
});

#ifdef PE32
#define ImportThunk ImportThunk32
#else
#define ImportThunk ImportThunk64
#endif