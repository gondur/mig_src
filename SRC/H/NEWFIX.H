#include <malloc.h>
inline	void	*operator	new(size_t s)
{
	return	malloc(s);
}
inline	void	*operator	new[](size_t s)
{
	return	malloc(s);
}
inline	void	operator	delete(void* v)
{
	free(v);
}
inline	void	operator	delete[](void* v)
{
	free(v);
}

