#ifndef MyFileDlgH
#define MyFileDlgH

#include <BuildFileDlg.h>

#include <MyFramework_String.h>
#include <MyForm.h>  
#include <string>
#include <utility>
#include <optional>
#include <stdexcept>
#include <map>
#include <tuple>
#include <filesystem>

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
      static TMyForm CreateShowFile();
      static TMyForm CreateFileDlg(TFileDlgProcess& proc);
      static TMyForm CreateDirectoryDlg(TFileDlgProcess& proc);

      static TMyForm CreateInputDlg(int = 0);
      static std::pair<EMyRetResults, fw_String> InputDlg(fw_String const& value, std::string const& paCaption, std::string const& paDescription, std::string const& paRange);
      static std::pair<EMyRetResults, std::filesystem::path> InputDlg(std::filesystem::path const& value, std::string const& paCaption, std::string const& paDescription, std::string const& paRange);

   };



template<typename ty>
inline std::pair<EMyRetResults, ty> TMyFileDlg::Input(ty value, std::string const& paCaption, std::string const& paDescription, std::string const& paRange) {
   EMyRetResults result;
   if constexpr (std::is_same <std::filesystem::path, ty>::value) {
      std::filesystem::path fsPath;
      if (std::tie(result, fsPath) = InputDlg(value, paCaption, paDescription, paRange); result == EMyRetResults::ok) {
         return std::make_pair(result, fsPath);
      }
      else {
         return std::make_pair(result, ty());
      }
   }

   else {
      fw_String strValue = TMy_FW_String::SetText(value);
      if (std::tie(result, strValue) = InputDlg(strValue, paCaption, paDescription, paRange); result == EMyRetResults::ok) {
         return std::make_pair(result, TMy_FW_String::GetText<ty>(strValue));
         }
      else {
         return std::make_pair(result, ty());
         }
      }
   }




#endif