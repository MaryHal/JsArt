#ifndef _StringUtils_h_
#define _StringUtils_h_

#include <string>

//#include <sstream>
#include <boost/lexical_cast.hpp>
#define toString boost::lexical_cast<std::string>
#define fromString boost::lexical_cast

std::string& ltrim(std::string& s);
std::string& rtrim(std::string& s);
std::string& trim(std::string& s);

std::string formatString(const char* format, ...);
std::string numberString(int number);

/*
template <typename T>
T fromString(const std::string& s, std::ios_base& (*f)(std::ios_base&) = std::dec)
{
    std::istringstream iss(s);

    T t;
    iss >> f >> t;
    return t;
}

template<class T>
std::string toString(const T& t)
{
     std::ostringstream stream;
     stream << t;
     return stream.str();
}
*/

#endif

