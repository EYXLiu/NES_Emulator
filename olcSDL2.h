#pragma once

#include "olcCore.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <map>

namespace olc
{
    class Platform_SDL2 : public Platform
    {
    public:
        Platform_SDL2()
        {
            // Letters A-Z
            keyMap[olc::Key::A] = SDL_SCANCODE_A;
            keyMap[olc::Key::B] = SDL_SCANCODE_B;
            keyMap[olc::Key::C] = SDL_SCANCODE_C;
            keyMap[olc::Key::D] = SDL_SCANCODE_D;
            keyMap[olc::Key::E] = SDL_SCANCODE_E;
            keyMap[olc::Key::F] = SDL_SCANCODE_F;
            keyMap[olc::Key::G] = SDL_SCANCODE_G;
            keyMap[olc::Key::H] = SDL_SCANCODE_H;
            keyMap[olc::Key::I] = SDL_SCANCODE_I;
            keyMap[olc::Key::J] = SDL_SCANCODE_J;
            keyMap[olc::Key::K] = SDL_SCANCODE_K;
            keyMap[olc::Key::L] = SDL_SCANCODE_L;
            keyMap[olc::Key::M] = SDL_SCANCODE_M;
            keyMap[olc::Key::N] = SDL_SCANCODE_N;
            keyMap[olc::Key::O] = SDL_SCANCODE_O;
            keyMap[olc::Key::P] = SDL_SCANCODE_P;
            keyMap[olc::Key::Q] = SDL_SCANCODE_Q;
            keyMap[olc::Key::R] = SDL_SCANCODE_R;
            keyMap[olc::Key::S] = SDL_SCANCODE_S;
            keyMap[olc::Key::T] = SDL_SCANCODE_T;
            keyMap[olc::Key::U] = SDL_SCANCODE_U;
            keyMap[olc::Key::V] = SDL_SCANCODE_V;
            keyMap[olc::Key::W] = SDL_SCANCODE_W;
            keyMap[olc::Key::X] = SDL_SCANCODE_X;
            keyMap[olc::Key::Y] = SDL_SCANCODE_Y;
            keyMap[olc::Key::Z] = SDL_SCANCODE_Z;

            // Numbers 0-9
            keyMap[olc::Key::K0] = SDL_SCANCODE_0;
            keyMap[olc::Key::K1] = SDL_SCANCODE_1;
            keyMap[olc::Key::K2] = SDL_SCANCODE_2;
            keyMap[olc::Key::K3] = SDL_SCANCODE_3;
            keyMap[olc::Key::K4] = SDL_SCANCODE_4;
            keyMap[olc::Key::K5] = SDL_SCANCODE_5;
            keyMap[olc::Key::K6] = SDL_SCANCODE_6;
            keyMap[olc::Key::K7] = SDL_SCANCODE_7;
            keyMap[olc::Key::K8] = SDL_SCANCODE_8;
            keyMap[olc::Key::K9] = SDL_SCANCODE_9;

            // Numpad 0-9
            keyMap[olc::Key::NP0] = SDL_SCANCODE_KP_0;
            keyMap[olc::Key::NP1] = SDL_SCANCODE_KP_1;
            keyMap[olc::Key::NP2] = SDL_SCANCODE_KP_2;
            keyMap[olc::Key::NP3] = SDL_SCANCODE_KP_3;
            keyMap[olc::Key::NP4] = SDL_SCANCODE_KP_4;
            keyMap[olc::Key::NP5] = SDL_SCANCODE_KP_5;
            keyMap[olc::Key::NP6] = SDL_SCANCODE_KP_6;
            keyMap[olc::Key::NP7] = SDL_SCANCODE_KP_7;
            keyMap[olc::Key::NP8] = SDL_SCANCODE_KP_8;
            keyMap[olc::Key::NP9] = SDL_SCANCODE_KP_9;

            // Numpad operators
            keyMap[olc::Key::NP_MUL] = SDL_SCANCODE_KP_MULTIPLY;
            keyMap[olc::Key::NP_DIV] = SDL_SCANCODE_KP_DIVIDE;
            keyMap[olc::Key::NP_ADD] = SDL_SCANCODE_KP_PLUS;
            keyMap[olc::Key::NP_SUB] = SDL_SCANCODE_KP_MINUS;
            keyMap[olc::Key::NP_DECIMAL] = SDL_SCANCODE_KP_DECIMAL;

            // Function keys F1-F12
            keyMap[olc::Key::F1]  = SDL_SCANCODE_F1;
            keyMap[olc::Key::F2]  = SDL_SCANCODE_F2;
            keyMap[olc::Key::F3]  = SDL_SCANCODE_F3;
            keyMap[olc::Key::F4]  = SDL_SCANCODE_F4;
            keyMap[olc::Key::F5]  = SDL_SCANCODE_F5;
            keyMap[olc::Key::F6]  = SDL_SCANCODE_F6;
            keyMap[olc::Key::F7]  = SDL_SCANCODE_F7;
            keyMap[olc::Key::F8]  = SDL_SCANCODE_F8;
            keyMap[olc::Key::F9]  = SDL_SCANCODE_F9;
            keyMap[olc::Key::F10] = SDL_SCANCODE_F10;
            keyMap[olc::Key::F11] = SDL_SCANCODE_F11;
            keyMap[olc::Key::F12] = SDL_SCANCODE_F12;

            // Arrows
            keyMap[olc::Key::UP] = SDL_SCANCODE_UP;
            keyMap[olc::Key::DOWN] = SDL_SCANCODE_DOWN;
            keyMap[olc::Key::LEFT] = SDL_SCANCODE_LEFT;
            keyMap[olc::Key::RIGHT] = SDL_SCANCODE_RIGHT;

            // Common keys
            keyMap[olc::Key::SPACE] = SDL_SCANCODE_SPACE;
            keyMap[olc::Key::TAB] = SDL_SCANCODE_TAB;
            keyMap[olc::Key::SHIFT] = SDL_SCANCODE_LSHIFT;
            keyMap[olc::Key::CTRL] = SDL_SCANCODE_LCTRL;
            keyMap[olc::Key::INS] = SDL_SCANCODE_INSERT;
            keyMap[olc::Key::DEL] = SDL_SCANCODE_DELETE;
            keyMap[olc::Key::HOME] = SDL_SCANCODE_HOME;
            keyMap[olc::Key::END] = SDL_SCANCODE_END;
            keyMap[olc::Key::PGUP] = SDL_SCANCODE_PAGEUP;
            keyMap[olc::Key::PGDN] = SDL_SCANCODE_PAGEDOWN;
            keyMap[olc::Key::BACK] = SDL_SCANCODE_BACKSPACE;
            keyMap[olc::Key::ESCAPE] = SDL_SCANCODE_ESCAPE;
            keyMap[olc::Key::RETURN] = SDL_SCANCODE_RETURN;
            keyMap[olc::Key::ENTER] = SDL_SCANCODE_RETURN;  // same as RETURN
            keyMap[olc::Key::PAUSE] = SDL_SCANCODE_PAUSE;
            keyMap[olc::Key::SCROLL] = SDL_SCANCODE_SCROLLLOCK;

            // Symbols / OEM keys (common US layout)
            keyMap[olc::Key::PERIOD] = SDL_SCANCODE_PERIOD;
            keyMap[olc::Key::MINUS] = SDL_SCANCODE_MINUS;
            keyMap[olc::Key::EQUALS] = SDL_SCANCODE_EQUALS;
            keyMap[olc::Key::COMMA] = SDL_SCANCODE_COMMA;
            keyMap[olc::Key::OEM_1] = SDL_SCANCODE_SEMICOLON;   // ;
            keyMap[olc::Key::OEM_2] = SDL_SCANCODE_SLASH;       // /
            keyMap[olc::Key::OEM_3] = SDL_SCANCODE_GRAVE;       // `
            keyMap[olc::Key::OEM_4] = SDL_SCANCODE_LEFTBRACKET; // [
            keyMap[olc::Key::OEM_5] = SDL_SCANCODE_BACKSLASH;   // 
            keyMap[olc::Key::OEM_6] = SDL_SCANCODE_RIGHTBRACKET;// ]
            keyMap[olc::Key::OEM_7] = SDL_SCANCODE_APOSTROPHE;  // '
            keyMap[olc::Key::OEM_8] = SDL_SCANCODE_UNKNOWN;     // optional

            // Caps Lock
            keyMap[olc::Key::CAPS_LOCK] = SDL_SCANCODE_CAPSLOCK;
        }
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* frameTexture = nullptr;
        HWButton keys[olc::Key::ENUM_END];
        std::map<int, SDL_Scancode> keyMap;

        rcode ApplicationStartUp() override {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) return FAIL;
            return OK;
        }

        rcode ApplicationCleanUp() override {
            SDL_Quit();
            if (frameTexture) SDL_DestroyTexture(frameTexture);
            if (renderer) SDL_DestroyRenderer(renderer);
            if (window) SDL_DestroyWindow(window);
            return OK;
        }
        
        rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const vi2d& vResolution, const vi2d& vPixelSize) override 
        {
            //nothing unless using opengl
            return OK;
        }

        rcode CreateWindowPane(const vi2d& vWindowPos, bool bFullScreen) override 
        {
            Uint32 flags = SDL_WINDOW_SHOWN;

            if (bFullScreen) flags |= SDL_WINDOW_FULLSCREEN;

            window = SDL_CreateWindow("olc6502 SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, vWindowPos.x, vWindowPos.y, flags);
            if (!window) return FAIL;

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (!renderer) return FAIL;

            return OK;
        }

        rcode SetWindowTitle(const std::string& s) override
        {
            SDL_SetWindowTitle(window, s.c_str());
            return OK;
        }

        rcode StartSystemEventLoop() override
        {
            //sdl autostarts
            return OK;
        }

        HWButton GetKey(int scancode) override
        {
            return keys[scancode];
        }

        rcode HandleSystemEvent(bool& running) override
        {
            for (auto &btn : keys)
            {
                btn.bPressed = false;
                btn.bReleased = false;
            }

            SDL_Event event;
            while (SDL_PollEvent(&event)) 
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                        running = false;
                        return FAIL;

                    case SDL_KEYDOWN:
                    case SDL_KEYUP:
                    {
                        bool pressed = (event.type == SDL_KEYDOWN);
                        SDL_Scancode sc = event.key.keysym.scancode;

                        for(auto &pair : keyMap)
                        {
                            int k = pair.first;
                            SDL_Scancode mapped = pair.second;
                            if(sc == mapped)
                            {
                                HWButton &btn = keys[k];

                                if (pressed)
                                {
                                    if (!btn.bHeld) btn.bPressed = true;
                                    btn.bHeld = true;
                                }
                                else
                                {
                                    if (btn.bHeld) btn.bReleased = true;
                                    btn.bHeld = false;
                                }
                            }
                        }
                        break;
                    }

                    // case SDL_MOUSEBUTTONDOWN:
                    // case SDL_MOUSEBUTTONUP:
                    // case SDL_MOUSEMOTION:
                }
            }

            return OK;
        }

        rcode PresentFrame(uint32_t* pixels, int width, int height) override
        {
            if (!frameTexture)
            {
                frameTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
                if (!frameTexture) return FAIL;
            }

            SDL_UpdateTexture(frameTexture, nullptr, pixels, width * sizeof(uint32_t));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, frameTexture, nullptr, nullptr);
            SDL_RenderPresent(renderer);
            return OK;
        }
    };

    class PGEX;

    class PixelGameEngine
    {
    protected:
        Platform* platform;
        int screenWidth, screenHeight;
        std::vector<Pixel> framebuffer;
        bool running = false;

    public:
        PixelGameEngine(Platform* plat) : platform(plat) { platform->pge = this; }

        rcode Construct(int w, int h)
        {
            screenWidth = w;
            screenHeight = h;
            framebuffer.resize(screenWidth * screenHeight, BLACK);
            return platform->CreateWindowPane(vi2d(w, h), false);
        }

        rcode DrawPixel(int x, int y, Pixel p)
        {
            if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight) return FAIL;
            framebuffer[y*screenWidth + x] = p;
            return OK;
        }

        rcode Clear(Pixel p) { std::fill(framebuffer.begin(), framebuffer.end(), p); return OK; }

        rcode DrawSprite(int x, int y, Sprite* sprite, int scale = 1)
        {
            if (!sprite) return FAIL;

            for (uint32_t j = 0; j < sprite->height; j++)
            {
                int py = y + j * scale;
                if (py < 0 || py >= screenHeight) continue;

                for (uint32_t i = 0; i < sprite->width; i++)
                {
                    int px = x + i * scale;
                    if (px < 0 || px >= screenWidth) continue;

                    Pixel p = sprite->GetPixel(i, j);
                    for (int sy = 0; sy < scale; sy++)
                    {
                        int fy = py + sy;
                        if (fy < 0 || fy >= screenHeight) continue;

                        for (int sx = 0; sx < scale; sx++)
                        {
                            int fx = px + sx;
                            if (fx < 0 || fx >= screenWidth) continue;

                            framebuffer[fy * screenWidth + fx] = p;
                        }
                    }
                }
            }

            return OK;
        }

        rcode DrawPartialSprite(int x, int y, Sprite* sprite, int ox, int oy, int w, int h, int scale = 1)
        {
            if (!sprite) return FAIL;

            // Clip source rectangle to sprite bounds
            if (ox < 0) { w += ox; x -= ox; ox = 0; }
            if (oy < 0) { h += oy; y -= oy; oy = 0; }
            if (ox + w > (int)sprite->width) w = sprite->width - ox;
            if (oy + h > (int)sprite->height) h = sprite->height - oy;
            if (w <= 0 || h <= 0) return FAIL;

            for (int j = 0; j < h; j++)
            {
                int py = y + j * scale;
                if (py < 0 || py >= screenHeight) continue;

                for (int i = 0; i < w; i++)
                {
                    int px = x + i * scale;
                    if (px < 0 || px >= screenWidth) continue;

                    Pixel p = sprite->GetPixel(ox + i, oy + j);
                    for (int sy = 0; sy < scale; sy++)
                    {
                        int fy = py + sy;
                        if (fy < 0 || fy >= screenHeight) continue;

                        for (int sx = 0; sx < scale; sx++)
                        {
                            int fx = px + sx;
                            if (fx < 0 || fx >= screenWidth) continue;

                            framebuffer[fy * screenWidth + fx] = p;
                        }
                    }
                }
            }

            return OK;
        }

        rcode FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p)
        {
            if (w <= 0 || h <= 0) return OK;

            int32_t x2 = x + w;
            int32_t y2 = y + h;

            // Clip to screen
            if (x < 0) x = 0;
            if (y < 0) y = 0;
            if (x2 > (int32_t)screenWidth) x2 = (int32_t)screenWidth;
            if (y2 > (int32_t)screenHeight) y2 = (int32_t)screenHeight;

            // If rectangle is fully outside screen, do nothing
            if (x >= x2 || y >= y2) return OK;

            for (int i = x; i < x2; i++)
                for (int j = y; j < y2; j++)
                    DrawPixel(i, j, p);

            return OK;
        }

        rcode DrawLine(int x0, int y0, int x1, int y1, Pixel p) {
            int dx = std::abs(x1 - x0);
            int dy = std::abs(y1 - y0);
            int sx = (x0 < x1) ? 1 : -1;
            int sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;

            while (true) {
                DrawPixel(x0, y0, p); // Draw the pixel

                if (x0 == x1 && y0 == y1) break;

                int e2 = 2 * err;
                if (e2 > -dy) {
                    err -= dy;
                    x0 += sx;
                }
                if (e2 < dx) {
                    err += dx;
                    y0 += sy;
                }
            }
            return OK;
        }

        rcode DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p)
        {
            DrawLine(x, y, x + w, y, p);
            DrawLine(x + w, y, x + w, y + h, p);
            DrawLine(x + w, y + h, x, y + h, p);
            DrawLine(x, y + h, x, y, p);
            
            return OK;
        }

        HWButton GetKey(int scancode) { return platform->GetKey(scancode); }

        rcode Start()
        {
            if (!OnUserCreate()) return FAIL;
            running = true;
            while (running)
            {
                platform->HandleSystemEvent(running);
                if(!OnUserUpdate(1.0f/60.0f)) running=false;

                std::vector<uint32_t> pixels(screenWidth*screenHeight);
                for(int i=0;i<screenWidth*screenHeight;i++)
                    pixels[i] = (framebuffer[i].PixelToUInt32());

                platform->PresentFrame(pixels.data(), screenWidth, screenHeight);
            }
            platform->ApplicationCleanUp();
            return OK;
        }

        virtual bool OnUserCreate() { return true; }
        virtual bool OnUserDestroy() { return true; }
        virtual bool OnUserUpdate(float fElapsedTime) { return true; }

        friend class PGEX;
        void PGEX_Register(olc::PGEX* pgex);

    private:
        std::vector<olc::PGEX*> vExtensions;
    };
}
