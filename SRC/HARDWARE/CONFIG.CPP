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
//Filename       config.cpp
//System         
//Author         Paul.   
//Date           Fri 23 Apr 1999
//Description    Contains processor ID code + DirectX capability tests
//------------------------------------------------------------------------------
#undef DDSCAPS_LOCALVIDMEM
#define DDSCAPS_LOCALVIDMEM 0x10000000l

#define HAS_NPU		0x01
#define CPU_MMX		0x02
#define	CPU_TS		0x04
#define CYRIX		0x08
#define NEC			0x10
#define NEXGEN		0x20
#define AMD			0x40
#define UMC			0x80

#define	CPUSUPP_FP		0x00000001
#define	CPUSUPP_V86X	0x00000002
#define	CPUSUPP_IOBP	0x00000004
#define	CPUSUPP_PSX		0x00000008
#define	CPUSUPP_TS		0x00000010
#define	CPUSUPP_PSMR	0x00000020
#define	CPUSUPP_PAX		0x00000040
#define	CPUSUPP_MCX		0x00000080
#define	CPUSUPP_CXG8	0x00000100
#define	CPUSUPP_APIC	0x00000200
#define	CPUSUPP_reserved 0x00000400
#define	CPUSUPP_SYSE_E	0x00000800
#define	CPUSUPP_MTRR	0x00001000
#define	CPUSUPP_PGX		0x00002000
#define	CPUSUPP_MCA		0x00004000
#define	CPUSUPP_CMOV	0x00008000
#define	CPUSUPP_MMX		0x00800000

#define cpuid _asm _emit 0x0f _asm _emit 0xa2
#define wrmsr _asm _emit 0x0f _asm _emit 0x30
#define rdtsc _asm _emit 0x0f _asm _emit 0x31
#define rdmsr _asm _emit 0x0f _asm _emit 0x32

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		cpu_id
//Author		Paul.   
//Date			Fri 23 Apr 1999
//------------------------------------------------------------------------------
#pragma warning (disable : 4035)
UWord cpu_id()
{
	_asm
	{
        push    ebx
        push    ecx
        push    edx
        push    ebp
        mov     ebp,esp
        xor     dx,dx                   ; result = 0 (UNKNOWN)
//**********************************************************************
// The 486 test
//
//   Try toggling the ID bit in EFLAGS.  If the flag can't be toggled,
//   it's a 486.
//
// Note:
//   This one isn't completely reliable -- I've heard that the NexGen
//   CPU's don't make it through this one even though they have all
//   the Pentium instructions.
//**********************************************************************
        pushfd
        pop     cx
        pop     bx
        mov     dl,4                    ;
        mov     ax,bx                   ;
        xor     al,20h                  ; flip EFLAGS ID bit
        push    ax                      ;
        push    cx                      ;
        popfd                           ;
        pushfd                          ;
        pop     cx                      ;
        pop     ax                      ;
        and     al,20h                  ; check ID bit
        xor     al,bl                   ; Q: did ID bit change?
        jz      TestNpu                 ;   N: it's a 486

//**********************************************************************
// The Pentium+ tests
//
//   First, we issue a CPUID instruction with EAX=0 to get back the
//   manufacturer's name string.  (We only check the first letter.)
//
//**********************************************************************
        push    dx                      ;
        xor     eax,eax                 ;
        cpuid                           ;
        pop     dx                      ;
        cmp     bl,'G'                  ; Q: GenuineIntel?
        jz      WhatPent                ;   Y: what kind?
        or      dh,CYRIX                ; assume Cyrix for now
        cmp     bl,'C'                  ;
        jz      WhatPent                ;
        xor     dh,(CYRIX OR AMD)       ;
        cmp     bl,'A'                  ;
        jz      WhatPent                ;
        xor     dh,(AMD OR NEXGEN)      ;
        cmp     bl,'N'                  ;
        jz      WhatPent                ;
        xor     dh,(NEXGEN OR UMC)      ; assume it's UMC
        cmp     bl,'U'                  ;
        jz      WhatPent                ;
        xor     dh,UMC                  ; we don't know who made it!
//**********************************************************************
// The Pentium+ tests (part II)
//
//   This test simply gets the family information via the CPUID
//   instruction
//
//**********************************************************************
WhatPent:
        push    edx                     ;
        xor     eax,eax                 ;
        inc     al                      ;
        cpuid                           ;
		xor		al,al
		test	edx,CPUSUPP_TS
		jz		NoRDTSC
		or		al,CPU_TS
NoRDTSC:
		test	edx,CPUSUPP_MMX
		jz		NoMMX
		or		al,CPU_MMX
NoMMX:
        pop     edx                     ;
		or		dh,al					; fill in rdtsc/mmx flags
        and     ah,0fh                  ;
        mov     dl,ah                   ; put family code in DL

//**********************************************************************
// The NPU test
//
//   We reset the NPU (using the non-wait versions of the instruction, of
//   course!), put a non-zero value on the stack, then write the NPU
//   status word to that stack location.  Then we check for zero, which
//   is what would be there if there were an NPU.
//
//**********************************************************************
TestNpu:
        mov     esp,ebp                 ; restore stack
        fninit                          ; init but don't wait
        mov     ax,0EdEdh               ;
        push    ax                      ; put non-zero value on stack
		fnstsw  word ptr [ebp-2]        ; save NPU status word
        pop     ax                      ;
        or      ax,ax                   ; Q: was status = 0?
        jnz     finish                  ;   N: no NPu
        or      dh,HAS_NPU              ;   Y: has NPU
finish:
        mov     ax,dx                   ; put our return value in place
        pop     ebp                     ; clean up stack
        pop     edx                     ;
        pop     ecx                     ;
        pop     ebx                     ;
	}
}
#pragma warning (default : 4035)

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		cpu_info
//Author		Paul.   
//Date			Fri 23 Apr 1999
//------------------------------------------------------------------------------
void cpu_info()
{
	UWord flags=cpu_id();
	SWord clock=-1;
	if (flags&CPU_TS)
	{
		__int64 freq,curr,test,ticks;

		if (QueryPerformanceFrequency((LARGE_INTEGER*)&freq))
		{
			freq=freq*2;	//two seconds

			QueryPerformanceCounter((LARGE_INTEGER*)&test);
			_asm
			{
			push eax
			push edx
			push edi
			lea edi,[ticks]
			rdtsc
			mov [dword ptr edi],eax
			mov [dword ptr edi+4],edx
			pop edi
			pop edx
			pop eax
			}
			test+=freq;
			do{QueryPerformanceCounter((LARGE_INTEGER*)&curr);}
			while (curr<test);
			_asm
			{
			push eax
			push edx
			push edi
			rdtsc
			lea edi,[ticks]
			sub edx,[dword ptr edi+4]
			sbb eax,[dword ptr edi]
			mov	[dword ptr edi+4],edx
			mov [dword ptr edi],eax
			pop edi
			pop edx
			pop eax
			}
			ticks=ticks/(2*1000*1000);	//convert to MHz
			clock=ticks;
		}
	}

	//set savegame.processorType to PROC_SLOW,PROC_MIN,PROC_MED,PROC_MAX

	ProcType pt;

	if (clock<200 || clock>2000 || flags&(UMC<<8))		pt=PROC_SLOW;
	else if (5<=(flags&0xFF) && clock<=266)				pt=PROC_MIN;
	else if (6<=(flags&0xFF) && clock<=300)				pt=PROC_MED;
	else												pt=PROC_MAX;

	Save_Data.processorType=pt;
}

//Direct Draw/Direct 3D initialisation tests

BOOL FAR PASCAL EnumDrivers(GUID FAR* lpGUID,LPSTR,LPSTR,LPVOID lpContext)
{
	SDrivers *psd=(SDrivers*)lpContext,&sd=*psd;
    LPDIRECTDRAW pDD;
    LPDIRECTDRAW2 pDD2;
    DDCAPS DriverCaps,HELCaps;
	if (lpGUID!=NULL)
	{
		if (DirectDrawCreate(lpGUID,&pDD,NULL)==DD_OK)
		{
			if (pDD->QueryInterface(IID_IDirectDraw2,(LPVOID*)&pDD2)==DD_OK)
			{
			    ZeroMem(&DriverCaps,sizeof(DDCAPS));
				ZeroMem(&HELCaps,sizeof(DDCAPS));
	    		DriverCaps.dwSize=sizeof(DDCAPS);
		    	HELCaps.dwSize=sizeof(DDCAPS);
				if (pDD2->GetCaps(&DriverCaps,&HELCaps)==DD_OK && (DriverCaps.dwCaps&DDCAPS_3D))
				{
					int driver_index=sd.num_drivers;
					memcpy(sd.hard_guids+driver_index,lpGUID,sizeof(GUID));
					sd.num_drivers++;
				}
				pDD2->Release();
			}
			pDD->Release();
			if (sd.num_drivers==SDrivers::Max_Drivers) return DDENUMRET_CANCEL;
		}
	}
	return DDENUMRET_OK;
}

HRESULT WINAPI EnumDisplays(LPDDSURFACEDESC lpDDSurfaceDesc,LPVOID lpContext)
{
	if (lpDDSurfaceDesc->dwWidth>=512 &&
		lpDDSurfaceDesc->dwWidth*3==lpDDSurfaceDesc->dwHeight*4 &&
		lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount==16)
	{
		SModeEnum *pme=(SModeEnum*)lpContext,&me=*pme;
		me.widths[me.num_modes]=lpDDSurfaceDesc->dwWidth;
		me.num_modes++;
		if (me.num_modes==SModeEnum::Max_Modes) return DDENUMRET_CANCEL;
	}
	return DDENUMRET_OK;
}

HRESULT WINAPI FindDevice(LPGUID lpGuid,LPSTR,LPSTR,LPD3DDEVICEDESC lpHWDesc,LPD3DDEVICEDESC,LPVOID lpContext)
{
    if (lpHWDesc->dcmColorModel)
	{
		GUID FAR** ppguid=(GUID FAR**)lpContext;
		*ppguid=lpGuid;
		return D3DENUMRET_CANCEL;
	}
	return D3DENUMRET_OK;
}

inline bool IsValidMode(SModeFlags* pmf,UWord w,UWord h)
{
	if (w*3!=h*4) return false;
	for (int x=0;x<SModeFlags::Max_Modes;x++) if (pmf->widths[x]==w) return true;
	return false;
}

inline ULong TextureRAM(SModeFlags* pmf,UWord w)
{
	for (int x=0;x<SModeFlags::Max_Modes;x++)
		if (pmf->widths[x]==w) return pmf->freeTextureRam[x];
	return ULong(0);
}

#define TEXTURES_PAL8		0x00000001
#define TEXTURES_RGB16		0x00000002
#define TEXTURES_RGBAMASK	0x00000004
#define TEXTURES_RGBAFADE	0x00000008

#define MIN_TEXTURERAM_PAL8	2*1024*1024
#define	MIN_TEXTURERAM_RGB16 4*1024*1024

HRESULT CALLBACK CheckTextures(LPDDSURFACEDESC pddsd,LPVOID pContext)
{
	DWORD* pflags=(DWORD*)pContext;

    if (pddsd->ddpfPixelFormat.dwFlags&DDPF_PALETTEINDEXED8)
		*pflags|=TEXTURES_PAL8;
	else if (pddsd->ddpfPixelFormat.dwFlags&DDPF_RGB &&	pddsd->ddpfPixelFormat.dwRGBBitCount==16)
	{
		*pflags|=TEXTURES_RGB16;
		if (pddsd->ddpfPixelFormat.dwFlags&DDPF_ALPHAPIXELS)
		{
			*pflags|=TEXTURES_RGBAMASK;

			WORD bits=0;
			DWORD mask=pddsd->ddpfPixelFormat.dwRGBAlphaBitMask;
			while(mask) {mask=mask&(mask-1);bits++;}
			if (bits>1) *pflags|=TEXTURES_RGBAFADE;
		}
	}
	return DDENUMRET_OK;
}

void Configure(bool fFullConfig,HWND hWnd)
{
	HRESULT hr;
	SDrivers sd;
	GUID FAR* pguid;
	Mono_Text.Print(0,UByteP("Configuring!!!!"));

	//primary driver test first...

	LPDIRECTDRAW pDD;
	LPDIRECTDRAW2 pDD2;
	if (DirectDrawCreate(NULL,&pDD,NULL)==DD_OK)
	{
		if (pDD->QueryInterface(IID_IDirectDraw2,(LPVOID*)&pDD2)==DD_OK)
		{
		    DDCAPS DriverCaps,HELCaps;
			ZeroMem(&DriverCaps,sizeof(DDCAPS));
			ZeroMem(&HELCaps,sizeof(DDCAPS));
    		DriverCaps.dwSize=sizeof(DDCAPS);
    		HELCaps.dwSize=sizeof(DDCAPS);
			if (pDD2->GetCaps(&DriverCaps,&HELCaps)==DD_OK && (DriverCaps.dwCaps&DDCAPS_3D))
				sd.fFirstHardIsPrimary=true;
			sd.num_drivers++;
			pDD2->Release();
		}
		pDD->Release();
	}
	hr=DirectDrawEnumerate(EnumDrivers,(void*)&sd);
	Save_Data.fNoHardwareAtAll=true;

	int i;
	for (i=sd.fFirstHardIsPrimary?0:1,sd.fFirstHardIsPrimary=false;i<sd.num_drivers;i++)
	{
		pguid=(!i)?NULL:&sd.hard_guids[i];
		if (DirectDrawCreate(pguid,&pDD,NULL)==DD_OK)
		{
			if (pDD->QueryInterface(IID_IDirectDraw2,(LPVOID*)&pDD2)==DD_OK)
			{
				SModeEnum modeEnum;
				modeEnum.num_modes=0;
				if (pDD2->EnumDisplayModes(DDEDM_REFRESHRATES,NULL,(LPVOID)&modeEnum,(LPDDENUMMODESCALLBACK)&EnumDisplays)==DD_OK &&
					modeEnum.num_modes>0)
				{
					int max_allowed_sw=65536;
					int max_allowed_hw=65536;
					pDD2->SetCooperativeLevel(hWnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN);
					pDD2->SetCooperativeLevel(hWnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN);
					for (int j=0;j<modeEnum.num_modes;j++)
					{
						if (modeEnum.widths[j]<max_allowed_sw)
						{
							if (pDD2->SetDisplayMode(modeEnum.widths[j],(modeEnum.widths[j]>>2)*3,16,0,0)==DD_OK)
							{
								DDSURFACEDESC ddsd;
								LPDIRECTDRAWSURFACE pSurf,pZBuf,pBack;
								ZeroMem(&ddsd,sizeof(DDSURFACEDESC));
								ddsd.dwSize=sizeof(DDSURFACEDESC);

								//attempt to create front & back buffers
								ddsd.dwFlags=DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
								ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE|
													DDSCAPS_FLIP|
													DDSCAPS_COMPLEX|
													DDSCAPS_3DDEVICE| 
													DDSCAPS_VIDEOMEMORY|
													DDSCAPS_LOCALVIDMEM;
								ddsd.dwBackBufferCount=1;
								if (modeEnum.widths[j]<max_allowed_hw && pDD2->CreateSurface(&ddsd,&pSurf,NULL)==DD_OK)
								{
									//attempt to create z-buffer
									ZeroMem (&ddsd,sizeof(DDSURFACEDESC));
									ddsd.dwSize=sizeof(DDSURFACEDESC);
									ddsd.dwFlags=DDSD_WIDTH|DDSD_HEIGHT|DDSD_CAPS|DDSD_ZBUFFERBITDEPTH;
							    	ddsd.ddsCaps.dwCaps=DDSCAPS_ZBUFFER|DDSCAPS_VIDEOMEMORY;
									ddsd.dwWidth=modeEnum.widths[j];
									ddsd.dwHeight=(modeEnum.widths[j]>>2)*3;
							        ddsd.dwZBufferBitDepth=16;
									if (pDD2->CreateSurface(&ddsd,&pZBuf,NULL)==DD_OK)
									{
										//now, test available texture RAM
										DDSCAPS	ddscaps;
										DWORD	total;
										DWORD	free;
										ddscaps.dwCaps=DDSCAPS_LOCALVIDMEM|DDSCAPS_TEXTURE;
										if (pDD2->GetAvailableVidMem(&ddscaps,&total,&free)==DD_OK)
										{
											LPDIRECT3D pD3D;

											if (pDD2->QueryInterface(IID_IDirect3D,(LPVOID*)&pD3D)==DD_OK)
											{
												GUID FAR* dev3d=NULL;
												ddscaps.dwCaps=DDSCAPS_BACKBUFFER;
												LPDIRECT3DDEVICE pD3DDEV;

												if(	pSurf->GetAttachedSurface(&ddscaps,&pBack)==DD_OK &&
													pD3D->EnumDevices(FindDevice,(LPVOID)&dev3d)==D3D_OK && 
													dev3d!=NULL &&
													pBack->QueryInterface(*dev3d,(LPVOID*)&pD3DDEV)==D3D_OK)
												{
													D3DDEVICEDESC HWCaps,HELCaps;
													ZeroMem(&HWCaps,sizeof(D3DDEVICEDESC));
													ZeroMem(&HELCaps,sizeof(D3DDEVICEDESC));
													HWCaps.dwSize=sizeof(D3DDEVICEDESC);
													HELCaps.dwSize=sizeof(D3DDEVICEDESC);

													if (pD3DDEV->GetCaps(&HWCaps,&HELCaps)==D3D_OK)
													{
														//check texture filtering flags

														DWORD mipFlags=	D3DPTFILTERCAPS_LINEARMIPLINEAR |
																		D3DPTFILTERCAPS_LINEARMIPNEAREST |
																		D3DPTFILTERCAPS_MIPLINEAR |
																		D3DPTFILTERCAPS_MIPNEAREST;

														if (HWCaps.dpcTriCaps.dwTextureFilterCaps&mipFlags)
															sd.hard_settings[i].filtering=3;
														else
															sd.hard_settings[i].filtering=1;

														DWORD texture_flag=0;
	
														if (pD3DDEV->EnumTextureFormats(CheckTextures,(LPVOID)&texture_flag)==D3D_OK &&
															texture_flag!=0)
														{
															DWORD min_texture_ram;

															if (texture_flag&TEXTURES_PAL8)	
															{
																min_texture_ram=MIN_TEXTURERAM_PAL8;
																sd.hard_settings[i].pal8=true;
															}
															else
															{
																min_texture_ram=MIN_TEXTURERAM_RGB16;
																sd.hard_settings[i].pal8=false;
															}
															if (texture_flag&TEXTURES_RGBAFADE)
																sd.hard_settings[i].transparency=true;
															else
																sd.hard_settings[i].transparency=false;

															if (min_texture_ram<=free) 
															{
																sd.hard_modes[i].widths[j]=modeEnum.widths[j];
																sd.hard_modes[i].freeTextureRam[j]=free;
																Save_Data.fNoHardwareAtAll=false;
																if (!i) sd.fFirstHardIsPrimary=true;
															}
														}
													}
													pD3DDEV->Release();
												}
												//else if (!i) sd.fFirstHardIsPrimary=false;
												pD3D->Release();
											}
										}
										pZBuf->Release();
									}
									pSurf->Release();
									if (!pguid) sd.soft_modes.widths[j]=modeEnum.widths[j];
								}
								else if (pguid==NULL)
								{
									ZeroMem(&ddsd,sizeof(DDSURFACEDESC));
									ddsd.dwSize=sizeof(DDSURFACEDESC);

									//attempt to create front & back buffers
									ddsd.dwFlags=DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
									ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE|
														DDSCAPS_FLIP|
														DDSCAPS_COMPLEX|
														DDSCAPS_VIDEOMEMORY|
														DDSCAPS_LOCALVIDMEM;
									ddsd.dwBackBufferCount=1;
									if (pDD2->CreateSurface(&ddsd,&pSurf,NULL)==DD_OK)
									{
										sd.soft_modes.widths[j]=modeEnum.widths[j];
										pSurf->Release();
									}
								}

								pDD2->RestoreDisplayMode();

								if (sd.hard_modes[i].widths[j]==0) max_allowed_hw=modeEnum.widths[j];
							}
							if (pguid==NULL && sd.soft_modes.widths[j]==0) 
								max_allowed_sw=
								max_allowed_hw=modeEnum.widths[j];
						}
					}
					pDD2->SetCooperativeLevel(hWnd,DDSCL_NORMAL);
					pDD2->SetCooperativeLevel(hWnd,DDSCL_NORMAL);
				}
				pDD2->Release();
			}
			pDD->Release();
		}
	}

	Save_Data.sd=sd;

	cpu_info();

	switch (Save_Data.processorType)
	{
	case PROC_SLOW:
	Save_Data.detail_3d%=DETAIL3D_AUTODETAIL;
	Save_Data.desiredfps=1;
	Save_Data.detail_3d%=DETAIL3D_GROUNDSHADING;
	Save_Data.detail_3d%=DETAIL3D_ITEMSHADING;
	Save_Data.detail_3d%=DETAIL3D_TRANSSMOKE;
	Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
	Save_Data.detail_3d%=DETAIL3D_ROUTES;
	Save_Data.detail_3d%=DETAIL3D_AIRCRAFTSHADOWS;
	Save_Data.detail_3d%=DETAIL3D_ITEMSHADOWS;
	Save_Data.detail_3d%=DETAIL3D_HORIZONDIST;
	Save_Data.detail_3d|=DETAIL3D_HORIZONFADE;
	Save_Data.detail_3d%=DETAIL3D_CONTOURDETAIL;
	Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
	Save_Data.gamedifficulty%=GD_WEATHEREFFECTS;
	Save_Data.filtering=0;
	break;

	case PROC_MIN:
	Save_Data.detail_3d%=DETAIL3D_AUTODETAIL;
	Save_Data.desiredfps=2;
	Save_Data.detail_3d|=DETAIL3D_GROUNDSHADING;
	Save_Data.detail_3d%=DETAIL3D_ITEMSHADING;
	Save_Data.detail_3d%=DETAIL3D_TRANSSMOKE;
	Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
	Save_Data.detail_3d|=DETAIL3D_ROUTES;
	Save_Data.detail_3d|=DETAIL3D_AIRCRAFTSHADOWS;
	Save_Data.detail_3d%=DETAIL3D_ITEMSHADOWS;
	Save_Data.detail_3d%=DETAIL3D_HORIZONDIST;
	Save_Data.detail_3d|=DETAIL3D_HORIZONFADE;
	Save_Data.detail_3d%=DETAIL3D_CONTOURDETAIL;
	Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
	Save_Data.gamedifficulty|=GD_WEATHEREFFECTS;
	Save_Data.filtering=1;
	break;

	case PROC_MED:
	Save_Data.detail_3d%=DETAIL3D_AUTODETAIL;
	Save_Data.desiredfps=3;
	Save_Data.detail_3d|=DETAIL3D_GROUNDSHADING;
	Save_Data.detail_3d|=DETAIL3D_ITEMSHADING;
	Save_Data.detail_3d|=DETAIL3D_TRANSSMOKE;
	Save_Data.detail_3d|=DETAIL3D_INCONSEQUENTIALS;
	Save_Data.detail_3d|=DETAIL3D_ROUTES;
	Save_Data.detail_3d|=DETAIL3D_AIRCRAFTSHADOWS;
	Save_Data.detail_3d|=DETAIL3D_ITEMSHADOWS;
	Save_Data.detail_3d|=DETAIL3D_HORIZONDIST;
	Save_Data.detail_3d%=DETAIL3D_HORIZONFADE;
	Save_Data.detail_3d|=DETAIL3D_CONTOURDETAIL;
	Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
	Save_Data.gamedifficulty|=GD_WEATHEREFFECTS;
	Save_Data.filtering=2;
	break;

	case PROC_MAX:
	Save_Data.detail_3d%=DETAIL3D_AUTODETAIL;
	Save_Data.desiredfps=3;
	Save_Data.detail_3d|=DETAIL3D_GROUNDSHADING;
	Save_Data.detail_3d|=DETAIL3D_ITEMSHADING;
	Save_Data.detail_3d|=DETAIL3D_TRANSSMOKE;
	Save_Data.detail_3d|=DETAIL3D_INCONSEQUENTIALS;
	Save_Data.detail_3d|=DETAIL3D_ROUTES;
	Save_Data.detail_3d|=DETAIL3D_AIRCRAFTSHADOWS;
	Save_Data.detail_3d|=DETAIL3D_ITEMSHADOWS;
	Save_Data.detail_3d|=DETAIL3D_HORIZONDIST;
	Save_Data.detail_3d%=DETAIL3D_HORIZONFADE;
	Save_Data.detail_3d|=DETAIL3D_CONTOURDETAIL;
	Save_Data.cockpit3Ddetail|=COCK3D_SKYIMAGES;
	Save_Data.gamedifficulty|=GD_WEATHEREFFECTS;
	Save_Data.filtering=3;
	break;
	}

	Save_Data.gammacorrection=2;

	//select a good range of default graphics options
	
	//if there is a secondary hardware 3D device then select it
	//else if there is a primary 3D device then select it
	//else select the software driver

	SModeFlags *pdm=NULL;
	SDriverSettings *pds=NULL;

	if (sd.num_drivers>=2)
	{
		Save_Data.fSoftware=false;
		pdm=sd.hard_modes+1;
		pds=sd.hard_settings+1;
	}
	else if (sd.fFirstHardIsPrimary)
	{
		Save_Data.fSoftware=false;
		pdm=sd.hard_modes+0;
		pds=sd.hard_settings+0;
	}
	else
	{
		Save_Data.fSoftware=true;
		pdm=&sd.soft_modes;
	}

	//for software version select a mode based on the processor speed

	if (Save_Data.fSoftware)
	{
		UWord max_w;
		switch (Save_Data.processorType)
		{
		default:
		case PROC_SLOW: max_w=512; break;
		case PROC_MIN:	max_w=640; break;
		case PROC_MED:	max_w=640; break;
		case PROC_MAX:	max_w=800; break;
		}
		//try to select a mode no more than 'max_w' wide

		int nm,rez;
		SDrvrModes* dm;
		GetModes(nm,dm);

		for (i=0,rez=0;i<nm;i++)
			if (dm[i].driverNo==0 &&
				dm[i].displayBPP==16 && 
				IsValidMode(pdm,dm[i].displayWidth,dm[i].displayHeight))
			{
				if (dm[i].displayWidth==max_w)
				{
					Save_Data.dddriver=-1;
					Save_Data.screenresolution=rez;
					gameSettings.m_dwWidth=Save_Data.displayW=dm[i].displayWidth;
					gameSettings.m_dwHeight=Save_Data.displayH=dm[i].displayHeight;
			 		Mono_Text.Print(Save_Data.displayH,UByteP("Save_Data.displayH (Soft)"));

				}
				rez++;
			}

		Save_Data.textureQuality=4;
		Save_Data.filtering=0;
		Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
		Save_Data.detail_3d%=DETAIL3D_GROUNDSHADING;
		Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
	}
	else
	{
		UWord max_w;
		int nm,rez,dddriver;
		SDrvrModes* dm;
		GetModes(nm,dm);
		dddriver=(sd.num_drivers>=2)?1:0;

		max_w=(Save_Data.processorType!=PROC_MAX)?800:1024;

		for (i=0,rez=0;i<nm;i++)
			if (dm[i].driverNo==dddriver &&
				dm[i].displayBPP==16 &&
				IsValidMode(pdm,dm[i].displayWidth,dm[i].displayHeight))
			{
				if (dm[i].displayWidth==max_w)
				{
					//if texture ram available is at least enuogh for texture quality == 3
					//then choose this mode

					ULong texture_ram=TextureRAM(pdm,max_w);
					if (!pds->pal8) texture_ram>>=1;

					ULong min_texture_ram=0x200000;
					if (pds->filtering>=2)	min_texture_ram+=(min_texture_ram>>1);
					if (pds->filtering==3)	min_texture_ram+=(!pds->pal8)?49152*2:49152;

					if (texture_ram>=min_texture_ram)
					{
						Save_Data.dddriver=dddriver-1;
						Save_Data.screenresolution=rez;
						gameSettings.m_dwWidth=Save_Data.displayW=dm[i].displayWidth;
						gameSettings.m_dwHeight=Save_Data.displayH=dm[i].displayHeight;
				 		Mono_Text.Print(Save_Data.displayH,UByteP("Save_Data.displayH (1)"));

						Save_Data.textureQuality=(texture_ram>2*min_texture_ram)?4:3;
						break;
					}
				}
				rez++;
			}

		if (i==nm)		//FAILED!
		{
			max_w=(Save_Data.processorType!=PROC_MAX)?640:800;

			for (i=0,rez=0;i<nm;i++)
				if (dm[i].driverNo==dddriver &&
					dm[i].displayBPP==16 &&
					IsValidMode(pdm,dm[i].displayWidth,dm[i].displayHeight))
				{
					if (dm[i].displayWidth==max_w)
					{
						//if texture ram available is at least enuogh for texture quality == 3
						//then choose this mode

						ULong texture_ram=TextureRAM(pdm,max_w);
						if (!pds->pal8) texture_ram>>=1;

						ULong min_texture_ram=0x200000;
//TEMP						if (pds->filtering>=2)	min_texture_ram+=(min_texture_ram>>1);
//TEMP						if (pds->filtering==3)	min_texture_ram+=(!pds->pal8)?49152*2:49152;

						if (texture_ram>=min_texture_ram)
						{
							Save_Data.dddriver=dddriver-1;
							Save_Data.screenresolution=rez;
							gameSettings.m_dwWidth=Save_Data.displayW=dm[i].displayWidth;
							gameSettings.m_dwHeight=Save_Data.displayH=dm[i].displayHeight;
				 		Mono_Text.Print(Save_Data.displayH,UByteP("Save_Data.displayH (2)"));
							Save_Data.textureQuality=(texture_ram>2*min_texture_ram)?4:3;
							break;
						}
					}
					rez++;
				}

			if (i==nm)	//FAILED AGAIN!
			{
				max_w=(Save_Data.processorType!=PROC_MAX)?512:640;

				for (i=0,rez=0;i<nm;i++)
					if (dm[i].driverNo==dddriver &&
						dm[i].displayBPP==16 &&
						IsValidMode(pdm,dm[i].displayWidth,dm[i].displayHeight))
					{
						if (dm[i].displayWidth==max_w)
						{
							//if texture ram available is at least enuogh for texture quality == 3
							//then choose this mode

							ULong texture_ram=TextureRAM(pdm,max_w);
							if (!pds->pal8) texture_ram>>=1;

							ULong min_texture_ram=0x200000;
//TEMP							if (pds->filtering>=2)	min_texture_ram+=(min_texture_ram>>1);
//TEMP							if (pds->filtering==3)	min_texture_ram+=(!pds->pal8)?49152*2:49152;

							if (texture_ram>=min_texture_ram)
							{
								Save_Data.dddriver=dddriver-1;
								Save_Data.screenresolution=rez;
								gameSettings.m_dwWidth=Save_Data.displayW=dm[i].displayWidth;
								gameSettings.m_dwHeight=Save_Data.displayH=dm[i].displayHeight;
				 		Mono_Text.Print(Save_Data.displayH,UByteP("Save_Data.displayH (3)"));
								Save_Data.textureQuality=(texture_ram>2*min_texture_ram)?4:3;
								break;
							}
						}
						rez++;
					}		  

				if (i==nm)	//FAILED AGAIN - ONE LAST ATTEMPT @ HARDWARE MODE
				{
					max_w=640;

					for (i=0,rez=0;i<nm;i++)
			 			if (dm[i].driverNo==dddriver &&
							dm[i].displayBPP==16 &&
							IsValidMode(pdm,dm[i].displayWidth,dm[i].displayHeight))
						{
							if (dm[i].displayWidth==max_w)
							{
								//if texture ram available is at least enuogh for texture quality == 3
								//then choose this mode

								ULong texture_ram=TextureRAM(pdm,max_w);
								if (!pds->pal8) texture_ram>>=1;

								ULong min_texture_ram=0x200000;

								if (texture_ram>=min_texture_ram)
								{
									Save_Data.dddriver=dddriver-1;
									Save_Data.screenresolution=rez;
									gameSettings.m_dwWidth=Save_Data.displayW=dm[i].displayWidth;
									gameSettings.m_dwHeight=Save_Data.displayH=dm[i].displayHeight;
				 		Mono_Text.Print(Save_Data.displayH,UByteP("Save_Data.displayH (4)"));
									Save_Data.textureQuality=(texture_ram>2*min_texture_ram)?4:3;
									break;
								}
							}
							rez++;
						}

					if (i==nm)	//CHOOSE THE SOFTWARE DRIVER!
					{
						Save_Data.fSoftware=true;
						pdm=&sd.soft_modes;
						switch (Save_Data.processorType)
						{
						default:
						case PROC_SLOW: max_w=512; break;
						case PROC_MIN:	max_w=640; break;
						case PROC_MED:	max_w=640; break;
						case PROC_MAX:	max_w=800; break;
						}
						//try to select a mode no more than 'max_w' wide

						for (i=0,rez=0;i<nm;i++)
							if (dm[i].driverNo==-1 &&
								dm[i].displayBPP==16 && 
								IsValidMode(pdm,dm[i].displayWidth,dm[i].displayHeight))
							{
								if (dm[i].displayWidth==max_w)
								{
									Save_Data.dddriver=-1;
									Save_Data.screenresolution=rez;
									gameSettings.m_dwWidth=Save_Data.displayW=dm[i].displayWidth;
									gameSettings.m_dwHeight=Save_Data.displayH=dm[i].displayHeight;
				 		Mono_Text.Print(Save_Data.displayH,UByteP("Save_Data.displayH (S)"));
								}
								rez++;
							}

						Save_Data.textureQuality=4;
						Save_Data.filtering=0;
						Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
						Save_Data.detail_3d%=DETAIL3D_GROUNDSHADING;
						Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
					}
				}
			}
		}
	}
}
