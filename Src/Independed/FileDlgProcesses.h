//---------------------------------------------------------------------------

#ifndef FileDlgProcessesH
#define FileDlgProcessesH
//---------------------------------------------------------------------------

#include "MyForm.h"
#include "MyTools.h"
#include <string>

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

      bool                  msg_toggle; ///< switch for framework messages
   public:
      void InitFileDlg(TMyForm& frm);
      void InitDrives(TMyForm& frm);
      void ChangeDirectory(TMyForm& frm);
      void ClickDirectory(TMyForm& frm);
      void ChangeDrives(TMyForm& frm);
      void ChangeFiles(TMyForm& frm);
      void SplitPath(TMyForm& frm);
      void Backward(TMyForm& frm);

      bool FireMessages(void) { return msg_toggle; }
      bool Execute(TMyForm& frm);
      void SetFileOrDirectory(TMyForm& frm, std::string const& strFile);
      std::string GetFileOrDirectory(TMyForm& frm);

private:

   };




#endif
