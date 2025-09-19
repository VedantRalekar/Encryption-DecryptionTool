#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to encrypt a text using Caesar Cipher
string encryptCaesar(const string &text, int key) {
    string result = "";
    for (char c : text) {
        if (isupper(c))
            result += char(int(c - 65 + key) % 26 + 65);
        else if (islower(c))
            result += char(int(c - 97 + key) % 26 + 97);
        else
            result += c; // non-alphabetic characters remain unchanged
    }
    return result;
}

// Function to decrypt a text using Caesar Cipher
string decryptCaesar(const string &text, int key) {
    return encryptCaesar(text, 26 - key); // decryption is reverse of encryption
}

int main() {
    int choice;
    string filename, text;
    int key;

    cout << "=== File/Text Encryption & Decryption Tool ===\n";
    cout << "1. Encrypt Text/File\n2. Decrypt Text/File\nEnter choice: ";
    cin >> choice;
    cin.ignore(); // ignore newline

    if (choice != 1 && choice != 2) {
        cout << "Invalid choice!" << endl;
        return 0;
    }

    cout << "Enter text (or leave empty to use a file): ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Enter filename (with extension): ";
        getline(cin, filename);
        ifstream fileIn(filename);
        if (!fileIn) {
            cout << "File not found!" << endl;
            return 0;
        }
        text = string((istreambuf_iterator<char>(fileIn)), istreambuf_iterator<char>());
        fileIn.close();
    }

    cout << "Enter key (number of shifts): ";
    cin >> key;

    string result;
    if (choice == 1) {
        result = encryptCaesar(text, key);
        cout << "\nEncrypted Text:\n" << result << endl;
    } else {
        result = decryptCaesar(text, key);
        cout << "\nDecrypted Text:\n" << result << endl;
    }

    // Optionally, save to file
    char saveChoice;
    cout << "\nDo you want to save the result to a file? (y/n): ";
    cin >> saveChoice;
    if (saveChoice == 'y' || saveChoice == 'Y') {
        cout << "Enter output filename: ";
        cin >> filename;
        ofstream fileOut(filename);
        fileOut << result;
        fileOut.close();
        cout << "Saved to " << filename << endl;
    }

    return 0;
}
