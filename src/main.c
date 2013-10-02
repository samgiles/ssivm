#include "stdio.h";
#include "stdlib.h";

#define OP_MASK 0xFF;
#define OP_ARGA_MASK 0xFFF00;
#define OP_ARGB_MASK 0xFFF00000;


#define OP_SET 0x1
#define OP_MUL 0x2
#define OP_ADD 0x3
#define OP_MOV 0x4
#define OP_PRINT 0x5

void set(int* reg, int literal);
void mul(int* regOne, int* regTwo);
void add(int* regOne, int* regTwo);
void mov(int* regOne, int* regTwo);
void run(int* operations, int* registers, int* pc);

int main(int argc, char* argv[]) {
  int registers[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  // 10 * ( 4 + 5) * 123 = 11070
  int ops[8] = {
    // print r4
    0x405,
    // mul r4, r3
    0x300402,
    // mul r4, r1
    0x100402,
    // add r3, r2
    0x200303,
    // set r4, 123
    0x7B00401,
    // set r3, 5
    0x500301,
    // set r2, 4
    0x400201,
    // set r1, 10
    0xA00101 };

  int pc = 7;

  while(pc >= 0) {
    run(ops, registers, &pc);
    pc--;
  };

  return 0;
}


void run(int* operations, int* registers, int* pc) {
  // Get opcode and operands out of int
  int op = operations[*pc];
  unsigned char opcode = op & OP_MASK;
  int arg1 = op & OP_ARGA_MASK;
  arg1 = arg1 >> 8;
  int arg2 = op & OP_ARGB_MASK;
  arg2 = arg2 >> 20;


  printf("PC: %d; OP: %d; ARG1: %d; ARG2: %d;\n", *pc, opcode, arg1, arg2);

  switch(opcode) {
  case(OP_SET): // set r1, literal
    set(&registers[arg1], arg2);
    break;
  case(OP_MUL): // mul r1, r2 (mul reg1 and reg2 put result in reg1)
    mul(&registers[arg1], &registers[arg2]);
    break;
  case(OP_ADD): // add r1, r2 (add reg1 and reg2 put result in reg1)
    add(&registers[arg1], &registers[arg2]);
    break;
  case(OP_MOV): // mov r1, r2 copy r2 into r1
    mov(&registers[arg1], &registers[arg2]);
    break;
  case(OP_PRINT): // print r1 output contents of register 1
    printf("-> %d\n", registers[arg1]);
    break;
  }
}

void set(int* reg, int literal) {
  *reg = literal;
}

void mul(int* regOne, int* regTwo) {
  *regOne = *regOne * *regTwo;
}

void add(int* regOne, int* regTwo) {
  *regOne = *regOne + *regTwo;
}

void mov(int* regOne, int* regTwo) {
  *regOne = *regTwo;
}
