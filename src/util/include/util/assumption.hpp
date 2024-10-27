#ifndef ASSUMPTION_INCLUDE
#define ASSUMPTION_INCLUDE

// Code from: https://gitlab.fi.muni.cz/qtrtik/rofibots

// #if (want assumption checking):

#include <util/fail_message.hpp>
#include <stdexcept>
#include <string>
struct assumption_failure : public std::logic_error 
{
    explicit assumption_failure(std::string const& msg) : std::logic_error(msg) {}
};
#define ASSUME(C) do { if (!(C)) { [](){ throw assumption_failure(FAIL_MSG("Assumption failure.")); }(); }\
                         } while (false)

// #else define assumption as this:

// #define ASSUME(C)

// #endif

#endif // ASSUMPTION_INCLUDE
