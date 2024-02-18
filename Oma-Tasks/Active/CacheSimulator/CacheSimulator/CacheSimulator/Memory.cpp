#include "stdafx.h"
#include "Memory.h"


Memory::Memory(int accessTime)
{
	memoryAccessTime = accessTime;
}


Memory::~Memory(void)
{
}

int Memory::read(uint64_t address)
{
	return memoryAccessTime;
}

int Memory::write(uint64_t address)
{
	return memoryAccessTime;
}
