#include <iostream>
#include <filesystem>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>

// wow base = 50 0C00

static std::fstream wow_exe;

template <typename T>
void write_pos(std::streampos pos, T value)
{
    wow_exe.clear();
    wow_exe.seekg(0);
    wow_exe.seekp(pos);
    wow_exe << value;
}

void write_pos(std::streampos pos, std::vector<uint8_t> const& values)
{
    wow_exe.clear();
    wow_exe.seekg(0);
    wow_exe.seekp(pos);
    for (uint8_t v : values)
        wow_exe << v;
}

void write_pos_n(std::streampos pos, uint8_t value, size_t n)
{
    wow_exe.clear();
    wow_exe.seekg(0);
    wow_exe.seekp(pos);
    for (size_t i = 0; i < n; ++i)
        wow_exe << value;
}

int main(int argc, char** argv)
{
    std::string wow;
    if (argc < 2)
    {
        std::cout << "World of Warcraft exe not found!\n";
        return 1;
    }

    wow = argv[1];

    wow_exe = std::fstream(wow, std::ios::in | std::ios::out | std::ios::binary);

    if (!wow_exe)
    {
        std::cout << "World of Warcraft exe not found!\n";
        return 1;
    }

    // windowed mode to full screen
    write_pos<uint8_t>(0xE94, 0xEB);

    // melee swing on right-click
    write_pos_n(0x2E1C67, 0x90, 11);

    // NPC attack animation when turning
    write_pos<uint8_t>(0x33D7C9, 0xEB);

    // "ghost" attack when NPC evades from combat
    write_pos<uint8_t>(0x355BF, 0xEB);

    // missing pre cast animation when canceling channeled spells
    write_pos_n(0x33E0D6, 0x90, 22);

    // mouse flickering and camera snapping issue when mouse has high report rate
    // credits to bonbigz
    {
        write_pos(0x469A2C, { 0xE9, 0x71, 0xF0, 0x0B, 0x00,  0xF8, 0x13, 0xD4, 0x00, 0x8B, 0x1D, 0xFC });
        write_pos(0x528AA2, { 0x8D, 0x4D, 0xF0, 0x51, 0x57, 0xFF, 0x15, 0xDC, 0xF5, 0x9D, 0x00, 0x8B, 0x45, 0xF0, 0x8B, 0x15, 0xF8, 0x13, 0xD4, 0x00, 0xE9, 0x7A, 0x0F, 0xF4, 0xFF });
        write_pos(0x4691B1, { 0x89, 0xE5, 0x8B, 0x05, 0xFC, 0x13, 0xD4, 0x00, 0x8B, 0x0D, 0xF8, 0x13, 0xD4, 0x00, 0xEB, 0xC2, 0x7D, 0x03, 0x83, 0xC1, 0x01, 0x83, 0xC0, 0x32, 0x83, 0xC1, 0x32, 0x3B, 0x0D, 0xEC, 0xBC, 0xCA, 0x00, 0x7E, 0x03, 0x83, 0xE9, 0x01, 0x3B, 0x05, 0xF0, 0xBC, 0xCA, 0x00, 0x7E, 0x03, 0x83, 0xE8, 0x01, 0x83, 0xE9, 0x32, 0x83, 0xE8, 0x32, 0x89, 0x0D, 0xF8, 0x13, 0xD4, 0x00, 0x89, 0x05, 0xFC, 0x13, 0xD4, 0x00, 0x89, 0xEC, 0x5D, 0xE9, 0xB4, 0xF7, 0xFF, 0xFF, 0xEC, 0x5D, 0xC3, 0xC3 });
        write_pos(0x469183, { 0x83, 0xF8, 0x32, 0x7D, 0x03, 0x83, 0xC0, 0x01, 0x83, 0xF9, 0x32, 0xEB, 0x31 });
    }

    // naked character issue (disables SPELL_AURA_X_RAY)
    write_pos<uint8_t>(0x1DDC5D, 0xEB);

    // patches missiles impacting with terrain
    // (spell effects such as Typhoon will lose their visual effect once they impact with terrain)
    // (Typhoon is spanwed on the ground so it loses its visual most of the time)
    write_pos<uint8_t>(0x1FC99E, 0x00);
    write_pos<uint8_t>(0x1FC8C7, 0x00);
    write_pos<uint8_t>(0x1FC735, 0x00);

    // patch mail request timeout
    // you no longer need to wait 60 seconds or relog to receive new mail
    write_pos(0x6D899, { 0x05, 0x01, 0x00, 0x00, 0x00 });

    // patch area trigger timer to be more precise (250ms -> 50ms)
    write_pos<uint8_t>(0x1DB241, 50);

    // Return of "The Blue Moon"
    write_pos(0x5CFBC0, { 0xC7, 0x05, 0x74, 0x8E, 0xD3, 0x00, 0xFF, 0xFF, 0xFF, 0xFF });

    std::cout << "World of Warcraft exe has been patched!\n";
    return 0;
}
