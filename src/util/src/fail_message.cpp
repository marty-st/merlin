#include <util/fail_message.hpp>
#include <sstream>

// Code from: https://gitlab.fi.muni.cz/qtrtik/rofibots

std::string buildFailureMessage(char const* const file, int const line,
                                char const* const func, std::string const& msg)
{
    std::stringstream sstr;
    sstr << std::string(file)
         << '[' << line << "]{" << std::string(func) << "} : "
         << msg
         ;
    return sstr.str();
}
