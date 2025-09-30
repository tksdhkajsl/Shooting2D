
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
        // g_MapImage�� �ε��Ǿ� �ִ�.
        InGraphics->DrawImage(
            MapImage,          // �׷��� �̹���
            0,    // �׷��� ��ġ
            posY1,
            g_ScreenSize.X, g_ScreenSize.Y );  // �׷��� ������

        // g_MapImage�� �ε��Ǿ� �ִ�.
       InGraphics->DrawImage(
        MapImage,          // �׷��� �̹���
        0,    // �׷��� ��ġ
        posY2,
        g_ScreenSize.X, g_ScreenSize.Y);  // �׷��� ������
    }
    else
    {
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,
           0,    // �׷��� ��ġ
           0,
           g_ScreenSize.X, g_ScreenSize.Y);
    }
}
