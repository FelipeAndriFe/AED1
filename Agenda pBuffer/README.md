# FELIPE ANDRIOTTI FERREIRA (M1)

## Agenda pBuffer

O problema:

- Fazer uma agenda de contatos com as funções (1- Adicionar pessoa, 2- Remover pessoa, 3- Buscar pessoa, 4- Listar todas e 5- Sair).
- Cada pessoa possui: nome, idade e email.
- No código não é permitido declarar variáveis convencionais (int, char, ...), somente ponteiros. Variáveis como parâmentros de funções também não são permitidas.
- Não é permitido usar structs.
- Todos os dados do programa devem estar dentro de um buffer (void *pBuffer).

Implementação:

- No início do pBuffer é alocado um HEADER, composto de um int i (contador), um int qnt (quantidade de pessoas), um int menu (usado na escolha da operação), e um char alvo[10] (usado nas funções de busca e remoção).
- As pessoas são alocadas sequencialmente após o HEADER. Cada pessoa ocupa 10 char (nome) + 1 int (idade) + 20 char (email).