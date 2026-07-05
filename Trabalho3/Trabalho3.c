#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <crtdbg.h>

typedef struct no_s {
	int					valor;
	int					tamanho;
	int					altura;
	struct no_s *		esq;
	struct no_s *		dir;
} no_t;

/*
====================
Altura
====================
*/
static int Altura( const no_t *n ) {
	return n ? n->altura : 0;
}

/*
====================
Tamanho
====================
*/
static int Tamanho( const no_t *n ) {
	return n ? n->tamanho : 0;
}

/*
====================
Atualizar
====================
*/
static void Atualizar( no_t *n ) {
	int		he;
	int		hd;

	he = Altura( n->esq );
	hd = Altura( n->dir );
	n->altura = ( he > hd ? he : hd ) + 1;
	n->tamanho = 1 + Tamanho( n->esq ) + Tamanho( n->dir );
}

/*
====================
RotacaoDireita
====================
*/
static no_t *RotacaoDireita( no_t *y ) {
	no_t *	x;

	x = y->esq;
	y->esq = x->dir;
	x->dir = y;
	Atualizar( y );
	Atualizar( x );
	return x;
}

/*
====================
RotacaoEsquerda
====================
*/
static no_t *RotacaoEsquerda( no_t *x ) {
	no_t *	y;

	y = x->dir;
	x->dir = y->esq;
	y->esq = x;
	Atualizar( x );
	Atualizar( y );
	return y;
}

/*
====================
FatorBalanceamento
====================
*/
static int FatorBalanceamento( const no_t *n ) {
	return Altura( n->esq ) - Altura( n->dir );
}

/*
====================
Rebalancear
====================
*/
static no_t *Rebalancear( no_t *n ) {
	int		fb;

	Atualizar( n );
	fb = FatorBalanceamento( n );

	if ( fb > 1 ) {
		if ( FatorBalanceamento( n->esq ) < 0 ) {
			n->esq = RotacaoEsquerda( n->esq );
		}
		return RotacaoDireita( n );
	}
	if ( fb < -1 ) {
		if ( FatorBalanceamento( n->dir ) > 0 ) {
			n->dir = RotacaoDireita( n->dir );
		}
		return RotacaoEsquerda( n );
	}
	return n;
}

/*
====================
Inserir_r

	Essa funcao insere um valor na arvore e retorna a nova raiz.
====================
*/
no_t *Inserir_r( no_t *raiz, int valor ) {
	no_t *	n;

	if ( !raiz ) {
		n = malloc( sizeof( no_t ) );
		n->valor = valor;
		n->tamanho = 1;
		n->altura = 1;
		n->esq = NULL;
		n->dir = NULL;
		return n;
	}
	if ( valor < raiz->valor ) {
		raiz->esq = Inserir_r( raiz->esq, valor );
	} else {
		raiz->dir = Inserir_r( raiz->dir, valor );
	}
	return Rebalancear( raiz );
}

/*
====================
Liberar_r
====================
*/
void Liberar_r( no_t *n ) {
	if ( !n ) {
		return;
	}
	Liberar_r( n->esq );
	Liberar_r( n->dir );
	free( n );
}

/*
====================
Search

	Funcao auxiliar para a solucao com AVL.
	Conta quantos nos da arvore sao maiores que o alvo.
====================
*/
long int Search( no_t *root, long int target ) {
	no_t *curr = root;
	long int count = 0;

	while ( curr ) {
		 if ( curr->valor > target ) {
			count += 1 + Tamanho( curr->dir );
			curr = curr->esq;
		 } else {
			curr = curr->dir;
		 }
	}

	return count;
}

/*
====================
isIdealPermutation

	Solucao utilizando uma arvore AVL.
====================
*/
bool isIdealPermutation( int* nums, int numsSize ) {
    if ( numsSize == 1 ) return true;

	long int global = 0, local = 0;

	no_t *root = NULL;
	root = Inserir_r( root, nums[0] );

	for ( long int i = 1; i < numsSize; i++ ) {
		global += Search( root, nums[i] );

		root = Inserir_r( root, nums[i] );
	}

	for ( long int i = 0; i + 1 < numsSize; i++ ) {
		if ( nums[i] > nums[i + 1] ) {
			local++;
		}
	}

	Liberar_r( root );
	return global == local;
}

/*
====================
ForcaBruta

	Referencia O( n^2 ) usada para conferir os resultados dos testes.
====================
*/
static bool ForcaBruta( const int *nums, int n ) {
	long long	global;
	long long	local;
	int			i;
	int			j;

	global = 0;
	for ( i = 0; i < n; i++ ) {
		for ( j = i + 1; j < n; j++ ) {
			if ( nums[i] > nums[j] ) {
				global++;
			}
		}
	}

	local = 0;
	for ( i = 0; i + 1 < n; i++ ) {
		if ( nums[i] > nums[i + 1] ) {
			local++;
		}
	}

	return global == local;
}

/*
====================
ImprimirArray
====================
*/
static void ImprimirArray( const int *a, int n ) {
	int		i;

	printf( "[" );
	for ( i = 0; i < n; i++ ) {
		printf( "%d%s", a[i], i + 1 < n ? "," : "" );
	}
	printf( "]" );
}

/*
====================
RodarTeste
====================
*/
static int RodarTeste( int num, int *nums, int n, bool esperado ) {
	bool	obtido;
	bool	bruto;
	int		ok;

	obtido = isIdealPermutation( nums, n );
	bruto = ForcaBruta( nums, n );
	ok = ( obtido == esperado ) && ( bruto == esperado );

	printf( "Teste %2d: nums = ", num );
	ImprimirArray( nums, n );
	printf( "\n  esperado = %s | avl = %s | forca bruta = %s  ->  %s\n\n",
			esperado ? "true" : "false",
			obtido ? "true" : "false",
			bruto ? "true" : "false",
			ok ? "OK" : "FALHOU" );
	return ok;
}

/*
====================
main
====================
*/
int main( void ) {
	int		passou;

	int		t1[]  = { 1, 0, 2 };				/* exemplo 1 do enunciado             */
	int		t2[]  = { 1, 2, 0 };				/* exemplo 2 do enunciado             */
	int		t3[]  = { 0 };						/* elemento unico                     */
	int		t4[]  = { 0, 1, 2, 3, 4 };			/* identidade: zero inversoes         */
	int		t5[]  = { 1, 0, 3, 2, 4 };			/* trocas adjacentes disjuntas        */
	int		t6[]  = { 2, 0, 1 };				/* valor a 2 posicoes do lugar        */
	int		t7[]  = { 4, 3, 2, 1, 0 };			/* permutacao reversa                 */
	int		t8[]  = { 0, 2, 1 };				/* uma troca adjacente no fim         */
	int		t9[]  = { 1, 0, 2, 4, 3 };			/* trocas nas duas pontas             */
	int		t10[] = { 3, 0, 1, 2 };				/* 3 globais, 1 local                 */

	passou = 0;
	passou += RodarTeste(  1, t1,  3, true );
	passou += RodarTeste(  2, t2,  3, false );
	passou += RodarTeste(  3, t3,  1, true );
	passou += RodarTeste(  4, t4,  5, true );
	passou += RodarTeste(  5, t5,  5, true );
	passou += RodarTeste(  6, t6,  3, false );
	passou += RodarTeste(  7, t7,  5, false );
	passou += RodarTeste(  8, t8,  3, true );
	passou += RodarTeste(  9, t9,  5, true );
	passou += RodarTeste( 10, t10, 4, false );

	printf( "Resultado final: %d/10 testes passaram\n", passou );
	_CrtDumpMemoryLeaks();
	return passou == 10 ? 0 : 1;
}