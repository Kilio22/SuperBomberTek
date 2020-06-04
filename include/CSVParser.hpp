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
    class CSVParser
    {
    public:
        CSVParser() = default;
        ~CSVParser() = default;

        std::vector<std::vector<std::string>> parse(const std::string &filepath);
        void writeToFile(const std::string &filepath, const std::vector<std::vector<std::string>> &data);

    private:
    };
} // namespace Indie

#endif /* !CSVPARSER_HPP_ */
