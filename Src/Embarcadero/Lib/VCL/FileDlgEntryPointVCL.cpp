//   Wichtiger Hinweis zur DLL-Speicherverwaltung, wenn Ihre DLL die statische
//   Version der Laufzeitbibliothek verwendet:
//
//   Wenn Ihre DLL Funktionen exportiert, die String-Objekte (oder Strukturen/Klassen
//   mit verschachtelten Strings) als Parameter oder Funktionsergebnisse �bergeben,
//   m�ssen Sie die Bibliothek MEMMGR.LIB dem DLL-Projekt und allen anderen Projekten,
//   die die DLL verwenden, hinzuf�gen.  Au�erdem m�ssen Sie die MEMMGR.LIB verwenden, 
//   wenn andere Projekte, die die DLL einsetzen, Neu- oder L�schen-Operationen f�r nicht
//   von TObject abgeleitete Klassen durchf�hren, die aus der DLL exportiert
//   wurden. Das Hinzuf�gen von MEMMGR.LIB zu Ihrem Projekt �ndert die DLL und ihre aufrufenden 
//   EXE-Dateien, damit diese BORLNDMM.DLL als Speicherverwaltung verwenden.  In diesen F�llen
//   muss die Datei BORLNDMM.DLL zusammen mit Ihrer DLL weitergegeben werden.
//
//   �bergeben Sie String-Informationen mit "char *" oder ShortString-Parametern, 
//   um die Verwendung von BORLNDMM.DLL zu vermeiden.
//
//   Wenn Ihre DLL die dynamische Version der RTL verwendet, m�ssen Sie MEMMGR.LIB
//   nicht explizit hinzuf�gen, weil dies implizit ausgef�hrt wird.

#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

// BUILD_FILEDLG_DLL

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved) {
   switch(reason) {
      case DLL_PROCESS_ATTACH:
         ::CoInitialize(0);
         break;
      case DLL_THREAD_ATTACH:
         break;
      case DLL_THREAD_DETACH:
         break;
      case DLL_PROCESS_DETACH:
         ::CoUninitialize();
         break;
      }
	return 1;
   }

