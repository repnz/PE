#pragma once
#include <memory>
#include <PE.Parser/PEParser.h>
#include "Headers/Directories/Resource.h"

struct ResourceTable;

struct ResourceEntry
{
	ResourceTable* SubTable;

};

struct ResourceTable
{
	ResourceDirectoryTable table;
	std::vector<ResourceEntry> entries;
};


class ResourceDirectoryParser
{
private:
	class Impl;
	std::unique_ptr<Impl> _impl;
public:
	explicit ResourceDirectoryParser(PEParser& peParser);
	void Load();
	~ResourceDirectoryParser();
};

