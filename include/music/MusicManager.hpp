/*
** EPITECH PROJECT, 2020
** joujou_cmake
** File description:
** MusicManager
*/

#ifndef MUSICMANAGER_HPP_
#define MUSICMANAGER_HPP_

#include "Music.hpp"
#include <memory>
#include <vector>

namespace Indie
{
    /**
     * @brief MusicManager class
     */
    class MusicManager
    {
    public:
        MusicManager();
        ~MusicManager() = default;

        /**
         * @brief Adds a music
         * @param filepath Path to the music
         */
        void addMusic(const std::string filepath);

        /**
         * @brief Sets the current music
         * @param id ID of the music to set
         */
        void setMusic(size_t id);

        /**
         * @brief Sets the current volume
         * @param vol The new volume
         */
        void setVolume(int vol);

        /**
         * @brief Gets the current volume
         * @return float The current volume
         */
        int getMusicVolume(void) const;

        /**
         * @brief Mutes the current music
         */
        void mute();

        /**
         * @brief Unmutes the current music
         */
        void unMute();

        /**
         * @brief Plays the current music
         */
        void playMusic();

        /**
         * @brief Pauses the current music
         *
         */
        void pauseMusic();

        /**
         * @brief Stops the current music
         */
        void stopMusic();

        /**
         * @brief Restarts the current music
         *
         */
        void restartMusic();

        /**
         * @brief Updates the musics
         */
        void update();

        /**
         * @brief Gets the status of the current music
         * @return Music::Status The status of the music
         */
        Music::Status getStatus();

        /**
         * @brief Sets the status of the current music
         */
        void setStatus(Music::Status);

        /**
         * @brief Checks if the current music is muted or not
         * @return true The music is muted
         * @return false The music is not muted
         */
        bool isMusicMuted() const;

    private:
        std::vector<std::unique_ptr<Music>> musics;
        size_t currentMusic;
        int volume;
        bool isMuted;
        bool isPlaying;
    };

}
#endif /* !MUSICMANAGER_HPP_ */