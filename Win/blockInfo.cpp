/*
Copyright (c) 2014, Eric Haines
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "stdafx.h"

bool gDebug = false;

MaterialCost gMtlCostTable[MTL_COST_TABLE_SIZE]={
    // wname                 name                  Currency minWall in meters  minSum in meters    costH  costPerCCM cDens    cDisCCM  costMinimum?  costMachCC maxSizeCM (descending order)
    { L"White & Flexible",   "white & flexible",   L"$", 0.7f*MM_TO_METERS, 7.5f*MM_TO_METERS,  1.50f, 0.28f,    999.0f, 99999.0f,  1.50f*0.10f,  0.21f,     65.0f,55.0f,35.0f },
    { L"Colored Sandstone",  "colored sandstone",  L"$", 2.0f*MM_TO_METERS, 10.0f*MM_TO_METERS, 3.00f, 0.75f,    999.0f, 99999.0f,  3.00f*0.134f, 0.0f,      38.0f,25.0f,20.0f },
    { L"Full Color Plastic", "full color plastic", L"$", 0.7f*MM_TO_METERS, 10.0f*MM_TO_METERS, 3.00f, 2.00f,    999.0f, 99999.0f,  3.00f*0.134f, 0.0f,      15.0f,15.0f,15.0f },
    { L"Colored & Flexible", "colored & flexible", L"$", 0.7f*MM_TO_METERS, 7.5f*MM_TO_METERS,  2.25f, 0.28f,    999.0f, 99999.0f,  2.25f*0.10f,  0.21f,     65.0f,55.0f,35.0f },
    { L"Brass/Bronze",       "brass/bronze",       L"$", 0.8f*MM_TO_METERS, 3.4f*MM_TO_METERS,  10.0f, 16.0f,    999.0f, 99999.0f, 10.0f *0.10f,  0.0f,      10.0f, 8.9f, 8.9f },
    { L"Castable Wax",       "castable wax",       L"$", 0.6f*MM_TO_METERS, 12.0f*MM_TO_METERS, 10.0f, 8.0f,     999.0f, 99999.0f, 10.0f *0.10f,  0.0f,      75.0f,75.0f,50.0f },
    { L"Ceramics",           "ceramics",           L"$", 3.0f*MM_TO_METERS, 120.0f*MM_TO_METERS,6.00f, 0.35f,    999.0f, 99999.0f,  6.00f,        0.0f,      30.0f,22.0f,17.0f },
    { L"Detailed Plastic",   "alumide/detail",	   L"$", 1.0f*MM_TO_METERS, 6.25f*MM_TO_METERS, 2.50f, 2.99f,    999.0f, 99999.0f,  2.50f*0.10f,  0.0f,      25.0f,25.0f,20.0f },
    { L"Elasto Plastic",     "elasto plastic",     L"$", 0.8f*MM_TO_METERS, 10.0f*MM_TO_METERS, 1.50f, 0.42f,    999.0f, 99999.0f,  1.95f*0.10f,  0.26f,     30.0f,30.0f,25.0f },
    { L"Frosted Detail",     "frosted detail",     L"$", 0.5f*MM_TO_METERS, 12.0f*MM_TO_METERS, 5.00f, 2.39f,    999.0f, 99999.0f,  5.00f*0.10f,  0.0f,      28.4f,20.3f,18.4f },
    // make the dialog usable: { L"Gold",               "gold",               0.8f*MM_TO_METERS, 5.4f*MM_TO_METERS,  50.0f,600.0f,    999.0f, 99999.0f, 50.0f *0.10f,  0.0f,      10.0f, 8.9f, 8.9f },
    //{ L"Metallic Plastic",   "metallic plastic",   0.8f*MM_TO_METERS, 7.5f*MM_TO_METERS,  1.50f, 0.56f,    999.0f, 99999.0f,  1.50f*0.10f,  0.32f,     31.0f,23.0f,18.0f },
    // make the dialog usable: { L"Platinum",           "platinum",           0.8f*MM_TO_METERS, 5.4f*MM_TO_METERS,  100.0f,1750.0f,  999.0f, 99999.0f, 100.0f*0.10f,  0.0f,      10.0f, 8.9f, 8.9f },
    { L"Silver",             "silver",             L"$", 0.8f*MM_TO_METERS, 3.4f*MM_TO_METERS,  45.0f, 28.0f,    999.0f, 99999.0f, 45.0f *0.10f,  0.0f,      10.0f, 8.9f, 8.9f },
    { L"Steel",              "steel",              L"$", 1.0f*MM_TO_METERS, 27.0f*MM_TO_METERS, 6.00f, 5.00f,    999.0f, 99999.0f,  8.00f*0.10f,  0.0f,      76.2f,39.3f,39.3f },
    // old model, based on surface area: { L"Glazed Ceramics",    "glazed ceramics",    3.0f*MM_TO_METERS, 0.0f,               0.00f, 0.00f,    999.0f, 99999.0f,  1.00f,        0.18f,     30.0f,22.0f,17.0f },
    // I haven't figured out Sculpteo's cost model. Prices tend to be 20% higher, so that's what's here, but I think it also has to do with dimensions, which affects print time.
    // With full-sized rectangular blocks, the costPerCCM is more like 1.05
    { L"Sculpteo Multicolor", "Sculpteo multicolor", L"$", 2.0f*MM_TO_METERS, 0.0f*MM_TO_METERS, 3.00f, 1.20f*0.75f, 999.0f, 99999.0f, 3.00f,     0.0f,      38.0f,25.0f,20.0f },	// Sculpteo sandstone
    // typical home printer, 1.75 mm PLA: https://hwg.fictiv.com/fabricate/recommended-wall-thickness-for-3d-printing and http://www.fabbaloo.com/blog/2015/9/27/is-it-filament-weight-or-length
    { L"Custom Printer", "custom printer",       L"$", 1.5f*MM_TO_METERS,  0.0f*MM_TO_METERS,  0.00f, 0.03f,   999.0f, 99999.0f,  0.00f,        0.0f,      20.0f,20.0f,20.0f },	// Ultimaker, PLA
};

UnitType gUnitTypeTable[MODELS_UNITS_TABLE_SIZE] = {
    { L"Meters", "meters", 1.0f },
    { L"Centimeters", "centimeters", 100.0f },
    { L"Millimeters", "millimeters", 1000.0f },
    { L"Inches", "inches", 100.0f/2.54f }
};

// if you add new blocks, also set NUM_BLOCKS_STANDARD in the blockInfo.h file
BlockDefinition gBlockDefinitions[256]={	// IMPORTANT: do not change 256 size here. Crazy as it sounds, this is important: color schemes use this hard-wired size to copy stuff over.
    // Don't trust the premultiplied colors - these really are just placeholders, it's color * alpha that sets them when the program starts up.
    // name                               read_color ralpha color     prem-clr  alpha,     txX,Y  flags
    { /*   0 */ "Air",                    0x000000, 0.000f, 0xff7711, 0xff7711, 0.12345f,  13,14, 0x0F, BLF_NONE},	//00
    { /*   1 */ "Stone",                  0x7C7C7C, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1, 0, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//01
    // Grass block color is from Plains biome color (default terrain in a flat world). Grass and Sunflower should also be changed if this is changed.
    { /*   2 */ "Grass Block", /*output!*/0x8cbd57, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 0, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//02 3,0 side gets turned into 6,2
    { /*   3 */ "Dirt",                   0x8c6344, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2, 0, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//03
    { /*   4 */ "Cobblestone",            0x828282, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 1, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//04
    { /*   5 */ "Wood Planks",            0x9C8149, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 0, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//05
    { /*   6 */ "Sapling",                0x7b9a29, 1.000f, 0xff7711, 0xff7711, 0.12345f,  15, 0, 0x07, BLF_FLATTOP|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//06
    { /*   7 */ "Bedrock",                0x565656, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1, 1, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//07
    { /*   8 */ "Water",                  0x295dfe, 0.535f, 0xff7711, 0xff7711, 0.12345f,  15,13, 0x00, BLF_ALMOST_WHOLE|BLF_TRANSPARENT},	//08
    { /*   9 */ "Stationary Water",       0x295dfe, 0.535f, 0xff7711, 0xff7711, 0.12345f,  15,13, 0x00, BLF_ALMOST_WHOLE|BLF_TRANSPARENT},	//09
    { /*  10 */ "Lava",                   0xf56d00, 1.000f, 0xff7711, 0xff7711, 0.12345f,  15,15, 0x00, BLF_ALMOST_WHOLE|BLF_EMITTER},	//0a
    { /*  11 */ "Stationary Lava",        0xf56d00, 1.000f, 0xff7711, 0xff7711, 0.12345f,  15,15, 0x00, BLF_ALMOST_WHOLE|BLF_EMITTER},	//0b
    { /*  12 */ "Sand",                   0xDCD0A6, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2, 1, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//0c/12
    { /*  13 */ "Gravel",                 0x857b7b, 1.000f, 0xff7711, 0xff7711, 0.12345f,   3, 1, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//0d
    { /*  14 */ "Gold Ore",               0xfcee4b, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 2, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//0e
    { /*  15 */ "Iron Ore",               0xbc9980, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1, 2, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//0f
    { /*  16 */ "Coal Ore",               0x343434, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2, 2, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//10
    { /*  17 */ "Wood",                   0x695333, 1.000f, 0xff7711, 0xff7711, 0.12345f,   5, 1, 0x03, BLF_WHOLE|BLF_TRUNK_PART|BLF_FENCE_NEIGHBOR},	//11/17
    // Leaves block color is from Plains biome color (default terrain in a flat world). Acacia Leaves should also be changed if this is changed.
    { /*  18 */ "Leaves",      /*output!*/0x6fac2c, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 3, 0x03, BLF_WHOLE|BLF_CUTOUTS|BLF_LEAF_PART},	//12
    { /*  19 */ "Sponge",                 0xD1D24E, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 3, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//13
    { /*  20 */ "Glass",                  0xc0f6fe, 0.500f, 0xff7711, 0xff7711, 0.12345f,   1, 3, 0x0F, BLF_WHOLE|BLF_CUTOUTS},	//14 - note that BLF_TRANSPARENT is not flagged, 0x00FF, Because glass is either fully on or off, not blended
    { /*  21 */ "Lapis Lazuli Ore",       0x143880, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,10, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//15
    { /*  22 */ "Lapis Lazuli Block",     0x1b4ebb, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 9, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//16
    { /*  23 */ "Dispenser",              0x6f6f6f, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14, 3, 0x00, BLF_WHOLE},	//17 14,2 front, 13,2 sides
    { /*  24 */ "Sandstone",              0xe0d8a6, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,11, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//18 0,12 side, 0,13 bottom
    { /*  25 */ "Note Block",             0x342017, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10, 4, 0x00, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//19 10,4 side
    { /*  26 */ "Bed",                    0xff3333, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 8, 0x00, BLF_HALF|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT},	//1a
    { /*  27 */ "Powered Rail",           0xAB0301, 1.000f, 0xff7711, 0xff7711, 0.12345f,   3,11, 0x08, BLF_FLATTOP|BLF_BILLBOARD|BLF_3D_BIT|BLF_CUTOUTS|BLF_DNE_FLUID|BLF_OFFSET},	//1b/27
    { /*  28 */ "Detector Rail",          0xCD5E58, 1.000f, 0xff7711, 0xff7711, 0.12345f,   3,12, 0x08, BLF_FLATTOP|BLF_BILLBOARD|BLF_3D_BIT|BLF_CUTOUTS|BLF_DNE_FLUID|BLF_CONNECTS_REDSTONE|BLF_OFFSET},	//1c
    { /*  29 */ "Sticky Piston",          0x719e60, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12, 6, 0x00, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},	//1d
    { /*  30 */ "Cobweb",                 0xeeeeee, 1.000f, 0xff7711, 0xff7711, 0.12345f,  11, 0, 0x0F, BLF_BILLBOARD|BLF_CUTOUTS},	//1e
    { /*  31 */ "Grass",       /*output!*/0x8cbd57, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7, 2, 0x0F, BLF_FLATTOP|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//1f/31
    { /*  32 */ "Dead Bush",              0x946428, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7, 3, 0x0F, BLF_FLATTOP|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//20/32
    { /*  33 */ "Piston",                 0x95774b, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12, 6, 0x00, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},	//21
    { /*  34 */ "Piston Head",            0x95774b, 1.000f, 0xff7711, 0xff7711, 0.12345f,  11, 6, 0x00, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},	//22/34
    { /*  35 */ "Wool",                   0xEEEEEE, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 4, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//23 - gets converted to colors at end
    { /*  36 */ "Block moved By Piston",  0x000000, 1.000f, 0xff7711, 0xff7711, 0.12345f,  11, 6, 0x00, BLF_NONE},	//24 (36) - really, nothing...
    { /*  37 */ "Dandelion",              0xD3DD05, 1.000f, 0xff7711, 0xff7711, 0.12345f,  13, 0, 0x0F, BLF_FLATTOP|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//25
    { /*  38 */ "Poppy",                  0xCE1A05, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12, 0, 0x0F, BLF_FLATTOP|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//26 - 38
    { /*  39 */ "Brown Mushroom",         0xc19171, 1.000f, 0xff7711, 0xff7711, 0.12345f,  13, 1, 0x0F, BLF_FLATTOP|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//27
    { /*  40 */ "Red Mushroom",           0xfc5c5d, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12, 1, 0x0F, BLF_FLATTOP|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//28
    { /*  41 */ "Block of Gold",          0xfef74e, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7, 1, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//29
    { /*  42 */ "Block of Iron",          0xeeeeee, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 1, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//2a
    { /*  43 */ "Double Stone Slab",      0xa6a6a6, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 0, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//2b/43 - 5,0 side
    { /*  44 */ "Stone Slab",             0xa5a5a5, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 0, 0x07, BLF_HALF|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},	//2c/44 - 5,0 side
    { /*  45 */ "Bricks",                 0x985542, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7, 0, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//2d 
    { /*  46 */ "TNT",                    0xdb441a, 1.000f, 0xff7711, 0xff7711, 0.12345f,   9, 0, 0x0F, BLF_WHOLE},	//2e 7,0 side, 9,0 under
    { /*  47 */ "Bookshelf",              0x795a39, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 0, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//2f 3,2
    { /*  48 */ "Moss Stone",             0x627162, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 2, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//30
    { /*  49 */ "Obsidian",               0x1b1729, 1.000f, 0xff7711, 0xff7711, 0.12345f,   5, 2, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//31
    { /*  50 */ "Torch",                  0xfcfc00, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 5, 0x00, BLF_MIDDLER|BLF_FLATSIDE|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_EMITTER|BLF_DNE_FLUID},	//32/50 - should be BLF_EMITTER, flatten torches only if sides get flattened, too
    { /*  51 */ "Fire",                   0xfca100, 1.000f, 0xff7711, 0xff7711, 0.12345f,  /* somewhat bogus */ 15, 1, 0x00, BLF_BILLBOARD|BLF_CUTOUTS|BLF_EMITTER|BLF_DNE_FLUID},	//33/51 - no billboard, sadly BLF_CUTOUTS
    { /*  52 */ "Monster Spawner",        0x254254, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1, 4, 0x0F, BLF_ALMOST_WHOLE|BLF_CUTOUTS},	//34
    { /*  53 */ "Oak Wood Stairs",        0x9e804f, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 0, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},	//35
    { /*  54 */ "Chest",                  0xa06f23, 1.000f, 0xff7711, 0xff7711, 0.12345f,   9, 1, 0x00, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},	//36 (10,1) side; (11,1) front
    { /*  55 */ "Redstone Wire",          0xd60000, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4,10, 0x0F, BLF_FLATTOP|BLF_DNE_FLUID|BLF_CUTOUTS|BLF_CONNECTS_REDSTONE|BLF_OFFSET},	//37 - really, 0xfd3200 is lit, we use a "neutral" red here
    { /*  56 */ "Diamond Ore",            0x5decf5, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2, 3, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//38
    { /*  57 */ "Block of Diamond",       0x7fe3df, 1.000f, 0xff7711, 0xff7711, 0.12345f,   8, 1, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//39
    { /*  58 */ "Crafting Table",         0x825432, 1.000f, 0xff7711, 0xff7711, 0.12345f,  11, 2, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//3a - 12,3 side; 11,3 side2
    { /*  59 */ "Wheat",                  0x766615, 1.000f, 0xff7711, 0xff7711, 0.12345f,  15, 5, 0x0F, BLF_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//3b
    { /*  60 */ "Farmland",               0x40220b, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 5, 0x0F, BLF_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},	//3c - 7,5 dry
    { /*  61 */ "Furnace",                0x767677, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14, 3, 0x00, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//3d 13,2 side, 12,2 front
    { /*  62 */ "Burning Furnace",        0x777676, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14, 3, 0x00, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//3e 13,2 side, 13,3 front
    { /*  63 */ "Standing Sign",          0x9f814f, 1.000f, 0xff7711, 0xff7711, 0.12345f,  /* bogus */ 4, 0, 0x00, BLF_SMALL_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT},	//3f (63)
    { /*  64 */ "Oak Door",               0x7e5d2d, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1, 5, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT}, // 40 1,6 bottom	//40 TODO: BLF_FLATSIDE?
    { /*  65 */ "Ladder",                 0xaa8651, 1.000f, 0xff7711, 0xff7711, 0.12345f,   3, 5, 0x00, BLF_FLATSIDE|BLF_ENTRANCE|BLF_CUTOUTS|BLF_DNE_FLUID|BLF_OFFSET},	//41
    { /*  66 */ "Rail",                   0x686868, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 8, 0x00, BLF_FLATTOP|BLF_BILLBOARD|BLF_3D_BIT|BLF_CUTOUTS|BLF_DNE_FLUID|BLF_OFFSET},	//42 - TODO: doesn't do angled pieces, top to bottom edge
    { /*  67 */ "Cobblestone Stairs",     0x818181, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 1, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},	//43 (67)
    { /*  68 */ "Wall Sign",              0xa68a46, 1.000f, 0xff7711, 0xff7711, 0.12345f,  /* bogus */ 4, 0, 0x00, BLF_FLATSIDE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},	//44
    { /*  69 */ "Lever",                  0x8a6a3d, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 6, 0x00, BLF_SMALL_MIDDLER|BLF_TRUE_GEOMETRY|BLF_FLATTOP|BLF_FLATSIDE|BLF_DNE_FLUID|BLF_CONNECTS_REDSTONE},	//45
    { /*  70 */ "Stone Pressure Plate",   0xa4a4a4, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1, 0, 0x00, BLF_FLATTOP|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_CONNECTS_REDSTONE},	//46 (70)
    { /*  71 */ "Iron Door",              0xb2b2b2, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2, 5, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT},	//47 (71) 2,6 bottom TODO BLF_FLATSIDE?
    { /*  72 */ "Wooden Pressure Plate",  0x9d7f4e, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 0, 0x00, BLF_FLATTOP|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_CONNECTS_REDSTONE},	//48
    { /*  73 */ "Redstone Ore",           0x8f0303, 1.000f, 0xff7711, 0xff7711, 0.12345f,   3, 3, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//49
    { /*  74 */ "Glowing Redstone Ore",   0x900303, 1.000f, 0xff7711, 0xff7711, 0.12345f,   3, 3, 0x0F, BLF_WHOLE|BLF_EMITTER|BLF_FENCE_NEIGHBOR},	//4a (74)
    { /*  75 */ "Redstone Torch (inactive)",0x560000, 1.000f, 0xff7711, 0xff7711, 0.12345f, 3, 7, 0x00, BLF_MIDDLER|BLF_FLATSIDE|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID|BLF_CONNECTS_REDSTONE},	//4b
    { /*  76 */ "Redstone Torch (active)",  0xfd0000, 1.000f, 0xff7711, 0xff7711, 0.12345f, 3, 6, 0x00, BLF_MIDDLER|BLF_FLATSIDE|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_EMITTER|BLF_DNE_FLUID|BLF_CONNECTS_REDSTONE},	//4c should be BLF_EMITTER, 0x00FF, But it makes the whole block glow
    { /*  77 */ "Stone Button",           0xacacac, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1, 0, 0x00, BLF_FLATSIDE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},	//4d
    { /*  78 */ "Snow (layer)",           0xf0fafa, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2, 4, 0x00, BLF_FLATTOP|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},	//4e
    { /*  79 */ "Ice",                    0x7dacfe, 0.613f, 0xff7711, 0xff7711, 0.12345f,   3, 4, 0x0F, BLF_WHOLE|BLF_TRANSPARENT},	//4f
    { /*  80 */ "Snow",                   0xf1fafa, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2, 4, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//50 4,4 side
    { /*  81 */ "Cactus",                 0x0D6118, 1.000f, 0xff7711, 0xff7711, 0.12345f,   5, 4, 0x00, BLF_ALMOST_WHOLE|BLF_BILLBOARD|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT},	//51 6,4 side - note: the cutouts are not used when "lesser" is off for rendering, 0x00FF, But so it goes.
    { /*  82 */ "Clay",                   0xa2a7b4, 1.000f, 0xff7711, 0xff7711, 0.12345f,   8, 4, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//52
    { /*  83 */ "Sugar Cane",             0x72944e, 1.000f, 0xff7711, 0xff7711, 0.12345f,   9, 4, 0x00, BLF_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//53
    { /*  84 */ "Jukebox",                0x8a5a40, 1.000f, 0xff7711, 0xff7711, 0.12345f,  11, 4, 0x00, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//54 11,3 side
    { /*  85 */ "Fence",                  0x9f814e, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 0, 0x00, BLF_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},	//55
    { /*  86 */ "Pumpkin",                0xc07615, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 6, 0x08, BLF_WHOLE},	//56 6,7 side, 7,7 face
    { /*  87 */ "Netherrack",             0x723a38, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7, 6, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},   //57
    { /*  88 */ "Soul Sand",              0x554134, 1.000f, 0xff7711, 0xff7711, 0.12345f,   8, 6, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},   //58
    { /*  89 */ "Glowstone",              0xf9d49c, 1.000f, 0xff7711, 0xff7711, 0.12345f,   9, 6, 0x0F, BLF_WHOLE|BLF_EMITTER},   //59
    { /*  90 */ "Nether Portal",          0x472272, 0.800f, 0xff7711, 0xff7711, 0.12345f,  14, 0, 0x0F, BLF_PANE|BLF_TRANSPARENT|BLF_EMITTER|BLF_DNE_FLUID},   //5a/90 - 0xd67fff unpremultiplied
    { /*  91 */ "Jack o'Lantern",         0xe9b416, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 6, 0x08, BLF_WHOLE|BLF_EMITTER},   //5b 6,7 side, 8,7 lit face
    { /*  92 */ "Cake",                   0xfffdfd, 1.000f, 0xff7711, 0xff7711, 0.12345f,   9, 7, 0x00, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},   //5c 10,7 side, 11,7 inside, 12,7 under - TODO: not really whole
    { /*  93 */ "Redstone Repeater (inactive)",0x560000, 1.000f, 0xff7711, 0xff7711, 0.12345f,   3, 8, 0x00, BLF_MIDDLER|BLF_FLATTOP|BLF_DNE_FLUID|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},   //5d
    { /*  94 */ "Redstone Repeater (active)",  0xee5555, 1.000f, 0xff7711, 0xff7711, 0.12345f,   3, 9, 0x00, BLF_MIDDLER|BLF_FLATTOP|BLF_DNE_FLUID|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},   //5e
    // in 1.7 locked chest was replaced by stained glass block
    //{"Locked Chest",           0xa06f23, 1.000f, 0xa06f23,  9, 1, 0x0F, BLF_WHOLE},   //5f/95 (10,1) side; (11,1) front
    { /*  95 */ "Stained Glass",          0xEFEFEF, 0.500f, 0xff7711, 0xff7711, 0.12345f,   0,20, 0x0F, BLF_WHOLE|BLF_TRANSPARENT},	//5f/95 - note BLF_CUTOUTS is off, since all pixels are semitransparent
    { /*  96 */ "Trapdoor",               0x886634, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 5, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_FLATSIDE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT},   //60/96 - tricky case: could be a flattop, or a flatside. For now, render it
    { /*  97 */ "Monster Egg",            0x787878, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1, 0, 0x0F, BLF_WHOLE},   //61
    { /*  98 */ "Stone Bricks",           0x797979, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 3, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},   //62
    { /*  99 */ "Brown Mushroom (block)", 0x654b39, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14, 7, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},   //63
    { /* 100 */ "Red Mushroom (block)",   0xa91b19, 1.000f, 0xff7711, 0xff7711, 0.12345f,  13, 7, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},   //64
    { /* 101 */ "Iron Bars",              0xa3a4a4, 1.000f, 0xff7711, 0xff7711, 0.12345f,   5, 5, 0x00, BLF_PANE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_CUTOUTS},   //65
    { /* 102 */ "Glass Pane",             0xc0f6fe, 0.500f, 0xff7711, 0xff7711, 0.12345f,   1, 3, 0x0F, BLF_PANE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_CUTOUTS},   //66
    { /* 103 */ "Melon",                  0xaead27, 1.000f, 0xff7711, 0xff7711, 0.12345f,   9, 8, 0x0F, BLF_WHOLE},   //67 (8,8) side
    { /* 104 */ "Pumpkin Stem",           0xE1C71C, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14,11, 0x0F, BLF_FLATTOP|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},   //68/104 15,11 connected TODO
    { /* 105 */ "Melon Stem",             0xE1C71C, 1.000f, 0xff7711, 0xff7711, 0.12345f,  15, 6, 0x0F, BLF_FLATTOP|BLF_SMALL_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},   //69/105 15,7 connected TODO
    { /* 106 */ "Vines",                  0x76AB2F, 1.000f, 0xff7711, 0xff7711, 0.12345f,  15, 8, 0x00, BLF_BILLBOARD|BLF_FLATSIDE|BLF_PANE|BLF_CUTOUTS|BLF_DNE_FLUID|BLF_OFFSET},   //6a
    { /* 107 */ "Fence Gate",             0xa88754, 1.000f, 0xff7711, 0xff7711, 0.12345f,  /* bogus */ 4, 0, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_FENCE_NEIGHBOR|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},   //6b
    { /* 108 */ "Brick Stairs",           0xa0807b, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7, 0, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},   //6c
    { /* 109 */ "Stone Brick Stairs",     0x797979, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 3, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},   //6d
    { /* 110 */ "Mycelium",               0x685d69, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14, 4, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},   //6e 13,4 side, 2,0 bottom
    { /* 111 */ "Lily Pad",               0x217F30, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12, 4, 0x0F, BLF_FLATTOP|BLF_CUTOUTS|BLF_DNE_FLUID|BLF_OFFSET},   //6f
    { /* 112 */ "Nether Brick",           0x32171c, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,14, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},   //70/112
    { /* 113 */ "Nether Brick Fence",     0x241316, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,14, 0x00, BLF_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},   //71
    { /* 114 */ "Nether Brick Stairs",    0x32171c, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,14, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},   //72
    { /* 115 */ "Nether Wart",            0x81080a, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4,14, 0x0F, BLF_BILLBOARD|BLF_CUTOUTS},   //73
    { /* 116 */ "Enchantment Table",      0xa6701a, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6,10, 0x0F, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},   //74 6,11 side, 7,11 under
    { /* 117 */ "Brewing Stand",          0x77692e, 1.000f, 0xff7711, 0xff7711, 0.12345f,  /* bogus */ 13, 9, 0x00, BLF_MIDDLER|BLF_TRUE_GEOMETRY|BLF_CUTOUTS},   //75 13,8 base - no BLF_IMAGE_TEXTURE
    { /* 118 */ "Cauldron",               0x3b3b3b, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10, 8, 0x0F, BLF_ALMOST_WHOLE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},   //76 - 10,8 top (inside's better), 10,9 side, 11,9 feet TODO: not really whole
    { /* 119 */ "End Portal",             0x0c0b0b, 0.7f,   0xff7711, 0xff7711, 0.12345f,   8,11, 0x0F, BLF_PANE|BLF_TRANSPARENT},   //77 - not really whole, no real texture, make it a portal
    { /* 120 */ "End Portal Frame",       0x3e6c60, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14, 9, 0x00, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},   //78 15,9 side, 15,10 bottom
    { /* 121 */ "End Stone",              0xdadca6, 1.000f, 0xff7711, 0xff7711, 0.12345f,  15,10, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},   //79
    { /* 122 */ "Dragon Egg",             0x1b1729, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7,10, 0x0F, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},    //7A - not really whole
    { /* 123 */ "Redstone Lamp (inactive)",0x9F6D4D, 1.000f, 0xff7711, 0xff7711, 0.12345f,  3,13, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},   //7b
    { /* 124 */ "Redstone Lamp (active)", 0xf9d49c, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4,13, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR|BLF_EMITTER},    //7c
    { /* 125 */ "Double Wooden Slab",     0x9f8150, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 0, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},    //7d
    { /* 126 */ "Wooden Slab",            0x9f8150, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 0, 0x07, BLF_HALF|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},    //7e
    { /* 127 */ "Cocoa"      ,            0xBE742D, 1.000f, 0xff7711, 0xff7711, 0.12345f,   8,10, 0x0C, BLF_SMALL_MIDDLER|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},    //7f/127
    { /* 128 */ "Sandstone Stairs",       0xe0d8a6, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,11, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},    //80/128
    { /* 129 */ "Emerald Ore",            0x900303, 1.000f, 0xff7711, 0xff7711, 0.12345f,  11,10, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},    //81
    { /* 130 */ "Ender Chest",            0x293A3C, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10,13, 0x00, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},    //82 - don't really have tiles for this one, added to terrainExt.png
    { /* 131 */ "Tripwire Hook",          0xC79F63, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12,10, 0x00, BLF_SMALL_MIDDLER|BLF_TRUE_GEOMETRY|BLF_FLATSIDE|BLF_DNE_FLUID},    //83 - decal
    { /* 132 */ "Tripwire",               0x000000, 1.000f, 0xff7711, 0xff7711, 0.12345f,  13,10, 0x00, BLF_NONE},    //84 - sorta redwire decal, 0x00FF, But really it should be invisible, so BLF_NONE. Color 0x8F8F8F
    // alternate { /* 130 */ "Tripwire",               0x8F8F8F, 1.000f, 0xff7711, 0xff7711, 0.12345f,  13,10, 0x0F, BLF_FLATTOP|BLF_CUTOUTS},    //84 - sorta redwire decal, but really it should be invisible, so BLF_NONE. Color 0x8F8F8F
    { /* 133 */ "Block of Emerald",       0x53D778, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12,14, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},    //85 - should be at 9,1 for 1.3.X TODO!, but that wipes out the chest. This location given works with my special terrainExt.png file
    { /* 134 */ "Spruce Wood Stairs",     0x785836, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6,12, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},    //86
    { /* 135 */ "Birch Wood Stairs",      0xD7C185, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6,13, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},    //87
    { /* 136 */ "Jungle Wood Stairs",     0xB1805C, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7,12, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},    //88
    { /* 137 */ "Command Block",          0xB28B79, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10,24, 0x00, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//89
    { /* 138 */ "Beacon",                 0x9CF2ED, 0.800f, 0xff7711, 0xff7711, 0.12345f,  11,14, 0x00, BLF_ALMOST_WHOLE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_EMITTER},	//8A/138 - it's a whole block sorta, it doesn't attach to fences or block wires
    { /* 139 */ "Cobblestone Wall",       0x828282, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 1, 0x0F, BLF_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},   //8B
    { /* 140 */ "Flower Pot",             0x7C4536, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10,11, 0x00, BLF_SMALL_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},   //8C
    { /* 141 */ "Carrot",                 0x056B05, 1.000f, 0xff7711, 0xff7711, 0.12345f,  11,12, 0x0F, BLF_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//8d/141
    { /* 142 */ "Potato",                 0x00C01B, 1.000f, 0xff7711, 0xff7711, 0.12345f,  15,12, 0x0F, BLF_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	//8e/142
    { /* 143 */ "Wooden Button",          0x9f8150, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4, 0, 0x00, BLF_FLATSIDE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},	//8f/143
    { /* 144 */ "Mob Head",	              0xcacaca, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 6, 0x07, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},	//90/144 - TODO; we use a pumpkin for now...
    { /* 145 */ "Anvil",                  0x404040, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7,13, 0x0C, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},    // 91/145 - NOTE: the top swatch is not used, the generic side swatch is
    // 1.6
    { /* 146 */ "Trapped Chest",          0xa06f23, 1.000f, 0xff7711, 0xff7711, 0.12345f,   9, 1, 0x00, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_CONNECTS_REDSTONE},	// 92/146
    { /* 147 */ "Weighted Pressure Plate (Light)",0xEFE140, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7, 1, 0x00, BLF_FLATTOP|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_CONNECTS_REDSTONE},	// 93/147 gold
    { /* 148 */ "Weighted Pressure Plate (Heavy)",0xD7D7D7, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6, 1, 0x00, BLF_FLATTOP|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_CONNECTS_REDSTONE},	// 94/148 iron
    { /* 149 */ "Redstone Comparator",    0xC5BAAD, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14,14, 0x00, BLF_MIDDLER|BLF_FLATTOP|BLF_DNE_FLUID|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID|BLF_CONNECTS_REDSTONE},   // 95/149 TODO from repeater off
    { /* 150 */ "Redstone Comparator (deprecated)",0xD1B5AA, 1.000f, 0xff7711, 0xff7711, 0.12345f,  15,14, 0x00, BLF_MIDDLER|BLF_FLATTOP|BLF_DNE_FLUID|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID|BLF_CONNECTS_REDSTONE},   // 96/150 TODO from repeater on
    { /* 151 */ "Daylight Sensor",        0xBBA890, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6,15, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_FLATSIDE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_CONNECTS_REDSTONE},   // 97/151 TODO from trapdoor
    { /* 152 */ "Block of Redstone",      0xA81E09, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14,15, 0x03, BLF_WHOLE|BLF_EMITTER|BLF_FENCE_NEIGHBOR|BLF_CONNECTS_REDSTONE},	// 98/152
    { /* 153 */ "Nether Quartz Ore",      0x7A5B57, 1.000f, 0xff7711, 0xff7711, 0.12345f,   8,17, 0x00, BLF_WHOLE|BLF_FENCE_NEIGHBOR}, // 99/153
    { /* 154 */ "Hopper",                 0x363636, 1.000f, 0xff7711, 0xff7711, 0.12345f,  13,15, 0x00, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},    // 9A/154 - note that 3d print version is simpler, no indentation, so it's thick enough
    { /* 155 */ "Block of Quartz",        0xE0DDD7, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7,17, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	// 9B/155
    { /* 156 */ "Quartz Stairs",          0xE1DCD1, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7,17, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},    // 9C/156
    { /* 157 */ "Activator Rail",         0x880300, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10,17, 0x08, BLF_FLATTOP|BLF_BILLBOARD|BLF_3D_BIT|BLF_CUTOUTS|BLF_DNE_FLUID|BLF_OFFSET},	// 9D/157
    { /* 158 */ "Dropper",                0x6E6E6E, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14, 3, 0x00, BLF_WHOLE},	// 9E/158
    { /* 159 */ "Stained Clay",           0xCEAE9E, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,16, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	// 9F/159
    { /* 160 */ "Stained Glass Pane",     0xEFEFEF, 0.500f, 0xff7711, 0xff7711, 0.12345f,   0,20, 0x0F, BLF_PANE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_TRANSPARENT},	// A0/160 - semitransparent, not a cutout like glass panes are
    { /* 161 */ "Leaves (Acacia/Dark Oak)",/*output*/0x6fac2c, 1.000f, 0xff7711, 0xff7711, 0.12345f,  11,19, 0x03, BLF_WHOLE|BLF_CUTOUTS|BLF_LEAF_PART},	//A1/161
    { /* 162 */ "Wood (Acacia/Dark Oak)", 0x766F64, 1.000f, 0xff7711, 0xff7711, 0.12345f,  13,19, 0x03, BLF_WHOLE|BLF_TRUNK_PART|BLF_FENCE_NEIGHBOR},	//A2/162
    { /* 163 */ "Acacia Wood Stairs",     0xBA683B, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,22, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},    //A3
    { /* 164 */ "Dark Oak Wood Stairs",   0x492F17, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1,22, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},    //A4/164
    { /* 165 */ "Slime Block",            0x787878, 0.500f, 0xff7711, 0xff7711, 0.12345f,   3,22, 0x0F, BLF_WHOLE|BLF_TRUE_GEOMETRY|BLF_TRANSPARENT|BLF_FENCE_NEIGHBOR},	// A5/165 - 1.8
    { /* 166 */ "Barrier",                0xE30000, 0.000f, 0xff7711, 0xff7711, 0.12345f,  14,25, 0x0F, BLF_WHOLE|BLF_CUTOUTS},	// A6/166 - 1.8 - to make visible, set alpha to 1.0
    { /* 167 */ "Iron Trapdoor",          0xC0C0C0, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2,22, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_FLATSIDE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT},	// A7/167 - 1.8
    { /* 168 */ "Prismarine",             0x5A9B95, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12,22, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	// 1.8 add
    { /* 169 */ "Sea Lantern",            0xD3DBD3, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14,22, 0x0F, BLF_WHOLE|BLF_EMITTER},   //59
    { /* 170 */ "Hay Bale",               0xB5970C, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10,15, 0x00, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	// AA/170
    { /* 171 */ "Carpet",                 0xEEEEEE, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0, 4, 0x0F, BLF_FLATTOP|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},	// AB/171
    { /* 172 */ "Hardened Clay",          0x945A41, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,17, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	// AC/172
    { /* 173 */ "Block of Coal",          0x191919, 1.000f, 0xff7711, 0xff7711, 0.12345f,  13,14, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	// AD/173
    // 1.7
    { /* 174 */ "Packed Ice",             0x7dacfe, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12,17, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	// AE/174 - like ice, but not transparent, and a fence neighbor
    { /* 175 */ "Large Flowers",    /*output*/0x8cbd57, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,18, 0x07, BLF_FLATTOP|BLF_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},	// AF/175 - note color is used to multiply grayscale textures, so don't change it
    { /* 176 */ "Standing Banner",        0x9C9C9C, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10,23, 0x00, BLF_SMALL_MIDDLER|BLF_TRUE_GEOMETRY},	// assumed to be like signs in properties, but cannot 3D print (too darn thin)
    { /* 177 */ "Wall Banner",            0x9C9C9C, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10,23, 0x00, BLF_SMALL_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_DNE_FLUID},	// BLF_FLATSIDE removed - too tricky to do, since it spans two block, here and below TODO
    { /* 178 */ "Inverted Daylight Sensor",0xBBA890,1.000f, 0xff7711, 0xff7711, 0.12345f,  13,22, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_FLATSIDE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_CONNECTS_REDSTONE},
    { /* 179 */ "Red Sandstone",          0x964C19, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12,19, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 180 */ "Red Sandstone Stairs",   0x964C19, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12,19, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 181 */ "Double Red Sandstone Slab",0x964C19,1.000f,0xff7711, 0xff7711, 0.12345f,  12,19, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},	//2b/43 - 5,0 side
    { /* 182 */ "Red Sandstone Slab",     0x964C19, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12,19, 0x07, BLF_HALF|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},	//2c/44 - 5,0 side
    { /* 183 */ "Spruce Fence Gate",      0x785836, 1.000f, 0xff7711, 0xff7711, 0.12345f,  /* bogus */ 6,12, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_FENCE_NEIGHBOR|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 184 */ "Birch Fence Gate",       0xD7C185, 1.000f, 0xff7711, 0xff7711, 0.12345f,  /* bogus */ 6,13, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_FENCE_NEIGHBOR|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 185 */ "Jungle Fence Gate",      0xB1805C, 1.000f, 0xff7711, 0xff7711, 0.12345f,  /* bogus */ 7,12, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_FENCE_NEIGHBOR|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 186 */ "Dark Oak Fence Gate",    0x492F17, 1.000f, 0xff7711, 0xff7711, 0.12345f,  /* bogus */ 1,22, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_FENCE_NEIGHBOR|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 187 */ "Acacia Fence Gate",      0xBA683B, 1.000f, 0xff7711, 0xff7711, 0.12345f,  /* bogus */ 0,22, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_FENCE_NEIGHBOR|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 188 */ "Spruce Fence",           0x785836, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6,12, 0x00, BLF_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 189 */ "Birch Fence",            0xD7C185, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6,13, 0x00, BLF_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 190 */ "Jungle Fence",           0xB1805C, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7,12, 0x00, BLF_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 191 */ "Dark Oak Fence",         0x492F17, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1,22, 0x00, BLF_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 192 */ "Acacia Fence",           0xBA683B, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,22, 0x00, BLF_MIDDLER|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 193 */ "Spruce Door",            0x7A5A36, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1,23, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT},
    { /* 194 */ "Birch Door",             0xD6CA8C, 1.000f, 0xff7711, 0xff7711, 0.12345f,   3,23, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT},
    { /* 195 */ "Jungle Door",            0xB2825E, 1.000f, 0xff7711, 0xff7711, 0.12345f,   5,23, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT},
    { /* 196 */ "Acacia Door",            0xB16640, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7,23, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT},
    { /* 197 */ "Dark Oak Door",          0x51341A, 1.000f, 0xff7711, 0xff7711, 0.12345f,   9,23, 0x00, BLF_MIDDLER|BLF_ENTRANCE|BLF_CUTOUTS|BLF_TRUE_GEOMETRY|BLF_3D_BIT},	// yes, for this one dark oak really does go after acacia
    { /* 198 */ "End Rod",                0xE0CFD0, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12,23, 0x00, BLF_SMALL_MIDDLER|BLF_TRUE_GEOMETRY|BLF_DNE_FLUID},
    { /* 199 */ "Chorus Plant",           0x654765, 1.000f, 0xff7711, 0xff7711, 0.12345f,  13,23, 0x0F, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},
    { /* 200 */ "Chorus Flower",          0x937E93, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14,23, 0x00, BLF_ALMOST_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT},
    { /* 201 */ "Purpur Block",           0xA77BA7, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,24, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 202 */ "Purpur Pillar",          0xAC82AC, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2,24, 0x00, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 203 */ "Purpur Stairs",          0xA77BA7, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,24, 0x00, BLF_STAIRS|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 204 */ "Purpur Double Slab",     0xA77BA7, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,24, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 205 */ "Purpur Slab",            0xA77BA7, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,24, 0x07, BLF_HALF|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 206 */ "End Stone Bricks",       0xE2E8AC, 1.000f, 0xff7711, 0xff7711, 0.12345f,   3,24, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 207 */ "Beetroot Seeds",         0x6D7F44, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7,24, 0x0F, BLF_BILLBOARD|BLF_CUTOUTS|BLF_DNE_FLUID},
    { /* 208 */ "Grass Path",             0x977E48, 1.000f, 0xff7711, 0xff7711, 0.12345f,   8,24, 0x0F, BLF_WHOLE|BLF_TRUE_GEOMETRY|BLF_3D_BIT|BLF_3D_BIT_GLUE},
    { /* 209 */ "End Gateway",            0x1A1828, 1.000f, 0xff7711, 0xff7711, 0.12345f,   8,11, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 210 */ "Repeating Command Block",0x8577B2, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14,24, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 211 */ "Chain Command Block",    0x8AA59A, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2,25, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 212 */ "Frosted Ice",            0x81AFFF, 0.613f, 0xff7711, 0xff7711, 0.12345f,   6,25, 0x0F, BLF_WHOLE|BLF_TRANSPARENT},
    { /* 213 */ "Magma Block",            0x9D4E1D, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,26, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 214 */ "Nether Wart Block",      0x770C0D, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1,26, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 215 */ "Red Nether Brick",       0x470709, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2,26, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR},
    { /* 216 */ "Bone Block",             0xE1DDC9, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4,26, 0x00, BLF_WHOLE|BLF_FENCE_NEIGHBOR}, // top location; side is previous tile
    { /* 217 */ "Structure Void",         0xff0000, 0.000f, 0xff7711, 0xff7711, 0.12345f,   1, 8, 0x0F, BLF_SMALL_MIDDLER|BLF_TRUE_GEOMETRY},	// uses red wool
    { /* 218 */ "Observer",				  0x6E6E6E, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4,33, 0x00, BLF_WHOLE},
    { /* 219 */ "White Shulker Box",      0xD8DDDE, 1.000f, 0xff7711, 0xff7711, 0.12345f,   0,27, 0x00, BLF_WHOLE},
    { /* 220 */ "Orange Shulker Box",     0xEB6B0B, 1.000f, 0xff7711, 0xff7711, 0.12345f,   1,27, 0x00, BLF_WHOLE},
    { /* 221 */ "Magenta Shulker Box",    0xAE37A4, 1.000f, 0xff7711, 0xff7711, 0.12345f,   2,27, 0x00, BLF_WHOLE},
    { /* 222 */ "Light Blue Shulker Box", 0x32A5D4, 1.000f, 0xff7711, 0xff7711, 0.12345f, 3, 27, 0x00, BLF_WHOLE },
    { /* 223 */ "Yellow Shulker Box",     0xF8BD1E, 1.000f, 0xff7711, 0xff7711, 0.12345f,   4,27, 0x00, BLF_WHOLE},
    { /* 224 */ "Lime Shulker Box",       0x65AE17, 1.000f, 0xff7711, 0xff7711, 0.12345f,   5,27, 0x00, BLF_WHOLE},
    { /* 225 */ "Pink Shulker Box",       0xE77B9E, 1.000f, 0xff7711, 0xff7711, 0.12345f,   6,27, 0x00, BLF_WHOLE},
    { /* 226 */ "Gray Shulker Box",       0x383B3F, 1.000f, 0xff7711, 0xff7711, 0.12345f,   7,27, 0x00, BLF_WHOLE},
    { /* 227 */ "Light Grey Shulker Box", 0x7E7E75, 1.000f, 0xff7711, 0xff7711, 0.12345f, 8, 27, 0x00, BLF_WHOLE },
    { /* 228 */ "Cyan Shulker Box",       0x147A88, 1.000f, 0xff7711, 0xff7711, 0.12345f,   9,27, 0x00, BLF_WHOLE},
    { /* 229 */ "Purple Shulker Box",     0x8C618C, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10,27, 0x00, BLF_WHOLE},
    { /* 230 */ "Blue Shulker Box",       0x2C2E8D, 1.000f, 0xff7711, 0xff7711, 0.12345f,  11,27, 0x00, BLF_WHOLE},
    { /* 231 */ "Brown Shulker Box",      0x6B4224, 1.000f, 0xff7711, 0xff7711, 0.12345f,  12,27, 0x00, BLF_WHOLE},
    { /* 232 */ "Green Shulker Box",      0x4F6520, 1.000f, 0xff7711, 0xff7711, 0.12345f,  13,27, 0x00, BLF_WHOLE},
    { /* 233 */ "Red Shulker Box",        0x8E201F, 1.000f, 0xff7711, 0xff7711, 0.12345f,  14,27, 0x00, BLF_WHOLE},
    { /* 234 */ "Black Shulker Box",      0x1A1A1E, 1.000f, 0xff7711, 0xff7711, 0.12345f,  15,27, 0x00, BLF_WHOLE},
    { /* 235 */ "White Glazed Terracotta",      0xD4DBD7, 1.000f, 0xff7711, 0xff7711, 0.12345f,  0,28, 0x00, BLF_WHOLE },
    { /* 236 */ "Orange Glazed Terracotta",     0xC09A7F, 1.000f, 0xff7711, 0xff7711, 0.12345f,  1,28, 0x00, BLF_WHOLE },
    { /* 237 */ "Magenta Glazed Terracotta",    0xD26FC1, 1.000f, 0xff7711, 0xff7711, 0.12345f,  2,28, 0x00, BLF_WHOLE },
    { /* 238 */ "Light Blue Glazed Terracotta", 0x80B3D4, 1.000f, 0xff7711, 0xff7711, 0.12345f, 3, 28, 0x00, BLF_WHOLE },
    { /* 239 */ "Yellow Glazed Terracotta",     0xEDC671, 1.000f, 0xff7711, 0xff7711, 0.12345f,  4,28, 0x00, BLF_WHOLE },
    { /* 240 */ "Lime Glazed Terracotta",       0xB0C84F, 1.000f, 0xff7711, 0xff7711, 0.12345f,  5,28, 0x00, BLF_WHOLE },
    { /* 241 */ "Pink Glazed Terracotta",       0xEC9EB7, 1.000f, 0xff7711, 0xff7711, 0.12345f,  6,28, 0x00, BLF_WHOLE },
    { /* 242 */ "Gray Glazed Terracotta",       0x5B6164, 1.000f, 0xff7711, 0xff7711, 0.12345f,  7,28, 0x00, BLF_WHOLE },
    { /* 243 */ "Light Grey Glazed Terracotta", 0x9FACAD, 1.000f, 0xff7711, 0xff7711, 0.12345f, 8, 28, 0x00, BLF_WHOLE },
    { /* 244 */ "Cyan Glazed Terracotta",       0x4F8288, 1.000f, 0xff7711, 0xff7711, 0.12345f,  9,28, 0x00, BLF_WHOLE },
    { /* 245 */ "Purple Glazed Terracotta",     0x7633A5, 1.000f, 0xff7711, 0xff7711, 0.12345f, 10,28, 0x00, BLF_WHOLE },
    { /* 246 */ "Blue Glazed Terracotta",       0x324D98, 1.000f, 0xff7711, 0xff7711, 0.12345f, 11,28, 0x00, BLF_WHOLE },
    { /* 247 */ "Brown Glazed Terracotta",      0x896E60, 1.000f, 0xff7711, 0xff7711, 0.12345f, 12,28, 0x00, BLF_WHOLE },
    { /* 248 */ "Green Glazed Terracotta",      0x7F9563, 1.000f, 0xff7711, 0xff7711, 0.12345f, 13,28, 0x00, BLF_WHOLE },
    { /* 249 */ "Red Glazed Terracotta",        0xB8433B, 1.000f, 0xff7711, 0xff7711, 0.12345f, 14,28, 0x00, BLF_WHOLE },
    { /* 250 */ "Black Glazed Terracotta",      0x592225, 1.000f, 0xff7711, 0xff7711, 0.12345f, 15,28, 0x00, BLF_WHOLE },
    { /* 251 */ "Concrete",               0xCFD5D6, 1.000f, 0xff7711, 0xff7711, 0.12345f, 0,29, 0x0F, BLF_WHOLE | BLF_FENCE_NEIGHBOR },
    { /* 252 */ "Concrete Powder",        0xE2E4E4, 1.000f, 0xff7711, 0xff7711, 0.12345f, 0,30, 0x0F, BLF_WHOLE | BLF_FENCE_NEIGHBOR },
    { /* 253 */ "Unknown Block", 0x565656, 1.000f, 0xff7711, 0xff7711, 0.12345f, 1, 1, 0x0F, BLF_WHOLE | BLF_FENCE_NEIGHBOR },	// same as bedrock
    { /* 254 */ "Unknown Block", 0x565656, 1.000f, 0xff7711, 0xff7711, 0.12345f, 1, 1, 0x0F, BLF_WHOLE | BLF_FENCE_NEIGHBOR },	// same as bedrock - BLOCK_FAKE is used here
    { /* 255 */ "Structure Block",        0x665E5F, 1.000f, 0xff7711, 0xff7711, 0.12345f,  10,25, 0x0F, BLF_WHOLE|BLF_FENCE_NEIGHBOR}
};
