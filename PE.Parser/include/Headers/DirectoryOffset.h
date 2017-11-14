#pragma once
#include <cstdint>

namespace Headers
{
	namespace DirectoryOffsets
	{
		const uint32_t EXPORT = 0;//Export Directory	
		const uint32_t IMPORT = 1;//Import Directory	
		const uint32_t RESOURCE = 2;//Resource Directory	
		const uint32_t EXCEPTION = 3;//Exception Directory	
		const uint32_t SECURITY = 4;//Security Directory	
		const uint32_t BASERELOC = 5;//Base Relocation Table	
		const uint32_t DEBUG = 6;//Debug Directory	
		const uint32_t ARCHITECTURE = 7;//Architecture specific data	
		const uint32_t GLOBALPTR = 8;//Global pointer register relative virtual address	
		const uint32_t TLS = 9;//Thread Local Storage directory	
		const uint32_t LOAD_CONFIG = 10;//Load Configuration directory	
		const uint32_t BOUND_IMPORT = 11;//Bound Import directory
		const uint32_t IAT = 12;//Import Address Table
		const uint32_t DELAY_IMPORT = 13;//Delay Import table
		const uint32_t COM_DESCRIPTOR = 14;//	COM descriptor table	
	}
}
