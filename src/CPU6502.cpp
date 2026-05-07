#include "../CPU6502.h"

#include <cstdint>

CPU6502 ::CPU6502()
{
    A = 0;
    X = 0;
    Y = 0;
    SP = 0xFF;
    PC = 0;
    N = 0, Z = 0, C = 0, V = 0, I = 0, D = 0;
    memory.resize(65536, 0);
}

bool CPU6502::step()
{
    uint8_t opcode = read(PC++);

    switch (opcode)
    {
        case 0x00:
            cout<<"BRK"<<endl;
            return BRK();
    // Load & Store Instructions
    // LDA
    case 0xA9:
    {
        uint8_t operand = imm();
        cout << "LDA #$" << hex << setw(2) << setfill('0') << (int)operand << endl;
        LDA(operand);
        break;
    }
    case 0xA5:
    {
        uint8_t addr = zp();
        cout << "LDA $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        LDA(read(addr));
        break;
    }
    case 0xB5:
    {
        uint8_t addr = zpX();
        cout << "LDA $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        LDA(read(addr));
        break;
    }
    case 0xAD:
    {
        uint16_t addr = abs16();
        cout << "LDA $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        LDA(read(addr));
        break;
    }
    case 0xBD:
    {
        uint16_t addr = absX();
        cout << "LDA $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        LDA(read(addr));
        break;
    }
    case 0xB9:
    {
        uint16_t addr = absY();
        cout << "LDA $" << hex << setw(4) << setfill('0') << (int)addr << ",Y" << endl;
        LDA(read(addr));
        break;
    }
    case 0xA1:
    {
        uint16_t addr = indX();
        cout << "LDA ($" << hex << setw(2) << setfill('0') << (int)addr << ",X)" << endl;
        LDA(read(addr));
        break;
    }
    case 0xB1:
    {
        uint16_t addr = indY();
        cout << "LDA ($" << hex << setw(2) << setfill('0') << (int)addr << "),Y" << endl;
        LDA(read(addr));
        break;
    }

    // LDX
    case 0xA2:
    {
        uint8_t operand = imm();
        cout << "LDX #$" << hex << setw(2) << setfill('0') << (int)operand << endl;
        LDX(operand);
        break;
    }
    case 0xA6:
    {
        uint8_t addr = zp();
        cout << "LDX $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        LDX(read(addr));
        break;
    }
    case 0xB6:
    {
        uint8_t addr = zpY();
        cout << "LDX $" << hex << setw(2) << setfill('0') << (int)addr << ",Y" << endl;
        LDX(read(addr));
        break;
    }
    case 0xAE:
    {
        uint16_t addr = abs16();
        cout << "LDX $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        LDX(read(addr));
        break;
    }
    case 0xBE:
    {
        uint16_t addr = absY();
        cout << "LDX $" << hex << setw(4) << setfill('0') << (int)addr << ",Y" << endl;
        LDX(read(addr));
        break;
    }

    // LDY
    case 0xA0:
    {
        uint8_t operand = imm();
        cout << "LDY #$" << hex << setw(2) << setfill('0') << (int)operand << endl;
        LDY(operand);
        break;
    }
    case 0xA4:
    {
        uint8_t addr = zp();
        cout << "LDY $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        LDY(read(addr));
        break;
    }
    case 0xB4:
    {
        uint8_t addr = zpX();
        cout << "LDY $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        LDY(read(addr));
        break;
    }
    case 0xAC:
    {
        uint16_t addr = abs16();
        cout << "LDY $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        LDY(read(addr));
        break;
    }
    case 0xBC:
    {
        uint16_t addr = absX();
        cout << "LDY $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        LDY(read(addr));
        break;
    }

    // STA
    case 0x85:
    {
        uint8_t addr = zp();
        cout << "STA $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        STA(addr);
        break;
    }
    case 0x95:
    {
        uint8_t addr = zpX();
        cout << "STA $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        STA(addr);
        break;
    }
    case 0x8D:
    {
        uint16_t addr = abs16();
        cout << "STA $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        STA(addr);
        break;
    }
    case 0x9D:
    {
        uint16_t addr = absX();
        cout << "STA $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        STA(addr);
        break;
    }
    case 0x99:
    {
        uint16_t addr = absY();
        cout << "STA $" << hex << setw(4) << setfill('0') << (int)addr << ",Y" << endl;
        STA(addr);
        break;
    }
    case 0x81:
    {
        uint16_t addr = indX();
        cout << "STA ($" << hex << setw(2) << setfill('0') << (int)addr << ",X)" << endl;
        STA(addr);
        break;
    }
    case 0x91:
    {
        uint16_t addr = indY();
        cout << "STA ($" << hex << setw(2) << setfill('0') << (int)addr << "),Y" << endl;
        STA(addr);
        break;
    }

    // STX
    case 0x86:
    {
        uint8_t addr = zp();
        cout << "STX $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        STX(addr);
        break;
    }
    case 0x96:
    {
        uint8_t addr = zpY();
        cout << "STX $" << hex << setw(2) << setfill('0') << (int)addr << ",Y" << endl;
        STX(addr);
        break;
    }
    case 0x8E:
    {
        uint16_t addr = abs16();
        cout << "STX $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        STX(addr);
        break;
    }

    // STY
    case 0x84:
    {
        uint8_t addr = zp();
        cout << "STY $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        STY(addr);
        break;
    }
    case 0x94:
    {
        uint8_t addr = zpX();
        cout << "STY $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        STY(addr);
        break;
    }
    case 0x8C:
    {
        uint16_t addr = abs16();
        cout << "STY $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        STY(addr);
        break;
    }

    // Transfer Instructions
    // TAX
    case 0xAA: { cout << "TAX" << endl; TAX(); break; }

    // TAY
    case 0xA8: { cout << "TAY" << endl; TAY(); break; }

    // TSX
    case 0xBA: { cout << "TSX" << endl; TSX(); break; }

    // TXA
    case 0x8A: { cout << "TXA" << endl; TXA(); break; }

    // TXS
    case 0x9A: { cout << "TXS" << endl; TXS(); break; }

    // TYA
    case 0x98: { cout << "TYA" << endl; TYA(); break; }

    // Stack Instructions
    // PHA
    case 0x48: {
        cout<<"PHA"<<endl; PHA(); break;
    }

    // PHP
    case 0x08: {
        cout<<"PHP"<<endl; PHP(); break;
    }

    // PLA
    case 0x68: {
        cout<<"PLA"<<endl; PLA(); break;
    }

    // PLP
    case 0x28: {
        cout<<"PLP"<<endl; PLP(); break;
    }

    // Logical Instructions
    // ORA
    case 0x09:
    {
        uint8_t operand = imm();
        cout << "ORA #$" << hex << setw(2) << setfill('0') << (int)operand << endl;
        ORA(operand);
        break;
    }
    case 0x05:
    {
        uint8_t addr = zp();
        cout << "ORA $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        ORA(read(addr));
        break;
    }
    case 0x15:
    {
        uint8_t addr = zpX();
        cout << "ORA $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        ORA(read(addr));
        break;
    }
    case 0x0D:
    {
        uint16_t addr = abs16();
        cout << "ORA $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        ORA(read(addr));
        break;
    }
    case 0x1D:
    {
        uint16_t addr = absX();
        cout << "ORA $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        ORA(read(addr));
        break;
    }

    case 0x19:
    case 0x01:
    {
        uint16_t addr = indX();
        cout << "ORA ($" << hex << setw(2) << setfill('0') << (int)addr << ",X)" << endl;
        ORA(read(addr));
        break;
    }
    case 0x11:
    {
        uint16_t addr = indY();
        cout << "ORA ($" << hex << setw(2) << setfill('0') << (int)addr << "),Y" << endl;
        ORA(read(addr));
        break;
    }

    // AND
    case 0x29:
    {
        uint8_t operand = imm();
        cout << "AND #$" << hex << setw(2) << setfill('0') << (int)operand << endl;
        AND(operand);
        break;
    }
    case 0x25:
    {
        uint8_t addr = zp();
        cout << "AND $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        AND(read(addr));
        break;
    }
    case 0x35:
    {
        uint8_t addr = zpX();
        cout << "AND $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        AND(read(addr));
        break;
    }
    case 0x2D:
    {
        uint16_t addr = abs16();
        cout << "AND $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        AND(read(addr));
        break;
    }
    case 0x3D:
    {
        uint16_t addr = absX();
        cout << "AND $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        AND(read(addr));
        break;
    }
    case 0x39:
    {
        uint16_t addr = absX();
        cout << "AND $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        AND(read(addr));
        break;
    }
    case 0x21:
    {
        uint16_t addr = indX();
        cout << "AND ($" << hex << setw(2) << setfill('0') << (int)addr << ",X)" << endl;
        AND(read(addr));
        break;
    }
    case 0x31:
    {
        uint16_t addr = indY();
        cout << "AND ($" << hex << setw(2) << setfill('0') << (int)addr << "),Y" << endl;
        AND(read(addr));
        break;
    }
    // BIT
    case 0x24:
    {
        uint8_t addr = zp();
        cout << "BIT $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        BIT(read(addr));
        break;
    }
    case 0x2C:
    {
        uint16_t addr = abs16();
        cout << "BIT $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        BIT(read(addr));
        break;
    }


    // EOR
    case 0x49:
    case 0x45:
    {
        uint8_t addr = zp();
        cout << "EOR $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        EOR(read(addr));
        break;
    }
    case 0x55:
    {
        uint8_t addr = zpX();
        cout << "EOR $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        EOR(read(addr));
        break;
    }
    case 0x4D:
    {
        uint16_t addr = abs16();
        cout << "EOR $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        EOR(read(addr));
        break;
    }
    case 0x5D:
    {
        uint16_t addr = absX();
        cout << "EOR $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        EOR(read(addr));
        break;
    }
    case 0x59:
    {
        uint16_t addr = absY();
        cout << "EOR $" << hex << setw(4) << setfill('0') << (int)addr << ",Y" << endl;
        EOR(read(addr));
        break;
    }
    case 0x41:
    {
        uint16_t addr = indX();
        cout << "EOR ($" << hex << setw(2) << setfill('0') << (int)addr << ",X)" << endl;
        EOR(read(addr));
        break;
    }
    case 0x51:
    {
        uint16_t addr = indY();
        cout << "EOR ($" << hex << setw(2) << setfill('0') << (int)addr << "),Y" << endl;
        EOR(read(addr));
        break;
    }

    // Arithmetic Instructions
    // ADC
    case 0x69:
    {
        uint8_t operand = imm();  // read next byte
        cout << "ADC #$" << hex << setw(2) << setfill('0') << (int)operand << endl;
        ADC(operand);  // execute ADC
        break;
    }
    case 0x65:
    {
        uint8_t addr = zp();
        cout << "ADC $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        ADC(read(addr));
        break;
    }
    case 0x75:
    {
        uint8_t addr = zpX();
        cout << "ADC $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        ADC(read(addr));
        break;
    }
    case 0x6D:
    {
        uint16_t addr = abs16();
        cout << "ADC $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        ADC(read(addr));
        break;
    }
    case 0x7D:
    {
        uint16_t addr = absX();
        cout << "ADC $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        ADC(read(addr));
        break;
    }
    case 0x79:
    {
        uint16_t addr = absY();
        cout << "ADC $" << hex << setw(4) << setfill('0') << (int)addr << ",Y" << endl;
        ADC(read(addr));
        break;
    }
    case 0x61:
    {
        uint16_t addr = indX();
        cout << "ADC ($" << hex << setw(2) << setfill('0') << (int)addr << ",X)" << endl;
        ADC(read(addr));
        break;
    }
    case 0x71:
    {
        uint16_t addr = indY();
        cout << "ADC ($" << hex << setw(2) << setfill('0') << (int)addr << "),Y" << endl;
        ADC(read(addr));
        break;
    }

    // SBC
    case 0xE9:
    {
        uint8_t operand = imm();
        cout << "SBC #$" << hex << setw(2) << setfill('0') << (int)operand << endl;
        SBC(operand);
        break;
    }
    case 0xE5:
    {
        uint8_t addr = zp();
        cout << "SBC $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        SBC(read(addr));
        break;
    }
    case 0xF5:
    {
        uint8_t addr = zpX();
        cout << "SBC $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        SBC(read(addr));
        break;
    }
    case 0xED:
    {
        uint16_t addr = abs16();
        cout << "SBC $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        SBC(read(addr));
        break;
    }
    case 0xFD:
    {
        uint16_t addr = absX();
        cout << "SBC $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        SBC(read(addr));
        break;
    }
    case 0xF9:
    {
        uint16_t addr = absY();
        cout << "SBC $" << hex << setw(4) << setfill('0') << (int)addr << ",Y" << endl;
        SBC(read(addr));
        break;
    }
    case 0xE1:
    {
        uint16_t addr = indX();
        cout << "SBC ($" << hex << setw(2) << setfill('0') << (int)addr << ",X)" << endl;
        SBC(read(addr));
        break;
    }
    case 0xF1:
    {
        uint16_t addr = indY();
        cout << "SBC ($" << hex << setw(2) << setfill('0') << (int)addr << "),Y" << endl;
        SBC(read(addr));
        break;
    }

    // CMP
    case 0xC9:
    {
        uint8_t operand = imm();
        cout << "CMP #$" << hex << setw(2) << setfill('0') << (int)operand << endl;
        CMP(operand);
        break;
    }
    case 0xC5:
    {
        uint8_t addr = zp();
        cout << "CMP $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        CMP(read(addr));
        break;
    }
    case 0xD5:
    {
        uint8_t addr = zpX();
        cout << "CMP $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        CMP(read(addr));
        break;
    }
    case 0xCD:
    {
        uint16_t addr = abs16();
        cout << "CMP $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        CMP(read(addr));
        break;
    }
    case 0xDD:
    {
        uint16_t addr = absX();
        cout << "CMP $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        CMP(read(addr));
        break;
    }
    case 0xD9:
    {
        uint16_t addr = absY();
        cout << "CMP $" << hex << setw(4) << setfill('0') << (int)addr << ",Y" << endl;
        CMP(read(addr));
        break;
    }
    case 0xC1:
    {
        uint16_t addr = indX();
        cout << "CMP ($" << hex << setw(2) << setfill('0') << (int)addr << ",X)" << endl;
        CMP(read(addr));
        break;
    }
    case 0xD1:
    {
        uint16_t addr = indY();
        cout << "CMP ($" << hex << setw(2) << setfill('0') << (int)addr << "),Y" << endl;
        CMP(read(addr));
        break;
    }

    // CPX
    case 0xE0:
    {
        uint8_t operand = imm();
        cout << "CPX #$" << hex << setw(2) << setfill('0') << (int)operand << endl;
        CPX(operand);
        break;
    }
    case 0xE4:
    {
        uint8_t addr = zp();
        cout << "CPX $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        CPX(read(addr));
        break;
    }
    case 0xEC:
    {
        uint16_t addr = abs16();
        cout << "CPX $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        CPX(read(addr));
        break;
    }

    // CPY
    case 0xC0:
    {
        uint8_t operand = imm();
        cout << "CPY #$" << hex << setw(2) << setfill('0') << (int)operand << endl;
        CPY(operand);
        break;
    }
    case 0xC4:
    {
        uint8_t addr = zp();
        cout << "CPY $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        CPY(read(addr));
        break;
    }
    case 0xCC:
    {
        uint16_t addr = abs16();
        cout << "CPY $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        CPY(read(addr));
        break;
    }

    // Increment & Decrement Instructions
    //  DEC
    case 0xC6:
    {
        uint8_t addr = zp();
        cout << "DEC $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        DEC(addr);
        break;
    }
    case 0xD6:
    {
        uint8_t addr = zpX();
        cout << "DEC $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        DEC(addr);
        break;
    }
    case 0xCE:
    {
        uint16_t addr = abs16();
        cout << "DEC $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        DEC(addr);
        break;
    }
    case 0xDE:
    {
        uint16_t addr = absX();
        cout << "DEC $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        DEC(addr);
        break;
    }
    // DEX
    case 0xCA: { cout << "DEX" << endl; DEX(); break; }

    // DEY
    case 0x88:
    {
        cout << "DEY" << endl;
        DEY();
        break;
    }
    // INC
    case 0xE6:
    {
        uint8_t addr = zp();
        cout << "INC $" << hex << setw(2) << setfill('0') << (int)addr << endl;
        INC(addr);
        break;
    }
    case 0xF6:
    {
        uint8_t addr = zpX();
        cout << "INC $" << hex << setw(2) << setfill('0') << (int)addr << ",X" << endl;
        INC(addr);
        break;
    }
    case 0xEE:
    {
        uint16_t addr = abs16();
        cout << "INC $" << hex << setw(4) << setfill('0') << (int)addr << endl;
        INC(addr);
        break;
    }
    case 0xFE:
    {
        uint16_t addr = absX();
        cout << "INC $" << hex << setw(4) << setfill('0') << (int)addr << ",X" << endl;
        INC(addr);
        break;
    }

    // INX
    case 0xE8:
    {
        cout << "INX" << endl;
        INX();
        break;
    }
    // INY
    case 0xC8:
    {
        cout << "INY" << endl;
        INY();
        break;
    }
    // Shift & Rotate Instructions
    // ASL
    case 0x0A: { cout << "ASL A" << endl; ASL(true, 0); break; }
    case 0x06: { uint16_t a = zp();  cout << "ASL $" << hex << (int)a << endl; ASL(false, a); break; }
    case 0x16: { uint16_t a = zpX(); cout << "ASL $" << hex << (int)a << ",X" << endl; ASL(false, a); break; }
    case 0x0E: { uint16_t a = abs16(); cout << "ASL $" << hex << (int)a << endl; ASL(false, a); break; }
    case 0x1E: { uint16_t a = absX();  cout << "ASL $" << hex << (int)a << ",X" << endl; ASL(false, a); break; }

    // LSR
    case 0x4A: { cout << "LSR A" << endl; LSR(true, 0); break; }
    case 0x46: { uint16_t a = zp();  cout << "LSR $" << hex << (int)a << endl; LSR(false, a); break; }
    case 0x56: { uint16_t a = zpX(); cout << "LSR $" << hex << (int)a << ",X" << endl; LSR(false, a); break; }
    case 0x4E: { uint16_t a = abs16(); cout << "LSR $" << hex << (int)a << endl; LSR(false, a); break; }
    case 0x5E: { uint16_t a = absX();  cout << "LSR $" << hex << (int)a << ",X" << endl; LSR(false, a); break; }


    // ROL
    case 0x2A: { cout << "ROL A" << endl; ROL(true, 0); break; }
    case 0x26: { uint16_t a = zp();  cout << "ROL $" << hex << (int)a << endl; ROL(false, a); break; }
    case 0x36: { uint16_t a = zpX(); cout << "ROL $" << hex << (int)a << ",X" << endl; ROL(false, a); break; }
    case 0x2E: { uint16_t a = abs16(); cout << "ROL $" << hex << (int)a << endl; ROL(false, a); break; }
    case 0x3E: { uint16_t a = absX();  cout << "ROL $" << hex << (int)a << ",X" << endl; ROL(false, a); break; }


    // ROR
    case 0x6A: { cout << "ROR A" << endl; ROR(true, 0); break; }
    case 0x66: { uint16_t a = zp();  cout << "ROR $" << hex << (int)a << endl; ROR(false, a); break; }
    case 0x76: { uint16_t a = zpX(); cout << "ROR $" << hex << (int)a << ",X" << endl; ROR(false, a); break; }
    case 0x6E: { uint16_t a = abs16(); cout << "ROR $" << hex << (int)a << endl; ROR(false, a); break; }
    case 0x7E: { uint16_t a = absX();  cout << "ROR $" << hex << (int)a << ",X" << endl; ROR(false, a); break; }

    // Branch Instructions
    // BCC
    case 0x90:
    {
        uint8_t offset = imm();
        cout << "BCC $" << hex << setw(2) << setfill('0') << (int)offset << endl;
        BCC(offset);
        break;
    }

    // BCS
    case 0xB0:
    {
        uint8_t offset = imm();
        cout << "BCS $" << hex << setw(2) << setfill('0') << (int)offset << endl;
        BCS(offset);
        break;
    }

    // BEQ
    case 0xF0:
    {
        uint8_t offset = imm();
        cout << "BEQ $" << hex << setw(2) << setfill('0') << (int)offset << endl;
        BEQ(offset);
        break;
    }
    // BMI
    case 0x30:
    {
    uint8_t offset = imm();
    cout << "BMI $" << hex << setw(2) << setfill('0') << (int)offset << endl;
    BMI(offset);
    break;
    }


    // BNE
    case 0xD0:
    {
        uint8_t operand = imm();
        cout << "BNE $" << hex << setw(2) << setfill('0') << (int)operand << endl;
        BNE(operand);
        break;
    }

    // BPL
    case 0x10:
    {
        uint8_t offset = imm();
        cout << "BPL $" << hex << setw(4) << setfill('0') << (PC + static_cast<int8_t>(offset)) << endl;
        BPL(offset);
        break;
    }

    // BVC
    case 0x50:
    {
        uint8_t offset = imm();
        cout << "BVC $" << hex << setw(2) << setfill('0') << (int)offset << endl;
        BVC(offset);
        break;
    }

    // BVS
    case 0x70:
    {
        uint8_t offset = imm();
        cout << "BVS $" << hex << setw(2) << setfill('0') << (int)offset << endl;
        BVS(offset);
        break;
    }

    // Jump / Call / Return Instructions
    // JMP
    case 0x4C: { uint16_t a = abs16(); cout << "JMP $" << hex << (int)a << endl; JMP(a); break; }
    case 0x6C: { uint16_t a = read16_wraparound(abs16()); cout << "JMP ($" << hex << (int)a << ")" << endl; JMP(a); break; }

    // JSR
    case 0x20: { uint16_t a = abs16(); cout << "JSR $" << hex << (int)a << endl; JSR(a); break; }

    // RTI
    case 0x40:
    {
        cout << "RTI" << endl;
        RTI();
        break;
    }

    // RTS
    case 0x60:
    {
        cout << "RTS" << endl;
        RTS();
        break;
    }

    // Flag Control Instructions
    // CLC
    case 0x18:
    {
        cout << "CLC" << endl;
        CLC();
        break;
    }
    // CLD
    case 0xD8:

    // CLI
    case 0x58:
    {
        cout << "CLI" << endl;
        CLI();
        break;
    }
    // CLV
    case 0xB8:
    {
        cout << "CLV" << endl;
        CLV();
        break;
    }
    // SEC
    case 0x38:
    {
        cout << "SEC" << endl;
        SEC();
        break;
    }
    // SED
    case 0xF8:
    {
        cout << "SED" << endl;
        SED();
        break;
    }
    // SEI
    case 0x78:
    {
        cout << "SEI" << endl;
        SEI();
        break;
    }

    // NOP
    case 0xEA: { cout << "NOP" << endl; break; }

    default:
        cout <<""<< endl;
        return true;
    }
    return false;
}

void CPU6502::run()
{
    bool stop = false;
    while (!stop)
    {
        stop = step();
    }
}

//Memory Helpers
uint8_t CPU6502::read(uint16_t addr) {
    return memory[addr];
}
void CPU6502::write(uint16_t addr, uint8_t val) {
    memory[addr] = val;
}
uint16_t CPU6502::read16(uint16_t addr) {
    uint8_t lo =read(addr);
    uint8_t hi = read(addr+1);
    return (hi << 8) | lo;
}
//6502 page-wraparound bug version for JMP indirect
uint16_t CPU6502::read16_wraparound(uint16_t addr) {
    uint8_t lo =read(addr);
    uint8_t hi = read((addr & 0xFF00) | ((addr + 1) & 0x00FF));
    return (hi << 8) | lo;
}
//Stack Helpers
void CPU6502::push(uint8_t val) {
    write(0x00100+SP,val);
    SP--;
}
uint8_t CPU6502::pop() {
    SP++;
    return read(0x00100+SP);
}
//Status Helpers
uint8_t CPU6502::packP(bool BFP) {
    uint8_t p=0;
    p |= C ? 0x01 : 0;
    p |= Z ? 0x02 : 0;
    p |= I ? 0x04 : 0;
    p |= D ? 0x08 : 0;
    p |= BFP ? 0x10 : 0;
    p |= 0x20; // unused bit always 1
    p |= V ? 0x40 : 0;
    p |= N ? 0x80 : 0;
    return p;
}
void CPU6502::unpackP(uint8_t p) {
    N = p & 0x80;
    V = p & 0x40;
    D = p & 0x08;
    I = p & 0x04;
    Z = p & 0x02;
    C = p & 0x01;
}

void CPU6502::updateNZ(uint8_t val)
{
    Z = (val == 0);
    N = (val & 0x80);
}
//Addressing Helpers
uint8_t CPU6502::imm()
{
    return read(PC++);
}

uint16_t CPU6502::zp()
{
    return read(PC++);
}
uint16_t CPU6502::zpX()
{
    uint8_t addr = (read(PC++) + X) & 0xFF;
    return addr;
}

uint16_t CPU6502::zpY()
{
    uint8_t addr = (read(PC++) + Y) & 0xFF;
    return addr;
}

uint16_t CPU6502::abs16()
{
    uint16_t addr = read16(PC);
    PC += 2;
    return addr;
}

uint16_t CPU6502::absX()
{
    uint16_t base = read16(PC);
    PC += 2;
    return base + X;
}

uint16_t CPU6502::absY()
{
    uint16_t base = read16(PC);
    PC += 2;
    return base + Y;
}

uint16_t CPU6502::indX()
{
    uint8_t zpAddr = (read(PC++) + X) & 0xFF;
    return read(zpAddr) | (read((zpAddr + 1) & 0xFF) << 8);
}

uint16_t CPU6502::indY()
{
    uint8_t zpAddr = read(PC++);
    uint16_t base = read(zpAddr) | (read((zpAddr + 1) & 0xFF) << 8);
    return base + Y;
}
//Stack Instructions
void CPU6502::PHA()
{
    push(A);
}

void CPU6502::PHP()
{
    push(packP(true));
}

void CPU6502::PLA()
{
    A = pop();
    updateNZ(A);
}

void CPU6502::PLP()
{
    uint8_t p = pop();
    unpackP(p);
}
//Transfer Instructions
void CPU6502::TAX()
{
    X = A;
    updateNZ(X);
}

void CPU6502::TAY()
{
    Y = A;
    updateNZ(Y);
}

void CPU6502::TXA()
{
    A = X;
    updateNZ(A);
}

void CPU6502::TXS()
{
    SP = X;
}

void CPU6502::TSX()
{
    X = SP;
    updateNZ(X);
}

void CPU6502::TYA()
{
    A = Y;
    updateNZ(A);
}
bool CPU6502::BRK()
{
    // Push PC and processor status to stack
    push((PC >> 8) & 0xFF);
    push(PC & 0xFF);
    push(packP(true));
    I = 1; // Disable interrupts

    switch (X)
    {
        case 0: // exit
            return true;

        case 1: // putc - print single character in A
            output << static_cast<char>(A);
            break;

        case 2: // puts - print null-terminated string at address in $00/$01
        {
            uint16_t addr = memory[0] | (memory[1] << 8);
            while (memory[addr] != 0) {
                output << static_cast<char>(memory[addr++]);
            }
            cout.flush();
            break;
        }

        case 3: // puthex8 - print byte in A as 2-digit hex
            output << hex << setw(2) << setfill('0')
                   << uppercase << (int)A;
            break;

        default:
            std::cerr << "Unknown system call: " << (int)X << std::endl;
            break;
    }
    return false; // continue execution
}


void CPU6502::NOP(){}
void CPU6502::JMP(uint16_t addr) {
    PC = addr;
}

// Logical Instructions
void CPU6502::ORA(uint8_t val)
{
    A |= val;
    updateNZ(A);
}
void CPU6502::AND(uint8_t val)
{
    A &= val;
    updateNZ(A);
}
void CPU6502::BIT(uint8_t val)
{
    Z = (A & val) == 0;
    V = (val & 0x40) != 0;
    N = (val & 0x80) != 0;
}
void CPU6502::EOR(uint8_t val)
{
    A ^= val;
    updateNZ(A);
}

// Increment & Decrement Instructions
void CPU6502::DEC(uint16_t addr)
{
    uint8_t val = read(addr);
    val--;
    write(addr, val);
    updateNZ(val);
}
void CPU6502::DEX()
{
    X--;
    updateNZ(X);
}
void CPU6502::DEY()
{
    Y--;
    updateNZ(Y);
}
void CPU6502::INC(uint16_t addr)
{
    uint8_t val = read(addr);
    val++;
    write(addr, val);
    updateNZ(val);
}
void CPU6502::INX()
{
    X++;
    updateNZ(X);
}
void CPU6502::INY()
{
    Y++;
    updateNZ(Y);
}

// Branch Instructions
void CPU6502::BCC(uint8_t val)
{
    if (!C)
    {
        int8_t offset = static_cast<int8_t>(val);
        PC += offset;
    }
}
void CPU6502::BCS(uint8_t val)
{
    if (C)
    {
        int8_t offset = static_cast<int8_t>(val);
        PC += offset;
    }
}
void CPU6502::BEQ(uint8_t val)
{
    if (Z)
    {
        int8_t offset = static_cast<int8_t>(val);
        PC += offset;
    }
}
void CPU6502::BMI(uint8_t val)
{
    if (N)
    {
        int8_t offset = static_cast<int8_t>(val);
        PC += offset;
    }
}
void CPU6502::BNE(uint8_t val)
{
    if (!Z)
    {
        int8_t offset = static_cast<int8_t>(val);
        PC += offset;
    }
}
void CPU6502::BPL(uint8_t val)
{
    if (!N)
    {
        int8_t offset = static_cast<int8_t>(val);
        PC += offset;
    }
}
void CPU6502::BVC(uint8_t val)
{
    if (!V)
    {
        int8_t offset = static_cast<int8_t>(val);
        PC += offset;
    }
}
void CPU6502::BVS(uint8_t val)
{
    if (V)
    {
        int8_t offset = static_cast<int8_t>(val);
        PC += offset;
    }
}

// Arithmetic Instructions
void CPU6502::ADC(uint8_t val)
{
    uint16_t sum = A + val + (C ? 1 : 0);
    V = (~(A ^ val) & (A ^ sum)) & 0x80;
    A = sum & 0xFF;
    C = sum > 0xFF;
    updateNZ(A);
}
void CPU6502::SBC(uint8_t val)
{
    uint16_t sum = A - val - (C ? 0 : 1);
    V = ((A ^ val) & (A ^ sum) & 0x80) != 0;
    A = sum & 0xFF;
    C = sum < 0x100;
    updateNZ(A);
}
void CPU6502::CMP(uint8_t val)
{
    uint8_t result = A - val;
    C = A >= val;
    updateNZ(result);
}
void CPU6502::CPX(uint8_t val)
{
    uint8_t result = X - val;
    C = X >= val;
    updateNZ(result);
}
void CPU6502::CPY(uint8_t val)
{
    uint8_t result = Y - val;
    C = Y >= val;
    updateNZ(result);
}

// Load & Store Instructions
void CPU6502::LDA(uint8_t val)
{
    A = val;
    updateNZ(A);
}
void CPU6502::LDX(uint8_t val)
{
    X = val;
    updateNZ(X);
}
void CPU6502::LDY(uint8_t val)
{
    Y = val;
    updateNZ(Y);
}
void CPU6502::STA(uint16_t addr)
{
    write(addr, A);
}
void CPU6502::STX(uint16_t addr)
{
    write(addr, X);
}
void CPU6502::STY(uint16_t addr)
{
    write(addr, Y);
}

//Jump Instructions/ Return Instructions
void CPU6502::JSR(uint16_t addr)
{
    uint16_t retAddr = PC - 1;
    push((retAddr >> 8) & 0xFF);
    push(retAddr & 0xFF);
    PC = addr;
}
void CPU6502::RTI()
{
    uint8_t status = pop();
    unpackP(status);
    uint8_t lo = pop();
    uint8_t hi = pop();
    PC = (hi << 8) | lo;
}
void CPU6502::RTS()
{
    uint8_t lo = pop();
    uint8_t hi = pop();
    PC = ((hi << 8) | lo) + 1;
}
//Shift and Rotate
void CPU6502::ASL(bool accumulator, uint16_t addr)
{
    uint8_t val = accumulator ? A : read(addr);
    C = (val & 0x80);
    val <<= 1;
    if (accumulator) A = val; else write(addr, val);
    updateNZ(val);
}
void CPU6502::LSR(bool accumulator, uint16_t addr)
{
    uint8_t val = accumulator ? A : read(addr);
    C = val & 0x01;
    val >>= 1;
    if (accumulator) A = val; else write(addr, val);
    updateNZ(val);
}
void CPU6502::ROL(bool accumulator, uint16_t addr)
{
    uint8_t val = accumulator ? A : read(addr);
    bool oldC = C;
    C = val & 0x80;
    val = (val << 1) | (oldC ? 1 : 0);
    if (accumulator) A = val; else write(addr, val);
    updateNZ(val);
}
void CPU6502::ROR(bool accumulator, uint16_t addr)
{
    uint8_t val = accumulator ? A : read(addr);
    bool oldC = C;
    C = val & 0x01;
    val = (val >> 1) | (oldC ? 0x80 : 0);
    if (accumulator) A = val; else write(addr, val);
    updateNZ(val);
}
//Flag Control SET/CLEAR
void CPU6502::CLC() { C = 0; }
void CPU6502::CLD() { D = 0; }
void CPU6502::CLI() { I = 0; }
void CPU6502::CLV() { V = 0; }
void CPU6502::SEC() { C = 1; }
void CPU6502::SED() { D = 1; }
void CPU6502::SEI() { I = 1; }

