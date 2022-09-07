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
      std::string strExceptInitForm;    ///< error message for exceprions during initialize the form
      std::string strExceptReadDrive;   ///< error message for exceptions during initialize drives
      std::string strPathFieldEmpty;    ///< error message if path field empty
      std::string strDirectoriesEmpty;  ///< error message if directories unexpected empty
      std::string strChangeDrivesEmpty; ///< eror message because drive empty during change

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
   };



#endif
