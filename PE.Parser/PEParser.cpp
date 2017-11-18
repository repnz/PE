#include <PE.Parser/PEParser.h>
#include <iostream>
#include "Headers/DirectoryOffset.h"

using namespace Headers;

PEParser::PEParser(std::istream& stream) : _streamParser(stream)
{
}

void PEParser::Load()
{
	_streamParser.Read<DosHeader>(&_dosHeader);
	_streamParser.ReadFrom<PEHeader>(&_peHeader, _dosHeader.NewExeHeaderFilePointer);
	_streamParser.Read(&_optionalHeader);
	

	_directories.resize(_optionalHeader.NtSpecific.NumberofRvaAndSizes);
	_streamParser.ReadVector<DataDirectory>(_directories, _optionalHeader.NtSpecific.NumberofRvaAndSizes);

	_sections.resize(_peHeader.CoffHeader.NumberOfSections);
	_streamParser.ReadVector<SectionHeader>(_sections, _peHeader.CoffHeader.NumberOfSections);
	_exportDirectory = std::make_unique<ExportDirectoryTable>();

	

}

uint32_t PEParser::RVAToFilePointer(const uint32_t rva)
{
	for (const SectionHeader& section : _sections)
	{
		if (rva >= section.VirtualAddress && rva <= (section.VirtualAddress+section.SizeOfRawData))
		{
			return rva - section.VirtualAddress + section.PointerToRawData;
		}
	}

	return -1;
}

void PEParser::ReadData(void* ptr, const uint32_t rva, const uint32_t size)
{
	const uint32_t filePointer = RVAToFilePointer(rva);

	_streamParser.Read(
		ptr,
		filePointer,
		size
	);
}

std::string PEParser::ReadString(uint32_t rva)
{
	return _streamParser.ReadString(RVAToFilePointer(rva));
}

uint8_t* PEParser::GetSectionData(const uint32_t index)
{
	if (_sectionData[index] == nullptr)
	{
		_sectionData[index] = std::make_unique<uint8_t[]>(_sections[index].SizeOfRawData);

		_streamParser.Read<uint8_t>(
			_sectionData[index].get(),
			_sections[index].PointerToRawData,
			_sections[index].SizeOfRawData
			);
	}

	return _sectionData[index].get();
}

const std::vector<Headers::DataDirectory>& PEParser::GetDataDirectories() const
{
	return _directories;
}

const std::vector<Headers::SectionHeader>& PEParser::GetSectionHeaders() const
{
	return _sections;
}

const Headers::DosHeader& PEParser::GetDosHeader() const
{
	return _dosHeader;
}

const CpuOptionalHeader& PEParser::GetOptionalHeader() const
{
	return _optionalHeader;
}

const Headers::PEHeader& PEParser::GetPEHeader() const
{
	return _peHeader;
}

StreamParser& PEParser::StreamParser()
{
	return _streamParser;
}
