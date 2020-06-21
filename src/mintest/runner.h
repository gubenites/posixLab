#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int size = sizeof(all_tests)/sizeof(test_data);
    pid_t filho,pai;
    int wt;

    printf("Number of tests to be executed: %d\n", size);
    printf("=====================\n\n");
    int pass_count = 0;
    for (int i = 0; i < size; i++) {
      filho = fork();
      if (filho == 0) {
        printf("LOOP: %d\n", i);
        if (all_tests[i].function() >= 0) {
            printf("TEST: %d\n", i + 1);
            printf("%s: [PASS]\n", all_tests[i].name);
            pass_count++;
        };
      }
    }

    printf("\n\n=====================\n");
    printf("%d/%d tests passed\n", pass_count, size);
    return 0;
}
