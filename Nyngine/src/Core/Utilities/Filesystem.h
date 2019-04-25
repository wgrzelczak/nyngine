#pragma once

namespace ny::Utilities
{
    std::string ReadFileToString(const std::string& filename)
    {
        // no feedback is provided for stream errors / exceptions.

        std::ifstream file(filename);
        if (!file) return std::string();

        file.ignore(std::numeric_limits<std::streamsize>::max());
        auto size = file.gcount();

        file.clear();
        file.seekg(0, std::ios_base::beg);

        std::stringstream sstr;
        sstr << file.rdbuf();
        file.close();

        return sstr.str();
    }
} // namespace ny::Utilities