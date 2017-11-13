#pragma once
#include <cstdint>
#include <Pack.h>

PACK(struct FixupBlock
{
	uint32_t PageRVA;
	uint32_t BlockSize;
});

PACK(struct TypeOffsetEntry
{
	uint16_t TypeOffsetValue;

	uint8_t Type() const { return ((TypeOffsetValue >> 8) & 0xE); }
	uint16_t Offset() const { return TypeOffsetValue & 0xEFF; }

});