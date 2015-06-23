#include <stdio.h>
//#include <string.h>

using namespace std;

int arrTablero[50][50];
//int arrTableroCount[19][19][2];
int dimension;

//int currFila = 0;
//int currColumna = 0;
int currAmazonas = 0;
//int initColumna = 0;
//int cantSoluciones = 0;

void funcMapeo();
void funcPedirPieza();
int funcAgregarPieza(int fila, int columna);
void funcRemoverPieza(int fila, int columna);
int funcVerificarPieza(int fila, int columna);
void EncontrarColumnaSegura(int fila);

int funcReinaEnFila(int fila);
//int funcReinaEnColumna(int columna);

//long funcFactorial(int numero);

//int funcAlgoritmo();

// BACKTRACKING: n! soluciones

int debug;
int main()
{	
	debug = 0;
	printf("Inserta la dimension: ");
	scanf("%d", &dimension);
	
	/*while (dimension <= 5 || dimension >= 50)
	{
		printf("\nInserta la dimension [6-49]: ");
		scanf("%d", &dimension);
	}*/
	
	if(dimension < 4 || dimension > 50)
		return main();
	
	for(int i = 0; i < 50; i ++)
	{
		for(int j = 0; j < 50; j ++)
		{
			arrTablero[i][j] = -1;
		}
	}	
	for(int i = 0; i < dimension; i ++)
	{
		for(int j = 0; j < dimension; j ++)
		{
			arrTablero[i][j] = 0;
		}
	}
		
	currAmazonas = 0;	
	
	funcMapeo();
	funcPedirPieza();
	//EncontrarColumnaSegura(0);
    return 1;
}

void funcMapeo()
{
	printf("\n\nACTUAL MATRIZ:\n");	

	for(int i = 0; i < dimension; i ++)
	{
		for(int j = 0; j < dimension; j ++)
		{
			if(arrTablero[i][j] == 0)
			{
				printf("O ");
			}
			else if(arrTablero[i][j] == 1)
			{
				printf("A ");
			}
			else if(arrTablero[i][j] >= 2) 
			{
				printf("x ");
			}
			else
				printf("? ");
		}
		printf("\t(%d;%d)\n",i,funcReinaEnFila(i));
	}
	printf("\n\n");
	funcPedirPieza();
	return;
}

void funcPedirPieza()
{
	int coordenada[2], remove;
	printf("Ingrese coordenadas de la amazona: ");
	scanf("%d %d %d", &coordenada[0], &coordenada[1], &remove);
	
	while ((coordenada[0] >= dimension || coordenada[0] < -1) || (coordenada[1] >= dimension || coordenada[1] < -1))
	{
		printf("\nIngrese coordenadas de la amazona: ");
		scanf("%d %d %d", &coordenada[0], &coordenada[1], &remove);
	}
	
	if(coordenada[0] == -1 && coordenada[1] == -1)
	{//clear
		main();
	}
	
	if(remove == 1)
	{
		funcRemoverPieza(coordenada[0], coordenada[1]);
	}
	else	
		funcAgregarPieza(coordenada[0], coordenada[1]);
		
	return;
}


int funcReinaEnFila(int fila)
{//Retorna el valor de la columna en el que se encuntra la reina en la fila
	if(fila < 0 || fila > 50)
		return -1;
	
	for(int i = 0; i < dimension; i ++)
	{
		if(arrTablero[fila][i] == 1)
			return i;
	}
	
	return -1;
}

/*int funcReinaEnColumna(int columna)
{//Retorna el valor de la fila en el que se encuentra la reina en la columna
	
	for(int i = 0; i < dimension; i ++)
	{
		if(arrTablero[i][columna] == 1)
			return i;
	}
	
	return -1;
}*/

void EncontrarColumnaSegura(int fila)
{	
	if(fila < 0 || fila > dimension)
		return;
	
	if(fila == dimension)
	{
		if(currAmazonas == dimension)
		{
			printf("SOLUCION PARA %dx%d (%d reinas encontradas en %d recursiones)", dimension, dimension, currAmazonas, debug);
			funcMapeo();
			main();
			return;
		}
		printf("No se encontro solucion para %dx%d (%d recursiones efectuadas)", dimension, dimension, debug);
		funcMapeo();
		main();
		return;
	}
	
	for(int j = 0; j < dimension; j ++)
	{
		if(arrTablero[fila][j] == 0)
		{
			funcAgregarPieza(fila, j);
			EncontrarColumnaSegura(fila + 1);
			funcRemoverPieza(fila, j);
			debug ++;
			
			if(j == dimension-1 && fila == 0) //Esta por la ultima columna en la primera fila, ya intento todas las posibilidades, eso quiere decir que no hay solucion.
			{
				EncontrarColumnaSegura(dimension);
				break;
			}
		}
	}
	return;
}

/*int funcAlgoritmo()
{
	if(currFila < 0)
	{
		currFila = 0;
		initColumna ++;
	}
	
	for(int i = initColumna; i < dimension; i ++)
	{
		if(arrTablero[currFila][i] == 0)
		{
			if(funcAgregarPieza(currFila, i) == 1)
			{
				currColumna = i;
			}
			else continue;
		}
	}
	if(funcReinaEnFila(currFila) == -1)
	{//no se pudo agregar la reina en toda la fila, hay que volver para atras
		//hay que remover la pieza de la fila anterior y moverla a la proxima columna habilitada.
		int backtrack = funcReinaEnFila(currFila-1);
		
		funcRemoverPieza(currFila-1, backtrack);
		initColumna ++;
		currFila --;
		funcAlgoritmo();
		return 0;
	}
	currFila ++;
	
	
	
	if(initColumna == dimension)
	{
		main();
		return 1;
	}	
	if(currFila == dimension)
	{
		main();
		return 1;
	}
	
	
	return funcAlgoritmo();
}*/

/*int funcAlgoritmo()
{	
	funcAgregarPieza(currFila, currColumna);
	
	//guardar los utilizados en cada fila y columna
	arrTableroCount[currFila][currColumna][0] = currFila;
	arrTableroCount[currFila][currColumna][1] = currColumna;
	
	if(currAmazonas-1 != currFila)
	{
		//Por cada iteracion (cada vez que se analiza una fila), deberia haber una reina, si no la hay, significa que no se pudo seguir con la rama actual.
		//Hay que volver atras y la ultima columna aumentarle + 1, si eso sigue fallando, hay que volver aun mas atras.	
		
		currFila --;
		funcRemoverPieza(arrTableroCount[currFila][currColumna][0], arrTableroCount[currFila][currColumna][1]);
		currColumna ++;
	}
	
	//encontrar el siguiente vacio en la proxima fila
	currFila ++;
	
	if(currColumna == dimension)
	{//limite encontrado
		for(int j = 0; j < dimension; j ++)
		{
			if(arrTableroCount[currFila][j][1] == 0)
			{//primer valor de la columna que no se uso
				currColumna = j;
				arrTableroCount[currFila][j][0] = currFila;
				arrTableroCount[currFila][j][1] = currColumna;
				break;
			}
		}	
	}
	
	if(currFila == dimension)
	{//Ya se analizaron todas las filas posibles
		if(currAmazonas == dimension)
		{//Solucion encontrada
			main();
			return 1;
		}
	}	
	
	
	for(int j = currColumna; j < dimension; j ++)
	{
		if(arrTablero[currFila][j] == 0)
		{
			currColumna = j;
			break;
		}
	}
	
	
	
	return funcAlgoritmo();
}*/

// verifica si una pieza nueva va a ser comida por otra o no
int funcVerificarPieza(int fila, int columna)
{
	//printf("\nfuncVerificarPieza(%d, %d)\n", fila, columna);
	
	if(fila > 50 || columna > 50 || fila < 0 || columna < 0)
		return 0;
	
	if(arrTablero[fila][columna] >= 2 || arrTablero[fila][columna] == -1)
		return 0;
	
	return 1;
}

// remueve una pieza
void funcRemoverPieza(int fila, int columna)
{
	//printf("\nfuncRemoverPieza(%d, %d)\n", fila, columna);
	
	if(fila > 50 || columna > 50 || fila < 0 || columna < 0)
		return;
	
	if(arrTablero[fila][columna] != 1)
	{
		//funcMapeo();
		return;
	}
			
	arrTablero[fila][columna] = 0;
	currAmazonas --;
	
	for(int i = 0; i < dimension; i ++)
	{				
		//Fila y columna
		if(arrTablero[fila][i] != 1)
			if(arrTablero[fila][i] > 2) 
				arrTablero[fila][i] --;
			else
				arrTablero[fila][i] = 0;
			
		if(arrTablero[i][columna] != 1)
			if(arrTablero[i][columna] > 2) 
				arrTablero[i][columna] --;
			else
				arrTablero[i][columna] = 0;
			
		//diagonales	
		if(i+columna < dimension && i+fila < dimension)
			if(arrTablero[i+fila][i+columna] != 1)
				if(arrTablero[i+fila][i+columna] > 2) 
					arrTablero[i+fila][i+columna] --;	
				else
					arrTablero[i+fila][i+columna] = 0;	
		
		if(fila-i >= 0 && i+columna < dimension)
			if(arrTablero[fila-i][i+columna] != 1)
				if(arrTablero[fila-i][i+columna] > 2) 
					arrTablero[fila-i][i+columna] --;	
				else
					arrTablero[fila-i][i+columna] = 0;	
		
		if(columna-i >= 0 && fila+i < dimension)
			if(arrTablero[fila+i][columna-i] != 1)
				if(arrTablero[fila+i][columna-i] > 2)
					arrTablero[fila+i][columna-i] --;
				else
					arrTablero[fila+i][columna-i] = 0;	
		
		if(fila-i >= 0 && columna-i >= 0)
			if(arrTablero[fila-i][columna-i] != 1)
				if(arrTablero[fila-i][columna-i] > 2)
					arrTablero[fila-i][columna-i] --;
				else
					arrTablero[fila-i][columna-i] = 0;	
			
		//caballo L
		if(fila + 2 < dimension && columna + 1 < dimension)
			if(arrTablero[fila+2][columna+1] != 1) 
				if(arrTablero[fila+2][columna+1] > 2) 
					arrTablero[fila+2][columna+1] --;
				else
					arrTablero[fila+2][columna+1] = 0;
				
		if(columna - 1 >= 0 && fila + 2 < dimension) 
			if(arrTablero[fila+2][columna-1] != 1) 
				if(arrTablero[fila+2][columna-1] > 2) 
					arrTablero[fila+2][columna-1] --;	
				else
					arrTablero[fila+2][columna-1] = 0;	
			
		if(fila - 2 >= 0 && columna + 1 < dimension)	
			if(arrTablero[fila-2][columna+1] != 1) 
				if(arrTablero[fila-2][columna+1] > 2) 
					arrTablero[fila-2][columna+1] --;
				else
					arrTablero[fila-2][columna+1] = 0;
		
		if(fila - 2 >= 0 && columna - 1 >= 0)
			if(arrTablero[fila-2][columna-1] != 1)
				if(arrTablero[fila-2][columna-1] > 2) 
					arrTablero[fila-2][columna-1] --;
				else
					arrTablero[fila-2][columna-1] = 0;
				
				
		//caballo L acostada
		if(fila + 1 < dimension && columna + 2 < dimension)
			if(arrTablero[fila+1][columna+2] != 1) 
				if(arrTablero[fila+1][columna+2] > 2) 
					arrTablero[fila+1][columna+2] --;
				else
					arrTablero[fila+1][columna+2] = 0;	
				
		if(columna - 2 >= 0 && fila + 1 < dimension) 
			if(arrTablero[fila+1][columna-2] != 1)
				if(arrTablero[fila+1][columna-2] > 2) 
					arrTablero[fila+1][columna-2] --;
				else
					arrTablero[fila+1][columna-2] = 0;
					
			
		if(fila - 1 >= 0 && columna + 2 < dimension)	
			if(arrTablero[fila-1][columna+2] != 1)
				if(arrTablero[fila-1][columna+2] > 2) 
					arrTablero[fila-1][columna+2] --;
				else
					arrTablero[fila-1][columna+2] = 0;
					
		
		if(fila - 1 >= 0 && columna - 2 >= 0)
			if(arrTablero[fila-1][columna-2] != 1)
				if(arrTablero[fila-1][columna-2] > 2)
					arrTablero[fila-1][columna-2] --;
				else
					arrTablero[fila-1][columna-2] = 0;
		
	}
	
	funcMapeo();
	return;
}

// agrega permanentemente una pieza, si no es comida
int funcAgregarPieza(int fila, int columna)
{
	//printf("\nfuncAgregarPieza(%d, %d)\n", fila, columna);
	
	if(fila > 50 || columna > 50 || fila < 0 || columna < 0)
		return 0;
	
	if(funcVerificarPieza(fila, columna) == 0)
	{
		printf("\nError: la pieza va a ser comida en las coordenadas (%d,%d).\n", fila, columna);
		funcMapeo();
		return 0;
	}	
	
	arrTablero[fila][columna] = 1;
	currAmazonas ++;
	
	for(int i = 0; i < dimension; i ++)
	{				
		//Fila y columna
		if(arrTablero[fila][i] != 1)
			if(arrTablero[fila][i] >= 2) 
				arrTablero[fila][i] ++;
			else
				arrTablero[fila][i] = 2;
			
		if(arrTablero[i][columna] != 1)
			if(arrTablero[i][columna] >= 2) 
				arrTablero[i][columna] ++;
			else
				arrTablero[i][columna] = 2;
			
		//diagonales	
		if(i+columna < dimension && i+fila < dimension)
			if(arrTablero[i+fila][i+columna] != 1)
				if(arrTablero[i+fila][i+columna] >= 2) 
					arrTablero[i+fila][i+columna] ++;	
				else
					arrTablero[i+fila][i+columna] = 2;	
		
		if(fila-i >= 0 && i+columna < dimension)
			if(arrTablero[fila-i][i+columna] != 1)
				if(arrTablero[fila-i][i+columna] >= 2) 
					arrTablero[fila-i][i+columna] ++;	
				else
					arrTablero[fila-i][i+columna] = 2;
		
		if(columna-i >= 0 && fila+i < dimension)
			if(arrTablero[fila+i][columna-i] != 1)
				if(arrTablero[fila+i][columna-i] >= 2)
					arrTablero[fila+i][columna-i]  ++;
				else
					arrTablero[fila+i][columna-i] = 2;	
		
		if(fila-i >= 0 && columna-i >= 0)
			if(arrTablero[fila-i][columna-i] != 1)
				if(arrTablero[fila-i][columna-i] >= 2)
					arrTablero[fila-i][columna-i] ++;
				else
					arrTablero[fila-i][columna-i] = 2;
			
		//caballo L
		if(fila + 2 < dimension && columna + 1 < dimension)
			if(arrTablero[fila+2][columna+1] != 1) 
				if(arrTablero[fila+2][columna+1] >= 2) 
					arrTablero[fila+2][columna+1] ++;
				else
					arrTablero[fila+2][columna+1] = 2;
				
		if(columna - 1 >= 0 && fila + 2 < dimension) 
			if(arrTablero[fila+2][columna-1] != 1) 
				if(arrTablero[fila+2][columna-1] >= 2) 
					arrTablero[fila+2][columna-1]  ++;	
				else
					arrTablero[fila+2][columna-1] = 2;	
			
		if(fila - 2 >= 0 && columna + 1 < dimension)	
			if(arrTablero[fila-2][columna+1] != 1) 
				if(arrTablero[fila-2][columna+1] >= 2) 
					arrTablero[fila-2][columna+1] ++;
				else
					arrTablero[fila-2][columna+1] = 2;
		
		if(fila - 2 >= 0 && columna - 1 >= 0)
			if(arrTablero[fila-2][columna-1] != 1)
				if(arrTablero[fila-2][columna-1] >= 2) 
					arrTablero[fila-2][columna-1] ++;
				else
					arrTablero[fila-2][columna-1] = 2;
				
				
		//caballo L acostada
		if(fila + 1 < dimension && columna + 2 < dimension)
			if(arrTablero[fila+1][columna+2] != 1) 
				if(arrTablero[fila+1][columna+2] >= 2) 
					arrTablero[fila+1][columna+2] ++;
				else
					arrTablero[fila+1][columna+2] = 2;	
				
		if(columna - 2 >= 0 && fila + 1 < dimension) 
			if(arrTablero[fila+1][columna-2] != 1)
				if(arrTablero[fila+1][columna-2] >= 2) 
					arrTablero[fila+1][columna-2] ++;
				else
					arrTablero[fila+1][columna-2] = 2;
					
			
		if(fila - 1 >= 0 && columna + 2 < dimension)	
			if(arrTablero[fila-1][columna+2] != 1) 
				if(arrTablero[fila-1][columna+2] >= 2) 
					arrTablero[fila-1][columna+2] ++;
				else
					arrTablero[fila-1][columna+2] = 2;
					
		
		if(fila - 1 >= 0 && columna - 2 >= 0)
			if(arrTablero[fila-1][columna-2] != 1)
				if(arrTablero[fila-1][columna-2] >= 2)
					arrTablero[fila-1][columna-2] ++;
				else
					arrTablero[fila-1][columna-2] = 2;
		
	}
	
	funcMapeo();
	return 1;
}

/*long funcFactorial(int numero)
{
	long ffactorial;
	if(numero == 1 || numero == 0)
		ffactorial = 1;
	else
		ffactorial = numero * funcFactorial(numero - 1);
		
	return ffactorial;
}*/
