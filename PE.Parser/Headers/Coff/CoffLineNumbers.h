#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>


namespace Headers
{
	namespace Coff
	{
		PACK(struct COFFLineNumbers
		{
			union
			{
				uint32_t SymbolTableIndex;
				uint32_t RVA;
			} Type;
			uint32_t Linenumber;
			uint32_t SymbolTableIndex;
			uint32_t VirtualAddress;
		});
	}
}