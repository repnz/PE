#include <PE.Parser/ExportDirectoryParser.h>
#include <PE.Parser/Headers/DirectoryOffset.h>
#include <PE.Parser/Headers/Directories/ExportTable.h>

class ExportDirectoryParser::Impl
{
public:
	PEParser& _peParser;

	const Headers::SectionHeader* _exportSection;

	ExportDirectoryTable _exportTable;

	std::vector<ExportEntry> _entries;

	explicit Impl(PEParser& parser);

	bool Load();

	void LoadEntries();

	bool LoadExportDirectoryTable();

	void LoadAddressTable(uint32_t* exportAddresses);

	void LoadNamePointerTable(uint32_t* exportNames);

	void LoadOrdinalTable(uint16_t* exportNames);

};

ExportDirectoryParser::ExportDirectoryParser(PEParser& peParser) :
_impl(std::make_unique<Impl>(peParser))
{
}

const ExportDirectoryTable& ExportDirectoryParser::GetExportDirectoryTable() const
{
	return _impl->_exportTable;
}

const std::vector<ExportEntry>& ExportDirectoryParser::GetEntries() const
{
	return _impl->_entries;
}

ExportDirectoryParser::~ExportDirectoryParser() = default;


bool ExportDirectoryParser::Load()
{
	return _impl->Load();
}


ExportDirectoryParser::Impl::Impl(PEParser& parser) : _peParser(parser), _exportSection(nullptr)
{
}

bool ExportDirectoryParser::Impl::Load()
{
	if (!LoadExportDirectoryTable())
	{
		return false;
	}

	LoadEntries();
	return true;
}

bool ExportDirectoryParser::Impl::LoadExportDirectoryTable()
{
	const Headers::DataDirectory& exportDir = 
		_peParser.GetDataDirectories().at(Headers::DirectoryOffsets::Export);

	if (exportDir.RVA == 0 && exportDir.Size == 0)
	{
		return false;
	}

	_exportSection = &_peParser.GetMatchSection(exportDir.RVA);

	const uint32_t filePointer = _exportSection->GetFilePointer(exportDir.RVA);

	_peParser.GetStreamParser().ReadFrom<ExportDirectoryTable>(
		&_exportTable,
		filePointer
		);

	return true;
}


void ExportDirectoryParser::Impl::LoadEntries()
{
	std::vector<uint32_t> addresses(_exportTable.AddressTableEntries);
	std::vector<uint32_t> namePointers(_exportTable.NumberOfNamePointers);
	std::vector<uint16_t> ordinals(_exportTable.NumberOfNamePointers);

	LoadAddressTable(addresses.data());
	LoadNamePointerTable(namePointers.data());
	LoadOrdinalTable(ordinals.data());
	
	_entries.resize(_exportTable.NumberOfNamePointers);

	for (uint32_t i=0; i<_exportTable.NumberOfNamePointers; ++i)
	{
		_entries[i].Name = _peParser.ReadStringFromRVA(namePointers[i]);
		_entries[i].Ordinal = ordinals[i];
		_entries[i].Address = addresses[ordinals[i] - _exportTable.OrdinalBase + 1];

		// Forwarded Symbol ->
		if (_exportSection->IsInSection(_entries[i].Address))
		{
			const uint32_t symbolNameFilePointer = 
				_exportSection->GetFilePointer(_entries[i].Address);

			_entries[i].ForwardedSymbol = 
				_peParser.GetStreamParser().ReadString(symbolNameFilePointer);
		}
	}
}

void ExportDirectoryParser::Impl::LoadAddressTable(uint32_t* addresses)
{
	return _peParser.ReadData(
		addresses, 
		_exportTable.ExportAddressTable, 
		_exportTable.AddressTableEntries*sizeof(uint32_t)
	);
}

void ExportDirectoryParser::Impl::LoadNamePointerTable(uint32_t* namesArray)
{
	return _peParser.ReadData(
		namesArray, 
		_exportTable.ExportNamePointerTable, 
		_exportTable.NumberOfNamePointers*sizeof(uint32_t)
	);
}

void ExportDirectoryParser::Impl::LoadOrdinalTable(uint16_t* ordinalArray)
{
	return _peParser.ReadData(
		ordinalArray, 
		_exportTable.OrdinalTableAddress,
		_exportTable.NumberOfNamePointers*sizeof(uint16_t)
	);
}