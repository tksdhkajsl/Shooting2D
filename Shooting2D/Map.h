#pragma once

extern HWND g_hMainWindow; // g_hMainWindow�� �ٸ� ���Ͽ� �ִٴ� ���� �˷���
extern Gdiplus::Point g_ScreenSize;
extern int PositionY;
using PointF = Gdiplus::PointF;

class Map
{
public:

	Map() = delete;
	Map(const wchar_t* InImagePath)
	{
		MapImage = new Gdiplus::Bitmap(InImagePath); // �÷��̾� �̹��� �ε�
		if (MapImage->GetLastStatus() != Gdiplus::Ok)
		{
			// ���������� ���� �ε��� �ȉ��.
			delete MapImage;       // ���������� ��� ����
			MapImage = nullptr;
			OutputDebugString(L"�÷��̾� �̹��� �ε� ����");
			MessageBox(g_hMainWindow, L"�÷��̾� �̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
		}
	}
	void Render(Gdiplus::Graphics* InGraphics);
	~Map();
private:
	Gdiplus::Bitmap* MapImage = nullptr;
};

