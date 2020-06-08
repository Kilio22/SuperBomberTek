/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FileParser | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "FileParser.hpp"
#include "FileCorruptedException.hpp"
#include "FileNotFoundException.hpp"
#include <fstream>
#include <sstream>

std::unordered_map<std::string, std::string> Indie::FileParser::parse(const std::string &filepath, size_t nbValues) const
{
    std::ifstream ifs(filepath);
    std::string line;
    std::string value;
    std::unordered_map<std::string, std::string> data;

    if (ifs.is_open() == false) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "File \"" + filepath + "\" not found.");
    }
    while (std::getline(ifs, line)) {
        std::istringstream ss(line);
        std::vector<std::string> values;

        while (std::getline(ss, value, '=')) {
            if (value.size() != 0)
                values.push_back(value);
        }
        if (values.size() != nbValues)
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"" + filepath + "\" corrupted.");
        if (values.size() != 0) {
            if (data.find(values.at(0)) != data.end()) {
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"" + filepath + "\" corrupted.");
            }
            if (values.size() == 1)
                data.insert({ values.at(0), "" });
            else
                data.insert({ values.at(0), values.at(1) });
        }
    }
    ifs.close();
    return data;
}

void Indie::FileParser::writeToFile(const std::string &filepath, const std::unordered_map<std::string, std::string> &data) const
{
    std::ofstream ofs(filepath);

    if (ofs.is_open() == false) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"" + filepath + "\".");
    }
    for (auto values : data) {
        std::ostringstream oss;

        oss << values.first << "=" << values.second;
        std::string finalString = oss.str();

        ofs << finalString << std::endl;
    }
    ofs.close();
}
