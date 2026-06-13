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

void Microplot::bezier(i16 x0, i16 y0, i16 x1, i16 y1, i16 x2, i16 y2)
{
    i16 sx = x2 - x1, sy = y2 - y1;
    i32 xx = x0 - x1, yy = y0 - y1, xy;
    double dx, dy, err, cur = xx * sy - yy * sx;

    if (!(xx * sx <= 0 && yy * sy <= 0))
        return;

    if (sx * (i32)sx + sy * (i32)sy > xx * xx + yy * yy)
    {
        x2 = x0;
        x0 = sx + x1;
        y2 = y0;
        y0 = sy + y1;
        cur = -cur;
    }
    if (cur != 0)
    {
        xx += sx;
        xx *= sx = x0 < x2 ? 1 : -1;
        yy += sy;
        yy *= sy = y0 < y2 ? 1 : -1;
        xy = 2 * xx * yy;
        xx *= xx;
        yy *= yy;
        if (cur * sx * sy < 0)
        {
            xx = -xx;
            yy = -yy;
            xy = -xy;
            cur = -cur;
        }
        dx = 4.0 * sy * cur * (x1 - x0) + xx - xy;
        dy = 4.0 * sx * cur * (y0 - y1) + yy - xy;
        xx += xx;
        yy += yy;
        err = dx + dy + xy;
        do
        {
            point(x0, y0);
            if (x0 == x2 && y0 == y2)
                return;
            y1 = 2 * err < dx;
            if (2 * err > dy)
            {
                x0 += sx;
                dx -= xy;
                err += dy += yy;
            }
            if (y1)
            {
                y0 += sy;
                dy -= xy;
                err += dx += xx;
            }
        } while (dy < dx);
    }
    line(x0, y0, x2, y2);
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