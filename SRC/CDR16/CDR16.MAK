# -----------------------------------------------------------------
# File name:  MAKEFILE
#
# This file contains the build information necessary to create both
# the application (APPSKEL) and the DLL it calls (DLL16).
#
# This is an NMAKE FILE.
#
# Copyright (c) 1991-1996 Microsoft Corporation.  All rights reserved.
# -----------------------------------------------------------------

all: ...\game\cdr16.dll

# Defines

#
# Build flags
#
DLL_CFLAGS = -c -W3 -AHu -G2 -Zi -Od /nologo
DLLMFLAGS   = /c /DIS_16 /W3 /Zi /nologo
DLL_LINKFLAGS = /NOD/NOE/MAP/COD
DLL_OBJS = CDR16.obj 16thk.obj

#
# Rules for building CDR16.DLL, the DLL.
# Get the thunking asm file from the directory up one level.
# This assumes that we've maintained the ..\thunk\cdr16 directory
# structure.
#
32to16.asm: 32to16.thk
    thunk -t thk -o 32to16.asm 32to16.thk

16thk.obj: 32to16.asm
    ml $(DLLMFLAGS) /Fo 16thk.obj 32to16.asm

CDR16.obj: CDR16.c CDR16.h
    s:\ms\bin\cl /X /Is:\ms\include $(DLL_CFLAGS) CDR16.c

...\game\CDR16.dll: $(DLL_OBJS) CDR16.def
    s:\ms\bin\link @<<
    $(DLL_LINKFLAGS) $(DLL_OBJS)
    CDR16.dll
    CDR16.map /map/li
    s:\ms\lib\libw s:\ms\lib\ldllcew
    CDR16.def
<<
    s:\ms\tools\rc -40 CDR16.dll
    mapsym CDR16
    s:\ms\bin\implib CDR16.lib CDR16.def
    copy CDR16.DLL ...\game

#
# Rules of convenience to remove the extra files in the directory
#
clean:
    -del *.bak
    -del *.obj
    -del *.res
    -del *.map
    -del *.sym
    -del *.lib
    -del 32to16.asm
cleaner: clean
    -del ...\game\CDR16.dll
    -del *.exe


