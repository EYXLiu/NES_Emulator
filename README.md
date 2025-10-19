# To run
*This compiler is built solely for macOS* <br/>
Make sure you have sdl2 installed; `brew install sdl2` <br/>
In the `c_cpp_properties.json` file, add the path to the sdl2 to the includePath; `brew --prefix sdl2` <br/>
Only add up to `include`, since the import is `SDL2/SDL.h` <br/>
To run a .nes file, move the file into the directory <br/>
In `olcNES.h`, at the very top change the cartridge string to your nes file name <br/>
Compile an executable using `g++ -std=c++17 -Wall -Wextra -o em main.cpp ./src/*.cpp ./src/mappers/*.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2`, making sure that the -I and -L flages both map to the proper homebrew locations <br/>
Run the executable using the name provided <br/>

# Mappers
Includes mappers 000, 001, 002, 003, 004, 066 from https://www.nesdev.org/wiki/Mapper <br/>

# Issues
Audio does not currently work, likely to do with SDL2 -> also does not use audio because ow my ears <br/>
To test and fix audio, SDL2_Audio code is found in `olcPGEX.h` <br/>
In `olcNES.h`, change the `OnUserUpdate` function to emulate with audio and test then. <br/>

# Source References
https://web.archive.org/web/20221112220234if_/http://archive.6502.org/datasheets/rockwell_r65c00_microprocessors.pdf <br/>
https://www.nesdev.org/wiki/Nesdev_Wiki <br/>
https://www.nesdev.org/6502bugs.txt <br/>

# Nes NROM
https://www.nesdev.org/w/index.php/NROM

# Nes test roms
https://www.qmtpro.com/~nes/misc/nestest.txt <br/>
https://github.com/christopherpow/nes-test-roms/tree/master/other

# Credits
https://youtube.com/playlist?list=PLrOv9FMX8xJHqMvSGB_9G9nZZ_4IgteYf&si=J-i5mwQwBl6FgCou <br/>
