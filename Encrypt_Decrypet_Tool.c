#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Control IDs
#define ID_INPUT       101
#define ID_KEY         102
#define ID_ENCRYPT     103
#define ID_DECRYPT     104
#define ID_OUTPUT      105
#define ID_CLEAR       106

HWND txtInput, txtKey, txtOutput;
HWND btnEncrypt, btnDecrypt, btnClear;

// Custom Caesar Cipher Encrypt
void CipherEncrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + shift) % 26 + base;
        }
    }
}

// Custom Caesar Cipher Decrypt
void CipherDecrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base - shift + 26) % 26 + base;
        }
    }
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    char buffer[512], keyBuffer[10];
    int keyValue;

    switch (msg) {
    case WM_CREATE:
        CreateWindow("STATIC", "Enter Text:", WS_CHILD | WS_VISIBLE,
            20, 20, 100, 20, hwnd, NULL, NULL, NULL);

        txtInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
            20, 45, 460, 25, hwnd, (HMENU)ID_INPUT, NULL, NULL);

        CreateWindow("STATIC", "Key (1-25):", WS_CHILD | WS_VISIBLE,
            20, 85, 100, 20, hwnd, NULL, NULL, NULL);

        txtKey = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
            20, 110, 80, 25, hwnd, (HMENU)ID_KEY, NULL, NULL);

        btnEncrypt = CreateWindow("BUTTON", "Encrypt", WS_CHILD | WS_VISIBLE,
            120, 110, 100, 25, hwnd, (HMENU)ID_ENCRYPT, NULL, NULL);

        btnDecrypt = CreateWindow("BUTTON", "Decrypt", WS_CHILD | WS_VISIBLE,
            240, 110, 100, 25, hwnd, (HMENU)ID_DECRYPT, NULL, NULL);

        btnClear = CreateWindow("BUTTON", "Clear", WS_CHILD | WS_VISIBLE,
            360, 110, 100, 25, hwnd, (HMENU)ID_CLEAR, NULL, NULL);

        CreateWindow("STATIC", "Result:", WS_CHILD | WS_VISIBLE,
            20, 160, 100, 20, hwnd, NULL, NULL, NULL);

        txtOutput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
            20, 185, 460, 25, hwnd, (HMENU)ID_OUTPUT, NULL, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_ENCRYPT:
        case ID_DECRYPT:
            GetWindowText(txtInput, buffer, sizeof(buffer));
            GetWindowText(txtKey, keyBuffer, sizeof(keyBuffer));
            keyValue = atoi(keyBuffer);

            if (strlen(buffer) == 0) {
                MessageBox(hwnd, "Please enter text to process.", "Error", MB_ICONERROR);
                break;
            }
            if (keyValue < 1 || keyValue > 25) {
                MessageBox(hwnd, "Please enter a valid key (1-25).", "Error", MB_ICONERROR);
                break;
            }

            if (LOWORD(wParam) == ID_ENCRYPT) {
                CipherEncrypt(buffer, keyValue);
                SetWindowText(hwnd, "Mini Encryptor - Encryption Done");
            } else {
                CipherDecrypt(buffer, keyValue);
                SetWindowText(hwnd, "Mini Encryptor - Decryption Done");
            }
            SetWindowText(txtOutput, buffer);
            break;

        case ID_CLEAR:
            SetWindowText(txtInput, "");
            SetWindowText(txtKey, "");
            SetWindowText(txtOutput, "");
            SetWindowText(hwnd, "Mini Encryptor - Ready");
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// WinMain
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "MiniEncryptor";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("MiniEncryptor", "Mini Encryptor - Ready",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, 300, 200, 520, 280,
        NULL, NULL, hInst, NULL);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
