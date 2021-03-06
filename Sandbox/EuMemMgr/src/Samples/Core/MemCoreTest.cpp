#include <iostream.h>
#include <string.h>
#include <stdio.h>
#define __MEM_CORE_TEST_CPP__
#include "MemInternalIface.h"

#ifdef __DEBUG__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef __DEBUG__
// forward declaration.
extern "C" flag
DumpBlocksLogCallback(void *pv, c_char * const buf, pDBF_OutType pDBF,
		      void *p);
#endif // __DEBUG__

#ifdef __DEBUG__
#if defined(WIN32)
extern "C" flag
DumpBlocksLogCallback(void *, c_char * const buf, pDBF_OutType, void *)
#elif defined(__unix__)
extern "C" flag
DumpBlocksLogCallback(void *, c_char * const buf, pDBF_OutType, void *)
#else
#error
#error If highest warning levels are used (which we use), unused parameter
#error names are an error under Win32 and UNIX. How does your compiler behave?
#error
#endif
{
#if defined(WIN32)
    OutputDebugString(buf);
#elif defined(__unix__)
    printf("%s", buf);
#else
#error Error: Developer, please provide implementation of dumping
#error Error: memory blocks for your platform ...
#endif // WIN32
    return(TRUE);
}
#endif // __DEBUG__


int
main(int, char **)
{
    ::InitializeDebugMemoryManager();

    char *p = 0;

    if (::fNewBlock((void **)&p, 256)) {
	fBaptizeBlock(p, "Char-Memory1");
	::strcpy(p, "String1");
    }

    if (p) {
	cout << p << endl << flush;
    }

    // Uncomment the following line to fix memory leak.
    // FreeBlock(p);

    if (::fNewBlock((void **)&p, 1024)) {
	fBaptizeBlock(p, "Char-Memory2");
	::strcpy(p, "String2");
    }

    if (p) {
	cout << p << endl << flush;
    }

    // Uncomment the following line to fix memory leak.
    // FreeBlock(p);

// Dump 1 --- all blocks.
#ifdef __DEBUG__
    cout << "\n\nDump 1\n\n" << flush;
    ::DumpBlocksLogByLabelAndFile(NULL, DumpBlocksLogCallback,
				  0, 0, 0);
#endif // __DEBUG__

// Dump 2 --- by file: you can specify the first few characters of the
//                     the file, and in any case. For example, the
//                     following dumps will report the same blocks.
#ifdef __DEBUG__
    cout << "\n\nDump 2\n\n" << flush;
    ::DumpBlocksLogByLabelAndFile(NULL, DumpBlocksLogCallback,
				  0, 0, "MemCoreTest.cpp");
    ::DumpBlocksLogByLabelAndFile(NULL, DumpBlocksLogCallback,
				  0, 0, "memcoretest.cpp");
    ::DumpBlocksLogByLabelAndFile(NULL, DumpBlocksLogCallback,
				  0, 0, "memcor");
#endif // __DEBUG__

// Dump 3 --- by label: you can specify the first few characters of the
//                      the label, and in any case too.
#ifdef __DEBUG__
    cout << "\n\nDump 3\n\n" << flush;
    ::DumpBlocksLogByLabelAndFile(NULL, DumpBlocksLogCallback,
				  0, "Char-Memory1", 0);
    ::DumpBlocksLogByLabelAndFile(NULL, DumpBlocksLogCallback,
				  0, "Char-Memory2", 0);
#endif // __DEBUG__

// Dump 4 --- by label and file : blocks of a certain label *and* file.
#ifdef __DEBUG__
    cout << "\n\nDump 4\n\n" << flush;
    ::DumpBlocksLogByLabelAndFile(NULL, DumpBlocksLogCallback,
				  0, "Char-Memory1", "mEmCoReTeSt.CpP");
#endif // __DEBUG__


    ::ShutdownDebugMemoryManager();

    return(0);
}

	
