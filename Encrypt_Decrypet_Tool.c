#include <windows.h>
#include <string.h>
#include <stdlib.h>

// Global handles
HWND hInput, hKey, hOutput, hEncrypt, hDecrypt;
HWND hInputLabel, hKeyLabel, hOutputLabel;

// Encrypt Function
void encryptText(char *text, int key) {
    for(int i=0; i<strlen(text); i++){
        if(text[i]>='a' && text[i]<='z') text[i]=((text[i]-'a'+key)%26)+'a';
        else if(text[i]>='A' && text[i]<='Z') text[i]=((text[i]-'A'+key)%26)+'A';
    }
}

// Decrypt Function
void decryptText(char *text, int key){
    for(int i=0; i<strlen(text); i++){
        if(text[i]>='a' && text[i]<='z') text[i]=((text[i]-'a'-key+26)%26)+'a';
        else if(text[i]>='A' && text[i]<='Z') text[i]=((text[i]-'A'-key+26)%26)+'A';
    }
}

// Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CREATE:
            // Input Section
            hInputLabel = CreateWindow("STATIC", "Input Text:", WS_CHILD | WS_VISIBLE,
                                       20, 20, 150, 20, hwnd, NULL, NULL, NULL);

            hInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  20, 45, 450, 25, hwnd, NULL, NULL, NULL);

            // Key Section
            hKeyLabel = CreateWindow("STATIC", "Key:", WS_CHILD | WS_VISIBLE,
                                     20, 85, 100, 20, hwnd, NULL, NULL, NULL);

            hKey = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                20, 110, 100, 25, hwnd, NULL, NULL, NULL);

            // Buttons (center aligned)
            hEncrypt = CreateWindow("BUTTON", "Encrypt", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    150, 110, 120, 28, hwnd, (HMENU)1, NULL, NULL);

            hDecrypt = CreateWindow("BUTTON", "Decrypt", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                    290, 110, 120, 28, hwnd, (HMENU)2, NULL, NULL);

            // Output Section
            hOutputLabel = CreateWindow("STATIC", "Output Text:", WS_CHILD | WS_VISIBLE,
                                        20, 160, 150, 20, hwnd, NULL, NULL, NULL);

            hOutput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                                   20, 185, 450, 25, hwnd, NULL, NULL, NULL);
            break;

        case WM_COMMAND:
            if(LOWORD(wParam) == 1 || LOWORD(wParam) == 2) { // Encrypt or Decrypt
                char text[500], keyText[10];
                int key;
                GetWindowText(hInput, text, 500);
                GetWindowText(hKey, keyText, 10);
                key = atoi(keyText);

                if(LOWORD(wParam) == 1)
                    encryptText(text, key);
                else
                    decryptText(text, key);

                SetWindowText(hOutput, text);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Main Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MiniEncrypt";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // Window Color

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, "MiniEncrypt", "Mini Encryption-Decryption Tool",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 200, 520, 280,
        NULL, NULL, hInstance, NULL
    );

    MSG msg = {0};
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
