/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SaveManager | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "SaveManager.hpp"
#include "FileParser.hpp"
#include "MasterInfo.hpp"
#include "MusicManager.hpp"
#include "SceneManager.hpp"
#include "Scenes.h"
#include "ServiceLocator.hpp"
#include "SoundManager.hpp"
#include <filesystem>

Indie::SaveManager::SaveManager()
    : currentSave({})
    , currentSavePath("")
{
}

Indie::SaveManager::~SaveManager()
{
    this->saveCurrentSave();
}

void Indie::SaveManager::loadSave(const std::string &filepath)
{
    if (filepath == this->currentSavePath) {
        this->loadMusicParams();
        this->loadMasterInfos();
        this->loadKeybinds();
        return;
    }
    if (this->currentSave.size() != 0) {
        this->saveCurrentSave();
    }
    this->currentSave.clear();
    this->currentSavePath = filepath;
    try {
        this->currentSave = Indie::ServiceLocator::getInstance().get<FileParser>().parse(filepath);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        this->resetMasterInfos();
        this->resetVolume();
        this->resetKeybinds();
        return;
    }
    this->loadMusicParams();
    this->loadMasterInfos();
    this->loadKeybinds();
}

void Indie::SaveManager::loadMusicParams(void)
{
    MusicManager &musicManager = ServiceLocator::getInstance().get<MusicManager>();
    SoundManager &soundManager = ServiceLocator::getInstance().get<SoundManager>();

    try {
        const std::string &musicVolume = this->currentSave.at("MUSIC_VOLUME");
        const std::string &muteMusic = this->currentSave.at("MUSIC_MUTE");
        const std::string &soundVolume = this->currentSave.at("SOUND_VOLUME");
        const std::string &muteSound = this->currentSave.at("SOUND_MUTE");

        if (musicVolume == "" || muteMusic == "" || soundVolume == "" || muteSound == "")
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"" + this->currentSavePath + "\" corrupted1.");
        if ((muteMusic != "true" && muteMusic != "false") || (muteSound != "true" && muteSound != "false"))
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"" + this->currentSavePath + "\" corrupted1.");
        if (muteMusic == "true") {
            musicManager.mute();
        } else {
            musicManager.unMute();
        }
        if (muteSound == "true") {
            soundManager.setMute(true);
        } else {
            soundManager.setMute(false);
        }
        int musicVolumeValue = std::stoi(musicVolume);
        int soundVolumeValue = std::stoi(soundVolume);

        if (musicVolumeValue > 20 || musicVolumeValue < 0 || soundVolumeValue > 20 || soundVolumeValue < 0)
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"" + this->currentSavePath + "\" corrupted1.");
        musicManager.setVolume(musicVolumeValue);
        soundManager.setVolume(soundVolumeValue);
    } catch (const std::exception &e) {
        this->resetVolume();
        std::cerr << e.what() << std::endl;
        std::cerr << "Reseting options..." << std::endl;
    }
}

void Indie::SaveManager::loadMasterInfos(void)
{
    std::unordered_map<std::string, std::string> mapsData;
    MasterInfo info;

    for (const auto &mapPath : SoloScene::mapPaths) {
        const auto &it
            = std::find_if(this->currentSave.begin(), this->currentSave.end(), [mapPath](const auto &ref) { return ref.first == mapPath.first; });

        if (it != this->currentSave.end()) {
            mapsData.insert({ it->first, it->second });
        }
    }
    try {
        const std::string &lvlData = this->currentSave.at("LVL");
        const std::string &xpData = this->currentSave.at("XP");
        int lvlValue = std::stoi(lvlData);
        int xpValue = std::stoi(xpData);

        if (xpValue < 0 || lvlValue < 0)
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"" + this->currentSavePath + "\" corrupted2.");
        info.lvl = lvlValue;
        info.xp = xpValue;
        for (auto data : mapsData) {
            std::string mapName = data.first;
            int highScore = std::stoi(data.second);

            if (highScore < 0)
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"" + this->currentSavePath + "\" corrupted.");
            info.scores_map.insert(std::pair<std::string, int>(mapName, highScore));
        }
        ServiceLocator::getInstance().get<SceneManager>().getScene<MenuScene>()->setMasterInfo(info);
    } catch (const std::exception &e) {
        this->resetMasterInfos();
        std::cerr << e.what() << std::endl;
        std::cerr << "Reseting game informations..." << std::endl;
    }
}

void Indie::SaveManager::loadKeybinds(void)
{
    std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>> keybinds = {};
    auto &contextManager = ServiceLocator::getInstance().get<ContextManager>();
    auto soloScene = ServiceLocator::getInstance().get<SceneManager>().getScene<SoloScene>();

    try {
        std::unordered_map<std::string, std::string> keybindsData = {};

        for (int keytype = (int)Indie::Components::KEY_TYPE::LEFT; keytype < (int)Indie::Components::KEY_TYPE::NONE; keytype++) {
            const auto &value = this->currentSave.at(std::to_string(keytype));

            keybindsData.insert({ std::to_string(keytype), value });
        }
        for (auto datas : keybindsData) {
            int keyType = std::stoi(datas.first);
            int keyNb = std::stoi(datas.second);

            if (keyType >= (int)Indie::Components::KEY_TYPE::NONE || keyType < (int)Indie::Components::KEY_TYPE::LEFT)
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"" + this->currentSavePath + "\" corrupted.");
            if (std::find_if(Keybind::keyCodes.begin(), Keybind::keyCodes.end(), [keyNb](const auto &var) { return ((int)var.first == keyNb); })
                == Keybind::keyCodes.end())
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"" + this->currentSavePath + "\" corrupted.");
            if (std::find_if(keybinds.begin(), keybinds.end(),
                    [keyType, keyNb](const auto &value) {
                        if (value.first == (Indie::Components::KEY_TYPE)keyType || value.second->getKey() == (irr::EKEY_CODE)keyNb)
                            return true;
                        return false;
                    })
                != keybinds.end())
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"" + this->currentSavePath + "\" corrupted.");
            keybinds.push_back({ (Indie::Components::KEY_TYPE)keyType, std::make_unique<Keybind>(contextManager, (irr::EKEY_CODE)keyNb) });
            soloScene->setKeybinds(keybinds);
        }
    } catch (const std::exception &e) {
        soloScene->resetKeybinds();
        std::cerr << e.what() << std::endl;
        std::cerr << "Reseting keybinds..." << std::endl;
    }
}

void Indie::SaveManager::saveCurrentSave(void)
{
    if (this->currentSavePath == "") {
        return;
    }
    this->saveMusicParams();
    this->saveMasterInfos();
    this->saveKeybinds();
    try {
        Indie::ServiceLocator::getInstance().get<FileParser>().writeToFile(this->currentSavePath, this->currentSave);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Can't save game" << std::endl;
    }
}

void Indie::SaveManager::saveMusicParams(void)
{
    auto &musicManager = ServiceLocator::getInstance().get<MusicManager>();
    auto &soundManager = ServiceLocator::getInstance().get<SoundManager>();

    this->saveValue({ "MUSIC_VOLUME", std::to_string(musicManager.getMusicVolume()) });
    if (musicManager.isMusicMuted() == true) {
        this->saveValue({ "MUSIC_MUTE", "true" });
    } else {
        this->saveValue({ "MUSIC_MUTE", "false" });
    }
    this->saveValue({ "SOUND_VOLUME", std::to_string(soundManager.getVolume()) });
    if (soundManager.isMuted() == true) {
        this->saveValue({ "SOUND_MUTE", "true" });
    } else {
        this->saveValue({ "SOUND_MUTE", "false" });
    }
}

void Indie::SaveManager::saveMasterInfos(void)
{
    const MasterInfo &info = ServiceLocator::getInstance().get<SceneManager>().getScene<MenuScene>()->getMasterInfo();

    this->saveValue({ "LVL", std::to_string((int)info.lvl) });
    this->saveValue({ "XP", std::to_string((int)info.xp) });
    for (auto highScoreMap : info.scores_map)
        this->saveValue({ highScoreMap.first, std::to_string((int)highScoreMap.second) });
}

void Indie::SaveManager::setCurrentSave(const std::unordered_map<std::string, std::string> &newSave)
{
    this->currentSave = newSave;
}

std::unordered_map<std::string, std::string> &Indie::SaveManager::getCurrentSave(void)
{
    return this->currentSave;
}

void Indie::SaveManager::saveValue(const std::pair<std::string, std::string> &value)
{
    if (std::find_if(this->currentSave.begin(), this->currentSave.end(), [value](const auto &ref) { return ref.first == value.first; })
        != this->currentSave.end()) {
        this->currentSave[value.first] = value.second;
    } else {
        this->currentSave.insert(value);
    }
}

void Indie::SaveManager::saveKeybinds(void)
{
    auto soloScene = ServiceLocator::getInstance().get<SceneManager>().getScene<SoloScene>();
    const std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>> &keybinds = soloScene->getKeybinds();

    for (auto &keybind : keybinds) {
        this->saveValue({ std::to_string((int)keybind.first), std::to_string((int)keybind.second->getKey()) });
    }
}

void Indie::SaveManager::resetVolume(void)
{
    MusicManager &musicManager = ServiceLocator::getInstance().get<MusicManager>();
    SoundManager &soundManager = ServiceLocator::getInstance().get<SoundManager>();

    musicManager.setVolume(10);
    musicManager.unMute();
    soundManager.setVolume(10);
    soundManager.setMute(false);
}

void Indie::SaveManager::resetMasterInfos(void)
{
    MasterInfo info = { 0, 0, {} };

    ServiceLocator::getInstance().get<SceneManager>().getScene<MenuScene>()->setMasterInfo(info);
}

void Indie::SaveManager::resetKeybinds(void)
{
    ServiceLocator::getInstance().get<SceneManager>().getScene<SoloScene>()->resetKeybinds();
}

template <typename TP>
time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
              + system_clock::now());
    return system_clock::to_time_t(sctp);
}

std::vector<std::pair<std::string, time_t>> Indie::SaveManager::getSavedGame(void)
{
    std::vector<std::pair<std::string, time_t>> nameSaves;

    for (const auto &entry : std::filesystem::directory_iterator("../ressources/.saves/")) {
        if (entry.is_regular_file() == true && entry.path().extension() == ".supersave") {
            auto timeEntry = entry.last_write_time();
            time_t cftime = to_time_t(timeEntry);
            nameSaves.push_back({ServiceLocator::getInstance().get<SceneManager>().getScene<Indie::SoloScene>()->getFileName(entry.path().u8string()), cftime});
        }
    }
    return nameSaves;
}

