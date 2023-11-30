#include <iostream>
#include <filesystem>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>

// wow base = 50 0C00

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

    // missing pre cast animation when canceling channeled spells
    wow_exe.clear();
    wow_exe.seekg(0);
    wow_exe.seekp(0x33E0D6);
    for (size_t i = 0; i < 22; ++i)
        wow_exe << static_cast<char>(0x90);

    // mouse flickering and camera snapping issue when mouse has high report rate
    // credits to bonbigz
    {
        wow_exe.clear();
        wow_exe.seekg(0);
        wow_exe.seekp(0x369A2F);
        for (char b : { 0x8B, 0x15, 0xF8, 0x13, 0xD4, 0x00, 0x8B, 0x1D, 0xFC, 0x13, 0xD4, 0x00 })
            wow_exe << b;

        wow_exe.clear();
        wow_exe.seekg(0);
        wow_exe.seekp(0x369A2C);
        for (char b : { 0xE9, 0x71, 0xF0, 0x0B, 0x00 })
            wow_exe << b;

        wow_exe.clear();
        wow_exe.seekg(0);
        wow_exe.seekp(0x428AA2);
        for (char b : { 0x8D, 0x4D, 0xF0, 0x51, 0x57, 0xFF, 0x15, 0xDC, 0xF5, 0x9D, 0x00, 0x8B, 0x45, 0xF0, 0x8B, 0x15, 0xF8, 0x13, 0xD4, 0x00, 0xE9, 0x7A, 0x0F, 0xF4, 0xFF })
            wow_exe << b;

        wow_exe.clear();
        wow_exe.seekg(0);
        wow_exe.seekp(0x3691B0);
        for (char b : { 0x55, 0x89, 0xE5, 0x8B, 0x05, 0xFC, 0x13, 0xD4, 0x00, 0x8B, 0x0D, 0xF8, 0x13, 0xD4, 0x00, 0xEB, 0xC2, 0x7D, 0x03, 0x83, 0xC1, 0x01, 0x83, 0xC0, 0x32, 0x83, 0xC1, 0x32, 0x3B, 0x0D, 0xEC, 0xBC, 0xCA, 0x00, 0x7E, 0x03, 0x83, 0xE9, 0x01, 0x3B, 0x05, 0xF0, 0xBC, 0xCA, 0x00, 0x7E, 0x03, 0x83, 0xE8, 0x01, 0x83, 0xE9, 0x32, 0x83, 0xE8, 0x32, 0x89, 0x0D, 0xF8, 0x13, 0xD4, 0x00, 0x89, 0x05, 0xFC, 0x13, 0xD4, 0x00, 0x89, 0xEC, 0x5D, 0xE9, 0xB4, 0xF7, 0xFF, 0xFF })
            wow_exe << b;

        wow_exe.clear();
        wow_exe.seekg(0);
        wow_exe.seekp(0x369183);
        for (char b : { 0x83, 0xF8, 0x32, 0x7D, 0x03, 0x83, 0xC0, 0x01, 0x83, 0xF9, 0x32, 0xEB, 0x31 })
            wow_exe << b;
    }

    // naked character issue
    wow_exe.clear();
    wow_exe.seekg(0);
    wow_exe.seekp(0x1DDC5D);
    wow_exe << static_cast<char>(0xEB);

    std::cout << "World of Warcraft exe has been patched!\n";
    return 0;
}
