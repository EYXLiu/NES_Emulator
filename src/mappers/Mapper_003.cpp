#include "../../Mapper_003.h"

Mapper_003::Mapper_003(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks)
{
}

Mapper_003::~Mapper_003()
{
}

void Mapper_003::reset()
{
    nCHRBankSelect = 0;
}

bool Mapper_003::cpuMapRead(uint16_t addr, uint32_t &mapped_addr, uint8_t &data)
{
    if (addr >= 0x8000 && addr <= 0xFFFF)
    {
        if (nPrgBanks == 1)
            mapped_addr = addr & 0x3FFF;
        else if (nPrgBanks == 2)
            mapped_addr = addr & 0x7FFF;
        return true;
    }
    return false;
}

bool Mapper_003::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data)
{
    if (addr >= 0x8000 && addr <= 0xFFFF)
    {
        nCHRBankSelect = data & 0x3F;
        mapped_addr = addr;
    }
    return false;
}

bool Mapper_003::ppuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
    if (addr < 0x2000)
    {
        mapped_addr = nCHRBankSelect * 0x2000 + addr;
        return true;
    }
    return false;
}

bool Mapper_003::ppuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
    return false;
}
