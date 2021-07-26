#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define MAX 20
#define LIM 50


// operacions basicas de datos simples

int leeEntero(char msje[], int min, int max,char msje1[])
{
	int num;

   do{
   	printf("%s", msje);
      scanf("%d", &num);
      if(num<min || num>max){
      	printf("*%s\n", msje1);
      }
   }while(!(num>=min && num<=max));

  	return num;
}

float leeReal(char msje[], float min, float max,char msje1[])
{ float num;
  do{
     printf("%s", msje);
     scanf("%f", &num);
     if(num<=min && num>=max){
      	printf("%s", msje1);
      }
  }while(!(num>=min && num<=max));
  return num;
}




//operaciones de vector enteros

void iniciaVE(int V[], int m)
{
 for(int i=0; i<m; i++)
 	V[i]=0;
}



//operaciones de vector reales
void iniciaVR(float V[], int m)
{
 for(int i=0; i<m; i++)
 	V[i]=0.0;
}


////operaciones de Tablas

void iniciaTabla(char T[][LIM], int m)
{
 for(int i=0; i<m; i++)
 	T[i][0]=NULL;
}

int validaTabla(char msje[], char T[][LIM], int tam,char msje1[])
{
 int opc;
 for(int i=0; i<tam; i++)
    printf("\n%d: %s",i+1, T[i]);

  opc=leeEntero(msje,1,tam,msje1);
  fflush(stdin);
  return opc;

}

 char continuar (char msje[])
{
	char rpta;
   do{
   	printf("\n%s", msje);
      fflush(stdin);            
      scanf("%c",&rpta);
      rpta = toupper(rpta);
   }while(!(rpta=='S' || rpta== 'N'));
   return rpta;
}

//Struct fecha

struct Fecha
{
	int Dia;
	int Mes;
	int Anio;
};

//inicia fecha

void iniciaFecha(Fecha &F)
{
	F.Dia=0;
	F.Mes=0;
	F.Anio=0;
}

//lee fecha

void leeFecha(char msje[],Fecha &F)
{
   printf("\n%s",msje);
	do
	{
		cout<<"\n\tDia [dd]:    ";
		cin>>F.Dia;
	}while(!(F.Dia>0 && F.Dia<=31));
	do
	{
		cout<<"\tMes [mm]:    ";
		cin>>F.Mes;
	}while(!(F.Mes>0 && F.Mes<=12));
	do
	{
		cout<<"\tA¤o [aaaa]:  ";
		cin>>F.Anio;
	}while(!(F.Anio>1900 && F.Anio<=2020));
}

//mostrar fecha

void mostrarFecha(char msje[],Fecha &F)
{
   printf("\%s",msje);
	cout<<"  "<<F.Dia;
	cout<<" / "<<F.Mes;
	cout<<" / "<<F.Anio;
}

//comparar fecha

int comparaFechas(Fecha &F,Fecha &FI)
{
	if(F.Anio>FI.Anio)
		return 1;
	else
	    if(F.Anio<FI.Anio)
	      return -1;
	    else
	      if(F.Mes>FI.Mes)
				return 1;
	      else
				if(F.Mes<FI.Mes)
		  			return -1;
				else
		   		if(F.Dia>FI.Dia)
		     			return 1;
               else
		     			if(F.Dia<FI.Dia)
		       			return -1;
		     			else
		       			return 0;
}

void copiaFecha(Fecha &F,Fecha &FI)
{
	F.Anio=FI.Anio;
   F.Mes=FI.Mes;
   F.Dia=FI.Dia;
}

//Adicionales}
char leeSexo(char msje[])
{
	char rpta;

   cout << " F : Femenino" <<endl;
   cout << " M : Masculinoino" <<endl;
   do{
   	printf("%s", msje);
      fflush(stdin);
      scanf("%c",&rpta);
      rpta= toupper(rpta);
   }while(!(rpta=='F' || rpta== 'M'));
   return rpta;
}

char leeCaracter(char msje1[],char msje2[],char A,char B,char msje[]){
	char rpta;

   cout << msje1 <<endl;
   cout << msje2 <<endl;
   do{
   	printf("%s", msje);
      fflush(stdin);
      scanf("%c",&rpta);
      rpta= toupper(rpta);
   }while(!(rpta==A || rpta== B));

   return rpta;
}

