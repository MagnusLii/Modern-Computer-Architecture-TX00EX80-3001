#pragma once
#include <vector>
#include "Memory.h"
#include "CacheSet.h"

class Cache :
	public Memory
{
public:
	Cache(int accessTime, int size, int blockSize, int associativity, Memory *lowerLevel);
	~Cache(void);
	int read(uint64_t address);
	int write(uint64_t address);
	int getMisses(void);
	int getHits(void);
private:
	Memory *lower;
	std::vector<CacheSet *> sets;
	int blockSize;
	int hits;
	int misses;
};

