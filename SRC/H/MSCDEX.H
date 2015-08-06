//------------------------------------------------------------------------------
//Filename       mscdex.h
//System         
//Author         Paul.   
//Date           Mon 28 Oct 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	MSCDEX_Included
#define	MSCDEX_Included

#define	DEFAULT_MSCDEX 0

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Command byte definitions for IOCTLO
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

const	UByte	IREQ_RADDR 			= 	0;
const	UByte	IREQ_LOCHEAD 		= 	1;
const	UByte	IREQ_reserved		=	2;
const	UByte	IREQ_ERRSTAT 		= 	3;
const	UByte	IREQ_AUDINFO 		= 	4;
const	UByte	IREQ_DRVBYTES		=	5;
const	UByte	IREQ_DEVSTAT		=	6;
const	UByte	IREQ_SECTSIZE		=	7;
const	UByte	IREQ_VOLSIZE		=	8;
const	UByte	IREQ_MEDCHNG		=	9;
const	UByte	IREQ_DISKINFO		=	10;
const	UByte	IREQ_TNOINFO		=	11;
const	UByte	IREQ_QINFO			=	12;
const	UByte	IREQ_SUBCHANINFO	=	13;
const	UByte	IREQ_UPCCODE		=	14;
const	UByte	IREQ_AUDSTAT		=	15;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Command byte definitions for IOCTLI
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

const	UByte	OREQ_EJECTDISK				=	0;
const	UByte	OREQ_LOCKUNLOCKDOOR			=	1;
const	UByte	OREQ_RESETDRIVE				=	2;
const	UByte	OREQ_AUDIOCHANNELCONTROL	=	3;
const	UByte	OREQ_WRITECONTROLSTRING		=	4;
const	UByte	OREQ_CLOSETRAY				=	5;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
typedef	struct	CDComm
{
	UByte	request;
}
*CDCommP;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

struct	Raddr : public CDComm
{
	UWord	devheaderp_off;
	UWord	devheaderp_seg;

	Raddr() {request=IREQ_RADDR;}
};

//------------------------------------------------------------------------------

struct LocHead : public CDComm
{
	UByte	addressingmode;
	ULong	locofdrivehead;
	
	LocHead()	{request=IREQ_LOCHEAD;addressingmode=0;}
};

//------------------------------------------------------------------------------

struct	ErrStat : public CDComm
{
	UByte	errstats[128];	//Err stats format is undefined
	
	ErrStat()	{request=IREQ_ERRSTAT;}
};

//------------------------------------------------------------------------------

struct	AudInfo : public CDComm
{
	UByte	inputchannelforch0;
	UByte	volcontrolforch0;

	UByte	inputchannelforch1;
	UByte	volcontrolforch1;

	UByte	inputchannelforch2;
	UByte	volcontrolforch2;

	UByte	inputchannelforch3;
	UByte	volcontrolforch3;

	AudInfo()	{request=IREQ_AUDINFO;}
};

//------------------------------------------------------------------------------

struct	DrvBytes : public CDComm
{
	UByte	bytesread;

	UByte	readbuffer[128];
	
	DrvBytes()	{request=IREQ_DRVBYTES;}
};

//------------------------------------------------------------------------------

struct	DevStat : public CDComm
{
	ULong	deviceparameters;
	
	DevStat()	{request=IREQ_DEVSTAT;}
};

//------------------------------------------------------------------------------

struct	SectSize : public CDComm
{
	UByte	readmode;
	UWord	sectorsize;
	
	SectSize()	{request=IREQ_SECTSIZE;readmode=0;}
};

//------------------------------------------------------------------------------

struct	VolSize : public CDComm
{
	ULong	volumesize;
	
	VolSize()	{request=IREQ_VOLSIZE;}
};

//------------------------------------------------------------------------------

struct	MedChng : public CDComm
{
	UByte	mediabyte;
	
	MedChng()	{request=IREQ_MEDCHNG;}
};

//------------------------------------------------------------------------------

struct	DiskInfo : public CDComm
{
	UByte	lowesttrackno;
	UByte	highesttrackno;
	ULong	leadouttrackstart;
	
	DiskInfo()	{request=IREQ_DISKINFO;}
};

//------------------------------------------------------------------------------

struct	TnoInfo : public CDComm
{
	UByte	trackno;
	ULong	trackstart;
	UByte	trackcontrolinfo;
	
	TnoInfo()	{request=IREQ_TNOINFO;}
};

//------------------------------------------------------------------------------

struct	QInfo : public CDComm
{
	UByte	CONTROLandADR;
	UByte	trackno;
	UByte	POINTorINDEX;

	UByte	runningtimemin;
	UByte	runningtimesec;
	UByte	runningtimeframe;
	UByte	runningtimezero;

	UByte	AMINorPMIN;
	UByte	ASECorPSEC;
	UByte	AFRAMEorPFRAME;
	
	QInfo()	{request=IREQ_QINFO;}
};

//------------------------------------------------------------------------------

struct	SubChanInfo : public CDComm
{
	ULong	sectorstart;
	ULong	transferaddress;
	ULong	sectorstoread;
	
	SubChanInfo()	{request=IREQ_SUBCHANINFO;}
};

//------------------------------------------------------------------------------

struct	UPCCode : public CDComm
{
	UByte	CONTROLandADR;
	UByte	UPC_EANcode[12];
	UByte	zero;
	UByte	aframe;
	
	UPCCode()	{request=IREQ_UPCCODE;}
};

//------------------------------------------------------------------------------

struct	AudStat : public CDComm
{
	UWord	audiostatus;
	ULong	lastplaynextresumestart;
	ULong	lastplaynextresumeend;
	
	AudStat()	{request=IREQ_AUDSTAT;}
};

//------------------------------------------------------------------------------

struct	RequestHeader
{
	UByte	length;			//length of record in bytes
	UByte	unit;			//unit number (block device only)
	UByte	function;		//function number
	UWord	status;			//status
	UByte	reserved[8];	//reserved
};

typedef	struct RequestHeader *RequestHeaderP;

struct	IOCTLI : public RequestHeader
{
	UByte	mediadescriptor;

	UWord	transferaddr_off,
			transferaddr_seg;		//ptr to one of the structures above

	UWord	bytestotransfer;

	UWord	startsector;

	ULong	requestedvol;

	IOCTLI()	{	mediadescriptor=0;
					startsector=0;
					requestedvol=0;
					unit=0;
					length=sizeof(IOCTLI);
					function=0x3;}
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

struct	Eject : public CDComm
{
	Eject()	{request=OREQ_EJECTDISK;}
};

//------------------------------------------------------------------------------

struct	LockDoor : public CDComm
{
	UByte	lockfunction;

	LockDoor()	{request=OREQ_LOCKUNLOCKDOOR;}
};

//------------------------------------------------------------------------------

struct	ResetDrv : public CDComm
{
	ResetDrv()	{request=OREQ_RESETDRIVE;}
};

//------------------------------------------------------------------------------

struct	AudInfo2 : public CDComm
{
	UByte	inputchannelforch0;
	UByte	volumecontrolforch0;

	UByte	inputchannelforch1;
	UByte	volumecontrolforch1;

	UByte	inputchannelforch2;
	UByte	volumecontrolforch2;

	UByte	inputchannelforch3;
	UByte	volumecontrolforch3;

	AudInfo2()	{request=OREQ_AUDIOCHANNELCONTROL;}
};

//------------------------------------------------------------------------------

struct	DrvBytes2 : public CDComm
{
	UByte	writebuffer[128];

	DrvBytes2()	{request=OREQ_WRITECONTROLSTRING;}
};

//------------------------------------------------------------------------------

struct	CloseTray : public CDComm
{
	CloseTray()	{request=OREQ_CLOSETRAY;}
};

//------------------------------------------------------------------------------

struct	IOCTLO : public RequestHeader
{
	UByte	mediadescriptor;

	UWord	transferaddr_off,
			transferaddr_seg;		//ptr to one of the structures above

	UWord	bytestotransfer;

	UWord	startsector;

	ULong	requestedvol;

	IOCTLO()	{	mediadescriptor=0;
					startsector=0;
					requestedvol=0;
					unit=0;
					length=sizeof(IOCTLO);
					function=12;}
};

struct	SEEKREQ : public RequestHeader
{
	UByte	addressingmode;

	UWord	transferaddr_off,
			transferaddr_seg;

	UWord	noofsectorstoread;

	ULong	startsectorno;

	SEEKREQ()	{	addressingmode=0;		//HSG addressing mode - use logical block number
					transferaddr_seg=0;
					transferaddr_off=0;
					unit=0;
					length=sizeof(SEEKREQ);
					function=131;}
};

struct	READLONG : public RequestHeader
{
	UByte	addressingmode;

	UWord	transferaddr_off,
			transferaddr_seg;

	UWord	noofsectorstoread;

	ULong	startsectorno;

	UByte	readmode;

	UByte	interleavesize;

	UByte	interleaveskip;

	READLONG()	{	addressingmode=0;		//HSG addressing mode - use logical block number
					unit=0;
					readmode=0;
					interleavesize=0;
					interleaveskip=0;
					length=sizeof(READLONG);
					function=128;}
};

struct	READLPRE : public RequestHeader
{
	UByte	addressingmode;

	UWord	transferaddr_off,
			transferaddr_seg;

	UWord	noofsectorstoread;

	ULong	startsectorno;

	UByte	readmode;

	UByte	interleavesize;

	UByte	interleaveskip;

	READLPRE()	{	addressingmode=0;		//HSG addressing mode - use logical block number
					transferaddr_seg=0;
					transferaddr_off=0;
					unit=0;
					readmode=0;
					interleavesize=0;
					interleaveskip=0;
					length=sizeof(READLPRE);
					noofsectorstoread=2;
					function=130;}
};

struct	dir_entry
{
	UByte	XAR_len;
	ULong	loc_extent;
	UWord	lb_size;
	ULong	data_len;
	UByte	record_time[7];
	UByte	file_flags;
	UByte	il_size;
	UByte	il_skip;
	UWord	VSSN;
	UByte	len_fi;
	UByte	file_id[38];
	UWord	file_version;
	UByte	len_su;
	UByte	su_data[220];
};

typedef	struct dir_entry DirEntry,*DirEntryP;


extern "C" void __FAR fileman__dosIRend();
extern "C" void __FAR fileman__dosIRcode();
extern "C" void __FAR fileman__dosIRstart();

extern "C" void __FAR fileman__DeviceHdrSeg();
extern "C" void __FAR fileman__DeviceHdrOff();

extern "C" void __FAR fileman__DriveLetter();

#endif
