#include "Player.h"

Player::~Player()
{
    if (Image)
    {
        delete Image;
        Image = nullptr;
    }
}

void Player::Render(Gdiplus::Graphics* InGraphics)
{
    if (Image)
    {
        // g_PlayerImage�� �ε��Ǿ� �ִ�.
        InGraphics->DrawImage(
            Image,          // �׷��� �̹���
            static_cast<int>(Position.X - PixelSize * Pivot.X),    // �׷��� ��ġ
            static_cast<int>(Position.Y - PixelSize * Pivot.Y),
            PixelSize, PixelSize);  // �׷��� ������
    }
    else
    {
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,
            static_cast<int>(Position.X - PixelSize * Pivot.X),    // �׷��� ��ġ
            static_cast<int>(Position.Y - PixelSize * Pivot.Y),
            PixelSize, PixelSize);
    }
}

void Player::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    if (InKey == VK_LEFT || InKey == VK_RIGHT)
    {
        KeyWasPressedMap[static_cast<InputDirection>(InKey)] = InIsPressed;

        if (InKey == VK_LEFT)
        {
            Position.X -= Speed;
            if (Position.X < 0)
            {
                Position.X = static_cast<float>(g_ScreenSize.X - PixelSize);
            }
            InvalidateRect(g_hMainWindow, nullptr, FALSE);
        }
        else if (InKey == VK_RIGHT)
        {
            Position.X += Speed;
            if (g_ScreenSize.X < Position.X)
            {
                Position.X = 0;
            }
            InvalidateRect(g_hMainWindow, nullptr, FALSE);
        }
    }
}
