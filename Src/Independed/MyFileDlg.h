#ifndef MyFileDlgH
#define MyFileDlgH

#include "FileDlgProcesses.h"
#include <MyForm.h>
#include <string>
#include <utility>
#include <optional>
#include <stdexcept>
#include <map>


class my_file_runtime_error : public std::runtime_error {
private:
   std::string strFile;          ///< Ursprung des Fehlers
   mutable std::string strWhat;  ///< Hilfsobjekt, um Lebensdauer von what() zu gewährleisten
   my_source_position thePosition;
   static std::map<std::errc, std::pair<std::string, std::string>> errc_messages;
public:
   my_file_runtime_error(std::string const& pSrc, std::string pMsg,
      std::string const& pFunc, std::string const& pFile, size_t pLine) : std::runtime_error(pMsg),
      strFile(pSrc), thePosition(pFunc, pFile, pLine) { }

   my_file_runtime_error(std::string const& pSrc, std::string pMsg, my_source_position&& pPos) : std::runtime_error(pMsg),
      strFile(pSrc), thePosition(std::forward<my_source_position>(pPos)) { }

   my_file_runtime_error(std::string const& pSrc, std::errc value, my_source_position&& pPos) : std::runtime_error(errc_messages[value].second),
      strFile(pSrc), thePosition(std::forward<my_source_position>(pPos)) { }


   virtual const char* what() const noexcept;
};


class TMyFileDlg {
   public:
      static std::pair<EMyRetResults, std::string> SelectWithFileDirDlg(TMyForm& caller_frm, std::optional<std::string> const& strField);
      static void OpenFileAction(TMyForm& call_form, std::string const& strFile);

      static void LoadFile(std::wostream& stream, std::string const& strFile);
   private:
      static TFileDlgProcess inline theFileDlgProcess;

      static void InitFileShowForm(TMyForm& frm, std::string const& strFile);
      static TMyForm CreateShowFile();
      static TMyForm CreateFileDlg(TFileDlgProcess& proc);
   };


#endif