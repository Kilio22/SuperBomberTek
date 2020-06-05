/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoundManager
*/

#include "SoundManager.hpp"

Indie::SoundManager::SoundManager() : muted(false), volume(20)
{
    sf::Listener::setPosition(150, 40, 130);
    sf::Listener::setDirection(0, -1, 0);
}

std::string Indie::SoundManager::getFileName(std::string const &filepath)
{
    std::string filename(filepath.c_str());
    const size_t last_slash_id = filename.find_last_of("\\/");

    if (std::string::npos != last_slash_id)
        filename.erase(0, last_slash_id + 1);
    const size_t period_id = filename.rfind('.');
    if (std::string::npos != period_id)
        filename.erase(period_id);
    return (filename);
}

void Indie::SoundManager::setMute(bool mute)
{
    this->muted = mute;
}

void Indie::SoundManager::setVolume(int volume)
{
    this->volume = volume;
}

bool Indie::SoundManager::isMuted() const
{
    return muted;
}

int Indie::SoundManager::getVolume() const
{
    return volume;
}

void Indie::SoundManager::addSound(std::string filepath)
{
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile(filepath))
        throw (Indie::Exceptions::FileNotFoundException(ERROR_STR, "File " + filepath + " not found."));
    buffers.insert({getFileName(filepath), buffer});
}

sf::SoundBuffer &Indie::SoundManager::getBuffer(std::string &key)
{
    auto it = buffers.find(key);

    if (it == buffers.end())
        throw (Indie::Exceptions::SoundNotFoundException(ERROR_STR, "Sound " + key + " was never loaded and therefor could not be accessed."));
    return it->second;
}

void Indie::SoundManager::playSound(std::string key)
{
    if (muted)
        return;

    sf::SoundBuffer &buffer = getBuffer(key);
    std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();

    sound->setBuffer(buffer);
    sound->setVolume(float(volume));
    sound->setRelativeToListener(false);
    toPlay.push_back(sound);
}

void Indie::SoundManager::playSound(std::string key, int x, int y, int z)
{
    if (muted)
        return;

    sf::SoundBuffer &buffer = getBuffer(key);
    std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();

    sound->setBuffer(buffer);
    sound->setVolume(float(volume));
    sound->setRelativeToListener(true);
    sound->setPosition(float(x), float(y), float(z));
    toPlay.push_back(sound);
}

void Indie::SoundManager::playPitchedSound(std::string key)
{
    if (muted)
        return;

    sf::SoundBuffer &buffer = getBuffer(key);
    std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();

    sound->setBuffer(buffer);
    sound->setVolume(float(volume));
    sound->setPitch(float((std::rand() % 5)));
    sound->setRelativeToListener(false);
    toPlay.push_back(sound);
}

void Indie::SoundManager::playPitchedSound(std::string key, int x, int y, int z)
{
    if (muted)
        return;

    sf::SoundBuffer &buffer = getBuffer(key);
    std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();

    sound->setBuffer(buffer);
    sound->setVolume(float(volume));
    sound->setPitch(float((std::rand() % 5)));
    //sound->setRelativeToListener(true);
    sound->setPosition(float(x), float(y), float(z));
    toPlay.push_back(sound);
}

void Indie::SoundManager::update()
{
    while (!toPlay.empty()) {
        toPlay[0]->play();
        playing.push_back(toPlay[0]);
        toPlay.erase(toPlay.begin());
    }
    for (size_t i = 0; i < playing.size(); i++) {
        if (playing[i]->getStatus() != sf::SoundSource::Status::Playing)
            playing.erase(playing.begin() + i);
    }
}