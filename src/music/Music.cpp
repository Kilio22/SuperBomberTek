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
    this->currentMusic = CHUNKS::Intro;
    if (!intro->openFromFile(filepath + "_intro" + extension))
        throw Indie::Exceptions::FileNotFoundException(__PRETTY_FUNCTION__, "File \"" + filepath + "intro" + extension + "\" not found.");
    if (!loop->openFromFile(filepath + "_loop" + extension))
        throw Indie::Exceptions::FileNotFoundException(__PRETTY_FUNCTION__, "File \"" + filepath + "loop" + extension + "\" not found.");
    if (!outro->openFromFile(filepath + "_outro" + extension))
        throw Indie::Exceptions::FileNotFoundException(__PRETTY_FUNCTION__, "File \"" + filepath + "outro" + extension + "\" not found.");
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
}

void Indie::Music::unLoop()
{
    isLooped = false;
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
    pauseMusic();
    musics[(int)currentMusic]->play();
    isPlaying = true;
}

void Indie::Music::pauseMusic()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->pause();
    isPlaying = false;
}

void Indie::Music::stopMusic()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->stop();
    currentMusic = CHUNKS::Intro;
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
    musics[(int)CHUNKS::Loop]->setLoop(isLooped);
    if (musics[(int)currentMusic]->getStatus() == sf::SoundSource::Status::Stopped) {
        switch (currentMusic) {
        case CHUNKS::Intro:
            musics[(int)CHUNKS::Loop]->stop();
            musics[(int)CHUNKS::Loop]->play();
            musics[(int)CHUNKS::Loop]->setLoop(isLooped);
            currentMusic = CHUNKS::Loop;
            break;
        case CHUNKS::Loop:
            if (!isLooped) {
                musics[(int)CHUNKS::Outro]->stop();
                musics[(int)CHUNKS::Outro]->play();
                currentMusic = CHUNKS::Outro;
            } else {
                musics[(int)currentMusic]->setLoop(isLooped);
                musics[(int)currentMusic]->play();
            }
            break;
        case CHUNKS::Outro:
            stopMusic();
            break;
        default:
            stopMusic();
            break;
        }
    }
}