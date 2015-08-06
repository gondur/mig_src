//DEADCODE DAW 27/05/99 #ifdef _DEBUG
//DEADCODE DAW 27/05/99 void* __cdecl operator new(size_t nSize, char* lpszFileName, int nLine);
//DEADCODE DAW 27/05/99 #define THIS_FILE "FILE:" __FILE__
//DEADCODE DAW 27/05/99 #define DEBUG_NEW new(THIS_FILE, __LINE__)
//DEADCODE DAW 27/05/99 
//DEADCODE DAW 27/05/99 #endif
#include <new.h>
#include "dosdefs.h"
