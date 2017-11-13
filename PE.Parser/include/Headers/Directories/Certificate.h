#pragma once
#include <cstdint>
#include <Pack.h>

PACK(struct CertificateTableEntry
{
	uint32_t DataPointer;
	uint32_t Size;
});
