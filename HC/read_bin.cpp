#include <fstream>
#include <iostream>
#include <bitset>
using namespace std;

void view_binary_file(const string &file_path)
{
    ifstream inFile(file_path, ios::binary);
    if (!inFile.is_open())
    {
        cerr << "Error: Unable to open file: " << file_path << endl;
        return;
    }

    cout << "Binary File Content:\n";
    char byte;
    while (inFile.read(&byte, sizeof(char)))
    {
        // Print each byte as binary and its ASCII equivalent if printable
        cout << bitset<8>(byte) << " (" << (isprint(byte) ? byte : '.') << ")\n";
    }

    inFile.close();
}

int main()
{
    view_binary_file("output.huf");
    return 0;
}
