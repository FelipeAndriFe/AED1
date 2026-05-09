#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <crtdbg.h>

#define HEADER ( sizeof( int ) * 5 + sizeof( char ) * 256 )
#define I ( (int *) pBuffer )
#define I2 ( (int *) *pBuffer )
#define QNT ( (int *) pBuffer + 1 )
#define QNT2 ( (int *) *pBuffer + 1 )
#define MENU ( (int *) pBuffer + 2 )
#define MENU2 ( (int *) *pBuffer + 2 )
#define TAMANHO ( (int *) pBuffer + 3 )
#define TAMANHO2 ( (int *) *pBuffer + 3 )
#define OFFSET ( (int *) pBuffer + 4 )
#define OFFSET2 ( (int *) *pBuffer + 4 )
#define TEMP ( (char *) pBuffer + ( sizeof( int ) * 5 ) )
#define TEMP2 ( (char *) *pBuffer + ( sizeof( int ) * 5 ) )

void Adicionar( void **pBuffer );
void Listar( void *pBuffer );
void Buscar( void *pBuffer );
void Remover( void **pBuffer );

int main() {
    void *pBuffer;
    
    //pBuffer = int i, int qnt, int menu, int tamanho, int offset, char temp[256]
    pBuffer = malloc( HEADER );
    if ( !pBuffer ) {
        exit(1);
    }

    *QNT = 0;
    *TAMANHO = (int) HEADER;

    printf( "--AGENDA PBUFFER MENU--\n" );
    for( ;; ) {
        do {
            printf( "\n1. Adicionar pessoa\n" );
            printf( "2. Remover pessoa\n" );
            printf( "3. Buscar pessoa\n" );
            printf( "4. Listar todas\n" );
            printf( "5. Sair\n" );
            scanf( "%d", MENU );
        } while ( *MENU > 5 || *MENU < 1 );

        switch( *MENU ) {
            case 1:
                Adicionar( &pBuffer );
                break;
            case 2:
                Remover( &pBuffer );
                break;
            case 3:
                Buscar( pBuffer );
                break;
            case 4:
                Listar( pBuffer );
                break;
            case 5:
                free( pBuffer );
                _CrtDumpMemoryLeaks();
                exit(0);
                break;
        }
    }
}

void Adicionar( void **pBuffer ) {
    void *temp;

    printf( "--Digite o nome: " );
    scanf( "%255s", TEMP2 );
    *I2 = (int) strlen( TEMP2 ) + 1;

    temp = realloc( *pBuffer, *TAMANHO2 + sizeof( int ) * 2 + *I2 );
    if ( !temp ) {
        printf( "Falha ao Adicionar\n " );
        return;
    }
    *pBuffer = temp;

    *OFFSET2 = *TAMANHO2; 
    *(int *)( (char *)*pBuffer + *OFFSET2 ) = (int) sizeof( int ) + *I2;
    
    strcpy( (char *)*pBuffer + *OFFSET2 + sizeof( int ), TEMP2 );
    *TAMANHO2 += (int) sizeof( int ) * 2 + *I2;

    printf( "--Digite a idade: " );
    scanf( "%d", (int *) ( (char *)*pBuffer + *OFFSET2 + *(int *)( (char *)*pBuffer + *OFFSET2 ) ) );

    *(int *) ( (char *)*pBuffer + *OFFSET2 ) += (int) sizeof( int );

    printf( "--Digite o email: " );
    scanf( "%255s", TEMP2 );

    *I2 = (int) strlen( TEMP2 ) + 1;

    temp = realloc( *pBuffer, *TAMANHO2 + *I2 );
    if ( !temp ) {
        printf( "Falha ao Adicionar\n " );
        return;
    }
    *pBuffer = temp;

    strcpy( (char *)*pBuffer + *OFFSET2 + *(int *) ( (char *) *pBuffer + *OFFSET2 ), TEMP2 );
    *(int *) ( (char *) *pBuffer + *OFFSET2 ) += *I2;
    *TAMANHO2 += *I2;
    *QNT2 += 1;

    printf( "Nome Adicionado\n" );
}

void Listar( void *pBuffer ) {
    if ( *QNT == 0 ) {
        printf( "Agenda Vazia\n" );
        return;
    }

    *OFFSET = (int) HEADER;

    for ( *I = 0; *I < *QNT; (*I)++ ) {
        printf( "\n--Pessoa %d\n", (*I) + 1 );
        printf( "%s\n", (char *) pBuffer + *OFFSET + sizeof( int ) );
        printf( "%d\n", *(int *) ( (char*) pBuffer + *OFFSET + sizeof( int ) + strlen( (char *) pBuffer + *OFFSET + sizeof( int ) ) + 1 ) );
        printf( "%s\n", (char *) pBuffer + *OFFSET + sizeof( int ) * 2 + strlen( (char *) pBuffer + *OFFSET + sizeof( int ) ) + 1 );

        *OFFSET += *(int *) ( (char *) pBuffer + *OFFSET );
    }
}

void Buscar( void *pBuffer ) {
    if ( *QNT == 0 ) {
        printf( "Agenda Vazia\n" );
        return;
    }

    printf( "--Digite o nome: " );
    scanf( "%255s", TEMP );

    *OFFSET = (int) HEADER;

    for ( *I = 0; *I < *QNT; (*I)++ ) {
        if ( strcmp( TEMP, (char *) pBuffer + *OFFSET + sizeof( int ) ) == 0 ) {
            printf( "\n--Pessoa %d\n", (*I) + 1 );
            printf( "%s\n", (char *) pBuffer + *OFFSET + sizeof( int ) );
            printf( "%d\n", *(int *) ( (char*) pBuffer + *OFFSET + sizeof( int ) + strlen( (char *) pBuffer + *OFFSET + sizeof( int ) ) + 1 ) );
            printf( "%s\n", (char *) pBuffer + *OFFSET + sizeof( int ) * 2 + strlen( (char *) pBuffer + *OFFSET + sizeof( int ) ) + 1 );
            break;
        }

        *OFFSET += *(int *) ( (char *) pBuffer + *OFFSET );
    }

    if ( *I == *QNT ) {
        printf( "Nome nao encontrado\n" );
    }
}

void Remover( void **pBuffer ) {
    void *temp;

    if ( *QNT2 == 0 ) {
        printf( "Agenda Vazia\n" );
        return;
    }

    printf( "--Digite o nome: " );
    scanf( "%255s", TEMP2 );
    
    *OFFSET2 = (int) HEADER;

    for ( *I2 = 0; *I2 < *QNT2; (*I2)++ ) {
        if ( strcmp( TEMP2, (char *) *pBuffer + *OFFSET2 + sizeof( int ) ) == 0 ) {
            if ( *I2 < ( *QNT2 - 1 ) ) {
                *MENU2 = *(int *) ( (char *) *pBuffer + *OFFSET2 );
                *I2 = *OFFSET2;
                while ( *I2 < *TAMANHO2 ) {
                    *I2 += *(int *) ( (char *) *pBuffer + *I2 );
                }

                memmove( (char *) *pBuffer + *OFFSET2,
                         (char *) *pBuffer + *OFFSET2 + *MENU2,
                         *I2 - ( *MENU2 + *OFFSET2 ) );

                *TAMANHO2 -= *MENU2;
            } else {
                *TAMANHO2 -= *(int *) ( (char *) *pBuffer + *OFFSET2 );
            }
            break;
        }

        *OFFSET2 += *(int *) ( (char *) *pBuffer + *OFFSET2 );
    }

    if ( *I2 == *QNT2 ) {
        printf( "Nome nao encontrado\n" );
    } else {
        temp = realloc( *pBuffer, *TAMANHO2 );
        if ( !temp ) {
            printf( "Falha ao Remover\n" );
            return;
        }
        *pBuffer = temp;
        (*QNT2)--;
        printf( "Nome Removido\n" );
    }
}