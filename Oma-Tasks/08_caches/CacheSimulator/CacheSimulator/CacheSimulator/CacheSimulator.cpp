// CacheSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Cache.h"
#include "Memory.h"

void stats(Cache &c)
{
	int hits  = c.getHits();
	int misses =c.getMisses();
	int total = hits + misses;
	std::cout << "hit rate: " << (double) hits / total << " miss rate:" << (double) misses / total << std::endl;
	std::cout << "hits:" << hits << " misses: " << misses  << std::endl;
}


int _tmain(int argc, _TCHAR* argv[])
{

	char operation;
	uint64_t address;
	uint64_t count;
	uint64_t atime = 0;
	uint64_t acount = 0;

	std::cout << "Start" << std::endl;

	std::ifstream infile("swim.trace"); 
	if(!infile) {
		std::cout << "Can't open file" << std::endl;
		return 1;
	}

	Memory mainMemory(90);
	Cache cacheL2(10, 8196, 16, 4, &mainMemory);
	Cache cacheL1(4, 2048, 16, 2, &cacheL2);

	atime = 0;
	acount = 0;

	while(infile.good()) {
		infile >> operation >> std::hex >> address >> count; 
		atime += cacheL1.read(address);
		acount++;
	}
	infile.close();

	std::cout << "L1 cache: " << std::endl;
	stats(cacheL1);
	std::cout << "L2 cache: " << std::endl;
	stats(cacheL2);

	std::cout << "Access times: " << std::endl;
	std::cout << "total time: " << atime << " access count:" << acount << std::endl;
	std::cout << "average access time: " << (double) atime / acount << std::endl;

	std::cout << "End" << std::endl;

	return 0;
}

