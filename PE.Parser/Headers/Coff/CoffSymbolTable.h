#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

namespace Headers
{
	namespace Coff
	{

		union COFFSymbolName
		{
			uint8_t ShortName[8];

			PACK(struct 
			{
				uint32_t Zeroes;
				uint32_t Offset;
			} StringTable);

		};

		PACK(struct COFFSymbolTable
		{
			COFFSymbolName Name;
			uint32_t Value;
			uint16_t SectionNumber;
			uint16_t Type;
			uint8_t StorageClass;
			uint8_t NumberOfAuxSymbols;
		});
	}
}
