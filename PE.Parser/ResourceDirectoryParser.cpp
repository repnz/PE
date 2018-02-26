#include <PE.Parser/ResourceDirectoryParser.h>
#include <PE.Parser/ExportDirectoryParser.h>
#include <PE.Parser/Headers/DirectoryOffset.h>

using Headers::DataDirectory;

class ResourceDirectoryParser::Impl
{
private:
	PEParser& _peParser;
	const Headers::SectionHeader* _resourceSection;
	ParsedResourceTable _rootTable;
public:
	explicit Impl(PEParser& parser);
	void LoadResourceEntryName(StreamParser& parser, ParsedResourceEntry* entry);
	void LoadDataEntry(StreamParser& parser, ParsedResourceEntry* entry);
	void ParseResourceEntry(const uint32_t level, StreamParser& parser, ParsedResourceEntry* entry);
	void Load();
	void ParseResourceTable(ParsedResourceTable* table, const uint32_t filePointer, const uint32_t level);
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

void ResourceDirectoryParser::Impl::LoadResourceEntryName(StreamParser& parser, ParsedResourceEntry* entry)
{
	const uint32_t nameFilePointer =
		_resourceSection->PointerToRawData + entry->RawEntry.NameOffset();

	parser.ReadFrom<uint16_t>(&entry->Name.Length, nameFilePointer);
			
	// align size to word alignment 
	if (entry->Name.Length % 2 == 1) { entry->Name.Length++; }

	// Allocate entry, delete it eventually
	entry->Name.String = new uint16_t[entry->Name.Length];

	parser.Read(entry->Name.String, entry->Name.Length);
}

void ResourceDirectoryParser::Impl::LoadDataEntry(StreamParser& parser, ParsedResourceEntry* entry)
{
	// Load Data Entry Sturcture
	
	const uint32_t dataEntryFilePointer =
		_resourceSection->PointerToRawData + entry->RawEntry.DataEntryOffset();

	parser.ReadFrom<ResourceDataEntry>(&entry->DataEntry, dataEntryFilePointer);
	
	// Load Actual Resource Data

	const uint32_t dataFilePointer =
		_resourceSection->GetFilePointer(entry->DataEntry.DataRVA);
			
	// Allocation of new buffer (find way to delete it)
	entry->Data = new uint8_t[entry->DataEntry.Size];

	parser.Read(entry->Data, dataFilePointer, entry->DataEntry.Size);
}

void ResourceDirectoryParser::Impl::ParseResourceEntry(const uint32_t level, StreamParser& parser, ParsedResourceEntry* entry)
{
	if (entry->HasName()) // if has a name, parse the name
	{
		LoadResourceEntryName(parser, entry);
	}

	if (entry->IsSubdirectory())
	{
		// handle subdirectory data

		const uint32_t subdirectoryPointer =
			_resourceSection->PointerToRawData + entry->RawEntry.SubdirectoryOffset();

		// recursive call to LoadResourceTable
		ParseResourceTable(&entry->SubDirectory, subdirectoryPointer, level+1);
	}
	else
	{
		// get data entry 
		LoadDataEntry(parser, entry);
	}
}

void ResourceDirectoryParser::Impl::ParseResourceTable(ParsedResourceTable* table, const uint32_t filePointer, const uint32_t level)
{
	StreamParser& parser = _peParser.GetStreamParser();

	parser.ReadFrom(&table->RawTable, filePointer);

	table->Level = level;
	
	const uint32_t numberOfEntries = table->RawTable.NumberOfNameEntries + table->RawTable.NumberOfIdEntries;

	table->Entries.resize(numberOfEntries);
	
	// Read Raw Resource Entries

	for (uint32_t i=0; i<numberOfEntries; ++i)
	{
		parser.Read<ResourceDirectoryEntry>(&table->Entries[i].RawEntry);
	}

	// Parse Resource Entries

	for (uint32_t i=0; i<numberOfEntries; ++i)
	{		
		ParseResourceEntry(level, parser, &table->Entries[i]);
	}
}

void ResourceDirectoryParser::Impl::Load()
{
	const DataDirectory& resourceDir = _peParser.GetDirectory(Headers::DirectoryOffsets::Resource);
	_resourceSection = &_peParser.GetMatchSection(resourceDir.RVA);
	
	ParseResourceTable(&_rootTable, _resourceSection->PointerToRawData, 0);
}
