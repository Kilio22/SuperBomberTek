/*
** EPITECH PROJECT, 2020
** joujou_cmake
** File description:
** MusicManager
*/

#include "MusicManager.hpp"

Indie::Music::Music(std::string filepath)
{
    volume = 100;
    isMuted = false;
    isLooped = false;
    isPlaying = false;
    currentMusic = CHUNKS::Intro;
    std::string extension = filepath.substr(filepath.find_last_of("."));
    filepath.resize(filepath.size() - extension.size());

    auto intro = std::make_unique<sf::Music>();
    auto loop = std::make_unique<sf::Music>();
    auto outro = std::make_unique<sf::Music>();
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
    return (volume);
}

void Indie::Music::loop()
{
    isLooped = true;
}

void Indie::Music::unLoop()
{
    isLooped = false;
}

void Indie::Music::drop()
{
    // while (musics.size() > 0) {
    //     auto tmp = musics[0];
    //     musics.erase(musics.begin());
    //     delete tmp;
    // }
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

Indie::MusicManager::MusicManager() :
musics(),
currentMusic(0),
volume(50),
isMuted(false),
isPlaying(false)
{}

void Indie::MusicManager::addMusic(const std::string filepath)
{
    auto ptr = std::make_unique<Indie::Music>(filepath);

    ptr->loop();
    ptr->setVolume(volume);
    if (isMuted)
        ptr->setVolume(0);
    musics.push_back(std::move(ptr));
}

void Indie::MusicManager::setMusic(size_t id)
{
    if (id >= musics.size())
        throw (Indie::Exceptions::InvalidIndexException(__PRETTY_FUNCTION__, "Music at index " + std::to_string(id) + " doesn't exist."));
    if (id == currentMusic)
        return;
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->stopMusic();
    currentMusic = id;
    if (isPlaying)
        musics[currentMusic]->playMusic();
}

void Indie::MusicManager::setVolume(float _vol)
{
    for (size_t i = 0; i < musics.size(); i++) {
        if (!isMuted)
            musics[i]->setVolume(_vol);
    }
    volume = _vol;
}

void Indie::MusicManager::mute()
{
    setVolume(0);
    isMuted = true;
}

void Indie::MusicManager::unMute()
{
    setVolume(volume);
    isMuted = false;
}

void Indie::MusicManager::playMusic()
{
    pauseMusic();
    musics[currentMusic]->playMusic();
    isPlaying = true;
}

void Indie::MusicManager::pauseMusic()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->pauseMusic();
    isPlaying = false;
}

void Indie::MusicManager::stopMusic()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->stopMusic();
    isPlaying = false;
}

void Indie::MusicManager::restartMusic()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->restartMusic();
}

void Indie::MusicManager::update()
{
    for (size_t i = 0; i < musics.size(); i++) {
        musics[i]->update();
    }
}

void Indie::MusicManager::drop()
{
    MusicManager::musics.clear();
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->drop();
}