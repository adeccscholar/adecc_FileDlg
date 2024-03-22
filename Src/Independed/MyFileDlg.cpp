#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>

#include "MyFileDlg.h"

#if defined BUILD_WITH_VCL
#include "FileDlgFormVCL.h"
#include "DirectoryDlgFormVCL.h"
#include "FileShowFormVCL.h"
#include "MessageDlg.h"
#include "InputDlgVCL.h"
#elif defined BUILD_WITH_FMX
#include "FileDlgFormFMX.h"
#include "DirectoryDlgFormFMX.h"
#include "FileShowDlgFMX.h"
#include "InputDlgFMX.h"
#include "MessageDlgFMX.h"
#elif defined BUILD_WITH_QT
#include "FileDlgClass.h"
#include "FileShowClass.h"
#include "DirectoryDlgClass.h"
#include "MessageDlgClass.h"
#include "InputDlgClass.h"
#include "UserDlg.h"  // broken for VCL / FMX
//#include "ConsolClass.h"     // muss noch für VCL / FMX angepasst werden
#else
#error framework not defined
#endif

#include <MyFileException.h>
#include "FileDlgProcesses.h"
#include <adecc_Scholar/MyForm.h>

#include <fstream>
#include <locale>
#include <filesystem>
#include <system_error>

namespace fs = std::filesystem;


void TMyFileDlg::OpenFileAction(std::string const& strFile) {
   try {
      auto frm = CreateShowFile();
      InitFileShowForm(frm, strFile);
      frm.ShowModal();
   }
   catch (std::exception& ex) {
      TMyFileDlg::Message(EMyMessageType::error, "File App", ex.what());
   }
   catch (...) {
      TMyFileDlg::Message(EMyMessageType::error, "File App", "unexpected exception occured");
   }
}

/*
std::pair<TMyForm&&, std::ostream&&> TMyFileDlg::Console(void) {
   TMyForm frm;
#if defined BUILD_WITH_QT
   frm.Set(new ConsolClass(nullptr), true); 
#else
#error Implementation missed
#endif
   return { std::forward<TMyForm>(frm), 
            std::forward<std::ostream>(std::ostream(frm.GetAsStreamBuff<Narrow, EMyFrameworkType::memo>("memText"s))) };
}
*/

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

std::pair<EMyRetResults, std::string> TMyFileDlg::SelectWithFileDirDlg(std::optional<std::string> const& path, bool parDirOnly) {
   std::optional<std::string> strRetPath = {};
   bool boRetVal = false;
   TFileDlgProcess theFileDlgProcess(parDirOnly, false);

   try {
      if(!path) return std::make_pair(EMyRetResults::error, "path parameter is empty.");
      fs::path fsPath = *path;

      auto form = parDirOnly ? CreateDirectoryDlg(theFileDlgProcess) : CreateFileDlg(theFileDlgProcess);
      theFileDlgProcess.InitFileDlg(form);

         if(fsPath.is_absolute()) {
         if(fs::exists(fsPath)) {
            if(fs::is_directory(fsPath)) {
               if (fsPath.has_root_name()) {
                  theFileDlgProcess.SetRoot(form, TMyTools::upper(fsPath.root_name().string()));
                  }
               theFileDlgProcess.SetDirectory(form, fsPath.string());
               }
            else if(fs::is_regular_file(fsPath)) {
               if (fsPath.has_root_name()) {
                  theFileDlgProcess.SetRoot(form, TMyTools::upper(fsPath.root_name().string()));
                  }
               theFileDlgProcess.SetDirectory(form, fsPath.parent_path().string());
               theFileDlgProcess.SetFile(form, fsPath.filename().string());
               }
            else {
               std::ostringstream os;
               os << "device \"" << fsPath.string() << "\" exist, but can't use for this dialog.";
               return std::make_pair(EMyRetResults::error, os.str());
               }
            }
         else { // path is absolut, but don't exist, checking if parent directory exist
            if (fsPath.has_parent_path() && fs::exists(fsPath.parent_path())) {
               if (fsPath.parent_path().has_root_name()) {
                  theFileDlgProcess.SetRoot(form, TMyTools::upper(fsPath.parent_path().root_name().string()));
                  }
               theFileDlgProcess.SetDirectory(form, fsPath.parent_path().string());
               theFileDlgProcess.SetFile(form, fsPath.filename().string());
               }
            else {
               std::ostringstream os;
               os << "parent directory for the absolute path \"" << fsPath.string() << "\" don't exist.";
               return std::make_pair(EMyRetResults::error, os.str());
               }
            }
         }
   
      switch (auto ret = form.ShowModal(); ret) {
         case EMyRetResults::ok:
            return std::make_pair(ret, theFileDlgProcess.GetFileOrDirectory(form));
         default:
            return std::make_pair(ret, ""s);
         }
      }
   catch(std::exception const& ex) {
      return std::make_pair(EMyRetResults::error, ex.what());
      }
   }



EMyRetResults TMyFileDlg::Message(EMyMessageType paType, std::string const& paCaption, std::string const& paMessage, std::string const& paDetails) {
  TMyForm frm; 
  #if defined BUILD_WITH_VCL
      auto fw_frm = new TfrmMessage(paType, nullptr);
      frm.Set(fw_frm, true);
   #elif defined BUILD_WITH_FMX
      auto fw_frm = new TfrmMessageDlgFMX(paType, nullptr);
      frm.Set(fw_frm, true);
   #elif defined BUILD_WITH_QT
      frm.Set(new MessageDlgClass(paType, nullptr), true);
   #else
   #error no implementation for this framework
   #endif
   frm.SetCaption(paCaption);
   frm.Set<EMyFrameworkType::memo>("memMessage", paMessage);
   frm.Set<EMyFrameworkType::memo>("memDetails", paDetails);
   frm.Set<EMyFrameworkType::button>("btnOk", "Ja");
   frm.Set<EMyFrameworkType::button>("btnNo", "Nein");
   frm.Set<EMyFrameworkType::button>("btnCancel", "Abbruch");

   if(paType != EMyMessageType::question) {
      frm.Set<EMyFrameworkType::button>("btnOk", "Bestätigen");
      frm.Visible<EMyFrameworkType::button>("btnCancel", false);
      frm.Visible<EMyFrameworkType::button>("btnNo", false);
      }
   else {
      frm.Set<EMyFrameworkType::button>("btnOk", "Ja");
      }

   return frm.ShowModal();      
}

std::tuple <bool, std::optional<std::string>, std::optional<std::string>, std::optional<bool>> 
      TMyFileDlg::UserLoginDlg(std::string const& strTheme, bool boHasIntegrated, std::optional<std::string> const& strUser, bool boIntegrated) {
   TMyForm dlg;
   #if defined BUILD_WITH_VCL
      dlg.Set(new TfrmUserDlgVCL(nullptr), true);
   #elif defined BUILD_WITH_FMX
      dlg.Set(new TfrmUserDlgFMX( nullptr), true);
   #elif defined BUILD_WITH_QT
      dlg.Set(new UserDlg(nullptr), true);
   #else
      #error no implementation for this framework
   #endif

   dlg.SetCaption(strTheme);
   dlg.Set<EMyFrameworkType::groupbox, std::string>("grpUser", "credentials");

   dlg.Set<EMyFrameworkType::label, std::string>("lblUser", "user:");
   dlg.Set<EMyFrameworkType::edit, std::string>("edtUser", strUser.value_or(""));
   dlg.Set<EMyFrameworkType::label, std::string>("lblPassword", "password:");
   dlg.Set<EMyFrameworkType::edit, std::string>("edtPassword","");
   dlg.Set< EMyFrameworkType::checkbox, std::string>("chbIntegrated", "use integrated security");

   dlg.Set<EMyFrameworkType::button, std::string>("btnOk", "login");
   dlg.Set<EMyFrameworkType::button, std::string>("btnCancel", "cancel");

   if (dlg.ShowModal() == EMyRetResults::ok) {
      auto strUser = dlg.Get<EMyFrameworkType::edit, std::string>("edtUser").value_or("");
      auto strPwd = dlg.Get<EMyFrameworkType::edit, std::string>("edtPassword").value_or("");
      auto boIntegrated = dlg.Get<EMyFrameworkType::checkbox, bool>("chbIntegrated").value_or(false);
      return { true, strUser, strPwd, boIntegrated };
      }
   else return { false, { }, { }, { } };
   }

TMyForm TMyFileDlg::CreateInputDlg(int iType) {
     #if defined BUILD_WITH_VCL
   return { new TfmInputVCL(iType), true};
   #elif defined BUILD_WITH_FMX
   return { new TfmInputFMX(iType), true};
   #elif defined BUILD_WITH_QT  
   return { new InputDlgClass(iType), true };
   #else
      #error No implemetation for the choosen framework
   #endif
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

TMyForm TMyFileDlg::CreateDirectoryDlg(TFileDlgProcess& proc) {
#if defined BUILD_WITH_VCL
   //#error No implemetation for VCL
   return TMyForm(new TfrmDirectoryDlgVCL(proc, nullptr), true);
#elif defined BUILD_WITH_FMX
   return TMyForm(new TfrmDirectoryDlgFMX(proc, nullptr), true);
#elif defined BUILD_WITH_QT
   return TMyForm(new DirectoryDlgClass(proc, nullptr), true);
#else
#error No implemetation for the choosen framework
#endif
}

void TMyFileDlg::TMyFileDlg::InitFileShowForm(TMyForm& frm, std::string const& strFile) {
   frm.Set<EMyFrameworkType::button>("btnOk", "Schließen");
   std::wostream mys(frm.GetAsStreamBuff<Wide, EMyFrameworkType::memo>("memFile"), true);
   mys.imbue(std::locale());
   frm.SetCaption(strFile);
   LoadFile(mys, strFile);
   frm.SetPosition<EMyFrameworkType::memo>("memFile", 0u);
   frm.ReadOnly<EMyFrameworkType::memo>("memFile", true);
   }

// witout exception -> open wstream + actual size
std::tuple<std::wifstream, const size_t> TMyFileDlg::OpenInputFile(std::string const& strFile) {
   std::wifstream ifs;
   ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
   try {
      std::locale loc(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10FFFF, std::consume_header>);
      ifs.imbue(loc);
      ifs.open(strFile);
      if (!ifs.is_open()) throw std::system_error(errno, std::generic_category(), strFile);  // if std::ifstream::failbit isn't set
      const size_t iSize = fs::file_size(strFile);
     ifs.exceptions(std::ifstream::goodbit);
      return { std::forward< std::wifstream>(ifs), iSize };
      }
   catch (std::ios_base::failure const& ex) {
      if (ex.code() == std::make_error_condition(std::io_errc::stream))
         throw my_file_information(strFile, static_cast<std::errc>(errno));
      else
         throw my_file_information(strFile, static_cast<std::errc>(ex.code().value()));
   }
   catch (std::system_error const& ex) {
      throw my_file_information(strFile, static_cast<std::errc>(ex.code().value()));
   }
   // can't reach because in each catch a new exception thrown
}


void TMyFileDlg::LoadFile(std::wostream& stream, std::string const& strFile) {
   try {
      auto [ifs, iSize] = OpenInputFile(strFile);
      std::wstring strBuff(iSize, '\0');
      ifs.read(strBuff.data(), iSize);
      ifs.close();
      stream << strBuff;
      }
   catch (my_file_information const& ex) {
      throw my_file_runtime_error(ex, my_source_position(__func__, __FILE__, __LINE__));
      }
   catch(std::ios_base::failure const& ex) {
      if (ex.code() == std::make_error_condition(std::io_errc::stream))
         throw my_file_runtime_error(strFile, static_cast<std::errc>(errno), my_source_position(__func__, __FILE__, __LINE__));
      else
         throw my_file_runtime_error(strFile, static_cast<std::errc>(ex.code().value()), my_source_position(__func__, __FILE__, __LINE__));
      }
   catch (std::system_error const& ex) {
      throw my_file_runtime_error(strFile, static_cast<std::errc>(ex.code().value()), my_source_position(__func__, __FILE__, __LINE__));
      }
  }

size_t TMyFileDlg::CheckFileSize(std::string const& strFile) {
   auto [ifs, iSize] = OpenInputFile(strFile);
   std::wstring strBuff(iSize, '\0');
   ifs.read(strBuff.data(), iSize);
   ifs.close();
   std::wstring_view test(strBuff.data(), strBuff.size());
   return std::count(test.begin(), test.end(), '\n');
}

std::pair<EMyRetResults, fw_String> TMyFileDlg::InputDlg(fw_String const& value, std::string const& paCaption, std::string const& paDescription, std::string const& paRange) {
   auto frm = CreateInputDlg();
   frm.SetCaption(paCaption);
   frm.Set<EMyFrameworkType::label>("lblDescription", paDescription);
   frm.Set<EMyFrameworkType::label>("lblRange", paRange);
   frm.Set<EMyFrameworkType::button>("btnOk", "Bestätigen");
   frm.Set<EMyFrameworkType::button>("btnCancel", "Abbruch");
   frm.Set<EMyFrameworkType::edit>("edtValue", value);

   if (auto ret = frm.ShowModal(); ret == EMyRetResults::ok) {
      auto val = frm.Get<EMyFrameworkType::edit, fw_String>("edtValue");
      if (!val) {
         return std::make_pair(EMyRetResults::error, fw_String());
      }
      else return std::make_pair(ret, *val);
   }
   else {
      return std::make_pair(ret, fw_String());
   }
}


std::pair<EMyRetResults, std::filesystem::path> TMyFileDlg::InputDlg(std::filesystem::path const& value, std::string const& paCaption, std::string const& paDescription, std::string const& paRange) {
   auto frm = CreateInputDlg(1);
   frm.SetCaption(paCaption);
   frm.Set<EMyFrameworkType::label>("lblDescription", paDescription);
   frm.Set<EMyFrameworkType::label>("lblRange", paRange);
   frm.Set<EMyFrameworkType::button>("btnOk", "Bestätigen");
   frm.Set<EMyFrameworkType::button>("btnCancel", "Abbruch");
 
   frm.Set<EMyFrameworkType::edit>("edtValue", value.string());

   if (auto ret = frm.ShowModal(); ret == EMyRetResults::ok) {
      auto val = frm.Get<EMyFrameworkType::edit, std::string>("edtValue");
      if (!val) {
         return std::make_pair(EMyRetResults::error, std::filesystem::path());
      }
      else return std::make_pair(ret, std::filesystem::path(*val));
   }
   else {
      return std::make_pair(ret, std::filesystem::path());
   }
}
