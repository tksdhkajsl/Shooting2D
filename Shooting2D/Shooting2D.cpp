// Shooting2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Shooting2D.h"
#include "Map.h"

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__,__LINE__)

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


int InputX = 0;
int InputY = 0;
// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);  // 사용 안하는 파라메터 명시적으로 표시
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GDI+ 초기화
    ULONG_PTR Token;
    Gdiplus::GdiplusStartupInput StartupInput;
    Gdiplus::GdiplusStartup(&Token, &StartupInput, nullptr);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SHOOTING2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);                 // 1. 윈도우 클래스 등록

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))    // 2. 윈도우 실제 생성 및 초기화
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SHOOTING2D));

    MSG msg;

    // 3. 메시지 루프
    // 기본 메시지 루프입니다:(메세지 큐에 들어온 메세지들을 하나씩 처리하는 부분)
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 단축키 처리
        {
            TranslateMessage(&msg); // 메시지를 메시지 프로시저로 보내 메시지를 처리한다.
            DispatchMessage(&msg);
        }
    }

    // GDI+ 정리하기
    Gdiplus::GdiplusShutdown(Token);
    return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // 윈도우의 모양과 기본동작 등을 결정
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;  // 윈도우 프로시저 함수 등록
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHOOTING2D));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr; // 메뉴 제거
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 실제 윈도우 생성
    HWND hWnd = CreateWindowW(szWindowClass,
        L"2D Shooting for GDI+",
        // WS_OVERLAPPEDWINDOW에서 
        // WS_MAXIMIZEBOX(최대화 버튼 비활성화)와 WS_THICKFRAME(테두리잡고 크기 변경 금지)만 제외
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        200, 100,   // 시작 좌표(스크린 좌표계)
        400, 600,    // 크기
        nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);  // 윈도우 보여주기
    UpdateWindow(hWnd);          // 윈도우 업데이트하기(윈도우 화면 갱신)

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
  
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //맵그리기
    const int TILE_SIZE = 20;
    static bool PutKey = false;
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        
        Gdiplus::Graphics GraphicsInstance(hdc);    // Graphics객체 만들기

        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
       
        Gdiplus::Pen BluePen(Gdiplus::Color(255, 0, 0, 255), 2.0f);
        
        //3. 집모양만들기     
       Gdiplus::SolidBrush BlueBrush(Gdiplus::Color(255, 0, 0, 255));
        Gdiplus::Point Triangle[3] = {
            Gdiplus::Point(25 + InputX,50 + InputY),
            Gdiplus::Point(10 + InputX,100 + InputY),
            Gdiplus::Point(40 + InputX,100 + InputY)
        };
       // GraphicsInstance.FillPolygon(&RedBrush, Triangle, 3);
        GraphicsInstance.DrawRectangle(&BluePen, 70 + InputX, 100 + InputY, 10, 10);
        // 타일 하나의 크기를 정의합니다.
        

        // maze 배열을 순회하며 벽(1)을 그립니다.
        for (int y = 0; y < mazeheight; ++y)
        {
            for (int x = 0; x < mazewidth; ++x)
            {
                // 배열의 값이 1이면 (벽이면)
                if (Maze[y][x] == 1)
                {
                    // 해당 위치에 사각형을 그립니다.
                    // x좌표: x * TILE_SIZE, y좌표: y * TILE_SIZE
                    // 크기: TILE_SIZE x TILE_SIZE
                    GraphicsInstance.FillRectangle(&BlueBrush, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                }
            }
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            if (!PutKey)
            {
                OutputDebugStringW(L"왼쪽 키를 눌렀다.\n");
                InputX -= 10;
                PutKey = true;
                InvalidateRect(hWnd, nullptr, TRUE); //창을 다시 그리도록 요청(WM_PAINT 메세지가 들어간다.)
            }
            break;
        case VK_RIGHT:
            if (!PutKey)
            {
                OutputDebugStringW(L"오른쪽 키를 눌렀다.\n");
                InputX += 10;
                PutKey = true;
                InvalidateRect(hWnd, nullptr, TRUE);
            }
            break;
        case VK_UP:
            if (!PutKey)
            {
                OutputDebugStringW(L"위쪽  키를 눌렀다.\n");
                InputY -= 10;
                PutKey = true;
                InvalidateRect(hWnd, nullptr, TRUE);
            }
            break;
        case VK_DOWN:
            if (!PutKey)
            {
                OutputDebugStringW(L"아래쪽 키를 눌렀다.\n");
                InputY += 10;
                PutKey = true;
                InvalidateRect(hWnd, nullptr, TRUE);
            }
            break;

        case VK_ESCAPE:
            DestroyWindow(hWnd);    // hWnd 창을 닫아라 -> 프로그램을 꺼라(WM_DESTROY 메세지가 들어감)
        break;      

        }
        break;
        // 2. WM_KEYUP 메시지 처리 추가
    case WM_KEYUP:
        switch (wParam)
        {
        case VK_LEFT:
            PutKey = false; // 키를 떼면 상태를 어짐(false)으로 변경
            break;
        case VK_RIGHT:
            PutKey = false;
            break;
        case VK_UP:
            PutKey = false;
            break;
        case VK_DOWN:

            PutKey = false;
            break;
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//실습
// 1. 집모양을 그리고 키보드 입력으로 위아래좌우로 움직이기
// 2. 눌르고 있을 때 한번만 움직여야 한다.




// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
