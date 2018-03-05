#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

/*
 *
 *	The base relocations directory is a sequence of chunks. each chunk describes a 4kb page.
 *  Structure:
 *   
 *  sequence of:
 *		BaseRelocationChunk - header of the chunk
 *		ReloactionInformation[] - array of relocation information
 *	
 *	the sequence ends when (BaseRelocationChunk.VirtualAddress == 0);
 */

/*
 * The type of the relocation 
 */
enum class RelocationType
{
	Absolute = 0x0, // NOP
	High = 0x1,     // Add the higher 16 bits to the value
	Low = 0x2,      // Add the lower 16 bits to the value
	HighLow = 0x3,  // Add the whole 32 bits to the value
	HighAdj,        // 
	JmpAddr,
	Section,
	Rel32
};

/*
 * The header of a relocation chunk (sequence of 'Relocation' struct)
 * Contains 
 * - VirtualAddress - the base RVA that the relocations of this chunk need to be applied to.
 * - SizeOfBlock - he size of the entire chunk in bytes
 */
PACK(struct BaseRelocationChunk
{
	uint32_t VirtualAddress; 
	uint32_t SizeOfBlock;

	/*
	* This function returns the number of trailing relocations
	* sizeOfBlock = bytes in the whole chunk
	* size of every relocation is 16 bits
	*/
	int GetNumberOfRelocations()
	{

		return (SizeOfBlock - sizeof(BaseRelocationChunk)) / 2;
	}
})
;


/*
 * Each 16-bit-relocation consists of:
 * 1) the relocation position in the lower 12 bits 
 * 2) a relocation type in the high 4 bits.
 */
PACK(struct Relocation
{
	uint16_t Value;

	RelocationType Type() const { return RelocationType(Value >> 12); }
	uint16_t Offset() const { return Value & 0xFFF; }

});

