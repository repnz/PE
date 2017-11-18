#pragma once
#include <PE.Parser/Headers/Directories/ExportTable.h>
#include <PE.Parser/PEParser.h>

struct ExportEntry
{
	std::string Name;
	uint32_t Address;
	uint16_t Ordinal;
};

class ExportDirectoryParser
{
private:
	PEParser& _peParser;

	void LoadEntries();

	bool LoadExportDirectoryTable();

	void LoadAddressTable(uint32_t* exportAddresses);

	void LoadNamePointerTable(uint32_t* exportNames);

	void LoadOrdinalTable(uint16_t* exportNames);

	ExportDirectoryTable exportTable;
	
	std::vector<ExportEntry> _entries;

public:
	explicit ExportDirectoryParser(PEParser& peParser);

	bool Load();

	const ExportDirectoryTable& GetExportDirectoryTable() const;

	const std::vector<ExportEntry>& GetEntries() const;
	
};
