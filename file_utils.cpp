#ifndef FILE_UTILS_CPP
#define FILE_UTILS_CPP

#include "file_utils.h"

CustomVector<fs::path> list_files_recursive(const fs::path &dir) // Remove template
{
    CustomVector<fs::path> files;
    for (const auto &entry : fs::recursive_directory_iterator(dir))
    {
        if (entry.is_regular_file())
        {
            files.append(entry.path());
        }
    }
    return files;
}

#endif // FILE_UTILS_CPP
