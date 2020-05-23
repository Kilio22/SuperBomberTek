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

class MyMusic {
    public:
        MyMusic(std::string filepath);
        ~MyMusic() = default;

        void drop();

        float getVolume() const {return volume;}
        void setVolume(float volume);
        void loop() {isLooped = true;}
        void unLoop() {isLooped = false;}
        void mute();
        void unMute();

        void playMusic();
        void pauseMusic();
        void stopMusic();
        void restartMusic();
        void update();

    private:

        enum class CHUNKS : int {
            Intro,
            Loop,
            Outro
        };

        std::vector<std::unique_ptr<sf::Music>> musics;
        CHUNKS currentMusic;
        float volume;
        bool isMuted;
        bool isLooped;
        bool isPlaying;
};

class MusicManager {
    public:
        MusicManager();
        ~MusicManager() {}

        void addMusic(const std::string filepath);
        void setMusic(size_t id);
        void setVolume(float _vol);
        void mute();
        void unMute();
        void playMusic();
        void pauseMusic();
        void stopMusic();
        void restartMusic();
        void update(); //To be called at every frame : MusicManager::update();
        void drop();

    private:
        std::vector<std::unique_ptr<MyMusic>> musics;
        size_t currentMusic;
        float volume;
        bool isMuted;
        bool isPlaying;
};

#endif /* !MUSICMANAGER_HPP_ */