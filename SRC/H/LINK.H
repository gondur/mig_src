//------------------------------------------------------------------------------
//Filename       link.h
//System         
//Author         Andrew McRae
//Date           Mon 10 Feb 1997
//Description    Template for Linked List Item
//------------------------------------------------------------------------------
#ifndef	LINK_Included
#define	LINK_Included

#define	DEFAULT_LINK 0

template <class ITEM> class LINKEDLIST {

public:

	ITEM** ppBase;
	ITEM* pNextItem;

	LINKEDLIST ()
	{
		ppBase = NULL;
		pNextItem = NULL;
	}

	void Attach (ITEM**, ITEM*);
	void Detach (ITEM*);
	ITEM* NextItem () { return pNextItem; }

//	Bool NextItem (Bool, ITEM**);	// true for from start

};

template <class ITEM> void LINKEDLIST<ITEM>::Attach (ITEM** base, ITEM* item)
{

	ppBase = base;

	if (*ppBase == NULL)
		*ppBase = item;
	else
	{
		ITEM* pItem = *ppBase;
		for (;;)
		{
			if (pItem->List.pNextItem == NULL)
				break;
			pItem = pItem->List.pNextItem;
		}
		pItem->List.pNextItem = item;
	}
	pNextItem = NULL;
	
}

template <class ITEM> void LINKEDLIST<ITEM>::Detach (ITEM* item)
{

	if (*ppBase == item)
	{
		*ppBase = pNextItem;
		return;
	}
	ITEM* pItem = *ppBase;
	for (;;)
	{
		if (pItem->List.pNextItem == NULL)
			return;
		if (pItem->List.pNextItem == item)
			break;
		pItem = pItem->List.pNextItem;
	}
	pItem->List.pNextItem = pNextItem;

}

#endif

