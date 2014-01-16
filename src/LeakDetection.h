#ifndef LEAK_DETECTION_H
#define LEAK_DETECTION_H

//! Note: This is defined via CMake for the entire project or can be defined
//! individually per module (executable or library).
//!
//! Macro that controls whether the memory leak detection capability is
//! turned on.  If this macro is turned on, then memory leaks will be 
//! reported on application exit.
//! To test a single module, comment out USE_LEAK_DETECTION here and add 
//! the definition to the .cpp file that includes LeakDetection.h.  This 
//! will enable leak detection for that single module (DLL or EXE).
//#define USE_LEAK_DETECTION

// Only use memory leak detection when in Debug and then only if it has been 
// requested.
#if defined(_DEBUG) && defined(USE_LEAK_DETECTION)

// Include the visual leak detector header file.  Simply including this 
// header will turn on the leak detection.  Note that leak detection
// is only turned on for DLLs (or EXEs) that have at least one source
// file including vld.h.
#include "vld.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//! This macro captures the common portions used for both MFC and 
//! non-MFC projects.
//! @todo Figure out if there is a way that CMake CONFIGURE_FILE can 
//!       automatically add the dependent modules to the leak detection.
#define COMMON_LEAK_DETECTION \
	//HMODULE hModule; \
	
	// Note: Qt 4.7.4 (at least) seems to choke when attached to the leak 
	// detection.  That is why it is commented out here.
	//hModule = GetModuleHandle( _T("QtCored4.dll") ); \
	//VLDEnableModule(hModule); \
	//hModule = GetModuleHandle( _T("QtGuid4.dll") ); \
	//VLDEnableModule(hModule); \


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//! This macro abstracts code that needs to execute to initialize the leak
//! detection.  Each module (DLL or EXE) should execute this macro once to 
//! setup the memory leak detection.  Without this call, memory leaks from
//! 3rdParty libraries will not be reported.
#if defined(_DEBUG) && defined(_MFC_VER) 

#define INITIALIZE_LEAK_DETECTION \
	::AfxEnableMemoryLeakDump( FALSE );\
	COMMON_LEAK_DETECTION

#else

#define INITIALIZE_LEAK_DETECTION \
	COMMON_LEAK_DETECTION


#endif


#else

//! Macro defined as nothing for release mode.
#define INITIALIZE_LEAK_DETECTION

#endif

#endif //LEAK_DETECTION_H

