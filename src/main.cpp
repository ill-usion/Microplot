#include <iostream>
#include "Microplot.h"

#define W 75
#define H 25

void drawAscii(uint8_t *bmp, uint16_t w, uint16_t h)
{
    char c;
    for (uint16_t y = h - 1; y > 0; y--)
    {
        std::cout << '|';
        for (uint16_t x = 0; x < w; x++)
        {
            c = bmp[(y * w) + x] == 0xFF ? '#' : ' ';
            std::cout << c;
        }
        std::cout << std::endl;
    }

    for (int16_t i = 0; i < w; i++)
        std::cout << '-';
    std::cout << std::endl;
}

int main()
{
    Microplot plot(W, H);

    int16_t points[][2] = {{0, 0}, {5, 10}, {13, 7}, {25, 20}, {50, 5}, {W, H}};
    size_t nPoints = sizeof(points) / sizeof(points[0]);

    for (size_t i = 1; i < nPoints; i++)
    {
        int16_t *p1 = points[i - 1];
        int16_t *p2 = points[i];

        plot.line(p1[0], p1[1], p2[0], p2[1]);
    }

    uint8_t *bmp = (uint8_t *)malloc(sizeof(uint8_t) * W * H);
    plot.toBitmap(bmp, W, H);
    drawAscii(bmp, W, H);

    free(bmp);
    return 0;
}