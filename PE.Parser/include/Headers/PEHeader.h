#pragma once
#include <cstdint>
#include <Headers/CoffHeader.h>
#include <Pack.h>

namespace Headers
{
	PACK(struct PEHeader
	{
		uint8_t FileSignature[4];
		struct COFFHeader CoffHeader;
	});
}
