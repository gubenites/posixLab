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
      int pass_count = 0;
      for (int i = 0; i < size; i++) {
        filho = fork();
        if (filho == 0) {
          if (all_tests[i].function() >= 0) {
              printf("%s: [PASS]\n", all_tests[i].name);
          };
          break;
        } else{
          if (wait(&wt) >= 0) {
            if (WIFSIGNALED(wt)) {
                printf("[ERROR]: %s\n",strsignal(WTERMSIG(wt)));

                printf("\n%d/%d tests passed\n", pass_count, size);
                printf("\n=====================\n");

                pass_count++;
            }
          }
        }


      }
    } else if(argc > 1){

      printf("Number of tests to be executed: %d\n", 1);
      printf("=====================\n\n");
      int pass_count = 0;

      for (int i = 0; i < size; i++) {
        if (strcmp(all_tests[i].name, argv[1]) == 0) {
          filho = fork();
          if (filho == 0) {
            if (all_tests[i].function() >= 0) {
              printf("%s: [PASS]\n", all_tests[i].name);
            }
            break;
          } else{
            if (wait(&wt) >= 0) {
              if (WIFEXITED(wt)) {
                  printf("Filho acabou: %d\n",(char) WEXITSTATUS(wt));
                  pass_count++;

                  printf("%d/%d tests passed\n", pass_count, 1);
                  printf("\n\n=====================\n");
              }
            }
          }
        }
      }
    }
    return 0;
}
