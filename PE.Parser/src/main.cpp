#include <fstream>
#include <string>
#include <Parser.h>
#include <Headers/DosHeader.h>
#include <Headers/OptionalHeader.h>
#include <Headers/PEHeader.h>
#include <vector>
#include <memory>
#include <Headers/SectionHeader.h>

const uint32_t i386 = 0x14c;
const uint32_t x64 = 0x8664;

using namespace Headers;

int main()
{
	const char* fileName = "C:\\Users\\Ori\\Desktop\\f.exe";

	std::ifstream peFile;
	peFile.open(fileName, std::ios_base::binary);

	Parser parser(peFile);

	const DosHeader dosHeader = parser.Read<DosHeader>();
	const PEHeader peHeader = parser.Read<PEHeader>(dosHeader.NewExeHeaderFilePointer);
	
	if (peHeader.CoffHeader.Machine != i386)
	{
		return -1;
	}

	const OptionalHeader32 optionalHeader = parser.Read<OptionalHeader32>();
	
	const auto directories = parser.ReadVector<DataDirectory>(optionalHeader.NtSpecific.NumberofRvaAndSizes);
	
	const auto sections = parser.ReadVector<SectionHeader>(peHeader.CoffHeader.NumberOfSections);

	return 0;
}



