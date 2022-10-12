#ifndef MyFileDlgH
#define MyFileDlgH

#include <BuildFileDlg.h>

#include <MyForm.h>
#include <string>
#include <utility>
#include <optional>
#include <stdexcept>
#include <map>
#include <tuple>

class TFileDlgProcess;

class MyFileLibAPI TMyFileDlg {
   public:
      static std::pair<EMyRetResults, std::string> SelectWithFileDirDlg(std::optional<std::string> const& path, bool parDirOnly = false);
      static void OpenFileAction(std::string const& strFile);

      static void LoadFile(std::wostream& stream, std::string const& strFile);
      static size_t CheckFileSize(std::string const& strFile);
      static std::tuple<std::wifstream, const size_t> OpenInputFile(std::string const& strFile);
      static EMyRetResults Message(EMyMessageType paType, std::string const& paCaption, std::string const& paMessage);
      
      template<typename ty>
      static std::pair<EMyRetResults, ty> Input(ty value, std::string const& paCaption = "Eingabedialog", std::string const& paDescription = "Geben Sie einen neuen Wert ein:", std::string const& paRange = ""); 
   private:
      static void InitFileShowForm(TMyForm& frm, std::string const& strFile);
      static TMyForm CreateInputDlg(void);
      static TMyForm CreateShowFile();
      static TMyForm CreateFileDlg(TFileDlgProcess& proc);
      static TMyForm CreateDirectoryDlg(TFileDlgProcess& proc);

   };

//MyFileLibAPI TMyForm CreateInputDlg(void);


template<typename ty>
inline std::pair<EMyRetResults, ty> TMyFileDlg::Input(ty value, std::string const& paCaption, std::string const& paDescription, std::string const& paRange) {
  auto frm = CreateInputDlg();
   frm.SetCaption(paCaption);
   frm.Set<EMyFrameworkType::label>("lblDescription", paDescription);
   frm.Set<EMyFrameworkType::label>("lblRange",       paRange);
   frm.Set<EMyFrameworkType::button>("btnOk",     "Bestätigen");
   frm.Set<EMyFrameworkType::button>("btnCancel", "Abbruch");
   frm.Set<EMyFrameworkType::edit>("edtValue", value);

   if(auto ret = frm.ShowModal(); ret == EMyRetResults::ok) {
      auto val = frm.Get<EMyFrameworkType::edit, ty>("edtValue");
      if(!val) {
         return std::make_pair(EMyRetResults::error, ty());
         }
      else return std::make_pair(ret, *val);
      }
   else {
      return std::make_pair(ret, ty());
      }
   }



#endif