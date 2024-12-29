#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <filesystem>
#include "dataStructs/CustomVector.h"

namespace fs = std::filesystem;

CustomVector<fs::path> list_files_recursive(const fs::path &dir);

#endif // FILE_UTILS_H
