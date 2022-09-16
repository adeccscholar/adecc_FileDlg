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

#include <fstream>
#include <locale>
#include <filesystem>
#include <system_error>


namespace fs = std::filesystem;


std::map<std::errc, std::pair<std::string, std::string>> my_file_runtime_error::errc_messages = {
      { std::errc::address_family_not_supported,       { "EAFNOSUPPORT"s,    "address family not supported"s } },
      { std::errc::address_in_use,                     { "EADDRINUSE"s,      "address in use"s } },
      { std::errc::address_not_available,              { "EADDRNOTAVAIL"s,   "address not available"s } },
      { std::errc::already_connected,                  { "EISCONN"s,         "already connected"s } },
      { std::errc::argument_list_too_long,             { "E2BIG"s,           "argument list too long"s } },
      { std::errc::argument_out_of_domain,             { "EDOM"s,            "argument out of domain"s } },
      { std::errc::bad_address,                        { "EFAULT"s,          "bad address"s } },
      { std::errc::bad_file_descriptor,                { "EBADF"s,           "bad file descriptor"s } },
      { std::errc::bad_message,                        { "EBADMSG"s,         "bad message"s } },
      { std::errc::broken_pipe,                        { "EPIPE"s,           "broken pipe"s } },
      { std::errc::connection_aborted,                 { "ECONNABORTED"s,    "connection aborted"s } },
      { std::errc::connection_already_in_progress,     { "EALREADY"s,        "connection already in progress"s } },
      { std::errc::connection_refused,                 { "ECONNREFUSED"s,    "connection refused"s } },
      { std::errc::connection_reset,                   { "ECONNRESET"s,      "connection reset"s } },
      { std::errc::cross_device_link,                  { "EXDEV"s,           "cross device link"s } },
      { std::errc::destination_address_required,       { "EDESTADDRREQ"s,    "destination address required"s } },
      { std::errc::device_or_resource_busy,            { "EBUSY"s,           "device or resource busy"s } },
      { std::errc::directory_not_empty,                { "ENOTEMPTY"s,       "directory not empty"s } },
      { std::errc::executable_format_error,            { "ENOEXEC"s,         "executable format error"s } },
      { std::errc::file_exists,                        { "EEXIST"s,          "file exists"s } },
      { std::errc::file_too_large,                     { "EFBIG"s,           "file too large"s } },
      { std::errc::filename_too_long,                  { "ENAMETOOLONG"s,    "filename too long"s } },
      { std::errc::function_not_supported,             { "ENOSYS"s,          "function not supported"s } },
      { std::errc::host_unreachable,                   { "EHOSTUNREACH"s,    "host unreachable"s } },
      { std::errc::identifier_removed,                 { "EIDRM"s,           "identifier removed"s } },
      { std::errc::illegal_byte_sequence,              { "EILSEQ"s,          "illegal byte sequence"s } },
      { std::errc::inappropriate_io_control_operation, { "ENOTTY"s,          "inappropriate io control operation"s } },
      { std::errc::interrupted,                        { "EINTR"s,           "interrupted"s } },
      { std::errc::invalid_argument,                   { "EINVAL"s,          "invalid argument"s } },
      { std::errc::invalid_seek,                       { "ESPIPE"s,          "invalid seek"s } },
      { std::errc::io_error,                           { "EIO"s,             "io error"s } },
      { std::errc::is_a_directory,                     { "EISDIR"s,          "is a directory"s } },
      { std::errc::message_size,                       { "EMSGSIZE"s,        "message size"s } },
      { std::errc::network_down,                       { "ENETDOWN"s,        "network down"s } },
      { std::errc::network_reset,                      { "ENETRESET"s,       "network reset"s } },
      { std::errc::network_unreachable,                { "ENETUNREACH"s,     "network unreachable"s } },
      { std::errc::no_buffer_space,                    { "ENOBUFS"s,         "nobufferspace"s } },
      { std::errc::no_child_process,                   { "ECHILD"s,          "no child process"s } },
      { std::errc::no_link,                            { "ENOLINK"s,         "no link"s } },
      { std::errc::no_lock_available,                  { "ENOLCK"s,          "no lock available"s } },
      { std::errc::no_message_available,               { "ENODATA"s,         "no message available"s } },
      { std::errc::no_message,                         { "ENOMSG"s,          "no message"s } },
      { std::errc::no_protocol_option,                 { "ENOPROTOOPT"s,     "no protocol option"s } },
      { std::errc::no_space_on_device,                 { "ENOSPC"s,          "no space on device"s } },
      { std::errc::no_stream_resources,                { "ENOSR"s,           "no stream_resources"s } },
      { std::errc::no_such_device_or_address,          { "ENXIO"s,           "no suc device or address"s } },
      { std::errc::no_such_device,                     { "ENODEV"s,          "no such device"s } },
      { std::errc::no_such_file_or_directory,          { "ENOENT"s,          "no such file or directory"s } },
      { std::errc::no_such_process,                    { "ESRCH"s,           "no such process"s } },
      { std::errc::not_a_directory,                    { "ENOTDIR"s,         "not a directory"s } },
      { std::errc::not_a_socket,                       { "ENOTSOCK"s,        "not a socket"s } },
      { std::errc::not_a_stream,                       { "ENOSTR"s,          "not a stream"s } },
      { std::errc::not_connected,                      { "ENOTCONN"s,        "not connected"s } },
      { std::errc::not_enough_memory,                  { "ENOMEM"s,          "not enough memory"s } },
      { std::errc::not_supported,                      { "ENOTSUP"s,         "not supported"s } },
      { std::errc::operation_canceled,                 { "ECANCELED"s,       "operation canceled"s } },
      { std::errc::operation_in_progress,              { "EINPROGRESS"s,     "operation in progress"s } },
      { std::errc::operation_not_permitted,            { "EPERM"s,           "operation not permitted"s } },
      { std::errc::operation_not_supported,            { "EOPNOTSUPP"s,      "operation not supported"s } },
      { std::errc::operation_would_block,              { "EWOULDBLOCK"s,     "operation would block"s } },
      { std::errc::owner_dead,                         { "EOWNERDEAD"s,      "owner dead"s } },
      { std::errc::permission_denied,                  { "EACCES"s,          "permission denied"s } },
      { std::errc::protocol_error,                     { "EPROTO"s,          "protocol error"s } },
      { std::errc::protocol_not_supported,             { "EPROTONOSUPPORT"s, "protocol not supported"s } },
      { std::errc::read_only_file_system,              { "EROFS"s,           "read only file system"s } },
      { std::errc::resource_deadlock_would_occur,      { "EDEADLK"s,         "resource deadlock would occur"s } },
      { std::errc::resource_unavailable_try_again,     { "EAGAIN"s,          "resource unavailable try again"s } },
      { std::errc::result_out_of_range,                { "ERANGE"s,          "result out of range"s } },
      { std::errc::state_not_recoverable,              { "ENOTRECOVERABLE"s, "state not recoverable"s } },
      { std::errc::stream_timeout,                     { "ETIME"s,           "stream timeout"s } },
      { std::errc::text_file_busy,                     { "ETXTBSY"s,         "text file busy"s } },
      { std::errc::timed_out,                          { "ETIMEDOUT"s,       "timed out"s } },
      { std::errc::too_many_files_open_in_system,      { "ENFILE"s,          "too many files open in system"s } },
      { std::errc::too_many_files_open,                { "EMFILE"s,          "too many files open"s } },
      { std::errc::too_many_links,                     { "EMLINK"s,          "too many links"s } },
      { std::errc::too_many_symbolic_link_levels,      { "ELOOP"s,           "too many symbolic link levels"s } },
      { std::errc::value_too_large,                    { "EOVERFLOW"s,       "value too large"s } },
      { std::errc::wrong_protocol_type,                { "EPROTOTYPE"s,      "wrong protocol type"s } } 
   };



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

void TMyFileDlg::LoadFile(std::wostream& stream, std::string const& strFile) {
   std::wifstream ifs;
   ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
   //ifs.exceptions(std::ifstream::badbit);
   try {
      std::locale loc(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10FFFF, std::consume_header>);
      ifs.imbue(loc);
      ifs.open(strFile);
      if(!ifs.is_open()) throw std::system_error(errno, std::generic_category(), strFile);  // if std::ifstream::failbit isn't set
      const auto iSize = fs::file_size(strFile);
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
   catch (std::exception const& ex) {
      throw my_file_runtime_error(strFile, ex.what(), MY_POSITION());
      }
   }

const char* my_file_runtime_error::what() const noexcept {
   std::ostringstream os;
   os << "Error accessing the file \"" << strFile << "\":\n"
      << std::runtime_error::what() << "\n\n" << thePosition;
   strWhat = os.str();
   return strWhat.c_str();
}
