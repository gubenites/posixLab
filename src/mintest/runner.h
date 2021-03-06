#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int size = sizeof(all_tests)/sizeof(test_data);
    pid_t filho,pai;
    int wt;

    if (argc == 1) {
      printf("Number of tests to be executed: %d\n", size);
      printf("=====================\n\n");

      int contador_pass = 0;
      int contador_error = 0;

      for (int i = 0; i < size; i++) {
        contador_pass += 1;
        filho = fork();
        if (filho == 0) {
          if (all_tests[i].function() >= 0) {
              printf("\n%s: [PASS]\n", all_tests[i].name);
              printf("\n%d/%d tests passed\n", contador_pass, size);
              printf("\n=====================\n");
          };
          break;
        } else{
          if (wait(&wt) >= 0) {
            if (WIFSIGNALED(wt)) {
                printf("%s: [ERROR]: %s\n",all_tests[i].name, strsignal(WTERMSIG(wt)));
                printf("\n=====================\n");
                contador_pass -= 1;
                contador_error += 1;

            }
          }
        }
        if(i == size - 1){
          int var1 = contador_pass - 1;
          int var2 = size - var1 - contador_error;
          printf("\n=====================\n");
          printf("\n%d/%d Total tests passed\n", var1, size);
          printf("%d/%d Total tests error\n", contador_error, size);
          printf("%d/%d Total tests fail\n", var2 , size);
          printf("\n=====================\n");

        }
      }
    } else if(argc > 1){
      printf("Number of tests to be executed: %d\n", 1);
      printf("=====================\n\n");

      int contador_pass = 0;

      for (int i = 0; i < size; i++) {
        if (strcmp(all_tests[i].name, argv[1]) == 0) {
          filho = fork();
          if (filho == 0) {
            if (all_tests[i].function() >= 0) {
                contador_pass += 1;
                printf("\n%s: [PASS]\n", all_tests[i].name);
                printf("\n%d/%d tests passed\n", contador_pass, 1);
                printf("\n=====================\n");
            };
            break;
          } else{
            if (wait(&wt) >= 0) {
              if (WIFSIGNALED(wt)) {
                  printf("%s: [ERROR]: %s\n",all_tests[i].name, strsignal(WTERMSIG(wt)));
                  printf("\n=====================\n");
              }
            }
          }
        }
      }
    }
    return 0;
}
