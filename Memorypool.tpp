#ifndef MEMORYPPOL_TPP
# define MEMORYPPOL_TPP

# include <cstdlib>
# include <iostream>


template<typename T>
Memorypool<T>::Memorypool(unsigned long unitNum) :
			_unitNum(unitNum), _poolSize(unitNum * (sizeof(T) + sizeof(_unit))),
			_mBlock(NULL), _freeStore(NULL)
{

	try
	{
		_mBlock = reinterpret_cast<_raw_pointer>(operator new(_poolSize));
		for (int i = 0; i < unitNum; i++)
		{
			_unit *newUnit = reinterpret_cast<_unit_pointer>(reinterpret_cast<_raw_pointer>(_mBlock) + (sizeof(_unit) + sizeof(T)) * i );
			newUnit->next = _freeStore;
			_freeStore = newUnit;
		}
	}
	catch (std::bad_alloc &e)
	{
		std::cerr << "bad alloc caught:  " << e.what() << std::endl;
	}
}

template<typename T>
Memorypool<T>::Memorypool(const Memorypool& pool)
throw()
{
	Memorypool(pool._unitNum);
}

template<typename T>
Memorypool<T>::~Memorypool()
{
	operator delete(_mBlock);
}

template<typename T>
void		*Memorypool<T>::alloc(unsigned long size)
{
	_unit		*tmp = NULL;

	if (_mBlock &&  size <= sizeof(T) && _freeStore)
	{
		tmp = _freeStore;
		_freeStore = tmp->next;
		return (tmp + sizeof(_unit));
	}
	std::cout << "Pool is full" << std::endl;
	return (operator new(size));
}

template<typename T>
void		Memorypool<T>::freee(void *p)
{
	_unit		*current = NULL;

	if (p >= _mBlock && p < reinterpret_cast<_raw_pointer>(_mBlock) + _poolSize)
	{
		current = reinterpret_cast<_unit_pointer>(reinterpret_cast<_raw_pointer>(p) - sizeof(_unit));
		current->next = _freeStore;
		_freeStore = current;
	}
	else
		throw(std::runtime_error("Pointer being freed was not allocated by the pool\n"));
}

#endif
