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

    // replace binary in exe (offset: 0xE94)
    wow_exe.seekp(0xE94);
    wow_exe << static_cast<char>(0xEB);

    std::cout << "World of Warcraft exe has been patched!\n";
    return 0;
}
