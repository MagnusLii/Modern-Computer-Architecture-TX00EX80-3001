#pragma once
#include <cstdint>
class CacheBlock
{
public:
	CacheBlock(void);
	virtual ~CacheBlock(void);
	virtual bool lookup(uint64_t tag);
	virtual bool update(uint64_t tag);
	int getFlags(void);
	void setFlags(int flags);
private:
	uint64_t tag;
	int flags;
};

