#ifdef _DEBUG
void* __cdecl operator new(size_t nSize, char* lpszFileName, int nLine);
#define THIS_FILE "MATH:" __FILE__
#define DEBUG_NEW new(THIS_FILE, __LINE__)

#endif

