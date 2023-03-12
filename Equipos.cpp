#include <iostream>
#include "Equipos.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <utility> //se usa para swap
#include <thread> //se usa par for_sleep


// ( 0 )
Equipos::Equipos( ){
	num_equipos=2;	
	Pedir_Memoria();
}

// ( 1 )
void Equipos::Menu( ){
	
	do{
		system("cls");
		gotoxy(  25, 2 );std::cout<<" M E N U   D E   O P C I O N E S ";
		gotoxy(  25, 4 );std::cout<<"1-INGRESAR EQUIPOS";
		gotoxy(  25, 6 );std::cout<<"2-MOSTRAR TABLA DE POSICIONES";
		gotoxy(  25, 8 );std::cout<<"3-MOSTRAR PARTIDOS JUEGADOS";
		gotoxy(  25, 10 );std::cout<<"4-MOSTRAR TABLA DE POSICIONES ORDENADO";
		gotoxy(  25, 12 );std::cout<<"0-SALIR";
		gotoxy(  25, 14 );std::cout<<"INGRESE UNA OPCION: ";
		gotoxy(  45, 14 );std::cin>>opcion;
		
			switch(opcion){
				
				case 1:
					
				system("cls");
				
				gotoxy(  25, 5 );std::cout<<"INGRESA EL NUMERO DE EQUIPOS: ";
				gotoxy(  55, 5 );std::cin>>num_equipos;
				
				Set_NumEquipos( num_equipos );
				
				system("cls");
				
				Pedir_Memoria( );
				
				Llenar( );
				
				std::cout<<"ESPERE UN MOMENTO PARA CONTINUAR...";
    			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    			
				break;
				
				case 2:
					
				system("cls");
				
				if(Get_NumEquipos( )>2){
					
				Simular_Partidos( );
				
				Mostrar( );
				
				}
				
				else{
					
				Mostrar( );
		
				}
				std::cout<<std::endl<<std::endl;
				std::cout<< "PRESIONA UNA TECLA PARA CONTINUAR...";
				fflush( stdin );
    			std::getchar( );
				
				break;
				
				case 3:
					
				system("cls");
				
				Mostrar_Partidos( );	
				std::cout<<std::endl<<std::endl;
				std::cout << "PRESIONA UNA TECLA PARA CONTINUAR...";
				fflush( stdin );
    			std::getchar( );
    			
				break;
				
				case 4:	
				
				system("cls");
				
				Ordenar_Equipos( );
				
				Mostrar( );
				
				std::cout<<std::endl<<std::endl;
				std::cout<< "PRESIONA UNA TECLA PARA CONTINUAR...";
				fflush( stdin );
    			std::getchar( );
    			
				break;
			}
			
		}while(opcion!=0);
}

// ( 2 )
void Equipos::Pedir_Memoria( ){
	equipos=new Registros[num_equipos];
	
	for(int i=0;i<num_equipos;i++){
		
		strcpy(equipos[i].nombre,"X");
		equipos[i].puntos=0;
		equipos[i].victorias=0;
		equipos[i].derrotas=0;
		equipos[i].empates=0;
		equipos[i].pjugados=0;
		equipos[i].goles=0;	
			
	}
	
	partidos=new bool*[num_equipos];
	
	for(int i=0;i<num_equipos;i++){
		
		partidos[i]=new bool[num_equipos];
		
	}
	
	for( int i=0;i<num_equipos;i++ ){
		
		for ( int j=0;j<num_equipos;j++ ){
			
			if( i==j ){
				partidos[i][j]=true;
			}
			else{
				partidos[i][j]=false;
			}
		}
	}
	
	juego_equipos=new Partidos*[num_equipos];
	
	for(int i=0;i<num_equipos;i++){
		
		juego_equipos[i]=new Partidos[num_equipos];
	}
	
	for(int i=0;i<num_equipos;i++ ){
		
		for (int j=0;j<num_equipos;j++){
			
			strcpy(juego_equipos[i][j].equipoA,"X");
			strcpy(juego_equipos[i][j].equipoB,"X");
			juego_equipos[i][j].golesA=0;
			juego_equipos[i][j].golesB=0;
			
		}
		
	}
	
}

//( 3 )
void Equipos::Set_NumEquipos( int num_equipos ){
	
	this->num_equipos=num_equipos;
	
}

//( 4 )
int Equipos::Get_NumEquipos( ){
	return num_equipos;
}

//( 5 )
void Equipos::Llenar( ){
	Pedir_Memoria( );
	for(int i=0;i<num_equipos;i++){
		system("cls");
		gotoxy(  25, 5 );std::cout<<"NOMBRE DEL EQUIPO ["<<i+1<<"]: ";
		fflush( stdin );
		std::cin.getline(equipos[i].nombre,30);
		
	}
}

// ( 6 )
void Equipos::Simular_Partidos( ){
	
	srand(time(NULL));
	int golesEA,golesEB;
		for(int i=0;i<(num_equipos-1);i++){
	 	
 	 		for(int j=0;j<num_equipos;j++){
 	 		
			 	 	if(partidos[i][j]!=true){
					  			 	 		
							golesEA=rand()%5;
							golesEB=rand()%5;
							
								if(golesEA>golesEB){ //VICTORIA DE ALGUN EQUIPO
								Modificar_Datos(VICTORIA,golesEA,i);
								Modificar_Datos(DERROTA,golesEA,j);
								
								}
									
								else if(golesEA==golesEB){ //EMPATE DE ALGUN EQUIPO
								Modificar_Datos(EMPATE,golesEA,i);
								Modificar_Datos(EMPATE,golesEB,j);
								}
								
								else{//DERROTA DE ALGUN EQUIPO
								Modificar_Datos(VICTORIA,golesEB,j); 
								Modificar_Datos(DERROTA,golesEB,i);
							
								}
						Guardar_Equipos(equipos[i].nombre,golesEA,equipos[j].nombre,golesEB,i,j);		
						partidos[i][j] = true;
				        partidos[j][i] = true;
					}
			}
		}	
}

//( 7 )
void Equipos::Modificar_Datos( int bandera , int goles , int i ){
		
		switch( bandera ){
			
			case VICTORIA:
			equipos[i].puntos+=3;
			equipos[i].victorias++;
			equipos[i].goles+=goles;
			break;
			
			case EMPATE:
			equipos[i].puntos++;
			equipos[i].empates++;
			break;
			
			case DERROTA:
			equipos[i].derrotas++;
			equipos[i].goles-=goles;	
			break;
			
		}
		equipos[i].pjugados++;
		

}

// ( 8 )
void Equipos::Guardar_Equipos( char *EquipoA , int golesA , char *EquipoB , int golesB , int i , int j ){
	
	  strcpy(juego_equipos[i][j].equipoA,EquipoA);
	  strcpy(juego_equipos[i][j].equipoB,EquipoB);
	  juego_equipos[i][j].golesA=golesA;
	  juego_equipos[i][j].golesB=golesB;
	  
	  strcpy(juego_equipos[j][i].equipoA,EquipoB);
	  strcpy(juego_equipos[j][i].equipoB,EquipoA);
	  juego_equipos[j][i].golesA=golesB;
	  juego_equipos[j][i].golesB=golesA;
	
}

// ( 9 )
void Equipos::Ordenar_Equipos( ){
	// Ordenar equipos por puntos y goles
	for (int i = 0; i < num_equipos - 1; i++) {
	    for (int j = 0; j < num_equipos - i - 1; j++) {
	        // Comparar los puntos de los equipos
	        if (equipos[j].puntos < equipos[j + 1].puntos) {
	            std::swap(equipos[j], equipos[j + 1]);
	        }
	        // Si hay empate en los puntos, comparar los goles
	        else if (equipos[j].puntos == equipos[j + 1].puntos && equipos[j].goles < equipos[j + 1].goles) {
	            std::swap(equipos[j], equipos[j + 1]);
	        }
	    }
	}
}

// ( 10 )
void Equipos::Mostrar( ){
	
	gotoxy(  25, 1 );std::cout<<"TABLA DE EQUIPOS "<<std::endl;
	gotoxy(  5, 2 );std::cout<<"POSICION";
	gotoxy(  15, 2 );std::cout<<"EQUIPO"; 
	gotoxy( 25, 2 );std::cout<<"P_J";
	gotoxy( 30, 2 );std::cout<<"P_G";
	gotoxy( 35, 2 );std::cout<<"P_E";
	gotoxy( 40, 2 );std::cout<<"P_P";
	gotoxy( 45, 2 );std::cout<<"GOLES";
	gotoxy( 55, 2 );std::cout<<"PUNTOS";
	
	for(int i=0;i<num_equipos;i++){
		
		gotoxy( 5, 4+2*i );std::cout<<i+1;	
		gotoxy( 15, 4+2*i );std::cout<<equipos[i].nombre;	
		gotoxy( 25, 4+2*i );std::cout<<equipos[i].pjugados;	
		gotoxy( 30, 4+2*i );std::cout<<equipos[i].victorias;	
		gotoxy( 35, 4+2*i );std::cout<<equipos[i].empates;
		gotoxy( 40, 4+2*i );std::cout<<equipos[i].derrotas;
		gotoxy( 45, 4+2*i );std::cout<<equipos[i].goles;
		gotoxy( 55, 4+2*i );std::cout<<equipos[i].puntos;	
		gotoxy( 5, 5+2*i );std::cout<<"--------------------------------------------------------";	
	}
}

// ( 11 )
void Equipos::Mostrar_Partidos( ){
	int y=5;
	gotoxy(  25, 1 );std::cout<<"LISTA DE PARTIDOS"<<std::endl;
	gotoxy(  15, 3 );std::cout<<"EQUIPO ";
	gotoxy(  25, 3 );std::cout<<"GOLES ";
	gotoxy(  35, 3 );std::cout<<"GOLES ";
	gotoxy(  45, 3 );std::cout<<"EQUIPO";
	std::cout<<std::endl;
	for(int i=0;i<num_equipos;i++){
		
		for (int j=0;j<num_equipos;j++){
			
			if(i==j){continue;}// SI ENTRA AQUI SE SALTA ESTA LINEA
			
			else{
				
			gotoxy(  15, y+i );std::cout<<juego_equipos[i][j].equipoA;
			gotoxy(  25, y+i );std::cout<<juego_equipos[i][j].golesA;
			gotoxy(  30, y+i );std::cout<<"VS";
			gotoxy(  35, y+i );std::cout<<juego_equipos[i][j].golesB;
			gotoxy(  45, y+i );std::cout<<juego_equipos[i][j].equipoB;
		
			}
			
		y++;
		}
	
	}
}

// ( 12 )
void Equipos::gotoxy( int x , int y ){
	 HANDLE hcon;  
     hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
     COORD dwPos;  
     dwPos.X = x;  
     dwPos.Y= y;  
     SetConsoleCursorPosition(hcon,dwPos);  
}

// ( 13 )
Equipos::~Equipos( ){
	
	for(int i=0;i<num_equipos;i++){
		delete []partidos[i];
		delete []juego_equipos[i];
	}
	delete []juego_equipos;
	delete []partidos;
	delete []equipos;
	
}

