/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#include "GameEngine.hpp"
#include "CSVParser.hpp"
#include "InitGame.hpp"
#include "SceneManager.hpp"
#include "Scenes.hpp"
#include "ServiceLocator.hpp"
#include <fstream>
#include <iostream>

std::string Indie::GameEngine::findValueByName(std::vector<std::vector<std::string>> parsedData, const std::string &value) const
{
    auto volumeData = std::find_if(parsedData.begin(), parsedData.end(), [value](std::vector<std::string> const &ref) {
        if (ref.size() != 2)
            return false;
        if (ref.at(0) == value)
            return true;
        return false;
    });
    if (volumeData == parsedData.end())
        return "";
    return volumeData->at(1);
}

void Indie::GameEngine::readOptions()
{
    MusicManager &musicManager = ServiceLocator::getInstance().get<MusicManager>();
    SoundManager &soundManager = ServiceLocator::getInstance().get<SoundManager>();

    try {
        std::vector<std::vector<std::string>> parsedData
            = Indie::ServiceLocator::getInstance().get<CSVParser>().parse("../ressources/.saves/options.txt");

        if (parsedData.size() != 4)
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/options.txt\" corrupted.");
        const std::string &musicVolume = this->findValueByName(parsedData, "MUSIC_VOLUME");
        const std::string &muteMusic = this->findValueByName(parsedData, "MUSIC_MUTE");
        const std::string &soundVolume = this->findValueByName(parsedData, "SOUND_VOLUME");
        const std::string &muteSound = this->findValueByName(parsedData, "SOUND_MUTE");

        if (musicVolume == "" || muteMusic == "" || soundVolume == "" || muteSound == "")
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/options.txt\" corrupted.");
        if ((muteMusic != "true" && muteMusic != "false") || (muteSound != "true" && muteSound != "false"))
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/options.txt\" corrupted.");
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
        float musicVolumeValue = std::stof(musicVolume);
        float soundVolumeValue = std::stof(soundVolume);

        if (musicVolumeValue > 20 || musicVolumeValue < 0 || soundVolumeValue > 20 || soundVolumeValue < 0)
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/options.txt\" corrupted.");
        musicManager.setVolume(musicVolumeValue);
        soundManager.setVolume(soundVolumeValue);
    } catch (const std::exception &e) {
        musicManager.setVolume(10.f);
        musicManager.unMute();
        soundManager.setVolume(10.f);
        soundManager.setMute(false);
        std::cerr << e.what() << '\n';
    }
}

void Indie::GameEngine::setupMusicManager()
{
    ServiceLocator::getInstance().get<MusicManager>().addMusic("../ressources/musics/main_menu.wav"); // id 0
    ServiceLocator::getInstance().get<MusicManager>().addMusic("../ressources/musics/level_select.wav"); // id 1
    ServiceLocator::getInstance().get<MusicManager>().setMusic(0);
    ServiceLocator::getInstance().get<MusicManager>().playMusic();
    this->readOptions();
}

void Indie::GameEngine::setupSoundManager()
{
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/bad.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/bomb_drop.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/bomb_explode.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/die.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/level_up.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/menu_back.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/menu_lock.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/menu_move.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/menu_select.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/power_down.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/power_up.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/title_select.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/xp_up.wav");
}

void Indie::GameEngine::setupSceneManager(ContextManager &context)
{
    ServiceLocator::getInstance().get<SceneManager>().initLoading(&context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<SplashScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<MenuScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<TitleScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<MainMenuScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<GameScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<PauseScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<OptionsScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<IntroScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<SoloScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<EndScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<Multi1Scene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<Multi2Scene>(context);
    ServiceLocator::getInstance().get<SceneManager>().setScene<SplashScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().setSceneUpdateActive(true);
    ServiceLocator::getInstance().get<SceneManager>().setSceneRenderActive(true);
}

Indie::GameEngine::GameEngine()
    : context(ServiceLocator::getInstance().get<ContextManager>())
{
    loadImage = context.getDriver()->getTexture("../ressources/images/Loading.png");
}

Indie::GameEngine::~GameEngine()
{
    auto &musicManager = ServiceLocator::getInstance().get<MusicManager>();
    auto &soundManager = ServiceLocator::getInstance().get<SoundManager>();
    std::vector<std::vector<std::string>> dataToWrite;

    dataToWrite.push_back({ "MUSIC_VOLUME", std::to_string(musicManager.getMusicVolume()) });
    if (musicManager.isMusicMuted() == true) {
        dataToWrite.push_back({ "MUSIC_MUTE", "true" });
    } else {
        dataToWrite.push_back({ "MUSIC_MUTE", "false" });
    }
    dataToWrite.push_back({ "SOUND_VOLUME", std::to_string(soundManager.getVolume()) });
    if (soundManager.isMuted() == true) {
        dataToWrite.push_back({ "SOUND_MUTE", "true" });
    } else {
        dataToWrite.push_back({ "SOUND_MUTE", "false" });
    }
    try {
        ServiceLocator::getInstance().get<CSVParser>().writeToFile("../ressources/.saves/options.txt", dataToWrite);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    if (loadImage)
        context.getDriver()->removeTexture(loadImage);
}

void Indie::GameEngine::startGame()
{
    /* ================================================================================ */
    /* LOADING SCREEN */
    /* ================================================================================ */
    context.getDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
    context.displayImage(loadImage);
    context.getDriver()->endScene();
    ServiceLocator::getInstance().get<ImageLoader>();
    this->setupSoundManager();
    this->setupMusicManager();
    this->setupSceneManager(context);
    /* ================================================================================ */
    /* LOOP */
    /* ================================================================================ */
    this->context.getDevice()->setEventReceiver(&EventHandler::getInstance());
    this->context.getDevice()->getTimer()->stop();
    this->context.getDevice()->getTimer()->start();

    irr::u32 lastTime = this->context.getDevice()->getTimer()->getTime();
    irr::u32 currentTime = 0;
    irr::f32 deltaTime = 0;
    irr::f32 totalDeltaTime = 0;
    while (context.getDevice()->run()) {
        currentTime = this->context.getDevice()->getTimer()->getTime();
        deltaTime = (irr::f32)((currentTime - lastTime) / 1000.f);
        totalDeltaTime += deltaTime;
        // std::cout << "Delta time: " << deltaTime << ", FPS: " << this->context.getDriver()->getFPS() << std::endl;
        if (totalDeltaTime >= 0.016f) {
            ServiceLocator::getInstance().get<MusicManager>().update();
            ServiceLocator::getInstance().get<SoundManager>().update();
            ServiceLocator::getInstance().get<SceneManager>().update(context, totalDeltaTime);
            totalDeltaTime = 0.f;
        }
        lastTime = currentTime;
    }
}