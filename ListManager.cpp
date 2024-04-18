//Incluir a biblioteca do windows
#include <windows.h>

//Declarar as variáveis constantes
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define ID_BUTTON_ADD 10

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
void Readd(HWND);

//Declarar as variáveis globais
HMENU hMenu;
int padding = 10;
int listHeight = 50;
int firstY = 10;
int listQuantity = 0;
HWND hwndButton;

//Exibição da janela principal
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    //Configuração da janela
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"WindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc))
        return -1;

    //Criação da janela
    CreateWindowW(L"WindowClass", L"Schedule", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 600, 800, NULL, NULL, NULL, NULL);

    //Loop de mensagem
    MSG msg = {0};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

//Procedimento da janela principal
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    //Execução dos botões
    case WM_COMMAND:
        switch (msg)
        {
        case WM_COMMAND:
            switch (wp)
            {
                case ID_BUTTON_ADD:
                {
                    CreateWindowW(L"BUTTON", L"Nova Tarefa", WS_VISIBLE | WS_CHILD | BS_LEFT, 0, (firstY + padding + listHeight) * listQuantity, 800, listHeight, hWnd, NULL, NULL, NULL);
                    listQuantity++;
                    DestroyWindow(hwndButton);
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateWindow(hWnd);
                    break;
                }
            case FILE_MENU_EXIT:
                DestroyWindow(hWnd);
                return 0;
            }
            break;
        }
    //Criação Imediata
    case WM_CREATE:
        AddMenus(hWnd);
        AddControls(hWnd);
        return 0;
    //Fechamento da janela
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

//Criação dos Menus
void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenuW(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New File");
    AppendMenuW(hFileMenu, MF_STRING, FILE_MENU_OPEN, L"Open File");
    AppendMenuW(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenuW(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");

    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
    AppendMenuW(hMenu, MF_STRING, NULL, L"Help");

    SetMenu(hWnd, hMenu);
}


//Criação dos controles
void AddControls(HWND hWnd)
{
    RECT rect;
    GetClientRect(hWnd, &rect);

    int windowWidth = rect.right - rect.left;

    int addY = 10;

    if(listQuantity > 0){
        addY = (firstY + padding + listHeight) * (listQuantity);
    }

    // Criação do botão
    CreateWindowW(L"BUTTON",                            // Definição que é um botão
                  L"+",                                 // Texto no botão
                  WS_VISIBLE | WS_CHILD | BS_TEXT,      // Estilos do botão
                  (windowWidth - 64) / 2,               // Posição X
                  addY,                                 // Posição Y
                  64,                                   // Largura
                  64,                                   // Altura
                  hWnd,                                 // Janela pai
                  (HMENU)ID_BUTTON_ADD,                 // Identificador do botão
                  NULL,
                  NULL);

    hwndButton = GetDlgItem(hWnd, ID_BUTTON_ADD);
}