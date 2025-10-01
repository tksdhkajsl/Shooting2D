#pragma once
#include <Windows.h>
#include <vector>
#include"enums.h"

class ResourceManager
{
public:

private:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;	// ���� ������ ����
	ResourceManager& operator=(const ResourceManager&) = delete; // ���� ������ ����
	ResourceManager(const ResourceManager&&) = delete;	// �̵� ������ ����
	ResourceManager& operator=(const ResourceManager&&) = delete; // �̵� ���� ������ ����

	std::vector<RenderLayer*> RenderType;
};

//--�̱��� Ŭ����
//-- ���ӿ��� ���� ��� �̹��������� ����
//-- ���ϴ� �̹��������� Bitmap ����
//-- enum class Ȱ���ϱ�