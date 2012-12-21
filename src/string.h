#ifndef STRING_H
#define STRING_H

#include <string>
#include <sstream>

template <typename T>
std::string NumberToString ( T Number )
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}


template <typename T>
T StringToNumber(const std::string& numberAsString)
{
    T valor;

    std::stringstream stream(numberAsString);
    stream >> valor;
    return valor;
}

#endif
