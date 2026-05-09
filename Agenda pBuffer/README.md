# FELIPE ANDRIOTTI FERREIRA (M1)

## Agenda pBuffer

O problema:

- Fazer uma agenda de contatos com as funções (1- Adicionar pessoa, 2- Remover pessoa, 3- Buscar pessoa, 4- Listar todas e 5- Sair).
- Cada pessoa possui: nome, idade e email.
- No código não é permitido declarar variáveis convencionais (int, char, ...), somente ponteiros tipo void. Variáveis como parâmentros de funções também não são permitidas.
- Não é permitido usar structs.
- Todos os dados do programa devem estar dentro de um buffer (void *pBuffer).
- Nome e email podem ser de qualquer tamanho.

Implementação:

- No início do pBuffer é alocado um HEADER, composto de um int i (contador), um int qnt (quantidade de pessoas), um int menu (usado na escolha da operação), um int tamanho (número de bytes ocupados pelo pBuffer inteiro), um int offset (usado para navegar pelo pBuffer), e um char temp[256] (buffer auxiliar para leitura de strings).
- Macros (define) foram usados para melhorar a escrita e leitura do código. 
- Código inteiramente modularizado.

Restrições:

- Nomes e emails não podem conter espaços nem exceder 255 caracteres (devido ao uso do scanf).