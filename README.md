**Mini Encryption-Decryption Tool (C)**

A simple Windows GUI application written in C using the Windows API, allowing users to encrypt and decrypt text using a Caesar Cipher algorithm.

**Features**

Text Encryption – Shift letters using a user-defined key.

Text Decryption – Reverse the shift to retrieve the original message.

Graphical Interface – Built using native Windows controls (TextBox, Buttons, Static Labels).

Lightweight – No external libraries required.

Instant Processing – Results appear immediately.

<img width="633" height="342" alt="image" src="https://github.com/user-attachments/assets/34c1d7a2-00ac-4457-bd7c-5ff1e21f6aa9" />


**How It Works**

The tool uses a Caesar Cipher algorithm:

For encryption:

new_char = ((char - base + key) % 26) + base

For decryption:

new_char = ((char - base - key + 26) % 26) + base


 **Usage**

Enter the text you want to encrypt or decrypt.

Enter the key (shift value).

Click Encrypt or Decrypt.

The result will be shown instantly in the output box.

**License**

This project is open-source under the MIT License – you can freely use, modify, and distribute it.
