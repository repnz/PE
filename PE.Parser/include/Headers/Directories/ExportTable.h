#pragma once
#include <cstdint>
#include <Pack.h>

PACK(struct ExportDirectoryTable
{
	uint32_t ExportFlags;
	uint32_t TimeDateStamp;
	uint16_t MajorVersion;
	uint16_t MinorVersion;
	uint32_t Name;
	uint32_t OrdinalBase;
	uint32_t AddressTableEntries;
	uint32_t NumberOfNamePointers;
	uint32_t ExportAddressTable;
	uint32_t ExportNamePointerTable;
	uint32_t OrdinalTableAddress;
});

PACK(struct ExportAddressTable
{
	uint32_t ExportAddress;
	uint32_t ForwarderAddress;

});