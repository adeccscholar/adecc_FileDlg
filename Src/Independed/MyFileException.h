#ifndef MyFileExceptionH
#define MyFileExceptionH

#include <MyStdTypes.h>

#include <string>
#include <stdexcept>
#include <map>
#include <utility>
#include <system_error>

class my_filedlg_exception : public std::exception {
private:
   std::string strSource;        ///< Ursprung des Fehlers
   std::string strMessage;       ///< eigentliche Fehlermeldung
   mutable std::string strWhat;  ///< Hilfsobjekt, um Lebensdauer von what() zu gewährleisten
   my_source_position thePosition;
public:
   my_filedlg_exception(std::string const& pSrc, std::string pMsg,
      std::string const& pFunc, std::string const& pFile, size_t pLine) : std::exception(),
      strSource(pSrc), strMessage(pMsg), thePosition(pFunc, pFile, pLine) { }

   my_filedlg_exception(std::string const& pSrc, std::string pMsg, my_source_position&& pPos) : std::exception(),
      strSource(pSrc), strMessage(pMsg), thePosition(std::forward<my_source_position>(pPos)) { }

   virtual const char* what() const noexcept;
};

class my_file_information {
protected:
   std::string strFile;          ///< Ursprung des Fehlers
   std::errc  error_code;
   static std::map<std::errc, std::pair<std::string, std::string>> errc_messages;
public:
   my_file_information(std::string const& pFile, std::errc code) : strFile(pFile), error_code(code) { }
   my_file_information(my_file_information const& ref) : strFile(ref.strFile), error_code(ref.error_code) { }
   std::string GetInformation() const;
};


class my_file_runtime_error : public std::runtime_error, public my_file_information {
private:
   mutable std::string strWhat;  ///< Hilfsobjekt, um Lebensdauer von what() zu gewährleisten
   my_source_position thePosition;
public:
   /*
   my_file_runtime_error(std::string const& pSrc, std::string pMsg,
      std::string const& pFunc, std::string const& pFile, size_t pLine) : std::runtime_error(pMsg),
      strFile(pSrc), thePosition(pFunc, pFile, pLine) { }

   my_file_runtime_error(std::string const& pSrc, std::string pMsg, my_source_position&& pPos) : std::runtime_error(pMsg),
      strFile(pSrc), thePosition(std::forward<my_source_position>(pPos)) { }
   */
   my_file_runtime_error(std::string const& pSrc, std::errc value, my_source_position&& pPos) : std::runtime_error(errc_messages[value].second),
      my_file_information(pSrc, value), thePosition(std::forward<my_source_position>(pPos)) { }

   my_file_runtime_error(my_file_information const& info, my_source_position&& pPos) 
          : std::runtime_error(info.GetInformation()), my_file_information(info), thePosition(std::forward<my_source_position>(pPos)) { }

   virtual const char* what() const noexcept;
};

#endif

