#include <stdio.h>

// �������� ���� �Լ�
void sort_desc(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] < arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// ���� Ž�� �Լ�
void binary_search(int arr[], int left, int right, int target)
{
    while (left <= right)
    {
        int mid = (left + right) / 2;

        // ���� Ž�� ������ ���
        for (int i = left; i <= right; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");

        if (arr[mid] == target)
        {
            printf("ã�� ��: %d\n", arr[mid]);
            return;
        }
        else if (arr[mid] < target)
        { // ���ʿ� ����
            right = mid - 1;
        }
        else
        { // �����ʿ� ����
            left = mid + 1;
        }
    }

    printf("���� ã�� ���߽��ϴ�.\n");
}

int main()
{
    int arr[] = {34, 56, 72, 126, 31, 11, 7, 8, 29, 100};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 72;

    // �迭�� ������������ ����
    sort_desc(arr, n);

    // ���ĵ� �迭 ���
    printf("���ĵ� ��: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // ���� Ž�� ���� �� ���� ���
    printf("���� Ž�� ����:\n");
    binary_search(arr, 0, n - 1, target);

    return 0;
}
