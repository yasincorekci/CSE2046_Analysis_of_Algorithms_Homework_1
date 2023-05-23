
#include <fstream>
#include <sstream>
#include <random>
#include <ctime>

#include "util.h"

std::string Util::readFile(const std::string& filename)
{
    std::string content = "";

    std::ifstream ifs(filename);

    if (ifs.is_open()) {
        std::ostringstream ss;
        ss << ifs.rdbuf();
        content = ss.str();
        ifs.close();
    }

    return content;
}

bool Util::writeFile(const std::string& filename, const std::string& content)
{
    std::ofstream ofs(filename);

    if (ofs.is_open()) {
        ofs << content;
        ofs.close();
        return true;
    }

    return false;
}

std::string Util::createRandomHtml()
{
    std::ostringstream ss;
    
    const static char alphabets[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size_t len = strlen(alphabets);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    ss << "<html><head><title>Random Html</title><style type=\"text/css\" xml:space=\"preserve\">div.chapter {page-break-before: always; margin-top: 4em;}</style></head><body><div class=\"chapter\"><p>";

    for (int i = 0; i < (1 << 21); ++i) {
        ss << alphabets[std::rand() % len];
        if (i % 120 == 0)
            ss << "\n";
    }

    ss << "</p></div></body></html>";

    return ss.str();
}
