#include "../olc6502.h"
#include "../Bus.h"

uint8_t olc6502::GetFlag(FLAGS6502 f)
{
    return ((status & f) > 0) ? 1 : 0;
}

void olc6502::SetFlag(FLAGS6502 f, bool v)
{
    if (v)
        status |= f;
    else
        status &= ~f;
}