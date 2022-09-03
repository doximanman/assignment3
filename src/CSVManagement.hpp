#ifndef ASSIGNMENT1_CSVMANAGEMENT_HPP
#define ASSIGNMENT1_CSVMANAGEMENT_HPP

#include "Distance/Distance.hpp"
#include <vector>
#include <map>

namespace CSV {
    class CSVManagement {
    private:
        /**
         * @param points the lines of the csv file.
         * @return a vector with the data given as a vector of the lines of a CSV file.
         */
        static std::vector<std::vector<std::string>> createDataVector(const std::vector<std::string>& lines);

    public:

        /**
         * @param lines lines of a csv file.
         * @return a map between the type and the set of points that belong to the type.
         */
        static std::map<std::string,std::vector<Geometry::Point>> getClassifiedData(const std::vector<std::string>& lines);

        /**
         * get unclassified vector of points from lines of a csv file.
         * @return
         */
        static std::vector<Geometry::Point> getUnclassifiedData(const std::vector<std::string>& lines);

    };
}
#endif //ASSIGNMENT1_CSVMANAGEMENT_HPP

