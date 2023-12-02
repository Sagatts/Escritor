#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct ColaEstado{
	int Estado;
	ColaEstado *sgte;	
}ColaEstado;

typedef struct ArbolSimbolos{
	ArbolSimbolos *izquierda;
	int Simbolo;
	ArbolSimbolos *derecha;
}ArbolSimbolos;

typedef struct ListasOrden{
	ListasOrden *ante;
	int numero;
	ListasOrden *sgte;
}ListaOrden;

typedef struct Principal{
	Principal *ante;
	ColaEstado *inicio;
	ColaEstado *final;
	ArbolSimbolos *raiz;
	ListaOrden *lista1;
	ListaOrden *lista2;
	ListaOrden *lista3;
	Principal *sgte;
}Principal;


//Lista
void crearlista(Principal *&p);
int listavacia(Principal *&p);
void crear_estructuras(Principal *&p);
//Listas pre in post
void crearlistaOrden(ListasOrden *&p);
int listavaciaOrden(ListasOrden *&p);
int insertarlistaOrden(ListasOrden *&p,int v);
void mostrar_listaOrden(ListaOrden *&p);
//Cola
void crearcola(ColaEstado *&i,ColaEstado *&f);
int colavacia(ColaEstado *&i,ColaEstado *&f);
int insertarcola(ColaEstado *&i,ColaEstado *&f,int d);
void mostrar_estado(ColaEstado *&i,ColaEstado *&f);
int eliminar(ColaEstado *&i,ColaEstado *&f,int *v);
//Arbol
void creararbol(ArbolSimbolos *&R);
void insertararbol(ArbolSimbolos *&R,int num);

void pre_orden(ArbolSimbolos *&R,ListaOrden *&L);
void in_orden(ArbolSimbolos *&R,ListaOrden *&L);
void post_orden(ArbolSimbolos *&R,ListaOrden *&L);

//Listas
void crearlista(Principal *&p)
{
	p=NULL;
}
int listavacia(Principal *&p)
{
	if(p==NULL)
		return 1;
	else
		return 0;
}
//Listas de pre - in - post orden
void crearlistaOrden(ListaOrden *&p)
{
	p=NULL;
}
int listavaciaOrden(ListaOrden *&p)
{
	if(p==NULL)
		return 1;
	else
		return 0;
}
int insertarlistaOrden(ListaOrden *&p,int v)
{
	ListaOrden *aux;
	aux=(ListaOrden*)malloc(sizeof(ListaOrden));
	if(aux==NULL)
		return 0;
	else{
		aux->ante=aux->sgte=NULL;
		aux->numero=v;
		if(listavaciaOrden(p))
			p=aux;
		else{
			for(;p->sgte!=NULL;p=p->sgte);
				p->sgte=aux;
				aux->ante=p;
			for(;p->ante!=NULL;p=p->ante);
		}
		return 1;
	}
}
void mostrar_listaOrden(ListaOrden *&p)
{
	ListaOrden *q=p;
	for(q=p;q!=NULL;q=q->sgte){
		printf("%d-",q->numero);
	}
}
//Cola
void crearcola(ColaEstado *&i,ColaEstado *&f)
{
	i=f=NULL;
}
int colavacia(ColaEstado *&i,ColaEstado *&f)
{
	if(i==NULL && f==NULL)
	   	return 1;
	else
		return 0;
}
int insertarcola(ColaEstado *&i,ColaEstado *&f,int d)
{
	ColaEstado *aux;
	aux=(ColaEstado*)malloc(sizeof(ColaEstado));
	if(aux==NULL)
		return 0;
	else
	{
		aux->Estado=d;
		aux->sgte=NULL;
		if(colavacia(i,f))
		    i=f=aux;
		else
		{
			f->sgte=aux;
			f=aux;
		}
		return 1;
	}	
}
void mostrar_estado(ColaEstado *&i,ColaEstado *&f)
{
	ColaEstado *c1,*f1;
	crearcola(c1,f1);
	int d;
	while(!colavacia(i,f)){
		if(eliminar(i,f,&d)){
			printf("%d-",d);
			
		}
		if(insertarcola(c1,f1,d)){
			printf("");
		}
	}
	while(!colavacia(c1,f1)){
		if(eliminar(c1,f1,&d)){
			if(insertarcola(i,f,d)){
				printf("");
			}
		}
	}
	free(c1);
	free(f1);	
}
int eliminar(ColaEstado *&i,ColaEstado *&f,int *v)
{
	ColaEstado *aux;
	if(colavacia(i,f))
	    return 0;
	else
	{
		aux=i;
		*v=aux->Estado;
		if(i->sgte==NULL)
			i=f=NULL;
		else
		{
			i=i->sgte;
			aux->sgte=NULL;
		}
		return 1;
		free(aux);
	}
}
//Arbol
void creararbol(ArbolSimbolos *&R)
{
	R=NULL;
}
void insertararbol(ArbolSimbolos *&R,int num)
{
	if(R==NULL){
		R=(ArbolSimbolos*)malloc(sizeof(ArbolSimbolos));
		R->derecha=R->izquierda=NULL;
		R->Simbolo=num;
	}
	else{
		if(R->Simbolo<=num){
			insertararbol(R->derecha,num);
		}
		else
			insertararbol(R->izquierda,num);
	} 
}
void pre_orden(ArbolSimbolos *&R,ListaOrden *&L)
{
	if(R!=NULL){
		insertarlistaOrden(L,R->Simbolo);
		pre_orden(R->izquierda,L);
		pre_orden(R->derecha,L);
	}
}
void in_orden(ArbolSimbolos *&R,ListaOrden *&L)
{
	if(R!=NULL){
		in_orden(R->izquierda,L);
		insertarlistaOrden(L,R->Simbolo);
		in_orden(R->derecha,L);
	}
}
void post_orden(ArbolSimbolos *&R,ListaOrden *&L)
{
	if(R!=NULL){
		post_orden(R->izquierda,L);
		post_orden(R->derecha,L);
		insertarlistaOrden(L,R->Simbolo);
	}
}
//Generar las estructuras
void crear_estructuras(Principal *&p)
{
	crearcola(p->inicio,p->final);
    creararbol(p->raiz);
    crearlistaOrden(p->lista1);
    crearlistaOrden(p->lista2);
    crearlistaOrden(p->lista3);
}

int main(){
	Principal *estructura;
	crearlista(estructura);
	estructura = (Principal*)malloc(sizeof(Principal));
    estructura->inicio = (ColaEstado*)malloc(sizeof(ColaEstado));
    estructura->final = (ColaEstado*)malloc(sizeof(ColaEstado));
    estructura->raiz = (ArbolSimbolos*)malloc(sizeof(ArbolSimbolos));
    estructura->lista1 = (ListaOrden*)malloc(sizeof(ListaOrden));
    estructura->lista2 = (ListaOrden*)malloc(sizeof(ListaOrden));
    estructura->lista3 = (ListaOrden*)malloc(sizeof(ListaOrden));
    
    crear_estructuras(estructura);
	
	int i,op,cont1=0,cont2=0;
	char caracter1,caracter2,caracter3;
	do{
		do{
			printf("Que desea hacer?\n");
			printf("1. Generar un simbolo\n");
			printf("2. Finalizar el programa y mostrar los titulos\n");
			while(scanf("%d",&op)!=1){
				printf("Error, Ingrese un numero valido\n");
				while(getchar()!='\n');
			}
		}while(op<1 or op>2);
		if (op==1){
			printf("Ingrese el primer caracter, solo se tomara el primer caracter ingresado (cuenta el espacio y el enter)\n");
			while(getchar() != '\n');
			caracter1=getchar();
			
			printf("Ingrese el segundo caracter, solo se tomara el primer caracter ingresado (cuenta el espacio y el enter)\n");
			while(getchar() != '\n');
			caracter2=getchar();
			
			printf("Ingrese el tercer caracter, solo se tomara el primer caracter ingresado (cuenta el espacio y el enter)\n");
			while(getchar() != '\n');
			caracter3=getchar();
			
			printf("Caracteres ingresado: %c %c %c \n",caracter1,caracter2,caracter3);
			if (caracter1 >= '0' && caracter1 <= '9' && caracter2 >= '0' && caracter2 <= '9' && caracter3 >= '0' && caracter3 <= '9') {
		        char caracteres[4]={caracter3,caracter2,caracter1,'\0'};
		        int simbolo=atoi(caracteres);
		        
		        insertarcola(estructura->inicio,estructura->final,1);
		        insertararbol(estructura->raiz,simbolo);
		        cont1++;
		        printf("Simbolo generado: %d \n",simbolo);
		        while(getchar() != '\n');
			}
    		else{
    			insertarcola(estructura->inicio,estructura->final,0);
    			cont2++;
    			printf("No se genero el simbolo por que unos de los caracteres es distinto a un numero\n");
    			while(getchar() != '\n');
    		}
    	}
    	if(cont1==20)
		    break;
	}while(op!=2);
	printf("Estados del escritor 0=dormido 1=despierto\n");
	mostrar_estado(estructura->inicio,estructura->final);
	printf("\n");
	printf("Cantidad de veces que desperto: %d\n",cont1);
	printf("Cantidad de veces que durmio: %d\n",cont2);
	printf("\nPrimer titulo generado (pre-orden)\n");
	pre_orden(estructura->raiz,estructura->lista1);
	mostrar_listaOrden(estructura->lista1);
	printf("\nSegundo titulo generado (in-orden)\n");
	in_orden(estructura->raiz,estructura->lista2);
	mostrar_listaOrden(estructura->lista2);
	printf("\nTercer titulo generado (post-orden)\n");
	post_orden(estructura->raiz,estructura->lista3);
	mostrar_listaOrden(estructura->lista3);
	if(cont1>cont2){
		printf("\nLos tres titulos son validos para el libro\n");
	}
	else{
		printf("\nNinguno de los tres titulos son validos para el libro\n");
	}
}
