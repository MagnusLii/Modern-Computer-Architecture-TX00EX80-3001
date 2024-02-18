#include "stdafx.h"
#include <iostream>
#include "CacheSet.h"


CacheSet::CacheSet(int blockSize, int associativity)
{
	//std::cout << "CacheSet: constructor" << std::endl;
	while(associativity-- > 0) {
		blocks.push_back(new CacheBlock());
	}
}


CacheSet::~CacheSet(void)
{
	//std::cout << "CacheSet: destructor" << std::endl;
	std::vector<CacheBlock *>::iterator blockIterator;

	for(blockIterator = blocks.begin(); blockIterator != blocks.end();	blockIterator++)
	{
		delete *blockIterator;
	}
}

bool CacheSet::lookup(uint64_t tag)
{
	std::vector<CacheBlock *>::iterator blockIterator;
	bool hit = false;
	CacheBlock *hb = NULL;

	for(blockIterator = blocks.begin(); blockIterator != blocks.end() && !hit;	blockIterator++)
	{
		hb = *blockIterator;
		hit = hb->lookup(tag);
	}
	if(hit) {
		updateLru(hb);
	}

	return hit;
}

bool CacheSet::update(uint64_t tag)
{
	CacheBlock *lru = *blocks.begin();
	std::vector<CacheBlock *>::iterator lruIterator;

	for(lruIterator = blocks.begin(); lruIterator != blocks.end();	lruIterator++)
	{
		if(lru->getFlags() > (*lruIterator)->getFlags()) lru = *lruIterator;
	}
	lru->update(tag); // least recently used block is replaced with new values
	updateLru(lru); // update LRU counters to match new situation

	return 0;
}


void CacheSet::updateLru(CacheBlock *recent)
{
	int lruIndex = recent->getFlags();
	std::vector<CacheBlock *>::iterator lruIterator;

	for(lruIterator = blocks.begin(); lruIterator != blocks.end();	lruIterator++)
	{
		int i = (*lruIterator)->getFlags();
		if(i > lruIndex) (*lruIterator)->setFlags(i-1);
	}
	recent->setFlags(blocks.size());
}
