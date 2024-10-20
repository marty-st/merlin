#ifndef FAIL_MESSAGE_INCLUDE
#define FAIL_MESSAGE_INCLUDE

#include <string>

// Code from: https://gitlab.fi.muni.cz/qtrtik/rofibots

#define FAIL_MSG(M) buildFailureMessage(__FILE__,__LINE__,__FUNCTION__,M)

std::string buildFailureMessage(char const* const file, int const line,
                                char const* const func, std::string const& msg);


#endif
