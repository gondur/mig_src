//------------------------------------------------------------------------------
//Filename       stack.h
//System         
//Author         Paul.   
//Date           Wed 29 Nov 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	STACK_Included
#define	STACK_Included

#define	DEFAULT_STACK 0

template<class T>
class	Stack
{
	T		*v;			//Stack base ptr
	T		*p;			//Current stack position ptr
	int		sz;			//Stack size
	T		*e;			//Stack end ptr
	char	*stack_name;//Stack ID string ptr

	public:

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Stack
//Author		Paul.   
//Date			Wed 29 Nov 1995
//
//Description	initialises a stack of objects of type T
//
//Inputs		name = stack ID
//				s	 = stack size required	
//------------------------------------------------------------------------------
		Stack(char *name, int s)
		{
			v = p = new T[sz=s];
		 	e = &p[sz];
			stack_name = name;
		}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		~Stack
//Author		Paul.   
//Date			Wed 29 Nov 1995
//
//Description	Deletes stack object.
//
//------------------------------------------------------------------------------
		~Stack()
		{
			delete [] v;
		}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		Paul.   
//Date			Wed 29 Nov 1995
//
//Description	Push an object of type T onto the stack
//
//Inputs		a = object of type T
//
//------------------------------------------------------------------------------
		void	Push(T a)
		{
			*p++=a;
			if(p>e)
				_Error.EmitSysErr("ERROR: %s stack o'flow.",stack_name);
		}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		Paul.   
//Date			Wed 29 Nov 1995
//
//Description	Pops an object of type T off the stack
//
//Returns		Object of type T	
//
//------------------------------------------------------------------------------
		T		Pop()
		{
			T	ret_val = *--p;
			if(p<v)
				_Error.EmitSysErr("ERROR: %s stack u'flow.",stack_name);
			return ret_val;
		}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		Paul.   
//Date			Wed 29 Nov 1995
//
//Description	Gets currently allocated size of a stack.
//
//Returns		stack size.
//
//------------------------------------------------------------------------------
		int		Size() const{ return p-v; }

	private:

	protected:

};

template<class T>
class	Heap
{
	T*	currentheapp;
	T*	heapbasep;
	T*	heapendp;

	public:

	CON	Heap()
		{
			currentheapp =
				heapbasep =
				heapendp = (T* )NULL;
		}

	CON	Heap(SLong hs)
		{
			currentheapp =
				heapbasep = new T[hs];
			heapendp = heapbasep + hs;
		}

	DES	~Heap()
		{
			if (heapbasep!=NULL)
			{
				delete [] heapbasep;
				heapbasep =
					heapendp =
					currentheapp = (T* )NULL;
			}
		}

	T*	Alloc(SLong count=1)
		{
			T*	retval = currentheapp;
			currentheapp += count;
//TempCode PD 18Oct96 			if (currentheapp>=heapendp)	INT3();
			return (retval);
		}

	void Reset()
		{
			currentheapp = heapbasep;
		}
};

#endif

