//---------------------------------------------------------------------------

#ifndef FileDlgProcessesH
#define FileDlgProcessesH
//---------------------------------------------------------------------------

#include "MyForm.h"
#include "MyTools.h"
#include <string>
#include <utility>

//using mpOperations = std::map<std::string, std::function<void (TMyForm&)>>;

/// process class for the fileopen - dialog
class TFileDlgProcess {
   protected:
      static inline std::string strExceptInitForm    = "error while initialization FileDlg";
      static inline std::string strExceptReadDrive   = "error while reading the drives ...";
      static inline std::string strPathFieldEmpty    = "path information can't processed, path is empty.";
      static inline std::string strDirectoriesEmpty  = "listbox with directories is empty unexpected.";
      static inline std::string strChangeDrivesEmpty = "drives box is empty while changing";
      static inline std::string strMultipleFiles     = "multiple selections for files isn't supported";

      bool                  msg_toggle       = false; ///< switch for framework messages
      bool                  boDirectory_only = false; ///< only directories to chose
      bool                  boCaseSensitive  = false; ///< are names casesensitive? 
      std::string           strFileOrDirectory = "";  ///< choosen file or directory for return
   public:
      TFileDlgProcess() = default;
      TFileDlgProcess(bool, bool);
      TFileDlgProcess(TFileDlgProcess const&) = delete;
      TFileDlgProcess(TFileDlgProcess&&) = delete;
      ~TFileDlgProcess() = default;
      void InitFileDlg(TMyForm& frm);
      void ChangeDirectory(TMyForm& frm);
      void ClickDirectory(TMyForm& frm);
      void ChangeDrives(TMyForm& frm);
      void ChangeFiles(TMyForm& frm);
      void Backward(TMyForm& frm);

      bool FireMessages(void) { return msg_toggle; }
      bool Execute(TMyForm& frm);

      void SetFile(TMyForm& frm, std::string const& strFile);
      void SetDirectory(TMyForm& frm, std::string const& strFile);
      void SetRoot(TMyForm& frm, std::string const& strRoot);

      std::string const& GetFileOrDirectory(TMyForm& frm);

private:
   void InitDrives(TMyForm& frm);
   std::pair<bool, std::string> BuildPath(TMyForm& frm);

   };




#endif
