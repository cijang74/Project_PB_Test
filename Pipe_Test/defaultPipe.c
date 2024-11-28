#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MAXLINE 100

int main()
{
    int n, length, fd[2], pid;
    char message[MAXLINE], line[MAXLINE];

    // ������ ����
    pipe(fd);

    // �ڽ� ���μ��� ����, �Ʒ� ��� ����
    if (pid = fork() == 0)
    {
        // �б� ������ ����
        close(fd[0]);

        sprintf(message, "�ȳ�. �� ���μ��� ���̵�� %d (��)��.\n", getpid());
        length = strlen(message) + 1;

        // ���� �������� �޽��� �۽�
        write(fd[1], message, length);
    }

    // �θ� ���μ����� �Ʒ� ��� ����
    else
    {
        // ���� ������ ����
        close(fd[1]);

        // �б� �������� �ִ� �޽��� ����
        n = read(fd[0], line, MAXLINE);

        printf("[%d] %s", getpid(), line);
    }

    exit(0);
}