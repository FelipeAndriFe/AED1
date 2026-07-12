#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

/*
====================
CompararInt

	Comparador para qsort; forma segura contra overflow de ( x - y ).
====================
*/
static int CompararInt( const void *a, const void *b ) {
	int		x;
	int		y;

	x = *( const int * )a;
	y = *( const int * )b;
	return ( x > y ) - ( x < y );
}

/*
====================
fourSum

	Assinatura exigida pelo LeetCode.
	returnSize        <- numero de quadruplas encontradas
	returnColumnSizes <- array com o tamanho de cada linha ( sempre 4 )
====================
*/
int **fourSum( int *nums, int numsSize, int target,
			   int *returnSize, int **returnColumnSizes ) {

	if ( numsSize < 4 ) {
		*returnSize = 0;
		*returnColumnSizes = NULL;
		return NULL;
	}

	int **result = NULL, c = 1;

	qsort( nums, numsSize, sizeof( int ), CompararInt );

	int pont1, pont2, pont3, pont4;

	for ( int i = 0; i < numsSize - 3; i++ ) {
		pont1 = i;

        for (int j = i + 1; j < numsSize - 2; j++ ) {
            pont2 = j;
            pont3 = j + 1;
            pont4 = numsSize - 1;

			while ( pont3 < pont4 ) {
				long long int test = ( long long int ) nums[pont1] + nums[pont2] + nums[pont3] + nums[pont4];

				if ( test < target ) {
					while ( pont3 < pont4 && nums[pont3] == nums[pont3 + 1] ) {
						pont3++;
					}
					pont3++;
				} else if ( test > target ) {
					while ( pont3 < pont4 && nums[pont4] == nums[pont4 - 1] ) {
						pont4--;
					}
					pont4--;
				} else if ( test == target ) {
					result = ( int ** ) realloc( result, sizeof( int * ) * c );
					result[c - 1] = ( int * ) malloc( sizeof( int ) * 4 );

					int k = 0;
					result[c - 1][k++] = nums[pont1];
					result[c - 1][k++] = nums[pont2];
					result[c - 1][k++] = nums[pont3];
					result[c - 1][k++] = nums[pont4];

					c++;
					
					while ( pont3 < pont4 && nums[pont3] == nums[pont3 + 1] ) {
						pont3++;
					}
					pont3++;
				}
            }

			while ( pont2 < numsSize - 2 && nums[pont2] == nums[pont2 + 1] ) {
				pont2++;
                j++;
			}
		}

		while ( pont1 < numsSize - 3 && nums[pont1] == nums[pont1 + 1] ) {
			pont1++;
			i++;
		}
	}

	*returnSize = c - 1;

	if ( c - 1 == 0 ) {
		*returnColumnSizes = NULL;
	} else {
		*returnColumnSizes = ( int * ) malloc( sizeof( int ) * ( c - 1 ) );
		for ( int i = 0; i < c - 1; i++ ) {
			( *returnColumnSizes )[i] = 4;
		}
	}

	return result;
}

/*
====================
CompararQuadruplas

	Ordena as linhas do resultado lexicograficamente para permitir
	comparacao direta com o esperado, ja que o enunciado aceita a
	resposta em qualquer ordem.
====================
*/
static int CompararQuadruplas( const void *a, const void *b ) {
	const int *	x;
	const int *	y;
	int			k;

	x = *( int *const * )a;
	y = *( int *const * )b;
	for ( k = 0; k < 4; k++ ) {
		if ( x[k] != y[k] ) {
			return ( x[k] > y[k] ) - ( x[k] < y[k] );
		}
	}
	return 0;
}

/*
====================
ImprimirQuadruplas
====================
*/
static void ImprimirQuadruplas( int **res, int n ) {
	int		k;

	printf( "[" );
	for ( k = 0; k < n; k++ ) {
		printf( "[%d,%d,%d,%d]%s", res[k][0], res[k][1], res[k][2], res[k][3],
				k + 1 < n ? "," : "" );
	}
	printf( "]" );
}

/*
====================
RodarTeste

	Compara o retorno de fourSum com o resultado esperado hard-coded.
	As quadruplas esperadas devem estar em ordem lexicografica.
====================
*/
static int RodarTeste( int num, const int *entrada, int n, int target,
					   const int esperado[][4], int esperadoQtd ) {
	int **	res;
	int *	nums;
	int *	colSizes;
	int		qtd;
	int		ok;
	int		k;
	int		c;

	nums = malloc( sizeof( int ) * ( n > 0 ? n : 1 ) );
	memcpy( nums, entrada, sizeof( int ) * n );

	qtd = 0;
	colSizes = NULL;
	res = fourSum( nums, n, target, &qtd, &colSizes );

	ok = ( qtd == esperadoQtd );
	if ( ok && qtd > 0 ) {
		qsort( res, qtd, sizeof( int * ), CompararQuadruplas );
		for ( k = 0; k < qtd && ok; k++ ) {
			for ( c = 0; c < 4; c++ ) {
				if ( res[k][c] != esperado[k][c] ) {
					ok = 0;
					break;
				}
			}
		}
	}

	printf( "Teste %2d: target = %d, nums = [", num, target );
	for ( k = 0; k < n; k++ ) {
		printf( "%d%s", entrada[k], k + 1 < n ? "," : "" );
	}
	printf( "]\n  obtido = " );
	ImprimirQuadruplas( res, qtd );
	printf( "  ->  %s\n\n", ok ? "OK" : "FALHOU" );

	for ( k = 0; k < qtd; k++ ) {
		free( res[k] );
	}
	free( res );
	free( colSizes );
	free( nums );
	return ok;
}

/*
====================
main
====================
*/
int main( void ) {
	int		passou;

	/* Teste 1: exemplo 1 do enunciado */
	int		t1[] = { 1, 0, -1, 0, -2, 2 };
	int		e1[][4] = { { -2, -1, 1, 2 }, { -2, 0, 0, 2 }, { -1, 0, 0, 1 } };

	/* Teste 2: exemplo 2 do enunciado - duplicatas extremas */
	int		t2[] = { 2, 2, 2, 2, 2 };
	int		e2[][4] = { { 2, 2, 2, 2 } };

	/* Teste 3: menos de 4 elementos - resposta vazia */
	int		t3[] = { 1, 2, 3 };

	/* Teste 4: overflow - 4 * 10^9 com int estoura para -294967296;   */
	/* uma solucao sem long long ENCONTRARIA esta quadrupla e falharia */
	int		t4[] = { 1000000000, 1000000000, 1000000000, 1000000000 };

	/* Teste 5: negativos e simetrias - 8 quadruplas */
	int		t5[] = { -3, -2, -1, 0, 0, 1, 2, 3 };
	int		e5[][4] = { { -3, -2, 2, 3 }, { -3, -1, 1, 3 }, { -3, 0, 0, 3 },
						{ -3, 0, 1, 2 }, { -2, -1, 0, 3 }, { -2, -1, 1, 2 },
						{ -2, 0, 0, 2 }, { -1, 0, 0, 1 } };

	/* Teste 6: exatamente 4 elementos que somam o alvo */
	int		t6[] = { 1, 2, 3, 4 };
	int		e6[][4] = { { 1, 2, 3, 4 } };

	/* Teste 7: exatamente 4 elementos que NAO somam o alvo */
	int		t7[] = { 1, 2, 3, 4 };

	/* Teste 8: todos iguais a zero - deve sair UMA quadrupla, nao varias */
	int		t8[] = { 0, 0, 0, 0, 0, 0 };
	int		e8[][4] = { { 0, 0, 0, 0 } };

	/* Teste 9: todos negativos com alvo negativo */
	int		t9[] = { -5, -4, -3, -2, -1 };
	int		e9[][4] = { { -4, -3, -2, -1 } };

	/* Teste 10: duplicatas espalhadas e desordenadas */
	int		t10[] = { 4, 3, 3, 4, 4, 2, 1, 2, 1, 1 };
	int		e10[][4] = { { 1, 1, 3, 4 }, { 1, 2, 2, 4 }, { 1, 2, 3, 3 } };

	passou = 0;
	passou += RodarTeste(  1, t1,  6, 0,          e1,   3 );
	passou += RodarTeste(  2, t2,  5, 8,          e2,   1 );
	passou += RodarTeste(  3, t3,  3, 6,          NULL, 0 );
	passou += RodarTeste(  4, t4,  4, -294967296, NULL, 0 );
	passou += RodarTeste(  5, t5,  8, 0,          e5,   8 );
	passou += RodarTeste(  6, t6,  4, 10,         e6,   1 );
	passou += RodarTeste(  7, t7,  4, 11,         NULL, 0 );
	passou += RodarTeste(  8, t8,  6, 0,          e8,   1 );
	passou += RodarTeste(  9, t9,  5, -10,        e9,   1 );
	passou += RodarTeste( 10, t10, 10, 9,         e10,  3 );

	printf( "Resultado final: %d/10 testes passaram\n", passou );

    _CrtDumpMemoryLeaks();
	return passou == 10 ? 0 : 1;
}