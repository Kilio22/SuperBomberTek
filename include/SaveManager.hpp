/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SaveManager | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef SAVEMANAGER_HPP_
#define SAVEMANAGER_HPP_

#include <string>
#include <unordered_map>
#include <chrono>

namespace Indie
{
    class SaveManager
    {
    public:
        SaveManager();
        ~SaveManager();

        void loadSave(const std::string &filepath);
        void saveCurrentSave(void);
        void setCurrentSave(const std::unordered_map<std::string, std::string> &newSave);
        void saveValue(const std::pair<std::string, std::string> &value);
        std::unordered_map<std::string, time_t> getSavedGame(void);

    private:
        void loadMusicParams(void);
        void loadMasterInfos(void);
        void loadKeybinds(void);
        void saveMusicParams(void);
        void saveMasterInfos(void);
        void saveKeybinds(void);

        void resetVolume(void);
        void resetMasterInfos(void);
        void resetKeybinds(void);

        std::unordered_map<std::string, std::string> currentSave;
        std::string currentSavePath;
    };
} // namespace Indie

#endif /* !SAVEMANAGER_HPP_ */
