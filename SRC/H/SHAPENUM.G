//------------------------------------------------------------------------------
//Filename       shapenum.g
//System
//Author         Generated File
//Date           Feb 15 1996
//Description    Enums for shapes go here...
//------------------------------------------------------------------------------
#ifndef	SHAPENUM_INCLUDED
#define	SHAPENUM_INCLUDED
MINMAX	(ShapeNum,0,1023);
MINMAX	(SShpNum,0,1023);
MINMAX	(GroupNum,0,1023);
MINMAX	(SingleNum,0,1023);
inline	ShapeNum	operator+(SShpNum sshp)	{return(ShapeNum) sshp;}
inline	ShapeNum	operator+(GroupNum sshp)	{return(ShapeNum) sshp;}
inline	ShapeNum	operator+(SingleNum sshp){return(ShapeNum) sshp;}

const	ShapeNum	BEXP		=	(ShapeNum)   1;
const	ShapeNum	BSMKE		=	(ShapeNum)   2;
const	ShapeNum	EXPLO		=	(ShapeNum)   3;
const	ShapeNum	DOT		=	(ShapeNum)   4;
const	ShapeNum	SPARK		=	(ShapeNum)   5;
const	ShapeNum	DSPARK		=	(ShapeNum)   6;
const	ShapeNum	CRATER		=	(ShapeNum)   7;
const	ShapeNum	HOLE		=	(ShapeNum)   8;
const	ShapeNum	FIRE		=	(ShapeNum)   9;
const	ShapeNum	DEB1		=	(ShapeNum)  10;
const	ShapeNum	DEB2		=	(ShapeNum)  11;
const	ShapeNum	DEB3		=	(ShapeNum)  12;
const	ShapeNum	DEB6		=	(ShapeNum)  13;
const	ShapeNum	DEB5		=	(ShapeNum)  14;
const	ShapeNum	DEB4		=	(ShapeNum)  15;
const	ShapeNum	DEB7		=	(ShapeNum)  16;
const	ShapeNum	SMOKE		=	(ShapeNum) 257;
const	ShapeNum	RSMOKE		=	(ShapeNum) 258;
const	ShapeNum	BULLET		=	(ShapeNum) 259;
const	ShapeNum	SMLFIR		=	(ShapeNum)  17;
const	ShapeNum	FLMONN		=	(ShapeNum) 260;
const	ShapeNum	EMPTY2		=	(ShapeNum) 261;
const	ShapeNum	PCHUTE		=	(ShapeNum) 262;
const	ShapeNum	TROOP1		=	(ShapeNum)  18;
const	ShapeNum	VAPSHP		=	(ShapeNum)  19;
const	ShapeNum	SMKTRL		=	(ShapeNum)  20;
const	ShapeNum	WINDSC		=	(ShapeNum)  21;
const	ShapeNum	SUN		=	(ShapeNum)  22;
const	ShapeNum	SDUST		=	(ShapeNum)  23;
const	ShapeNum	BDUST		=	(ShapeNum)  24;
const	ShapeNum	WRECK		=	(ShapeNum) 263;
const	ShapeNum	PDEATH		=	(ShapeNum)  25;
const	ShapeNum	MIG15		=	(ShapeNum) 264;
const	ShapeNum	F86		=	(ShapeNum) 265;
const	ShapeNum	F80		=	(ShapeNum) 266;
const	ShapeNum	F82		=	(ShapeNum) 267;
const	ShapeNum	F9F		=	(ShapeNum) 268;
const	ShapeNum	B29		=	(ShapeNum) 269;
const	ShapeNum	YAK9		=	(ShapeNum) 270;
const	ShapeNum	CORS		=	(ShapeNum) 271;
const	ShapeNum	SKYR		=	(ShapeNum) 272;
const	ShapeNum	F51		=	(ShapeNum) 273;
const	ShapeNum	FURY		=	(ShapeNum) 274;
const	ShapeNum	FLY		=	(ShapeNum) 275;
const	ShapeNum	MET		=	(ShapeNum) 276;
const	ShapeNum	C54		=	(ShapeNum) 277;
const	ShapeNum	F84		=	(ShapeNum) 278;
const	ShapeNum	F86SHD		=	(ShapeNum) 279;
const	ShapeNum	F84SHD		=	(ShapeNum) 280;
const	ShapeNum	F80SHD		=	(ShapeNum) 281;
const	ShapeNum	F51SHD		=	(ShapeNum) 282;
const	ShapeNum	M15SHD		=	(ShapeNum) 283;
const	ShapeNum	CTWR1		=	(ShapeNum)  26;
const	ShapeNum	SHDK14		=	(ShapeNum)  27;
const	ShapeNum	DUMMY2		=	(ShapeNum)  28;
const	ShapeNum	DUMMY3		=	(ShapeNum)  29;
const	ShapeNum	DUMMY4		=	(ShapeNum)  30;
const	ShapeNum	DUMMY5		=	(ShapeNum)  31;
const	ShapeNum	DUMMY6		=	(ShapeNum)  32;
const	ShapeNum	DUMMY7		=	(ShapeNum)  33;
const	ShapeNum	DUMMY8		=	(ShapeNum) 284;
const	ShapeNum	DUMMY9		=	(ShapeNum)  34;
const	ShapeNum	DUMMY1		=	(ShapeNum)  35;
const	ShapeNum	HNGK14		=	(ShapeNum)  36;
const	ShapeNum	FIREB		=	(ShapeNum) 285;
const	ShapeNum	FTRUCK		=	(ShapeNum) 286;
const	ShapeNum	START		=	(ShapeNum)  37;
const	ShapeNum	MUSHY		=	(ShapeNum) 287;
const	ShapeNum	RUNSEC		=	(ShapeNum)  38;
const	ShapeNum	RUNEND		=	(ShapeNum)  39;
const	ShapeNum	GCLONE		=	(ShapeNum) 288;
const	ShapeNum	CMIG15		=	(ShapeNum) 289;
const	ShapeNum	METAL1		=	(ShapeNum)  40;
const	ShapeNum	RUNLIT		=	(ShapeNum)  41;
const	ShapeNum	CART1		=	(ShapeNum) 290;
const	ShapeNum	TANKER		=	(ShapeNum) 291;
const	ShapeNum	TCOAL		=	(ShapeNum)  42;
const	ShapeNum	THAUL		=	(ShapeNum)  43;
const	ShapeNum	CRANE		=	(ShapeNum)  44;
const	ShapeNum	TWOOD		=	(ShapeNum)  45;
const	ShapeNum	HUT		=	(ShapeNum)  46;
const	ShapeNum	HUT01		=	(ShapeNum)  47;
const	ShapeNum	HUT02		=	(ShapeNum)  48;
const	ShapeNum	HUT03		=	(ShapeNum)  49;
const	ShapeNum	CIVI01		=	(ShapeNum)  50;
const	ShapeNum	CIVI02		=	(ShapeNum)  51;
const	ShapeNum	CIVI03		=	(ShapeNum)  52;
const	ShapeNum	CIVI04		=	(ShapeNum)  53;
const	ShapeNum	CIVI05		=	(ShapeNum)  54;
const	ShapeNum	CIVI06		=	(ShapeNum)  55;
const	ShapeNum	TANKC		=	(ShapeNum) 292;
const	ShapeNum	TROOPC		=	(ShapeNum)  56;
const	ShapeNum	SUPPLY		=	(ShapeNum)  57;
const	ShapeNum	TPIPE		=	(ShapeNum)  58;
const	ShapeNum	TCABLE		=	(ShapeNum)  59;
const	ShapeNum	TEMPTY		=	(ShapeNum)  60;
const	ShapeNum	TBACK		=	(ShapeNum)  61;
const	ShapeNum	TPINC		=	(ShapeNum)  62;
const	ShapeNum	TROLL		=	(ShapeNum)  63;
const	ShapeNum	TGOODS		=	(ShapeNum)  64;
const	ShapeNum	GRNDD1		=	(ShapeNum)  65;
const	ShapeNum	GRNDD2		=	(ShapeNum)  66;
const	ShapeNum	GRNDD3		=	(ShapeNum)  67;
const	ShapeNum	GRNDD4		=	(ShapeNum)  68;
const	ShapeNum	GRNDD5		=	(ShapeNum)  69;
const	ShapeNum	GRNDD6		=	(ShapeNum)  70;
const	ShapeNum	GRNDD7		=	(ShapeNum)  71;
const	ShapeNum	GRNDD8		=	(ShapeNum)  72;
const	ShapeNum	SHED		=	(ShapeNum)  73;
const	ShapeNum	FUELDE		=	(ShapeNum)  74;
const	ShapeNum	BOAT		=	(ShapeNum) 293;
const	ShapeNum	TENT1		=	(ShapeNum)  75;
const	ShapeNum	TENT2		=	(ShapeNum)  76;
const	ShapeNum	TENT3		=	(ShapeNum)  77;
const	ShapeNum	TENT4		=	(ShapeNum)  78;
const	ShapeNum	TENT5		=	(ShapeNum)  79;
const	ShapeNum	HANGER		=	(ShapeNum)  80;
const	ShapeNum	FTANK		=	(ShapeNum) 294;
const	ShapeNum	CIVI07		=	(ShapeNum)  81;
const	ShapeNum	CIVI08		=	(ShapeNum)  82;
const	ShapeNum	CIVI09		=	(ShapeNum)  83;
const	ShapeNum	CIVI10		=	(ShapeNum)  84;
const	ShapeNum	DUMY10		=	(ShapeNum) 295;
const	ShapeNum	DUMY11		=	(ShapeNum)  85;
const	ShapeNum	DUMY12		=	(ShapeNum)  86;
const	ShapeNum	DUMY13		=	(ShapeNum)  87;
const	ShapeNum	DUMY14		=	(ShapeNum)  88;
const	ShapeNum	DUMY15		=	(ShapeNum)  89;
const	ShapeNum	DUMY16		=	(ShapeNum)  90;
const	ShapeNum	DUMY17		=	(ShapeNum)  91;
const	ShapeNum	DUMY18		=	(ShapeNum)  92;
const	ShapeNum	DUMY19		=	(ShapeNum)  93;
const	ShapeNum	DUMY20		=	(ShapeNum)  94;
const	ShapeNum	T6		=	(ShapeNum) 296;
const	ShapeNum	HO3S		=	(ShapeNum)  95;
const	ShapeNum	C47		=	(ShapeNum) 297;
const	ShapeNum	FOX		=	(ShapeNum)  96;
const	ShapeNum	SBAG		=	(ShapeNum)  97;
const	ShapeNum	SLIT		=	(ShapeNum)  98;
const	ShapeNum	BUNK		=	(ShapeNum)  99;
const	ShapeNum	UNBATT		=	(ShapeNum) 100;
const	ShapeNum	CHBATT		=	(ShapeNum) 101;
const	ShapeNum	UNHOW		=	(ShapeNum) 102;
const	ShapeNum	CHART		=	(ShapeNum) 103;
const	ShapeNum	UNMORT		=	(ShapeNum) 104;
const	ShapeNum	CHMORT		=	(ShapeNum) 105;
const	ShapeNum	CHINFT		=	(ShapeNum) 106;
const	ShapeNum	UNINFT		=	(ShapeNum) 107;
const	ShapeNum	WORSEL		=	(ShapeNum) 108;
const	ShapeNum	T34		=	(ShapeNum) 298;
const	ShapeNum	HALFT		=	(ShapeNum) 299;
const	ShapeNum	JEEP1		=	(ShapeNum) 300;
const	ShapeNum	UNTANK		=	(ShapeNum) 301;
const	ShapeNum	JEEP2		=	(ShapeNum) 302;
const	ShapeNum	TTRUCK		=	(ShapeNum) 303;
const	ShapeNum	SFTRCK		=	(ShapeNum) 304;
const	ShapeNum	RTRUCK		=	(ShapeNum) 305;
const	ShapeNum	HTRUCK		=	(ShapeNum) 306;
const	ShapeNum	CHTRCK		=	(ShapeNum) 307;
const	ShapeNum	UNTRCK		=	(ShapeNum) 308;
const	ShapeNum	STEPTO		=	(ShapeNum) 309;
const	ShapeNum	HARLEY		=	(ShapeNum) 310;
const	ShapeNum	MORSEL		=	(ShapeNum) 109;
const	ShapeNum	GHANDI		=	(ShapeNum) 110;
const	ShapeNum	FISHR		=	(ShapeNum) 111;
const	ShapeNum	BARGE		=	(ShapeNum) 311;
const	ShapeNum	SAMPAN		=	(ShapeNum) 112;
const	ShapeNum	CARGO		=	(ShapeNum) 113;
const	ShapeNum	CHLBAA		=	(ShapeNum) 114;
const	ShapeNum	CHSBAA		=	(ShapeNum) 115;
const	ShapeNum	CH12ML		=	(ShapeNum) 116;
const	ShapeNum	CH37ML		=	(ShapeNum) 117;
const	ShapeNum	UNSBAA		=	(ShapeNum) 118;
const	ShapeNum	UNLBAA		=	(ShapeNum) 119;
const	ShapeNum	MOBILA		=	(ShapeNum) 312;
const	ShapeNum	FUELD		=	(ShapeNum) 120;
const	ShapeNum	FUELS		=	(ShapeNum) 121;
const	ShapeNum	AMMOC		=	(ShapeNum) 122;
const	ShapeNum	AMMOS		=	(ShapeNum) 123;
const	ShapeNum	FOODB		=	(ShapeNum) 124;
const	ShapeNum	FOODS		=	(ShapeNum) 125;
const	ShapeNum	FAKEC		=	(ShapeNum) 126;
const	ShapeNum	FAKER		=	(ShapeNum) 127;
const	ShapeNum	CTWR2		=	(ShapeNum) 128;
const	ShapeNum	TRAM		=	(ShapeNum) 313;
const	ShapeNum	ETRUCK		=	(ShapeNum) 314;
const	ShapeNum	RMAST		=	(ShapeNum) 129;
const	ShapeNum	PMAST		=	(ShapeNum) 130;
const	ShapeNum	BULL		=	(ShapeNum) 131;
const	ShapeNum	CARNE2		=	(ShapeNum) 132;
const	ShapeNum	COOLIE		=	(ShapeNum) 133;
const	ShapeNum	SCAFF		=	(ShapeNum) 134;
const	ShapeNum	PUFF		=	(ShapeNum) 135;
const	ShapeNum	LCRANE		=	(ShapeNum) 136;
const	ShapeNum	BMB100		=	(ShapeNum) 315;
const	ShapeNum	BMB500		=	(ShapeNum) 316;
const	ShapeNum	FLUTTR		=	(ShapeNum) 137;
const	ShapeNum	DRIFTR		=	(ShapeNum) 138;
const	ShapeNum	IL10		=	(ShapeNum) 317;
const	ShapeNum	PO2		=	(ShapeNum) 318;
const	ShapeNum	VSCON		=	(ShapeNum) 139;
const	ShapeNum	VSROCK		=	(ShapeNum) 140;
const	ShapeNum	VSVAP		=	(ShapeNum) 141;
const	ShapeNum	VSBSMK		=	(ShapeNum) 142;
const	ShapeNum	VSFSMK		=	(ShapeNum) 143;
const	ShapeNum	VSGSMK		=	(ShapeNum) 144;
const	ShapeNum	F86RTL		=	(ShapeNum) 145;
const	ShapeNum	F86RTR		=	(ShapeNum) 146;
const	ShapeNum	F51RTL		=	(ShapeNum) 147;
const	ShapeNum	F51RTR		=	(ShapeNum) 148;
const	ShapeNum	F80RT		=	(ShapeNum) 149;
const	ShapeNum	F84RT		=	(ShapeNum) 150;
const	ShapeNum	STBOMB		=	(ShapeNum) 151;
const	ShapeNum	F86BMB		=	(ShapeNum) 152;
const	ShapeNum	F80BMB		=	(ShapeNum) 153;
const	ShapeNum	F84BMB		=	(ShapeNum) 154;
const	ShapeNum	F51BMB		=	(ShapeNum) 155;
const	ShapeNum	F86FU		=	(ShapeNum) 156;
const	ShapeNum	F80FUL		=	(ShapeNum) 157;
const	ShapeNum	F80FUR		=	(ShapeNum) 158;
const	ShapeNum	F84FUL		=	(ShapeNum) 159;
const	ShapeNum	F84FUR		=	(ShapeNum) 160;
const	ShapeNum	M15FU		=	(ShapeNum) 161;
const	ShapeNum	F51FU		=	(ShapeNum) 162;
const	ShapeNum	ROCKET		=	(ShapeNum) 319;
const	ShapeNum	BOMB		=	(ShapeNum) 320;
const	ShapeNum	TPM15		=	(ShapeNum) 321;
const	ShapeNum	TPF86		=	(ShapeNum) 322;
const	ShapeNum	TPF80L		=	(ShapeNum) 323;
const	ShapeNum	TPF80R		=	(ShapeNum) 324;
const	ShapeNum	TPF84L		=	(ShapeNum) 325;
const	ShapeNum	TPF84R		=	(ShapeNum) 326;
const	ShapeNum	TPF51		=	(ShapeNum) 327;
const	ShapeNum	CLOUD1		=	(ShapeNum) 163;
const	ShapeNum	B26		=	(ShapeNum) 328;
const	ShapeNum	EMPTY		=	(ShapeNum) 513;
const	ShapeNum	KIMPO		=	(ShapeNum) 514;
const	ShapeNum	CONSHP		=	(ShapeNum) 164;
const	ShapeNum	ROKSHP		=	(ShapeNum) 165;
const	ShapeNum	SMKSHP		=	(ShapeNum) 166;
const	ShapeNum	SHUNT		=	(ShapeNum) 329;
const	ShapeNum	DUSSHP		=	(ShapeNum) 167;
const	ShapeNum	VSDUST		=	(ShapeNum) 168;
const	ShapeNum	LNHALB		=	(ShapeNum) 169;
const	ShapeNum	LNHALS		=	(ShapeNum) 170;
const	ShapeNum	LNSOLS		=	(ShapeNum) 171;
const	ShapeNum	SCNSHP		=	(ShapeNum) 172;
const	ShapeNum	VSSCON		=	(ShapeNum) 173;
const	ShapeNum	AFDL		=	(ShapeNum) 515;
const	ShapeNum	AFDS		=	(ShapeNum) 516;
const	ShapeNum	MDM		=	(ShapeNum) 517;
const	ShapeNum	MDL		=	(ShapeNum) 518;
const	ShapeNum	MDXL		=	(ShapeNum) 519;
const	ShapeNum	CTL		=	(ShapeNum) 520;
const	ShapeNum	CTS		=	(ShapeNum) 521;
const	ShapeNum	OPPSL		=	(ShapeNum) 522;
const	ShapeNum	OPPSM		=	(ShapeNum) 523;
const	ShapeNum	OPPSS		=	(ShapeNum) 524;
const	ShapeNum	HREW		=	(ShapeNum) 525;
const	ShapeNum	HRNS		=	(ShapeNum) 526;
const	ShapeNum	RRNS		=	(ShapeNum) 527;
const	ShapeNum	RREW		=	(ShapeNum) 528;
const	ShapeNum	RRNWSE		=	(ShapeNum) 529;
const	ShapeNum	RRNESW		=	(ShapeNum) 530;
const	ShapeNum	BRNS		=	(ShapeNum) 531;
const	ShapeNum	BREW		=	(ShapeNum) 532;
const	ShapeNum	WF1S		=	(ShapeNum) 533;
const	ShapeNum	WF2S		=	(ShapeNum) 534;
const	ShapeNum	WF3M		=	(ShapeNum) 535;
const	ShapeNum	WF4M		=	(ShapeNum) 536;
const	ShapeNum	WF5M		=	(ShapeNum) 537;
const	ShapeNum	WF6L		=	(ShapeNum) 538;
const	ShapeNum	WF7L		=	(ShapeNum) 539;
const	ShapeNum	SYARD		=	(ShapeNum) 540;
const	ShapeNum	LAREA		=	(ShapeNum) 541;
const	ShapeNum	SDISP1		=	(ShapeNum) 542;
const	ShapeNum	SDISP2		=	(ShapeNum) 543;
const	ShapeNum	SDISP3		=	(ShapeNum) 544;
const	ShapeNum	CITY1		=	(ShapeNum) 545;
const	ShapeNum	CITY2		=	(ShapeNum) 546;
const	ShapeNum	TWN1		=	(ShapeNum) 547;
const	ShapeNum	TWN2		=	(ShapeNum) 548;
const	ShapeNum	TWN3EW		=	(ShapeNum) 549;
const	ShapeNum	V1NS		=	(ShapeNum) 550;
const	ShapeNum	V2EW		=	(ShapeNum) 551;
const	ShapeNum	V3NESW		=	(ShapeNum) 552;
const	ShapeNum	V4NWSE		=	(ShapeNum) 553;
const	ShapeNum	LBFLAK		=	(ShapeNum) 554;
const	ShapeNum	SAAA		=	(ShapeNum) 555;
const	ShapeNum	MHQ		=	(ShapeNum) 556;
const	ShapeNum	TF		=	(ShapeNum) 557;
const	ShapeNum	CHUTE2		=	(ShapeNum) 330;
const	ShapeNum	VSMUD		=	(ShapeNum) 174;
const	ShapeNum	VSWVAP		=	(ShapeNum) 175;
const	ShapeNum	CPTM15		=	(ShapeNum) 331;
const	ShapeNum	CPTF80		=	(ShapeNum) 332;
const	ShapeNum	CPTF84		=	(ShapeNum) 333;
const	ShapeNum	CPTF51		=	(ShapeNum) 334;
const	ShapeNum	CPTF86		=	(ShapeNum) 335;
const	ShapeNum	CLOUD2		=	(ShapeNum) 176;
const	ShapeNum	CLOUD3		=	(ShapeNum) 177;
const	ShapeNum	CLOUD4		=	(ShapeNum) 178;
const	ShapeNum	GNDEXP		=	(ShapeNum) 179;
const	ShapeNum	AIREXP		=	(ShapeNum) 180;
const	ShapeNum	BULWAT		=	(ShapeNum) 181;
const	ShapeNum	BULGND		=	(ShapeNum) 182;
const	ShapeNum	FIREB2		=	(ShapeNum) 183;
const	ShapeNum	SOOT		=	(ShapeNum) 184;
const	ShapeNum	SOOT2		=	(ShapeNum) 185;
const	ShapeNum	RDSEG1		=	(ShapeNum) 186;
const	ShapeNum	RDSEG2		=	(ShapeNum) 187;
const	ShapeNum	RDSEG3		=	(ShapeNum) 188;
const	ShapeNum	RLSEG1		=	(ShapeNum) 189;
const	ShapeNum	RLSEG2		=	(ShapeNum) 190;
const	ShapeNum	RLSEG3		=	(ShapeNum) 191;
const	ShapeNum	RLSEG4		=	(ShapeNum) 192;
const	ShapeNum	RLSEG5		=	(ShapeNum) 193;
const	ShapeNum	RLSEG6		=	(ShapeNum) 194;
const	ShapeNum	RLSEG7		=	(ShapeNum) 195;
const	ShapeNum	RLSEG8		=	(ShapeNum) 196;
const	ShapeNum	RLSEG9		=	(ShapeNum) 197;
const	ShapeNum	RLSE10		=	(ShapeNum) 198;
const	ShapeNum	RDLNS		=	(ShapeNum) 558;
const	ShapeNum	RDLEW		=	(ShapeNum) 559;
const	ShapeNum	RDSNS		=	(ShapeNum) 560;
const	ShapeNum	RDSEW		=	(ShapeNum) 561;
const	ShapeNum	RLL1NS		=	(ShapeNum) 562;
const	ShapeNum	RLL2NS		=	(ShapeNum) 563;
const	ShapeNum	RLL3NS		=	(ShapeNum) 564;
const	ShapeNum	RLL4NS		=	(ShapeNum) 565;
const	ShapeNum	RLS1NS		=	(ShapeNum) 566;
const	ShapeNum	RLS2NS		=	(ShapeNum) 567;
const	ShapeNum	RLS3NS		=	(ShapeNum) 568;
const	ShapeNum	RLS4NS		=	(ShapeNum) 569;
const	ShapeNum	RLL1EW		=	(ShapeNum) 570;
const	ShapeNum	RLL2EW		=	(ShapeNum) 571;
const	ShapeNum	RLL3EW		=	(ShapeNum) 572;
const	ShapeNum	RLL4EW		=	(ShapeNum) 573;
const	ShapeNum	RLS1EW		=	(ShapeNum) 574;
const	ShapeNum	RLS2EW		=	(ShapeNum) 575;
const	ShapeNum	RLS3EW		=	(ShapeNum) 576;
const	ShapeNum	RLS4EW		=	(ShapeNum) 577;
const	ShapeNum	METSHD		=	(ShapeNum) 336;
const	ShapeNum	B26SHD		=	(ShapeNum) 337;
const	ShapeNum	B29SHD		=	(ShapeNum) 338;
const	ShapeNum	F82SHD		=	(ShapeNum) 339;
const	ShapeNum	T6SHD		=	(ShapeNum) 340;
const	ShapeNum	ILSHD		=	(ShapeNum) 341;
const	ShapeNum	CORSHD		=	(ShapeNum) 342;
const	ShapeNum	HO3SHD		=	(ShapeNum) 343;
const	ShapeNum	C47SHD		=	(ShapeNum) 344;
const	ShapeNum	C54SHD		=	(ShapeNum) 345;
const	ShapeNum	YAKSHD		=	(ShapeNum) 346;
const	ShapeNum	DRTYX		=	(ShapeNum) 347;
const	ShapeNum	FIRYX		=	(ShapeNum) 348;
const	ShapeNum	TREE1		=	(ShapeNum) 199;
const	ShapeNum	TREE2		=	(ShapeNum) 200;
const	ShapeNum	TREE3		=	(ShapeNum) 201;
const	ShapeNum	TREE4		=	(ShapeNum) 202;
const	ShapeNum	WATSHP		=	(ShapeNum) 349;
const	ShapeNum	VSWATR		=	(ShapeNum) 350;
const	ShapeNum	SPLASH		=	(ShapeNum) 351;
const	ShapeNum	WRECKP		=	(ShapeNum) 352;
const	ShapeNum	WRECKT		=	(ShapeNum) 353;
const	ShapeNum	WRECKB		=	(ShapeNum) 354;
const	ShapeNum	MAP		=	(ShapeNum) 203;
const	ShapeNum	MAPZ		=	(ShapeNum) 204;
const	ShapeNum	MAPBLU		=	(ShapeNum) 355;
const	ShapeNum	MAPRED		=	(ShapeNum) 356;
const	ShapeNum	SLITN		=	(ShapeNum) 578;
const	ShapeNum	SLITNE		=	(ShapeNum) 579;
const	ShapeNum	SLITNW		=	(ShapeNum) 580;
const	ShapeNum	SLITS		=	(ShapeNum) 581;
const	ShapeNum	SLITSW		=	(ShapeNum) 582;
const	ShapeNum	SLITSE		=	(ShapeNum) 583;
const	ShapeNum	BUNKN		=	(ShapeNum) 584;
const	ShapeNum	BUNKNE		=	(ShapeNum) 585;
const	ShapeNum	BUNKNW		=	(ShapeNum) 586;
const	ShapeNum	BUNKS		=	(ShapeNum) 587;
const	ShapeNum	BUNKSW		=	(ShapeNum) 588;
const	ShapeNum	BUNKSE		=	(ShapeNum) 589;
const	ShapeNum	RPCTL		=	(ShapeNum) 590;
const	ShapeNum	RPOPPSL		=	(ShapeNum) 591;
const	ShapeNum	RPOPPSM		=	(ShapeNum) 592;
const	ShapeNum	RPHREW		=	(ShapeNum) 593;
const	ShapeNum	RPHRNS		=	(ShapeNum) 594;
const	ShapeNum	RPCTS		=	(ShapeNum) 595;
const	ShapeNum	RPMHQ		=	(ShapeNum) 596;
const	ShapeNum	BARAGL		=	(ShapeNum) 357;
const	ShapeNum	RPLAY		=	(ShapeNum) 205;
const	ShapeNum	BRIDGE1		=	(ShapeNum) 597;
const	ShapeNum	BRIDGE2		=	(ShapeNum) 598;
const	ShapeNum	BRIDGE3		=	(ShapeNum) 599;
const	ShapeNum	BRIDGE4		=	(ShapeNum) 600;
const	ShapeNum	BRIDGE5		=	(ShapeNum) 601;
const	ShapeNum	BRIDGE6		=	(ShapeNum) 602;
const	ShapeNum	BRIDGE7		=	(ShapeNum) 603;
const	ShapeNum	BRIDGE8		=	(ShapeNum) 604;
const	ShapeNum	BRIDGE9		=	(ShapeNum) 605;
const	ShapeNum	BRIDGE10		=	(ShapeNum) 606;
const	ShapeNum	PLUME1		=	(ShapeNum) 206;
const	ShapeNum	PLUME2		=	(ShapeNum) 207;
const	ShapeNum	VSTRAC		=	(ShapeNum) 358;
const	ShapeNum	TRACER		=	(ShapeNum) 359;
const	ShapeNum	SMKDRK		=	(ShapeNum) 360;
const	ShapeNum	SMKMED		=	(ShapeNum) 361;
const	ShapeNum	SMKFIR		=	(ShapeNum) 362;
const	ShapeNum	BLOKRN		=	(ShapeNum) 363;
const	ShapeNum	BLOKFR		=	(ShapeNum) 364;
const	ShapeNum	BLOKFY		=	(ShapeNum) 365;
const	ShapeNum	FIST		=	(ShapeNum) 366;
const	ShapeNum	VSDSMK		=	(ShapeNum) 367;
const	ShapeNum	FLASH		=	(ShapeNum) 368;
const	ShapeNum	VSEHST		=	(ShapeNum) 369;
const	ShapeNum	F80NAP		=	(ShapeNum) 208;
const	ShapeNum	F84NAP		=	(ShapeNum) 209;
const	ShapeNum	F51NAP		=	(ShapeNum) 210;
const	ShapeNum	CHIM		=	(ShapeNum) 607;
const	ShapeNum	REDR2		=	(ShapeNum) 211;
const	ShapeNum	REDREV		=	(ShapeNum) 212;
const	ShapeNum	PUFF2		=	(ShapeNum) 213;
const	ShapeNum	COVER1		=	(ShapeNum) 214;
const	ShapeNum	COVER2		=	(ShapeNum) 215;
const	ShapeNum	COVER3		=	(ShapeNum) 216;
const	ShapeNum	COVER4		=	(ShapeNum) 217;
const	ShapeNum	BRIDGE11		=	(ShapeNum) 608;
const	ShapeNum	BRIDGE12		=	(ShapeNum) 609;
const	ShapeNum	BRIDGE13		=	(ShapeNum) 610;
const	ShapeNum	BRIDGE14		=	(ShapeNum) 611;
const	ShapeNum	BRIDGE15		=	(ShapeNum) 612;
const	ShapeNum	BRIDGE16		=	(ShapeNum) 613;
const	ShapeNum	BRIDGE17		=	(ShapeNum) 614;
const	ShapeNum	BRIDGE18		=	(ShapeNum) 615;
const	ShapeNum	BRIDGE19		=	(ShapeNum) 616;
const	ShapeNum	BRIDGE20		=	(ShapeNum) 617;
const	ShapeNum	TWN3		=	(ShapeNum) 618;
const	ShapeNum	TWN4		=	(ShapeNum) 619;
const	ShapeNum	BRIDGE21		=	(ShapeNum) 620;
const	ShapeNum	BRIDGE22		=	(ShapeNum) 621;
const	ShapeNum	BRIDGE23		=	(ShapeNum) 622;
const	ShapeNum	BRIDGE24		=	(ShapeNum) 623;
const	ShapeNum	BRIDGE25		=	(ShapeNum) 624;
const	ShapeNum	BRIDGE26		=	(ShapeNum) 625;
const	ShapeNum	BRIDGE27		=	(ShapeNum) 626;
const	ShapeNum	BRIDGE28		=	(ShapeNum) 627;
const	ShapeNum	BRIDGE29		=	(ShapeNum) 628;
const	ShapeNum	BRIDGE30		=	(ShapeNum) 629;
const	ShapeNum	LBFLAK2		=	(ShapeNum) 630;
const	ShapeNum	SAAA2		=	(ShapeNum) 631;
const	ShapeNum	BRIDGE31		=	(ShapeNum) 632;
const	ShapeNum	BRIDGE32		=	(ShapeNum) 633;
const	ShapeNum	BRIDGE33		=	(ShapeNum) 634;
const	ShapeNum	BRIDGE34		=	(ShapeNum) 635;
const	ShapeNum	BRIDGE35		=	(ShapeNum) 636;
const	ShapeNum	BRIDGE36		=	(ShapeNum) 637;
const	ShapeNum	BRIDGE37		=	(ShapeNum) 638;
const	ShapeNum	BRIDGE38		=	(ShapeNum) 639;
const	ShapeNum	BRIDGE39		=	(ShapeNum) 640;
const	ShapeNum	BRIDGE40		=	(ShapeNum) 641;
const	ShapeNum	RUNWAY00		=	(ShapeNum) 642;
const	ShapeNum	RUNWAY01		=	(ShapeNum) 643;
const	ShapeNum	RUNWAY02		=	(ShapeNum) 644;
const	ShapeNum	RUNWAY03		=	(ShapeNum) 645;
const	ShapeNum	RUNWAY04		=	(ShapeNum) 646;
const	ShapeNum	RUNWAY05		=	(ShapeNum) 647;
const	ShapeNum	RUNWAY06		=	(ShapeNum) 648;
const	ShapeNum	RUNWAY07		=	(ShapeNum) 649;
const	ShapeNum	RUNWAY08		=	(ShapeNum) 650;
const	ShapeNum	RUNWAY09		=	(ShapeNum) 651;
const	ShapeNum	RUNWAY10		=	(ShapeNum) 652;
const	ShapeNum	RUNWAY11		=	(ShapeNum) 653;
const	ShapeNum	RUNWAY12		=	(ShapeNum) 654;
const	ShapeNum	RUNWAY13		=	(ShapeNum) 655;
const	ShapeNum	RUNWAY14		=	(ShapeNum) 656;
const	ShapeNum	RUNWAY15		=	(ShapeNum) 657;
const	ShapeNum	RUNWAY16		=	(ShapeNum) 658;
const	ShapeNum	RUNWAY17		=	(ShapeNum) 659;
const	ShapeNum	RUNWAY18		=	(ShapeNum) 660;
const	ShapeNum	RUNWAY19		=	(ShapeNum) 661;
const	ShapeNum	RUNWAY20		=	(ShapeNum) 662;
const	ShapeNum	RUNWAY21		=	(ShapeNum) 663;
const	ShapeNum	RUNWAY22		=	(ShapeNum) 664;
const	ShapeNum	RUNWAY23		=	(ShapeNum) 665;
const	ShapeNum	RUNWAY24		=	(ShapeNum) 666;
const	ShapeNum	RUNWAY25		=	(ShapeNum) 667;
const	ShapeNum	RUNWAY26		=	(ShapeNum) 668;
const	ShapeNum	RUNWAY27		=	(ShapeNum) 669;
const	ShapeNum	RUNWAY28		=	(ShapeNum) 670;
const	ShapeNum	RUNWAY29		=	(ShapeNum) 671;
const	ShapeNum	RUNWAY30		=	(ShapeNum) 672;
const	ShapeNum	F84B10		=	(ShapeNum) 218;
const	ShapeNum	F80B10		=	(ShapeNum) 219;
const	ShapeNum	F51B10		=	(ShapeNum) 220;
const	ShapeNum	T6RT		=	(ShapeNum) 221;
const	ShapeNum	SCORCH		=	(ShapeNum) 222;
const	ShapeNum	FOREST1		=	(ShapeNum) 673;
const	ShapeNum	FOREST2		=	(ShapeNum) 674;
const	ShapeNum	WOOD1		=	(ShapeNum) 675;
const	ShapeNum	WOOD2		=	(ShapeNum) 676;
const	ShapeNum	WOOD3		=	(ShapeNum) 677;
const	ShapeNum	FLKTRP1		=	(ShapeNum) 678;
const	ShapeNum	FLKTRP2		=	(ShapeNum) 679;
const	ShapeNum	FLKTRP3		=	(ShapeNum) 680;
const	ShapeNum	TREES		=	(ShapeNum) 223;
const	ShapeNum	SOOTY		=	(ShapeNum) 224;
const	ShapeNum	TWN1A		=	(ShapeNum) 681;
const	ShapeNum	TWN2A		=	(ShapeNum) 682;
const	ShapeNum	TWNB		=	(ShapeNum) 683;
const	ShapeNum	LAREA2		=	(ShapeNum) 684;
const	ShapeNum	BOMB29		=	(ShapeNum) 225;
const	ShapeNum	DSTNAP		=	(ShapeNum) 226;
const	ShapeNum	SUPMIG		=	(ShapeNum) 370;
const	ShapeNum	WSMOKE		=	(ShapeNum) 371;
const	ShapeNum	CLSFIR		=	(ShapeNum) 227;
const	ShapeNum	CLLFIR		=	(ShapeNum) 228;
const	ShapeNum	WFLAK		=	(ShapeNum) 229;
const	ShapeNum	BFLAK		=	(ShapeNum) 230;
const	ShapeNum	CLUSTA		=	(ShapeNum) 231;
const	ShapeNum	CLUSTF		=	(ShapeNum) 232;
const	ShapeNum	BULCSE		=	(ShapeNum) 233;
const	ShapeNum	BMB129		=	(ShapeNum) 372;
#endif
