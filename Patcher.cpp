#include <iostream>
#include <filesystem>
#include <fstream>
#include <array>
#include <iterator>

int main(int argc, char** argv)
{
    std::string wow;
    if (argc < 2)
    {
        std::cout << "World of Warcraft exe not found!\n";
        return 1;
    }

    wow = argv[1];

    std::fstream wow_exe(wow, std::ios::in | std::ios::out | std::ios::binary);
    if (!wow_exe)
    {
        std::cout << "World of Warcraft exe not found!\n";
        return 1;
    }

    // windowed mode to full screen
    wow_exe.seekp(0xE94);
    wow_exe << static_cast<char>(0xEB);

    // melee swing on right-click
    wow_exe.clear();
    wow_exe.seekg(0);
    wow_exe.seekp(0x2E1C67);
    for (size_t i = 0; i < 11; ++i)
        wow_exe << static_cast<char>(0x90);

    // NPC attack animation when turning
    wow_exe.clear();
    wow_exe.seekg(0);
    wow_exe.seekp(0x33D7C9);
    wow_exe << static_cast<char>(0xEB);

    // "ghost" attack when NPC evades from combat
    wow_exe.clear();
    wow_exe.seekg(0);
    wow_exe.seekp(0x355BF);
    wow_exe << static_cast<char>(0xEB);

    std::cout << "World of Warcraft exe has been patched!\n";
    return 0;
}
