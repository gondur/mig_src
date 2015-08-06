//------------------------------------------------------------------------------
//Filename       modfile.h
//System         
//Author         Jim Taylor
//Date           Wed 14 Feb 1996
//Description    The struct UFILE gives an update file
//				 This file is written sequentially, but will only change date if
//				 actually changed values.
//				 Note: size may not work correctly.				
//				Syntax for fopen() has changed slightly. 
//				You only specify the file type T/B as a character.
//------------------------------------------------------------------------------
#ifndef	MODFILE_Included
#define	MODFILE_Included

#define	DEFAULT_MODFILE 0


	enum	{BUFFERSIZE=10000};
struct UFILE
{
	char	mode;
    Bool	written;
 	char*	buffer;
	int		bufferind;
	int		lasttell;
	FILE*	f;
};

static	UFILE*	fopen(char* name,char type)
{
UFILE*	retval=new UFILE;
		retval->mode=type;
char	mtype[]={'r','+',type,0};
char	wtype[]={'w',type,0};
	retval->bufferind=0;
	retval->lasttell=0;
	retval->buffer=NULL;
	retval->written=FALSE;
	retval->f=fopen(name,mtype);
	if (retval->f==NULL)
	{
		retval->written=TRUE;
		retval->f=fopen(name,wtype);
	}
	else
		retval->buffer= new char [BUFFERSIZE];
	if (retval->f==NULL)
	{
		delete retval;
		return(NULL);
	}
	elser
		return(retval);
}

static	int fwrite(void const * src,unsigned int recsize,unsigned int reccount,UFILE* ofile)
{
    if (!ofile->written)
    {
		if (recsize*reccount>(ULong)BUFFERSIZE-ofile->bufferind)
			//it won't fit!
		{
			ofile->lasttell=ftell(ofile->f);
			ofile->bufferind=0;
		}
		if (recsize*reccount>BUFFERSIZE)
		{
			char* btmp=new char [recsize*reccount];
//DeadCode JIM 13Feb96 			Assert(btmp&&"Memory!");
			ULong recsread=fread(btmp,recsize,reccount,ofile->f);
			if (recsread!=reccount)
    	        ofile->written=TRUE;
	        else
    	        if (memcmp(btmp,src,reccount*recsize)!=0)
        	        ofile->written=TRUE;
			delete [] btmp;
	        if (!ofile->written)
    	        return reccount;

		}
		else
		{
	        ULong recsread=fread(&ofile->buffer[ofile->bufferind],recsize,reccount,ofile->f);
			if (recsread!=reccount)
    	        ofile->written=TRUE;
	        else
    	        if (memcmp(&ofile->buffer[ofile->bufferind],src,reccount*recsize)!=0)
        	        ofile->written=TRUE;
	        if (!ofile->written)
			{
				ofile->bufferind+=reccount*recsize;
    	        return reccount;
			}
		}

	    fflush(ofile->f);
    	fseek(ofile->f,ofile->lasttell,SEEK_SET);
        fflush(ofile->f);
		//chsize(_os_handle(fileno(ofile->f)),ofile->lasttell);
        fflush(ofile->f);
		fwrite(ofile->buffer,ofile->bufferind,1,ofile->f);
		delete [] ofile->buffer;
		ofile->buffer=NULL;
    }
    return(fwrite(src,recsize,reccount,ofile->f));
}

static	int	fprintf(UFILE* ofile,const char* fmt ...)
{
	char	workspace[300];
	va_list	marker;
	va_start(marker, fmt);
	int count=vsprintf(workspace,fmt,marker);
	return(fwrite(workspace,1,count,ofile));
}

static	int	fputc( int __c, UFILE* __fp )
{
	return(fwrite(&__c,1,1,__fp));
}

static	int	fclose( UFILE*	__fp )
{
	if (__fp->written)
		if (__fp->mode=='t' || __fp->mode=='T')
			fwrite(&(__fp->mode=26),1,1,__fp);
FILE*	tmp=__fp->f;
	delete [] __fp->buffer;
	delete __fp;
 	return(fclose(tmp));
}

typedef	FILE*	file;
typedef	UFILE*	ufile;



#endif
