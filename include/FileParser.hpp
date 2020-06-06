/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FileParser | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef CSVPARSER_HPP_
#define CSVPARSER_HPP_

#include <string>
#include <vector>
#include <unordered_map>

namespace Indie
{
    /**
     * @brief FileParser class
     */
    class FileParser
    {
    public:
        FileParser() = default;
        ~FileParser() = default;

        /**
         * @brief Reads values from given file which must be in CSV format and return the data parsed
         * @param filepath The filepath of the file to parse
         * @return std::vector<std::vector<std::string>> The parsed data
         */
        std::unordered_map<std::string, std::string> parse(const std::string &filepath, size_t nbValues = 2) const;

        /**
         * @brief Writes given data in a file located at given filepath
         * @param filepath File location
         * @param data Data to write
         */
        void writeToFile(const std::string &filepath, const std::unordered_map<std::string, std::string> &data) const;

    private:
    };
} // namespace Indie

#endif /* !CSVPARSER_HPP_ */
