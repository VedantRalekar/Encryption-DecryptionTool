#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to encrypt text using Caesar Cipher
string encryptCaesar(const string &text, int key) {
    string result = "";
    for (char c : text) {
        if (isupper(c))
            result += char((c - 'A' + key) % 26 + 'A');
        else if (islower(c))
            result += char((c - 'a' + key) % 26 + 'a');
        else
            result += c;
    }
    return result;
}

// Function to decrypt text using Caesar Cipher
string decryptCaesar(const string &text, int key) {
    return encryptCaesar(text, 26 - key);
}

// Function to read file content
bool readFile(const string &filename, string &content) {
    ifstream file(filename);
    if (!file) return false;
    content = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return true;
}

// Function to write content to file
bool writeFile(const string &filename, const string &content) {
    ofstream file(filename, ios::trunc);
    if (!file) return false;
    file << content;
    file.close();
    return true;
}

void processText() {
    string text, filename, result;
    int key;
    char saveChoice;

    cout << "Enter text (or leave empty to use a file): ";
    cin.ignore(); // clear input buffer
    getline(cin, text);

    if (text.empty()) {
        cout << "Enter filename (with extension): ";
        getline(cin, filename);
        if (!readFile(filename, text)) {
            cout << "File not found!" << endl;
            return;
        }
    }

    cout << "Enter key (number of shifts, positive integer): ";
    cin >> key;
    if (key < 0) key = (key % 26 + 26) % 26; // normalize key

    int choice;
    cout << "1. Encrypt\n 2. Decrypt\nChoice: ";
    cin >> choice;

    if (choice == 1)
        result = encryptCaesar(text, key);
    else if (choice == 2)
        result = decryptCaesar(text, key);
    else {
        cout << "Invalid choice!" << endl;
        return;
    }

    cout << "\nResult:\n" << result << endl;

    cout << "\nDo you want to save the result to a file? (y/n): ";
    cin >> saveChoice;
    if (saveChoice == 'y' || saveChoice == 'Y') {
        cout << "Enter output filename: ";
        cin >> filename;
        if (writeFile(filename, result))
            cout << "Saved to " << filename << endl;
        else
            cout << "Failed to save file!" << endl;
    }
}

int main() {
    int menuChoice;

    cout << "=== Welcome to Enhanced Caesar Cipher Encryption/Decryption Tool ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Encrypt/Decrypt Text or File\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1: processText();
             break;
            case 0: cout << "Exiting program. Goodbye!\n";
             break;
            default: cout << "Invalid choice, try again.\n";
        }

    } while (menuChoice != 0);

    return 0;
}
