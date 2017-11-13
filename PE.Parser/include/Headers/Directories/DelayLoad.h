#pragma once
#include <cstdint>
#include <Pack.h>

PACK(struct DelayLoadDirectoryTable
{
	uint32_t Attributes; // zero
	uint32_t Name;
	uint32_t ModuleHandle;
	uint32_t DelayImportAddressTable;
	uint32_t DelayImportNameTable;
	uint32_t BoundDelayImportTable;
	uint32_t LoadDelayImportTable;
	uint32_t TimeStamp;
});