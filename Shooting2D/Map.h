#pragma once

extern HWND g_hMainWindow; // g_hMainWindow가 다른 파일에 있다는 것을 알려줌
extern Gdiplus::Point g_ScreenSize;
extern int PositionY;
using PointF = Gdiplus::PointF;

class Map
{
public:

	Map() = delete;
	Map(const wchar_t* InImagePath)
	{
		MapImage = new Gdiplus::Bitmap(InImagePath); // 플레이어 이미지 로딩
		if (MapImage->GetLastStatus() != Gdiplus::Ok)
		{
			// 정상적으로 파일 로딩이 안됬다.
			delete MapImage;       // 실패했으면 즉시 해제
			MapImage = nullptr;
			OutputDebugString(L"플레이어 이미지 로드 실패");
			MessageBox(g_hMainWindow, L"플레이어 이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
		}
	}
	void Render(Gdiplus::Graphics* InGraphics);
	~Map();
private:
	Gdiplus::Bitmap* MapImage = nullptr;
};

