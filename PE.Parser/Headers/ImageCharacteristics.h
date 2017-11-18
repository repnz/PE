#pragma once
#include <cstdint>

namespace Headers
{
	typedef uint16_t ImageCharacteristic;

	namespace ImageCharacteristics
	{
		const ImageCharacteristic RELOCS_STRIPPED = 0x0001;
		const ImageCharacteristic EXECUTABLE_IMAGE = 0x0002;
		const ImageCharacteristic LINE_NUMS_STRIPPED = 0x0004;
		const ImageCharacteristic LOCAL_SYMS_STRIPPED = 0x0008;
		const ImageCharacteristic AGGRESSIVE_WS_TRIM = 0x0010;
		const ImageCharacteristic LARGE_ADDRESS_AWARE = 0x0020;
		const ImageCharacteristic MACHINE_16BIT = 0x0040;
		const ImageCharacteristic BYTES_REVERSED_LO = 0x0080;
		const ImageCharacteristic MACHINE_32BIT = 0x0100;
		const ImageCharacteristic DEBUG_STRIPPED = 0x0200;
		const ImageCharacteristic REMOVABLE_RUN_FROM_SWAP = 0x0400;
		const ImageCharacteristic SYSTEM = 0x1000;
		const ImageCharacteristic DLL = 0x2000;
		const ImageCharacteristic SYSTEM_ONLY = 0x4000;
		const ImageCharacteristic BYTES_REVERSED_HI = 0x8000;
	}

}
