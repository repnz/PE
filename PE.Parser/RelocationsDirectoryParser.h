#pragma once
#include <PE.Parser/PEParser.h>
#include <PE.Parser/Headers/Directories/Relocations.h>
#include <memory>

struct ParsedRelocationChunk
{
	uint32_t VirtualAddress;
	std::vector<Relocation> Relocations;
};

class RelocationsDirectoryParser
{
private:
	class Impl;
	std::unique_ptr<Impl> _impl;
public:
	RelocationsDirectoryParser(PEParser& peParser);

	void Load();

	const std::vector<ParsedRelocationChunk>& GetRelocationChunks() const;

	~RelocationsDirectoryParser();
};
