#pragma once
#include <cstdint>

class Memory
{
public:
	Memory(int accessTime);
	~Memory(void);
	virtual int read(uint64_t address);
	virtual int write(uint64_t address);
protected:
	int memoryAccessTime;
};

