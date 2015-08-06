/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

//------------------------------------------------------------------------------
//Filename       aggrgtor.cpp
//System         
//Author         Andy McMaster
//Date           Wed 29 Apr 1998
//Description    
//------------------------------------------------------------------------------
#include	"aggrgtor.h"
#include	"stdio.h"
#include	"comms.h"
#include	"stub3d.h"

//#define 	AGGLOGS
//#define		VERBOSE
//#define		AGGRESEND 50

//DeadCode AMM 15Apr99 int Aggregator::inaggregator=0;

extern void	AggTracer(char* str);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AggregatorGetPackets
//Author		Andy McMaster
//Date			Thu 20 Mar 1997
//
//
//Inputs		
//
//
//------------------------------------------------------------------------------
void Aggregator::AggregatorGetPackets(Bool reset, Bool timercall)
{
	LPACPACKET RecPacket;
 	HRESULT	res;
	ULong	n,m;
//DeadCode AMM 13May99 	myDPID	from,to;
	myDPID	from;
//DeadCode AMM 13May99 	DWORD	BufferLen,BufferSize;
	DWORD	BufferLen;
//DeadCode AMM 12May99 	char*	Buffer=new char[MAXCOMMSPACKETSIZE];;
//DeadCode AMM 13May99 	char*	Buffer=new char[2048];;
	char* Buffer;
	bool	SendResult;

	static Bool	buffer=FALSE;	// are all players synched. if so buffer packets
	static time=0;				// number of calls by timer, use to determine timeout
	static clearbuffertime=0;	// try to clear buffers by sending extra agg packets every other agg frame
	static AGGSENDPACKET allpackets;	// aggregated packet

#ifdef AGGLOGS	
	static ULong lasttime=timeGetTime();
	ULong ttime=timeGetTime();

	AggTracer("in ");

	if (!_DPlay.Host)
		_Error.SayAndQuit("Player processing packets to aggregator!!!!!");

	FILE* fp=fopen("aggspack.txt","at");

	if (timercall)
		fprintf(fp,"\nCALLED BY TIMER %d %d\n",ttime,(ttime-lasttime)/10);
	else
		fprintf(fp,"\nCALLED BY MESSAGE %d %d\n",ttime,(ttime-lasttime)/10);

	lasttime=ttime;
#endif

	if (reset || ResetFlag)
	{
// clear all packets for me

#ifdef AGGLOGS	
		fprintf(fp,"RESET aggregator\n");
#endif
//DeadCode AMM 13May99 		res=DP_OK;
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 		while (res==DP_OK)
//DeadCode AMM 13May99 		{
//DeadCode AMM 13May99 			to=_DPlay.aggID;
//DeadCode AMM 13May99 //DeadCode AMM 12May99 			BufferLen=BufferSize=MAXCOMMSPACKETSIZE;
//DeadCode AMM 13May99 			BufferLen=BufferSize=2048;
//DeadCode AMM 13May99 			res=_DPlay.lpDP4->Receive(0,&to,DPRECEIVE_TOPLAYER,Buffer,&BufferLen);
//DeadCode AMM 13May99 		}

		while (ReceiveMessage(Buffer,BufferLen,from)==DP_OK)
		{
		}

		ResendStatus=0;
		ResendPacket=0;
		InitAggregator();
		InitReservePackets();
		InitAggArrayBuffer(&allpackets);
		ResetAcks();
		time=0;
		clearbuffertime=0;
//		_DPlay.dodgytime=0;
		buffer=FALSE;
		ResetFlag=false;
	}
	else
	if (Running)
	{
// calls from timer are every 1/50 sec. Use to determine timeout

		if (timercall)
		{
			time++;
			clearbuffertime++;
//			_DPlay.dodgytime++;
		}

//DeadCode AMM 12May99 		BufferLen=MAXCOMMSPACKETSIZE;
		BufferLen=2048;

// get all packets from Q
		do
		{
//DeadCode AMM 13May99 			from=0;
//DeadCode AMM 13May99 			to=_DPlay.aggID;
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 			res=_DPlay.lpDP4->Receive(&from,&to,DPRECEIVE_TOPLAYER,Buffer,&BufferLen);

			res=ReceiveMessage(Buffer,BufferLen,from);

#ifdef AGGLOGS	
#ifdef VERBOSE
//DeadCode AMM 13May99 			if (res!=DP_OK && !timercall)
			if (res!=DP_OK && !timercall)
			{
				fprintf(fp,"got message interrupt but no message!!!!\n");
				fflush(fp);
			}
#endif
#endif
//DeadCode AMM 13May99 			if (res==DP_OK)
			if (res==DP_OK)
			{
				if (BufferLen==sizeof(ACPACKET))
				{
					for (n=0;n<MAXPLAYERS;n++)
					{
						if (DPlay::H2H_Player[n].dpid==from)
							break;
					}

					if (n!=MAXPLAYERS)
					{
// got a delta packet from player

						RecPacket=(LPACPACKET)Buffer;

#ifdef AGGLOGS	
						fprintf(fp,"Aggframe=%d : Received %d from %d\n",AggFrameCount,RecPacket->Count,from);
						fflush(fp);
#endif

// check for ack'ed packets 

						if (RecPacket->IDCode!=PIDC_DUMMYPACKET)
						{
							CheckAck(RecPacket->Ack1,RecPacket->Count,n);
							CheckAck(RecPacket->Ack2,RecPacket->Count,n);
							UpdateAckBuffer();
						}

// put packet in buffer

// check packets in buffer and only add to buffer if this packet number 
// has not already been received - should get rid of huge number of resent packets problem...

						Bool add=TRUE;
						ULong p=0;

						if (ReservePackets[n].NumEntries())
						{
//DeadCode AMM 22Dec98 							ReservePackets[n].SetTemp();
							ReservePackets[n].SetTempCurr();
							do
							{
								if (ReservePackets[n].GetTemp()->Count==RecPacket->Count
								&& ReservePackets[n].GetTemp()->IDCode!=PIDC_PACKETERROR)
								{
									add=FALSE;
	#ifdef AGGLOGS	
									fprintf(fp,"IGNORE - packet already in buffer\n");
	#endif
									p++;
									break;
								}
								ReservePackets[n].UpdateTemp();
							}
							while (ReservePackets[n].GetTemp()!=ReservePackets[n].GetNext());
						}

						if (add)
						{
// if reserves are full then overwrite oldest packet. If this causes a problem then
// a player will have to initiate a resynch

							if (ReservePackets[n].NumEntries()==BUFFERLENGTH)
							{
								ReservePackets[n].GetCurr()->IDCode=PIDC_PACKETERROR;
								ReservePackets[n].UpdateCurr();
#ifdef AGGLOGS	
								fprintf(fp,"BUFFER FULL - overwrite old entry ");
#endif
							}

							_DPlay.CopyBuffer((char*)ReservePackets[n].GetNext(),Buffer,BufferLen);
							ReservePackets[n].AddEntryAndUpdateNext();
#ifdef AGGLOGS	
							fprintf(fp,"BUFFER packet (entries=%d)\n",ReservePackets[n].NumEntries());
#endif
						}

//						if (ReservePackets[n].NumEntries()>=BUFFERLENGTH)
//							_Error.SayAndQuit("reserve packets>BUFLEN slot %d",n);

					}
					else
					{
// who cares - not a player
#ifdef AGGLOGS
						if (from==0)
							fprintf(fp,"system message ignored (of acpacket size!!)\n");
						else
							fprintf(fp,"acpacket from illegal player ignored\n");
#endif
					}
				}
				else
				{
// who cares - not a delta packet
// need to check for resync init

#ifdef AGGLOGS	
					fprintf(fp,"Non-delta packet from %d size=%d\n",from,BufferLen);
#endif
					if (from==0)
					{
// ignore system message
					}
					else
					{
						PCOMMONDATA pack=(PCOMMONDATA)Buffer;

						if (pack->PacketID==PID_NEEDRESYNC)
						{
// resync has occurred. Stop aggregator and reset (just in case reset doesnt arrive!!)

// clear all packets for me

#ifdef AGGLOGS	
							fprintf(fp,"RESET aggregator from PID_NEEDRESYNC\n");
#endif

							while (ReceiveMessage(Buffer,BufferLen,from)==DP_OK)
							{
							}
//DeadCode AMM 13May99 							res=DP_OK;
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 							while (res==DP_OK)
//DeadCode AMM 13May99 							{
//DeadCode AMM 13May99 								to=_DPlay.aggID;
//DeadCode AMM 13May99 //DeadCode AMM 12May99 								BufferLen=BufferSize=MAXCOMMSPACKETSIZE;
//DeadCode AMM 13May99 								BufferLen=BufferSize=2048;
//DeadCode AMM 13May99 								res=_DPlay.lpDP4->Receive(0,&to,DPRECEIVE_TOPLAYER,Buffer,&BufferLen);
//DeadCode AMM 13May99 							}

							buffer=FALSE;
							InitAggregator();
							InitReservePackets();
							InitAggArrayBuffer(&allpackets);
							ResetAcks();
							time=0;
						}
						else
						{
// ignore non resync 
						}
					}
				}
//DeadCode AMM 13May99 				BufferLen=BufferSize;
			}
//DeadCode AMM 13May99 			else
//DeadCode AMM 13May99 			{
//DeadCode AMM 13May99 // problem receiving packet. Check buffer is not too small as we need to get
//DeadCode AMM 13May99 // all messages off Q
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 				n=2;
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 				while (res==DPERR_BUFFERTOOSMALL && n<16) // lets not get too carried away with memory allocation!!!!
//DeadCode AMM 13May99 														  // anything bigger than 16K is stupid 	
//DeadCode AMM 13May99 				{
//DeadCode AMM 13May99 					to=_DPlay.aggID;
//DeadCode AMM 13May99 					from=0;
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 					delete [] Buffer;
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 //DeadCode AMM 12May99 					BufferLen=BufferSize=MAXCOMMSPACKETSIZE*n;
//DeadCode AMM 13May99 //DeadCode AMM 12May99 					Buffer=new char[MAXCOMMSPACKETSIZE*n++];
//DeadCode AMM 13May99 					BufferLen=BufferSize=2048*n;
//DeadCode AMM 13May99 					Buffer=new char[2048*n++];
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 					res=_DPlay.lpDP4->Receive(&from,&to,DPRECEIVE_PEEK|DPRECEIVE_TOPLAYER,Buffer,&BufferLen);
//DeadCode AMM 13May99 				}
//DeadCode AMM 13May99 			}
//DeadCode AMM 13May99 		}
//DeadCode AMM 13May99 		while (res==DP_OK);
		}
		while (res==DP_OK);

#ifdef AGGLOGS
		if (res!=DPERR_NOMESSAGES)
			fprintf(fp,"(NOT no messages!) res=%d\n",res);
#endif
//		AggTracer("collected packets ");
// OK, see who we need a packet from and check buffer

		ULong oldrecbits;

		do
		{
#ifdef AGGLOGS	
#ifdef VERBOSE
			fprintf(fp,"SEND LOOP\n");
#endif
#endif
			for (n=0;n<MAXPLAYERS;n++)
			{
				if (!(RecBits&(1<<n)) && ReservePackets[n].NumEntries()>0)
				{
	// if we havent got a packet for this player yet and there is one in buffer......

					RecPacket=ReservePackets[n].GetCurr();
							
	#ifdef AGGLOGS	
#ifdef VERBOSE
					fprintf(fp,"GOT %d from buffer\n",RecPacket->Count);
	#endif
	#endif

	// wahay, a needed packet...maybe

	//				if (RecPacket->IDCode==PIDC_DUMMYPACKET && !buffer)
					if (!buffer)
					{
	// still require dummy/init packets in frame order

						Bool gotOK=FALSE;

						do
						{
							RecPacket=ReservePackets[n].GetCurr();

							if (RecPacket->Count==AggFrameCount)
							{
	// if we have found packet for this frame copy and continue

								RecBits|=(1<<n);
	#ifdef AGGLOGS	
#ifdef VERBOSE
								fprintf(fp,"DUMMY from %d put in slot %d\n",from,n);
	#endif
	#endif
								_DPlay.CopyBuffer((char*)&allpackets.player[n],(char*)RecPacket,sizeof(ACPACKET));

								gotOK=TRUE;
							}
							else
							{
	// if this packet is wrong check buffer until dummy/init packets are exhausted

	#ifdef AGGLOGS	
#ifdef VERBOSE
								fprintf(fp,"JUNK dummy from %d\n",from);
	#endif
	#endif
//DeadCode AMM 22Dec98 								ReservePackets[n].SetTemp();
								ReservePackets[n].SetTempCurr();
								ReservePackets[n].UpdateTemp();

								if (ReservePackets[n].GetTemp()->IDCode==PIDC_DUMMYPACKET
								|| ReservePackets[n].GetTemp()->IDCode==PIDC_INITPACK)
								{
									ReservePackets[n].GetCurr()->IDCode=PIDC_PACKETERROR;
									ReservePackets[n].UpdateCurr();
								}
								else
								{
	// no more dummy packets
									gotOK=TRUE;
								}
							}
						}
						while (!gotOK);
					}
					else
					{
	// we are in 'real packet mode' dont care what frame count on packet is......

						RecBits|=(1<<n);
	#ifdef AGGLOGS	
#ifdef VERBOSE
						fprintf(fp,"REAL from %d put in slot %d\n",from,n);
	#endif
	#endif
						_DPlay.CopyBuffer((char*)&allpackets.player[n],(char*)RecPacket,sizeof(ACPACKET));

//DeadCode AMM 07Jul99 	// determine if resend is necessary
//DeadCode AMM 07Jul99 	// how many frames 50?
//DeadCode AMM 07Jul99 // resend on 1/4 and 1/2 buffer length
//DeadCode AMM 07Jul99 
//DeadCode AMM 07Jul99 						SWord rec,cur;
//DeadCode AMM 07Jul99 
//DeadCode AMM 07Jul99 //DeadCode AMM 16Feb99 						rec=RecPacket->Count;
//DeadCode AMM 07Jul99 						ReservePackets[n].SetTempNext();
//DeadCode AMM 07Jul99 						ReservePackets[n].TempPrev();
//DeadCode AMM 07Jul99 						rec=ReservePackets[n].GetTemp()->Count;//AMM 16Feb99
//DeadCode AMM 07Jul99 						cur=AggBuffer.GetCurr()->aggpack.player[n].Count;
//DeadCode AMM 07Jul99 
//DeadCode AMM 07Jul99 	//DeadCode AMM 01Dec98 					if (((rec-cur>50) || (rec<cur && abs(rec-cur)>50)))
//DeadCode AMM 07Jul99 //DeadCode AMM 12Mar99 						if (false && ((rec-cur>AGGRESEND) || (rec<cur && abs(rec-cur)<(256-AGGRESEND))))
//DeadCode AMM 07Jul99 //DeadCode AMM 12Mar99 						if (((rec-cur>AGGRESEND) || (rec<cur && abs(rec-cur)<(256-AGGRESEND))))
//DeadCode AMM 07Jul99 						if (cur!=ResendPacket)
//DeadCode AMM 07Jul99 						{
//DeadCode AMM 07Jul99 							ResendPacket=cur;
//DeadCode AMM 07Jul99 							ResendStatus=0;
//DeadCode AMM 07Jul99 						}
//DeadCode AMM 07Jul99 
//DeadCode AMM 07Jul99 						if	(
//DeadCode AMM 07Jul99 								(		
//DeadCode AMM 07Jul99 									((rec-cur>BUFFERLENGTH/4)
//DeadCode AMM 07Jul99 									|| (rec<cur && abs(rec-cur)<(256-BUFFERLENGTH/4)))
//DeadCode AMM 07Jul99 									&& ResendStatus==0	 
//DeadCode AMM 07Jul99 								)
//DeadCode AMM 07Jul99 		
//DeadCode AMM 07Jul99 							||
//DeadCode AMM 07Jul99 								(
//DeadCode AMM 07Jul99 									((rec-cur>BUFFERLENGTH/2)
//DeadCode AMM 07Jul99 									|| (rec<cur && abs(rec-cur)<(256-BUFFERLENGTH/2)))
//DeadCode AMM 07Jul99 									&& ResendStatus<2	 
//DeadCode AMM 07Jul99 								)
//DeadCode AMM 07Jul99 							)
//DeadCode AMM 07Jul99 						{
//DeadCode AMM 07Jul99 							if (AggBuffer.GetCurr()->aggpack.player[n].IDCode!=PIDC_PACKETERROR)
//DeadCode AMM 07Jul99 							{
//DeadCode AMM 07Jul99 								if (AggBuffer.NumEntries()>0)
//DeadCode AMM 07Jul99 								{
//DeadCode AMM 07Jul99 									ResendStatus++;
//DeadCode AMM 07Jul99 									HRESULT res;
//DeadCode AMM 07Jul99 									res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&((AggBuffer.GetCurr())->aggpack),sizeof(AGGSENDPACKET),0,0,NULL,NULL);
//DeadCode AMM 07Jul99 	#ifdef AGGLOGS	
//DeadCode AMM 07Jul99 #ifdef VERBOSE
//DeadCode AMM 07Jul99 						fprintf(fp,"RESEND packet %d rec=%d cur=%d slot0=%d slot1=%d\n",
//DeadCode AMM 07Jul99 							AggBuffer.GetCurr()->aggpack.Count,rec,cur,
//DeadCode AMM 07Jul99 							AggBuffer.GetCurr()->aggpack.player[0].Count,
//DeadCode AMM 07Jul99 							AggBuffer.GetCurr()->aggpack.player[1].Count);
//DeadCode AMM 07Jul99 
//DeadCode AMM 07Jul99 						if (AggBuffer.GetCurr()->Acks[0])
//DeadCode AMM 07Jul99 						{
//DeadCode AMM 07Jul99 							fprintf(fp,"GOTACK from slot0\n");
//DeadCode AMM 07Jul99 						}
//DeadCode AMM 07Jul99 						else
//DeadCode AMM 07Jul99 						{
//DeadCode AMM 07Jul99 							fprintf(fp,"NEEDACK from slot0\n");
//DeadCode AMM 07Jul99 						}
//DeadCode AMM 07Jul99 
//DeadCode AMM 07Jul99 						if (AggBuffer.GetCurr()->Acks[1])
//DeadCode AMM 07Jul99 						{
//DeadCode AMM 07Jul99 							fprintf(fp,"GOTACK from slot1\n");
//DeadCode AMM 07Jul99 						}
//DeadCode AMM 07Jul99 						else
//DeadCode AMM 07Jul99 						{
//DeadCode AMM 07Jul99 							fprintf(fp,"NEEDACK from slot1\n");
//DeadCode AMM 07Jul99 						}
//DeadCode AMM 07Jul99 #endif
//DeadCode AMM 07Jul99 	#endif
//DeadCode AMM 07Jul99 								}
//DeadCode AMM 07Jul99 							}
//DeadCode AMM 07Jul99 						}

//DeadCode DAW 09Jul99 // put back in again trying to get 8 player comms working
//DeadCode DAW 09Jul99 
//DeadCode DAW 09Jul99 	// determine if resend is necessary
//DeadCode DAW 09Jul99 	// how many frames 50?
//DeadCode DAW 09Jul99 // resend on 1/4 and 1/2 buffer length
//DeadCode DAW 09Jul99 
//DeadCode DAW 09Jul99 						SWord rec,cur;
//DeadCode DAW 09Jul99 
//DeadCode DAW 09Jul99 //DeadCode AMM 16Feb99 						rec=RecPacket->Count;
//DeadCode DAW 09Jul99 						ReservePackets[n].SetTempNext();
//DeadCode DAW 09Jul99 						ReservePackets[n].TempPrev();
//DeadCode DAW 09Jul99 						rec=ReservePackets[n].GetTemp()->Count;//AMM 16Feb99
//DeadCode DAW 09Jul99 						cur=AggBuffer.GetCurr()->aggpack.player[n].Count;
//DeadCode DAW 09Jul99 
//DeadCode DAW 09Jul99 	//DeadCode AMM 01Dec98 					if (((rec-cur>50) || (rec<cur && abs(rec-cur)>50)))
//DeadCode DAW 09Jul99 //DeadCode AMM 12Mar99 						if (false && ((rec-cur>AGGRESEND) || (rec<cur && abs(rec-cur)<(256-AGGRESEND))))
//DeadCode DAW 09Jul99 //DeadCode AMM 12Mar99 						if (((rec-cur>AGGRESEND) || (rec<cur && abs(rec-cur)<(256-AGGRESEND))))
//DeadCode DAW 09Jul99 						if (cur!=ResendPacket)
//DeadCode DAW 09Jul99 						{
//DeadCode DAW 09Jul99 							ResendPacket=cur;
//DeadCode DAW 09Jul99 							ResendStatus=0;
//DeadCode DAW 09Jul99 						}
//DeadCode DAW 09Jul99 
//DeadCode DAW 09Jul99 						if	(
//DeadCode DAW 09Jul99 								(		
//DeadCode DAW 09Jul99 									((rec-cur>BUFFERLENGTH/4)
//DeadCode DAW 09Jul99 									|| (rec<cur && abs(rec-cur)<(256-BUFFERLENGTH/4)))
//DeadCode DAW 09Jul99 									&& ResendStatus==0	 
//DeadCode DAW 09Jul99 								)
//DeadCode DAW 09Jul99 		
//DeadCode DAW 09Jul99 							||
//DeadCode DAW 09Jul99 								(
//DeadCode DAW 09Jul99 									((rec-cur>BUFFERLENGTH/2)
//DeadCode DAW 09Jul99 									|| (rec<cur && abs(rec-cur)<(256-BUFFERLENGTH/2)))
//DeadCode DAW 09Jul99 									&& ResendStatus<2	 
//DeadCode DAW 09Jul99 								)
//DeadCode DAW 09Jul99 							)
//DeadCode DAW 09Jul99 						{
//DeadCode DAW 09Jul99 							if (AggBuffer.GetCurr()->aggpack.player[n].IDCode!=PIDC_PACKETERROR)
//DeadCode DAW 09Jul99 							{
//DeadCode DAW 09Jul99 								if (AggBuffer.NumEntries()>0)
//DeadCode DAW 09Jul99 								{
//DeadCode DAW 09Jul99 									ResendStatus++;
//DeadCode DAW 09Jul99 									HRESULT res;
//DeadCode DAW 09Jul99 									res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&((AggBuffer.GetCurr())->aggpack),sizeof(AGGSENDPACKET),0,0,NULL,NULL);
//DeadCode DAW 09Jul99 	#ifdef AGGLOGS	
//DeadCode DAW 09Jul99 #ifdef VERBOSE
//DeadCode DAW 09Jul99 						fprintf(fp,"RESEND packet %d rec=%d cur=%d slot0=%d slot1=%d\n",
//DeadCode DAW 09Jul99 							AggBuffer.GetCurr()->aggpack.Count,rec,cur,
//DeadCode DAW 09Jul99 							AggBuffer.GetCurr()->aggpack.player[0].Count,
//DeadCode DAW 09Jul99 							AggBuffer.GetCurr()->aggpack.player[1].Count);
//DeadCode DAW 09Jul99 
//DeadCode DAW 09Jul99 						if (AggBuffer.GetCurr()->Acks[0])
//DeadCode DAW 09Jul99 						{
//DeadCode DAW 09Jul99 							fprintf(fp,"GOTACK from slot0\n");
//DeadCode DAW 09Jul99 						}
//DeadCode DAW 09Jul99 						else
//DeadCode DAW 09Jul99 						{
//DeadCode DAW 09Jul99 							fprintf(fp,"NEEDACK from slot0\n");
//DeadCode DAW 09Jul99 						}
//DeadCode DAW 09Jul99 
//DeadCode DAW 09Jul99 						if (AggBuffer.GetCurr()->Acks[1])
//DeadCode DAW 09Jul99 						{
//DeadCode DAW 09Jul99 							fprintf(fp,"GOTACK from slot1\n");
//DeadCode DAW 09Jul99 						}
//DeadCode DAW 09Jul99 						else
//DeadCode DAW 09Jul99 						{
//DeadCode DAW 09Jul99 							fprintf(fp,"NEEDACK from slot1\n");
//DeadCode DAW 09Jul99 						}
//DeadCode DAW 09Jul99 #endif
//DeadCode DAW 09Jul99 	#endif
//DeadCode DAW 09Jul99 								}
//DeadCode DAW 09Jul99 							}
//DeadCode DAW 09Jul99 						}
	//					ReservePackets[n].GetCurr()->IDCode=PIDC_PACKETERROR;
					}
					ReservePackets[n].GetCurr()->IDCode=PIDC_PACKETERROR;
					ReservePackets[n].UpdateCurr();
				}
			}

			//AggTracer("made packet ");

	// is it time to send packet

			oldrecbits=RecBits;

//if a player drops out then for this frame recbits may have that players
//bit set. If use >= then this doesnt matter!
// NO. need to be equal, its bits set not number of players
//DeadCode AMM 15Apr99 			if (time==_DPlay.RateDivider || RecBits==_DPlay.ActivePlayers)
//DeadCode DAW 09Jul99 			if (time==_DPlay.RateDivider || RecBits>=_DPlay.ActivePlayers)
			if (time==_DPlay.RateDivider || RecBits==_DPlay.ActivePlayers)
			{
				HRESULT res;
				if (time==_DPlay.RateDivider)
				{
					time=0;
//					_DPlay.dodgytime=0;
				}

	#ifdef AGGLOGS
				if (RecBits==_DPlay.ActivePlayers)
					fprintf(fp,"%d: got allpacks\n",AggFrameCount);
				else
					fprintf(fp,"%d: time out\n",AggFrameCount);
	#endif
				allpackets.Count=AggFrameCount;

				if (buffer)
				{
	// hey, if we're already synched dont send any agregated packets that are empty....

					if (RecBits!=0)
					{
//DeadCode AMM 07Jul99 						if (!_DPlay.dodgytime)
//DeadCode DAW 22Sep99 						res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&allpackets,sizeof(AGGSENDPACKET),0,0,NULL,NULL);
//DeadCode AMM 07Jul99 						else
//DeadCode AMM 07Jul99 							_DPlay.dodgytime=false;

						SendResult=MakeAndSendPacket(&allpackets,buffer);

//DeadCode DAW 22Sep99 	// copy sent packet into buffer
//DeadCode DAW 22Sep99 
//DeadCode DAW 22Sep99 	// if we have filled up sent buffer then overwrite last entry.
//DeadCode DAW 22Sep99 	// If packet has really not been received by a player then it will cause them to 
//DeadCode DAW 22Sep99 	// initaite a resynch quite soon....!!!!
//DeadCode DAW 22Sep99 
//DeadCode DAW 22Sep99 						if (AggBuffer.NumEntries()==BUFFERLENGTH)
//DeadCode DAW 22Sep99 						{
//DeadCode DAW 22Sep99 							ResetAcks();
//DeadCode DAW 22Sep99 							AggBuffer.UpdateCurr();
//DeadCode DAW 22Sep99 							UpdateAckBuffer();
//DeadCode DAW 22Sep99 						}

						SetAcks(&allpackets);
//DeadCode DAW 22Sep99 						_DPlay.CopyBuffer( (char*)&(AggBuffer.GetNext()->aggpack),(char*)&allpackets,sizeof(AGGSENDPACKET));

//DeadCode AMM 28Jan99 						SetAcks(&allpackets);
						AggBuffer.AddEntryAndUpdateNext();

	#ifdef AGGLOGS
#ifdef VERBOSE
//DeadCode DAW 22Sep99 						if (!res || res==DPERR_PENDING)
//DeadCode AMM 07Jul99 							fprintf(fp,"sent and buffered %d OK\n",AggFrameCount);
						if (SendResult)
							fprintf(fp,"sent and buffered %d OK p0=%d p1=%d\n",AggFrameCount,
								allpackets.player[0].Count,allpackets.player[1].Count);
						else
							fprintf(fp,"error sending %d\n",AggFrameCount);
	#endif
#endif

//DeadCode AMM 14Dec98 						if (AggBuffer.NumEntries()>BUFFERLENGTH)
//DeadCode AMM 14Dec98 							_Error.SayAndQuit("AckPackEntries>BUFFERLENGTH (should never happen!)");
					}
					else
					{
#ifdef AGGLOGS
						fprintf(fp,"EMPTY AGG PACKET\n");
#endif
					}
				}
				else
				{
	// not synched yet, gotta send every 1/50th - even empty packets

//DeadCode DAW 22Sep99 					res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&allpackets,sizeof(AGGSENDPACKET),0,0,NULL,NULL);
					SendResult=MakeAndSendPacket(&allpackets,buffer);
					
	#ifdef AGGLOGS
#ifdef VERBOSE
//DeadCode DAW 22Sep99 					if (!res || res==DPERR_PENDING)
					if (SendResult)
			  			fprintf(fp,"sent %d OK\n",AggFrameCount);
					else
			  			fprintf(fp,"error sending %d\n",AggFrameCount);
	#endif
#endif
					m=0;
					for (n=0;n<MAXPLAYERS;n++)
					{
						if (allpackets.player[n].IDCode==PIDC_INITPACK)
						{
							m++;
						}
 					}

					if (m==_DPlay.CurrPlayers)
					{
	#ifdef AGGLOGS
						fprintf(fp,"EVERYBODY IS READY- START BUFFERS!!!\n",n);
	#endif
						buffer=TRUE;
//DeadCode AMM 16Feb99 						time=0;
						//AggTracer("init period ended\n");
					}
				}

				RecBits=0;
				AggFrameCount++;
//DeadCode AMM 08Jul99 				if (!AggFrameCount)
//DeadCode AMM 08Jul99 					AggFrameCount=1;

// when all players are synched and acking packets, treat AggFrame 0 as an empty packet
// so that when a player sends ack 0 it doesnt update buffers

				if (buffer && !AggFrameCount)
					AggFrameCount=1;

				InitAggArrayBuffer(&allpackets);
			}
		}
		while (oldrecbits==_DPlay.ActivePlayers && buffer);

		if (buffer)
		{
// only resend packets or clear buffers if we are REAL game mode, not whilst
// in resync!!!!!!!!!!!!!


	// took out to get 8 player network going


	// determine if resend is necessary 

			ULong num=AggBuffer.NumEntries();

			if (ResendPacket!=AggBuffer.GetCurr()->aggpack.Count)
			{
				ResendPacket=AggBuffer.GetCurr()->aggpack.Count;
				ResendStatus=0;
			}

			if ((num>BUFFERLENGTH/4 && ResendStatus==0)
			|| (num>BUFFERLENGTH/2 && ResendStatus<2))	 
			{
				ResendStatus++;
				HRESULT res;
//DeadCode DAW 22Sep99 				res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&((AggBuffer.GetCurr())->aggpack),sizeof(AGGSENDPACKET),0,0,NULL,NULL);
				SendResult=ResendAggPacket();
	#ifdef AGGLOGS	
	#ifdef VERBOSE
				SWord rec=ReservePackets[0].GetTemp()->Count;
				SWord cur=AggBuffer.GetCurr()->aggpack.player[0].Count;
	//DeadCode AMM 06Jul99 			fprintf(fp,"RESEND packet %d rec=%d cur=%d slot0=%d slot1=%d\n",
				fprintf(fp,"RESEND packet %d num=%d rs=%d slot0=%d slot1=%d\n",
					AggBuffer.GetCurr()->aggpack.Count,num,ResendStatus,
					AggBuffer.GetCurr()->aggpack.player[0].Count,
					AggBuffer.GetCurr()->aggpack.player[1].Count);

				if (AggBuffer.GetCurr()->Acks[0])
				{
					fprintf(fp,"GOTACK from slot0\n");
				}
				else
				{
					fprintf(fp,"NEEDACK from slot0\n");
				}

				if (AggBuffer.GetCurr()->Acks[1])
				{
					fprintf(fp,"GOTACK from slot1\n");
				}
				else
				{
					fprintf(fp,"NEEDACK from slot1\n");
				}
	#endif
	#endif
			}
			else if (clearbuffertime==((_DPlay.RateDivider*2)-(_DPlay.RateDivider/2)))
			{
	// in between every other agg packet

	#ifdef AGGLOGS	
	#ifdef VERBOSE
				fprintf(fp,"bufsize=%d curr=%d\n",num,AggBuffer.GetCurr()->aggpack.Count);
	#endif
	#endif
	// if not resending a packet check if buffers have any entries and if so try 
	// and clear by sending an extra packet a frame.

//DeadCode DAW 22Sep99 				ULong total=0;

				for (n=0;n<MAXPLAYERS;n++)
				{
//DeadCode DAW 22Sep99 			 		if (ReservePackets[n].NumEntries())
			 		if (ReservePackets[n].NumEntries() && !(RecBits&1<<n))
					{
						RecPacket=ReservePackets[n].GetCurr();
	#ifdef AGGLOGS	
	#ifdef VERBOSE
						fprintf(fp,"GOT %d from buffer\n",RecPacket->Count);
	#endif
	#endif
						_DPlay.CopyBuffer((char*)&allpackets.player[n],(char*)RecPacket,sizeof(ACPACKET));
//DeadCode DAW 22Sep99 						total++;
						RecBits|=1<<n;
						ReservePackets[n].GetCurr()->IDCode=PIDC_PACKETERROR;
						ReservePackets[n].UpdateCurr();
					}
				}

//DeadCode DAW 22Sep99 				if (total)
				if (RecBits)
				{
	#ifdef AGGLOGS	
	#ifdef VERBOSE
					int total=1;
					fprintf(fp,"found %d packets to send as extra\n",total);
	#endif
	#endif
					allpackets.Count=AggFrameCount;
//DeadCode AMM 13Jan00 					AggFrameCount++;
//DeadCode AMM 13Jan00 					if (!AggFrameCount)
//DeadCode AMM 13Jan00 						AggFrameCount=1;

//DeadCode DAW 22Sep99 					res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&allpackets,sizeof(AGGSENDPACKET),0,0,NULL,NULL);
					SendResult=MakeAndSendPacket(&allpackets,buffer);

					AggFrameCount++;							//AMM 12Jan00
					if (!AggFrameCount)							//AMM 12Jan00
						AggFrameCount=1;						//AMM 12Jan00

					RecBits=0;
	#ifdef AGGLOGS
	#ifdef VERBOSE
//DeadCode DAW 22Sep99 					if (!res || res==DPERR_PENDING)
					if (SendResult)
						fprintf(fp,"sent and buffered %d OK p0=%d p1=%d\n",AggFrameCount,
							allpackets.player[0].Count,allpackets.player[1].Count);
					else
						fprintf(fp,"error sending %d\n",AggFrameCount);
	#endif
	#endif
					if (AggBuffer.NumEntries()==BUFFERLENGTH)
					{
						ResetAcks();
						AggBuffer.UpdateCurr();
						UpdateAckBuffer();
					}

					SetAcks(&allpackets);
//DeadCode DAW 22Sep99 					_DPlay.CopyBuffer((char*)&(AggBuffer.GetNext()->aggpack),(char*)&allpackets,sizeof(AGGSENDPACKET));
					AggBuffer.AddEntryAndUpdateNext();
					InitAggArrayBuffer(&allpackets);
				}
			}
		}
// took out to get 8 player network going

//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 // determine if resend is necessary 
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 		ULong num=AggBuffer.NumEntries();
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 		if (ResendPacket!=AggBuffer.GetCurr()->aggpack.Count)
//DeadCode AMM 08Jul99 		{
//DeadCode AMM 08Jul99 			ResendPacket=AggBuffer.GetCurr()->aggpack.Count;
//DeadCode AMM 08Jul99 			ResendStatus=0;
//DeadCode AMM 08Jul99 		}
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 		if ((num>BUFFERLENGTH/4 && ResendStatus==0)
//DeadCode AMM 08Jul99 		|| (num>BUFFERLENGTH/2 && ResendStatus<2))	 
//DeadCode AMM 08Jul99 		{
//DeadCode AMM 08Jul99 			ResendStatus++;
//DeadCode AMM 08Jul99 			HRESULT res;
//DeadCode AMM 08Jul99 			res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&((AggBuffer.GetCurr())->aggpack),sizeof(AGGSENDPACKET),0,0,NULL,NULL);
//DeadCode AMM 08Jul99 #ifdef AGGLOGS	
//DeadCode AMM 08Jul99 #ifdef VERBOSE
//DeadCode AMM 08Jul99 			SWord rec=ReservePackets[0].GetTemp()->Count;
//DeadCode AMM 08Jul99 			SWord cur=AggBuffer.GetCurr()->aggpack.player[0].Count;
//DeadCode AMM 08Jul99 //DeadCode AMM 06Jul99 			fprintf(fp,"RESEND packet %d rec=%d cur=%d slot0=%d slot1=%d\n",
//DeadCode AMM 08Jul99 			fprintf(fp,"RESEND packet %d num=%d rs=%d slot0=%d slot1=%d\n",
//DeadCode AMM 08Jul99 				AggBuffer.GetCurr()->aggpack.Count,num,ResendStatus,
//DeadCode AMM 08Jul99 				AggBuffer.GetCurr()->aggpack.player[0].Count,
//DeadCode AMM 08Jul99 				AggBuffer.GetCurr()->aggpack.player[1].Count);
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 			if (AggBuffer.GetCurr()->Acks[0])
//DeadCode AMM 08Jul99 			{
//DeadCode AMM 08Jul99 				fprintf(fp,"GOTACK from slot0\n");
//DeadCode AMM 08Jul99 			}
//DeadCode AMM 08Jul99 			else
//DeadCode AMM 08Jul99 			{
//DeadCode AMM 08Jul99 				fprintf(fp,"NEEDACK from slot0\n");
//DeadCode AMM 08Jul99 			}
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 			if (AggBuffer.GetCurr()->Acks[1])
//DeadCode AMM 08Jul99 			{
//DeadCode AMM 08Jul99 				fprintf(fp,"GOTACK from slot1\n");
//DeadCode AMM 08Jul99 			}
//DeadCode AMM 08Jul99 			else
//DeadCode AMM 08Jul99 			{
//DeadCode AMM 08Jul99 				fprintf(fp,"NEEDACK from slot1\n");
//DeadCode AMM 08Jul99 			}
//DeadCode AMM 08Jul99 #endif
//DeadCode AMM 08Jul99 #endif
//DeadCode AMM 08Jul99 		}
//DeadCode AMM 08Jul99 		else
//DeadCode AMM 08Jul99 		{
//DeadCode AMM 08Jul99 #ifdef AGGLOGS	
//DeadCode AMM 08Jul99 #ifdef VERBOSE
//DeadCode AMM 08Jul99 			fprintf(fp,"bufsize=%d curr=%d\n",num,AggBuffer.GetCurr()->aggpack.Count);
//DeadCode AMM 08Jul99 #endif
//DeadCode AMM 08Jul99 #endif
//DeadCode AMM 08Jul99 // if not resending a packet check if buffers have any entries and if so try 
//DeadCode AMM 08Jul99 // and clear by sending an extra packet a frame.
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 			ULong total=0;
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 			for (n=0;n<MAXPLAYERS;n++)
//DeadCode AMM 08Jul99 			{
//DeadCode AMM 08Jul99 			 	if (ReservePackets[n].NumEntries())
//DeadCode AMM 08Jul99 				{
//DeadCode AMM 08Jul99 					RecPacket=ReservePackets[n].GetCurr();
//DeadCode AMM 08Jul99 #ifdef AGGLOGS	
//DeadCode AMM 08Jul99 #ifdef VERBOSE
//DeadCode AMM 08Jul99 					fprintf(fp,"GOT %d from buffer\n",RecPacket->Count);
//DeadCode AMM 08Jul99 #endif
//DeadCode AMM 08Jul99 #endif
//DeadCode AMM 08Jul99 					_DPlay.CopyBuffer((char*)&allpackets.player[n],(char*)RecPacket,sizeof(ACPACKET));
//DeadCode AMM 08Jul99 					total++;
//DeadCode AMM 08Jul99 					ReservePackets[n].GetCurr()->IDCode=PIDC_PACKETERROR;
//DeadCode AMM 08Jul99 					ReservePackets[n].UpdateCurr();
//DeadCode AMM 08Jul99 				}
//DeadCode AMM 08Jul99 			}
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 			if (total)
//DeadCode AMM 08Jul99 			{
//DeadCode AMM 08Jul99 #ifdef AGGLOGS	
//DeadCode AMM 08Jul99 #ifdef VERBOSE
//DeadCode AMM 08Jul99 				fprintf(fp,"found %d packets to send as extra\n",total);
//DeadCode AMM 08Jul99 #endif
//DeadCode AMM 08Jul99 #endif
//DeadCode AMM 08Jul99 				allpackets.Count=AggFrameCount;
//DeadCode AMM 08Jul99 				AggFrameCount++;
//DeadCode AMM 08Jul99 				if (!AggFrameCount)
//DeadCode AMM 08Jul99 					AggFrameCount=1;
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 				res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&allpackets,sizeof(AGGSENDPACKET),0,0,NULL,NULL);
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 #ifdef AGGLOGS
//DeadCode AMM 08Jul99 #ifdef VERBOSE
//DeadCode AMM 08Jul99 				if (!res || res==DPERR_PENDING)
//DeadCode AMM 08Jul99 					fprintf(fp,"sent and buffered %d OK p0=%d p1=%d\n",AggFrameCount,
//DeadCode AMM 08Jul99 						allpackets.player[0].Count,allpackets.player[1].Count);
//DeadCode AMM 08Jul99 				else
//DeadCode AMM 08Jul99 					fprintf(fp,"error sending %d\n",AggFrameCount);
//DeadCode AMM 08Jul99 #endif
//DeadCode AMM 08Jul99 #endif
//DeadCode AMM 08Jul99 				if (AggBuffer.NumEntries()==BUFFERLENGTH)
//DeadCode AMM 08Jul99 				{
//DeadCode AMM 08Jul99 					ResetAcks();
//DeadCode AMM 08Jul99 					AggBuffer.UpdateCurr();
//DeadCode AMM 08Jul99 					UpdateAckBuffer();
//DeadCode AMM 08Jul99 				}
//DeadCode AMM 08Jul99 
//DeadCode AMM 08Jul99 				SetAcks(&allpackets);
//DeadCode AMM 08Jul99 				_DPlay.CopyBuffer((char*)&(AggBuffer.GetNext()->aggpack),(char*)&allpackets,sizeof(AGGSENDPACKET));
//DeadCode AMM 08Jul99 				AggBuffer.AddEntryAndUpdateNext();
//DeadCode AMM 08Jul99 				InitAggArrayBuffer(&allpackets);
//DeadCode AMM 08Jul99 			}
//DeadCode AMM 08Jul99 		}
//DeadCode AMM 08Jul99 
	}
	else
	{
// receive and junk all messages to aggregator as we are not ready for them yet!!!!

		while (ReceiveMessage(Buffer,BufferLen,from)==DP_OK)
		{
		}

//DeadCode AMM 13May99 		do 
//DeadCode AMM 13May99 		{
//DeadCode AMM 13May99 			from=0;
//DeadCode AMM 13May99 			to=_DPlay.aggID;
//DeadCode AMM 13May99 //DeadCode AMM 12May99 			BufferLen=MAXCOMMSPACKETSIZE;
//DeadCode AMM 13May99 			BufferLen=2048;
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 			res=_DPlay.lpDP4->Receive(&from,&to,DPRECEIVE_TOPLAYER,Buffer,&BufferLen);
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 			n=2;
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 //DeadCode AMM 12May99 			while (res==DPERR_BUFFERTOOSMALL && n<16)
//DeadCode AMM 13May99 			while (res==DPERR_BUFFERTOOSMALL)
//DeadCode AMM 13May99 			{
//DeadCode AMM 13May99 				to=_DPlay.aggID;
//DeadCode AMM 13May99 				from=0;
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 				delete [] Buffer;
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 //DeadCode AMM 12May99 				BufferLen=BufferSize=MAXCOMMSPACKETSIZE*n;
//DeadCode AMM 13May99 //DeadCode AMM 12May99 				Buffer=new char[MAXCOMMSPACKETSIZE*n++];
//DeadCode AMM 13May99 				BufferLen=BufferSize=2048*n;
//DeadCode AMM 13May99 				Buffer=new char[2048*n++];
//DeadCode AMM 13May99 
//DeadCode AMM 13May99 				res=_DPlay.lpDP4->Receive(&from,&to,DPRECEIVE_PEEK|DPRECEIVE_TOPLAYER,Buffer,&BufferLen);
//DeadCode AMM 13May99 			}
//DeadCode AMM 13May99 		}
//DeadCode AMM 13May99 		while (res==DP_OK);
	}
//DeadCode AMM 13May99 	delete [] Buffer;
	//LockExchange(&Aggregator::inaggregator,0);
#ifdef AGGLOGS
	fclose(fp);
	AggTracer("out\n");
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitAggArrayBuffer
//Author		Andy McMaster
//Date			Tue 25 Mar 1997
//
//Description	Initialises the aggregators array buffer to error values
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Aggregator::InitAggArrayBuffer(LPAGGSENDPACKET pack)
{
	ULong n;

	for(n=0;n<MAXPLAYERS;n++)
	{
		memset(&pack->player[n],0,sizeof(ACPACKET));
		pack->player[n].IDCode=PIDC_PACKETERROR;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ServerGetPackets
//Author		Andy McMaster
//Date			Mon 9 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Aggregator::ServerGetPackets(Bool reset)
{
//DeadCode AMM 17Aug98 	ACPACKET RecPacket;
//DeadCode AMM 17Aug98 	HRESULT	res;
//DeadCode AMM 17Aug98 	ULong	n;
//DeadCode AMM 17Aug98 	myDPID	from,to;
//DeadCode AMM 17Aug98 	DWORD	BufferLen;
//DeadCode AMM 17Aug98 	char	Buffer[1024];
//DeadCode AMM 17Aug98 	Bool	junkedpacket=FALSE;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	ULong thistime=Timer_Code.GetTime();
//DeadCode AMM 17Aug98 	static RecCount=0;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	static timetosendnextframe=0;
//DeadCode AMM 17Aug98 	static firstgo=TRUE;
//DeadCode AMM 17Aug98 	static Bool	buffer=FALSE;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	if (reset)
//DeadCode AMM 17Aug98 	{
//DeadCode AMM 17Aug98 // clear all packets for me
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		res=DP_OK;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		while (res==DP_OK)
//DeadCode AMM 17Aug98 		{
//DeadCode AMM 17Aug98 			to=_DPlay.aggID;
//DeadCode AMM 17Aug98 			BufferLen=1024;
//DeadCode AMM 17Aug98 			res=_DPlay.lpDP4->Receive(0,&to,DPRECEIVE_TOPLAYER,Buffer,&BufferLen);
//DeadCode AMM 17Aug98 		}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		_DPlay.CurrPlayers=_DPlay.NumAggPlayers;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		firstgo=TRUE;
//DeadCode AMM 17Aug98 		buffer=FALSE;
//DeadCode AMM 17Aug98 		return;
//DeadCode AMM 17Aug98 	}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	if (firstgo)
//DeadCode AMM 17Aug98 	{
//DeadCode AMM 17Aug98 		timetosendnextframe=thistime+(_DPlay.RateDivider*3)+6;
//DeadCode AMM 17Aug98 		firstgo=FALSE;
//DeadCode AMM 17Aug98 	}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	for(n=1;n<=_DPlay.NumAggPlayers;n++)
//DeadCode AMM 17Aug98 	{
//DeadCode AMM 17Aug98 		{
//DeadCode AMM 17Aug98 			from=0;
//DeadCode AMM 17Aug98 			to=_DPlay.aggID;
//DeadCode AMM 17Aug98 			BufferLen=1024;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 			res=_DPlay.lpDP4->Receive(&from,&to,DPRECEIVE_TOPLAYER|DPRECEIVE_PEEK,Buffer,&BufferLen);
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 			if(to==_DPlay.aggID)
//DeadCode AMM 17Aug98 			{
//DeadCode AMM 17Aug98 				if(res==DP_OK)
//DeadCode AMM 17Aug98 				{
//DeadCode AMM 17Aug98 					if(BufferLen==sizeof(ACPACKET))
//DeadCode AMM 17Aug98 					{
//DeadCode AMM 17Aug98 						res=_DPlay.lpDP4->Receive(&from,&to,DPRECEIVE_TOPLAYER,(LPVOID)&RecPacket,&BufferLen);
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 #ifdef AGGLOGS	
//DeadCode AMM 17Aug98 						FILE* fp2=fopen("aggspack.txt","at");
//DeadCode AMM 17Aug98 						fprintf(fp2,"Aggframe=%d : Received %d from %d\n",AggFrameCount,RecPacket.Count,from);
//DeadCode AMM 17Aug98 						fclose(fp2);
//DeadCode AMM 17Aug98 #endif
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 						if(RecPacket.IDCode==PIDC_PLAYERGONE)
//DeadCode AMM 17Aug98 						{
//DeadCode AMM 17Aug98 #ifdef AGGLOGS	
//DeadCode AMM 17Aug98 						FILE* fp5=fopen("aggspack.txt","at");
//DeadCode AMM 17Aug98 						fprintf(fp5,"RECEIVED PLAYERGONE from %d\n",from);
//DeadCode AMM 17Aug98 						fclose(fp5);
//DeadCode AMM 17Aug98 #endif
//DeadCode AMM 17Aug98 							RecCount++;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							allpackets.player[n-1].IDCode=RecPacket.IDCode;
//DeadCode AMM 17Aug98 							_DPlay.CurrPlayers--;
//DeadCode AMM 17Aug98 							if (_DPlay.CurrPlayers<1)
//DeadCode AMM 17Aug98 							{
//DeadCode AMM 17Aug98 								Running=FALSE;
//DeadCode AMM 17Aug98 								break;
//DeadCode AMM 17Aug98 							}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 						}
//DeadCode AMM 17Aug98 						else if (RecPacket.IDCode==PIDC_DUMMYPACKET)
//DeadCode AMM 17Aug98 						{
//DeadCode AMM 17Aug98 							if (RecPacket.Count==AggFrameCount)
//DeadCode AMM 17Aug98 							{
//DeadCode AMM 17Aug98 								RecCount++;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 								allpackets.player[n-1].Count=RecPacket.Count;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].Ack1=RecPacket.Ack1;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].Ack2=RecPacket.Ack2;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].Shift=RecPacket.Shift;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].Velocity=RecPacket.Velocity;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].X=RecPacket.X;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].Y=RecPacket.Y;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].Z=RecPacket.Z;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].Heading=RecPacket.Heading;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].Pitch=RecPacket.Pitch;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].Roll=RecPacket.Roll;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].IDCode=RecPacket.IDCode;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].byte1=RecPacket.byte1;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].byte2=RecPacket.byte2;
//DeadCode AMM 17Aug98 								allpackets.player[n-1].byte3=RecPacket.byte3;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							}
//DeadCode AMM 17Aug98 							else
//DeadCode AMM 17Aug98 							{
//DeadCode AMM 17Aug98 #ifdef AGGLOGS	
//DeadCode AMM 17Aug98 						FILE* fp6=fopen("aggspack.txt","at");
//DeadCode AMM 17Aug98 						fprintf(fp6,"PIDC_DUMMYPACKET frame=%d aggframe=%d from %d\n",RecPacket.Count,AggFrameCount,from);
//DeadCode AMM 17Aug98 						fclose(fp6);
//DeadCode AMM 17Aug98 #endif
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							}
//DeadCode AMM 17Aug98 						}
//DeadCode AMM 17Aug98 						else
//DeadCode AMM 17Aug98 						{
//DeadCode AMM 17Aug98 							RecCount++;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							allpackets.player[n-1].Count=RecPacket.Count;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].Ack1=RecPacket.Ack1;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].Ack2=RecPacket.Ack2;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].Shift=RecPacket.Shift;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].Velocity=RecPacket.Velocity;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].X=RecPacket.X;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].Y=RecPacket.Y;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].Z=RecPacket.Z;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].Heading=RecPacket.Heading;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].Pitch=RecPacket.Pitch;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].Roll=RecPacket.Roll;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].IDCode=RecPacket.IDCode;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].byte1=RecPacket.byte1;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].byte2=RecPacket.byte2;
//DeadCode AMM 17Aug98 							allpackets.player[n-1].byte3=RecPacket.byte3;
//DeadCode AMM 17Aug98 // check for ack'ed packets 
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							UByte offset1=0,offset2=0;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							if (RecPacket.Ack1!=0)
//DeadCode AMM 17Aug98 							{
//DeadCode AMM 17Aug98 								offset1=RecPacket.Count-RecPacket.Ack1;
//DeadCode AMM 17Aug98 							}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							if (RecPacket.Ack2!=0)
//DeadCode AMM 17Aug98 							{
//DeadCode AMM 17Aug98 								offset2=RecPacket.Count-RecPacket.Ack2;
//DeadCode AMM 17Aug98 							}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							LPAGGBUFF temp;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							if (RecPacket.Ack1!=0)
//DeadCode AMM 17Aug98 							{
//DeadCode AMM 17Aug98 #ifdef AGGLOGS	
//DeadCode AMM 17Aug98 								FILE* fpa2=fopen("aggspack.txt","at");
//DeadCode AMM 17Aug98 								fprintf(fpa2,"received ack for %d\n",offset1);
//DeadCode AMM 17Aug98 								fclose(fpa2);
//DeadCode AMM 17Aug98 #endif
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 								AggBuffer.SetTemp();
//DeadCode AMM 17Aug98 								while ((temp=AggBuffer.GetTemp())!=AggBuffer.GetNext())
//DeadCode AMM 17Aug98 								{
//DeadCode AMM 17Aug98 									if (temp->aggpack.player[n-1].Count==offset1)
//DeadCode AMM 17Aug98 									{
//DeadCode AMM 17Aug98 #ifdef AGGLOGS	
//DeadCode AMM 17Aug98 								FILE* fpa9=fopen("aggspack.txt","at");
//DeadCode AMM 17Aug98 								fprintf(fpa9,"found packet entry to ack1\n",offset1);
//DeadCode AMM 17Aug98 								fclose(fpa9);
//DeadCode AMM 17Aug98 #endif
//DeadCode AMM 17Aug98 										temp->Acks[n-1]=TRUE;
//DeadCode AMM 17Aug98 										break;
//DeadCode AMM 17Aug98 									}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 									AggBuffer.UpdateTemp();
//DeadCode AMM 17Aug98 								}
//DeadCode AMM 17Aug98 							}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							if (RecPacket.Ack2!=0)
//DeadCode AMM 17Aug98 							{
//DeadCode AMM 17Aug98 #ifdef AGGLOGS	
//DeadCode AMM 17Aug98 								FILE* fpa3=fopen("aggspack.txt","at");
//DeadCode AMM 17Aug98 								fprintf(fpa3,"received ack for %d\n",offset1);
//DeadCode AMM 17Aug98 								fclose(fpa3);
//DeadCode AMM 17Aug98 #endif
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 								AggBuffer.SetTemp();
//DeadCode AMM 17Aug98 								while ((temp=AggBuffer.GetTemp())!=AggBuffer.GetNext())
//DeadCode AMM 17Aug98 								{
//DeadCode AMM 17Aug98 									if (temp->aggpack.player[n-1].Count==offset2)
//DeadCode AMM 17Aug98 									{
//DeadCode AMM 17Aug98 #ifdef AGGLOGS	
//DeadCode AMM 17Aug98 								FILE* fpa8=fopen("aggspack.txt","at");
//DeadCode AMM 17Aug98 								fprintf(fpa8,"found packet entry to ack2\n",offset1);
//DeadCode AMM 17Aug98 								fclose(fpa8);
//DeadCode AMM 17Aug98 #endif
//DeadCode AMM 17Aug98 										temp->Acks[n-1]=TRUE;
//DeadCode AMM 17Aug98 										break;
//DeadCode AMM 17Aug98 									}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 									AggBuffer.SetTemp();
//DeadCode AMM 17Aug98 								}
//DeadCode AMM 17Aug98 							}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 // determine if resend is necessary
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							if (RecPacket.Count-AggBuffer.GetCurr()->aggpack.player[n-1].Count>10
//DeadCode AMM 17Aug98 							&& (AggBuffer.GetCurr()->aggpack.player[n-1].IDCode!=PIDC_PACKETERROR)
//DeadCode AMM 17Aug98 							&& (AggBuffer.NumEntries()>0))
//DeadCode AMM 17Aug98 							{
//DeadCode AMM 17Aug98 								_DPlay.lpDP4->Send(_DPlay.aggID,DPID_ALLPLAYERS,0,&AggBuffer.GetCurr()->aggpack,sizeof(AGGSENDPACKET));
//DeadCode AMM 17Aug98 #ifdef AGGLOGS	
//DeadCode AMM 17Aug98 								FILE* fpa4=fopen("aggspack.txt","at");
//DeadCode AMM 17Aug98 								fprintf(fpa4,"packet resend %d\n",AggBuffer.GetCurr()->aggpack.Count);
//DeadCode AMM 17Aug98 								fclose(fpa4);
//DeadCode AMM 17Aug98 #endif
//DeadCode AMM 17Aug98 							}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 						}
//DeadCode AMM 17Aug98 					}
//DeadCode AMM 17Aug98 					else
//DeadCode AMM 17Aug98 					{
//DeadCode AMM 17Aug98 						res=_DPlay.lpDP4->Receive(&from,&to,DPRECEIVE_TOPLAYER,(LPVOID)Buffer,&BufferLen);
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 						if (BufferLen==sizeof(CONTROLPACKET))
//DeadCode AMM 17Aug98 						{
//DeadCode AMM 17Aug98 							LPCONTROLPACKET pack=(LPCONTROLPACKET)(&Buffer);
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 							if (pack->opcode==254)
//DeadCode AMM 17Aug98 							{
//DeadCode AMM 17Aug98 								switch (pack->controlcode)
//DeadCode AMM 17Aug98 								{
//DeadCode AMM 17Aug98 									case 1:
//DeadCode AMM 17Aug98 										Running=TRUE;
//DeadCode AMM 17Aug98 										break;
//DeadCode AMM 17Aug98 						
//DeadCode AMM 17Aug98  									case 2:
//DeadCode AMM 17Aug98 										Running=FALSE;
//DeadCode AMM 17Aug98 										break;
//DeadCode AMM 17Aug98 								}
//DeadCode AMM 17Aug98 							}
//DeadCode AMM 17Aug98 						}
//DeadCode AMM 17Aug98 					}
//DeadCode AMM 17Aug98 				}
//DeadCode AMM 17Aug98 			}
//DeadCode AMM 17Aug98 		}
//DeadCode AMM 17Aug98 	}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	if(thistime>=timetosendnextframe || RecCount==_DPlay.CurrPlayers)
//DeadCode AMM 17Aug98 	{
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 // has everybody ack'ed oldest packet?
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		Bool update=TRUE;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		for (n=0;n<MAXPLAYERS;n++)
//DeadCode AMM 17Aug98 		{
//DeadCode AMM 17Aug98 			if (AggBuffer.GetCurr()->Acks[n]==FALSE)
//DeadCode AMM 17Aug98 			{
//DeadCode AMM 17Aug98 				update=FALSE;
//DeadCode AMM 17Aug98 				break;
//DeadCode AMM 17Aug98 			}
//DeadCode AMM 17Aug98 		}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		if (update)
//DeadCode AMM 17Aug98 		{
//DeadCode AMM 17Aug98 #ifdef AGGLOGS	
//DeadCode AMM 17Aug98 		FILE* fpa5=fopen("aggspack.txt","at");
//DeadCode AMM 17Aug98 		fprintf(fpa5,"update CurrAggPackPos %d=%d %d\n",
//DeadCode AMM 17Aug98 			AggBuffer.GetCurr()->aggpack.player[0].Count,
//DeadCode AMM 17Aug98 			AggBuffer.GetCurr()->aggpack.player[1].Count);
//DeadCode AMM 17Aug98 		fclose(fpa5);
//DeadCode AMM 17Aug98 #endif
//DeadCode AMM 17Aug98 			AggBuffer.UpdateCurr();
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 			if (AggBuffer.NumEntries()<0)
//DeadCode AMM 17Aug98 				_Error.SayAndQuit("AggPackEntries<0");
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 #ifdef AGGLOGS
//DeadCode AMM 17Aug98 		FILE* fp=fopen("aggspack.txt","at");
//DeadCode AMM 17Aug98 		if (RecCount==_DPlay.CurrPlayers)
//DeadCode AMM 17Aug98 		{
//DeadCode AMM 17Aug98 			fprintf(fp,"got allpacks %d %d\n",AggFrameCount,thistime);
//DeadCode AMM 17Aug98 			fprintf(fp,"thistime=%d timetosend=%d\n",thistime,timetosendnextframe);
//DeadCode AMM 17Aug98 		}
//DeadCode AMM 17Aug98 		else
//DeadCode AMM 17Aug98 		{
//DeadCode AMM 17Aug98 			fprintf(fp,"time out %d %d\n",AggFrameCount,thistime);
//DeadCode AMM 17Aug98 			fprintf(fp,"thistime=%d timetosend=%d\n",thistime,timetosendnextframe);
//DeadCode AMM 17Aug98 		}
//DeadCode AMM 17Aug98 		fclose(fp);
//DeadCode AMM 17Aug98 #endif
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		timetosendnextframe+=((_DPlay.RateDivider*3)+1);
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		allpackets.Count=AggFrameCount;
//DeadCode AMM 17Aug98 		_DPlay.lpDP4->Send(_DPlay.aggID,DPID_ALLPLAYERS,0,&allpackets,sizeof(AGGSENDPACKET));
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 // copy sent packet into buffer
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		if (buffer)
//DeadCode AMM 17Aug98 		{
//DeadCode AMM 17Aug98 			UByte *src,*dest;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 			src=(UByte*)&allpackets;
//DeadCode AMM 17Aug98 			dest=(UByte*)(&((AggBuffer.GetNext())->aggpack));
//DeadCode AMM 17Aug98 			n=sizeof(AGGSENDPACKET);
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 			while (n--)
//DeadCode AMM 17Aug98 			{
//DeadCode AMM 17Aug98 				*dest++=*src++;
//DeadCode AMM 17Aug98 			}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 			SetAcks(&allpackets);
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 			AggBuffer.AddEntry();
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 			if (AggBuffer.NumEntries()>BUFFERLENGTH)
//DeadCode AMM 17Aug98 				_Error.SayAndQuit("AckPackEntries>BUFFERLENGTH");
//DeadCode AMM 17Aug98 		}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		if (!buffer)
//DeadCode AMM 17Aug98 		{
//DeadCode AMM 17Aug98 			for (n=0;n<MAXPLAYERS;n++)
//DeadCode AMM 17Aug98 			{
//DeadCode AMM 17Aug98 				if (allpackets.player[n].IDCode==PIDC_INITPACK)
//DeadCode AMM 17Aug98 				{
//DeadCode AMM 17Aug98 					buffer=TRUE;
//DeadCode AMM 17Aug98 					break;
//DeadCode AMM 17Aug98 				}
//DeadCode AMM 17Aug98 			}
//DeadCode AMM 17Aug98 		}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		AggFrameCount++;
//DeadCode AMM 17Aug98 		InitAggArrayBuffer();
//DeadCode AMM 17Aug98 		RecCount=0;
//DeadCode AMM 17Aug98 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAcks
//Author		Andy McMaster
//Date			Wed 14 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Aggregator::SetAcks(LPAGGSENDPACKET packet)
{
	for (ULong n=0;n<MAXPLAYERS;n++)
	{
//DeadCode AMM 07Jul99 		if (packet->player[n].IDCode==PIDC_PACKETERROR)
//DeadCode AMM 07Jul99 			AggBuffer.GetNext()->Acks[n]=TRUE;
//DeadCode AMM 07Jul99 		else 
//DeadCode AMM 07Jul99 			AggBuffer.GetNext()->Acks[n]=FALSE;

// took out to get 8 player network going
//DeadCode AMM 08Jul99 // want acks from all active players for all packets thankyouverymuch
//DeadCode AMM 08Jul99 		if (_DPlay.ActivePlayers&1<<n)
//DeadCode AMM 08Jul99 			AggBuffer.GetNext()->Acks[n]=FALSE;
//DeadCode AMM 08Jul99 		else
//DeadCode AMM 08Jul99 			AggBuffer.GetNext()->Acks[n]=TRUE;
//DeadCode DAW 09Jul99 		if (packet->player[n].IDCode==PIDC_PACKETERROR)
//DeadCode DAW 09Jul99 			AggBuffer.GetNext()->Acks[n]=TRUE;
//DeadCode DAW 09Jul99 		else 
//DeadCode DAW 09Jul99 			AggBuffer.GetNext()->Acks[n]=FALSE;
// want acks from all active players for all packets thankyouverymuch
			if (_DPlay.ActivePlayers&1<<n)
				AggBuffer.GetNext()->Acks[n]=FALSE;
			else
				AggBuffer.GetNext()->Acks[n]=TRUE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateAggregator
//Author		Andy McMaster
//Date			Mon 9 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Aggregator::CreateAggregator()
{
//DeadCode AMM 17Aug98 	HRESULT res;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	memset(&_DPlay.DPSessionDesc2, 0x00, sizeof(DPSESSIONDESC2));
//DeadCode AMM 17Aug98 	_DPlay.DPSessionDesc2.dwSize = sizeof (DPSESSIONDESC2);
//DeadCode AMM 17Aug98 	_DPlay.DPSessionDesc2.dwMaxPlayers = MAXPLAYERS+1;	 // allow for aggregator
//DeadCode AMM 17Aug98 	_DPlay.DPSessionDesc2.guidApplication=*_DPlay.lpAppGuid;				
//DeadCode AMM 17Aug98 	_DPlay.DPSessionDesc2.dwCurrentPlayers=0;
//DeadCode AMM 17Aug98 	_DPlay.DPSessionDesc2.lpszSessionNameA=new char[20];
//DeadCode AMM 17Aug98 	strcpy( _DPlay.DPSessionDesc2.lpszSessionNameA, "Aggregator");
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 //	Whole_Screen->EnableGUI (TRUE);
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 //DeadCode AMM 16Jul98 	_DPlay.InCommsStartup=TRUE;
//DeadCode AMM 17Aug98 	res=_DPlay.lpDP4->Open(&_DPlay.DPSessionDesc2,DPOPEN_CREATE);
//DeadCode AMM 17Aug98 //DeadCode AMM 16Jul98 	_DPlay.InCommsStartup=FALSE;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	if (res!=DP_OK)
//DeadCode AMM 17Aug98 		return FALSE;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	_DPlay.NextGameID=1;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	if (_DPlay.lpDP4->CreatePlayer ( &_DPlay.aggID, NULL, NULL, NULL,0,0) != DP_OK)
//DeadCode AMM 17Aug98 		return FALSE;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	_DPlay.myDPlayID=_DPlay.aggID;
//DeadCode AMM 17Aug98 	_DPlay.myGameID=0;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	_DPlay.InitBuffers();
//DeadCode AMM 17Aug98 
	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RunAggregator
//Author		Andy McMaster
//Date			Mon 9 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Aggregator::RunAggregator()
{
//DeadCode AMM 17Aug98 	char Buffer[1024];
//DeadCode AMM 17Aug98 	ULong BufLen=1024;
//DeadCode AMM 17Aug98 	Bool	exit=FALSE;
//DeadCode AMM 17Aug98 	ULong from;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 //DeadCode AMM 29Apr98 	DPSessionDesc2.dwFlags%=DPSESSION_NEWPLAYERSDISABLED;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 	while (!exit)
//DeadCode AMM 17Aug98 	{
//DeadCode AMM 17Aug98 		BufLen=1024;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 		if (Running)
//DeadCode AMM 17Aug98 		{
//DeadCode AMM 17Aug98 			ServerGetPackets(FALSE);
//DeadCode AMM 17Aug98 		}
//DeadCode AMM 17Aug98 		else
//DeadCode AMM 17Aug98 		{
//DeadCode AMM 17Aug98 // receive control messages
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 //DeadCode AMM 07Aug98 			while (_DPlay.UIGetMyNonSysMessage(Buffer, BufLen))
//DeadCode AMM 17Aug98 			while (_DPlay.ReceiveNextMessage(Buffer, BufLen,from))
//DeadCode AMM 17Aug98 			{
//DeadCode AMM 17Aug98 				if (from==0)
//DeadCode AMM 17Aug98 				{
//DeadCode AMM 17Aug98 // do I really care????
//DeadCode AMM 17Aug98 				}
//DeadCode AMM 17Aug98 				else
//DeadCode AMM 17Aug98 				if (BufLen==sizeof(ACPACKET))
//DeadCode AMM 17Aug98 				{
//DeadCode AMM 17Aug98 // if we receive a players delta packet then start aggregating
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 					ServerGetPackets(TRUE);
//DeadCode AMM 17Aug98 					Running=TRUE;
//DeadCode AMM 17Aug98 					break;
//DeadCode AMM 17Aug98 				}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 				else
//DeadCode AMM 17Aug98 				if (BufLen==sizeof(CONTROLPACKET))
//DeadCode AMM 17Aug98 				{
//DeadCode AMM 17Aug98 					LPCONTROLPACKET pack=(LPCONTROLPACKET)(&Buffer);
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 					if (pack->opcode==254)
//DeadCode AMM 17Aug98 					{
//DeadCode AMM 17Aug98 						switch (pack->controlcode)
//DeadCode AMM 17Aug98 						{
//DeadCode AMM 17Aug98 							case 1:
//DeadCode AMM 17Aug98 								ServerGetPackets(TRUE);
//DeadCode AMM 17Aug98 								Running=TRUE;
//DeadCode AMM 17Aug98 								break;
//DeadCode AMM 17Aug98 						
//DeadCode AMM 17Aug98  							case 2:
//DeadCode AMM 17Aug98 								Running=FALSE;
//DeadCode AMM 17Aug98 								break;
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 						}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 					}
//DeadCode AMM 17Aug98 				}
//DeadCode AMM 17Aug98 				else if (BufLen==sizeof(UIPLAYERDATA))
//DeadCode AMM 17Aug98 				{
//DeadCode AMM 17Aug98 					PUIPLAYERDATA pUIPlayerData = (PUIPLAYERDATA)(&Buffer);
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 					if (pUIPlayerData->PacketID==PID_REQUESTGAMEID)
//DeadCode AMM 17Aug98 					{
//DeadCode AMM 17Aug98 				 		_DPlay.SendGameID(pUIPlayerData->PlayerID,_DPlay.NextGameID);
//DeadCode AMM 17Aug98 						_DPlay.NumAggPlayers++;
//DeadCode AMM 17Aug98 						_DPlay.NextGameID++;
//DeadCode AMM 17Aug98 					}
//DeadCode AMM 17Aug98 					else if (pUIPlayerData->PacketID==PID_PLAYERQUIT)
//DeadCode AMM 17Aug98 					{
//DeadCode AMM 17Aug98 						_DPlay.NextGameID--;
//DeadCode AMM 17Aug98 						_DPlay.NumAggPlayers--;
//DeadCode AMM 17Aug98 						if (_DPlay.NextGameID==1)
//DeadCode AMM 17Aug98 							exit=TRUE;
//DeadCode AMM 17Aug98 					}
//DeadCode AMM 17Aug98 				}
//DeadCode AMM 17Aug98 				else
//DeadCode AMM 17Aug98 				{
//DeadCode AMM 17Aug98 // dont care again?
//DeadCode AMM 17Aug98 				}
//DeadCode AMM 17Aug98 
//DeadCode AMM 17Aug98 				BufLen=1024;
//DeadCode AMM 17Aug98 			}
//DeadCode AMM 17Aug98 		}
//DeadCode AMM 17Aug98 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitAggregator
//Author		Andy McMaster
//Date			Wed 29 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Aggregator::InitAggregator()
{
	ULong n;

//DeadCode AMM 07Jul99 	AggFrameCount = 0;
//DeadCode AMM 08Jul99 	AggFrameCount=1;											//AMM 07Jul99
//DeadCode DAW 09Jul99 	AggFrameCount=0;											//AMM 07Jul99
//DeadCode RDH 11Jul99 		AggFrameCount=1;											//AMM 07Jul99
		AggFrameCount=0;										

	AggBuffer.InitBuffer();
//DeadCode AMM 22Dec98 	AggBuffer.SetTemp();
	AggBuffer.SetTempCurr();
	do
	{
		for (n=0;n<MAXPLAYERS;n++)
		{
			AggBuffer.GetTemp()->Acks[n]=FALSE;
		}

		AggBuffer.UpdateTemp();
	}
	while (AggBuffer.GetTemp()!=AggBuffer.GetCurr());
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitRecBits
//Author		Andrew McMaster
//Date			13 Feb 1997
//
//Description	Bit set if we want to receive a packet from player
//Old_Code AMM 03Apr97 //				i.e. for 3 players 1,2,3 and I am player 2 RecBits= bits
//Old_Code AMM 03Apr97 //				1 and 3 set = 5.(we dont want to receive from ourselves!(yet!))
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 21Aug98 void Aggregator::InitRecBits ()
//DeadCode AMM 21Aug98 {
//DeadCode AMM 21Aug98 // with aggregator we do want to receive from all players
//DeadCode AMM 21Aug98 
//DeadCode AMM 21Aug98 //	RecBits=_DPlay.ActivePlayers;										//AMM 21Mar97
//DeadCode AMM 21Aug98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopResetAggregator
//Author		Andy McMaster
//Date			Mon 15 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Aggregator::StopResetAggregator()
{
//DeadCode AMM 02Dec98 	ULong t=0;
//DeadCode AMM 02Dec98 	while (LockExchange(&inaggregator,1)) 
//DeadCode AMM 02Dec98 	{
//DeadCode AMM 02Dec98 		Sleep(0);
//DeadCode AMM 02Dec98 		if (t++>100000)
//DeadCode AMM 02Dec98 			_Error.SayAndQuit("stopreset exceeds 100000");
//DeadCode AMM 02Dec98 	};
//DeadCode AMM 02Dec98 	AggTracer("got stopreset lock\n");
//DeadCode AMM 02Dec98 	_Agg.AggregatorGetPackets(TRUE,FALSE);
//DeadCode AMM 02Dec98 	LockExchange(&inaggregator,0);
//DeadCode AMM 02Dec98 	AggTracer("released stopreset lock\n");

	ResetFlag=TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetAcks
//Author		Andy McMaster
//Date			Wed 15 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Aggregator::ResetAcks()
{
	ULong n;

	for (n=0;n<MAXPLAYERS;n++)
	{
		AggBuffer.GetCurr()->Acks[n]=FALSE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckAck
//Author		Andy McMaster
//Date			Thu 13 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Aggregator::CheckAck(UByte val, UByte count,UByte pos)
{
//DeadCode AMM 07Jul99  	UByte offset=0;
//DeadCode DAW 09Jul99  	UByte offset=0;
	LPAGGBUFF temp;

#ifdef AGGLOGS	
#ifdef VERBOSE
	FILE* fp=fopen("aggspack.txt","at");
#endif
#endif

	if (val!=0)
	{
//DeadCode AMM 07Jul99 		offset=count-val;
//DeadCode DAW 09Jul99 		offset=count-val;

#ifdef AGGLOGS	
#ifdef VERBOSE
//DeadCode AMM 07Jul99 		fprintf(fp,"received ack for %d\n",offset);
		fprintf(fp,"received ack for %d\n",val);
#endif
#endif

//DeadCode AMM 22Dec98 		AggBuffer.SetTemp();
		AggBuffer.SetTempCurr();
		while (AggBuffer.GetTemp()!=AggBuffer.GetNext())
		{
			temp=AggBuffer.GetTemp();
//DeadCode AMM 07Jul99 			if (temp->aggpack.player[pos].Count==offset)
//DeadCode DAW 09Jul99 			if (temp->aggpack.player[pos].Count==offset)
//DeadCode AMM 08Jul99 			if (temp->aggpack.Count==val)
			if (temp->aggpack.Count==val)
			{
#ifdef AGGLOGS	
#ifdef VERBOSE
//DeadCode AMM 07Jul99 				fprintf(fp,"found packet %d to ack in slot %d\n",offset,pos);
				fprintf(fp,"found packet %d to ack in slot %d\n",val,pos);
#endif
#endif
				temp->Acks[pos]=TRUE;
				break;
			}
			AggBuffer.UpdateTemp();
		}
	}
#ifdef AGGLOGS	
#ifdef VERBOSE
	fclose(fp);
#endif
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateAckBuffer
//Author		Andy McMaster
//Date			Thu 20 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Aggregator::UpdateAckBuffer()
{
	Bool update=TRUE;
	ULong n;

#ifdef AGGLOGS	
#ifdef VERBOSE
	FILE* fp=fopen("aggspack.txt","at");
#endif
#endif

	while (update)
	{
		update=TRUE;

		for (n=0;n<MAXPLAYERS;n++)
		{
			if (AggBuffer.GetCurr()->Acks[n]==FALSE)
			{
				update=FALSE;
				break;
			}
		}

		if (update)
		{
			ResetAcks();

#ifdef AGGLOGS	
#ifdef VERBOSE
		fprintf(fp,"update CurrAggPackPos %d slot0=%d slot1=%d\n",
			AggBuffer.GetCurr()->aggpack.Count,
			AggBuffer.GetCurr()->aggpack.player[0].Count,
			AggBuffer.GetCurr()->aggpack.player[1].Count);
#endif
#endif
				AggBuffer.UpdateCurr();

//DeadCode AMM 14Dec98 			if (AggBuffer.NumEntries()<0)
//DeadCode AMM 14Dec98 				_Error.SayAndQuit("AggPackEntries<0");
		}
	}
#ifdef AGGLOGS
#ifdef VERBOSE
	fclose(fp);
#endif
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitReservePackets
//Author		Andy McMaster
//Date			Mon 17 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Aggregator::InitReservePackets()
{
	ULong n;

	for (n=0;n<MAXPLAYERS;n++)
	{
		ReservePackets[n].InitBuffer();
//DeadCode AMM 22Dec98 		ReservePackets[n].SetTemp();
		ReservePackets[n].SetTempCurr();
		do 
		{
//DeadCode AMM 28Jul99 			ReservePackets[n].GetTemp()->IDCode==PIDC_PACKETERROR;
			ReservePackets[n].GetTemp()->IDCode=PIDC_PACKETERROR;//AMM 28Jul99
			ReservePackets[n].UpdateTemp();
		}
		while (ReservePackets[n].GetTemp()!=ReservePackets[n].GetCurr());
	}
}

UByte	Aggregator::GetAggFrameCount()
{
	return AggFrameCount;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReceiveMessage
//Author		Andy McMaster
//Date			Thu 13 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
HRESULT	Aggregator::ReceiveMessage(char*&buf,ULong& buflen,ULong& from)
{
	HRESULT res;

	ULong to=_DPlay.aggID,temp;
	from=0;

	while (true)
	{
		temp=AggPacketLength;
		res=_DPlay.lpDP4->Receive(&from,&to,DPRECEIVE_TOPLAYER,AggPacketPtr,&temp);

		if (res==DPERR_BUFFERTOOSMALL)
		{
			delete [] AggPacketPtr;
			AggPacketPtr=new char[temp];
			AggPacketLength=temp;
			if (!AggPacketPtr)
				_Error.EmitSysErr("Out of memory");
		}
		else if (res==DP_OK)
		{
			buf=AggPacketPtr;
			buflen=temp;
			return res;
		}
		else break;
	}
	return res;
}

bool Aggregator::MakeAndSendPacket(LPAGGSENDPACKET packet, Bool buffer)
{
	ULong NumPlayers=0, n, PacketSize;
	bool ok;
	HRESULT res;
	AGGSENDPACKET p;
	UByteP TempPtr=(UByteP)&p;

	PacketSize=sizeof(UByte); // count
	PacketSize+=sizeof(ULong); // player in packet

	*((ULong*)TempPtr)=RecBits;
	TempPtr+=sizeof(ULong);
	*TempPtr=AggFrameCount;
	TempPtr+=sizeof(UByte);

// start filling in players packets

	for (n=0; n<MAXPLAYERS; n++)
	{
		if (RecBits & 1<<n)
		{
// copy player from packet to Packet

			memcpy(TempPtr,&packet->player[n],sizeof(ACPACKET));
			TempPtr+=sizeof(ACPACKET);
			PacketSize+=sizeof(ACPACKET);
			NumPlayers++;
		}
	}

	res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&p,PacketSize,0,0,NULL,NULL);

	if (!res || res==DPERR_PENDING)
		ok=true;
	else
		ok=false;

// copy packet into buffer if not in sync phase

	if (buffer)
	{
// if we have filled up sent buffer then overwrite last entry.
// If packet has really not been received by a player then it will cause them to 
// initaite a resynch quite soon....!!!!

		if (AggBuffer.NumEntries()==BUFFERLENGTH)
		{
			ResetAcks();
			AggBuffer.UpdateCurr();
			UpdateAckBuffer();
		}

		AggBuffer.GetNext()->NumPlayersInPacket=NumPlayers;

		memcpy((char*)&AggBuffer.GetNext()->aggpack,(char*)&p,sizeof(AGGSENDPACKET));
	}

	return ok;
}

bool Aggregator::ResendAggPacket()
{
	ULong PacketSize;
	HRESULT res;
	bool	ok;

	PacketSize=sizeof(ULong);
	PacketSize+=sizeof(UByte);
	PacketSize+=sizeof(ACPACKET) * AggBuffer.GetCurr()->NumPlayersInPacket;

	res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&((AggBuffer.GetCurr())->aggpack),PacketSize,0,0,NULL,NULL);

	if (!res || res==DPERR_PENDING)
		ok=true;
	else
		ok=false;

	return ok;
}

CON		Aggregator::Aggregator()
{
 	AggFrameCount=0;
//DeadCode AMM 07Jul99  	AggFrameCount=0;
//DeadCode AMM 08Jul99  	AggFrameCount=1;											//AMM 07Jul99
	RecBits = 0;
	Running=FALSE;
	ResetFlag=false;
	ResendStatus=0;
	ResendPacket=0;
	AggPacketPtr=NULL;
	AggPacketLength=0;
}

CON		Aggregator::~Aggregator()
{
	delete [] AggPacketPtr;
	AggPacketPtr=NULL;
	AggPacketLength=0;
}
