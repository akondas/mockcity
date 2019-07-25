#include "inmemoryfile.hpp"

InMemoryFile::InMemoryFile(const std::string &path)
{
    load(path);
}

bool InMemoryFile::load(const std::string &path)
{
    if (data.size() != 0) {
        this->path = "";
        data.clear();
        position = 0;
    }

    std::ifstream handle{path, std::ios::binary};
    if (!handle.is_open() || !handle.good()) {
        return false;
    }

    handle.unsetf(std::ios::skipws);

    std::streampos size = 0;
    handle.seekg(0, std::ios::end);
    size = handle.tellg();
    handle.seekg(0, std::ios::beg);

    data.reserve(size);
    data.insert(
        data.begin(),
        std::istream_iterator<uint8_t>(handle),
        std::istream_iterator<uint8_t>()
    );

    this->path = path;
    handle.close();
    return true;
}

bool InMemoryFile::save(const std::string &path/* = ""*/)
{
    std::ofstream handle{path.size() ? path : this->path, std::ios::binary | std::ios::trunc};
    if (!handle.is_open() || !handle.good()) {
        return false;
    }

    handle.write(reinterpret_cast<char *>(&data[0]), data.size() * sizeof(uint8_t));
    handle.close();
    return true;
}

void InMemoryFile::write(const char *data)
{
    write(std::string(data));
}

void InMemoryFile::write(const std::string &string)
{
    write<uint16_t>(string.size());
    for (const auto &ch : string) {
        write<uint8_t>(ch);
    }
}
