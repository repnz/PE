#pragma once
#include <memory>
#include <PE.Parser/PEParser.h>
#include "Headers/Directories/Debug.h"

class DebugDirectoryParser
{
private:
	class Impl;
	std::unique_ptr<Impl> _impl;
public:
	explicit DebugDirectoryParser(PEParser& peParser);
	void Load();
	const std::vector<DebugDirectoryEntry>& GetDebugEntries() const;
	~DebugDirectoryParser();
};

