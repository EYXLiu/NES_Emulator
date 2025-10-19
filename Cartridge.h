#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

#include "Mapper_000.h"
#include "Mapper_001.h"
#include "Mapper_002.h"
#include "Mapper_003.h"
#include "Mapper_004.h"
#include "Mapper_066.h"

class Cartridge
{
private:
    std::vector<uint8_t> vPRGMemory;
    std::vector<uint8_t> vCHRMemory;

    uint8_t nMapperID = 0;
    uint8_t nPRGBanks = 0;
    uint8_t nCHRBanks = 0;

    std::shared_ptr<Mapper> pMapper;
    bool bImageValid = false;

    MIRROR hw_mirror = HORIZONTAL;

public:
    Cartridge(const std::string& sFileName);
    ~Cartridge();

    bool cpuRead(uint16_t addr, uint8_t &data);
    bool cpuWrite(uint16_t addr, uint8_t data);

    bool ppuRead(uint16_t addr, uint8_t &data);
    bool ppuWrite(uint16_t addr, uint8_t data);

    void reset();
    bool ImageValid();

    MIRROR Mirror();

	std::shared_ptr<Mapper> GetMapper();
};
