#pragma once
#include <PE.Parser/Headers/Directories/ExportTable.h>
#include <PE.Parser/PEParser.h>

struct ExportEntry
{
	std::string Name;
	uint32_t Address;
	uint16_t Ordinal;
	std::string ForwardedSymbol;

	bool IsForward() const
	{
		return ForwardedSymbol.length() > 0;
	}
};

class ExportDirectoryParser
{
private:
	class Impl;
	std::unique_ptr<Impl> _impl;
public:
	explicit ExportDirectoryParser(PEParser& peParser);

	bool Load();

	const ExportDirectoryTable& GetExportDirectoryTable() const;

	const std::vector<ExportEntry>& GetEntries() const;

	~ExportDirectoryParser();
};
