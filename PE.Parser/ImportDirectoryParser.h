#pragma once
#include <PE.Parser/PEParser.h>
#include <PE.Parser/Headers/Directories/ImportDirectory.h>

#include <memory>

class ImportedFunction
{
public:
	std::string name;
	uint32_t ordinal;
	uint16_t hint;

	ImportedFunction() : name(""), ordinal(0), hint(0){}

	ImportedFunction(const std::string& name, const uint16_t hint) : name(name), ordinal(-1), hint(hint)
	{
	}

	ImportedFunction(const uint32_t ordinal) : name(""), ordinal(ordinal), hint(0)
	{
	}

	bool IsOrdinal() const
	{
		return name.length() == 0;
	}
};

class ParsedImportDescriptor
{
public:
	std::string dllName;
	std::vector<ImportedFunction> functions;
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
