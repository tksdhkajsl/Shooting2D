
#pragma once
#include <unordered_map>
#include <Windows.h>
#include <gdiplus.h>
#include "Map.h"

Map::~Map()
{
    if (MapImage)
    {
        delete MapImage;
        MapImage = nullptr;
    }
}

void Map::Render(Gdiplus::Graphics* InGraphics)
{
    if (MapImage)
    {
        int posY1 = (g_ScreenSize.Y + PositionY) % g_ScreenSize.Y;
        int posY2 = (posY1 + 3) - g_ScreenSize.Y;
        // g_MapImage가 로딩되어 있다.
        InGraphics->DrawImage(
            MapImage,          // 그려질 이미지
            0,    // 그려질 위치
            posY1,
            g_ScreenSize.X, g_ScreenSize.Y );  // 그려질 사이즈

        // g_MapImage가 로딩되어 있다.
       InGraphics->DrawImage(
        MapImage,          // 그려질 이미지
        0,    // 그려질 위치
        posY2,
        g_ScreenSize.X, g_ScreenSize.Y);  // 그려질 사이즈
    }
    else
    {
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,
           0,    // 그려질 위치
           0,
           g_ScreenSize.X, g_ScreenSize.Y);
    }
}
