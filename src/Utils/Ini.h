#ifndef _Ini_h_
#define _Ini_h_

#include <map>
#include <string>

class Ini
{
    private:
    std::map<std::string, std::string> entries;

    public:
    Ini();
    Ini(const std::string& Filename);

    bool LoadFile(const std::string& Filename);
    std::string operator[](const std::string& str);

    void __dump(FILE* f);

    void ExportFile(const std::string& Filename);
};

#endif

