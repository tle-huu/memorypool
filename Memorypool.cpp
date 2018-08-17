#include "Memorypool.h"
#include <cstdlib>
#include <iostream>

Memorypool::Memorypool(unsigned long unitSize, unsigned long unitNum) :
			_unitSize(unitSize), _poolSize(unitNum * (unitSize + sizeof(struct _unit))),
			_mBlock(NULL), _freeQueue(NULL)
{

	if ((_mBlock = malloc(_poolSize)))
	{
		for (int i = 0; i < unitNum; i++)
		{
			struct _unit *newUnit = (struct _unit *)((char *)_mBlock + (sizeof(struct _unit) + unitSize) * i );
			newUnit->next = _freeQueue;
			_freeQueue = newUnit;
		}
	}
}

Memorypool::~Memorypool()
{
	free(_mBlock);
}

void		*Memorypool::alloc(unsigned long size)
{
	struct _unit		*tmp = NULL;

	if (_mBlock &&  size <= _unitSize && _freeQueue)
	{
		tmp = _freeQueue;
		_freeQueue = tmp->next;
		return (tmp + sizeof(struct _unit));
	}
	return (malloc(size));
}

void		Memorypool::freee(void *p)
{
	struct _unit		*current = NULL;

	if (p >= _mBlock && p < (char *)_mBlock + _poolSize)
	{
		current = (struct _unit *)((char *)p - sizeof(struct _unit));
		current->next = _freeQueue;
		_freeQueue = current;
	}
	else
		throw(std::runtime_error("Pointer being freed was not allocated by the pool\n"));
}
