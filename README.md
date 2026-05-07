# CSCE 2303 – Instruction Set Simulator for 8-Bit Microprocessor

---

## Overview

This project implements an **Instruction Set Simulator (ISS)** for the **MOS 6502 8-bit microprocessor**, a classic CPU used in historical systems such as the **Apple II** and **Commodore 64**.
The simulator emulates the **fetch-decode-execute** cycle of the processor, allowing binary machine code programs to be executed, inspected, and tested on a virtual CPU environment.

The implementation ignores the 6502’s **BCD mode** as per project specifications and supports basic system calls via the **BRK instruction**, using the **X register** to specify the system call ID.

---

## Features

- Full 6502 instruction decoding and execution for supported opcodes
- Accurate emulation of registers (**A**, **X**, **Y**, **SP**, **PC**, **Status flags**)
- Memory model of **64 KB** with zero-page addressing support
- System call simulation for:
  - `0`: exit
  - `1`: putc (print one character in register A)
  - `2`: puts (print zero-terminated string)
  - `3`: puthex8 (print register A as two hex digits)

- One mode of operation:
  1. Execute a provided binary file (`.bin`) via terminal

---

## Build Instructions

### Requirements

- C++ compiler (GCC, Clang, or MSVC supporting **C++11** or later)
- Git for version tracking

### Steps

Clone your project repository:

```bash
git [clone https://github.com/<your-team-repo>](https://github.com/CSCE-2303/csce-2303-f25-project-1-the_achievers).git
cd <csce-2303-f25-project-1-the_achievers>
```

Compile the simulator:

```bash
g++ -std=c++17 is8sim.cpp CPU6502.cpp -o is8sim.exe
```

Ensure that the compiled binary `is8sim` (or `is8sim.exe` on Windows) is in your project directory.

---

## Usage Guidelines

### 1. Built-in Test Mode

Executes predefined test programs stored in the code.

```bash
./is8sim  <TEST_BINARY_FILE>
```

Select **option 1** when prompted and use Evaluation.txt to confirm the output.

### 2. Custom Binary Execution

Run your own assembled `.bin` file:

```bash
./is8sim  <BINARY_FILE>
```

Select **option 2**, then enter the path to your binary file (e.g., `program.bin`).

#### Input Format

- The binary file represents memory starting from address `0x0000`.
- The reset vector is read from addresses `0xFFFC–0xFFFD` to set the program counter (PC).

---

## Design Overview

### Architecture

| Component            | Description                                                                              |
| -------------------- | ---------------------------------------------------------------------------------------- |
| **CPU6502**          | Core class containing all registers, memory array, and methods for instruction emulation |
| **read() / write()** | Memory access helpers                                                                    |
| **step()**           | Fetches, decodes, and executes a single instruction                                      |
| **run()**            | Repeatedly calls `step()` until a termination instruction (`BRK`) is encountered         |
| **runTests()**       | Executes built-in test cases for validation                                              |
| **runBinaryFile()**  | Loads and executes external machine code                                                 |

### Execution Flow

1. Load program data into memory
2. Initialize registers (**A**, **X**, **Y**, **SP**, **PC**)
3. Start the simulation loop:
   - Fetch next opcode using **PC**
   - Decode instruction tyWRITE pe and addressing mode
   - Execute operation and update registers or flags
   - Continue until **BRK** or unknown opcode halts the simulator

---

## Test Cases

A minimum of **10 test programs** are embedded within the simulator, including:

- Arithmetic operations (`ADC`, `SBC`)

- Logical operations (`AND`, `ORA`, `EOR`)

- Load/Store instructions (`LDA`, `STA`, `LDX`, `STX`)

- Branching and Jump instructions (`BPL`, `BEQ`, `JMP`, `JSR`, `RTS`)

- Stack operations (`PHA`, `PLA`, `PHP`, `PLP`)

- Increment/Decrement (`INX`, `DEY`, `INC`, `DEC`)

- Status flag operations (`CLC`, `SEC`, `SEI`, etc.)

- Memory wraparound behavior for `JMP indirect`

- Comparison instructions (`CMP`, `CPX`, `CPY`)

- No-operation and termination (`NOP`, `BRK`)

Each test prints its **instruction trace**, **register updates**, and **final CPU state**.

---

## Project Challenges

- Handling a large and diverse instruction set with multiple addressing modes
- Accurately replicating 6502-specific quirks (such as the `JMP` indirect bug at page boundaries)
- Designing an efficient opcode decoder without massive repetition
- Ensuring correct flag updates (**Carry**, **Zero**, **Negative**, **Overflow**) across all operations
- Debugging memory wrapping and stack behavior in indirect and subroutine instructions

---

## Known Limitations

- **BCD (Binary Coded Decimal)** mode not implemented (as instructed)
- Limited I/O system call simulation (text-only output)
- No cycle-level timing or hardware peripherals emulated
- Minimal error handling for unsupported opcodes

---

## References

- [Masswerk 6502 Instruction Set Reference](https://www.masswerk.at/6502/assembler.html)
- [Easy 6502 Guide](https://skilldrick.github.io/easy6502/)
- _Motorola 6809 Programmer’s Reference Manual_
- _CSCE 2303 Fall 2025 Project Specification_ (Course Handout)
