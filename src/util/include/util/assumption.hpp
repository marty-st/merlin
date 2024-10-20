#ifndef ASSUMPTION_INCLUDED
#define ASSUMPTION_INCLUDED

// Code from: https://gitlab.fi.muni.cz/qtrtik/rofibots

// #if (want assumption checking):

#include <util/fail_message.hpp>
#include <stdexcept>
#include <string>
struct assumption_failure : public std::logic_error 
{
    explicit assumption_failure(std::string const& msg) : std::logic_error(msg) {}
};
#define ASSUMPTION(C) do { if (!(C)) { [](){ throw assumption_failure(FAIL_MSG("Assumption failure.")); }(); }\
                         } while (false)

// #else define assumption as this:

// #define ASSUMPTION(C)

// #endif

#endif
