#include <PE.Parser/ResourceDirectoryParser.h>
#include <PE.Parser/ExportDirectoryParser.h>
#include <PE.Parser/Headers/DirectoryOffset.h>

using Headers::DataDirectory;

class ResourceDirectoryParser::Impl
{
private:
	PEParser& _peParser;
	const Headers::SectionHeader* _resourceSection;
	ResourceTable _rootTable;
public:
	explicit Impl(PEParser& parser);
	void Load();
	void LoadResourceTable(ResourceTable& table, const uint32_t filePointer);
};

ResourceDirectoryParser::ResourceDirectoryParser(PEParser& parser) : _impl(std::make_unique<Impl>(parser))
{
}

void ResourceDirectoryParser::Load()
{
	_impl->Load();
}


ResourceDirectoryParser::~ResourceDirectoryParser() = default;


ResourceDirectoryParser::Impl::Impl(PEParser& parser) : _peParser(parser), _resourceSection(nullptr)
{
}

void ResourceDirectoryParser::Impl::LoadResourceTable(ResourceTable& table, const uint32_t filePointer)
{
	_peParser.GetStreamParser().ReadFrom(&table.table, filePointer);
	const uint32_t numberOfEntries = table.table.NumberOfNameEntries + table.table.NumberOfIdEntries;
	
	_rootTable.entries.resize(numberOfEntries);
	
	for (uint32_t i = 0; i<numberOfEntries; ++i)
	{
		_peParser.GetStreamParser().Read(&table.entries[i]);
	}
}

void ResourceDirectoryParser::Impl::Load()
{
	const DataDirectory& resourceDir = _peParser.GetDirectory(Headers::DirectoryOffsets::Resource);
	_resourceSection = &_peParser.GetMatchSection(resourceDir.RVA);
	
	LoadResourceTable(_rootTable, _resourceSection->PointerToRawData);
}
