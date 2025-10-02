#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include "enums.h"

using Point = Gdiplus::Point;
using PointF = Gdiplus::PointF;

/*
충돌처리
-원과 원의 겹침
 두 원의 반지름의 합과  두 원의 중심점간의 거리를 비교
 반지름의 합 > 중심점간의 거리 => 겹쳤다.
 반지름의 합 == 중심점간의 거리 => 접촉했다.
 반지름의 합 < 중심점간의 거리 => 안 겹쳤다.

 중심점간의 거리 : sqrt((x의 차이)^2 + (y의 차이)^2)



 -사각형과 사각형의 겹침(AABB)
  

  -원과 사각형의 겹침
*/