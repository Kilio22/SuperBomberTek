/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoundManager
*/

#include <iostream>
#include "SoundManager.hpp"

Indie::SoundManager::SoundManager() : muted(false), volume(100)
{
    sf::Listener::setPosition(150, 100, 130);
    sf::Listener::setDirection(1.f, 0.f, 1.f);
    //sf::Listener::setUpVector(0.f, 0.f, 0.f);
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
    this->volume = volume * 5;
}

bool Indie::SoundManager::isMuted() const
{
    return muted;
}

int Indie::SoundManager::getVolume() const
{
    return int(volume / 5);
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
    sound->setPosition(float(sf::Listener::getPosition().x), float(sf::Listener::getPosition().y - 40), float(sf::Listener::getPosition().z));
    toPlay.push_back(sound);
}

void Indie::SoundManager::playSound(std::string key, int x, int y, int z)
{
    if (muted)
        return;

    sf::SoundBuffer &buffer = getBuffer(key);
    std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();

    sound->setBuffer(buffer);
    sound->setVolume(float(volume * 4));
    sound->setRelativeToListener(true);
    sound->setPosition(float(x - sf::Listener::getPosition().x), float(y - sf::Listener::getPosition().y), float(z - sf::Listener::getPosition().z));
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
    sound->setPitch(float((std::rand() % 200 + 100) / 100));
    sound->setRelativeToListener(false);
    sound->setPosition(float(sf::Listener::getPosition().x), float(sf::Listener::getPosition().y - 40), float(sf::Listener::getPosition().z));
    toPlay.push_back(sound);
}

void Indie::SoundManager::playPitchedSound(std::string key, int x, int y, int z)
{
    if (muted)
        return;

    sf::SoundBuffer &buffer = getBuffer(key);
    std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();

    sound->setBuffer(buffer);
    sound->setVolume(float(volume * 4));
    sound->setPitch(float((std::rand() % 200 + 100) / 100));
    sound->setRelativeToListener(true);
    // Dans la doc c'est dit que c'est absolue par défaut, mais quand on le met en relatif c'est bon.
    // bah enfaite non, c'est des fdp.
    // Ils ont menti.
    // C'est tjrs absolu. fuk u è_é
    sound->setPosition(float(x - sf::Listener::getPosition().x), float(y - sf::Listener::getPosition().y), float(z - sf::Listener::getPosition().z));
    toPlay.push_back(sound);
}

void Indie::SoundManager::update()
{
    while (!toPlay.empty()) {
        if (playing.size() >= 126) {
            toPlay.clear();
            break;
        }
        toPlay[0]->play();
        playing.push_back(toPlay[0]);
        toPlay.erase(toPlay.begin());
    }
    // NEVER PLAY MORE THAN 126 BUFFERS AT ONCE. OpenAL big pooopoo.
    //std::cout << "SIZE : ======================================================= " << playing.size() << std::endl;
    for (size_t i = 0; i < playing.size(); i++) {
        if (playing[i]->getStatus() != sf::SoundSource::Status::Playing)
            playing.erase(playing.begin() + i);
    }
}