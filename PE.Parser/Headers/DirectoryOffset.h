#pragma once
#include <cstdint>

namespace Headers
{
	namespace DirectoryOffsets
	{
		const uint32_t Export = 0;//Export Directory	
		const uint32_t Import = 1;//Import Directory	
		const uint32_t Resource = 2;//Resource Directory	
		const uint32_t Exception = 3;//Exception Directory	
		const uint32_t Security = 4;//Security Directory	
		const uint32_t BaseReloc = 5;//Base Relocation Table	
		const uint32_t Debug = 6;//Debug Directory	
		const uint32_t Architecture = 7;//Architecture specific data	
		const uint32_t GlobalPtr = 8;//Global pointer register relative virtual address	
		const uint32_t TLS = 9;//Thread Local Storage directory	
		const uint32_t LoadConfig = 10;//Load Configuration directory	
		const uint32_t BoundImport = 11;//Bound Import directory
		const uint32_t ImportAddressTable = 12;//Import Address Table
		const uint32_t DelayImport = 13;//Delay Import table
		const uint32_t ComDescriptor = 14;//	COM descriptor table	


		const char* const OffsetToName[]
		{
			"Export",
			"Import",
			"Resource",
			"Exception",
			"Security",
			"BaseReloc",
			"Debug",
			"Architecture",
			"GlobalPtr",
			"Tls",
			"LoadConfig",
			"Bound Import",
			"Import Address Table",
			"Delay Import",
			"Com Descriptor",
			"Reserved",
			"Reserved"
		};
	}
}
