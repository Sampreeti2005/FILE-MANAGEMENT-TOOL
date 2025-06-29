#include <iostream>
#include <string>
using namespace std;

// Function to compress using Run-Length Encoding (RLE)
string compress(const string& input) {
    string result = "";
    int count = 1;
    for (size_t i = 0; i < input.length(); i++) {
        while (i + 1 < input.length() && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        result += input[i] + to_string(count);
        count = 1;
    }
    return result;
}

// Function to decompress RLE encoded string
string decompress(const string& input) {
    string result = "";
    for (size_t i = 0; i < input.length(); i += 2) {
        char ch = input[i];
        int count = input[i + 1] - '0'; // works for single-digit counts (0–9)
        result.append(count, ch);
    }
    return result;
}

int main() {
    int choice;
    string data, compressedData, decompressedData;

    do {
        cout << "\n====== FILE COMPRESSOR TOOL (RLE) ======\n";
        cout << "1. Compress a string\n";
        cout << "2. Decompress a string\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter string to compress (e.g., aaabbbcc): ";
                getline(cin, data);
                compressedData = compress(data);
                cout << "Compressed result: " << compressedData << endl;
                break;

            case 2:
                cout << "Enter RLE compressed string (e.g., a3b2c2): ";
                getline(cin, data);
                decompressedData = decompress(data);
                cout << " Decompressed result: " << decompressedData << endl;
                break;

            case 3:
                cout << "Exiting...\n";
                break;

            default:
                cout << " Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
