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
	uint32_t IdNameUnion;
	uint32_t DataEntrySubdirectoryUnion;

	bool IsSubdirectory() const { return DataEntrySubdirectoryUnion & 0x80000000; }
	bool HasName() const { return  IdNameUnion & 0x80000000; }

	uint32_t NameOffset() const { return IdNameUnion ^ 0x80000000; }
	uint32_t IdOffset() const { return IdNameUnion; }

	uint32_t DataEntryOffset() const { return DataEntrySubdirectoryUnion; }
	uint32_t SubdirectoryOffset() const { return DataEntrySubdirectoryUnion ^ 0x80000000; }
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
