/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <vector>
#include <string>
#include <memory>
#include <SFML/Audio.hpp>

namespace Indie {

class Music {
    public:
        Music(std::string filepath);
        ~Music() = default;

        enum class Status : int {
            Intro,
            Loop,
            Outro,
            NotPlaying
        };

        float getVolume() const;
        void setVolume(float volume);
        void loop();
        void unLoop();
        void mute();
        void unMute();

        void playMusic();
        void pauseMusic();
        void stopMusic();
        void restartMusic();
        void update();
        void setStatus(Status);
        Status getStatus();

    private:
        std::vector<std::unique_ptr<sf::Music>> musics;
        Status currentMusic;
        float volume;
        bool isMuted;
        bool isLooped;
        bool isPlaying;
};

} // namespace Indie::Music

#endif /* !MUSIC_HPP_ */
