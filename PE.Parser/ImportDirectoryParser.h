#pragma once
#include <PE.Parser/PEParser.h>
#include <PE.Parser/Headers/Directories/ImportDirectory.h>

#include <memory>

class ParsedImportDescriptor
{
public:
	std::string dllName;
};

class ImportDirectoryParser
{
	
private:
	class Impl;
	std::unique_ptr<Impl> _impl;
public:
	explicit ImportDirectoryParser(PEParser& parser);

	bool Load();

	const std::vector<ImportDescriptor>& GetImportDescriptors() const;

	const std::vector<ParsedImportDescriptor>& GetParsedImportDescriptors() const;

	~ImportDirectoryParser();

};
