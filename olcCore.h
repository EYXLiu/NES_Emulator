#pragma once
#include <cstdint>
#include <vector>

namespace olc
{
    enum rcode { FAIL = 0, OK = 1 };

    struct Pixel
    {
        uint8_t r=0, g=0, b=0, a=255;
        Pixel() = default;
        Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=255) : r(red), g(green), b(blue), a(alpha) {};
        uint32_t PixelToUInt32() const { return (a << 24) | (r << 16) | (g << 8) | (b); };
    };

    static const Pixel
		GREY(192, 192, 192), DARK_GREY(128, 128, 128), VERY_DARK_GREY(64, 64, 64),
		RED(255, 0, 0), DARK_RED(128, 0, 0), VERY_DARK_RED(64, 0, 0),
		YELLOW(255, 255, 0), DARK_YELLOW(128, 128, 0), VERY_DARK_YELLOW(64, 64, 0),
		GREEN(0, 255, 0), DARK_GREEN(0, 128, 0), VERY_DARK_GREEN(0, 64, 0),
		CYAN(0, 255, 255), DARK_CYAN(0, 128, 128), VERY_DARK_CYAN(0, 64, 64),
		BLUE(0, 0, 255), DARK_BLUE(0, 0, 128), VERY_DARK_BLUE(0, 0, 64),
		MAGENTA(255, 0, 255), DARK_MAGENTA(128, 0, 128), VERY_DARK_MAGENTA(64, 0, 64),
		WHITE(255, 255, 255), BLACK(0, 0, 0), BLANK(0, 0, 0, 0);

    class Sprite
    {
    public:
        uint32_t width = 0;
        uint32_t height = 0;
        std::vector<Pixel> data;

        Sprite(uint32_t w, uint32_t h) : width(w), height(h) { data.resize(width * height); };
        
        bool SetPixel(uint32_t x, uint32_t y, Pixel p)
        {
            if (x < 0 || x >= width || y < 0 || y >= height) 
                return false;
            data[y * width + x] = p;
            return true;
        };

        Pixel GetPixel(uint32_t x, uint32_t y)
        {
            if (x < 0 || x >= width || y < 0 || y >= height) 
                return Pixel(0,0,0,0);
            return data[y * width + x];
        };
    };

    struct vi2d
    {
        int32_t x = 0;
        int32_t y = 0;

        vi2d() = default;
        vi2d(int32_t _x, int32_t _y) : x(_x), y(_y) {}

        vi2d operator+ (const vi2d& rhs) const { return { x + rhs.x, y + rhs.y }; }
        vi2d operator- (const vi2d& rhs) const { return { x - rhs.x, y - rhs.y }; }
        vi2d operator* (int32_t k) const { return { x * k, y * k }; }
        vi2d operator/ (int32_t k) const { return { x / k, y / k }; }

        bool operator== (const vi2d& rhs) const { return x == rhs.x && y == rhs.y; }
        bool operator!= (const vi2d& rhs) const { return !(*this == rhs); }
    };

    enum Key
	{
		NONE,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		UP, DOWN, LEFT, RIGHT,
		SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
		BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
		NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
		NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD,
		EQUALS, COMMA, MINUS,
		OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_8,
		CAPS_LOCK, ENUM_END
	};

    struct HWButton
    {
        bool bPressed = false;
        bool bReleased = false;
        bool bHeld = false;
    };

    class PixelGameEngine;

    class Platform 
    {
    public:
        virtual ~Platform() = default;
        virtual rcode ApplicationStartUp() = 0;
        virtual rcode ApplicationCleanUp() = 0;
        virtual rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const vi2d& vViewPos, const vi2d& vViewSize) = 0;
        virtual rcode CreateWindowPane(const vi2d& vWindowPos, bool bFullScreen) = 0;
        virtual rcode SetWindowTitle(const std::string& s) = 0;
        virtual rcode StartSystemEventLoop() = 0;
        virtual HWButton GetKey(int scancode) = 0;
        virtual rcode HandleSystemEvent(bool& running) = 0;
        virtual rcode PresentFrame(uint32_t* pixels, int width, int height) = 0;
        PixelGameEngine *pge = nullptr;
    };
}