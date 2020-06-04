/*
** EPITECH PROJECT, 2020
** joujou_cmake
** File description:
** MusicManager
*/

#ifndef MUSICMANAGER_HPP_
#define MUSICMANAGER_HPP_

#include <iostream>
#include <limits>
#include <vector>
#include <memory>
#include <SFML/Audio.hpp>
#include "Exceptions.h"
#include "Music.hpp"

namespace Indie {

class MusicManager {
    public:
        MusicManager();
        ~MusicManager() = default;

        void addMusic(const std::string filepath);
        void setMusic(size_t id);
        void setVolume(float _vol);
        float getMusicVolume(void) const;
        void mute();
        void unMute();
        void playMusic();
        void pauseMusic();
        void stopMusic();
        void restartMusic();
        void update();
        Music::Status getStatus();
        void setStatus(Music::Status);
        bool isMusicMuted() const;

    private:
        std::vector<std::unique_ptr<Indie::Music>> musics;
        size_t currentMusic;
        float volume;
        bool isMuted;
        bool isPlaying;
};

}
#endif /* !MUSICMANAGER_HPP_ */