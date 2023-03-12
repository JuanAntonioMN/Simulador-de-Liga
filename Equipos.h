#ifndef SOMETHING_H
#define SOMETHING_H
enum Bandera{VICTORIA=3,EMPATE=2,DERROTA=1};
class Equipos{
	private: 
	//Struct para guardar la informacion de cada equipo
	 struct Registros{	
	 	char nombre[30];
	 	int puntos;
	 	int victorias;
	 	int derrotas;
	 	int empates;
	 	int pjugados;
	 	int goles;
	 };
	 
	 //Struct para guardar los partidos de cada equipo
	 struct Partidos{
	 	char equipoA[30];
	 	char equipoB[30];
	 	int golesA;
	 	int golesB;
	 };
	 
	 Registros *equipos; //Puntero de struct
	 Partidos **juego_equipos; //Puntero de Puntero de struct 
	 bool **partidos; //Puntero de Punteros boleanos
	 int num_equipos; //cantidad de equipos
	 int opcion;
	 
	public:
		
		Equipos( ); //contructor por defecto ( 0 )
		void Menu(); //Menu de opciones de nuestra clase ( 1 )
		void Pedir_Memoria( ); // Metodo para reservar memoria ( 2 )
		void Set_NumEquipos( int ); // Metodo para setear el numero de equipos ( 3 )
		int Get_NumEquipos( ); //Metodo para obtener el numero de equipos ( 4 )
		void Llenar( ); //Metodo para llenar el nombre de los equipos	( 5 )
		void Simular_Partidos( ); //Metodo para crear la simulacion de partidos	 ( 6 )
		void Modificar_Datos( int , int , int ); //Metodo para modificar la informacion del struct Registros bandera, goles y posicion a modificar ( 7 )	
		void Guardar_Equipos( char* , int , char* , int , int , int ); //Metodo que guarda la informacion de los enfrentamientos de cada equipo nombre, goles y posicion a modificar ( 8 )
		void Ordenar_Equipos( ); //Metodo para ordenar el struct de Registros ( 9 )
		void Mostrar( ); //Metodo para mostrar la informacion del struct de Registros ( 10 )
		void Mostrar_Partidos( ); // Metodo que muestra a los Partidos de cada equipo ( 11 )
		void gotoxy( int , int ); //Metodo para posicionar cursor ( 12 )
		~Equipos(); //Destructor para liberar memoria ( 13 )
		
};

#endif