



	INVALIDFILENUM		=0xFFFF
};

typedef	UByte	dirindex;
const	dirindex	RAMCACHEHANDLEDIR=255;

dirindex	inline	dirnum(FileNum	filenum)
{	return	(dirindex)	((int)filenum>>(int)DIRNUMSH);	}

FileNum	inline	dirnum(dirindex dirnum)
{	return	(FileNum)	((int)dirnum<<(int)DIRNUMSH);	}


