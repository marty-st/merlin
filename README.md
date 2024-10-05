Have installed:
MS Build Tools 2022
CMake
vcpkg:
    vcpkg install sdl2 glad glm boost gtest imgui[opengl3-binding,sdl2-binding] --clean-after-build
    On Windows append the option --triplet=x64-windows to the command
    run .bat script, in powershell as admin: .\vcpkg.exe integrate install
    in project dir: follow microsoft tutorial, and then vcpkg add port sdl2; vcpkg add port glad
(Git)

Followed these tutorials to set up the project:
https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vscode?pivots=shell-powershell
Note: set generator in CMakePresets.json as "Visual Studio 17 2022"

Video name: Getting Started with SDL2 C++ in Visual Studio using vcpkg
https://www.youtube.com/watch?v=NUiSyNALG60
Note: Not everything mentioned here is relevant