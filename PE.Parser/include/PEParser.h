#pragma once
#include <StreamParser.h>
#include "Headers/OptionalHeader.h"
#include "Headers/DosHeader.h"
#include "Headers/PEHeader.h"
#include "Headers/SectionHeader.h"
#include <memory>

namespace Headers {
	struct DosHeader;
}

using CpuOptionalHeader = Headers::OptionalHeader32;

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

public:
	PEParser(std::istream& stream);
	void Load();

	uint32_t RVAToFilePointer(uint32_t rva);
	uint8_t* PEParser::GetSectionData(const uint32_t index);
	const std::vector<Headers::DataDirectory>& GetDataDirectories() const;
	const std::vector<Headers::SectionHeader>& GetSectionHeaders() const;
	
	const Headers::DosHeader& GetDosHeader() const;

	const CpuOptionalHeader& GetOptionalHeader() const;

	const Headers::PEHeader& GetPEHeader() const;
};
