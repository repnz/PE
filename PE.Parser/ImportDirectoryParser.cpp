#include <PE.Parser/ImportDirectoryParser.h>
#include <PE.Parser/Headers/Directories/ImportDirectory.h>
#include <PE.Parser/Headers/DirectoryOffset.h>

using namespace Headers;

class ImportDirectoryParser::Impl
{
private:
	void LoadImportDescriptors(const uint32_t rva);
public:
	PEParser& _parser;
	StreamParser& streamParser;
	std::vector<ParsedImportDescriptor> _parsedDescriptors;
	std::vector<ImportDescriptor> _descriptors;
	const SectionHeader* _importSection;
	explicit Impl(PEParser& parser);

	void ParseImportDescriptors();
	ImportedFunction ParseImportThunk(ImportThunk thunk);
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

const std::vector<ImportDescriptor>& ImportDirectoryParser::GetImportDescriptors() const
{
	return _impl->_descriptors;
}

const std::vector<ParsedImportDescriptor>& ImportDirectoryParser::GetParsedImportDescriptors() const
{
	return _impl->_parsedDescriptors;
}


ImportDirectoryParser::~ImportDirectoryParser() = default;

ImportDirectoryParser::Impl::Impl(PEParser& parser) : _parser(parser), _importSection(nullptr), streamParser(parser.GetStreamParser())
{
}

ImportedFunction ImportDirectoryParser::Impl::ParseImportThunk(ImportThunk thunk)
{
	const uint32_t val = thunk.ActualValue();

	if (thunk.IsOrdinal())
	{
		// import by ordinal
		return ImportedFunction(val);
	}

	// import by name
	const uint32_t importByNamePtr = _importSection->GetFilePointer(val);
	const uint16_t hint = streamParser.Read<uint16_t>(importByNamePtr);
	const std::string functionName = streamParser.ReadString();
	return ImportedFunction(functionName, hint);
}

void ImportDirectoryParser::Impl::ParseImportDescriptors()
{
	StreamParser& streamParser = _parser.GetStreamParser();

	_parsedDescriptors.resize(_descriptors.size()-1);

	for (size_t i = 0; i < _parsedDescriptors.size(); ++i)
	{
		ParsedImportDescriptor& parsedDescriptor = _parsedDescriptors[i];
		ImportDescriptor& descriptor = _descriptors[i];

		const uint32_t fp = _importSection->GetFilePointer(descriptor.NameRVA);
		parsedDescriptor.dllName = streamParser.ReadString(fp);
		
		std::vector<ImportThunk> thunks;
		streamParser.Seek(_importSection->GetFilePointer(descriptor.OriginalFirstThunk));
		streamParser.ReadNullTerminatedVector(thunks);

		const uint32_t functionsSize = thunks.size() - 1;
		parsedDescriptor.functions.resize(functionsSize);

		for (size_t j=0; j<functionsSize; ++j)
		{
			parsedDescriptor.functions[j] = ParseImportThunk(thunks[j]);
		}
	}
}

void ImportDirectoryParser::Impl::LoadImportDescriptors(const uint32_t startRva)
{	
	streamParser.Seek(_importSection->GetFilePointer(startRva));

	const DataDirectory& importDir = _parser.GetDirectory(DirectoryOffsets::Import);

	_descriptors.resize(importDir.Size / sizeof(ImportDescriptor));

	for (size_t i=0; i<_descriptors.size(); ++i)
	{
		// initialize import descriptor
		streamParser.Read<ImportDescriptor>(&_descriptors[i]);

		if (_descriptors[i].IsNullDescriptor() && i != (_descriptors.size() - 1))
		{
			// warning
			break;
		}
	}
}

bool ImportDirectoryParser::Impl::Load()
{
	const DataDirectory& dir = _parser.GetDirectory(DirectoryOffsets::Import);

	_importSection = &_parser.GetMatchSection(dir.RVA);

	if (_importSection == nullptr) { return false; }
	
	LoadImportDescriptors(dir.RVA);

	ParseImportDescriptors();

	return true;
}