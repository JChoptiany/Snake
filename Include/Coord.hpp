#pragma once

struct Coord
{
    Coord(const unsigned& x, const unsigned& y)
            :x(x), y(y)
    {
    }

    unsigned x;
    unsigned y;
};