#pragma once
#include <memory>
#include <PE.Parser/PEParser.h>
#include "Headers/Directories/ImportTable.h"

class ImportDirectoryParser
{
	
private:
	class Impl;
	std::unique_ptr<Impl> _impl;
public:
	explicit ImportDirectoryParser(PEParser& parser);

	bool Load();

	const ImportDirectoryTable& GetImportTable() const;

	~ImportDirectoryParser();

};
