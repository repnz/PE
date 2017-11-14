#pragma once
#include <cstdint>
#include <Pack.h>
#include <Headers/Subsystem.h>
#include <Headers/DllCharacteristics.h>

namespace Headers
{

	typedef uint16_t OptionalHeaderMagicNumber;

	namespace OptionalHeaderMagicNumbers
	{
		const OptionalHeaderMagicNumber PE32 = 0x10b;
		const OptionalHeaderMagicNumber PE64 = 0x20b;
	}

	PACK(struct DataDirectory
	{
		uint32_t RVA;
		uint32_t Size;
	});

	PACK(struct OptionalHeaderStandardFields64
	{
		OptionalHeaderMagicNumber Magic;
		uint8_t MajorLinkerVersion;
		uint8_t MinorLinkerVersion;
		uint32_t SizeOfCode; // code sections
		uint32_t SizeOfInitializedData; // data sections
		uint32_t SizeOfUninitializedData; // bss sections
		uint32_t AddressOfEntryPoint;
		uint32_t BaseOfCode; // RVA 
	});

	PACK(struct OptionalHeaderStandardFields32
	{
		OptionalHeaderMagicNumber Magic;
		uint8_t MajorLinkerVersion;
		uint8_t MinorLinkerVersion;
		uint32_t SizeOfCode; // code sections
		uint32_t SizeOfInitializedData; // data sections
		uint32_t SizeOfUninitializedData; // bss sections
		uint32_t AddressOfEntryPoint;
		uint32_t BaseOfCode; // RVA 
		uint32_t BaseOfData;
	}
	);


	PACK(
	template <typename PointerSize>
	struct NtSpecificHeader
	{
		PointerSize ImageBase;
		uint32_t SectionAlignment;
		uint32_t FileAlignment;
		uint16_t MajorOperatingSystemVersion;
		uint16_t MinorOperatingSystemVersion;
		uint16_t MajorImageVersion;
		uint16_t MinorImageVersion;
		uint16_t MajorSubsystemVersion;
		uint16_t MinorSubsystemVersion;
		uint32_t Reserved;
		uint32_t SizeOfImage;
		uint32_t SizeOfHeaders;
		uint32_t CheckSum;
		Subsystem Subsystem;
		DllCharacteristic DllCharacteristics;
		PointerSize SizeOfStackReserve;
		PointerSize SizeOfStackCommit;
		PointerSize SizeOfHeapReserve;
		PointerSize SizeOfHeapCommit;
		uint32_t LoaderFlags; // Obsolete
		uint32_t NumberofRvaAndSizes;
	};
	)

	typedef NtSpecificHeader<uint32_t> NtSpecificHeader32;
	typedef NtSpecificHeader<uint64_t> NtSpecificHeader64;

	PACK(struct OptionalHeader32
	{
		OptionalHeaderStandardFields32 StandardFields;
		NtSpecificHeader32 NtSpecific;
	});


	PACK(struct OptionalHeader64
	{
		OptionalHeaderStandardFields64 StandardFields;
		NtSpecificHeader64 NtSpecific;
	});
}
