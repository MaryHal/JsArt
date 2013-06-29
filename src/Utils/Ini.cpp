#include "Ini.h"

#include <fstream>

#include "StringUtils.h"

Ini::Ini()
{
}

Ini::Ini(const std::string& Filename)
{
    LoadFile(Filename);
}

bool Ini::LoadFile(const std::string& Filename)
{
    std::ifstream file(Filename.c_str(), std::ios::in);

    if (file.fail())
    {
        return false;
    }

    std::string section;
    std::string key;
    std::string value;

    std::string line;

    while (getline(file, line, '\n'))
    {
        trim(line);

        if (line.empty() || line[0] == ';')
            continue;

        if (line[0] == '[')
        {
            unsigned int bracketLoc = line.find_last_of(']');
            section = line.substr(1, bracketLoc - 1);
            section = trim(section);
            continue;
        }

        unsigned int equalLoc = line.find_first_of('=');
        key = line.substr(0, equalLoc - 1);
        key = trim(key);

        value = line.substr(equalLoc + 1);
        trim(value);

        // Is this wasteful?
        // check for comments after a section
        std::string::size_type comment = value.find_first_of(';');
        if (comment != std::string::npos)
        {
            value = value.substr(0, comment - 1);
            trim(value);
        }

        // check for string value
        // TO DO: 
        //      - reason out that after all this stuff, the first quotation mark
        //        would be the first character, and the second quotation would be
        //        the last character
        //      - decide whether to retain spaces, if any, between the quotation.
        if (value[0] == '\"')
        {
            value = value.substr(1, value.length() - 1);
            trim(value);
        }

        entries[section + '/' + key] = value;
    }
    file.close();

    return true;
}

std::string Ini::operator[](const std::string& str)
{
    return entries[str];
}

void Ini::__dump(FILE* f)
{
    // Messy dump. Does not retain ini file format
    for (std::map<std::string, std::string>::iterator iter = entries.begin();
         iter != entries.end();
         ++iter)
    {
        fprintf(f, "%s=%s\n", iter->first.c_str(), iter->second.c_str());
    }
}

void Ini::ExportFile(const std::string& Filename)
{
    // Doing it this way because we don't want to delete comments in their file, right?
    for (std::map<std::string, std::string>::iterator iter = entries.begin();
         iter != entries.end();
         ++iter)
    {
        // Search for key, search for value, replace value.
    }
}

