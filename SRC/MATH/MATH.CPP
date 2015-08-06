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
//Filename       math.cpp
//System         
//Author         Paul.   
//Date           Tue 22 Aug 1995
//Description    
//------------------------------------------------------------------------------
								
	#include	"DOSDefs.h"
	#include	"myAngles.h"
//DeadCode DAW 15Apr96 	#include	"screen.h"
//DeadCode DAW 19Mar96 	#include	"getset.h"
	#include	"mymath.h"
	#include	"Worldinc.h"
	#include	"World.h"
//	#include	"main.h"
	#include	"myerror.h"
	#include	"mytime.h"

//	#include	"winmove.h"										//ARM 25Oct96

//DeadCode JIM 05Jan96 	extern class Main _Main;
//DeadCode JIM 05Jan96 	extern class Error _Error;			//For 'EmitSysErr'

//DeadCode PD 29Nov95 	class mathlib	_mathlib;
	class	MathLib	Math_Lib;									//PD 29Nov95
	
#define	sin_index	0
#define	cos_index	256

UWord MathLib::Days_in_Month[] =
{
		31,28,31,30,31,30,31,31,30,31,30,31
};


SWord	MathLib::matan[] =
		{
		   0,  41,  81, 122, 163, 204, 244, 285	,
		 326, 367, 407, 448, 489, 529, 570, 610,

		 651, 692, 732, 773, 813, 854, 894, 935	,
		 975,1015,1056,1096,1136,1177,1217,1257,

		1297,1337,1377,1417,1457,1497,1537,1577	,
		1617,1656,1696,1736,1775,1815,1854,1894,

		1933,1973,2012,2051,2090,2129,2168,2207	,
		2246,2285,2324,2363,2401,2440,2478,2517,

		2555,2594,2632,2670,2708,2746,2784,2822	,
		2860,2897,2935,2973,3010,3047,3085,3122,

		3159,3196,3233,3270,3307,3344,3380,3417	,
		3453,3490,3526,3562,3599,3635,3670,3706,

		3742,3778,3813,3849,3884,3920,3955,3990	,
		4025,4060,4095,4129,4164,4199,4233,4267,

		4302,4336,4370,4404,4438,4471,4505,4539	,
		4572,4605,4639,4672,4705,4738,4771,4803,

		4836,4869,4901,4933,4966,4998,5030,5062	,
		5094,5125,5157,5188,5220,5251,5282,5313,

		5344,5375,5406,5437,5467,5498,5528,5559	,
		5589,5619,5649,5679,5708,5738,5768,5797,

		5826,5856,5885,5914,5943,5972,6000,6029	,
		6058,6086,6114,6142,6171,6199,6227,6254,

		6282,6310,6337,6365,6392,6419,6446,6473	,
		6500,6527,6554,6580,6607,6633,6660,6686,

		6712,6738,6764,6790,6815,6841,6867,6892	,
		6917,6943,6968,6993,7018,7043,7068,7092,

		7117,7141,7166,7190,7214,7238,7262,7286	,
		7310,7334,7358,7381,7405,7428,7451,7475,

		7498,7521,7544,7566,7589,7612,7635,7657	,
		7679,7702,7724,7746,7768,7790,7812,7834,

		7856,7877,7899,7920,7942,7963,7984,8005	,
		8026,8047,8068,8089,8110,8131,8151,8172,

		8192,
		8192
		};

SWord	MathLib::sincos_table[] =
			{
//sine table
			0x0,0x0C9,0x0192,0x025B,
			0x0324,0x03ED,0x04B6,0x057E,
			0x0647,0x0710,0x07D9,0x08A1,
			0x096A,0x0A32,0x0AFB,0x0BC3,
			0x0C8B,0x0D53,0x0E1B,0x0EE3,
			0x0FAB,0x01072,0x01139,0x01200,
			0x012C7,0x0138E,0x01455,0x0151B,
			0x015E1,0x016A7,0x0176D,0x01833,
			0x018F8,0x019BD,0x01A82,0x01B46,
			0x01C0B,0x01CCF,0x01D93,0x01E56,
			0x01F19,0x01FDC,0x0209F,0x02161,
			0x02223,0x022E4,0x023A6,0x02467,
			0x02527,0x025E7,0x026A7,0x02767,
			0x02826,0x028E5,0x029A3,0x02A61,
			0x02B1E,0x02BDB,0x02C98,0x02D54,
			0x02E10,0x02ECC,0x02F86,0x03041,
			0x030FB,0x031B4,0x0326D,0x03326,
			0x033DE,0x03496,0x0354D,0x03603,
			0x036B9,0x0376F,0x03824,0x038D8,
			0x0398C,0x03A3F,0x03AF2,0x03BA4,
			0x03C56,0x03D07,0x03DB7,0x03E67,
			0x03F16,0x03FC5,0x04073,0x04120,
			0x041CD,0x04279,0x04325,0x043D0,
			0x0447A,0x04523,0x045CC,0x04674,
			0x0471C,0x047C3,0x04869,0x0490E,
			0x049B3,0x04A57,0x04AFA,0x04B9D,
			0x04C3F,0x04CE0,0x04D80,0x04E20,
			0x04EBF,0x04F5D,0x04FFA,0x05097,
			0x05133,0x051CE,0x05268,0x05301,
			0x0539A,0x05432,0x054C9,0x0555F,
			0x055F4,0x05689,0x0571D,0x057B0,
			0x05842,0x058D3,0x05963,0x059F3,
			0x05A81,0x05B0F,0x05B9C,0x05C28,
			0x05CB3,0x05D3D,0x05DC6,0x05E4F,
			0x05ED6,0x05F5D,0x05FE2,0x06067,
			0x060EB,0x0616E,0x061F0,0x06271,
			0x062F1,0x06370,0x063EE,0x0646B,
			0x064E7,0x06562,0x065DD,0x06656,
			0x066CE,0x06745,0x067BC,0x06831,
			0x068A5,0x06919,0x0698B,0x069FC,
			0x06A6C,0x06ADB,0x06B4A,0x06BB7,
			0x06C23,0x06C8E,0x06CF8,0x06D61,
			0x06DC9,0x06E30,0x06E95,0x06EFA,
			0x06F5E,0x06FC0,0x07022,0x07082,
			0x070E1,0x07140,0x0719D,0x071F9,
			0x07254,0x072AE,0x07306,0x0735E,
			0x073B5,0x0740A,0x0745E,0x074B1,
			0x07503,0x07554,0x075A4,0x075F3,
			0x07640,0x0768D,0x076D8,0x07722,
			0x0776B,0x077B3,0x077F9,0x0783F,
			0x07883,0x078C6,0x07908,0x07949,
			0x07989,0x079C7,0x07A04,0x07A41,
			0x07A7C,0x07AB5,0x07AEE,0x07B25,
			0x07B5C,0x07B91,0x07BC4,0x07BF7,
			0x07C29,0x07C59,0x07C88,0x07CB6,
			0x07CE2,0x07D0E,0x07D38,0x07D61,
			0x07D89,0x07DB0,0x07DD5,0x07DF9,
			0x07E1C,0x07E3E,0x07E5E,0x07E7E,
			0x07E9C,0x07EB9,0x07ED4,0x07EEF,
			0x07F08,0x07F20,0x07F37,0x07F4C,
			0x07F61,0x07F74,0x07F86,0x07F96,
			0x07FA6,0x07FB4,0x07FC1,0x07FCD,
			0x07FD7,0x07FE0,0x07FE8,0x07FEF,
			0x07FF5,0x07FF9,0x07FFC,0x07FFE,

//cosine table
			0x07FFF,0x07FFE,0x07FFC,0x07FF9,
			0x07FF5,0x07FEF,0x07FE8,0x07FE0,
			0x07FD7,0x07FCD,0x07FC1,0x07FB4,
			0x07FA6,0x07F96,0x07F86,0x07F74,
			0x07F61,0x07F4C,0x07F37,0x07F20,
			0x07F08,0x07EEF,0x07ED4,0x07EB9,
			0x07E9C,0x07E7E,0x07E5E,0x07E3E,
			0x07E1C,0x07DF9,0x07DD5,0x07DB0,
			0x07D89,0x07D61,0x07D38,0x07D0E,
			0x07CE2,0x07CB6,0x07C88,0x07C59,
			0x07C29,0x07BF7,0x07BC4,0x07B91,
			0x07B5C,0x07B25,0x07AEE,0x07AB5,
			0x07A7C,0x07A41,0x07A04,0x079C7,
			0x07989,0x07949,0x07908,0x078C6,
			0x07883,0x0783F,0x077F9,0x077B3,
			0x0776B,0x07722,0x076D8,0x0768D,
			0x07640,0x075F3,0x075A4,0x07554,
			0x07503,0x074B1,0x0745E,0x0740A,
			0x073B5,0x0735E,0x07306,0x072AE,
			0x07254,0x071F9,0x0719D,0x07140,
			0x070E1,0x07082,0x07022,0x06FC0,
			0x06F5E,0x06EFA,0x06E95,0x06E30,
			0x06DC9,0x06D61,0x06CF8,0x06C8E,
			0x06C23,0x06BB7,0x06B4A,0x06ADB,
			0x06A6C,0x069FC,0x0698B,0x06919,
			0x068A5,0x06831,0x067BC,0x06745,
			0x066CE,0x06656,0x065DD,0x06562,
			0x064E7,0x0646B,0x063EE,0x06370,
			0x062F1,0x06271,0x061F0,0x0616E,
			0x060EB,0x06067,0x05FE2,0x05F5D,
			0x05ED6,0x05E4F,0x05DC6,0x05D3D,
			0x05CB3,0x05C28,0x05B9C,0x05B0F,
			0x05A81,0x059F3,0x05963,0x058D3,
			0x05842,0x057B0,0x0571D,0x05689,
			0x055F4,0x0555F,0x054C9,0x05432,
			0x0539A,0x05301,0x05268,0x051CE,
			0x05133,0x05097,0x04FFA,0x04F5D,
			0x04EBF,0x04E20,0x04D80,0x04CE0,
			0x04C3F,0x04B9D,0x04AFA,0x04A57,
			0x049B3,0x0490E,0x04869,0x047C3,
			0x0471C,0x04674,0x045CC,0x04523,
			0x0447A,0x043D0,0x04325,0x04279,
			0x041CD,0x04120,0x04073,0x03FC5,
			0x03F16,0x03E67,0x03DB7,0x03D07,
			0x03C56,0x03BA4,0x03AF2,0x03A3F,
			0x0398C,0x038D8,0x03824,0x0376F,
			0x036B9,0x03603,0x0354D,0x03496,
			0x033DE,0x03326,0x0326D,0x031B4,
			0x030FB,0x03041,0x02F86,0x02ECC,
			0x02E10,0x02D54,0x02C98,0x02BDB,
			0x02B1E,0x02A61,0x029A3,0x028E5,
			0x02826,0x02767,0x026A7,0x025E7,
			0x02527,0x02467,0x023A6,0x022E4,
			0x02223,0x02161,0x0209F,0x01FDC,
			0x01F19,0x01E56,0x01D93,0x01CCF,
			0x01C0B,0x01B46,0x01A82,0x019BD,
			0x018F8,0x01833,0x0176D,0x016A7,
			0x015E1,0x0151B,0x01455,0x0138E,
			0x012C7,0x01200,0x01139,0x01072,
			0x0FAB,0x0EE3,0x0E1B,0x0D53,
			0x0C8B,0x0BC3,0x0AFB,0x0A32,
			0x096A,0x08A1,0x07D9,0x0710,
			0x0647,0x057E,0x04B6,0x03ED,
			0x0324,0x025B,0x0192,0x0C9,
			0x0,0x0FF37,0x0FE6E,0x0FDA5,
			0x0FCDC,0x0FC13,0x0FB4A,0x0FA82,
			0x0F9B9,0x0F8F0,0x0F827,0x0F75F,
			0x0F696,0x0F5CE,0x0F505,0x0F43D,
			0x0F375,0x0F2AD,0x0F1E5,0x0F11D,
			0x0F055,0x0EF8E,0x0EEC7,0x0EE00,
			0x0ED39,0x0EC72,0x0EBAB,0x0EAE5,
			0x0EA1F,0x0E959,0x0E893,0x0E7CD,
			0x0E708,0x0E643,0x0E57E,0x0E4BA,
			0x0E3F5,0x0E331,0x0E26D,0x0E1AA,
			0x0E0E7,0x0E024,0x0DF61,0x0DE9F,
			0x0DDDD,0x0DD1C,0x0DC5A,0x0DB99,
			0x0DAD9,0x0DA19,0x0D959,0x0D899,
			0x0D7DA,0x0D71B,0x0D65D,0x0D59F,
			0x0D4E2,0x0D425,0x0D368,0x0D2AC,
			0x0D1F0,0x0D134,0x0D07A,0x0CFBF,
			0x0CF05,0x0CE4C,0x0CD93,0x0CCDA,
			0x0CC22,0x0CB6A,0x0CAB3,0x0C9FD,
			0x0C947,0x0C891,0x0C7DC,0x0C728,
			0x0C674,0x0C5C1,0x0C50E,0x0C45C,
			0x0C3AA,0x0C2F9,0x0C249,0x0C199,
			0x0C0EA,0x0C03B,0x0BF8D,0x0BEE0,
			0x0BE33,0x0BD87,0x0BCDB,0x0BC30,
			0x0BB86,0x0BADD,0x0BA34,0x0B98C,
			0x0B8E4,0x0B83D,0x0B797,0x0B6F2,
			0x0B64D,0x0B5A9,0x0B506,0x0B463,
			0x0B3C1,0x0B320,0x0B280,0x0B1E0,
			0x0B141,0x0B0A3,0x0B006,0x0AF69,
			0x0AECD,0x0AE32,0x0AD98,0x0ACFF,
			0x0AC66,0x0ABCE,0x0AB37,0x0AAA1,
			0x0AA0C,0x0A977,0x0A8E3,0x0A850,
			0x0A7BE,0x0A72D,0x0A69D,0x0A60D,
			0x0A57F,0x0A4F1,0x0A464,0x0A3D8,
			0x0A34D,0x0A2C3,0x0A23A,0x0A1B1,
			0x0A12A,0x0A0A3,0x0A01E,0x09F99,
			0x09F15,0x09E92,0x09E10,0x09D8F,
			0x09D0F,0x09C90,0x09C12,0x09B95,
			0x09B19,0x09A9E,0x09A23,0x099AA,
			0x09932,0x098BB,0x09844,0x097CF,
			0x0975B,0x096E7,0x09675,0x09604,
			0x09594,0x09525,0x094B6,0x09449,
			0x093DD,0x09372,0x09308,0x0929F,
			0x09237,0x091D0,0x0916B,0x09106,
			0x090A2,0x09040,0x08FDE,0x08F7E,
			0x08F1F,0x08EC0,0x08E63,0x08E07,
			0x08DAC,0x08D52,0x08CFA,0x08CA2,
			0x08C4B,0x08BF6,0x08BA2,0x08B4F,
			0x08AFD,0x08AAC,0x08A5C,0x08A0D,
			0x089C0,0x08973,0x08928,0x088DE,
			0x08895,0x0884D,0x08807,0x087C1,
			0x0877D,0x0873A,0x086F8,0x086B7,
			0x08677,0x08639,0x085FC,0x085BF,
			0x08584,0x0854B,0x08512,0x084DB,
			0x084A4,0x0846F,0x0843C,0x08409,
			0x083D7,0x083A7,0x08378,0x0834A,
			0x0831E,0x082F2,0x082C8,0x0829F,
			0x08277,0x08250,0x0822B,0x08207,
			0x081E4,0x081C2,0x081A2,0x08182,
			0x08164,0x08147,0x0812C,0x08111,
			0x080F8,0x080E0,0x080C9,0x080B4,
			0x0809F,0x0808C,0x0807A,0x0806A,
			0x0805A,0x0804C,0x0803F,0x08033,
			0x08029,0x08020,0x08018,0x08011,
			0x0800B,0x08007,0x08004,0x08002,
			0x08001,0x08002,0x08004,0x08007,
			0x0800B,0x08011,0x08018,0x08020,
			0x08029,0x08033,0x0803F,0x0804C,
			0x0805A,0x0806A,0x0807A,0x0808C,
			0x0809F,0x080B4,0x080C9,0x080E0,
			0x080F8,0x08111,0x0812C,0x08147,
			0x08164,0x08182,0x081A2,0x081C2,
			0x081E4,0x08207,0x0822B,0x08250,
			0x08277,0x0829F,0x082C8,0x082F2,
			0x0831E,0x0834A,0x08378,0x083A7,
			0x083D7,0x08409,0x0843C,0x0846F,
			0x084A4,0x084DB,0x08512,0x0854B,
			0x08584,0x085BF,0x085FC,0x08639,
			0x08677,0x086B7,0x086F8,0x0873A,
			0x0877D,0x087C1,0x08807,0x0884D,
			0x08895,0x088DE,0x08928,0x08973,
			0x089C0,0x08A0D,0x08A5C,0x08AAC,
			0x08AFD,0x08B4F,0x08BA2,0x08BF6,
			0x08C4B,0x08CA2,0x08CFA,0x08D52,
			0x08DAC,0x08E07,0x08E63,0x08EC0,
			0x08F1F,0x08F7E,0x08FDE,0x09040,
			0x090A2,0x09106,0x0916B,0x091D0,
			0x09237,0x0929F,0x09308,0x09372,
			0x093DD,0x09449,0x094B6,0x09525,
			0x09594,0x09604,0x09675,0x096E7,
			0x0975B,0x097CF,0x09844,0x098BB,
			0x09932,0x099AA,0x09A23,0x09A9E,
			0x09B19,0x09B95,0x09C12,0x09C90,
			0x09D0F,0x09D8F,0x09E10,0x09E92,
			0x09F15,0x09F99,0x0A01E,0x0A0A3,
			0x0A12A,0x0A1B1,0x0A23A,0x0A2C3,
			0x0A34D,0x0A3D8,0x0A464,0x0A4F1,
			0x0A57F,0x0A60D,0x0A69D,0x0A72D,
			0x0A7BE,0x0A850,0x0A8E3,0x0A977,
			0x0AA0C,0x0AAA1,0x0AB37,0x0ABCE,
			0x0AC66,0x0ACFF,0x0AD98,0x0AE32,
			0x0AECD,0x0AF69,0x0B006,0x0B0A3,
			0x0B141,0x0B1E0,0x0B280,0x0B320,
			0x0B3C1,0x0B463,0x0B506,0x0B5A9,
			0x0B64D,0x0B6F2,0x0B797,0x0B83D,
			0x0B8E4,0x0B98C,0x0BA34,0x0BADD,
			0x0BB86,0x0BC30,0x0BCDB,0x0BD87,
			0x0BE33,0x0BEE0,0x0BF8D,0x0C03B,
			0x0C0EA,0x0C199,0x0C249,0x0C2F9,
			0x0C3AA,0x0C45C,0x0C50E,0x0C5C1,
			0x0C674,0x0C728,0x0C7DC,0x0C891,
			0x0C947,0x0C9FD,0x0CAB3,0x0CB6A,
			0x0CC22,0x0CCDA,0x0CD93,0x0CE4C,
			0x0CF05,0x0CFBF,0x0D07A,0x0D134,
			0x0D1F0,0x0D2AC,0x0D368,0x0D425,
			0x0D4E2,0x0D59F,0x0D65D,0x0D71B,
			0x0D7DA,0x0D899,0x0D959,0x0DA19,
			0x0DAD9,0x0DB99,0x0DC5A,0x0DD1C,
			0x0DDDD,0x0DE9F,0x0DF61,0x0E024,
			0x0E0E7,0x0E1AA,0x0E26D,0x0E331,
			0x0E3F5,0x0E4BA,0x0E57E,0x0E643,
			0x0E708,0x0E7CD,0x0E893,0x0E959,
			0x0EA1F,0x0EAE5,0x0EBAB,0x0EC72,
			0x0ED39,0x0EE00,0x0EEC7,0x0EF8E,
			0x0F055,0x0F11D,0x0F1E5,0x0F2AD,
			0x0F375,0x0F43D,0x0F505,0x0F5CE,
			0x0F696,0x0F75F,0x0F827,0x0F8F0,
			0x0F9B9,0x0FA82,0x0FB4A,0x0FC13,
			0x0FCDC,0x0FDA5,0x0FE6E,0x0FF37,
			0x0,0x0C9,0x0192,0x025B,
			0x0324,0x03ED,0x04B6,0x057E,
			0x0647,0x0710,0x07D9,0x08A1,
			0x096A,0x0A32,0x0AFB,0x0BC3,
			0x0C8B,0x0D53,0x0E1B,0x0EE3,
			0x0FAB,0x01072,0x01139,0x01200,
			0x012C7,0x0138E,0x01455,0x0151B,
			0x015E1,0x016A7,0x0176D,0x01833,
			0x018F8,0x019BD,0x01A82,0x01B46,
			0x01C0B,0x01CCF,0x01D93,0x01E56,
			0x01F19,0x01FDC,0x0209F,0x02161,
			0x02223,0x022E4,0x023A6,0x02467,
			0x02527,0x025E7,0x026A7,0x02767,
			0x02826,0x028E5,0x029A3,0x02A61,
			0x02B1E,0x02BDB,0x02C98,0x02D54,
			0x02E10,0x02ECC,0x02F86,0x03041,
			0x030FB,0x031B4,0x0326D,0x03326,
			0x033DE,0x03496,0x0354D,0x03603,
			0x036B9,0x0376F,0x03824,0x038D8,
			0x0398C,0x03A3F,0x03AF2,0x03BA4,
			0x03C56,0x03D07,0x03DB7,0x03E67,
			0x03F16,0x03FC5,0x04073,0x04120,
			0x041CD,0x04279,0x04325,0x043D0,
			0x0447A,0x04523,0x045CC,0x04674,
			0x0471C,0x047C3,0x04869,0x0490E,
			0x049B3,0x04A57,0x04AFA,0x04B9D,
			0x04C3F,0x04CE0,0x04D80,0x04E20,
			0x04EBF,0x04F5D,0x04FFA,0x05097,
			0x05133,0x051CE,0x05268,0x05301,
			0x0539A,0x05432,0x054C9,0x0555F,
			0x055F4,0x05689,0x0571D,0x057B0,
			0x05842,0x058D3,0x05963,0x059F3,
			0x05A81,0x05B0F,0x05B9C,0x05C28,
			0x05CB3,0x05D3D,0x05DC6,0x05E4F,
			0x05ED6,0x05F5D,0x05FE2,0x06067,
			0x060EB,0x0616E,0x061F0,0x06271,
			0x062F1,0x06370,0x063EE,0x0646B,
			0x064E7,0x06562,0x065DD,0x06656,
			0x066CE,0x06745,0x067BC,0x06831,
			0x068A5,0x06919,0x0698B,0x069FC,
			0x06A6C,0x06ADB,0x06B4A,0x06BB7,
			0x06C23,0x06C8E,0x06CF8,0x06D61,
			0x06DC9,0x06E30,0x06E95,0x06EFA,
			0x06F5E,0x06FC0,0x07022,0x07082,
			0x070E1,0x07140,0x0719D,0x071F9,
			0x07254,0x072AE,0x07306,0x0735E,
			0x073B5,0x0740A,0x0745E,0x074B1,
			0x07503,0x07554,0x075A4,0x075F3,
			0x07640,0x0768D,0x076D8,0x07722,
			0x0776B,0x077B3,0x077F9,0x0783F,
			0x07883,0x078C6,0x07908,0x07949,
			0x07989,0x079C7,0x07A04,0x07A41,
			0x07A7C,0x07AB5,0x07AEE,0x07B25,
			0x07B5C,0x07B91,0x07BC4,0x07BF7,
			0x07C29,0x07C59,0x07C88,0x07CB6,
			0x07CE2,0x07D0E,0x07D38,0x07D61,
			0x07D89,0x07DB0,0x07DD5,0x07DF9,
			0x07E1C,0x07E3E,0x07E5E,0x07E7E,
			0x07E9C,0x07EB9,0x07ED4,0x07EEF,
			0x07F08,0x07F20,0x07F37,0x07F4C,
			0x07F61,0x07F74,0x07F86,0x07F96,
			0x07FA6,0x07FB4,0x07FC1,0x07FCD,
			0x07FD7,0x07FE0,0x07FE8,0x07FEF,
			0x07FF5,0x07FF9,0x07FFC,0x07FFE
			};

SWord	MathLib::tan_table[]=
			{
			0x00000,0x00001,0x00003,0x00004,0x00006,0x00007,0x00009,0x0000A,
			0x0000C,0x0000E,0x0000F,0x00011,0x00012,0x00014,0x00015,0x00017,
			0x00019,0x0001A,0x0001C,0x0001D,0x0001F,0x00021,0x00022,0x00024,
			0x00025,0x00027,0x00029,0x0002A,0x0002C,0x0002D,0x0002F,0x00031,
			0x00032,0x00034,0x00036,0x00037,0x00039,0x0003B,0x0003C,0x0003E,
			0x0003F,0x00041,0x00043,0x00045,0x00046,0x00048,0x0004A,0x0004B,
			0x0004D,0x0004F,0x00050,0x00052,0x00054,0x00056,0x00057,0x00059,
			0x0005B,0x0005D,0x0005E,0x00060,0x00062,0x00064,0x00066,0x00068,
			0x00069,0x0006B,0x0006D,0x0006F,0x00071,0x00073,0x00075,0x00076,
			0x00078,0x0007A,0x0007C,0x0007E,0x00080,0x00082,0x00084,0x00086,
			0x00088,0x0008A,0x0008C,0x0008E,0x00090,0x00092,0x00094,0x00097,
			0x00099,0x0009B,0x0009D,0x0009F,0x000A1,0x000A4,0x000A6,0x000A8,
			0x000AA,0x000AD,0x000AF,0x000B1,0x000B4,0x000B6,0x000B8,0x000BB,
			0x000BD,0x000C0,0x000C2,0x000C5,0x000C7,0x000CA,0x000CC,0x000CF,
			0x000D1,0x000D4,0x000D7,0x000D9,0x000DC,0x000DF,0x000E2,0x000E5,
			0x000E7,0x000EA,0x000ED,0x000F0,0x000F3,0x000F6,0x000F9,0x000FC,
			0x00100,0x00103,0x00106,0x00109,0x0010C,0x00110,0x00113,0x00117,
			0x0011A,0x0011E,0x00121,0x00125,0x00128,0x0012C,0x00130,0x00134,
			0x00138,0x0013C,0x00140,0x00144,0x00148,0x0014C,0x00150,0x00155,
			0x00159,0x0015E,0x00162,0x00167,0x0016C,0x00170,0x00175,0x0017A,
			0x0017F,0x00185,0x0018A,0x0018F,0x00195,0x0019A,0x001A0,0x001A6,
			0x001AC,0x001B2,0x001B8,0x001BF,0x001C5,0x001CC,0x001D2,0x001D9,
			0x001E0,0x001E8,0x001EF,0x001F7,0x001FE,0x00206,0x0020F,0x00217,
			0x00220,0x00229,0x00232,0x0023B,0x00245,0x0024E,0x00259,0x00263,
			0x0026E,0x00279,0x00284,0x00290,0x0029C,0x002A9,0x002B6,0x002C4,
			0x002D2,0x002E0,0x002EF,0x002FE,0x0030F,0x0031F,0x00331,0x00343,
			0x00356,0x00369,0x0037E,0x00393,0x003A9,0x003C1,0x003D9,0x003F3,
			0x0040E,0x0042B,0x00448,0x00468,0x00489,0x004AC,0x004D2,0x004F9,
			0x00524,0x00551,0x00581,0x005B4,0x005EB,0x00626,0x00667,0x006AC,
			0x006F7,0x00749,0x007A3,0x00806,0x00873,0x008ED,0x00974,0x00A0D,
			0x00AB9,0x00B7E,0x00C62,0x00D6B,0x00EA5,0x0101D,0x011E8,0x01426,
			0x01708,0x01AE0,0x02042,0x02853,0x035C6,0x050AA,0x07FFF,0x07FFF
			};


UWord	MathLib::bval=23,MathLib::cval=54;
UWord	MathLib::rndlookup[]=
		{	  899,   456,   143, 65000,  7543, 19837, 34509,    34,
			23056,  4582, 19003, 37032, 18954,   274,  4873, 59341,
			40087, 39024,  2984, 19823, 30182, 39261, 21998,   453,
			58191, 53195,  1984, 24219, 23652, 49735, 27428, 19824,
			35674, 58778, 21127, 45420, 56109, 46663,  9415, 45778,
			12944, 24972, 23459, 43876,  1435, 27684, 17698, 55536,
			32475,  9577, 59072,  5701, 11770, 19560, 13950};

UWord MathLib::GetRndLookUp (UWord n)							//ARM 04Sep96
{																//ARM 04Sep96
	return rndlookup[n];										//ARM 04Sep96
}																//ARM 04Sep96

void MathLib::SetRndLookUp (UWord n, UWord val)					//ARM 04Sep96
{																//ARM 04Sep96
	rndlookup[n] = val;											//ARM 04Sep96
}																//ARM 04Sep96

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	sin_cos
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void MathLib::sin_cos(ANGLES ang, SWord& sin_ang, SWord& cos_ang)
{
	UWord	temp = ang>>6;
	sin_ang = sincos_table[temp];
	cos_ang = sincos_table[cos_index+temp];
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	high_sin_cos
//------------------------------------------------------------------------------
//Author		Rod prepared shell   
//Date		//RDH 30Oct95
//Modified	
//
//Description	
//Description	Return Sin&Cos for 64K angle
//		First approx is from sin/cos table
//		This is improved by the relationships:
//		Sin(A+B)=Sin(A)*Cos(B)+Sin(B)*Cos(A)
//		Cos(A+B)=Cos(A)*Cos(B)-Sin(A)*Sin(B)
//		And the approximations for B:
//		B ranges from 0 to pi/1024 
//		Cos(B)*65536>65535
//		Sin(B[0-63])*65536 is linear between 0 and 398
//		25*B=0-1575 /4=394
//		Thus we are encoding:
//		Sin(A+B)=Sin(A)+Cos(A)*25B/4
//		Cos(A+B)=Cos(A)-Sin(A)*25B/4
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void MathLib::high_sin_cos(ANGLES ang, SWord& sin_ang, SWord& cos_ang)
{
	SLong	bb,temp_cos;

	sin_cos(ang,sin_ang,cos_ang);
 	bb = ang & 63;
	bb = bb * 25 ;
	temp_cos = cos_ang;
	cos_ang = cos_ang - sin_ang * bb / (ANGLES_FRACT * 8);
	sin_ang = sin_ang + temp_cos * bb / (ANGLES_FRACT * 8);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	arcsin
//------------------------------------------------------------------------------
//Author		Martin   
//Date			Tue 19 Sep 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ANGLES MathLib::arcsin(SWord ax)
{
	ANGLES ang;
	SWord i;

	for (i=0;i<256;i++)											//RJS 17Nov97
	{															//RJS 17Nov97
		if (sincos_table[i]==ax)								//RJS 17Nov97
		{														//RJS 17Nov97
			ang =(Angles) i;									//RJS 17Nov97
			break;												//RJS 17Nov97
		}														//RJS 17Nov97
	}															//RJS 17Nov97
	return(ang);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		high_arc_cos
//Author		Paul.   
//Date			Thu 23 May 1996
//
//Description	
//
//Inputs		cosine of angle	
//
//Returns		Angle in the range 0 Deg to 180 Deg
//
//------------------------------------------------------------------------------
ANGLES MathLib::high_arc_cos(SWord ca)
{
	//changed to use the fact that arccos(x)==arctan(sqrt((1-x*x)/x*x))
	if (!ca)
		return ANGLES_90Deg;
	Float cosang,oneminuscosang;
	cosang=Float(ca)/Float(ANGLES_FRACT);
	cosang*=cosang;
	oneminuscosang=1.-cosang;
	cosang=oneminuscosang/cosang;
	_asm {
			fld cosang; 
			fsqrt; 
			fstp cosang;
	}
	cosang=10430.387*FPATan(cosang,1.);
	int intang(cosang);
	return ca<0?(Angles)(int(ANGLES_180Deg)-intang):(Angles)intang;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		high_arc_sin
//Author		Paul.   
//Date			Thu 23 May 1996
//
//Description	
//
//Inputs		sine of angle	
//
//Returns		Angle in the range -90 Deg to 90 Deg
//
//------------------------------------------------------------------------------
ANGLES MathLib::high_arc_sin(SWord sa)
{
	//changed to use the fact that arcsin(x)==arctan(sqrt(x*x/(1-x*x)))
	Float sinang,oneminussinang;
	sinang=Float(sa)/Float(ANGLES_FRACT);
	sinang*=sinang;
	if (sinang==1.)
		return sa<0?ANGLES_270Deg:ANGLES_90Deg;
	oneminussinang=1.-sinang;
	sinang/=oneminussinang;
	_asm{
		fld sinang;
		fsqrt;
		fstp sinang;
	}
	sinang=10430.387*FPATan(sinang,1.);
	int intang(sinang);
	return sa<0?(Angles)-intang:(Angles)intang;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	arccos
//------------------------------------------------------------------------------
//Author		Martin   
//Date			Tue 19 Sep 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ANGLES MathLib::arccos(SWord ax)
{
	ANGLES ang;
	SWord i;

	for (i=0;i<256;i++)
		{
			if (sincos_table[i+cos_index]==ax)
				{
					ang = (Angles) i;
				}
		}
	return(ang);
	
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	arctan
//------------------------------------------------------------------------------
//Author 		Martin
//Date			19 Sep 1995
//Modified		   	//RDH 03Nov95
//				   = changed to ==
//					return (ang) added after each ang =
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ANGLES MathLib::arctan(SLong dx, SLong dy)
{
//rdh, pd 28/5/98
	Float ang;
	int intang;

	ang = 10430.387 * FPATan ((Float)dx,(Float)dy);
	intang = (int)ang;
	return ((Angles)intang);
	
/*	
	ANGLES ang;
	SLong temp,temp2;



	if (dx>0)
		{
			if (dy==0)
				{
					ang = ANGLES_90Deg;
				}
			if (dy<0)
				{
//DeadCode JIM 26Sep96 					temp = dy;
					dy = -dy;
					if (dx<=dy)
						{
//DeadCode JIM 26Sep96 							temp = dx;
//DeadCode JIM 26Sep96 							dx = temp * 256;
							temp = SHDIVUNS(dx,8,dy);
//DeadCode JIM 26Sep96 							temp2 = ;
							ang= (Angles) (ANGLES_180Deg - matan[temp]);
							return (ang);
						}
					else  //i.e if dx>dy
						{
//DeadCode JIM 26Sep96 							temp = dy;
//DeadCode JIM 26Sep96 							dy = temp * 256;
							temp = SHDIVUNS(dy,8,dx);
//DeadCode JIM 26Sep96 							temp2 = ;
							ang = (Angles) (ANGLES_90Deg + matan[temp]);
							return (ang);
						}
				}
			if (dy>0)
				{
					if (dx<=dy)
						{
//DeadCode JIM 26Sep96 							temp = dx;
//DeadCode JIM 26Sep96 							dx = temp * 256;
							temp = SHDIVUNS(dx,8,dy);
//DeadCode JIM 26Sep96 							temp2 = ;
							ang= (Angles) matan[temp];
							return (ang);
						}
					else  //i.e if dx>dy
						{
//DeadCode JIM 26Sep96 							temp = dy;
//DeadCode JIM 26Sep96 							dy = temp * 256;
							temp = SHDIVUNS(dy,8,dx);
//DeadCode JIM 26Sep96 							temp2 = ;
							ang = (Angles) (ANGLES_90Deg - matan[temp]);
							return (ang);
						}
				}
		}

	if(dx<0)
		{
			dx=-dx;
			if (dy==0)
				{
					ang = ANGLES_270Deg;
					return (ang);
				}
			if (dy<0)
				{
//DeadCode JIM 26Sep96 					temp = dy;
					dy = -dy;
//DeadCode JIM 26Sep96 					temp = dx;
//DeadCode JIM 26Sep96 					dx = -temp;
					if (dx<=dy)
						{
//DeadCode JIM 26Sep96 							temp = dx;
//DeadCode JIM 26Sep96 							dx= temp * 256;
							temp = SHDIVUNS(dx,8,dy);
//DeadCode JIM 26Sep96 							temp2 = ;
							ang = (Angles) (matan[temp] + ANGLES_180Deg);
							return (ang);
						}
					else
						{
//DeadCode JIM 26Sep96 							temp = dy;
//DeadCode JIM 26Sep96 							dy = temp * 256;
							temp = SHDIVUNS(dy,8,dx);
//DeadCode JIM 26Sep96 							temp2 =;
							ang = (Angles) (ANGLES_270Deg - matan[temp]);
							return (ang);

						}
				}
			if (dy>0)
				{
//DeadCode JIM 26Sep96 					temp = dx;
//DeadCode JIM 26Sep96 					dx = - temp;
					if (dx<=dy)
						{
//DeadCode JIM 26Sep96 							temp = dx;
//DeadCode JIM 26Sep96 							dx = temp * 256;
							temp = SHDIVUNS(dx,8,dy);
//DeadCode JIM 26Sep96 							temp2 = ANGLES_0Deg;
							ang = (Angles)( - matan[temp]);
							return (ang);
						}
					else
						{
//DeadCode JIM 26Sep96 							temp = dy;
//DeadCode JIM 26Sep96 							dy = temp * 256;
							temp = SHDIVUNS(dy,8,dx);
//DeadCode JIM 26Sep96 							temp = ;
							ang = (Angles)( ANGLES_270Deg+matan[temp]);
							return (ang);
						}
				}
		}
//DeadCode JIM 26Sep96 	if (dx==0)
//DeadCode JIM 26Sep96 		{
			if (dy==0)
				{
					ang = ANGLES_0Deg;	//ANGLES_270Deg; - result not really defined//PD 24May96
				}
			if (dy<0)
				{
					ang = ANGLES_180Deg;
				}
			if (dy>0)
				{
					ang = ANGLES_0Deg;
				}
//DeadCode JIM 26Sep96 		}
	return (ang);
*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HighArcTan
//Author		Paul.   
//Date			Wed 3 Jul 1996
//
//Description	
//
//Inputs		Are words to prevent any overflows
//
//Returns	
//
//------------------------------------------------------------------------------
ANGLES MathLib::HighArcTan(SLong dx, SLong dy)
{
	ANGLES ang;

//DeadCode JIM 27Sep96 	SLong dx,dy;
	SLong temp,temp2;

	SWord	thistan;

//DeadCode JIM 27Sep96 	dx = deltax;
//DeadCode JIM 27Sep96 	dy = deltay;

	if (dx>0)
	{
		if (dy==0)	return (ANGLES_90Deg);

		if (dy<0)
		{
			dy = -dy;

			if (dx<=dy)
			{
				temp 	= SHDIVUNS(dx,16,dy);
				temp2	= temp & 0x0FF;
				temp	>>= 8;
				thistan = matan[temp];
				temp  	= matan[temp+1] - thistan;
				thistan	+= (temp*temp2)>>8;
				return 	((Angles ) (ANGLES_180Deg - thistan));
			}
			else  //i.e if dx>dy
			{
				temp 	= SHDIVUNS(dy,16,dx);
//DeadCode JIM 26Sep96 				temp	= (dy<<16)/dx;
				temp2	= temp &0x0FF;
				temp	>>= 8;
				thistan	= matan[temp];
				temp	= matan[temp+1] - thistan;
				thistan += (temp*temp2)>>8;
				return ((Angles ) (thistan + ANGLES_90Deg));
			}
		}
		if (dy>0)
		{
			if (dx<=dy)
			{
				temp 	= SHDIVUNS(dx,16,dy);
//DeadCode JIM 26Sep96 				temp	= (dx<<16)/dy;
				temp2	= temp & 0x0FF;
				temp	>>= 8;
				thistan	= matan[temp];
				temp	= matan[temp+1] - thistan;
				thistan += (temp*temp2)>>8;
				return ((Angles )thistan);
			}
			else  //i.e if dx>dy
			{
				temp 	= SHDIVUNS(dy,16,dx);
//DeadCode JIM 26Sep96 				temp 	= (dy<<16)/dx;
				temp2 	= temp & 0x0FF;
				temp	>>= 8;
				thistan = matan[temp];
				temp	= matan[temp+1] - thistan;
				thistan += (temp*temp2)>>8;
				return	((Angles )(ANGLES_90Deg - thistan));
			}
		}
	}

	if(dx<0)
	{
		if (dy==0)	return (ANGLES_270Deg);

		if (dy<0)
		{
			dy = -dy;
			dx = -dx;
			if (dx<=dy)
			{
				temp 	= SHDIVUNS(dx,16,dy);
//DeadCode JIM 26Sep96 				temp 	= (dx<<16)/dy;
				temp2 	= temp & 0x0FF;
				temp	>>= 8;
				thistan	= matan[temp];
				temp	= matan[temp+1] - thistan;
				thistan	+= (temp*temp2)>>8;
				return 	((Angles )(ANGLES_180Deg + thistan));
			}
			else
			{
				temp 	= SHDIVUNS(dy,16,dx);
//DeadCode JIM 26Sep96 				temp 	= (dy<<16)/dx;
				temp2 	= temp & 0x0FF;
				temp	>>= 8;
				thistan	= matan[temp];
				temp	= matan[temp+1] - thistan;
				thistan	+= (temp*temp2)>>8;
				return 	((Angles )(ANGLES_270Deg - thistan));
			}
		}
		if (dy>0)
		{
			dx = -dx;
			if (dx<=dy)
			{
				temp 	= SHDIVUNS(dx,16,dy);
//DeadCode JIM 26Sep96 				temp 	= (dx<<16)/dy;
				temp2 	= temp & 0x0FF;
				temp	>>=8;
				thistan	= matan[temp];
				temp	= matan[temp+1] - thistan;
				thistan	+= (temp*temp2)>>8;
				return 	((Angles )(ANGLES_0Deg - thistan));
			}
			else
			{
				temp 	= SHDIVUNS(dy,16,dx);
//DeadCode JIM 26Sep96 				temp 	= (dy<<16)/dx;
				temp2 	= temp & 0x0FF;
				temp	>>=	8;
				thistan	= matan[temp];
				temp	= matan[temp+1] - thistan;
				thistan	+= (temp*temp2)>>8;
				return	((Angles )(ANGLES_270Deg + thistan));
			}
		}
	}
//DeadCode JIM 26Sep96 	if (dx==0)
//DeadCode JIM 26Sep96 	{
//TempCode PD 04Jul96 		if (dy==0)
//TempCode PD 04Jul96 			_Error.EmitSysErr(__FILE__":ArcTan(0/0) is undefined");

		if (dy<0)	return (ANGLES_180Deg);

//DeadCode JIM 26Sep96 		if (dy>0)	return (ANGLES_0Deg);
//DeadCode JIM 26Sep96 	}
	return (ANGLES_0Deg);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	tan
//------------------------------------------------------------------------------
//Author		Paul. & Martin   
//Date		Tue 22 Aug 1995
//Modified	Mon 18 Sep 1995	
//			//RDH 30Nov95   not debugged!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
SWord MathLib::tan(ANGLES ang)
{
	SWord	tan_ang;

	if (!(ang & ANGLES_90Deg))										//RDH 30Nov95
		{
			ang = (Angles)(ang & ANGLES_90Deg-1);
			ang = (Angles)(ang>>6);
			tan_ang = tan_table[ang];
		}
	else
		{
			ang = (Angles)(ang & ANGLES_90Deg-1);
			ang = (Angles)(ang>>6);
//DeadCode DAW 27Sep00 			tan_ang = -tan_table[256-ang];						//RDH 19Feb96
			tan_ang = -tan_table[255-ang];						//DAW 27Sep00 - from bob
		}

	return(tan_ang);
}

SLong MathLib::hightan(ANGLES ang)
{
	ANGLES a0, angmod;
	SLong tan0, tan1, reqtan;

	if (!(ang & ANGLES_90Deg))										//RDH 30Nov95
	{
		angmod = (Angles)(ang & ANGLES_90Deg-1);
		a0 = angmod = (Angles)(angmod>>6);
		tan0 = tan_table[angmod];
		if (angmod < 255)
			angmod++;
		tan1 = tan_table[angmod];
	}
	else
	{
		angmod = (Angles)(ang & ANGLES_90Deg-1);
		a0 = angmod = (Angles)(angmod>>6);
//DeadCode DAW 27Sep00 		tan0 = -tan_table[256-angmod];						//RDH 19Feb96
		tan0 = -tan_table[255-angmod];							//DAW 27Sep00 from bob
		if (angmod > 0)
			angmod++;
		tan0 = -tan_table[255-angmod];							//DAW 27Sep00 from bob
//DeadCode DAW 27Sep00 		tan1 = -tan_table[256 - angmod];
	}

//	reqtan = 256 * tan0 + 256 * (tan1 - tan0) * (ang - a0 * 64)/64
	reqtan = 256 * tan0 + 4 * (tan1 - tan0) * (ang - a0 * 64);
	return (reqtan);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Author		Martin Alderton
//Date			Mon 18 Sep 1995
//
//Description	
//
//		SQRT( dx^2 + dy^2 + dz^2)
//	is dammed close to (one of)
//		MAX(dx,dy,dz) + MED(dx,dy,dz)/4 + MIN(dx,dy,dz)/4     +/- 13%
//	or								   
//		MAX(dx,dy,dz) + MED(dx,dy,dz)5/16 + MIN(dx,dy,dz)/4   +/-  9% (1/4=4/16)
//	or
//		MAX(dx,dy,dz) + MED(dx,dy,dz)11/32 + MIN(dx,dy,dz)/4  +/-  8%	(1/4=8/32)
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ULong MathLib::distance3d(SLong ddx, SLong dy, SLong dz)
{
_asm	{
			FILD	ddx
			FMUL	ST,ST(0)
			FILD	dy
			FMUL	ST,ST(0)
			FILD	dz
			FMUL	ST,ST(0)
			FADDP	ST(1),ST
			FADDP	ST(1),ST
			FSQRT
			FISTP	ddx
		}
		return	ddx;

/*	SLong	absdx,absdy,absdz,temp;

	absdx = (dx>=0)?dx:-dx;
	absdy = (dy>=0)?dy:-dy;
	absdz = (dz>=0)?dz:-dz;

	if(absdx<absdy)	{temp=absdy;absdy=absdx;absdx=temp;}

	if(absdx<absdz) {temp=absdz;absdz=absdx;absdx=temp;}

	if(absdy<absdz) {temp=absdy;absdy=absdz;absdz=temp;}

	//Sorted so that absdx > absdy > absdz

	//Try +/- 8% option

	temp = absdx;
	absdy >>= 2;
	temp += absdy;
	absdy >>= 2;
	temp += absdy;
	absdy >>= 1;
	temp += absdy;
	absdz >>= 2;
	temp += absdz;

	return(temp);*/
}
//Old_Code DAW 30Nov95 {
//Old_Code DAW 30Nov95 	ULong x,y,z,dist,a,b,c;
//Old_Code DAW 30Nov95 
//Old_Code DAW 30Nov95 	if (dx<0)
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			x = -dx;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	else
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			x = dx;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if (dy<0)
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			y = -dy;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	else
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			y = dy;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if (dz<0)
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			z = -dz;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	else
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			z = dz;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 
//Old_Code DAW 30Nov95 	if ((x>y) && (y>z))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=x;
//Old_Code DAW 30Nov95 			b=y;
//Old_Code DAW 30Nov95 			c=z;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((x>z) && (z>y))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=x;
//Old_Code DAW 30Nov95 			b=z;
//Old_Code DAW 30Nov95 			c=y;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((y>x) && (x>z))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=y;
//Old_Code DAW 30Nov95 			b=x;
//Old_Code DAW 30Nov95 			c=z;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((y>z) && (z>x))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=y;
//Old_Code DAW 30Nov95 			b=z;
//Old_Code DAW 30Nov95 			c=x;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((z>y) && (y>x))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=z;
//Old_Code DAW 30Nov95 			b=y;
//Old_Code DAW 30Nov95 			c=x;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((z>x) && (x>y))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=z;
//Old_Code DAW 30Nov95 			b=x;
//Old_Code DAW 30Nov95 			c=y;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((x==y) && (x>z))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=x;
//Old_Code DAW 30Nov95 			b=y;
//Old_Code DAW 30Nov95 			c=z;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((x==y) && (x<z))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=z;
//Old_Code DAW 30Nov95 			b=y;
//Old_Code DAW 30Nov95 			c=x;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((x==z) && (x>y))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=x;
//Old_Code DAW 30Nov95 			b=z;
//Old_Code DAW 30Nov95 			c=y;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((x==z) && (x<y))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=y;
//Old_Code DAW 30Nov95 			b=x;
//Old_Code DAW 30Nov95 			c=z;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((z==y) && (x>z))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=x;
//Old_Code DAW 30Nov95 			b=y;
//Old_Code DAW 30Nov95 			c=z;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	if ((z==y) && (x<z))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=z;
//Old_Code DAW 30Nov95 			b=y;
//Old_Code DAW 30Nov95 			c=x;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 	else if ((x==y) && (x==z))
//Old_Code DAW 30Nov95 		{
//Old_Code DAW 30Nov95 			a=x;
//Old_Code DAW 30Nov95 			b=z;
//Old_Code DAW 30Nov95 			c=y;
//Old_Code DAW 30Nov95 		}
//Old_Code DAW 30Nov95 		
//Old_Code DAW 30Nov95 	dist = (a+((11*b)/32)+(c/4));
//Old_Code DAW 30Nov95 	return(dist);
//Old_Code DAW 30Nov95 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Author		Martin Alderton
//Date			Mon 18 Sep 1995
//
//Description	
// This routine calculates the distance between two points using approximation.
// A = 45Deg * SHORT / LONG
// DISTANCE = LONG * COS(A) + SHORT * SIN(A)
//
//	debugged	cos (1) = 32768 (ANGLES_FRACT) in our system												//RDH 30Nov95
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord MathLib::Distance_Unsigned(UWord dx, UWord dy)
{
	UWord	temp;
	ANGLES   ang;
	SWord	sin_ang,
			cos_ang;

	if (dx < dy)
		{
		temp = dx;
		dx = dy;
		dy = temp;
		}

	if(dy!=0)
		{
 		temp = dy * ANGLES_45Deg /dx;							//RDH 30Nov95
		sin_cos((Angles) temp,sin_ang,cos_ang);
		temp = (sin_ang * dy /ANGLES_FRACT) + (cos_ang *dx /ANGLES_FRACT);
//DeadCode MGA 19Sep95 		return(temp);		
		}
	else
		{
		temp = dx;			//return(dx);
		}

	return(temp);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Author		Martin Alderton
//Date			Mon 18 Sep 1995
//
//Description	Changed to work with longs	//RDH 30Nov95
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ULong  MathLib::Distance2d(SLong dx, SLong dy)
{
	ULong x,y,dist,max;												  //JIM 20/12/98
	if (dx<0)
		{
			x = -dx;
		}
	else
		{
			x = dx;
		}
	if (dy<0)
		{
			y = -dy;
		}
	else
		{
			y = dy;
		}
//need to get to word before next routine						//RDH 30Nov95
	if	(x >y)
	{
		max =x;
	}else
	{
		max =y;
	}
	const ULong modifier = 1+ (max/32768);							  //JIM 20/12/98
	x =x/modifier;
	y =y/modifier;

	dist = MathLib::Distance_Unsigned(x,y);
	dist = dist * modifier;										//RDH 30Nov95
	return(dist);
}

ULong	MathLib::DistAbsSum(SLong x,SLong y,SLong z,SLong w)
{
	x=AbsSign(x);
	y=AbsSign(y);
	z=AbsSign(z);
	w=AbsSign(w);
	return	(x+y+z+w);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Intercept
//Author		R. Hyde 
//Date			Thu 30 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MathLib::Intercept (SLong deltax,SLong deltay,SLong deltaz,
				SLong &Range,SWord &HdgIntercept,SWord &PitchIntercept)
						 
{						 

//DeadCode JIM 26Sep96 	SLong	modifier,maxdelta;
//DeadCode JIM 26Sep96 	SWord	moddeltax,moddeltay,moddeltaz;
	ULong	range2d;

	Range = MathLib::distance3d(deltax,deltay,deltaz);
	range2d = MathLib::Distance2d(deltax,deltaz);
	HdgIntercept = MathLib::arctan(deltax,deltaz);
	PitchIntercept = MathLib::arctan(deltay,range2d);
}

void MathLib::HighIntercept (SLong deltax,SLong deltay,SLong deltaz,
				SLong &Range,SWord &HdgIntercept,SWord &PitchIntercept)
						 
{						 

//DeadCode JIM 26Sep96 	SLong	modifier,maxdelta;
//DeadCode JIM 26Sep96 	SWord	moddeltax,moddeltay,moddeltaz;
	ULong	range2d;

//DeadCode JIM 26Sep96 	Range = MathLib::distance3d(deltax,deltay,deltaz);
//DeadCode JIM 26Sep96 	range2d = MathLib::Distance2d(deltax,deltaz);
	HdgIntercept = MathLib::HighArcTan(deltax,deltaz);
	SWord	s,c;
	
	high_sin_cos((Angles)HdgIntercept,s,c);
	if (AbsSign(s)>AbsSign(c))
		range2d=SHDIVSIN(deltax,ANGLES_SHIFT,s);
	else
		range2d=SHDIVSIN(deltaz,ANGLES_SHIFT,c);
	PitchIntercept = MathLib::HighArcTan(deltay,range2d);
	high_sin_cos((Angles)PitchIntercept,s,c);
	if (AbsSign(s)>AbsSign(c))
		Range=SHDIVSIN(deltay,ANGLES_SHIFT,s);
	else
		Range=SHDIVSIN(range2d,ANGLES_SHIFT,c);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptHdg
//Author		Martin Alderton
//Date			Tue 19 Sep 1995
//
//Description	Changed to work with longs	//RDH 30Nov95
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MathLib::InterceptHdg(ULong Wx1, ULong Wz1, ULong Wx2, ULong Wz2, ULong &dist, UWord &hdg)
{
	
	SLong dx,dy;

	dx = Wx2 - Wx1;
	dy = Wz2 - Wz1;
	dist = Distance2d(dx,dy);
	hdg = arctan(dx,dy);
	
}
		
//DeadCode DAW 28Nov95 mathlib	Math_Lib;

ULong	MathLib::a2iend(string&	source)
{
	ULong	retval=0;
	while ((*source>='0') && (*source<='9'))
		retval=retval*10+(*(source++)&0x0f);
	return(retval);
}

ULong	MathLib::a2iend				//returns numeric value found
			(	string&	source,		//input pointer is pushed forward
				ULong& lengthdec)	//remaining characters counter modified
{
	ULong	retval=0;
	while ((*source>='0') && (*source<='9'))
	{
		retval=retval*10+(*(source++)&0x0f);
		lengthdec--;
	}
	return(retval);
}
//DeadCode JIM 02May96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 02May96 //Procedure		Pos
//DeadCode JIM 02May96 //Author		R. Hyde 
//DeadCode JIM 02May96 //Date			Fri 27 Oct 1995
//DeadCode JIM 02May96 //
//DeadCode JIM 02May96 //Description	New, efficient inline version.
//DeadCode JIM 02May96 //
//DeadCode JIM 02May96 //Inputs		
//DeadCode JIM 02May96 //
//DeadCode JIM 02May96 //Returns	
//DeadCode JIM 02May96 //
//DeadCode JIM 02May96 //------------------------------------------------------------------------------
//DeadCode JIM 02May96 void MathLib::Pos (SWord inputvar, SWord &posvar,SWord &signvar)
//DeadCode JIM 02May96 
//DeadCode JIM 02May96 {
//DeadCode JIM 02May96 	if (inputvar >= 0)
//DeadCode JIM 02May96 	{
//DeadCode JIM 02May96  		signvar = POSITIVE;
//DeadCode JIM 02May96 		posvar = inputvar;
//DeadCode JIM 02May96 	}else
//DeadCode JIM 02May96 	{
//DeadCode JIM 02May96 		signvar = NEGATIVE;
//DeadCode JIM 02May96 		if (inputvar == -32768)	//I CANT DO THIS EFFICIENTLY!	//RDH 18Dec95
//DeadCode JIM 02May96 		{						//WE NEVER USED TO DO IT!		//RDH 18Dec95
//DeadCode JIM 02May96 			posvar = 32767;										//RDH 18Dec95
//DeadCode JIM 02May96 		}else													//RDH 18Dec95
//DeadCode JIM 02May96 		{
//DeadCode JIM 02May96 			posvar = (SWord)-inputvar;
//DeadCode JIM 02May96 		}
//DeadCode JIM 02May96 	}
//DeadCode JIM 02May96 
//DeadCode JIM 02May96 }
//DeadCode JIM 02May96 



//All dates are in seconds and are based on the xx01 year of the century
//For Flying Corps the origin is midnight on 1st Jan 1917
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MonthFromDays
//Author		R. Hyde 
//Date			Thu 4 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord MathLib::MonthFromDays (SWord daysinyear, SWord &daysinfullmonth, SWord leapyear)
{
	SWord	truedays;
	SWord	i = 0;
	daysinfullmonth = 0;
	truedays = Days_in_Month[i];
	while (daysinyear >truedays)
	{
		daysinfullmonth += truedays;
		daysinyear -= truedays;
		i++;
		truedays = Days_in_Month[i];
		if ((i == 1) && leapyear == TRUE)
		{
			truedays += 1;
		}

	}
	return (i);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DateFromSecs
//Author		R. Hyde 
//Date			Thu 4 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MathLib::DateFromSecs (SLong secs,SWord &day, SWord &month, SWord &year)
{

	SWord	daysinfullyears;
	SWord	daysinyear,leapyear;
	SWord	daysinfullmonths;

	day = 1 + (secs / SECSPERDAY);
	year = YearFromDays (day,daysinfullyears,leapyear);
	daysinyear = day - daysinfullyears;
	month =  MonthFromDays (daysinyear,daysinfullmonths,leapyear);
	day = daysinyear -  daysinfullmonths;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TimeFromSecs
//Author		R. Hyde 
//Date			Thu 4 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MathLib::TimeFromSecs (SLong secs,SWord &hr, SWord &mins)
{


	hr = secs / SECSPERHR;
	mins = ((secs- (SECSPERHR * hr)) / SECSPERMIN);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SunPosFromSecs
//Author		Paul.   
//Date			Mon 22 Apr 1996
//
//Description	returns the angle of the sun ANGLES_0Deg 	= 	6am
//											 ANGELS_90Deg	= 	12am
//											 ANGLES_180Deg	=	6pm
//
//				//JIM 03Jun96
//				This is not what I want in AI. 
//				For there, I want a relative heading and pitch.
//				Also, I want the value up to 2,000 times per second
//				We only need to update the sun position about every 20 secs
//				as this gives 2000 updates /12 hours
//
//Returns	
//
//------------------------------------------------------------------------------
void MathLib::SunPosFromSecs(SLong secs,ANGLES& pos)
{
	SLong	spd = secs % SECSPERDAY;
	spd <<= 12;
	spd /= SECSPERDAY;
	pos = (Angles )((spd<<4)-ANGLES_90Deg);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DofCampFromSecs
//Author		R. Hyde 
//Date			Thu 4 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord MathLib::DofCampFromSecs (SLong secs,SLong beginning)
{
	SWord	day;
	day = (secs - beginning) / SECSPERDAY;
	return (day);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		YearFromDays
//Author		R. Hyde 
//Date			Thu 4 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord MathLib::YearFromDays (SWord day, SWord &daysinfullyears, SWord &leapyear)
{
	SWord	year4,years;

	day -= 1;		//handle last day of year
	year4 = 4 * (day / DAYSPER4YEAR);
	years = day % DAYSPER4YEAR;
	years = years / DAYSPERYEAR;

	if (years == 3)
	{
		leapyear =TRUE;
	}else
	{
		leapyear = FALSE;
	}

	daysinfullyears =  year4 *  DAYSPER4YEAR / 4;
	daysinfullyears +=  DAYSPERYEAR * years;

	years = years + year4;
	return (years);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		YearFromSecs
//Author		R. Hyde 
//Date			Thu 4 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord MathLib::YearFromSecs (SLong secs)
{
	SWord	daysinfullyears,leapyear;
	SWord	years,day;

	day = secs / SECSPERDAY;
	years = YearFromDays (day,daysinfullyears,leapyear);
	return (years);

}
	
RndVal	MathLib::rnd()
{
	rndcount++;													//ARM 03Sep96

// 	return RND10PC;

	if (rndcount>=MAX_RND)
	{	//54 == 00110110
		UWord b;
		if (bval>20)
			if (bval>40)											  //JIM 26/03/99
				b=rndlookup[bval-(rndcount&31)];
			else
				b=rndlookup[bval+(rndcount&31)-16];
		else
			b=rndlookup[bval+(rndcount&31)];
		UWord c;
		if (cval>20)
			if (cval>40)											  //JIM 26/03/99
				c=rndlookup[cval-((rndcount>>5)&31)];
			else
				c=rndlookup[cval+((rndcount>>5)&31)-16];
		else
			c=rndlookup[cval+((rndcount>>5)&31)];

		return RndVal(UWord(b+c));									  //RJS 1/20/99
	}
	else
	{
	 	UWord	b=rndlookup[bval++];
		if (bval>54)	bval=0;
		b+=rndlookup[cval];
		rndlookup[cval++]=b;
		if (cval>54)	cval=0;
		return(RndVal)(b);
	}

}
