#include <PE.Parser/DebugDirectoryParser.h>
#include <PE.Parser/Headers/Directories/Debug.h>
#include <PE.Parser/Headers/DirectoryOffset.h>

class DebugDirectoryParser::Impl
{
private:
	PEParser& _peParser;
	StreamParser& _streamParser;
	std::vector<DebugDirectoryEntry> _entries;
public:
	explicit Impl(PEParser& peParser);
	const std::vector<DebugDirectoryEntry>& GetDebugEntries() const;
	void Load();

};

DebugDirectoryParser::DebugDirectoryParser(PEParser & peParser):
	_impl(std::make_unique<Impl>(peParser))
{
}

void DebugDirectoryParser::Load()
{
	_impl->Load();
}

const std::vector<DebugDirectoryEntry>& DebugDirectoryParser::GetDebugEntries() const
{
	return _impl->GetDebugEntries();
}

DebugDirectoryParser::Impl::Impl(PEParser& peParser) : 
_peParser(peParser),
_streamParser(peParser.GetStreamParser())
{
}

const std::vector<DebugDirectoryEntry>& DebugDirectoryParser::Impl::GetDebugEntries() const
{
	return _entries;
}

void DebugDirectoryParser::Impl::Load()
{
	const Headers::DataDirectory& debugDirectory = 
		_peParser.GetDirectory(Headers::DirectoryOffsets::Debug);

	const uint32_t numberOfEntries = debugDirectory.Size / sizeof(DebugDirectoryEntry);

	_entries.resize(numberOfEntries);

	const uint32_t debugEntriesFilePointer = 
		_peParser.GetMatchSection(debugDirectory.RVA).GetFilePointer(debugDirectory.RVA);
	
	_streamParser.Seek(debugEntriesFilePointer);

	for (int i=0; i<numberOfEntries; ++i)
	{
		_streamParser.Read<DebugDirectoryEntry>(&_entries[i]);
	}
}


DebugDirectoryParser::~DebugDirectoryParser() = default;
