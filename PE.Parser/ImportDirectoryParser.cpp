#include <PE.Parser/ImportDirectoryParser.h>
#include "Headers/Directories/ImportTable.h"
#include "Headers/DirectoryOffset.h"

using namespace Headers;

class ImportDirectoryParser::Impl
{
public:
	PEParser& _parser;
	ImportDirectoryTable _importTable;
	const SectionHeader* _importSection;

	Impl(PEParser& parser);
	bool Load();
};

ImportDirectoryParser::ImportDirectoryParser(PEParser& parser)
	: _impl(std::make_unique<Impl>(parser))
{
}

bool ImportDirectoryParser::Load()
{
	return _impl->Load();
}


const ImportDirectoryTable& ImportDirectoryParser::GetImportTable() const
{
	return _impl->_importTable;
}

ImportDirectoryParser::~ImportDirectoryParser() = default;

ImportDirectoryParser::Impl::Impl(PEParser& parser) : _parser(parser), _importSection(nullptr)
{
}

bool ImportDirectoryParser::Impl::Load()
{
	_importSection = _parser.ReadDirectoryTable<ImportDirectoryTable>(&_importTable, DirectoryOffsets::Import);

	return _importSection != nullptr;
}



