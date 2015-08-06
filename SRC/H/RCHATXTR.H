#ifndef		RCHATEXTRA_Defined
#define	RCHATEXTRA_Defined
typedef struct	SIMPLEWAVHEADER									//RJS 09Jun98
{																//RJS 09Jun98
	char	id[4];												//RJS 09Jun98
	UByte	bits_per_sample;									//RJS 09Jun98
	UByte	noChannels;											//RJS 09Jun98
	UWord	sample_rate;										//RJS 09Jun98
	ULong	chunk_size;											//RJS 09Jun98
	SLong	subFactor;											//RJS 27Jul98
	SLong	divFactor;											//RJS 27Jul98
}SWAV;															//RJS 27Jul98
																//RJS 09Jun98
struct	SOffsetList												//RJS 27Jul98
{																//RJS 27Jul98
	ULong	offset;												//RJS 27Jul98
	ULong	size;												//RJS 27Jul98
};																//RJS 27Jul98

class	fileblock;

struct RadioSampleRec											//RJS 09Jun98
{																//RJS 09Jun98
	fileblock	*blockptr;										//RJS 09Jun98
	SLong		size;											//RJS 09Jun98
	SOffsetList *offsetptr;										//RJS 27Jul98
	SWAV		*headerptr;										//RJS 09Jun98
	UByte		*dataptr;										//RJS 27Jul98
																//RJS 09Jun98
	UWord		noFiles;										//RJS 09Jun98
};

#endif