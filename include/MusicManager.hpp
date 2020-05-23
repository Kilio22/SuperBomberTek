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
#include <memory>
#include <SFML/Audio.hpp>

class MyMusicException : public std::exception
{
    public:
        MyMusicException(std::string const &message, std::string const type) noexcept {
            _message = message;
            _type = type;
        }

        const char *type() const noexcept {
            return (_type.data());
        }
        const char *what() const noexcept override {
            return (_message.data());
        };
    protected:
        std::string _message;
        std::string _type;
};

class InvalidPath : public MyMusicException
{
    public:
        InvalidPath(std::string const &message) noexcept : MyMusicException(message, "InvalidPath")
        {}
};

class MusicManagerException : public std::exception
{
    public:
        MusicManagerException(std::string const &message, std::string const type) noexcept {
            _message = message;
            _type = type;
        }

        const char *type() const noexcept {
            return (_type.data());
        }
        const char *what() const noexcept override {
            return (_message.data());
        };
    protected:
        std::string _message;
        std::string _type;
};

class InvalidIndex : public MusicManagerException
{
    public:
        InvalidIndex(std::string const &message) noexcept : MusicManagerException(message, "InvalidIndex")
        {}
};

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
        enum Chunks {Intro, Loop, Outro};
        std::vector<std::unique_ptr<sf::Music>> musics;
        MyMusic::Chunks currentMusic;
        float volume;
        bool isMuted;
        bool isLooped;
        bool isPlaying;
};

class MusicManager {
    public:
        MusicManager() = delete;
        ~MusicManager() = delete;

        static void addMusic(const std::string &filepath);
        static void setMusic(size_t id);
        static void setVolume(float _vol);

        static void mute();
        static void unMute();

        static void playMusic();
        static void pauseMusic();
        static void stopMusic();
        static void restartMusic();

        static void update(); //To be called at every frame : MusicManager::update();

        static void drop();

        static std::vector<std::unique_ptr<MyMusic>> musics;
        static size_t currentMusic;
        static float volume;
        static bool isMuted;
        static bool isPlaying;
};

#endif /* !MUSICMANAGER_HPP_ */