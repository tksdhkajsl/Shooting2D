#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include "enums.h"

using Point = Gdiplus::Point;
using PointF = Gdiplus::PointF;

/*
�浹ó��
-���� ���� ��ħ
 �� ���� �������� �հ�  �� ���� �߽������� �Ÿ��� ��
 �������� �� > �߽������� �Ÿ� => ���ƴ�.
 �������� �� == �߽������� �Ÿ� => �����ߴ�.
 �������� �� < �߽������� �Ÿ� => �� ���ƴ�.

 �߽������� �Ÿ� : sqrt((x�� ����)^2 + (y�� ����)^2)



 -�簢���� �簢���� ��ħ(AABB)
  

  -���� �簢���� ��ħ
*/