#include <fstream>
#include <string>
#include <Parser.h>
#include <Headers/DosHeader.h>
#include <Headers/OptionalHeader.h>
#include <Headers/PEHeader.h>
#include <vector>
#include <memory>
#include <Headers/SectionHeader.h>
#include <iostream>

using namespace Headers;

int main()
{
	const char* fileName = "C:\\Users\\Ori\\Desktop\\f.exe";

	std::ifstream peFile;
	peFile.open(fileName, std::ios_base::binary);

	Parser parser(peFile);

	const DosHeader dosHeader = parser.Read<DosHeader>();
	const PEHeader peHeader = parser.Read<PEHeader>(dosHeader.NewExeHeaderFilePointer);
	
	if (peHeader.CoffHeader.Machine != MachineTypes::I386)
	{
		return -1;
	}

	const OptionalHeader32 optionalHeader = parser.Read<OptionalHeader32>();
	
	const auto directories = parser.ReadVector<DataDirectory>(optionalHeader.NtSpecific.NumberofRvaAndSizes);
	
	const auto sections = parser.ReadVector<SectionHeader>(peHeader.CoffHeader.NumberOfSections);

	for each (SectionHeader section in sections)
	{
		if (section.Characteristics & SectionCharacteristics::MEM_EXECUTE)
		{
			std::cout << section.Name << " " << section.VirtualAddress << std::endl;
		}
	}

	getchar();
	return 0;
}



