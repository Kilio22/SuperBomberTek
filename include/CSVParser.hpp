/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CSVParser | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef CSVPARSER_HPP_
#define CSVPARSER_HPP_

#include <string>
#include <vector>

namespace Indie
{
    /**
     * @brief CSVParser class
     */
    class CSVParser
    {
    public:
        CSVParser() = default;
        ~CSVParser() = default;

        /**
         * @brief Reads values from given file which must be in CSV format and return the data parsed
         * @param filepath The filepath of the file to parse
         * @return std::vector<std::vector<std::string>> The parsed data
         */
        std::vector<std::vector<std::string>> parse(const std::string &filepath);

        /**
         * @brief Writes given data in a file located at given filepath
         * @param filepath File location
         * @param data Data to write
         */
        void writeToFile(const std::string &filepath, const std::vector<std::vector<std::string>> &data);

    private:
    };
} // namespace Indie

#endif /* !CSVPARSER_HPP_ */
