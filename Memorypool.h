#ifndef MEMORYPOOL_H
# define MEMORYPOOL_H


class Memorypool
{

	private:
		struct _unit
		{
			struct _unit *next;
		};

		unsigned long	_unitSize;
		unsigned long	_poolSize;

		void			*_mBlock;
		struct _unit	*_freeQueue;
	public:
		Memorypool(unsigned long, unsigned long);
		~Memorypool();

		void *alloc(unsigned long);
		void freee(void *);

};

#endif
