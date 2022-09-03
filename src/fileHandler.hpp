#ifndef SIMPLE_EXAMPLE_FILEHANDLER_HPP
#define SIMPLE_EXAMPLE_FILEHANDLER_HPP

#include <string>
#include <vector>

namespace files {
    class fileHandler {
    public:
        /**
         * @param filePath local path to the file.
         * @param err optional. whether an error occurred. -1 if an error occurred, 0 otherwise.
         * @return contents of the file in filePath.
         */
        static std::string getString(const std::string& filePath,int* err=nullptr);
        /**
         *
         * @param filePath local path to the file.
         * @param err optional. whether an error occurred. -1 if an error occurred, 0 otherwise.
         * @return lines of the file in filePath.
         */
        static std::vector<std::string> getLines(const std::string& filePath,int* err=nullptr);
        /**
         * writes the data string into a file located in the given file path.
         * @param data string to write into a file.
         * @param filePath local path to the file.
         * @param err optional. whether an error occurred. -1 if an error occurred, 0 otherwise.
         */
        static void stringToFile(const std::string& data, const std::string& filePath,int* err=nullptr);
        /**
         * writes the data lines into a file located in the given file path.
         * @param data lines to write into a file.
         * @param filePath local path to the file.
         * @param err optional. whether an error occurred. -1 if an error occurred, 0 otherwise.
         */
        static void linesToFile(const std::vector<std::string>& data,const std::string& filePath,int* err=nullptr);
        /**
         * converts the string into a vector of lines.
         * @param data string to convert into line vector.
         * @param separator '\\n' by default. a char that indicates where lines end.
         * @return vector of lines given by the string.
         */
        static std::vector<std::string>stringToLines(const std::string& data,char separator='\n');
        /**
         * @param lines vector of lines
         * @return string representation of all the lines combined. seperates lines with '\\n'.
         */
        static std::string linesToString(const std::vector<std::string>& lines);
        /**
         * @param path local path to a file.
         * @return whether the file in the path can be read from and writen to.
         */
        static bool validPath(const std::string& path);
    };
}

#endif //SIMPLE_EXAMPLE_FILEHANDLER_HPP
