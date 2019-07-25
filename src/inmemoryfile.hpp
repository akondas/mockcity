#ifndef INMEMORYFILE
#define INMEMORYFILE

#include <cstdint>
#include <fstream>
#include <iterator>
#include <vector>

class InMemoryFile
{
    public:
        InMemoryFile() = default;
        InMemoryFile(const std::string &path);
        ~InMemoryFile() = default;

        bool load(const std::string &path);
        bool save(const std::string &path = "");

        template<typename T> T read() {
            static_assert(std::is_integral<T>::value, "Non-integral type");

            std::size_t size = sizeof(T) - 1;
            T value = data[position++] << 8 * size;

            while (size--) {
                value |= data[position++] << 8 * size;
            }

            return value;
        };

        template<typename T> void write(T value) {
            static_assert(std::is_integral<T>::value, "Non-integral type");

            std::size_t size = sizeof(T);
            while (size--) {
                data.push_back((value >> 8 * size) & 0xFF);
            }

            position += sizeof(T);
        }

        void write(const char *data);
        void write(const std::string &string);

    private:
        std::string path{};
        std::vector<uint8_t> data{};
        size_t position = 0;
};

template<> inline std::string InMemoryFile::read<std::string>()
{
    uint16_t size = read<uint16_t>();
    std::string string = {};
    string.reserve(size);
    for (uint16_t i = 0; i < size; ++i) {
        string += read<uint8_t>();
    }

    return string;
}

#endif
