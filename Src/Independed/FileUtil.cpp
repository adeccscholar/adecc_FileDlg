//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileUtil.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <functional>
//---------------------------------------------------------------------------


// !!!
const int bits_in_byte = 8;
const int bytes_in_kilobyte = 1024;

std::uintmax_t Convert_Size_KiloByte(std::uintmax_t val) {
   return val / bytes_in_kilobyte + 1;
   }


std::ostream& operator << (std::ostream& out, Dir_Stats_Type const& val) {
   return out
       << std::left << std::setw(15) << "files:"       << std::right << std::setw(20) << std::get<0>(val) << std::endl
       << std::left << std::setw(15) << "directories:" << std::right << std::setw(20) << std::get<1>(val) << std::endl
       << std::left << std::setw(15) << "size:"        << std::right << std::setw(20) << std::get<2>(val);
   }

Dir_Stats_Type& operator += (Dir_Stats_Type& sum, Dir_Stats_Type const& val) {
   std::get<0>(sum) += std::get<0>(val);
   std::get<1>(sum) += std::get<1>(val);
   std::get<2>(sum) += std::get<2>(val);
   return sum;
   }

Dir_Stats_Type& operator += (Dir_Stats_Type& sum, std::uintmax_t const& size) {
   ++std::get<0>(sum);
   std::get<2>(sum) += size;
   return sum;
   }

Dir_Stats_Type& operator ++ (Dir_Stats_Type& sum) {
   ++std::get<1>(sum);
   return sum;
   }


Dir_Stats_Type operator ++ (Dir_Stats_Type& sum, int) {
   Dir_Stats_Type ret { sum };
   ++std::get<1>(sum);
   return ret;
   }




//----------------------------------------------------------------------------
bool Is_Hidden(fs::path const& dir) {
    std::set<fs::path> hidden = { "__history", "__astcache", "__recovery",
                                  ".git", ".svn", ".vs", "win32", "win64"  };
    static auto to_lower_string = [](fs::path const& p) {
                                std::string ret = p.filename().string();
                                std::transform(ret.begin(), ret.end(), ret.begin(), [](auto c) {
                                        return std::tolower(c);
                                        });
                                return ret;
                                };
    if(!fs::is_directory(dir)) return false;
    return hidden.find(to_lower_string(dir)) != hidden.end();
   }



Dir_Stats_Type Count(fs::path const& dir, bool boWithSub) {
   auto ret = Dir_Stats_Type { 0ul, 0ul, 0ull  };
   std::vector<fs::path> content;
   if(Is_Hidden(dir)) return ret;
   std::copy(fs::directory_iterator(dir), fs::directory_iterator(), std::back_inserter(content));
   auto it = std::partition(content.begin(), content.end(), [](auto const& val) { return fs::is_directory(val); });
   if(boWithSub) std::for_each(content.begin(), it, [&ret](auto const& val) { ++ret += Count(val, true); });
   else std::get<1>(ret) += std::distance(content.begin(), it);
   std::for_each(it, content.end(), [&ret](auto const& val) { ret += fs::file_size(val); });
   return ret;
   }



size_t Find(std::vector<fs::path>& ret, fs::path const& dir, std::set<std::string> const& extensions, bool boWithSub) {
   static auto constexpr check_func = [](fs::path const& p) { return !fs::is_directory(p); };
   auto check_func2          = [&extensions](fs::path const& p) {
                                             return extensions.find(p.extension().string()) != extensions.end();
                                             };
   auto collect_func = [&ret](fs::path const& p) mutable { ret.emplace_back(p.string()); };
   auto call_func = std::bind(Find, std::ref(ret), std::placeholders::_1, std::cref(extensions), boWithSub);

   if(Is_Hidden(dir)) return 0u;
   try {
      std::vector<fs::path> files;
      std::copy(fs::directory_iterator(dir), fs::directory_iterator(), std::back_inserter(files));
      auto it  = std::partition(files.begin(), files.end(), check_func);
      auto it2 = std::partition(files.begin(), it, check_func2);
      std::copy(files.begin(), it2, std::back_inserter(ret));
      if(boWithSub && it != files.end()) {
         std::for_each(it, files.end(), call_func);
         }
      }
   catch(std::exception& ex) {
      std::cerr << "error: " << ex.what() << std::endl;
      }
   return ret.size();
   }


size_t CheckFileSize(fs::path const& strFile) {
   size_t ret = 0u;
   try {
      std::ifstream ifs(strFile.string());
      if( !ifs.is_open()) {
         std::ostringstream os;
         os << "error while opening file \"" << strFile.string() << "\".";
         throw std::runtime_error(os.str().c_str());
         }
      const auto iSize = fs::file_size(strFile);
      std::string strBuff(iSize, '\0');
      ifs.read(strBuff.data(), iSize);
      ifs.close();
      std::string_view test(strBuff.data(), strBuff.size());
      ret = std::count(test.begin(), test.end(), '\n');
      }
   catch(std::exception & ex) {
      std::cerr << "error in " << __func__ << ": " << ex.what() << std::endl;
      }
   return ret;
   }






