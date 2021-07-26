/*
Lista de detalles[dianmica]: nombre,valor(cadena)

Reporte:
-Resumen de cantidad de equipos por tipo.
-Mostrar los equipos registrados segun un tipo definido.
-Dado el codigo de un equipo mostrar los detalles registrados.
*/

#include "basicas.cpp"

#define MAXDNI 9
#define MAXCOD 7
#define DELTA 3

char *tiposEquipo[]={"Laptop","PC","Proyector","SmartTV"};

class Detalle{
  private:
 	char nombre[MAX];
   	char valor[MAX];

  public:
 	Detalle()
	{
   		this->nombre[0] = NULL;
      	this->valor[0] = NULL;
   	}

   	void leer()
	{
   		cout << "Nombre : "; cin >> this->nombre;
      	cout << "Valor : "; cin >> this->valor;
   	}

   	void getNombre(char *nombre)
	{
   		strcpy(nombre,this->nombre);
   	}

   	void getValor(char *valor)
	{
   		strcpy(valor,this->valor);
   	}
};

class ListaDetalles{
  private:
 	int n;
   	int max;
   	Detalle **data;

  public:
 	ListaDetalles()
	{
   		this->n = 0;
      	this->max = 0;
      	this->data = NULL;
   	}

   	~ListaDetalles()
	{
   		if(this->max > 0)
		{
      		delete []this->data;
      	}
      	this->n = 0;
      	this->max = 0;
   	}

   	int getN()
	{
   		return this->n;
   	}

   	Detalle *get(int pos)
	{
  		return this->data[pos];
   	}

   	void agregar(Detalle *detalle)
	{
   		if(this->n == this->max)
		{
      		this->crecer();
      	}
      	this->data[this->n] = detalle;
      	this->n++;
   	}

  private:
 	void crecer()
	{
   		Detalle **aux;

      	this->max += DELTA;
      	aux = new Detalle *[this->max];

      	for(int i=0;i<this->n;i++)
		{
      		aux[i] = this->data[i];
      	}
      	if(this->n >0){
      		delete []this->data;
      	}
      	this->data = aux;
   }
};

class Equipo{
  private:
	char nombre[MAX];
   	char serie[MAX];
   	char marca[MAX];
   	int anio;
   	char codigo[MAXCOD];
   	ListaDetalles detalle;

  public:
	Equipo()
	{
   		this->nombre[0] = NULL;
      	this->serie[0] = NULL;
      	this->marca[0] = NULL;
      	this->anio = 0;
      	this->codigo[0] = NULL;
   	}

   	virtual void leer()
	{
   		cout << "Nombre : ";cin >> this->nombre;
      	cout << "Serie : ";cin >> this->serie;
      	cout << "Marca : ";cin >> this->marca;
      	this->anio = leeEntero("Anio de compra[1990-2017] : ",1990,2017,"\t* Anio no valido");
      	do
		{
   			cout << "Codigo(6 caracteres) : "; cin >> this->codigo;
   		}while(!(strlen(this->codigo) == MAXCOD-1));
   	}
   
	void getNombre(char *nombre)
	{
   		strcpy(nombre,this->nombre);
   	}

   	void getCodigo(char *codigo)
	{
   		strcpy(codigo,this->codigo);
   	}

   	virtual int getTipo() = 0;
   	//1: Laptop,2: PC,3: Proyector,4:Smart Tv

   	ListaDetalles & getListaDetalles()
	{
   		return this->detalle;
   	}
};

class NodoEquipo{
  friend class ListaEquipos;
  
  private:
	Equipo *equipo;
   	NodoEquipo *sgte;

  public:
	NodoEquipo()
	{
      this->equipo = NULL;
   		this->sgte = NULL;
   	}

   	~NodoEquipo()
	{
   		if(this->equipo != NULL)
		{
      		delete this->equipo;
      	}
   	}
};

class ListaEquipos{
  private:
	int n;
   	NodoEquipo *cab;

  public:
	ListaEquipos()
	{
   		this->n=0;
      	this->cab=NULL;
   	}

   	~ListaEquipos()
	{
   		NodoEquipo *temp;

      	while(this->cab!=NULL)
		{
      		temp=this->cab;

         	this->cab=temp->sgte;
         	delete temp;
      	}
      	this->n=0;
   	}

   	void agregar(Equipo *equipo)
	{
   		NodoEquipo *nuevo = new NodoEquipo();
      	NodoEquipo *ultimo;

      	nuevo->equipo = equipo;

      	if(this->cab == NULL)
		{
      		this->cab = nuevo;
      	}
		else
		{
      		ultimo = this->cab;
         	while(ultimo->sgte != NULL)
			{
         		ultimo = ultimo->sgte;
         	}
         	ultimo->sgte = nuevo;
      	}
      	this->n++;
   	}

   	int getN()
	{
   		return this->n;
   	}

   	Equipo *get(int pos)
	{
   		NodoEquipo *temp = this->cab;

      	if(pos>=0 && pos<this->n)
		{
      		for(int i=0;i<pos;i++)
			{
         		temp = temp->sgte;
         	}
         	return temp->equipo;
      	}
		else
		{
      		return NULL;
      	}
   	}

   	Equipo *buscarEquipoPorCodigo(char *codigoBuscar)
	{
   		NodoEquipo *temp = this->cab;

      	char codigo[MAX];

		while(temp!=NULL)
		{
      		temp->equipo->getCodigo(codigo);

         	if(strcmp(codigo,codigoBuscar)==0)
			{
         		return temp->equipo;
         	}
         	temp=temp->sgte;
      	}
      
      	return NULL;
   	}
};

class Proyector:public Equipo{
  private:
 	int lumenes;

  public:
   	Proyector()
	{
   		this->lumenes = 0;
   	}

 	virtual void leer()
	{
      	cout << endl;
   		Equipo::leer();
      	cout << "Lumenes : "; cin >> this->lumenes;
   	}

   	virtual int getTipo()
	{
   		return 3;
   	}
};

class SmartTV:public Equipo{
  private:
 	int tamanio;
   	int oled;

  public:
   	SmartTV()
	{
   		this->tamanio = 0;
      	this->oled = 0;
   	}

 	virtual void leer()
	{
      	cout << endl;
   		Equipo::leer();
      	cout << "Tamanio : "; cin >> this->tamanio;
      	cout << " 1. OLED " << endl;
      	cout << " 2. Otra tecnologia" << endl;
      	this->oled = leeEntero("Tipo : ",1,2,"\t* No valido");
   	}

   	virtual int getTipo()
	{
   		return 4;
   	}
};

class PC:public Equipo{
  private:
 	int discoDuro;
   	int ram;
   	
  public:
   	PC()
	{
   		this->discoDuro = 0;
      	this->ram = 0;
   	}

 	virtual void leer()
	{
      	cout << endl;
   		Equipo::leer();
      	this->discoDuro = leeEntero("Disco Duro - Capacidad(GB)[100-2048] : ",100,2048,"No valida");
      	this->ram = leeEntero("Tamanio de RAM(GB)[2-20] : ",2,20,"\t* No valida");
   	}

   	virtual int getTipo()
	{
   		return 2;
   	}
};

class Laptop:public Equipo{
  private:
 	char modelo[MAX];
   	int discoDuro;
   	int integrado;
   	
  public:
   	Laptop()
	{
   		this->modelo[0] = NULL;
      	this->discoDuro = 0;
      	this->integrado = 0;
   	}

 	virtual void leer()
	{
      	cout << endl;
   		Equipo::leer();
      	this->discoDuro = leeEntero("Disco Duro - Capacidad(GB)[100-2048] : ",100,2048,"\t* No valida");
      	cout << "Modelo : "; cin >> this->modelo;
      	cout << " 1. Video Integrado " << endl;
      	cout << " 2. Tarjeta de video " << endl;
      	this->integrado = leeEntero("Tipo de video : ",1,2,"\t* No valido");
   	}

   	int getIntegrado()
	{
   		return this->integrado;
   	}

   	virtual int getTipo()
	{
   		return 1;
   	}
};


ListaEquipos empresa;

// LISTA DE MENU
int leerOpcion()
{
	char *opciones[4]={"Registrar equipo","Registrar detalle","Reportes","Salir"};
   	int op;

   	for(int i=0;i<4;i++)
	{
   		cout<<(i+1)<<".- "<<opciones[i]<<endl;
   	}

	op=leeEntero(" Opcion : ",1,4,"\t* Opcion no valida");

   	return op;
}

int leerReporte()
{
	char *reportes[4]={"Resumen de cantidad de equipos por tipo",
		"Mostrar los equipos registrados segun un tipo definido",
		"Dado el codigo de un equipo mostrar los detalles registrados",
      	"Retornar"};
   	int rep;

   	for(int i=0;i<4;i++)
	{
   		cout<<(i+1)<< ".- " << reportes[i] << endl;
   	}

	rep = leeEntero(" Opcion : ",1,4,"\t* Opcion no valida");

   	return rep;
}

//EQUIPO
int leerTipoEquipo()
{
	char *tipos[4]={"Laptop","PC","Proyector","SmartTV"};
   	int tipo;

   	cout << endl;
   	for(int i=0;i<4;i++)
	{
   		cout << " " << (i+1) << ". "<< tipos[i] << endl;
   	}

   	tipo=leeEntero("Tipo de equipo : ",1,4,"\t* Tipo no valida");

   	return tipo;
}

Equipo *crearEquipo(int tipo)
{
	Equipo *e = NULL;

   	switch(tipo)
	{
   		case 1: e = new Laptop(); break;
      	case 2: e = new PC(); break;
      	case 3: e = new Proyector(); break;
      	case 4: e = new SmartTV(); break;
   	}

   	return e;
}

//REPORTES

// Reporte N01: "Resumen de cantidad de equipos por tipo"
void cantidadEquiposPorTipo()
{
   	int contador[4] = {0,0,0,0};

   	Equipo *equipo;

   	cout << endl;
   	cout<<"--- RESUMEN DE CANTIDAD DE EQUIPOS POR TIPO ---"<<endl;

   	for(int k=0;k<4;k++)
	{
   		for(int i=0;i<empresa.getN();i++)
		{
         	equipo = empresa.get(i);

         	if(equipo->getTipo() - 1 == k)
			{
         		contador[k]++;
         	}
   		}
   	}

   	for(int k=0;k<4;k++)
	{
      	cout << endl;
   		cout << (k+1) << ".- " << tiposEquipo[k] << ": " << contador[k] << endl;
   	}

   	cout << endl;
   	cout<<"-----------------------------------------------"<<endl;
	getch();
}

// Reporte N02: "Mostrar los equipos registrados segun un tipo definido"
void listaEquiposSegunTipo()
{
   	char nombreEquipo[MAX];
   	char codigo[MAXCOD];
   	int tipo;
   	int flag = 0;
   	int n = 0;

   	Equipo *equipo;

   	tipo = leerTipoEquipo();

   	cout << endl;
   	cout<<"---- LISTADO DE EQUIPO (" << tiposEquipo[tipo-1] << ") ----"<<endl;
   	cout << endl;

   	for(int i=0;i<empresa.getN();i++)
	{
   		equipo = empresa.get(i);

      	if(equipo->getTipo() == tipo)
		{
      		equipo->getNombre(nombreEquipo);
         	equipo->getCodigo(codigo);

         	flag = 1;
         	cout << "  " << (n+1) << ". " << nombreEquipo << "(" << codigo << ")" << endl;
         	n++;
   		}
   	}

   	if(flag == 0)
	{
   		cout << "\t* No se encontraron equipos del tipo solicitado*" << endl;
   	}

   	cout << endl;
   	cout<<"-----------------------------------------------------------"<<endl;
	getch();
}

// Reprote N03: "Dado el codigo de un equipo mostrar los detalles registrados"
void segunCodigoListaDetalles()
{
   	char codigo[MAXCOD];
   	char nombreDetalle[MAX];
   	char valorDetalle[MAX];
   	int tipo;
   	int flag = 0;
   	int n = 0;

   	Equipo *equipo;

   	cout << endl;
   	do
	{
   		cout << "Codigo(6 caracteres) : ";cin >> codigo;
   	}while(!(strlen(codigo)==MAXCOD-1));

   	equipo = empresa.buscarEquipoPorCodigo(codigo);

   	if(equipo != NULL )
	{
   		tipo = equipo->getTipo();

      	ListaDetalles & deta = equipo->getListaDetalles();

      	cout << endl;
   		cout<<"----- LISTADO DE DETALLES(" << tiposEquipo[tipo-1] << ") -----"<<endl;
   		cout << endl;

      	for(int i=0;i<deta.getN();i++)
		{
      		if(equipo->getTipo() == tipo)
			{
            	deta.get(i)->getNombre(nombreDetalle);
            	deta.get(i)->getValor(valorDetalle);

            	flag = 1;
            	cout << "  " <<(n+1)<< ". " << nombreDetalle << ": " << valorDetalle << endl;
            	n++;
         	}
      	}

      	if(flag == 0)
		{
   			cout << "\t* No se encontraron detalles del equipo solicitado*" << endl;
   		}

   		cout << endl;
   		cout<<"--------------------------------------------------------------"<<endl;
   	}
	else
	{
   		cout << "\t* No se encontro el equipo solicitado" << endl;
   	}
	getch();
}

//MENU

// REGISTRAR EQUIPO
void registrarEquipo()
{
	Equipo *equipo;
   	int tipo;

   	cout << endl;
   	tipo = leerTipoEquipo();
   	equipo = crearEquipo(tipo);
   	equipo->leer();
   	empresa.agregar(equipo);

   	cout << endl;
   	cout << "\t* Equipo registrado exitosamente*" << endl;
   	getch();
}

//REGISTRAR DETALLE
void registrarDetalle()
{
   	char codigo[MAXCOD];

   	Equipo *equipo;
   	Detalle *detalle = new Detalle();

   	cout << endl;
   	cout << "------- Registrar Detalle -------" << endl;
   	cout << endl;

   	do
	{
   		cout << "Codigo(6 caracteres) : "; cin >> codigo;
   	}while(!(strlen(codigo)==MAXCOD-1));

   	equipo = empresa.buscarEquipoPorCodigo(codigo);
   	ListaDetalles & deta = equipo->getListaDetalles();

   	cout << endl;
   	if(equipo != NULL )
	{
      	detalle->leer();
      	deta.agregar(detalle);

      	cout << endl;
      	cout << "\t* El detalle se registro exitosamente*" << endl;
   	}
	else
	{
   		cout << "\t* No se encontro el equipo solicitado" << endl;
   	}
   	getch();
}

void presentarReportes()
{
  	int rep;

	do
	{
      	system("cls");
  		cout<<"--------------------- REPORTES ---------------------"<<endl;
  		rep=leerReporte();
   		switch(rep)
		{
   			case 1: cantidadEquiposPorTipo(); break;
      		case 2: listaEquiposSegunTipo(); break;
      		case 3: segunCodigoListaDetalles(); break;
         	case 4: break;
   		}
  	}while(rep<4);
}

int main()
{
  	int op;

	do
	{
  		system("cls");
  		cout<<"--------- MENU ---------"<<endl;
  		op=leerOpcion();
   		switch(op)
		{
   			case 1: registrarEquipo(); break;
      		case 2: registrarDetalle(); break;
      		case 3: presentarReportes(); break;
      		case 4: break;
   		}
  	}while(op<4);
}
