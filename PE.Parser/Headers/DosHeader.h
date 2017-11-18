#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

namespace Headers
{

	PACK(struct DosHeader
	{
		uint16_t Magic;
		uint16_t LastSize;
		uint16_t BlocksNumber;
		uint16_t RelocationsNumber;
		uint16_t HeaderSize;
		uint16_t MinimumExtraParagraphs;
		uint16_t MaximumExtraParagraphs;
		uint16_t InitialStackSegment;
		uint16_t InitialStackPointer;
		uint16_t Checksum;
		uint16_t InitialIPValue;
		uint16_t InitialCodeSegment;
		uint16_t RelocationTableFileAddress;
		uint16_t OverlayNumber;
		uint16_t Reserved[4];
		uint16_t OEMIdentifier;
		uint16_t OEMInfo;
		uint16_t Reserved2[10];
		uint32_t NewExeHeaderFilePointer;
	});
}
