#pragma once
#include <cstdint>
#include <Pack.h>


namespace Headers
{
	namespace Coff
	{

		PACK(struct COFFRelocations
		{
			uint32_t VirtualAddress;
			uint32_t SymbolTableIndex;
			uint16_t Type;
		});
	}
}