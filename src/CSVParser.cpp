/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CSVParser | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "CSVParser.hpp"
#include "FileNotFoundException.hpp"
#include <fstream>
#include <sstream>

std::vector<std::vector<std::string>> Indie::CSVParser::parse(const std::string &filepath)
{
    std::ifstream ifs(filepath);
    std::string line;
    std::string value;
    std::vector<std::vector<std::string>> data;

    if (ifs.is_open() == false) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "File \"" + filepath + "\" not found.");
    }
    while (std::getline(ifs, line)) {
        std::istringstream ss(line);
        std::vector<std::string> values;

        while (std::getline(ss, value, ',')) {
            if (value.size() != 0)
                values.push_back(value);
        }
        data.push_back(values);
    }
    return data;
}

void Indie::CSVParser::writeToFile(const std::string &filepath, const std::vector<std::vector<std::string>> &data)
{
    std::ofstream ofs(filepath);

    if (ofs.is_open() == false) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "File \"" + filepath + "\" not found.");
    }
    for (auto values : data) {
        std::ostringstream oss;

        for (auto value : values) {
            oss << value << ",";
        }
        std::string finalString = oss.str();

        ofs << finalString.substr(0, finalString.size() - 1) << std::endl; // to delete useless ',' at the end of the string
    }
    ofs.close();
}

