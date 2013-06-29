#include "StringUtils.h"

#include <cstdio>
#include <cstdarg>
#include <algorithm>

std::string& ltrim(std::string& s) 
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string& rtrim(std::string& s) 
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string& trim(std::string& s) 
{
    return ltrim(rtrim(s));
}

std::string formatString(const char* format, ...)
{
    char sz[1024];
    va_list marker;
    
    va_start(marker, format);
    vsprintf(sz, format, marker);
    va_end(marker);
    
    return sz;
}

std::string numberString(int number)
{
    std::string result;
    bool negative = false;
    
    if (number < 0)
    {
        negative = true;
        number *= -1;
    }
    
    int millions = number / 1000000;
    number -= millions * 1000000;
    int thousands = number / 1000;
    number -= thousands * 1000;
    int ones = number;
    
    if (millions != 0)
    {
        result = formatString("%d,%03d,%03d", millions, thousands, ones);
    }
    else if (thousands != 0)
    {
        result = formatString("%d,%03d", thousands, ones);
    }
    else
    {
        result = formatString("%d", ones);
    }
    
    if (negative)
    {
        result = formatString("-%s",result.c_str());
    }
    
    return result;
}
 

