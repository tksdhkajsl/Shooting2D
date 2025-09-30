#pragma once
#include <unordered_map>
#include <Windows.h>
#include <gdiplus.h>
#include "enums.h"

// extern : �ڿ� �ִ� ������ �ٸ� ���Ͽ� ������ �Ǿ� �ִ�.
extern HWND g_hMainWindow; // g_hMainWindow�� �ٸ� ���Ͽ� �ִٴ� ���� �˷���
extern Gdiplus::Point g_ScreenSize;

using PointF = Gdiplus::PointF;
class Player
{
public:
	Player() = delete;
	Player(const wchar_t* InImagePath)
	{
		Position.X = 300;
		Position.Y = 700;

		KeyWasPressedMap[InputDirection::Up] = false;
		KeyWasPressedMap[InputDirection::Down] = false;
		KeyWasPressedMap[InputDirection::Left] = false;
		KeyWasPressedMap[InputDirection::Right] = false;

		Image = new Gdiplus::Bitmap(InImagePath); // �÷��̾� �̹��� �ε�
		if (Image->GetLastStatus() != Gdiplus::Ok)
		{
			// ���������� ���� �ε��� �ȉ��.
			delete Image;       // ���������� ��� ����
			Image = nullptr;
			OutputDebugString(L"�÷��̾� �̹��� �ε� ����");
			MessageBox(g_hMainWindow, L"�÷��̾� �̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
		}
	}	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.
	~Player();

	void Render(Gdiplus::Graphics* InGraphics);
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

private:
	// �÷��̾ �׷��� ũ��
	static constexpr int PixelSize = 64;

	// �÷��̾��� �߽���
	PointF Pivot = { 0.5f, 0.5f }; // Pivot �⺻ ���� �Ѱ��

	// �÷��̾��� ��ġ
	PointF Position = { 0.0f, 0.0f };

	// �÷��̾��� �̵� �ӵ�
	float Speed = 10.0f;

	// �÷��̾� Ű �Է� ����
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	// �÷��̾� �̹����� ������� ��Ʈ��
	Gdiplus::Bitmap* Image = nullptr;   // �÷��̾ �׷��� ����		
};

// �ǽ�
// 1. �÷��̾��� �������� �¿�� ���� ��ȯ�ǰ� �����
// 2. �帣�� ��� �����
// 3. �÷��̾��� �����̴� �ӵ��� ��ǻ�� ���ɿ� ������ �������� ��� �ؾ��ϴ°�?(��ȭ)