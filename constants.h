#ifndef _CONSTANTS_H
#define _CONSTANTS_H

const int SCREEN_HEIGHT = 768;
const int SCREEN_WIDTH = 1248;
const int TILE_SIZE = 48;

const int top_wall[11][4]={
    {672, 432, 1344, 432},
    {1632, 432, 2112, 432},
    {1344, 624, 1632, 624},
    {624, 1488, 912, 1488},
    {1104, 1488, 1392, 1488},
    {1392, 1824, 1776, 1824},
    {1440, 1872, 1728, 1872},
    {1776, 1392, 2688, 1392},
    {2928, 1776, 3168, 1776},
    {2688, 912, 3216, 912},
    {3216, 672, 4224, 672}
};
const int bottom_wall[10][4]={
    {672, 1032, 912, 1032},
    {1104, 1032, 1344, 1032},
    {1344, 840, 1632, 840},
    {1632, 1032, 2112, 1032},
    {624, 2376, 1392, 2376},
    {1392, 2040, 1776, 2040},
    {1440, 1992, 1728, 1992},
    {1776, 2472, 3168, 2472},
    {2928, 1176, 3216, 1176},
    {3216, 1416, 4224, 1416}
};
const int left_wall[12][4]={
    {672, 384, 672, 1056},
    {1632, 384, 1632, 624},
    {1632, 840, 1632, 1056},
    {912, 1032, 912, 1488},
    {624, 1440, 624, 2400},
    {1728, 1776, 1728, 1848},
    {1728, 1992, 1728, 2064},
    {1776, 1344, 1776, 1824},
    {1776, 2040, 1776, 2544},
    {2688, 912, 2688, 1392},
    {3216, 624, 3216, 912},
    {3216, 1176, 3216, 1440}
};
const int right_wall[11][4]={
    {1344, 384, 1344, 624},
    {1344, 840, 1344, 1056},
    {2112, 384, 2112, 1056},
    {1104, 1032, 1104, 1488},
    {1392, 1440, 1392, 1824},
    {1392, 2040, 1392, 2400},
    {1440, 1776, 1440, 1848},
    {1440, 1992, 1440, 2064},
    {3168, 1728, 3168, 2544},
    {2928, 1176, 2928, 1776},
    {4224, 624, 4224, 1440}
};

const int mob_coordinates[2][2]={
    {1700, 500},
    {1700, 700}
};

#endif // _CONSTANTS_H
