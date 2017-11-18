#include <PE.Parser/ExportDirectoryParser.h>
#include <PE.Parser/Headers/DirectoryOffset.h>
#include <PE.Parser/Headers/Directories/ExportTable.h>

ExportDirectoryParser::ExportDirectoryParser(PEParser& peParser) : _peParser(peParser)
{

}

bool ExportDirectoryParser::Load()
{
	if (!LoadExportDirectoryTable())
	{
		return false;
	}

	LoadEntries();
	return true;
}

const ExportDirectoryTable& ExportDirectoryParser::GetExportDirectoryTable() const
{
	return exportTable;
}

const std::vector<ExportEntry>& ExportDirectoryParser::GetEntries() const
{
	return _entries;
}


bool ExportDirectoryParser::LoadExportDirectoryTable()
{
	
	const Headers::DataDirectory& exportDir = 
		_peParser.GetDataDirectories().at(Headers::DirectoryOffsets::Export);

	if (exportDir.RVA == 0 && exportDir.Size == 0)
	{
		return false;
	}

	const uint32_t filePointer = _peParser.RVAToFilePointer(exportDir.RVA);

	_peParser.StreamParser().ReadFrom<ExportDirectoryTable>(
		&exportTable,
		filePointer
		);

	return true;
}


void ExportDirectoryParser::LoadEntries()
{
	std::vector<uint32_t> addresses(exportTable.AddressTableEntries);
	std::vector<uint32_t> namePointers(exportTable.NumberOfNamePointers);
	std::vector<uint16_t> ordinals(exportTable.NumberOfNamePointers);

	LoadAddressTable(addresses.data());
	LoadNamePointerTable(namePointers.data());
	LoadOrdinalTable(ordinals.data());
	
	_entries.resize(exportTable.NumberOfNamePointers);

	for (uint32_t i=0; i<exportTable.NumberOfNamePointers; ++i)
	{
		_entries[i].Name = _peParser.ReadString(namePointers[i]);
		_entries[i].Ordinal = ordinals[i];
		_entries[i].Address = addresses[ordinals[i] - exportTable.OrdinalBase + 1];
	}
}

void ExportDirectoryParser::LoadAddressTable(uint32_t* addresses)
{
	return _peParser.ReadData(
		addresses, 
		exportTable.ExportAddressTable, 
		exportTable.AddressTableEntries*sizeof(uint32_t)
	);
}

void ExportDirectoryParser::LoadNamePointerTable(uint32_t* namesArray)
{
	return _peParser.ReadData(
		namesArray, 
		exportTable.ExportNamePointerTable, 
		exportTable.NumberOfNamePointers*sizeof(uint32_t)
	);
}

void ExportDirectoryParser::LoadOrdinalTable(uint16_t* ordinalArray)
{
	return _peParser.ReadData(
		ordinalArray, 
		exportTable.OrdinalTableAddress,
		exportTable.NumberOfNamePointers*sizeof(uint16_t)
	);
}