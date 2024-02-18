#include "stdafx.h"
#include <iostream>
#include "CacheBlock.h"


CacheBlock::CacheBlock(void)
{
	//std::cout << "CacheBlock: constructor" << std::endl;
	tag = 0xFFFFFFFFFFFFFFFF;
	flags = 0;
}


CacheBlock::~CacheBlock(void)
{
	//std::cout << "CacheBlock: destructor" << std::endl;
}

bool CacheBlock::lookup(uint64_t tag)
{
	if(tag == this->tag) return true;

	return false;
}

bool CacheBlock::update(uint64_t tag)
{
	bool result = false;
	if(tag == 0xFFFFFFFFFFFFFFFF) {
		result = true;
	}
	this->tag= tag;

	return result;
}

int CacheBlock::getFlags(void)
{
	return flags;
}

void CacheBlock::setFlags(int flags)
{
	this->flags = flags;
}

