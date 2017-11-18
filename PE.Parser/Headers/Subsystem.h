#pragma once
#include <cstdint>

namespace Headers
{
	typedef uint16_t Subsystem;

	namespace Subsystems
	{
		const Subsystem UNKNOWN = 0;//Unknown subsystem.
		const Subsystem NATIVE = 1;//Used for device drivers and native Windows NT processes.
		const Subsystem WINDOWS_GUI = 2;//Image runs in the Windowsô graphical user interface(GUI) subsystem.
		const Subsystem WINDOWS_CUI = 3;//Image runs in the Windows character subsystem.
		const Subsystem POSIX_CUI = 7;//Image runs in the Posix character subsystem.
		const Subsystem WINDOWS_CE_GUI = 9;//Image runs in on Windows CE.
		const Subsystem EFI_APPLICATION = 10;//Image is an EFI application.
		const Subsystem EFI_BOOT_SERVICE_DRIVER = 11;// Image is an EFI driver that provides boot services.
		const Subsystem EFI_RUNTIME_DRIVER = 12; //Image is an EFI driver that provides runtime services.
		const Subsystem EFI_ROM = 13;//	EFI ROM image
		const Subsystem XBOX = 14;//	Xbox system
		const Subsystem WINDOWS_BOOT_APPLICATION = 16;//	Boot application
	}
}

