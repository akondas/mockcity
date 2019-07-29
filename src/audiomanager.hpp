#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <map>
#include <memory>
#include <vector>

#include <boost/filesystem.hpp>
#include <SFML/Audio.hpp>

#include "logger.hpp"

class AudioManager
{
    public:
        AudioManager() = default;
        ~AudioManager() = default;

        void releaseFinished();

        void load();

        void play(const std::string &name, bool loop = false);

    private:
        std::map<const std::string, std::unique_ptr<sf::SoundBuffer>> buffers;
        std::vector<std::unique_ptr<sf::Sound>> sounds;
};

#endif
