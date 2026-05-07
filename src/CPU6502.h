#ifndef CPU6502_H
#define CPU6502_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
using namespace std;

class CPU6502
{

public:
    uint8_t A;             // Accumulator
    uint8_t X;             // X Register
    uint8_t Y;             // Y Register
    uint8_t SP;            // Stack Pointer
    uint16_t PC;           // Program Counter
    bool N, Z, C, V, I, D; // Status flags
    vector<uint8_t> memory;
    ostringstream output;
    // Constructor
    CPU6502();

    // Memory helpers
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t val);
    uint16_t read16(uint16_t addr);
    uint16_t read16_wraparound(uint16_t addr);

    // Stack helpers
    void push(uint8_t v);
    uint8_t pop();

    // Status helpers
    uint8_t packP(bool breakFlagPush);
    void unpackP(uint8_t p);
    void updateNZ(uint8_t val);

    // Addressing Helpers
    uint8_t imm();
    uint16_t zp();
    uint16_t zpX();
    uint16_t zpY();
    uint16_t abs16();
    uint16_t absX();
    uint16_t absY();
    uint16_t indX();
    uint16_t indY();

    // Instruction decoder / executer
    bool step();
    void run();

    // Instructions

    // Load & Store Instructions
    void LDA(uint8_t val);
    void LDX(uint8_t val);
    void LDY(uint8_t val);
    void STA(uint16_t addr);
    void STX(uint16_t addr);
    void STY(uint16_t addr);

    // Transfer Instructions
    void TAX();
    void TAY();
    void TSX();
    void TXA();
    void TXS();
    void TYA();

    // Stack Instructions
    void PHA();
    void PHP();
    void PLA();
    void PLP();

    // Logical Instructions
    void ORA(uint8_t val);
    void AND(uint8_t val);
    void BIT(uint8_t val);
    void EOR(uint8_t val);

    // Arithmetic Instructions
    void ADC(uint8_t val);
    void SBC(uint8_t val);
    void CMP(uint8_t val);
    void CPX(uint8_t val);
    void CPY(uint8_t val);

    // Increment & Decrement Instructions
    void DEC(uint16_t addr);
    void DEX();
    void DEY();
    void INC(uint16_t addr);
    void INX();
    void INY();

    // Shift & Rotate Instructions
    void ASL(bool accumulator, uint16_t addr);
    void LSR(bool accumulator, uint16_t addr);
    void ROL(bool accumulator, uint16_t addr);
    void ROR(bool accumulator, uint16_t addr);

    // Branch Instructions
    void BCC(uint8_t val);
    void BCS(uint8_t val);
    void BEQ(uint8_t val);
    void BMI(uint8_t val);
    void BNE(uint8_t val);
    void BPL(uint8_t val);
    void BVC(uint8_t val);
    void BVS(uint8_t val);

    // Jump / Call / Return Instructions
    void JMP(uint16_t addr);
    void JSR(uint16_t addr);
    void RTI();
    void RTS();

    // Flag Control
    void CLC();
    void CLD();
    void CLI();
    void CLV();
    void SEC();
    void SED();
    void SEI();

    // System & Processor Control
    bool BRK();
    void NOP();
};

#endif
