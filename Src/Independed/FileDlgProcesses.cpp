//---------------------------------------------------------------------------
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>

#include "FileDlgProcesses.h"

#include "MyForm.h"
#include "MyTools.h"


#include <iostream>
#include <locale>
#include <sstream>
#include <fstream>
#include <exception>
#include <filesystem>
#include <algorithm>
#include <iterator>
#include <execution>

namespace fs = std::filesystem;
//#include "Wildcards.hpp"
//#include "globmatch.hpp"


const char* my_filedlg_exception::what() const noexcept {
   std::ostringstream os;
   os << strSource << ": " << strMessage << " " << thePosition;
   strWhat = os.str();
   return strWhat.c_str();
   }

//---------------------------------------------------------------------------

/// initialize the elements for the form to chose a file
void TFileDlgProcess::InitFileDlg(TMyForm& frm) {
   try {
      msg_toggle = false;
      
      frm.SetCaption("Datei auswählen .. ");
      frm.Set<EMyFrameworkType::label>     ("lblDrives",      "Laufwerk:");
      frm.Set<EMyFrameworkType::label>     ("lblDirectories", "Verzeichnisse:");

      if(frm.Exists<EMyFrameworkType::listbox>("lbFiles")) {
         frm.Set<EMyFrameworkType::label> ("lblFiles", "Dateien:");
         frm.Set<EMyFrameworkType::label> ("lblFile",  "Datei:");
         frm.Set<EMyFrameworkType::edit>  ("edtFile",  "");
         frm.ReadOnly<EMyFrameworkType::edit>("edtPath", true);
         }
      else
         frm.ReadOnly<EMyFrameworkType::edit>("edtPath", false);

      frm.Set<EMyFrameworkType::edit>      ("edtPath",        "");
      
      frm.Set<EMyFrameworkType::button>    ("btnOk",        "Übernehmen");
      frm.Set<EMyFrameworkType::button>    ("btnCancel",    "Abbruch");

      InitDrives(frm);
      ChangeDrives(frm);  // only for vcl really necessary
      msg_toggle = true;
      }
   catch(std::exception &ex) {
      std::cerr << strExceptInitForm << std::endl << ex.what() << std::endl;
      }
   }

/// Initialization for the drives. Only Windows know Letter as drives
void TFileDlgProcess::InitDrives(TMyForm& frm) {
   try {
      //ostream out(frm.GetAsStreamBuff<Narrow, EMyFrameworkType::combobox>("cbxDrives"));
      std::vector<std::string> vecDrives;
      for(char drive = 'A'; drive <= 'Z'; ++drive) {
         if (fs::path myPath = std::string{ drive, ':', '\0' }; fs::exists(myPath))
            vecDrives.push_back(myPath.string());
         }
      frm.InitCombobox("cbxDrives", vecDrives);
      frm.SetFirstComboBox("cbxDrives");
      }
   catch(std::exception &ex) {
      std::cerr << strExceptReadDrive << std::endl << ex.what() << std::endl;
      }
   }

// ----------------------------------------------------------------------------
void TFileDlgProcess::ChangeDrives(TMyForm& frm) {
   if(auto strDrive = frm.Get<EMyFrameworkType::combobox, std::string>("cbxDrives"); strDrive) {
      *strDrive += "\\";
      frm.Set<EMyFrameworkType::edit>("edtPath", strDrive);
      ChangeDirectory(frm);
      }
   else {
      throw my_filedlg_exception("TFileDlgProcess", strChangeDrivesEmpty, MY_POSITION());
      }
   }

// ----------------------------------------------------------------------------
void TFileDlgProcess::ChangeDirectory(TMyForm& frm) {
   try {
      if (auto strDirectory = frm.Get<EMyFrameworkType::edit, std::string>("edtPath"); strDirectory) {
         fs::path myPath = *strDirectory;
         myPath = fs::canonical(myPath);
         frm.Set<EMyFrameworkType::edit>("edtPath", myPath.string());

         auto my_rel = [&myPath](fs::path const& p) {
            std::string ret = p.string().substr(p.string().rfind("\\") + 1, p.string().length());
            return ret;
            };

         std::vector<fs::path> files;
         std::copy(fs::directory_iterator(myPath), fs::directory_iterator(), std::back_inserter(files));

         auto it1 = std::partition(files.begin(), files.end(), [](auto const& p) { return fs::is_directory(p); });

         std::ostream out(frm.GetAsStreamBuff<Narrow, EMyFrameworkType::listbox>("lbDirectories"));

         std::sort(files.begin(), it1,
            [this](auto const& a, auto const& b) {
               return TMyTools::lower(a.filename().string()) < TMyTools::lower(b.filename().string());
            });
         std::vector<std::string>   vec;
         vec.reserve(std::distance(files.begin(), it1) + 1);

         if (myPath.filename().string() != "\\") vec.push_back("..");
         std::transform(files.begin(), it1, std::back_inserter(vec), my_rel);
         std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(out, "\n"));
         vec.clear();
         vec.reserve(std::distance(it1, files.end()) + 1);
         delete out.rdbuf(frm.GetAsStreamBuff<Narrow, EMyFrameworkType::listbox>("lbFiles"));
         std::transform(it1, files.end(), std::back_inserter(vec), my_rel);
         std::sort(vec.begin(), vec.end(), [this](auto const& a, auto const& b) {
            return TMyTools::lower(a) < TMyTools::lower(b); });
         if (auto strPattern = frm.Get<EMyFrameworkType::edit, std::string>("edtFile"); strPattern) {
            static std::string strMatcher = "*?";
            if (TMyTools::contain(*strPattern, strMatcher) == true) {
                std::copy_if(vec.cbegin(), vec.cend(), std::ostream_iterator<std::string>(out, "\n"), [&](std::string const& pa) { return TMyTools::wildcard_matching(pa, *strPattern); });
 
            }
            else {
               std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(out, "\n"));
               std::string lower_p = TMyTools::lower(*strPattern);
               if (std::find_if(vec.begin(), vec.end(), [this, &lower_p](std::string const& file) {
                  return TMyTools::lower(file) == lower_p; }) != vec.end()) {
                  frm.SetListBox("lbFiles", *strPattern);
               }
            }
         }
         else {
            std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(out, "\n"));
         }
      }
      }
   catch (std::exception& ex) {
      std::cerr << "Fehler beim Wechseln der Verzeichnisse" << std::endl << ex.what() << std::endl;
      }
   }


bool TFileDlgProcess::Execute(TMyForm& frm) {
   bool boRetVal = false;
   SplitPath(frm);
   if(auto strDirectory = frm.Get<EMyFrameworkType::edit, std::string>("edtPath"); strDirectory) {
      if(auto strFile = frm.Get<EMyFrameworkType::edit, std::string>("edtFile"); strFile) {
         if(!TMyTools::contain(*strFile, "*?")) {
            return true;
            }
         }
      }
   return boRetVal;
   }


void TFileDlgProcess::Backward(TMyForm& frm) {
   // go backward
   }

void TFileDlgProcess::ClickDirectory(TMyForm& frm) {
   if(auto strDir = frm.Get<EMyFrameworkType::listbox, std::string>("lbDirectories"); strDir) {
      if(auto strPath = frm.Get<EMyFrameworkType::edit, std::string>("edtPath"); strPath) {
         fs::path pa(*strPath);
         pa /= fs::path(*strDir);
         frm.Set<EMyFrameworkType::edit>("edtPath", pa.string());
         ChangeDirectory(frm);
         }
      else throw my_filedlg_exception("TFileDlgProcess", strPathFieldEmpty, MY_POSITION());
      }
   else throw my_filedlg_exception("TFileDlgProcess", strDirectoriesEmpty, MY_POSITION());
   }

void TFileDlgProcess::ChangeFiles(TMyForm& frm) {
   auto selected = frm.GetSelectedRows<EMyFrameworkType::listbox>("lbFiles");
   if(selected.size() > 1) throw my_filedlg_exception("TFileDlgProcess", strMultipleFiles, MY_POSITION());
   if (selected.size() == 1) frm.Set<EMyFrameworkType::edit>("edtFile", frm.GetValue<EMyFrameworkType::listbox, std::string>("lbFiles", selected[0]));
   else  frm.Set<EMyFrameworkType::edit>("edtFile", "");
   }


/// processing the chosen path and split it in the components
void TFileDlgProcess::SplitPath(TMyForm& frm) {
   msg_toggle = false;
   try {
      std::optional<std::string> strDirectory;
      std::optional<std::string> strDrive;
      std::optional<std::string> strFilename;
      std::optional<std::string> strDir;
      std::optional<std::string> strPath;

      if(auto strDirectory = frm.Get<EMyFrameworkType::edit, std::string>("edtFile"); strDirectory) {
         if(fs::path check = *strDirectory; check.root_name() != fs::path("")) {
            strFilename = frm.Get<EMyFrameworkType::edit, std::string>("edtFile");
            frm.Set<EMyFrameworkType::edit>("edtFile", "");
            frm.Set<EMyFrameworkType::edit>("edtPath", strDirectory);   /// !!!!! Fehler
            }
         else {
            strDirectory = frm.Get<EMyFrameworkType::edit, std::string>("edtPath");
            }
         }
      else {
         strDirectory = frm.Get<EMyFrameworkType::edit, std::string>("edtPath");
         }

      if(!strDirectory) throw my_filedlg_exception("TFileDlgProcess", "path is empty or don't exist.", MY_POSITION());
      fs::path pa = *strDirectory;

      strDrive = std::make_optional(TMyTools::upper(pa.root_name().string()));
      if(fs::is_directory(pa)) {
         strDir      = std::make_optional(pa.filename().string());
         strPath     = std::make_optional(pa.parent_path().string());

         frm.Set<EMyFrameworkType::combobox>("cbxDrives", strDrive);
         frm.Set<EMyFrameworkType::edit>("edtPath", pa.string());
         }
      else {
         strFilename = make_optional(pa.filename().string());
         strPath     = make_optional(pa.parent_path().string());

         frm.Set<EMyFrameworkType::combobox>("cbxDrives", strDrive);
         frm.Set<EMyFrameworkType::edit>("edtPath", pa.parent_path().string());
         frm.Set<EMyFrameworkType::edit>("edtFile", pa.filename().string());
         }

      ChangeDirectory(frm);
      }
   catch(std::exception &ex) {
      std::cerr << "error while splitting the path in function SplitPath" << std::endl
           << ex.what() << std::endl;
      }
   msg_toggle = true;
   }


void TFileDlgProcess::SetFileOrDirectory(TMyForm& frm, std::string const& strFile) {
   frm.Set<EMyFrameworkType::edit>("edtFile", strFile);
   SplitPath(frm);
   return;
   }

std::string TFileDlgProcess::GetFileOrDirectory(TMyForm& frm) {
   fs::path mypath;
   if(auto strDirectory = frm.Get<EMyFrameworkType::edit, std::string>("edtPath"); strDirectory) {
      mypath = *strDirectory;
      if(auto strFile = frm.Get<EMyFrameworkType::edit, std::string>("edtFile"); strFile) {
         mypath /= fs::path(*strFile);
         }
      }
   return mypath.string();
   }

void TFileDlgProcess::InitFileShowForm(TMyForm& frm, std::string const& strFile) {
   frm.Set<EMyFrameworkType::button>("btnOk", "Schließen");
   std::wostream mys(frm.GetAsStreamBuff<Wide, EMyFrameworkType::memo>("memFile"), true);
   mys.imbue(std::locale());
   frm.SetCaption(strFile);
   std::wifstream ifs(strFile);
   std::locale loc(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10FFFF, std::consume_header>);
   ifs.imbue(loc);
   if (!ifs.is_open()) {
      std::ostringstream os;
      os << "error while opening file \"" << strFile << "\".";
      throw std::runtime_error(os.str().c_str());
   }
   const auto iSize = fs::file_size(strFile);
   std::wstring strBuff(iSize, '\0');
   ifs.read(strBuff.data(), iSize);
   ifs.close();
   mys << strBuff;
   frm.SetPosition<EMyFrameworkType::memo>("memFile", 0u);
   frm.ReadOnly<EMyFrameworkType::memo>("memFile", true);
}

