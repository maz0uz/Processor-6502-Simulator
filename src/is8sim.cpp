#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdint>
#include "CPU6502.h"
using namespace std;

void runBinaryFile(const string &filename);

int main(int argc, char *argv[])
{
    cout << "   6502 CPU Simulator  " << endl;

    if (argc > 1)
        runBinaryFile(argv[1]);
    else
        cout << "Invalid File Path. Exiting\n";

    return 0;
}

void runBinaryFile(const string &filename)
{
    ifstream f(filename, ios::binary);
    if (!f)
    {
        cerr << "Cannot open file " << filename << endl;
        return;
    }

    vector<uint8_t> data((istreambuf_iterator<char>(f)), {});
    CPU6502 cpu;

    // Load binary into memory
    for (size_t i = 0; i < data.size() && i < cpu.memory.size(); ++i)
        cpu.memory[i] = data[i];

    // Set PC from reset vector
    cpu.PC = uint16_t(cpu.memory[0xFFFC]) | (uint16_t(cpu.memory[0xFFFD]) << 8);

    cout << "Loaded " << data.size() << " bytes from " << filename << endl;
    cout << "Starting execution at $" << hex << setw(4) << setfill('0') << cpu.PC << endl;

    cpu.run();
    std::cout << "\n[Program Output]\n"
          << cpu.output.str() << std::endl;

}