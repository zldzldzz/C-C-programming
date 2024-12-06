#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *instruction[] = {"MOV", "ADD", "SUB", "CMP", "JMP", "JZ", "JA", "JB", "JAE", "JBE", "INC", "DEC", "INT"};
const char *reg8[] = {"AL", "AH", "BL", "BH", "CL", "CH", "DL", "DH"};
const char *reg16[] = {"AX", "BX", "CX", "DX", "CS", "DS", "ES", "SS", "IP", "SP", "BP", "SI", "DI"};
const char *pseudo[] = {"SEGMENT", "ASSUME", "DW", "DB", "END"};

// �迭 ũ�� ��ũ��
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

// Ư�� ���ڿ��� ��ɾ����� Ȯ��
int is_instruction(const char *word)
{
    for (int i = 0; i < ARRAY_SIZE(instruction); i++)
    {
        if (_stricmp(word, instruction[i]) == 0)
            return 1;
    }
    return 0;
}
// Ư�� ���ڿ��� reg8���� Ȯ��
int is_reg8(const char *word)
{
    for (int i = 0; i < ARRAY_SIZE(reg8); i++)
    {
        if (_stricmp(word, reg8[i]) == 0)
            return 1;
    }
    return 0;
}
// Ư�� ���ڿ��� reg16���� Ȯ��
int is_reg16(const char *word)
{
    for (int i = 0; i < ARRAY_SIZE(reg16); i++)
    {
        if (_stricmp(word, reg16[i]) == 0)
            return 1;
        else if (strchr(word, '+') != NULL)
            return 1;
    }
    return 0;
}
// Ư�� ���ڿ��� �ǻ��ɾ����� Ȯ��
int is_pseudo(const char *word)
{
    for (int i = 0; i < ARRAY_SIZE(pseudo); i++)
    {
        if (_stricmp(word, pseudo[i]) == 0)
            return 1;
    }
    return 0;
}
// Ư�� ���ڿ��� �������� Ȯ��
int is_number(const char *word)
{
    int i = 0;
    int len = strlen(word);
    if (word[0] == '-')
        i++; // ���� Ȯ��
    if (len > 1 && (word[len - 1] == 'H' || word[len - 1] == 'h'))
    {
        for (int j = i; j < len - 1; j++)
        {
            if (!isxdigit(word[j]))
                return 0;
        }
        return 1;
    }
    for (; word[i] != '\0'; i++)
    {
        if (!isdigit(word[i]))
            return 0;
    }
    return 1;
}
// Ư�� ���ڿ��� �迭�� �ִ��� Ȯ��
int is_in_array(const char *word, const char *arr[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (_stricmp(word, arr[i]) == 0)
            return 1;
    }
    return 0;
}
// ��ɾ� ���� ���
int calculate_length(const char *opcode, const char *op1, const char *op2)
{
    if (_stricmp(op1, "DB") == 0)
    {
        return 1; // DB�� 1 ����Ʈ
    }
    if (_stricmp(op1, "DW") == 0)
    {
        return 2; // DW�� 2 ����Ʈ
    }
    // MOV ��ɾ�
    if (_stricmp(opcode, "MOV") == 0)
    {
        if (is_in_array(op1, reg8, ARRAY_SIZE(reg8)) && is_in_array(op2, reg8, ARRAY_SIZE(reg8)))
        {
            return 2; // 8��Ʈ �������� �� MOV
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)) && is_in_array(op2, reg16, ARRAY_SIZE(reg16)))
        {
            return 2; // 16��Ʈ �������� �� MOV
        }
        if (is_in_array(op1, reg8, ARRAY_SIZE(reg8)))
        {
            if (is_number(op2))
            {
                return 2; // ��ð����� MOV
            }
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)))
        {
            if (is_number(op2))
            {
                return 3; // ��ð����� MOV
            }
            return 4; // �޸� �ּҿ��� MOV
        }
        return 3; // �⺻ �޸� MOV
    }
    // ADD, SUB ��ɾ�
    if (_stricmp(opcode, "ADD") == 0 || _stricmp(opcode, "SUB") == 0)
    {
        if (is_in_array(op1, reg8, ARRAY_SIZE(reg8)) && is_in_array(op2, reg8, ARRAY_SIZE(reg8)))
        {
            return 2; // 8��Ʈ �������� �� ADD/SUB
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)) && is_in_array(op2, reg16, ARRAY_SIZE(reg16)))
        {
            return 2; // 16��Ʈ �������� �� ADD/SUB
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)) || is_in_array(op1, reg8, ARRAY_SIZE(reg8)))
        {
            if (is_number(op2))
            {
                return 3; // ��ð����� ADD/SUB
            }
            return 4; // �޸� �ּҿ��� ADD/SUB
        }
        return 3; // �⺻ �޸� ADD/SUB
    }
    // CMP ��ɾ�
    if (_stricmp(opcode, "CMP") == 0)
    {
        if (is_in_array(op1, reg8, ARRAY_SIZE(reg8)) && is_in_array(op2, reg8, ARRAY_SIZE(reg8)))
        {
            return 2; // 8��Ʈ �������� �� CMP
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)) && is_in_array(op2, reg16, ARRAY_SIZE(reg16)))
        {
            return 2; // 16��Ʈ �������� �� CMP
        }
        if (is_in_array(op1, reg16, ARRAY_SIZE(reg16)) || is_in_array(op1, reg8, ARRAY_SIZE(reg8)))
        {
            if (is_number(op2))
            {
                return 3; // ��ð����� CMP
            }
            return 4; // �޸� �ּҿ��� CMP
        }
        return 3; // �⺻ �޸� CMP
    }
    // JMP �� ���Ǻ� ���� ��ɾ�
    if (is_in_array(opcode, (const char *[]){"JMP", "JZ", "JA", "JB", "JAE", "JBE"}, 6))
    {
        return 2;
    }
    // INC, DEC ��ɾ�
    if (_stricmp(opcode, "INC") == 0 || _stricmp(opcode, "DEC") == 0)
    {
        if (is_in_array(op1, reg8, ARRAY_SIZE(reg8)) || is_in_array(op1, reg16, ARRAY_SIZE(reg16)))
        {
            return 1; // �������� ���
        }
        return 2; // �޸� ���
    }
    // INT ��ɾ�
    if (_stricmp(opcode, "INT") == 0)
        return 2;
    // �⺻ ����
    return 2;
}

int main()
{
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;
    char line[256] = {0};
    const char *delim = " ,\t";
    // txt���� �б� ���� ����
    inputFile = fopen("symbol.txt", "r");
    if (inputFile == NULL)
    {
        printf("Failed to open input file again.\n");
        exit(1);
    }
    // ��� ���� ����
    outputFile = fopen("output3.txt", "w+");
    if (outputFile == NULL)
    {
        printf("Failed to open output file.\n");
        exit(1);
    }
    // ���Ͽ��� �� �پ� �а� ġȯ�ϱ�
    while (fgets(line, sizeof(line), inputFile))
    {
        if (strlen(line) <= 1)
        { // �� ���� �״�� ���
            fprintf(outputFile, "\n");
            continue;
        }
        line[strcspn(line, "\n")] = '\0'; // Enter ����
        fprintf(outputFile, "%s ", line);
        // ���� ���� �� �ܾ� ������ �и�
        char line_copy[256];
        strcpy(line_copy, line);
        // ���̺��� ������ ���� �ܾ�� �̵�
        char *command = strchr(line_copy, ':');
        if (command != NULL)
        {
            command++;
            // ���� �ܾ �����̸� �ѹ� �� �̵�
            while (*command == ' ' || *command == '\t')
            {
                command++;
            }
        }
        else
        {
            command = line_copy;
        }
        // ��ɾ�� ���۷��� �Ľ�
        char opcode[16] = "", op1[16] = "", op2[16] = "";
        char *token = strtok(command, delim);
        int count = 0;
        // �˻� �� ġȯ
        fprintf(outputFile, " [");

        while (token != NULL)
        {
            if (is_instruction(token))
            {
                strcpy(opcode, token);
                fprintf(outputFile, "op ");
            }
            else if (is_reg8(token))
            {
                if (count == 1)
                    strcpy(op1, token);
                else
                    strcpy(op2, token);
                fprintf(outputFile, "reg8 ");
            }
            else if (is_reg16(token))
            {
                if (count == 1)
                    strcpy(op1, token);
                else
                    strcpy(op2, token);
                fprintf(outputFile, "reg16 ");
            }
            else if (is_number(token))
            {
                strcpy(op2, token);
                fprintf(outputFile, "num ");
            }
            else if (is_pseudo(token))
            {
                strcpy(op1, token);
                fprintf(outputFile, "pop ");
            }
            else
            {
                if (count == 1)
                    strcpy(op1, token);
                else
                    strcpy(op2, token);
                fprintf(outputFile, "sym ");
            }
            count++;
            token = strtok(NULL, delim);
        }
        // ���� ���
        int length = calculate_length(opcode, op1, op2);
        // ��� ���

        fprintf(outputFile, "] %d\n", length);
    }
    printf("Complete\n");
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}