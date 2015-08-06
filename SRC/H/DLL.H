//
// 386FX file & DLL loader functions/equates
//

#ifndef DLL_H
#define DLL_H

//Old_Code PD 04Jun96 #include <string.h>  // (for size_t definition)
#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_
 typedef unsigned size_t;
#endif

//
// MetaWare support
//

#ifdef __HIGHC__
#define cdecl _CC(_REVERSE_PARMS | _NEAR_CALL)
#pragma Global_aliasing_convention("_%r");
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_ERRS
#define FILE_ERRS

#define NO_ERROR        0
#define IO_ERROR        1
#define OUT_OF_MEMORY   2
#define FILE_NOT_FOUND  3
#define CANT_WRITE_FILE 4
#define CANT_READ_FILE  5
#define DISK_FULL       6

#endif

#ifndef TYPEDEFS
#define TYPEDEFS

typedef unsigned char  UBYTE;
typedef unsigned short UWORD;
typedef unsigned long  ULONG;
typedef char  BYTE;
typedef short WORD;
typedef long  LONG;

#endif

//
// malloc() / free() wrapper functions
// 

extern void * (*MEM_alloc) (size_t);
extern void   (*MEM_free)  (void *);

typedef void* (*MEM_use_malloc_fn)(size_t);
typedef void (*MEM_use_free_fn)(void *);

void * cdecl MEM_use_malloc(MEM_use_malloc_fn);
void * cdecl MEM_use_free  (MEM_use_free_fn);


//
// Other memory-management functions
//

LONG   cdecl MEM_alloc_DOS    (ULONG  n_paras, 
                               void **protected_ptr, 
                               ULONG *segment_far_ptr,
                               ULONG *selector);

void   cdecl MEM_free_DOS     (void  *protected_ptr, 
                               ULONG  segment_far_ptr,
                               ULONG  selector);

void * cdecl MEM_alloc_lock   (size_t size);

void   cdecl MEM_free_lock    (void  *ptr, 
                               size_t size);

LONG   cdecl VMM_lock_range   (void *p1, void *p2);
LONG   cdecl VMM_unlock_range (void *p1, void *p2);

LONG   cdecl VMM_lock         (void *start, ULONG size);
LONG   cdecl VMM_unlock       (void *start, ULONG size);

//
// DLL loader flags & functions
//

#define DLLSRC_FILE  0     // *source is filename string
#define DLLSRC_MEM   1     // *source is pointer to DLL image in memory
#define DLLMEM_USER  2     // *dll -> output memory block alloc'd by user
#define DLLMEM_ALLOC 4     // *dll = don't care; allocate & return output mem

ULONG  cdecl DLL_size   (void *source, ULONG flags);
void * cdecl DLL_load   (void *source, ULONG flags, void *dll);

//
// File functions
//

LONG   cdecl FILE_error (void);
LONG   cdecl FILE_size  (BYTE *filename);
void * cdecl FILE_read  (BYTE *filename, void *dest);
LONG   cdecl FILE_write (BYTE *filename, void *buf, ULONG len);
LONG   cdecl FILE_append(BYTE *filename, void *buf, ULONG len);

#ifdef __cplusplus
}
#endif

//
// MetaWare support
//

#ifdef __HIGHC__
#pragma Global_aliasing_convention();
#endif

#endif

