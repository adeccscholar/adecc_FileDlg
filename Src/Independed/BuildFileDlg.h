
#if defined BUILD_WITH_VCL || defined BUILD_WITH_FMX || defined FILEDLG_QT_LIB

#ifndef BUILD_FILEDLG_DLL
   #define MyFileLibAPI __declspec(dllimport)
#else
   #define MyFileLibAPI __declspec(dllexport)
#endif

#else

#define MyFileLibAPI

#endif
