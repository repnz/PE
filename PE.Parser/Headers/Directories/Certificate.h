#pragma once
#include <cstdint>
#include <PE.Parser/Pack.h>

PACK(struct CertificateTableEntry
{
	uint32_t DataPointer;
	uint32_t Size;
});
