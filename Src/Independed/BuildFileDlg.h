
#ifndef BUILD_FILEDLG_DLL
   #define MyFileLibAPI __declspec(dllimport)
#else
   #define MyFileLibAPI __declspec(dllexport)
#endif
