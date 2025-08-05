#pragma once

#include <filesystem>
//#include <iostream>

#define GET_STRING(x) #x
#define GET_DIR(x) GET_STRING(x)

namespace fs = std::filesystem;

namespace gl3
{
    inline fs::path resolveAssetPath(const fs::path &relativeAssetPath)
    {
        auto mergedPath = (GET_DIR(ASSET_ROOT) / relativeAssetPath).make_preferred();
        return fs::canonical(mergedPath);
    }
}
