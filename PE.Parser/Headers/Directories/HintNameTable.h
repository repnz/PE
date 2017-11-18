#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

PACK(struct HintNameTableEntry
{
	uint16_t Hint; // index into Export Name Pointer Table
	uint8_t* Name;
});
