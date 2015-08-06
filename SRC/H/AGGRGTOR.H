//------------------------------------------------------------------------------
//Filename       aggrgtor.h
//System         
//Author         Andy McMaster
//Date           Wed 29 Apr 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	AGGRGTOR_Included
#define	AGGRGTOR_Included

#define	DEFAULT_AGGRGTOR 0

#include	"DOSDefs.h"	
#include	"mytime.h"
#include	"myerror.h"
#include	"dplay.h"
#include	"winmove.h"
#include	"comms.h"
#include	"cbuffer.h"

class Aggregator {

public:
	Aggregator::Aggregator();
	Aggregator::~Aggregator();

	void 	AggregatorGetPackets(Bool reset,Bool timercall);
	Bool	CreateAggregator();
	Bool	ConnectToAggregator(ULong& aggregatorID,char* Name);
	void	RunAggregator();
	void	ServerGetPackets(Bool reset);
	Bool	Running;
	void	StopResetAggregator();
	UByte	GetAggFrameCount();
//DeadCode AMM 21Aug98  	void	InitRecBits();

	static int	inaggregator;

private:
//	static	AGGSENDPACKET	allpackets;
//	static	ACPACKET		storepack[MAXPLAYERS];
	bool	ResetFlag;
	UByte	AggFrameCount;	// aggregators frame count
	void	SetAcks(LPAGGSENDPACKET packet);

	CBuffer<AGGBUFF,BUFFERLENGTH> AggBuffer;

// if we receive 2 packets from one player within 1 frame cycle, need to store the 2nd one
// for the next frame. As we have to receive all messages to aggregator at once must buffer
// any bursts of packets.

	CBuffer<ACPACKET, BUFFERLENGTH> ReservePackets[MAXPLAYERS];

	void	InitAggArrayBuffer(LPAGGSENDPACKET pack);
	void	InitAggregator();
 	ULong	RecBits;
	void	ResetAcks();
	void	CheckAck(UByte val, UByte count, UByte pos);
	void	InitReservePackets();
	void	UpdateAckBuffer();

	// 0=not resent, 1=resent 1/4 , 2=resent 1/2
	UByte	ResendStatus;
	UByte	ResendPacket;

	char*	AggPacketPtr;
	ULong	AggPacketLength;

	HRESULT	ReceiveMessage(char*&buf, ULong& buflen,ULong& from);

	bool	MakeAndSendPacket(LPAGGSENDPACKET, Bool);
	bool	ResendAggPacket();
};

extern Aggregator _Agg;


#endif
