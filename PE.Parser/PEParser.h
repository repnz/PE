#pragma once
#include <PE.Parser/StreamParser.h>
#include <PE.Parser/Headers/Directories/ExportTable.h>
#include <PE.Parser/Headers/OptionalHeader.h>
#include <PE.Parser/Headers/DosHeader.h>
#include <PE.Parser/Headers/PEHeader.h>
#include <PE.Parser/Headers/SectionHeader.h>

#include <memory>


#ifdef PE32
using CpuOptionalHeader = Headers::OptionalHeader32;
#else
using CpuOptionalHeader = Headers::OptionalHeader64;
#endif

class PEParser
{
private:
	StreamParser _streamParser;
	Headers::DosHeader _dosHeader;
	Headers::PEHeader _peHeader;
	CpuOptionalHeader _optionalHeader;
	std::vector<Headers::DataDirectory> _directories;
	std::vector<Headers::SectionHeader> _sections;
	std::vector<std::unique_ptr<uint8_t[]>> _sectionData;
	const Headers::SectionHeader* ReadDirectoryTable(void* directoryTable, const uint32_t offset, const size_t size);

public:
	PEParser(std::istream& stream);

	void Load();

	const Headers::SectionHeader& GetMatchSection(const uint32_t rva) const;

	uint32_t RVAToFilePointer(uint32_t rva);
	
	void ReadData(void* ptr, uint32_t rva, uint32_t size);

	std::string ReadStringFromRVA(const uint32_t rva);

	uint8_t* PEParser::GetSectionData(const uint32_t index);

	const std::vector<Headers::DataDirectory>& GetDataDirectories() const;

	const std::vector<Headers::SectionHeader>& GetSectionHeaders() const;
	
	const Headers::DosHeader& GetDosHeader() const;

	const CpuOptionalHeader& GetOptionalHeader() const;

	const Headers::PEHeader& GetPEHeader() const;

	StreamParser& GetStreamParser();

	const Headers::DataDirectory& GetDirectory(const uint32_t offset) const;

	template <typename T>
	void ReadData(T* ptr, const uint32_t rva)
	{
		ReadData(ptr, rva, sizeof(T));
	}

	template <typename T>
	const Headers::SectionHeader* ReadDirectoryTable(T* directoryTable, const uint32_t offset)
	{
		return ReadDirectoryTable(directoryTable, offset, sizeof(T));
	}
};
