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

            void addSound(const std::string &);
            void playSound(const std::string &);
            void playSound(const std::string &, float, float, float);
            void playPitchedSound(const std::string &);
            void playPitchedSound(const std::string &, float, float, float);

        private:
            std::string getFileName(std::string const &) const;
            const sf::SoundBuffer &getBuffer(const std::string &) const;

        private:
            bool muted;
            int volume;
            std::unordered_map<std::string, sf::SoundBuffer> buffers;
            std::vector<std::unique_ptr<sf::Sound>> toPlay;
            std::vector<std::unique_ptr<sf::Sound>> playing;
    };
}

#endif /* !SOUNDMANAGER_HPP_ */
