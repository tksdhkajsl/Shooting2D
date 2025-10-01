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
	ResourceManager(const ResourceManager&) = delete;	// 복사 생성자 삭제
	ResourceManager& operator=(const ResourceManager&) = delete; // 대입 연산자 삭제
	ResourceManager(const ResourceManager&&) = delete;	// 이동 생성자 삭제
	ResourceManager& operator=(const ResourceManager&&) = delete; // 이동 대입 연산자 삭제

	std::vector<RenderLayer*> RenderType;
};

//--싱글톤 클래스
//-- 게임에서 사용될 모든 이미지파일을 관리
//-- 원하는 이미지파일의 Bitmap 리턴
//-- enum class 활용하기