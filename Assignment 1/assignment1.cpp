/*
* Name: Ehtesham Shahzad
* Roll: Number: 19L-1891
* Assignment # 1
*/

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

void parentToChild(char *path) // Part 1: From parent to child
{

    int pipefd[2];

    pid_t pid;
    //int oldflags = fcntl(info_pipe[direction], F_GETFL);
    //if (pipe2(pipefd, O_NONBLOCK)==-1) // to avoid blocking call
    printf("Creating pipe.\n");
    if (pipe(pipefd))
    {
        printf("Pipe Failed.\n");
        return;
    }

    printf("Forking. Creating child process.\n");
    pid = fork();

    if (pid < 0)
    {
        printf("Error. Unable to create child process.\n");
        return;
    }

    else if (pid == 0)
    {
        printf("Inside child process.\nClosing writing end in child process.\n");
        close(pipefd[1]);

        printf("\nContent of file are:\n\n");
        char c = 0;
        while (read(pipefd[0], &c, sizeof(c)) > 0)
        {
            if (c != EOF)
            {
                printf("%c", c);
            }
            else
            {
                printf("\nTerminating child process.\n");
                exit(0); // Ends child process
            }
        }
    }

    printf("Inside parent process.\nClosing reading end in parent process.\n");
    close(pipefd[0]); // Closing reading end

    printf("Opening file\n");
    FILE *fd = fopen(path, "r");

    if (fd > 0)
    {
        printf("File successfully opened. Reading file\n");
        char c = 0;

        while (c != EOF)
        {
            c = getc(fd);
            write(pipefd[1], &c, 1);
        }
        printf("Finished reading file\n");
    }
    else
    {
        printf("Unable to open file.\n");
        return;
    }
    wait(NULL);
    printf("Closing file\n");
    fclose(fd);
}

//___________________________________________________

void childToParent(char *path) // Part 2: From child to parent
{

    int pipefd[2];

    pid_t pid;
    //int oldflags = fcntl(info_pipe[direction], F_GETFL);
    //if (pipe2(pipefd, O_NONBLOCK)==-1) // to avoid blocking call
    printf("Creating pipe.\n");
    if (pipe(pipefd))
    {
        printf("Pipe Failed.\n");
        return;
    }

    printf("Forking. Creating child process.\n");
    pid = fork();

    if (pid < 0)
    {
        printf("Error. Unable to create child process.\n");
        return;
    }

    else if (pid == 0)
    {
        printf("Inside child process\nClosing reading end in child process.\n");
        close(pipefd[0]); // Close reading end

        printf("Opening file\n");
        FILE *fd = fopen(path, "r");

        if (fd > 0)
        {
            printf("File successfully opened\nReading file\n");
            char c = 0;

            while (c != EOF)
            {
                c = getc(fd);
                write(pipefd[1], &c, 1);
            }
            printf("Finished reading file.\n");
        }
        else
        {
            printf("Unable to open file.\n");
            return;
        }

        printf("Closing file\n");
        fclose(fd);
        printf("\nTerminating child process\n");
        exit(0);
    }

    printf("Inside parent process\nClosing writing end in parent process.\n");
    close(pipefd[1]); // Close writing end of first pipe

    printf("\nContents of file are:\n");
    char c = 0;
    while (read(pipefd[0], &c, sizeof(c)) > 0)
    {
        if (c != EOF)
        {
            printf("%c", c);
        }
        else
        {
            break;
        }
    }
    wait(NULL);
}

//___________________________________________________

int main()
{
    int choice;
    printf("Enter\n1: To send data from parent to child\n2: To send data from child to parent: ");
    cin >> choice;

    char path[1000];
    printf("Enter file destination: ");
    cin >> path;

    do
    {
        switch (choice)
        {
        case 1:
            parentToChild(path);
            break;
        case 2:
            childToParent(path);
            break;
        default:
            printf("Invalid input!\nSelect\n1: To send data from parent to child\n2: To send data from child to parent: ");
            cin >> choice;
        }
    } while (choice == 0 || choice > 2);
}