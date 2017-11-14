#pragma once
#include <cstdint>

namespace Headers
{
	typedef uint16_t DllCharacteristic;

	namespace DllCharacteristics
	{
		const DllCharacteristic DYNAMIC_BASE = 0x40; // The DLL can be relocated at load time
		const DllCharacteristic FORCE_INTEGRITY = 0x0080; //	Code integrity checks are forced
		const DllCharacteristic NX_COMPAT = 0x0100;//	The image is compatible with data execution prevention(DEP)
		const DllCharacteristic NO_ISOLATION = 0x0200;//	The image is isolation aware, but should not be isolated
		const DllCharacteristic NO_SEH = 0x0400;// The image does not use structured exception handling(SEH).No handlers can be called in this image
		const DllCharacteristic NO_BIND = 0x0800; //Do not bind image
		const DllCharacteristic WDM_DRIVER = 0x2000; //Driver is a WDM Driver
		const DllCharacteristic TERMINAL_SERVER_AWARE = 0x8000;//Image is Terminal Server aware 
	}
}
