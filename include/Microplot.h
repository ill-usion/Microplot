#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <unordered_set>

typedef int8_t i8;
typedef uint8_t u8;

typedef int16_t i16;
typedef uint16_t u16;

typedef int32_t i32;
typedef uint32_t u32;

/// @brief Minimal point plotting class
class Microplot
{
private:
    /// @brief Only stores active points
    std::unordered_set<i32> points;

    /// @brief Canvas dimensions
    u16 canvw, canvh;

public:
    /// @brief Constructs a new canvas
    /// @param w Canvas width
    /// @param h Canvas height
    Microplot(i16 w, i16 h);

    /// @brief Plots a given point
    /// @param x Point x coordinate
    /// @param y Point y coordinate
    void point(i16 x, i16 y);

    /// @brief Plots a straight line from `(x0, y0)` to `(x1, y1)`
    /// @param x0 Point 0 x coordinate
    /// @param y0 Point 0 y coordinate
    /// @param x1 Point 1 x coordinate
    /// @param y1 Point 1 y coordinate
    void line(i16 x0, i16 y0, i16 x1, i16 y1);

    void bezier(i16 x0, i16 y0, i16 x1, i16 y1, i16 x2, i16 y2);

    /// @brief Convert the current plot to a bitmap
    /// @param bmp Bitmap array
    /// @param w Bitmap width
    /// @param h Bitmap height
    void toBitmap(u8 *bmp, u16 w, u16 h);

    /// @brief Clears current plot
    void clear();
    ~Microplot();

private:
    /// @brief Hashes/Packs the given coordinate
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @return 
    inline i32 hash(i16 x, i16 y);

    /// @brief Unhashes/Unpacks the given coordinate
    /// @param n Packed coordinate
    /// @param x Unpacked x coordinate destination
    /// @param y Unpacked y coordinate destination
    inline void unhash(i32 n, i16 &x, i16 &y);

    /// @brief Checks whether the given coordinate is within the canvas bounds
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @return True if the given coorindate is within the canvas bounds, otherwise false
    inline bool withinBounds(i16 x, i16 y);

    /// @brief Translates a 2d coordinate to a 1d array index based on the canvas dimensions
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @return 
    inline size_t ptToIdx(i16 x, i16 y);
};
