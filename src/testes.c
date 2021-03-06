#include "mintest/macros.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int test1(){
  test_assert(1/0, "Divisão por zero, não dara certo\n");
  return 0;
}

int test2(){
  int counter = 0;
  for(int i = 0; i < 200000 ; i++){
    counter += 1;
  }

  test_assert(counter == 200000, "Teste loop muitas iterações\n");
  return 0;
}

int test3(){
  alarm(7);
  while(1){
  }

  printf("ERRO, LOOP INFINITO\n");

  return 0;
}

int test4(){
  test_assert(4 == 4, "Esse teste ira passar\n");
  test_assert(1 != 1 , "Esse teste não ira passar\n");

  return 0;
}

int test5(){
  for(int i = 0 ; i < 50 ; i++){
    printf("Numero de prints %d,IGOR\n", i);
  }

  return 0;
}

int test6(){
  test_assert(1 == 1, "Teste rapido\n");
  test_assert(2 * 3 == 6, "Teste lento\n");

  return 0;
}

int test7(){
  char vectorX[12];

  test_assert(vectorX[14] == 4, "SEGMENTION FAULT ERROR");

  return 0;
}

test_list = { TEST(test1), TEST(test2), TEST(test3), TEST(test4) , TEST(test5) , TEST(test6) , TEST(test7) };

#include "mintest/runner.h"
