#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>

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

#include <MyFileException.h>

#include <fstream>
#include <locale>
#include <filesystem>
#include <system_error>


namespace fs = std::filesystem;




void TMyFileDlg::OpenFileAction(TMyForm& call_form, std::string const& strFile) {
   try {
      auto frm = CreateShowFile();
      InitFileShowForm(frm, strFile);
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
      
   try {
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
   catch(std::exception const& ex) {
      return std::make_pair(EMyRetResults::error, ex.what());
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
      ifs.exceptions(0);
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

   //return { ifs, 0u };
}

void TMyFileDlg::LoadFile(std::wostream& stream, std::string const& strFile) {
   try {
      //std::wifstream ifs;
      auto [ifs, iSize] = OpenInputFile(strFile);

      std::wstring strBuff(iSize, '\0');
      ifs.read(strBuff.data(), iSize);
      ifs.close();
      stream << strBuff;
      }
   catch(std::ios_base::failure const& ex) {
      if (ex.code() == std::make_error_condition(std::io_errc::stream))
         throw my_file_runtime_error(strFile, static_cast<std::errc>(errno), MY_POSITION());
      else
         throw my_file_runtime_error(strFile, static_cast<std::errc>(ex.code().value()), MY_POSITION());
      }
   catch (std::system_error const& ex) {
      throw my_file_runtime_error(strFile, static_cast<std::errc>(ex.code().value()), MY_POSITION());
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

 
/*
void TMyFileDlg::LoadFile(std::wostream& stream, std::string const& strFile) {
   std::wifstream ifs;
   ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
   //ifs.exceptions(std::ifstream::badbit);
   try {
      std::locale loc(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10FFFF, std::consume_header>);
      ifs.imbue(loc);
      ifs.open(strFile);
      if (!ifs.is_open()) throw std::system_error(errno, std::generic_category(), strFile);  // if std::ifstream::failbit isn't set
      const auto iSize = fs::file_size(strFile);
      ifs.exceptions(0);
      std::wstring strBuff(iSize, '\0');
      ifs.read(strBuff.data(), iSize);
      ifs.close();
      stream << strBuff;
   }
   catch (std::ios_base::failure const& ex) {
      if (ex.code() == std::make_error_condition(std::io_errc::stream))
         throw my_file_runtime_error(strFile, static_cast<std::errc>(errno), MY_POSITION());
      else
         throw my_file_runtime_error(strFile, static_cast<std::errc>(ex.code().value()), MY_POSITION());
   }
   catch (std::system_error const& ex) {
      throw my_file_runtime_error(strFile, static_cast<std::errc>(ex.code().value()), MY_POSITION());
   }

}
*/