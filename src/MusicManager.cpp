/*
** EPITECH PROJECT, 2020
** joujou_cmake
** File description:
** MusicManager
*/

#include "MusicManager.hpp"

MyMusic::MyMusic(std::string filepath)
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
        throw Indie::Exceptions::FileNotFoundException("MusicManager.cpp line 24", "File \"" + filepath + "intro" + extension + "\" not found.");
    if (!loop->openFromFile(filepath + "_loop" + extension))
        throw Indie::Exceptions::FileNotFoundException("MusicManager.cpp line 26", "File \"" + filepath + "loop" + extension + "\" not found.");
    if (!outro->openFromFile(filepath + "_outro" + extension))
        throw Indie::Exceptions::FileNotFoundException("MusicManager.cpp line 28", "File \"" + filepath + "outro" + extension + "\" not found.");
    musics.push_back(std::move(intro));
    musics.push_back(std::move(loop));
    musics.push_back(std::move(outro));
}

void MyMusic::drop()
{
    // while (musics.size() > 0) {
    //     auto tmp = musics[0];
    //     musics.erase(musics.begin());
    //     delete tmp;
    // }
}

void MyMusic::setVolume(float _vol)
{
    volume = _vol;
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->setVolume(_vol);
}

void MyMusic::mute()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->setVolume(0);
    isMuted = true;
}

void MyMusic::unMute()
{
    setVolume(volume);
    isMuted = false;
}

void MyMusic::playMusic()
{
    pauseMusic();
    musics[(int)currentMusic]->play();
    isPlaying = true;
}

void MyMusic::pauseMusic()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->pause();
    isPlaying = false;
}

void MyMusic::stopMusic()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->stop();
    currentMusic = CHUNKS::Intro;
    isPlaying = false;
}

void MyMusic::restartMusic()
{
    stopMusic();
    playMusic();
}

void MyMusic::update()
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

MusicManager::MusicManager() :
musics(),
currentMusic(0),
volume(50),
isMuted(false),
isPlaying(false)
{}

void MusicManager::addMusic(const std::string filepath)
{
    auto ptr = std::make_unique<MyMusic>(filepath);

    ptr->loop();
    ptr->setVolume(volume);
    if (isMuted)
        ptr->setVolume(0);
    musics.push_back(std::move(ptr));
}

void MusicManager::setMusic(size_t id)
{
    if (id >= musics.size())
        throw (Indie::Exceptions::InvalidIndexException("MusicManager.cpp line 151", "Music at index " + std::to_string(id) + " doesn't exist."));
    if (id == currentMusic)
        return;
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->stopMusic();
    currentMusic = id;
    if (isPlaying)
        musics[currentMusic]->playMusic();
}

void MusicManager::setVolume(float _vol)
{
    for (size_t i = 0; i < musics.size(); i++) {
        if (!isMuted)
            musics[i]->setVolume(_vol);
    }
    volume = _vol;
}

void MusicManager::mute()
{
    setVolume(0);
    isMuted = true;
}

void MusicManager::unMute()
{
    setVolume(volume);
    isMuted = false;
}

void MusicManager::playMusic()
{
    pauseMusic();
    musics[currentMusic]->playMusic();
    isPlaying = true;
}

void MusicManager::pauseMusic()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->pauseMusic();
    isPlaying = false;
}

void MusicManager::stopMusic()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->stopMusic();
    isPlaying = false;
}

void MusicManager::restartMusic()
{
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->restartMusic();
}

void MusicManager::update()
{
    for (size_t i = 0; i < musics.size(); i++) {
        musics[i]->update();
    }
}

void MusicManager::drop()
{
    MusicManager::musics.clear();
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->drop();
}