#pragma once
#include <cstdint>
#include <PE.Parser/Headers/CoffHeader.h>
#include <PE.Parser/Pack.h>

namespace Headers
{
	PACK(struct PEHeader
	{
		uint8_t FileSignature[4];
		struct COFFHeader CoffHeader;
	});
}
