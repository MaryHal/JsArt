#include "FileLoader.h"
#include "StringUtils.h"

#include <cstdio>

FileLoader::FileLoader(const std::string& filename, Mode m)
{
    mode = m;

    std::string modeStr[MAX] =
        {
            "rb", // Read
            "wb"  // Write
        };

    file = fopen(filename.c_str(), modeStr[mode].c_str());

    if (file)
    {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        rewind(file);
    }
}

FileLoader::~FileLoader()
{
    if (file)
        fclose(file);
}

void FileLoader::gotoBeginning()
{
    fseek(file, 0, SEEK_SET);
}

size_t FileLoader::getLength()
{
    return length;
}

bool FileLoader::atEnd()
{
    return !file || feof(file);
}

bool FileLoader::readLine(std::string* line)
{
    char buffer[1024]; // good enough... I hope

    if (!atEnd() && fgets(buffer, 1023, file))
    {
        buffer[1023] = 0;

        for (int i = 0; i < 1024; i++)
        {
            if (buffer[i] == 0 || buffer[i] == '\n' || buffer[i] == '\r')
            {
                buffer[i] = 0;
                break;
            }
        }
        *line = buffer;
        return true;
    }

    return false;
}

// static
bool FileLoader::exists(const std::string& filename)
{
    FILE* f = fopen(filename.c_str(), "r");
    if (f)
    {
        fclose(f);
        return true;
    }
    return false;
}
