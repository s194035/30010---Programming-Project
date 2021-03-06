#include "graphicsSheet.h"

// Graphics sheet.
const uint8_t graph[16][GRAPH_SIZE][GRAPH_SIZE] = {
    // [0] = player ship
{   {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 219, 219, 219, 000},
    {000, 219, 219, 219, 000},
    {219, 219, 000, 219, 219} },

    // [1] = player laser
{   {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000}  },

    // [2] = enemy 1
{   {000, 000, 000, 000, 000},
    {219, 000, 219, 000, 219},
    {000, 219, 219, 219, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 000, 000, 000}  },

    // [3] = enemy 2
{   {000, 000, 219, 000, 000},
    {000, 219, 219, 219, 000},
    {219, 000, 219, 000, 219},
    {219, 000, 000, 000, 219},
    {000, 219, 000, 219, 000}  },

    // [4] = enemy laser anim1
{   {000, 000, 000, 000, 000},
    {000, 219, 000, 219, 000},
    {000, 000, 219, 000, 000},
    {000, 219, 000, 219, 000},
    {000, 000, 000, 000, 000}  },

    // [5] = enemy laser anim2
{   {000, 000, 000, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 219, 219, 219, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 000, 000, 000}  },

    // [6] = powerup heart
{   {000, 219, 000, 219, 000},
    {219, 177, 219, 177, 219},
    {219, 177, 177, 177, 219},
    {000, 219, 177, 219, 000},
    {000, 000, 219, 000, 000}  },

    // [7] = reserving mem
{   {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000}  },

    // [8] = reserving mem
{   {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000}  },

    // [9] = reserving mem
{   {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000}  },

    // [10] = reserving mem
{   {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000}  },

    // [11] = reserving mem
{   {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000},
    {000, 000, 219, 000, 000}  },

    // [12] = stars
{   {000, 176, 000, 000, 000},
    {176, 177, 176, 000, 000},
    {000, 176, 000, 000, 000},
    {000, 000, 000, 176, 000},
    {000, 000, 000, 000, 000}  },

    // [13] = space dust
{   {176, 000, 176, 177, 000},
    {177, 177, 176, 176, 177},
    {000, 176, 177, 177, 176},
    {176, 176, 176, 000, 176},
    {000, 177, 176, 176, 177}  },

    // [14] = space dust corner
{   {176, 000, 177, 176, 176},
    {000, 177, 176, 176, 000},
    {000, 000, 177, 176, 177},
    {000, 176, 000, 177, 000},
    {000, 000, 000, 000, 000}  },

    // [15] = space dust corner 2
{   {177, 176, 176, 177, 176},
    {000, 176, 177, 000, 176},
    {000, 000, 176, 176, 000},
    {000, 000, 177, 000, 176},
    {000, 177, 000, 000, 176}  }

};

