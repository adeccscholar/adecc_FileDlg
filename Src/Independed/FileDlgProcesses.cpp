//---------------------------------------------------------------------------

#include "FileDlgProcesses.h"

#include "MyForm.h"
#include "MyTools.h"

#include <iostream>
#include <exception>
#include <filesystem>
#include <algorithm>
#include <iterator>
#include <execution>

using namespace std;
namespace fs = std::filesystem;
//#include "Wildcards.hpp"
//#include "globmatch.hpp"


//---------------------------------------------------------------------------

/// initialize the elements for the form to chose a file
void TFileDlgProcess::InitFileDlg(TMyForm& frm) {
   try {
      msg_toggle = false;
      strExceptInitForm    = "error while initialization FileDlg";
      strExceptReadDrive   = "error while reading the drives ...";
      strPathFieldEmpty    = "path information can't processed, path is empty.";
      strDirectoriesEmpty  = "listbox with directories is empty unexpected.";
      strChangeDrivesEmpty = "drives box is empty while changing";

      frm.SetCaption("Datei auswählen .. ");
      frm.Set<EMyFrameworkType::label>     ("lblDrives",      "Laufwerk:");
      frm.Set<EMyFrameworkType::label>     ("lblDirectories", "Verzeichnisse:");
      frm.Set<EMyFrameworkType::label>     ("lblFiles",       "Dateien:");
      frm.Set<EMyFrameworkType::label>     ("lblFile",        "Datei:");

      frm.Set<EMyFrameworkType::edit>      ("edtPath",        "");
      frm.Set<EMyFrameworkType::edit>      ("edtFile",        "");
      frm.ReadOnly<EMyFrameworkType::edit> ("edtPath",        true);

      frm.Set<EMyFrameworkType::button>    ("btnOk",        "Übernehmen");
      frm.Set<EMyFrameworkType::button>    ("btnCancel",    "Abbruch");

      InitDrives(frm);
      ChangeDrives(frm);  // only for vcl really necessary
      msg_toggle = true;
      }
   catch(exception &ex) {
      cerr << strExceptInitForm << endl << ex.what() << endl;
      }
   }

/// Initialization for the drives. Only Windows know Letter as drives
void TFileDlgProcess::InitDrives(TMyForm& frm) {
   try {
      //ostream out(frm.GetAsStreamBuff<Narrow, EMyFrameworkType::combobox>("cbxDrives"));
      std::vector<std::string> vecDrives;
      for(char drive = 'A'; drive <= 'Z'; ++drive) {
         if (fs::path myPath = string{ drive, ':', '\0' }; fs::exists(myPath))
            vecDrives.push_back(myPath.string());
         }
      frm.InitCombobox("cbxDrives", vecDrives);
      frm.SetFirstComboBox("cbxDrives");
      }
   catch(exception &ex) {
      ;//cerr << strExceptReadDrive << endl << ex.what() << endl;
      }
   }

// ----------------------------------------------------------------------------
void TFileDlgProcess::ChangeDrives(TMyForm& frm) {
   if(auto strDrive = frm.Get<EMyFrameworkType::combobox, string>("cbxDrives"); strDrive) {
      *strDrive += "\\";
      frm.Set<EMyFrameworkType::edit>("edtPath", strDrive);
      ChangeDirectory(frm);
      }
   else {
      throw runtime_error(strChangeDrivesEmpty);
      }
   }

// ----------------------------------------------------------------------------
void TFileDlgProcess::ChangeDirectory(TMyForm& frm) {
   try {
      if (auto strDirectory = frm.Get<EMyFrameworkType::edit, string>("edtPath"); strDirectory) {
         fs::path myPath = *strDirectory;
         myPath = fs::canonical(myPath);
         frm.Set<EMyFrameworkType::edit>("edtPath", myPath.string());

         auto my_rel = [&myPath](fs::path const& p) {
            string ret = p.string().substr(p.string().rfind("\\") + 1, p.string().length());
            return ret;
            };

         vector<fs::path> files;
         copy(fs::directory_iterator(myPath), fs::directory_iterator(), back_inserter(files));

         auto it1 = partition(files.begin(), files.end(), [](auto const& p) { return fs::is_directory(p); });

         ostream out(frm.GetAsStreamBuff<Narrow, EMyFrameworkType::listbox>("lbDirectories"));

         sort(files.begin(), it1,
            [this](auto const& a, auto const& b) {
               return TMyTools::lower(a.filename().string()) < TMyTools::lower(b.filename().string());
            });
         vector<string>   vec;
         vec.reserve(distance(files.begin(), it1) + 1);

         if (myPath.filename().string() != "\\") vec.push_back("..");
         transform(files.begin(), it1, back_inserter(vec), my_rel);
         copy(vec.begin(), vec.end(), ostream_iterator<string>(out, "\n"));
         vec.clear();
         vec.reserve(distance(it1, files.end()) + 1);
         delete out.rdbuf(frm.GetAsStreamBuff<Narrow, EMyFrameworkType::listbox>("lbFiles"));
         transform(it1, files.end(), back_inserter(vec), my_rel);
         sort(vec.begin(), vec.end(), [this](auto const& a, auto const& b) {
            return TMyTools::lower(a) < TMyTools::lower(b); });
         if (auto strPattern = frm.Get<EMyFrameworkType::edit, string>("edtFile"); strPattern) {
            static string strMatcher = "*?";
            if (TMyTools::contain(*strPattern, strMatcher) == true) {
               //auto matcher = wildcards::make_matcher(*strPattern);
               //std::copy_if(vec.cbegin(), vec.cend(), ostream_iterator<string>(out, "\n"), [&](std::string const& pa) { return glob::match(pa, *strPattern); });
               std::copy_if(vec.cbegin(), vec.cend(), ostream_iterator<string>(out, "\n"), [&](std::string const& pa) { return TMyTools::wildcard_matching(pa, *strPattern); });
               //[matcher](auto pa) { return matcher.matches(pa); } );

            }
            else {
               copy(vec.begin(), vec.end(), ostream_iterator<string>(out, "\n"));
               std::string lower_p = TMyTools::lower(*strPattern);
               if (find_if(vec.begin(), vec.end(), [this, &lower_p](string const& file) {
                  return TMyTools::lower(file) == lower_p; }) != vec.end()) {
                  frm.SetListBox("lbFiles", *strPattern);
               }
            }
         }
         else {
            copy(vec.begin(), vec.end(), ostream_iterator<string>(out, "\n"));
         }
      }
      }
   catch (std::exception& ex) {
      ;//std::cerr << "Fehler beim Wechseln der Verzeichnisse" << std::endl << ex.what() << std::endl;
      }
   }


bool TFileDlgProcess::Execute(TMyForm& frm) {
   bool boRetVal = false;
   SplitPath(frm);
   if(auto strDirectory = frm.Get<EMyFrameworkType::edit, string>("edtPath"); strDirectory) {
      if(auto strFile = frm.Get<EMyFrameworkType::edit, string>("edtFile"); strFile) {
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
   if(auto strDir = frm.Get<EMyFrameworkType::listbox, string>("lbDirectories"); strDir) {
      if(auto strPath = frm.Get<EMyFrameworkType::edit, string>("edtPath"); strPath) {
         fs::path pa(*strPath);
         pa /= fs::path(*strDir);
         frm.Set<EMyFrameworkType::edit>("edtPath", pa.string());
         ChangeDirectory(frm);
         }
      else throw runtime_error(strPathFieldEmpty);
      }
   else throw runtime_error(strDirectoriesEmpty);
   }

void TFileDlgProcess::ChangeFiles(TMyForm& frm) {
   auto strFile = frm.Get<EMyFrameworkType::listbox, string>("lbFiles");
   frm.Set<EMyFrameworkType::edit>("edtFile", strFile);
   }


/// processing the chosen path and split it in the components
void TFileDlgProcess::SplitPath(TMyForm& frm) {
   msg_toggle = false;
   try {
      optional<string> strDirectory;
      optional<string> strDrive;
      optional<string> strFilename;
      optional<string> strDir;
      optional<string> strPath;

      if(auto theFile = frm.Get<EMyFrameworkType::edit, string>("edtFile"); theFile) {
         if(fs::path check = *theFile; check.root_name() != fs::path("")) {
            strFilename = frm.Get<EMyFrameworkType::edit, string>("edtFile");
            frm.Set<EMyFrameworkType::edit>("edtFile", "");
            frm.Set<EMyFrameworkType::edit>("edtPath", strDirectory);   /// !!!!! Fehler
            }
         else {
            strDirectory = frm.Get<EMyFrameworkType::edit, string>("edtPath");
            }
         }
      else {
         strDirectory = frm.Get<EMyFrameworkType::edit, string>("edtPath");
         }

      if(!strDirectory) throw runtime_error("path is empty or don't exist.");
      fs::path pa = *strDirectory;

      strDrive = make_optional(TMyTools::upper(pa.root_name().string()));
      if(fs::is_directory(pa)) {
         strDir      = make_optional(pa.filename().string());
         strPath     = make_optional(pa.parent_path().string());

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
   catch(exception &ex) {
      cerr << "error while splitting the path in function SplitPath" << endl
           << ex.what() << endl;
      }
   msg_toggle = true;
   }


void TFileDlgProcess::SetFileOrDirectory(TMyForm& frm, string const& strFile) {
   frm.Set<EMyFrameworkType::edit>("edtFile", strFile);
   SplitPath(frm);
   return;
   }

string TFileDlgProcess::GetFileOrDirectory(TMyForm& frm) {
   fs::path mypath;
   if(auto strDirectory = frm.Get<EMyFrameworkType::edit, string>("edtPath"); strDirectory) {
      mypath = *strDirectory;
      if(auto strFile = frm.Get<EMyFrameworkType::edit, string>("edtFile"); strFile) {
         mypath /= fs::path(*strFile);
         }
      }
   return mypath.string();
   }

