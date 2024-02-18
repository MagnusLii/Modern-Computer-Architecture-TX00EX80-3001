#pragma once
#include <vector>
#include <cstdint>
#include "CacheBlock.h"

class CacheSet: public CacheBlock
{
public:
	CacheSet(int blockSize, int associativity);
	~CacheSet(void);
	bool lookup(uint64_t tag);
	bool update(uint64_t tag);
private:
	std::vector<CacheBlock *> blocks;
	void updateLru(CacheBlock *recent);
};

