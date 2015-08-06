//
// Mono debugs using printf syntax and \x commands:
//	\f	formfeed/cls
//  \b	backspace
//	\t	tabstop
//	\n	newline
//	\v	verticaltab
//	\r	carriagereturn
//	\g	hilight
//
class	MonoText
{
	const	int	rows,cols,usedcols;
    UWord*	const	screen;
   	UWord attribute;
    int	x,y;
public:
	MonoText(int origin=0000,int r=25,int c=80,int usedc=0):
		rows(r),cols(c),usedcols(usedc?usedc:c),
		x(0),y(0)
        {	//want to find current text display window. The code below always returns false.  
//       HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
  //      DWORD mode;
    //    CONSOLE_SCREEN_BUFFER_INFO s;
      //  GetConsoleScreenBufferInfo(h,&s);
        if (origin<0x10000)
//	        if (s.dwMaximumWindowSize.X==0 || s.dwMaximumWindowSize.Y==0)
    	    	origin+=0xb0000;
//        	else
  //      		origin+=0xb8000;
        *(UWordP*)&screen=UWordP(origin);
        attribute=screen[0]&-256;
        for(int x=0;x<usedcols;x++)for(int y=0;y<rows;y++)screen[x+y*cols]=' '+attribute;
        }

    void	GotoXY(int xx,int yy)
    {	UByteP(screen+x+y*cols)[1]=attribute>>8;x=xx;y=yy;	}

	void	VPrintF(char* fmt,va_list argptr)
	{
        int cnt;
   		char	buffer[200];
	   	cnt = vsprintf(buffer, fmt, argptr);
        int oldx=x,oldx2=0;
	   	for (int i=0;i<cnt;i++)
	   	{
        	if (buffer[i]<32)
            	switch (buffer[i])
                {
                case '\g':
                	attribute^=0x8000;
                    break;
                case '\f':
                {
			        for(int x=0;x<usedcols;x++)for(int y=0;y<rows;y++)
	                    screen[x+y*cols]=' '+attribute;
        	        x=0;y=0;
                    break;
                }
                case '\v':
                	oldx=x;
				case '\r':
                	oldx2=oldx;
                case '\n':
	            	while (x<cols)	screen[(x++)+y*cols]=' '+attribute;
                    break;
                case '\t':
		        	do	screen[(x++)+y*cols]=' '+attribute;	while (x&7);
                    break;
                case '\b':
	            	x--;
                }
        	else
		   		screen[(x++)+y*cols]=buffer[i]+attribute;
	        if (x>=usedcols)   	{  	x=oldx2;y++;oldx2=0;    }
           	if (y>=rows)   	y=0;
		}
   		UByteP(screen+x+y*cols)[1]=0xf9;
	}
	void	PrintF(char* fmt,...)
	{
		va_list argptr;
	   	va_start(argptr, fmt);
        VPrintF(fmt,argptr);
		va_end(argptr);
    }
    void	PrintF(int x,int y,char* fmt,...)
    {
    	GotoXY(x,y);
		va_list argptr;
	   	va_start(argptr, fmt);
        VPrintF(fmt,argptr);
		va_end(argptr);
    }
    void	PrintF(int y,char* fmt,...)
    {
    	GotoXY(0,y);
		va_list argptr;
	   	va_start(argptr, fmt);
        VPrintF(fmt,argptr);
		va_end(argptr);
    }

};

extern	MonoText	Mono_Text;

