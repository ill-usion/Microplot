#include "Microplot.h"

Microplot::Microplot(i16 w, i16 h)
{
    canvw = w;
    canvh = h;
}

void Microplot::point(i16 x, i16 y)
{
    points.emplace(hash(x, y));
}

void Microplot::line(i16 x0, i16 y0, i16 x1, i16 y1)
{
    i16 dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    i16 dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    i16 err = dx + dy, e2;

    while (true)
    {
        point(x0, y0);
        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
void Microplot::toBitmap(u8 *bmp, u16 w, u16 h)
{
    static i16 x, y;
    for (i32 p : points)
    {
        unhash(p, x, y);
        if (!withinBounds(x, y) || x >= w || y >= h)
            continue;

        bmp[ptToIdx(x, y)] = 0xFF;
    }
}

void Microplot::clear()
{
    points.clear();
}

Microplot::~Microplot()
{
}

inline i32 Microplot::hash(i16 x, i16 y)
{
    return ((i32)y << 16) | (i32)x;
}

inline void Microplot::unhash(i32 n, i16 &x, i16 &y)
{
    x = n & 0xFFFF;
    y = (n >> 16) & 0xFFFF;
}

inline bool Microplot::withinBounds(i16 x, i16 y)
{
    return x >= 0 && y >= 0 && x <= canvw && y <= canvh;
}

inline size_t Microplot::ptToIdx(i16 x, i16 y)
{
    return (y * canvw) + x;
}