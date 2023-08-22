//---------------------------------------------------------------------------


#include "FileDlgProcesses.h"

#include "adecc_Scholar/MyForm.h"
#include "adecc_Scholar/MyTools.h"

#include <MyFileException.h>

#include <iostream>
#include <locale>
#include <sstream>
#include <exception>
#include <filesystem>
#include <algorithm>
#include <iterator>
#include <execution>

namespace fs = std::filesystem;
//#include "Wildcards.hpp"
//#include "globmatch.hpp"


//---------------------------------------------------------------------------
TFileDlgProcess::TFileDlgProcess(bool boDirOnly, bool boCaseSense) {
   msg_toggle = false;
   boDirectory_only = boDirOnly;
   boCaseSensitive = boCaseSense; 
   }

/// initialize the elements for the form to chose a file
void TFileDlgProcess::InitFileDlg(TMyForm& frm) {
   try {
      msg_toggle = false;

      InitDrives(frm);

      if(boDirectory_only) frm.SetCaption("Verzeichnis auswählen .. ");
      else                 frm.SetCaption("Datei auswählen .. ");

      frm.Set<EMyFrameworkType::label>     ("lblDrives",      "Laufwerk:");
      frm.Set<EMyFrameworkType::label>     ("lblDirectories", "Verzeichnisse:");


      if(!boDirectory_only && frm.Exists<EMyFrameworkType::listbox>("lbFiles")) {
         frm.Set<EMyFrameworkType::label> ("lblFiles", "Dateien:");
         frm.Set<EMyFrameworkType::label> ("lblFile",  "Datei:");
         frm.Set<EMyFrameworkType::edit>  ("edtFile",  "");
         frm.ReadOnly<EMyFrameworkType::edit>("edtFile", false);
         frm.ReadOnly<EMyFrameworkType::edit>("edtPath", true);
         }
      else {
         frm.Set<EMyFrameworkType::label>("lblPath", "Verzeichnis:");
         frm.ReadOnly<EMyFrameworkType::edit>("edtPath", true);
         }
      frm.Set<EMyFrameworkType::edit>      ("edtPath",        "");
      
      frm.Set<EMyFrameworkType::button>    ("btnOk",        "Übernehmen");
      frm.Set<EMyFrameworkType::button>    ("btnCancel",    "Abbruch");

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
   #if !defined BUILD_WITH_FMX
   // !!!!! Problems with fmx events
   else {
      throw my_filedlg_exception("TFileDlgProcess", strChangeDrivesEmpty, MY_POSITION());
      }
   #endif
   }

// ----------------------------------------------------------------------------
void TFileDlgProcess::ChangeDirectory(TMyForm& frm) {
   try {
      if (auto strDirectory = frm.Get<EMyFrameworkType::edit, std::string>("edtPath"); strDirectory) {
         fs::path myPath = *strDirectory;
         myPath = fs::canonical(myPath);
         frm.Set<EMyFrameworkType::edit>("edtPath", myPath.string());

         /*
         auto my_rel = [&myPath](fs::path const& p) {
            std::string ret = p.string().substr(p.string().rfind("\\") + 1, p.string().length());
            return ret;
            };
         */
         static constexpr auto my_rel = [](fs::path const& p) { return p.filename().string();  };

         std::vector<fs::path> files;
         std::copy(fs::directory_iterator(myPath), fs::directory_iterator(), std::back_inserter(files));

#if defined __BORLANDC__
         auto it1 = std::partition(files.begin(), files.end(), [](auto const& p) { return fs::is_directory(p); });
#else         
         auto it1 = std::partition(std::execution::par, files.begin(), files.end(), [](auto const& p) { return fs::is_directory(p); });
#endif
         std::ostream out(frm.GetAsStreamBuff<Latin, EMyFrameworkType::listbox>("lbDirectories"));

         if (boCaseSensitive) {
            std::sort(files.begin(), it1, [](auto const& a, auto const& b) { return a.filename() < b.filename(); });
            }
         else {
            std::sort(files.begin(), it1, [](auto const& a, auto const& b) {
                             return TMyTools::lower(a.filename().string()) < TMyTools::lower(b.filename().string()); });
            }
         std::vector<std::string>   vec;
         vec.reserve(std::distance(files.begin(), it1) + 1);

         if (myPath.filename().string() != "\\") vec.push_back("..");
         std::transform(files.begin(), it1, std::back_inserter(vec), my_rel);
         std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(out, "\n"));
         vec.clear();
         vec.reserve(std::distance(it1, files.end()) + 1);

         if(!boDirectory_only) {
            delete out.rdbuf(frm.GetAsStreamBuff<Latin, EMyFrameworkType::listbox>("lbFiles"));
            std::transform(it1, files.end(), std::back_inserter(vec), my_rel);
            if(boCaseSensitive) {
               std::sort(vec.begin(), vec.end(), [this](auto const& a, auto const& b) {
                               return a < b; });
               }
            else {
               std::sort(vec.begin(), vec.end(), [this](auto const& a, auto const& b) {
                               return TMyTools::lower(a) < TMyTools::lower(b); });
               }
            if (auto strPattern = frm.Get<EMyFrameworkType::edit, std::string>("edtFile"); strPattern) {
               static std::string strMatcher = "*?";
               if (TMyTools::contain(*strPattern, strMatcher) == true) {
                  std::copy_if(vec.cbegin(), vec.cend(), std::ostream_iterator<std::string>(out, "\n"), 
                        [&](std::string const& pa) { return TMyTools::wildcard_matching(pa, *strPattern, boCaseSensitive); });
 
                  }
               else {
                  std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(out, "\n"));
                  if(boCaseSensitive) {
                    if (std::find_if(vec.begin(), vec.end(), [this, &strPattern](std::string const& file) {
                                                              return file == *strPattern; }) != vec.end()) {
                       frm.SetListBox("lbFiles", *strPattern);
                       }
                    }
                  else {
                     std::string lower_p = TMyTools::lower(*strPattern);
                     if (std::find_if(vec.cbegin(), vec.cend(), [this, &lower_p](std::string const& file) {
                                                              return TMyTools::lower(file) == lower_p; }) != vec.end()) {
                        frm.SetListBox("lbFiles", *strPattern);
                        }
                     }
                  }
               }
            else {
               std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(out, "\n"));
               }
            }
         }
      }
   catch (std::exception& ex) {
      std::cerr << "Fehler beim Wechseln der Verzeichnisse" << std::endl << ex.what() << std::endl;
      }
   }

void TFileDlgProcess::ChangeFiles(TMyForm& frm) {
   if (!boDirectory_only) {
      auto selected = frm.GetSelectedRows<EMyFrameworkType::listbox>("lbFiles");
      if (selected.size() > 1u) throw my_filedlg_exception("TFileDlgProcess", strMultipleFiles, MY_POSITION());
      if (selected.size() == 1u) frm.Set<EMyFrameworkType::edit>("edtFile", frm.GetValue<EMyFrameworkType::listbox, std::string>("lbFiles", selected[0]));
      else  frm.Set<EMyFrameworkType::edit>("edtFile", "");
      }
   }

// zusätzlicher Parameter für BuildPath
// Nutzung der Methode tie, Rückgabewert
bool TFileDlgProcess::Execute(TMyForm& frm) {
   bool boRetVal = false;
   try {
      std::tie(boRetVal, strFileOrDirectory) = BuildPath(frm);
      }
   catch(my_file_dlg_error const& ex) {
      return false;
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


std::pair<bool, std::string> TFileDlgProcess::BuildPath(TMyForm& frm) {
   auto strDirectory = frm.Get<EMyFrameworkType::edit, std::string>("edtPath");
   fs::path retPath;
   if (!strDirectory) throw my_file_dlg_error("Can't build filename, field for directory is empty.");
   else retPath = *strDirectory;
   if(!boDirectory_only) {
      auto strFilename  = frm.Get<EMyFrameworkType::edit, std::string>("edtFile");
      if (!strFilename) {
         ChangeDirectory(frm);
         return std::make_pair(false, "");
         }
      else {
         static std::string strMatcher = "*?";
         if (TMyTools::contain(*strFilename, strMatcher) == true) {
            ChangeDirectory(frm);
            return std::make_pair(false, fs::canonical(retPath).string());
            }
         retPath /= *strFilename;
         }
      }
   return std::make_pair(true, fs::canonical(retPath).string());
   }


void TFileDlgProcess::SetFile(TMyForm& frm, std::string const& strFile) {
   if (!boDirectory_only) {
      frm.Set<EMyFrameworkType::edit>("edtFile", strFile);
      frm.SetListBox("lbFiles", strFile);
      }
   else throw my_file_dlg_error("Try to set Filename in Dialog without filename.");

   }

void TFileDlgProcess::SetDirectory(TMyForm& frm, std::string const& strFile) {
   frm.Set<EMyFrameworkType::edit>("edtPath", strFile);
   ChangeDirectory(frm);
   }

void TFileDlgProcess::SetRoot(TMyForm& frm, std::string const& strRoot) {
   frm.Set<EMyFrameworkType::combobox>("cbxDrives", strRoot);
   ChangeDrives(frm);
   }



std::string const& TFileDlgProcess::GetFileOrDirectory(TMyForm& frm) {
   return strFileOrDirectory;
   }


