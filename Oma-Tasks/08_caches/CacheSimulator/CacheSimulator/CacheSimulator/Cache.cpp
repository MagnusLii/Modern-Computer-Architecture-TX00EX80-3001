#include "stdafx.h"
#include <iostream>
#include "Cache.h"


Cache::	Cache(int accessTime, int size, int blockSize, int associativity, Memory *lowerLevel): Memory(accessTime)
{
	int count = size / (blockSize * associativity);
	std::cout << "Sets: " << count << " Associativity: " << associativity << std::endl;
	this->blockSize = blockSize;
	while(count-- > 0) {
		sets.push_back(new CacheSet(blockSize, associativity));
	}
	this->lower = lowerLevel;
	this->hits = 0;
	this->misses = 0;
}


Cache::~Cache(void)
{
	std::vector<CacheSet *>::iterator setIterator;

	for(setIterator = sets.begin(); setIterator != sets.end(); setIterator++)
	{
		delete *setIterator;
	}
}

int Cache::read(uint64_t address)
{
	uint64_t block = address / blockSize; // calculate block number
	uint64_t set = block % (uint64_t) sets.size(); // calculate set number
	uint64_t tag = block / (uint64_t) sets.size(); // calculate tag

	if(sets[(unsigned int)set]->lookup(tag)) {
		hits++;
		// was found in the cache
		return memoryAccessTime;
	}
	else {
		misses++;
		// was not in the cache
		sets[(unsigned int)set]->update(tag); // bring it in to cache
		return memoryAccessTime + lower->read(address); // not in cache, go to lower level
	}
}

int Cache::write(uint64_t address)
{
	// this version makes no difference between reads and writes
	// for more accurate results implement write policy handling here
	return read(address); 
}
int Cache::getMisses(void)
{
	return misses;
}

int Cache::getHits(void)
{
	return hits;
}

