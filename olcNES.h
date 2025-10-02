#include "olcSDL2.h"
#include "Bus.h"
#include "font8x8_basic.h"

#include <memory>
#include <map>
#include <string>

class NES : public olc::PixelGameEngine
{
public:
    NES() : PixelGameEngine(new olc::Platform_SDL2) {};
private:
    Bus nes;
	std::shared_ptr<Cartridge> cart;
	bool bEmulationRun = false;
    float fResidualTime = 0.0f;

    std::map<uint16_t,std::string> mapAsm;

	uint8_t nSelectedPalette = 0x00;

    std::string hex(uint32_t n, uint8_t d) {
        std::string s(d,'0');
        for(int i=d-1;i>=0;i--, n>>=4)
            s[i] = "0123456789ABCDEF"[n & 0xF];
        return s;
    }

    void DrawRam(int x, int y, uint16_t nAddr, int nRows, int nColumns)
	{
		int nRamX = x, nRamY = y;
		for (int row = 0; row < nRows; row++)
		{
			std::string sOffset = "$" + hex(nAddr, 4) + ":";
			for (int col = 0; col < nColumns; col++)
			{
				sOffset += " " + hex(nes.cpuRead(nAddr, true), 2);
				nAddr += 1;
			}
			DrawString(nRamX, nRamY, sOffset);
			nRamY += 10;
		}
	}

    void DrawCpu(int x, int y)
	{
		std::string status = "STATUS: ";
		DrawString(x , y , "STATUS:", olc::WHITE);
		DrawString(x  + 64, y, "N", nes.cpu.status & olc6502::N ? olc::GREEN : olc::RED);
		DrawString(x  + 80, y , "V", nes.cpu.status & olc6502::V ? olc::GREEN : olc::RED);
		DrawString(x  + 96, y , "-", nes.cpu.status & olc6502::U ? olc::GREEN : olc::RED);
		DrawString(x  + 112, y , "B", nes.cpu.status & olc6502::B ? olc::GREEN : olc::RED);
		DrawString(x  + 128, y , "D", nes.cpu.status & olc6502::D ? olc::GREEN : olc::RED);
		DrawString(x  + 144, y , "I", nes.cpu.status & olc6502::I ? olc::GREEN : olc::RED);
		DrawString(x  + 160, y , "Z", nes.cpu.status & olc6502::Z ? olc::GREEN : olc::RED);
		DrawString(x  + 178, y , "C", nes.cpu.status & olc6502::C ? olc::GREEN : olc::RED);
		DrawString(x , y + 10, "PC: $" + hex(nes.cpu.pc, 4));
		DrawString(x , y + 20, "A: $" +  hex(nes.cpu.a, 2) + "  [" + std::to_string(nes.cpu.a) + "]");
		DrawString(x , y + 30, "X: $" +  hex(nes.cpu.x, 2) + "  [" + std::to_string(nes.cpu.x) + "]");
		DrawString(x , y + 40, "Y: $" +  hex(nes.cpu.y, 2) + "  [" + std::to_string(nes.cpu.y) + "]");
		DrawString(x , y + 50, "Stack P: $" + hex(nes.cpu.stkp, 4));
	}

    void DrawString(int x, int y, const std::string& text, olc::Pixel p = olc::WHITE) {
        for(size_t i=0;i<text.size();i++)
            DrawChar(x+i*8,y, text[i], p);
    }

	void DrawChar(int x, int y, char c, olc::Pixel p = olc::WHITE) {
		const uint8_t* glyph = reinterpret_cast<const uint8_t*>(font8x8_basic[c]);
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				if (glyph[row] & (1 << col)) DrawPixel(x + col, y + row, p);
			}
    	}
	}

    void DrawCode(int x, int y, int nLines)
	{
		auto it_a = mapAsm.find(nes.cpu.pc);
		if (it_a == mapAsm.end()) return;

		int nLineY = (nLines >> 1) * 10 + y;
		DrawString(x, nLineY, (*it_a).second, olc::CYAN);
		auto it_forward = it_a;
		int lineY = nLineY;
		while (lineY < (nLines * 10) + y)
		{
			++it_forward;
			if (it_forward == mapAsm.end()) break;
			lineY += 10;
			DrawString(x, lineY, it_forward->second);
		}


		auto it_backward = it_a;
		lineY = nLineY;
		while (lineY > y)
		{
			if (it_backward == mapAsm.begin()) break;
			--it_backward;
			lineY -= 10;
			DrawString(x, lineY, it_backward->second);
		}
	}

public:
    bool OnUserCreate() override
    {
        cart = std::make_shared<Cartridge>("dk.nes");
        nes.insertCartridge(cart);
        mapAsm = nes.cpu.disassemble(0x0000,0xFFFF);
        nes.reset();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::DARK_BLUE);	

        if (bEmulationRun)
        {
            if (fResidualTime > 0.0f)
				fResidualTime -= fElapsedTime;
			else
			{
				fResidualTime += (1.0f / 60.0f) - fElapsedTime;
				do { nes.clock(); } while (!nes.ppu.frame_complete);
				nes.ppu.frame_complete = false;
			}
        }
        else 
        {
            if (GetKey(olc::Key::C).bPressed)
            {
                do { nes.clock(); } while (!nes.cpu.complete());
                do { nes.clock(); } while (nes.cpu.complete());
            }


            if (GetKey(olc::Key::F).bPressed)
            {
                do { nes.clock(); } while (!nes.ppu.frame_complete);
                do { nes.clock(); } while (!nes.cpu.complete());
                nes.ppu.frame_complete = false;
            }
        }

        if (GetKey(olc::Key::SPACE).bPressed) bEmulationRun = !bEmulationRun;
		if (GetKey(olc::Key::R).bPressed) nes.reset();

		if (GetKey(olc::Key::P).bPressed) (++nSelectedPalette) &= 0x07;


        DrawCpu(516, 2);
		DrawCode(516, 72, 26);

		const int nSwatchSize = 6;
		for (int p = 0; p < 8; p++) // For each palette
			for(int s = 0; s < 4; s++) // For each index
				FillRect(516 + p * (nSwatchSize * 5) + s * nSwatchSize, 340, 
					nSwatchSize, nSwatchSize, nes.ppu.GetColourFromPaletteRam(p, s));
		
		// Draw selection reticule around selected palette
		DrawRect(516 + nSelectedPalette * (nSwatchSize * 5) - 1, 339, (nSwatchSize * 4), nSwatchSize, olc::WHITE);


		DrawSprite(516, 348, &nes.ppu.GetPatternTable(0, nSelectedPalette));
		DrawSprite(648, 348, &nes.ppu.GetPatternTable(1, nSelectedPalette));

		DrawSprite(0, 0, &nes.ppu.GetScreen(), 2);

		// olc::Sprite& s = nes.ppu.GetPatternTable(0, nSelectedPalette);
		// for (uint8_t y = 0; y < 30; y++)
		// 	for (uint8_t x = 0; x < 32; x++)
		// 	{
		// 		//DrawString(x * 16, y * 16, hex((uint32_t)nes.ppu.tblName[0][y * 32 + x], 2));
		// 		uint8_t id = (uint32_t)nes.ppu.tblName[0][y * 32 + x];
		// 		DrawPartialSprite(x * 16, y * 16, &s, (id & 0x0F) << 3, ((id >> 4) & 0x0F) << 3, 8, 8, 2);
		// 	}
		return true;
    } 
};