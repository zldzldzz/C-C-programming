#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define OUT_FILE "out.txt"

// �� �Ǻ� �Լ�: �ܾ ':'�� �������� Ȯ��
bool is_label(const char *word)
{
    size_t len = strlen(word);
    return len > 0 && word[len - 1] == ':';
}

// �󺧿��� ':' ����
void remove_colon(char *word)
{
    size_t len = strlen(word);
    if (len > 0 && word[len - 1] == ':')
    {
        word[len - 1] = '\0';
    }
}

// DB/DW �Ǻ� �Լ�
bool is_data_declaration(const char *word)
{
    return strcmp(word, "DB") == 0 || strcmp(word, "DW") == 0;
}

int main()
{
    FILE *input_file = fopen("symbol.txt", "r");
    FILE *output_file = fopen(OUT_FILE, "w");
    if (input_file == NULL || output_file == NULL)
    {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    char line[MAX_LENGTH];
    int word_count = 0;
    char *words[MAX_LENGTH] = {0};  // �ܾ� ���� �迭
    int word_positions[MAX_LENGTH]; // ��ġ ���� �迭
    int total_words = 0;            // ��ü �ܾ� ��

    // ù ��° �ܰ�: �ܾ�� ��ġ ����
    while (fgets(line, sizeof(line), input_file))
    {
        char *token = strtok(line, " \t\n");
        char *previous_token = NULL; // DB/DW ���� �ܾ �����ϱ� ���� ����
        while (token != NULL)
        {
            word_positions[total_words] = ++word_count;
            words[total_words] = strdup(token); // �ܾ� ����

            // DB/DW �տ� ��ġ�� �ܾ��� ��� ���
            if (is_data_declaration(token) && previous_token != NULL)
            {
                printf("�ܾ�: %s, ��ġ: %d��° �ܾ�\n", previous_token, word_positions[total_words - 1]);
            }

            // ���� ��� ��ġ ���
            if (is_label(token))
            {
                remove_colon(token); // ':' ����
                printf("��: %s, ��ġ: %d��° �ܾ�\n", token, word_positions[total_words]);
            }

            previous_token = token; // ���� ��ū�� ���� ��ū���� ����
            total_words++;
            token = strtok(NULL, " \t\n");
        }
    }

    // �� ��° �ܰ�: OUT.txt�� ��ġ�� ��ü�Ͽ� ����
    rewind(input_file);
    word_count = 0; // �ܾ� ī��Ʈ�� �ʱ�ȭ

    while (fgets(line, sizeof(line), input_file))
    {
        char *token = strtok(line, " \t\n");
        while (token != NULL)
        {
            bool replaced = false;

            for (int i = 0; i < total_words; i++)
            {
                // ���� ��ū�� ����� �ܾ�� ��ġ�ϸ� ��ġ�� ��ü
                if (strcmp(token, words[i]) == 0)
                {
                    if (is_label(words[i]) || (i > 0 && is_data_declaration(words[i - 1])))
                    {
                        fprintf(output_file, "%d ", word_positions[i]);
                    }
                    else
                    {
                        fprintf(output_file, "%s ", token);
                    }
                    replaced = true;
                    break;
                }
            }

            if (!replaced)
            {
                fprintf(output_file, "%s ", token); // ��ü���� ���� �ܾ� �״�� ���
            }

            token = strtok(NULL, " \t\n");
        }
        fprintf(output_file, "\n"); // �ٹٲ�
    }

    // ���� �޸� ����
    for (int i = 0; i < total_words; i++)
    {
        free(words[i]);
    }

    fclose(input_file);
    fclose(output_file);

    printf("��ȯ ����� %s�� ����Ǿ����ϴ�.\n", OUT_FILE);
    return 0;
}
