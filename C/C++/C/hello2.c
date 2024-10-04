#include <stdio.h>
#include <stdlib.h>

#define maxNumbers 25 // ���� �ִ� ���� ����

// ���� �˻� �Լ�
int binarySearch(int arr[], int size, int target)
{
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == target)
        {
            return mid; // ã���� �ε��� ��ȯ
        }
        else if (arr[mid] < target)
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
    int numbers[maxNumbers]; // ���Ͽ��� �о���� ���ڸ� ������ �迭
    int index = 0;           // ���ڵ��� �ε���
    FILE *file;

    // input.dat ���� �б�
    file = fopen("input.dat", "r"); // dat ���� �б� ���� ����
    if (file == NULL)
    {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    // ���Ͽ��� ���� �б�
    while (fscanf(file, "%d", &numbers[index]) != EOF && index < maxNumbers)
    {
        index++;
    }
    fclose(file); // ���� �ݱ�

    // ���� ���� (��������)
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - 1 - i; j++)
        {
            if (numbers[j] > numbers[j + 1])
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
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // ����� �Է� �ݺ� ó��
    int input;
    while (1)
    {
        printf("ã�� ���ڸ� �Է��ϼ��� (����: 0): ");
        scanf("%d", &input);

        if (input == 0)
        {
            break; // 0 �Է� �� ���α׷� ����
        }

        // ���� �˻� ����
        int result = binarySearch(numbers, index, input);

        if (result != -1)
        {
            printf("%d�� ���ĵ� ����Ʈ���� %d��°�� �ֽ��ϴ�.\n", input, result + 1);
        }
        else
        {
            printf("%d�� ����Ʈ�� �����ϴ�.\n", input);
        }
    }

    return 0;
}
