#ifndef MyFileDlgH
#define MyFileDlgH

#include <BuildFileDlg.h>

#include "FileDlgProcesses.h"
#include <MyForm.h>
#include <string>
#include <utility>
#include <optional>
#include <stdexcept>
#include <map>
#include <tuple>

class MyFileLibAPI TMyFileDlg {
   public:
      static std::pair<EMyRetResults, std::string> SelectWithFileDirDlg(TMyForm& caller_frm, std::optional<std::string> const& path, bool parDirOnly = false);
      static void OpenFileAction(TMyForm& call_form, std::string const& strFile);

      static void LoadFile(std::wostream& stream, std::string const& strFile);
      static size_t CheckFileSize(std::string const& strFile);
      static std::tuple<std::wifstream, const size_t> OpenInputFile(std::string const& strFile);

   private:
      static void InitFileShowForm(TMyForm& frm, std::string const& strFile);
      static TMyForm CreateShowFile();
      static TMyForm CreateFileDlg(TFileDlgProcess& proc);
      static TMyForm CreateDirectoryDlg(TFileDlgProcess& proc);
   };


#endif