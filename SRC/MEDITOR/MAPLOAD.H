//---------------------------------------------------------------------------
#ifndef maploadH
#define maploadH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
//---------------------------------------------------------------------------


    struct	LevelDrop
    {
    	struct	SubDrop
        {
            HBITMAP	h;
            UByte*	c;
			JimBits	scaled;
            SubDrop()	{c=NULL;}
            ~SubDrop()	{if (c) DeleteObject(h);}
        }	maps[4];
    	int	minscale;
        int shfact;
        int blblk;
        int	px,py;
//        int blx,bly;
        JimBits		dirty;
        LevelDrop(int scale=0);
    };

//---------------------------------------------------------------------------


class MapLoad : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall MapLoad(bool CreateSuspended=false);
    LevelDrop* leveldrop;
    UINT	cfreq;UINT cfsrc;
};
//---------------------------------------------------------------------------
#endif
