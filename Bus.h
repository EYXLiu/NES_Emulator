#pragma once
#include "olc6502.h"
#include "olc2C02.h"
#include "Cartridge.h"
#include <cstdint>
#include <array>
#include <iostream>
#include <memory>

#define RAM_SIZE 2048;

class Bus
{
private:
    uint32_t nSystemClockCounter = 0;

    uint8_t controller_state[2];

    uint8_t dma_page = 0x00;
    uint8_t dma_addr = 0x00;
    uint8_t dma_data = 0x00;

    bool dma_transfer = false;
    bool dma_dummy = true;

public:
    olc6502 cpu;
    olc2C02 ppu;
    std::array<uint8_t, 2048> cpuRam;


    std::shared_ptr<Cartridge> cart;

    uint8_t controller[2];

public:
    Bus();
    ~Bus();

    void run();

    void disassemble(uint16_t nStart, uint16_t nStop);

    uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);
    void cpuWrite(uint16_t addr, uint8_t data);

    //system interface
    void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
    void reset();
    void clock();
};
