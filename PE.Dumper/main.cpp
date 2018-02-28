#include <PE.Parser/Headers/OptionalHeader.h>
#include <PE.Parser/Headers/SectionHeader.h>
#include <PE.Parser/Headers/DirectoryOffset.h>
#include <PE.Parser/PEParser.h>
#include <PE.Parser/ExportDirectoryParser.h>
#include <PE.Parser/ImportDirectoryParser.h>
#include <PE.Parser/ResourceDirectoryParser.h>

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>


using namespace Headers;


void WriteDataDirectories(const PEParser& parser, std::ostream& output);
void WriteSectionHeaders(const PEParser& parser, std::ostream& output);
void WriteExports(const ExportDirectoryParser& parser, std::ostream& output);
void WriteImports(const ImportDirectoryParser& parser, std::ostream& output);
void WriteResourceTable(const ParsedResourceTable& table, std::ostream& output, std::string tab = " ");

int main()
{
	const char* fileName = "C:\\Windows\\System32\\kernel32.dll";

	std::ifstream peFile;
	peFile.exceptions(std::istream::failbit | std::istream::badbit);
	peFile.open(fileName, std::ios_base::binary);
	
	PEParser peParser(peFile);
	peParser.Load();

	ResourceDirectoryParser resourceParser(peParser);

	if(resourceParser.Load())
	{
		WriteResourceTable(resourceParser.GetRootTable(), std::cout);
	}

	getchar();
	return 0;
}

void WriteDataDirectories(const PEParser& parser, std::ostream& output)
{
	const std::ios_base::fmtflags oldFlags = output.flags();

	output << std::hex << std::uppercase;
	output << std::left << std::setfill(' ');
	output << std::setw(25) << "Directory" << " ";
	output << std::setw(8) << "RVA" << " ";
	output << std::setw(8) << "Size" << std::endl;
	
	int index = 0;
	
	for (const DataDirectory& directory : parser.GetDataDirectories())
	{
		// Write Data Directory Name
		output << std::left << std::setfill(' ');
		output << std::setw(25) << DirectoryOffsets::OffsetToName[index];

		// Write Directory Info
		output << std::right << std::setfill('0');
		output << std::setw(8) << directory.RVA << " ";
		output << std::setw(8) << directory.Size;
		output << std::endl;

		++index;
	}

	output << std::endl;
	output.flags(oldFlags);
}


void WriteSectionHeaders(const PEParser& parser, std::ostream& output)
{
	auto sections = parser.GetSectionHeaders();

	for (const SectionHeader& sec : sections)
	{
		std::cout << sec.Name << std::endl;
	}
}

void WriteExports(const ExportDirectoryParser& parser, std::ostream& output)
{
	const std::ios_base::fmtflags oldFlags = output.flags();

	output << std::hex << std::uppercase;

	output << std::left << std::setfill(' ');
	output << std::setw(8) << "Ordinal" << " ";
	output << std::setw(35) << "Name" << " ";
	output << std::setw(8) << "Address" << std::endl;
	
	for (const ExportEntry& exportEntry : parser.GetEntries())
	{
		// Write Export Entry
		
		output << std::setw(8) << exportEntry.Ordinal << " ";

		output << std::left << std::setfill(' ');
		output << std::setw(35) << exportEntry.Name << " ";

		output << std::right << std::setfill('0');
		output << std::setw(8) << exportEntry.Address;

		if (exportEntry.IsForward())
		{
			output << " -> " << exportEntry.ForwardedSymbol;
		}
		output << std::endl;
	}

	output << std::endl;
	output.flags(oldFlags);
}

void WriteImports(const ImportDirectoryParser& parser, std::ostream& output)
{
	const std::ios_base::fmtflags oldFlags = output.flags();

	for (const ParsedImportDescriptor& descriptor : parser.GetParsedImportDescriptors())
	{
		output << descriptor.dllName << std::endl;

		for(const ImportedFunction& function : descriptor.functions)
		{
			if (function.IsOrdinal())
			{
				output << "\tOrdinal" << function.ordinal << std::endl;
			}
			else
			{
				output << "\t" << function.name << " Hint:" << function.hint << std::endl;
			}
			
		}
	}

	output << std::endl;
	output.flags(oldFlags);
}

void WriteResourceTable(const ParsedResourceTable& table, std::ostream& output, std::string tab)
{
	output << tab << "Resource Table Data:" << std::endl;

	tab += " ";

	output << tab << "Level" << table.Level << std::endl;
	output << tab << "Characteristics " << table.RawTable.Characteristics << std::endl;
	output << tab << "TimeDateStamp " << table.RawTable.TimeDateStamp << std::endl;
	output << tab << "MajorVersion " << table.RawTable.MajorVersion << std::endl;
	output << tab << "MinorVersion " << table.RawTable.MinorVersion << std::endl;
	output << tab << "NumberOfNameEntries " << table.RawTable.NumberOfNameEntries << std::endl;
	output << tab << "NumberOfIdEntries " << table.RawTable.NumberOfIdEntries << std::endl;
	output << tab << "Entries: " << std::endl;

	tab += " ";

	for each (const ParsedResourceEntry& entry in table.Entries)
	{
		output << tab << "Entry ";

		if (entry.RawEntry.HasName())
		{
			std::wcout << std::wstring(reinterpret_cast<wchar_t*>(entry.Name.String),
				entry.Name.Length);
		}
		else
		{
			output << entry.RawEntry.Id();
		}

		if (entry.RawEntry.IsSubdirectory())
		{
			output << " Type: SubDirectory";
			output << std::endl;
			WriteResourceTable(entry.SubDirectory, output, tab+"  ");
		}
		else
		{
			output << " Type: DataEntry";
			output << std::endl;
			output << " " << tab << "DataEntry.Size " << entry.DataEntry.Size << std::endl;
			output << " " << tab << "DataEntry.Codepage " << entry.DataEntry.Codepage << std::endl;
			output << " " << tab << "DataEntry.Reserved " << entry.DataEntry.Reserved << std::endl;
		}
	}
}