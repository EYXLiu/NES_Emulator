#include "Bus.h"
#include "olcNES.h"

#include <stdint.h>
#include <iostream>

int main()
{
    NES nes;

    if (nes.Construct(760, 480) == olc::OK)
    {
        nes.Start();
    }

    return 0;
}