#include "audiomanager.hpp"

void AudioManager::releaseFinished()
{
    auto it = sounds.begin();
    while (it != sounds.end()) {
        auto &sound = *it;
        if (!sound->getLoop() && sound->getStatus() == sf::Sound::Stopped) {
            it = sounds.erase(it);
        } else {
            ++it;
        }
    }
}

void AudioManager::load()
{
    boost::filesystem::path path("media/sfx/");
    if (!boost::filesystem::exists(path) || !boost::filesystem::is_directory(path)) {
        return;
    }

    boost::filesystem::directory_iterator end;
    for (boost::filesystem::directory_iterator it(path); it != end; ++it) {
        if (boost::filesystem::is_directory(it->path())) {
            continue;
        }

        std::string name = it->path().filename().string();
        if (name.length() < 4 || name.substr(name.length() - 4) != ".ogg") {
            g_logger->log(LogLevel::Warning, "File \"%s\" could not be loaded as it's not an .ogg", name.c_str());
            continue;
        }

        auto buffer = std::make_unique<sf::SoundBuffer>();
        if (!buffer->loadFromFile("media/sfx/" + name)) {
            g_logger->log(LogLevel::Warning, "File \"%s\" could not be loaded", name.c_str());
            continue;
        }

        buffers[name.substr(0, name.length() - 4)] = std::move(buffer);
    }

    g_logger->log(LogLevel::Info, "Loaded %d sound(s)", buffers.size());
}

void AudioManager::play(const std::string &name, bool loop)
{
    auto buffer = buffers.find(name);
    if (buffer == buffers.end()) {
        g_logger->log(LogLevel::Warning, "Sound \"%s\" could not be played, as it is not loaded", name.c_str());
        return;
    }

    auto sound = std::make_unique<sf::Sound>(*buffer->second);
    sound->setLoop(loop);
    sound->play();

    sounds.push_back(std::move(sound));
}
