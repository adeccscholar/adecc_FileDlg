#include "MyFileDlg.h"

#if defined BUILD_WITH_VCL
#include "FileDlgFormVCL.h"
#include "FileShowFormVCL.h"
#elif defined BUILD_WITH_FMX
#include "FileDlgFormFMX.h"
#include "FileShowDlgFMX.h"
#elif defined BUILD_WITH_QT
#include "FileDlgClass.h"
#include "FileShowClass.h"
#else
#error framework not defined
#endif


void TMyFileDlg::OpenFileAction(TMyForm& call_form, std::string const& strFile) {
   try {
      auto frm = CreateShowFile();
      theFileDlgProcess.InitFileShowForm(frm, strFile);
      frm.ShowModal();
   }
   catch (std::exception& ex) {
      call_form.Message(EMyMessageType::error, "File App", ex.what());
   }
   catch (...) {
      call_form.Message(EMyMessageType::error, "File App", "unexpected excepttion occured");
   }
}


TMyForm TMyFileDlg::CreateShowFile() {
#if defined BUILD_WITH_VCL
   TfrmFileShowVCL* fwform = new TfrmFileShowVCL(nullptr);
   TMyForm frm(fwform, true);
   return frm;
#elif defined BUILD_WITH_FMX
   return TMyForm(new TfrmFileShowDlg(nullptr), true);
#elif defined BUILD_WITH_QT
   return TMyForm(new FileShowClass(nullptr), true);
#else
#error No implemetation for the choosen framework
#endif
}

std::pair<EMyRetResults, std::string> TMyFileDlg::SelectWithFileDirDlg(TMyForm& caller_frm, std::optional<std::string> const& path) {
   std::optional<std::string> strRetPath = {};
   bool boRetVal = false;
      
   auto form = CreateFileDlg(theFileDlgProcess);
   theFileDlgProcess.InitFileDlg(form);
   if (path) {
      theFileDlgProcess.SetFileOrDirectory(form, *path);
      switch (auto ret = form.ShowModal(); ret) {
         case EMyRetResults::ok:
            return std::make_pair(ret, theFileDlgProcess.GetFileOrDirectory(form));
         default:
            return std::make_pair(ret, ""s);
         }
      }
   else {
      return std::make_pair(EMyRetResults::error, "path is empty or invalid."s);
      }
   }


TMyForm TMyFileDlg::CreateFileDlg(TFileDlgProcess& proc) {
   #if defined BUILD_WITH_VCL
      return TMyForm(new TfrmFileDlg(proc, nullptr), true);
   #elif defined BUILD_WITH_FMX
      return TMyForm(new TfrmFileDlgFMX(proc, nullptr), true);
   #elif defined BUILD_WITH_QT
      return TMyForm(new FileDlgClass(proc, nullptr), true);
   #else
     #error No implemetation for the choosen framework
   #endif
   }
