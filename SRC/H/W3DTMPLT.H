//------------------------------------------------------------------------------
//Filename       w3dtmplt.h
//System         
//Author         Paul.   
//Date           Fri 13 Feb 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	W3DTMPLT_Included
#define	W3DTMPLT_Included

#define	DEFAULT_W3DTMPLT 0

template<class Obj> class IHeap
{
private:
	Obj* pCur;
	Obj* pBase;
	Obj* pEnd;
public:
	IHeap(ULong sz=1) {pCur=pBase=new Obj[sz];pEnd=pBase+sz;}
	~IHeap() {delete [] pBase;}
	Obj* Alloc(ULong cnt=1)
	{
		Obj* retval=pCur;
		while (--cnt)
		{
			pCur->Obj();
			pCur++;
		}
		if (pCur>pEnd) _asm {int 3};
		return retval;
	}
	void Reset() {pCur=pBase;}
};

template<class Obj> class SameDifference
{
public:
	Obj*	pNextSame;
	Obj*	pNextDif;
	SameDifference() {pNestSame=pNextDif=NULL;}
	virtual bool compareFn(Obj&,Obj&)=0;
};

template<class Obj> class PList
{
	friend class Obj;
private:
	Obj* pHead;
	Obj* pCurSame;
	Obj* pCurDif;
public:
	PList() {pHead=NULL;}
	~PList() {}
	void Reset()		{pHead=NULL;}

	void InsertFirst(Obj* newObj)
	{
		if (pHead==NULL) pCurSame=pHead=newObj,return;
		else
		{
			Obj* pScan=pHead;
			while (pScan!=NULL)
			{
	 			//Scan for matching type
				if (compareFn(newObj,pScan)==true)
				{
					while (pScan->pNextSame!=NULL)
						pScan=pScan->pNextSame;
					pCurSame=pScan->pNextSame=newObj;
					return;
				}
				else pScan=pScan->pNextDiff;
			}
			//New type so add to the start of the
			//list (should be faster to find the next
			//objects insertion point 'cos similar 
			//objects will probably be inserted together
			newObj->pNextDiff=pHead;
			pCurSame=pHead=newObj;
		}
	}
	void InsertNext(Obj* newObj)
	{
	 	if (compareFn(newObj,pCurSame))
		{
			pCurSame->pNextSame=newObj;
			pCurSame=newObj;
			return;
		}
		InsertFirst(newObj);
	}
	Obj* FindFirst() 	{return pCurDif=pCurSame=pHead;}
	Obj* FindNext()
	{
		if (pCurSame->pNextSame!=NULL) return pCurSame=pCurSame->pNextSame;
		return pCurSame=pCurDif=pCurDif->pNextDif;
	}
};

#endif
