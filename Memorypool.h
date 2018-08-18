#ifndef MEMORYPOOL_H
# define MEMORYPOOL_H
# include <cstdlib>

template<typename T>
class Memorypool
{
	private:
		struct _unit
		{
			_unit *next;
		};

		typedef char*	_raw_pointer;
		typedef _unit*	_unit_pointer;

		unsigned long	_unitNum;
		unsigned long	_poolSize;

		void			*_mBlock;
		struct _unit	*_freeStore;
	public:
		Memorypool(unsigned long);

		Memorypool(const Memorypool& pool) throw();
		~Memorypool();

		void	*alloc(unsigned long);
		void	freee(void *);

};

#include "Memorypool.tpp"

#endif
