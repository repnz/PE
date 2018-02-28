#pragma once
#include <memory>
#include <PE.Parser/PEParser.h>
#include <PE.Parser/Headers/Directories/Resource.h>

struct ParsedResourceEntry;

namespace ResourceDirectoryLevel
{
	const uint32_t Type		= 0x00;
	const uint32_t Name		= 0x01;
	const uint32_t Language = 0x02;
}


struct ParsedResourceTable
{
	uint32_t Level;
	ResourceDirectoryTable RawTable;
	std::vector<ParsedResourceEntry> Entries;	
};


struct ParsedResourceEntry
{
	ResourceDirectoryEntry RawEntry;
	ResourceDataEntry DataEntry;
	std::unique_ptr<uint8_t> Data;
	ParsedResourceTable SubDirectory;
	ResourceDirectoryString Name;

	bool IsSubdirectory() { return RawEntry.IsSubdirectory(); }
	bool HasName() { return RawEntry.HasName(); }
};


class ResourceDirectoryParser
{
private:
	class Impl;
	std::unique_ptr<Impl> _impl;
public:
	explicit ResourceDirectoryParser(PEParser& peParser);
	bool Load();
	const ParsedResourceTable& GetRootTable() const;
	~ResourceDirectoryParser();
};

