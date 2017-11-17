#include <fstream>
#include <string>
#include <Headers/OptionalHeader.h>
#include <vector>
#include <memory>
#include <Headers/SectionHeader.h>
#include <iostream>
#include <iomanip>
#include <Headers/DirectoryOffset.h>
#include <PEParser.h>

using namespace Headers;


template <typename DirIterator>
void WriteDataDirectories(DirIterator begin, const DirIterator end, std::ostream& output);

int main()
{
	const char* fileName = "C:\\Users\\Ori\\Desktop\\f.exe";

	std::ifstream peFile;
	peFile.exceptions(std::istream::failbit | std::istream::badbit);
	peFile.open(fileName, std::ios_base::binary);
	
	PEParser peParser(peFile);
	peParser.Load();

	auto dirs = peParser.GetDataDirectories();
	
	WriteDataDirectories(dirs.cbegin(), dirs.cend(), std::cout);

	auto sections = peParser.GetSectionHeaders();

	for (const auto& sec : sections)
	{
		std::cout << sec.Name << std::endl;
	}

	getchar();
	return 0;
}


template <typename DirIterator>
void WriteDataDirectories(DirIterator begin, const DirIterator end,
	std::ostream& output)
{
	const int oldFlags = output.flags();

	std::cout << std::hex << std::uppercase;

	std::cout << std::left << std::setfill(' ') <<
		std::setw(25) << "Directory" <<
		std::setw(8) << "RVA" << " " << std::setw(8) << "Size" << std::endl;

	for (int i = 0; begin != end; ++begin, ++i)
	{
		const DataDirectory& directory = *begin;

		std::cout << std::left << std::setfill(' ');
		std::cout << std::setw(25) << DirectoryOffsets::OffsetToName[i];

		std::cout << std::right
			<< std::setfill('0');

		std::cout << std::setw(8) << directory.RVA << " " << std::setw(8) << directory.Size << std::endl;
	}

	output.flags(oldFlags);
}