#pragma once
#include <cstdint>

namespace Headers
{
	typedef uint16_t MachineType;

	namespace MachineTypes
	{
		const MachineType UNKNOWN = 0x0; 		// Contents assumed to be applicable to any machine type.
		const MachineType ALPHA = 0x184;	// Alpha AXPô.
		const MachineType ARM = 0x1c0;    // 
		const MachineType ALPHA64 = 0x284; 	// Alpha AXPô 64 - bit.
		const MachineType I386 = 0x14c; 	// Intel 386 or later, and compatible processors.
		const MachineType IA64 = 0x200; 	// Intel IA64ô
		const MachineType M68K = 0x268; 	// Motorola 68000 series.
		const MachineType MIPS16 = 0x266;    // 
		const MachineType MIPSFPU = 0x366; 	// MIPS with FPU
		const MachineType MIPSFPU16 = 0x466;	// MIPS16 with FPU
		const MachineType POWERPC = 0x1f0; 	// Power PC, little endian.
		const MachineType R3000 = 0x162;    // 
		const MachineType R4000 = 0x166; 	// MIPSÆ little endian.
		const MachineType R10000 = 0x168;    // 
		const MachineType SH3 = 0x1a2; 	// Hitachi SH3
		const MachineType SH4 = 0x1a6; 	// Hitachi SH4
		const MachineType THUMB = 0x1c2;    // 
	}
}
