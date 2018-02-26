#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

PACK(struct ResourceDirectoryTable
{
	uint32_t Characteristics; // zero
	uint32_t TimeDateStamp;
	uint16_t MajorVersion;
	uint16_t MinorVersion;
	uint16_t NumberOfNameEntries;
	uint16_t NumberOfIdEntries;
});

PACK(struct ResourceDirectoryEntry
{
	union
	{
		uint32_t NameRVA;
		uint32_t Id;
	};
	
	union
	{
		uint32_t DataEntryRVA;
		uint32_t SubdirectoryRVA;
	};
});

PACK(struct ResourceDirectoryString
{
	uint16_t Length;
	uint16_t* String;
});

PACK(struct ResourceDataEntry
{
	uint32_t DataRVA;
	uint32_t Size;
	uint32_t Codepage;
	uint32_t Reserved; // must 0
});
