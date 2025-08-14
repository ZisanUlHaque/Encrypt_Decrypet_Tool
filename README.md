**Mini Encryption-Decryption Tool (C)**

A simple Windows GUI application written in C using the Windows API, allowing users to encrypt and decrypt text using a Caesar Cipher algorithm.

**Features**

Text Encryption – Shift letters using a user-defined key.

Text Decryption – Reverse the shift to retrieve the original message.

Graphical Interface – Built using native Windows controls (TextBox, Buttons, Static Labels).

Lightweight – No external libraries required.

Instant Processing – Results appear immediately.

<img width="632" height="342" alt="image" src="https://github.com/user-attachments/assets/1c71f8f8-9fe3-480c-bd87-939d9e09dfdc" />

**How It Works**

The tool uses a Caesar Cipher algorithm:

For encryption:

new_char = ((char - base + key) % 26) + base

For decryption:

new_char = ((char - base - key + 26) % 26) + base

## 📂 File Structure

<details>
<summary>Show structure</summary>

```text
MiniEncrypt/
├─ MiniEncrypt.c
├─ README.md
└─ screenshot.png


⚙️ Compilation & Running
Using GCC (MinGW) on Windows:
gcc MiniEncrypt.c -o MiniEncrypt.exe -mwindows
MiniEncrypt.exe

Using Visual Studio:

Create a Win32 Project.

Replace main.c content with MiniEncrypt.c.

Build and run.

 **Usage**

Enter the text you want to encrypt or decrypt.

Enter the key (shift value).

Click Encrypt or Decrypt.

The result will be shown instantly in the output box.

**License**

This project is open-source under the MIT License – you can freely use, modify, and distribute it.
