//------------------------------------------------------------------------------
//Filename       imagemap.h
//System         
//Author         Martin Alderton
//Date           Mon 9 Oct 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	imageMap_Included
#define	imageMap_Included

	#include	"3DDefs.h"										//PD 30Oct95
	#include	"FileMan.h"										//PD 06Nov95

	#include	"bitfield.h"									//PD 25Aug96

#define MaxNumberOfImageMaps 512								//RJS 11Jul97
#define MaxMapDirs 			16									//DAW 27Oct98

typedef ImageMapNumber *ImageMapListPtr;

MINMAX		(ImageMapBit,0,512);								//DAW 27Oct98
MAKEFIELD 	(ImageMapBit,ImageMapBitMIN,ImageMapBitMAX);		//DAW 27Oct98
//DeadCode DAW 27Oct98 MAKEFIELD 	(ImageMapNumber,ImageMapNumberMIN,ImageMapNumberMAX);//PD 25Aug96


class	 ImageMap
{
	struct	SuperMap											//DAW 27Oct98
	{															//DAW 27Oct98
		UWord				offset_8bit;						//DAW 03Nov98
		UWord				offset_16bit;						//DAW 03Nov98
		SWord				nomaps;								//DAW 27Oct98
		ImageMapBitField	imbf;								//DAW 27Oct98
		ImageMapDescPtr		*imagemaptable;						//DAW 27Oct98
	};															//DAW 27Oct98
																//DAW 27Oct98
	SuperMap		superimagemaptable[MaxMapDirs];				//DAW 27Oct98
	SWord			supercnt;									//DAW 27Oct98
	
	friend	class	fileblock;
	
//DeadCode DAW 27Oct98 	ImageMapDesc	*imagemaptable;

	SLong			total_image_mem;							//PD 06Jun96
	SLong			total_ac_mem;								//RJS 24Jun98
	SLong			total_cockpit_mem;							//RJS 24Jun98

	UWord			list_size,
					list_index;

	SLong			failedcnt;									//RJS 13Jun99

//DeadCode DAW 27Oct98 	ImageMapNumberField	imnf;									//PD 25Aug96

	public:
//DeadCode DAW 27Oct98 			SLong		*imagemaptable2;						//PD 10Mar97
			Bool		DoingAC,DoingCock;						//RJS 24Jun98

			ImageMap();											//DAW 27Oct98
   			~ImageMap(void );

			void	AddImageMapToGlbList(UWord );				//PD 03Nov98
			void 	UnLoadImageMapPtrs(void);
			void 	LoadImageMapPtrs();
 			ImageMapDescPtr	GetImageMapPtr(ImageMapNumber,Bool	skipmap=FALSE);//RJS 15Dec96

			SLong	ImageMapMemUsed()	{return total_image_mem;};//PD 06Jun96
			void	InitImageMaps();							//DAW 27Oct98
			void 	UnLoadImageMaps();							//RJS 14Jun99
		
	private:
			Bool 	LoadImageMap(SuperMap*,UWord,Bool,Bool	skipmap=FALSE);//DAW 27Oct98
			void 	UnLoadImageMap(ImageMapNumber);
			static  void 	FixupImageMap(void*	&dataarea,ULong&	datalengthin);
			void 	UnLoadImageMapPtr(SuperMap*,UWord);			//DAW 27Oct98
			void	LoadFontMap(SuperMap*, UWord);						//RJS 4Dec00

	protected:

};

extern ImageMap  Image_Map;										//PD 29Nov95

const ImageMapNumber FONTBASENO	=	(ImageMapNumber)   1025;

#endif


