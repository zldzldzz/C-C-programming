#include <stdio.h>
#include <stdlib.h>

#define maxNumbers 20 // ���� �ִ� ���� ����

int data[20] = {3, 4, 23, 493, 54, 13, 56, 76, 123, 888, 413, 234, 5, 432, 324, 11, 43, 53, 99, 1};

int main()
{
    int numbers[maxNumbers]; // ���������� ���� ����ִ� ����
    int index = 0;           // ���ڵ��� �ε���
    FILE *file;

    file = fopen("input.dat", "w"); // ���� ���� dat���� ����

    // ���� Ű���忡�� �Է¹޾Ƽ� �ϴ� ��� �� �κ� �ּ� ����ϸ� �˴ϴ�.
    char input[100]; // ���ڸ� �Է��� ����
    printf("�ؽ�Ʈ�� �Է��ϼ���: ");
    fgets(input, sizeof(input), stdin);
    fprintf(file, "%s", input);

    // ���� Ű���忡�� �Է¹޾Ƽ� �ϴ� ��� �Ʒ� �ݺ����� �ּ� ó���ϸ� �˴ϴ�.
    // for (int i = 0; i < 20; i++) // ����Ʈ�� �ִ� �����͸� ���� �ϴ� ����
    //{
    //    fprintf(file, "%d ", data[i]);
    //}

    fclose(file); // ���� �ݱ�

    file = fopen("input.dat", "r"); // dat���� �б���� ����

    if (file == NULL) // ������ �������� �ʴ� ���
    {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    // �ش� ������ ���� �о���� maxNumbers�� ������ŭ
    while (fscanf(file, "%d", &numbers[index]) != EOF && index < maxNumbers)
    {
        index++;
    }

    fclose(file); // ���� ��� �� ���� �ݱ�

    // ���� ���ķ� ���� ����
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - 1 - i; j++)
        {
            // ���� ���� ���� ������ ������ �Ʒ� <�� >�� �ٲٸ� �ȴ�.
            if (numbers[j] < numbers[j + 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    // ���ĵ� ���� ���
    printf("���ĵ� ����:\n");

    for (int i = 0; i < index; i++)
    {
        printf("%d, ", numbers[i]);
    }

    return 0;
}
