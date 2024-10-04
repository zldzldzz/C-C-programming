#include <stdio.h>  // ǥ�� ����� �Լ� ���
#include <ctype.h>  // ���� ó�� �Լ� ��� (��: isalpha, isdigit)
#include <stdlib.h> // ǥ�� ���̺귯�� �Լ� ���

int main()
{
    FILE *fp;              // ���� ������ ����
    char ch;               // ���Ͽ��� �о�� ���ڸ� ������ ����
    int letters = 0;       // ������ ������ ���� ����
    int digits = 0;        // ���� ������ ���� ����
    int special_chars = 0; // Ư������ ������ ���� ����

    // ���� ����
    fp = fopen("I_have_a_dream_Num.txt", "r"); // "ihaveadream.txt" ������ �б� ���� ���ϴ�
    if (fp == NULL)
    { // ���� ���� ���� �� ó��
        printf("���� ���⿡ �����߽��ϴ�.\n");
        return -1; // ���α׷� ����
    }

    // ���Ͽ��� �� ���ھ� �о �м�
    while ((ch = fgetc(fp)) != EOF)
    { // ���Ͽ��� �� ���ھ� �о� EOF(������ ��)���� �ݺ�

        if (isalpha(ch))
        {              // ���������� �˻�
            letters++; // �������� ��� ī��Ʈ ����
            printf("������: %c %d\n", ch, letters);
        }
        else if (isdigit(ch))
        {             // �������� �˻�
            digits++; // ������ ��� ī��Ʈ ����
            printf("����: %c %d\n", ch, digits);
        }
        else if (ispunct(ch))
        {                    // Ư���������� �˻�
            special_chars++; // Ư�������� ��� ī��Ʈ ����
            printf("Ư������:%c %d\n", ch, special_chars);
        }
    }

    // ��� ���
    printf("������ ����: %d\n", letters);
    printf("���� ����: %d\n", digits);
    printf("Ư������ ����: %d\n", special_chars);

    // ���� �ݱ�
    fclose(fp);
    return 0;
}