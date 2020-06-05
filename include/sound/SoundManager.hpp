/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoundManager
*/

#ifndef SOUNDMANAGER_HPP_
#define SOUNDMANAGER_HPP_

#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Exceptions.h"

namespace Indie {
class SoundManager {
        public:
            SoundManager();
            ~SoundManager() = default;

            void update();

            void setMute(bool);
            void setVolume(int);
            bool isMuted() const;
            int getVolume() const;

            void addSound(std::string);
            void playSound(std::string);
            void playSound(std::string, int, int, int);
            void playPitchedSound(std::string);
            void playPitchedSound(std::string, int, int, int);

        private:
            std::string getFileName(std::string const &);
            sf::SoundBuffer &getBuffer(std::string &);

        private:
            bool muted;
            int volume;
            std::unordered_map<std::string, sf::SoundBuffer> buffers;
            std::vector<std::shared_ptr<sf::Sound>> toPlay;
            std::vector<std::shared_ptr<sf::Sound>> playing;
    };
}

#endif /* !SOUNDMANAGER_HPP_ */
