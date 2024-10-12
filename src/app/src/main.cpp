#include <osi/run.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        osi::run();
    }
    catch(const std::exception& e)
    {
        osi::finish();
        std::cerr << e.what() << '\n';
    }

    return 0;
}
