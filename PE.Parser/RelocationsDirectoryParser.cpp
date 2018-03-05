#include <PE.Parser/RelocationsDirectoryParser.h>
#include <PE.Parser/Headers/DirectoryOffset.h>

using namespace Headers;

class RelocationsDirectoryParser::Impl
{
private:
	PEParser & _peParser;
	StreamParser& _streamParser;
	const SectionHeader* _relocSection;
	std::vector<ParsedRelocationChunk> _chunks;
	void ReadChunks();
public:
	explicit Impl(PEParser& peParser);
	bool ReadRelocationChunk(ParsedRelocationChunk* parsedChunk);
	void Load();
	const std::vector<ParsedRelocationChunk>& GetRelocationChunks() const;
};

RelocationsDirectoryParser::RelocationsDirectoryParser(PEParser & peParser):
	_impl(std::make_unique<Impl>(peParser))
{
}

void RelocationsDirectoryParser::Load()
{
	_impl->Load();
}

const std::vector<ParsedRelocationChunk>& RelocationsDirectoryParser::GetRelocationChunks() const
{
	return _impl->GetRelocationChunks();
}

RelocationsDirectoryParser::Impl::Impl(PEParser& peParser) : 
_peParser(peParser), _streamParser(peParser.GetStreamParser())
{
}

bool RelocationsDirectoryParser::Impl::ReadRelocationChunk(ParsedRelocationChunk* parsedChunk)
{
	BaseRelocationChunk rawChunk;
	
	_streamParser.Read<BaseRelocationChunk>(&rawChunk);

	if (rawChunk.VirtualAddress == 0) { return false; }
	
	parsedChunk->VirtualAddress = rawChunk.VirtualAddress;
	parsedChunk->Relocations.resize(rawChunk.GetNumberOfRelocations());

	_streamParser.ReadVector<Relocation>(parsedChunk->Relocations);
	
	return true;
}

void RelocationsDirectoryParser::Impl::ReadChunks()
{
	for (uint32_t i = 0;;++i)
	{
		// allocate the chunk
		_chunks.resize(i + 1);
		ParsedRelocationChunk* currentChunk = &_chunks[i];
		
		// if it is the last chunk, break
		if (!ReadRelocationChunk(currentChunk)) { break; }
	} 
}

void RelocationsDirectoryParser::Impl::Load()
{
	const DataDirectory& relocDir = 
		_peParser.GetDirectory(Headers::DirectoryOffsets::BaseReloc);

	_relocSection = &_peParser.GetMatchSection(relocDir.RVA);

	if (_relocSection == nullptr) { throw std::exception(); }

	const uint32_t chunksFilePointer = _relocSection->GetFilePointer(relocDir.RVA);

	_streamParser.Seek(chunksFilePointer);

	ReadChunks();
}

const std::vector<ParsedRelocationChunk>& RelocationsDirectoryParser::Impl::GetRelocationChunks() const
{
	return _chunks;
}

RelocationsDirectoryParser::~RelocationsDirectoryParser() = default;
