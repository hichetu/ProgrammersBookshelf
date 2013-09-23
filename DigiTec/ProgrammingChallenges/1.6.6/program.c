#include <stdio.h>

unsigned int registers[10];
unsigned int RAM[1000];

void ProcessProgram();
void Execute();

int main()
{
    char line[1024];
    unsigned long iterations = 0;

    gets(line);
    sscanf(line, "%lu\n", &iterations);

    gets(line);
    while (iterations--)
    {
        ProcessProgram();
        if (iterations > 0)
        {
            printf("\n");
        }
    }
    return 0;
}

void ProcessProgram()
{
    char line[1024];
    unsigned long fRead = 1;
    unsigned long instruction = 0;
    unsigned long instructionIndex = 0;

    // Initialize the VM
    memset(registers, 0, sizeof(registers));
    memset(RAM, 0, sizeof(RAM));

    // Read in instructions until we hit an empty line
    do
    {
        char* readLine = gets(line);
        if (readLine != NULL && readLine[0] != '\0')
        {
            sscanf(readLine, "%lu", &instruction);
            RAM[instructionIndex++] = instruction;
        }
        else
        {
            fRead = 0;
        }
    } while (fRead);

    // Execute the program
    Execute();
}

void Execute()
{
    unsigned long instructionPointer = 0;
    unsigned long instructionCounter = 0;
    while (1)
    {
        // Retrieve the instruction and set the instruction pointer
        unsigned long instruction = RAM[instructionPointer++];

        // Decode the instruction
        unsigned long command = instruction / 100;
        unsigned long operand1 = (instruction % 100) / 10;
        unsigned long operand2 = (instruction % 10);

        // Setup the instruction counter
        instructionCounter++;
#if DBG
        printf("instruction(%d), command(%d), op1(%d), op2(%d), ip(%d)\n", instruction, command, operand1, operand2, instructionPointer);
#endif

        switch (command)
        {
            case 1:
                if (operand1 == 0 && operand2 == 0)
                {
                    printf("%d\n", instructionCounter);
                    return;
                }
                break;
            case 2:
                registers[operand1] = operand2;
                break;
            case 3:
                registers[operand1] = (registers[operand1] + operand2) % 1000;
                break;
            case 4:
                registers[operand1] = (registers[operand1] * operand2) % 1000;
                break;
            case 5:
                registers[operand1] = registers[operand2];
                break;
            case 6:
                registers[operand1] = (registers[operand1] + registers[operand2]) % 1000;
                break;
            case 7:
                registers[operand1] = (registers[operand1] * registers[operand2]) % 1000;
                break;
            case 8:
                registers[operand1] = RAM[registers[operand2]];
                break;
            case 9:
                RAM[registers[operand2]] = registers[operand1];
                break;
            case 0:
                if (registers[operand2] != 0)
                {
                    instructionPointer = registers[operand1];
                }
                break;
        }
    }
}