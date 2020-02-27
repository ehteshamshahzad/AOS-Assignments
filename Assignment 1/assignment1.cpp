#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

void parentToChild(char *path) // 1
{

  int pipefd[2];

  pid_t pid;
  //int oldflags = fcntl(info_pipe[direction], F_GETFL);
  //if (pipe2(pipefd, O_NONBLOCK)==-1) // to avoid blocking call
  if (pipe(pipefd))
  {
    fprintf(stderr, "Pipe Failed\n");
    return;
  }

  printf("Creating child process\n");
  pid = fork();

  if (pid < 0)
  {
    printf("Error. Unable to create child process\n");
    return;
  }

  else if (pid > 0) // Parent Process
  {
    printf("Inside parent process\n");

    close(pipefd[0]); // Closing reading end
    FILE *fd = fopen(path, "r");

    if (fd <= 0)
    {
      printf("Unable to open file\n");
      return;
    }

    else if (fd > 0)
    {
      printf("File successfully opened\n");
      char c = 0;

      while (c != EOF)
      {
        c = getc(fd);
        write(pipefd[1], &c, 1);
      }
    }
    wait(NULL);
    fclose(fd);
  }

  else if (pid == 0)
  {

    printf("Inside child process\n");
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
        printf("\nTerminating child process\n");
        exit(0);
      }
    }
  }
}

//___________________________________________________

void childToParent(char *path) // 2
{

  int pipefd[2];

  pid_t pid;
  //int oldflags = fcntl(info_pipe[direction], F_GETFL);
  //if (pipe2(pipefd, O_NONBLOCK)==-1) // to avoid blocking call
  if (pipe(pipefd))
  {
    fprintf(stderr, "Pipe Failed\n");
    return;
  }

  printf("Creating child process\n");
  pid = fork();

  if (pid < 0)
  {
    printf("Error. Unable to create child process\n");
    return;
  }
  else if (pid > 0)
  {
    wait(NULL);
    printf("Inside parent process\n");
    close(pipefd[1]); // Close writing end of first pipe
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
  }

  else if (pid == 0)
  {
    printf("Inside child process\n");
    close(pipefd[0]); // Close reading end
    FILE *fd = fopen(path, "r");
    if (fd <= 0)
    {
      printf("Unable to open file\n");
      return;
    }

    else if (fd > 0)
    {
      printf("File successfully opened\n");
      char c = 0;
      while (c != EOF)
      {
        c = getc(fd);
        write(pipefd[1], &c, 1);
      }
    }
    fclose(fd);
    printf("\nTerminating child process\n");
    exit(0);
  }
}

//___________________________________________________

int main()
{
  int choice;
  printf("Select\n1: To send data from parent to child\n2: To send data from child to parent: ");
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