#ifndef MyFileDlgH
#define MyFileDlgH

#include "FileDlgProcesses.h"
#include <MyForm.h>
#include <string>
#include <utility>
#include <optional>

class TMyFileDlg {
   public:
      static std::pair<EMyRetResults, std::string> SelectWithFileDirDlg(TMyForm& caller_frm, std::optional<std::string> const& strField);
      static void OpenFileAction(TMyForm& call_form, std::string const& strFile);
   private:
      static TFileDlgProcess inline theFileDlgProcess;
      static TMyForm CreateShowFile();
      static TMyForm CreateFileDlg(TFileDlgProcess& proc);
   };


#endif