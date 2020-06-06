/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Music
*/

#include "Music.hpp"
#include "Exceptions.h"

Indie::Music::Music(std::string filepath)
{
    std::string extension = filepath.substr(filepath.find_last_of("."));
    auto intro = std::make_unique<sf::Music>();
    auto loop = std::make_unique<sf::Music>();
    auto outro = std::make_unique<sf::Music>();

    filepath.resize(filepath.size() - extension.size());
    this->volume = 100;
    this->isMuted = false;
    this->isLooped = false;
    this->isPlaying = false;
    this->currentMusic = Status::Intro;
    if (!intro->openFromFile(filepath + "_intro" + extension))
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + filepath + "_intro" + extension + "\" not found.");
    if (!loop->openFromFile(filepath + "_loop" + extension))
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + filepath + "_loop" + extension + "\" not found.");
    if (!outro->openFromFile(filepath + "_outro" + extension))
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + filepath + "_outro" + extension + "\" not found.");
    musics.push_back(std::move(intro));
    musics.push_back(std::move(loop));
    musics.push_back(std::move(outro));
}

float Indie::Music::getVolume() const
{
    return volume;
}

void Indie::Music::loop()
{
    isLooped = true;
    musics[(int)Status::Loop]->setLoop(true);
}

void Indie::Music::unLoop()
{
    isLooped = false;
    musics[(int)Status::Loop]->setLoop(false);

}

void Indie::Music::setVolume(float _vol)
{
    volume = _vol;
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->setVolume(_vol);
}

void Indie::Music::mute()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->setVolume(0);
    isMuted = true;
}

void Indie::Music::unMute()
{
    setVolume(volume);
    isMuted = false;
}

void Indie::Music::playMusic()
{
    musics[(int)currentMusic]->play();
    isPlaying = true;
}

void Indie::Music::pauseMusic()
{
    musics[(int)currentMusic]->pause();
    isPlaying = false;
}

void Indie::Music::stopMusic()
{
    musics[(int)currentMusic]->stop();
    currentMusic = Status::Intro;
    isPlaying = false;
}

void Indie::Music::restartMusic()
{
    stopMusic();
    playMusic();
}

void Indie::Music::update()
{
    if (!isPlaying)
        return;
    if (musics[(int)currentMusic]->getStatus() == sf::SoundSource::Status::Stopped) {
        switch (currentMusic) {
        case Status::Intro:
            musics[(int)Status::Loop]->stop();
            musics[(int)Status::Loop]->play();
            currentMusic = Status::Loop;
            break;
        case Status::Loop:
            if (!isLooped) {
                musics[(int)Status::Outro]->stop();
                musics[(int)Status::Outro]->play();
                currentMusic = Status::Outro;
            } else {
                musics[(int)currentMusic]->play();
            }
            break;
        case Status::Outro:
            stopMusic();
            break;
        default:
            stopMusic();
            break;
        }
    }
}

Indie::Music::Status Indie::Music::getStatus()
{
    if (!isPlaying)
        return Music::Status::NotPlaying;
    return currentMusic;
}

void Indie::Music::setStatus(Indie::Music::Status status)
{
    if (status == Status::NotPlaying)
        return;
    restartMusic();
    if (status == Status::Loop) {
        musics[0]->stop();
        musics[2]->stop();
    }
    if (status == Status::Outro) {
        musics[0]->stop();
        musics[1]->stop();
    }
}