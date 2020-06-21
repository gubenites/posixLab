# posixLab
GUSTAVO MOLINA \
REQUISITOS PARA: C

implementado : \
  -testes ocorrendo em paralelo \
  -testes ocorrendo de forma individual caso passado argumento em argv[2] \
  -testes ocorrendo sem interferencia por meio de fork() \

Para rodar o arquivo basta rodar gcc testes.c -o testes (compilar) e então rodar ./testes (rodara todos) ou então ./teste "testX" dado que testX sera o teste especifico que voce ira querer rodar. \
A seguinte implementação segue a estrutura de tres arquivos principais: \
  -runner.h \
  -testes.c \
  -macros.h \

  1.Runner.h: \
    Consiste no arquivo em que foi feita grande maioria das alterações, o mesmo pode ser separado em 2 partes, uma em que argc == 0 e a outra em que agrc > 1. Analisando a parte em que argc == 0 temos uma forma de rodar os testes feitos primeiramente em forma paralela, ao criar um fork, e gerenciar um wait, temos a necessidade do processo filho terminar e não rodar todos ao mesmo tempo. Enquanto quando argc >= 1, passamos via terminal o nome do teste a ser executado que é recebido como argv[2] o mesmo é iterado pelas funcoes do arquivo teste comparando string a string pelo comando strcmp de tal forma que ao encontrar o equivalente, somente aquele teste sera executado, cabe observar que no mesmo os testes não ocorrem de forma simultanea TAMBEM, dado que há a criação de processos filhos e chamadas de wait para que o processo acabe antes de avancar para o proximo. O fato pode ser observado como: \
    Primeiro é rodado test1, depois test 2, então test3 e assim por diante, se não houvesse a criação do fork(), os processos iriam acontecer simultaneamente ficando muito confuso para se ter uma analise mais detalhada e especifica a cerca dos teste. \

  2.Testes.c: \
    No arquivo testes.c temos a implementação dos testes que serão executados e transferidos para o runner.c, dados eles que são: \
    test1: Cause erro e termine com divisão por zero. \
    test2: Faça muito trabalho, mas eventualmente acabe (sem usar sleep ). \
    test3: Fique em loop infinito. \
    test4: Tenha asserts que falham e passem no mesmo teste. \
    test5: Tenha testes que façam muitos prints. \
    test6: Tenha testes que sejam rápidos e testes que sejam lentos (pode usar sleep para simular). \
    test7: Cause erro e termine com falha de segmentação. \

  3.Macros.h: \
    Não foi feita nenhuma alteração neste arquivo. \
