//
// Created by kalo3 on 18-Aug-22.
//

#ifndef SIMPLE_EXAMPLE_FILEHANDLER_HPP
#define SIMPLE_EXAMPLE_FILEHANDLER_HPP

#include <string>
#include <vector>

namespace files {
    class fileHandler {
    public:
        static std::string getString(const std::string& filePath);
        static std::vector<std::string> getLines(const std::string& filePath);
        static void stringToFile(const std::string& data, const std::string& filePath);
        static void linesToFile(const std::vector<std::string>& data,const std::string& filePath);
    };
}

#endif //SIMPLE_EXAMPLE_FILEHANDLER_HPP
