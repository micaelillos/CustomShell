//
//  shell.c
//  Test
//
//  Created by Micael Illos on 17/09/2020.
//  Copyright © 2020 Micael Illos. All rights reserved.
//

#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include  <stdio.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include  <signal.h>
#include  <stdlib.h>
#include <string.h>

void INThandler(int);
void welcomeScreen();


void welcomeScreen(){
        printf("\n\t============================================\n");
        printf("\t               Micael's C Shell\n");
        printf("\t--------------------------------------------\n");
        printf("\t             For Operating Systems\n");
        printf("\t============================================\n");
        printf("\t--------------------------------------------\n");
        printf("\t             Netanya Academic College\n");
        printf("\t============================================\n");
        printf("\n\n");
}

int main()

{

  char command[1024];

  char command2[1024];

  char command3[1024];

  char *token;

  char *outfile;

  char *infile;


  int i, fd, amper, redirect, readfrom, retid, status;

  char *argv[10];

  //char *prompt = 0;

  int redirectnew = 0;

  char prompt[20];

  int repeat = 0; // for !!

  strcpy(prompt, "hello: ");

  signal(SIGINT, INThandler);
  welcomeScreen();

  while (1)

  {

    //  printf("hello: ");

    if (repeat)

    {

      strcpy(command, command2);

      repeat = 0;
    }

    else

    {

      printf("%s", prompt);

      fgets(command, 1024, stdin);

      strcpy(command3, command);
    }

    command[strlen(command) - 1] = '\0';

    //printf("\"%s\"\n", command);

    //exit(0);

    /* parse command line */

    argv[0] = NULL;

    i = 0;

    token = strtok(command, " ");

    while (token != NULL)

    {

      argv[i] = token;

      //printf ("%s\n",token);

      token = strtok(NULL, " ");

      i++;
    }

    argv[i] = NULL;

    /* Does command line end with & */

    if (argv[0] && !strcmp(argv[i - 1], "&"))

    {

      amper = 1;

      argv[i - 1] = NULL;
    }

    else

      amper = 0;

       if (!strcmp(argv[0], "echo")){
   int j;
   if(i == 2 && !strcmp(argv[1], "$?")){
       printf("%d\n", status >> 8);
       continue;
     }
   else{
    for (j = 1; argv[j] != NULL; j++){
      printf("%s ", argv[j]);
    }
   }
    printf("\n");
    continue;
  }

    //check if to quit

    if (strcmp(argv[0], "quit") == 0) 

    {

      exit(0);
    }

    if (argv[0] && !strcmp(argv[0], "!!")) //if first string is  !!

    {

      repeat = 1;

      continue;
    }

    strcpy(command2, command3);

    if (argv[0] && argv[1] && !strcmp(argv[i - 2], ">"))

    {

      redirect = 1;

      argv[i - 2] = NULL;

      outfile = argv[i - 1];

      // f = fork();
    }

    else if (argv[0] && argv[1] && !strcmp(argv[i - 2], ">>")) // <---

    {

      redirect = 2;

      argv[i - 2] = NULL;

      outfile = argv[i - 1];
    }



      else if (argv[0] && i>2 && ! strcmp(argv[i - 2], "<")) {
    readfrom = 1;
    argv[i - 2] = NULL;
    infile = argv[i - 1];
  }

   else

      redirect = 0;

    /* for commands not part of the shell command language */

    if (argv[0] && !strcmp(argv[0], "prompt"))

    {

      if (!strcmp(argv[1], "="))

        strcpy(prompt, strcat(argv[2] , ": "));

      continue;
    }

    if (fork() == 0)

    {

      /* redirection of IO ? */

      if (redirect == 1)

      {

        fd = creat(outfile, 0660);

        close(STDOUT_FILENO); //only for child

        dup(fd); //only for child

        close(fd);

        /* stdout is now redirected */
      }

   if(readfrom){
      fd = open(infile, O_RDONLY);
      close (STDIN_FILENO);
      dup(fd);
      close(fd);
    }

      if (redirect == 2) //for 2 >>

      {

        fd = open(argv[i - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);

        close(STDOUT_FILENO); //only for child

        dup(fd); //only for child

        close(fd);

        /* stdout is now redirected */
      }

      execvp(argv[0], argv);
    }

    /* parent continues here */

    if (amper == 0)

      retid = wait(&status);
  }
}
void INThandler(int sig)
{
        char  c;

        signal(sig, SIG_IGN);
        printf("\nYou typed Control-C!\n");
        

        
            signal(SIGINT, INThandler);

}
