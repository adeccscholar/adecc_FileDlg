//---------------------------------------------------------------------------

#ifndef FileUtilH
#define FileUtilH
//---------------------------------------------------------------------------
#include <BuildFileDlg.h>

#include <filesystem>
#include <vector>
#include <set>
#include <string>


namespace fs = std::filesystem;

using Dir_Stats_Type = std::tuple<unsigned long, unsigned long, unsigned long long>;

std::ostream& MyFileLibAPI operator << (std::ostream& out, Dir_Stats_Type const& val);
Dir_Stats_Type& MyFileLibAPI operator += (Dir_Stats_Type& sum, Dir_Stats_Type const& val);
Dir_Stats_Type& MyFileLibAPI operator += (Dir_Stats_Type& sum, std::uintmax_t const& size);
Dir_Stats_Type& MyFileLibAPI operator ++ (Dir_Stats_Type& sum);
Dir_Stats_Type MyFileLibAPI operator ++ (Dir_Stats_Type& sum, int);

std::uintmax_t Convert_Size_KiloByte(std::uintmax_t val);
bool Is_Hidden(fs::path const& dir);
Dir_Stats_Type MyFileLibAPI Count(fs::path const& dir, bool boWithSub = false);
size_t MyFileLibAPI Find(std::vector<fs::path>& ret, fs::path const& dir, std::set<std::string> const& extensions, bool boWithSub = false);


#endif

