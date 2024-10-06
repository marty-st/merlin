#include <iostream>

#include <osi/run.hpp>

int main(int argc, char* argv[])
{
    try
    {
        osi::start();

        osi::run();

        osi::finish();
    }

    catch(const std::exception& e)
    {
        osi::finish();
        std::cerr << e.what() << '\n';
    }

    return 0;
}
