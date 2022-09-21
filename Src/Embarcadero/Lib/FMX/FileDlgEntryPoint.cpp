//   Wichtiger Hinweis zur DLL-Speicherverwaltung, wenn Ihre DLL die statische
//   Version der Laufzeitbibliothek verwendet:
//
//   Wenn Ihre DLL Funktionen exportiert, die String-Objekte (oder Strukturen/Klassen
//   mit verschachtelten Strings) als Parameter oder Funktionsergebnisse übergeben,
//   müssen Sie die Bibliothek MEMMGR.LIB dem DLL-Projekt und allen anderen Projekten,
//   die die DLL verwenden, hinzufügen.  Außerdem müssen Sie die MEMMGR.LIB verwenden, 
//   wenn andere Projekte, die die DLL einsetzen, Neu- oder Löschen-Operationen für nicht
//   von TObject abgeleitete Klassen durchführen, die aus der DLL exportiert
//   wurden. Das Hinzufügen von MEMMGR.LIB zu Ihrem Projekt ändert die DLL und ihre aufrufenden 
//   EXE-Dateien, damit diese BORLNDMM.DLL als Speicherverwaltung verwenden.  In diesen Fällen
//   muss die Datei BORLNDMM.DLL zusammen mit Ihrer DLL weitergegeben werden.
//
//   Übergeben Sie String-Informationen mit "char *" oder ShortString-Parametern, 
//   um die Verwendung von BORLNDMM.DLL zu vermeiden.
//
//   Wenn Ihre DLL die dynamische Version der RTL verwendet, müssen Sie MEMMGR.LIB
//   nicht explizit hinzufügen, weil dies implizit ausgeführt wird.

#include <fmx.h>

#pragma hdrstop
#pragma argsused

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

