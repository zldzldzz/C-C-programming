#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxWords 20      // �ܾ� �ִ� ���� ����
#define maxWordLength 50 // �ܾ� �ִ� ���� ����

int binarySearch(char arr[][maxWordLength], int size, char *target)
{
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        printf("Ž�� ����: low=%d, high=%d, mid=%d, �߰���: %s\n", low, high, mid, arr[mid]);
        int cmp = strcmp(arr[mid], target);
        if (cmp == 0)
        {
            return mid; // ã���� �ε��� ��ȯ
        }
        else if (cmp < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1; // ã�� ������ ���
}

int main()
{
    char words[maxWords][maxWordLength]; // ���Ͽ��� ���� �ܾ���� ������ �迭
    int index = 0;                       // �ܾ���� �ε���
    FILE *file;
    // input.dat ���� �б� ���� ����
    file = fopen("input1.dat", "r");
    if (file == NULL)
    {
        printf("input1.dat ������ �� �� �����ϴ�.\n");
        return 1;
    }

    // input.dat ���Ͽ��� �ܾ� �о����
    while (fscanf(file, "%s", words[index]) != EOF && index < maxWords)
    {
        index++;
    }

    fclose(file); // input.dat ���� �ݱ�

    // ���� ���ķ� �ܾ� ���� (���������� �������� ����)
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - 1 - i; j++)
        {
            if (strcmp(words[j], words[j + 1]) > 0) // ������ ��
            {
                char temp[maxWordLength];
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp);
            }
        }
    }

    // output.dat ���� ���� ���� ����
    file = fopen("output.dat", "w");
    if (file == NULL)
    {
        printf("output.dat ������ �� �� �����ϴ�.\n");
        return 1;
    }

    // ���ĵ� �ܾ���� output.dat ���Ͽ� ����
    for (int i = 0; i < index; i++)
    {
        fprintf(file, "%s\n", words[i]);
    }

    fclose(file); // output.dat ���� �ݱ�

    // output.dat ���Ͽ��� �ٽ� �о����
    file = fopen("output.dat", "r");
    if (file == NULL)
    {
        printf("output.dat ������ �� �� �����ϴ�.\n");
        return 1;
    }

    // �ܾ���� �ٽ� �о��
    index = 0;
    while (fscanf(file, "%s", words[index]) != EOF && index < maxWords)
    {
        index++;
    }

    fclose(file); // output.dat ���� �ݱ�

    // ���ĵ� �ܾ� ���
    printf("output.dat���� ���� ���ĵ� �ܾ��:\n");
    for (int i = 0; i < index; i++)
    {
        printf("%s, ", words[i]);
    }
    printf("\n");

    // Ű���忡�� ���� �Է¹޾� ���� ���
    char target[maxWordLength];
    while (1)
    {
        printf("������ �˰� ���� �ܾ �Է��ϼ���(����: 0): ");
        scanf("%s", target);

        if (strcmp(target, "0") == 0)
        {
            break; // 0 �Է� �� ���α׷� ����
        }

        // ���� ���
        int result = binarySearch(words, index, target);

        if (result != -1)
        {
            printf("�ܾ� %s�� ������ %d�Դϴ�.\n", target, result + 1);
        }
        else
        {
            printf("�ܾ� %s�� ��Ͽ� �����ϴ�.\n", target);
        }
    }
    return 0;
}
