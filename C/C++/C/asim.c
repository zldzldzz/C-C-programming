#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 100
#define INITIAL_SIZE 10 // �ʱ� �ɺ� �迭 ũ��

const char *reg16[] = {
    "AX",
    "BX",
    "CX",
    "DX",
    "SI",
    "DI",
    "SP",
    "BP",
    "IP",
    "FLAGS",
    "CS",
    "DS",
    "SS",
    "ES",
    "FS",
    "GS",
};

const char *reg8[] = {
    "AL",
    "AH",
    "BL",
    "BH",
    "CL",
    "CH",
    "DL",
    "DH",
};

const char *optbl[] = {
    "MOV", "POP", "PUSH", "ADD", "SUB", "MUL", "DIV", "INC", "DEC", "AND", "OR", "XOR", "NOT", "CMP", "INT", // ����� ��ɾ�
    "JA", "JAE", "JB", "JBE", "JC", "JE", "JNE", "JZ", "JZE", "CALL", "RET"                                  // ���Ǻб� ��ɾ�
};

const char *pop[] = {
    "DW", "DB",
    "SEGMENT", "ASSUME", "END"};

// �ɺ� �߰� �Լ�
void add_symbol(char ***sym, int *size, int *count, const char *new_symbol)
{
    if (*count >= *size)
    {
        *size *= 2; // �迭 ũ�⸦ �� ��� ����
        *sym = realloc(*sym, *size * sizeof(char *));
        if (*sym == NULL)
        {
            perror("�޸� �Ҵ� ����");
            exit(1);
        }
    }

    (*sym)[*count] = strdup(new_symbol);
    if ((*sym)[*count] == NULL)
    {
        perror("�޸� �Ҵ� ����");
        exit(1);
    }

    (*count)++;
}

// �ɺ� ���� �Լ�
void free_symbols(char **sym, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(sym[i]);
    }
    free(sym);
}

// ���ڿ� ������ ���� ����
void pop_back(char *word)
{
    size_t len = strlen(word);
    if (len > 0)
    {
        word[len - 1] = '\0';
    }
}

// ���ڿ� ù ��° ���� ����
void pop_front(char *word)
{
    size_t len = strlen(word);
    if (len > 0)
    {
        memmove(word, word + 1, len);
    }
}

// Ư�� ���� ����pop_backoptbl
void clean_word(char *word)
{
    size_t len = strlen(word);

    if (len > 0 && (word[len - 1] == ',' || word[len - 1] == ':'))
    {
        pop_back(word);
        len--;
    }

    if (len > 1 && word[0] == '[' && word[len - 1] == ']')
    {
        pop_back(word);
        pop_front(word);
    }
}

// ���� �Ǻ� �Լ�
bool is_integer(const char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (!isdigit(word[i]))
        {
            return false;
        }
    }
    return true;
}

// �迭���� �ܾ ã�� �迭 �̸����� ��ü
bool find_and_replace(const char *word, const char *arr[], int size, const char *arr_name, char *output)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(word, arr[i]) == 0)
        {
            sprintf(output, "%s", arr_name);
            return true;
        }
    }
    return false;
}

int main()
{
    FILE *input_file = fopen("symbol.txt", "r");
    FILE *output_file = fopen("out.txt", "w");
    if (input_file == NULL || output_file == NULL)
    {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    char line[MAX_LENGTH];
    char output_word[MAX_LENGTH];
    char **sym = malloc(INITIAL_SIZE * sizeof(char *));
    if (sym == NULL)
    {
        perror("�޸� �Ҵ� ����");
        return 1;
    }

    int size = INITIAL_SIZE;
    int count = 0;

    while (fgets(line, sizeof(line), input_file))
    {
        char *token = strtok(line, " \t\n");
        while (token != NULL)
        {
            memset(output_word, 0, sizeof(output_word));
            clean_word(token); // �ܾ� ����

            if (is_integer(token))
            {
                fprintf(output_file, "num ");
            }
            else if (find_and_replace(token, reg16, sizeof(reg16) / sizeof(reg16[0]), "reg16", output_word) ||
                     find_and_replace(token, reg8, sizeof(reg8) / sizeof(reg8[0]), "reg8", output_word) ||
                     find_and_replace(token, optbl, sizeof(optbl) / sizeof(optbl[0]), "op", output_word) ||
                     find_and_replace(token, pop, sizeof(pop) / sizeof(pop[0]), "pop", output_word))
            {
                fprintf(output_file, "%s ", output_word);
            }
            else
            {
                fprintf(output_file, "sym ");
                add_symbol(&sym, &size, &count, token);
            }

            token = strtok(NULL, " \t\n");
        }
        fprintf(output_file, "\n");
    }

    fclose(input_file);
    fclose(output_file);

    printf("��ȯ ����� out.txt�� ����Ǿ����ϴ�.\n");

    // �ɺ� ��� (������)
    for (int i = 0; i < count; i++)
    {
        printf("�ɺ� %d: %s\n", i + 1, sym[i]);
    }

    free_symbols(sym, count);
    return 0;
}
