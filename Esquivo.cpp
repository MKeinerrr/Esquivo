#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define ANCHO_PANTALLA 90
#define ALTURA_PANTALLA 26
#define ANCHO_VENTANA 70 

using namespace std; 

HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
COORD PosicionCursor;

int enemigoY[3];
int enemigoX[3];
int banderaEnemigo[3];
char coche[4][4] = { ' ','±','±',' ', 
					'±','±','±','±', 
					' ','±','±',' ',
					'±','±','±','±' }; 
					
int posCoche = ANCHO_VENTANA/2;
int puntuacion = 0; 

void gotoxy(int x, int y){
	PosicionCursor.X = x;
	PosicionCursor.Y = y;
	SetConsoleCursorPosition(consola, PosicionCursor);
}

void configurarCursor(bool visible, DWORD tamano) {
	if(tamano == 0)
		tamano = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = tamano;
	SetConsoleCursorInfo(consola, &lpCursor);
}

void dibujarBorde(){  
	for(int i=0; i<ALTURA_PANTALLA; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j, i); cout<<"±";
			gotoxy(ANCHO_VENTANA-j, i); cout<<"±";
		}
	} 
	for(int i=0; i<ALTURA_PANTALLA; i++){
		gotoxy(ANCHO_PANTALLA, i); cout<<"±";
	} 
}

void generarEnemigo(int indice){
	enemigoX[indice] = 17 + rand() % (33);  
}

void dibujarEnemigo(int indice){
	if(banderaEnemigo[indice] == true){
		gotoxy(enemigoX[indice], enemigoY[indice]);   cout<<"±±±±";  
		gotoxy(enemigoX[indice], enemigoY[indice]+1); cout<<" ±± "; 
		gotoxy(enemigoX[indice], enemigoY[indice]+2); cout<<"±±±±"; 
		gotoxy(enemigoX[indice], enemigoY[indice]+3); cout<<" ±± ";  
	} 
}

void borrarEnemigo(int indice){
	if(banderaEnemigo[indice] == true){
		gotoxy(enemigoX[indice], enemigoY[indice]); cout<<"    ";  
		gotoxy(enemigoX[indice], enemigoY[indice]+1); cout<<"    "; 
		gotoxy(enemigoX[indice], enemigoY[indice]+2); cout<<"    "; 
		gotoxy(enemigoX[indice], enemigoY[indice]+3); cout<<"    "; 
	} 
}

void reiniciarEnemigo(int indice){
	borrarEnemigo(indice);
	enemigoY[indice] = 1;
	generarEnemigo(indice);
}

void dibujarCoche(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+posCoche, i+22); cout<<coche[i][j];
		}
	}
}

void borrarCoche(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+posCoche, i+22); cout<<" ";
		}
	}
}

int colision(){
	if(enemigoY[0] + 4 >= 23){
		if(enemigoX[0] + 4 - posCoche >= 0 && enemigoX[0] + 4 - posCoche < 9){
			return 1;
		}
	}
	return 0;
}

void finDelJuego(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- GAME OVER -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPresiona cualquier tecla para regresar al menu.";
	getch();
}

void actualizarPuntuacion(){
	gotoxy(ANCHO_VENTANA + 7, 5);cout<<"Puntaje:"<<puntuacion<<endl;
}

void instrucciones(){
	system("cls");
	cout<<"Instrucciones";
	cout<<"\n----------------";
	cout<<"\n Evita los coches moviendote hacia la izquierda o derecha. ";
	cout<<"\n\n Presiona 'a' para moverte a la izquierda";
	cout<<"\n Presiona 'd' para moverte a la derecha";
	cout<<"\n Presiona 'escape' para salir";
	cout<<"\n\nPresiona cualquier tecla para regresar al menu";
	getch();
}

void jugar(){
	posCoche = -1 + ANCHO_VENTANA/2;
	puntuacion = 0;
	banderaEnemigo[0] = 1;
	banderaEnemigo[1] = 0;
	enemigoY[0] = enemigoY[1] = 1;
	  
	system("cls"); 
	dibujarBorde(); 
	actualizarPuntuacion();
	generarEnemigo(0);
	generarEnemigo(1);
	
	gotoxy(ANCHO_VENTANA + 7, 2);cout<<"Esquivo";
	gotoxy(ANCHO_VENTANA + 6, 4);cout<<"----------";
	gotoxy(ANCHO_VENTANA + 6, 6);cout<<"----------";
	gotoxy(ANCHO_VENTANA + 7, 12);cout<<"Control ";
	gotoxy(ANCHO_VENTANA + 7, 13);cout<<"-------- ";
	gotoxy(ANCHO_VENTANA + 2, 14);cout<<"Tecla A Izquierda";
	gotoxy(ANCHO_VENTANA + 2, 15);cout<<"Tecla D Derecha"; 
	
	gotoxy(18, 5);cout<<"Presiona para comenzar";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if(ch == 'a' || ch == 'A'){
				if(posCoche > 18)
					posCoche -= 4;
			}
			if(ch == 'd' || ch == 'D'){
				if(posCoche < 50)
					posCoche += 4;
			} 
			if(ch == 27){
				break;
			}
		} 
		
		dibujarCoche(); 
		dibujarEnemigo(0); 
		dibujarEnemigo(1); 
		if(colision() == 1){
			finDelJuego();
			return;
		} 
		Sleep(50);
		borrarCoche();
		borrarEnemigo(0);
		borrarEnemigo(1);   
		
		if(enemigoY[0] == 10)
			if(banderaEnemigo[1] == 0)
				banderaEnemigo[1] = 1;
		
		if(banderaEnemigo[0] == 1)
			enemigoY[0] += 1;
		
		if(banderaEnemigo[1] == 1)
			enemigoY[1] += 1;
		 
		if(enemigoY[0] > ALTURA_PANTALLA - 4){
			reiniciarEnemigo(0);
			puntuacion++;
			actualizarPuntuacion();
		}
		if(enemigoY[1] > ALTURA_PANTALLA - 4){
			reiniciarEnemigo(1);
			puntuacion++;
			actualizarPuntuacion();
		}
	}
}

int main()
{
	configurarCursor(0,0); 
	srand((unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |         Esquivo        | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Comenzar Juego";
		gotoxy(10,10); cout<<"2. Instrucciones";	 
		gotoxy(10,11); cout<<"3. Salir";
		gotoxy(10,13); cout<<"Seleccionar opcion: ";
		char op = getche();
		
		if(op == '1') jugar();
		else if(op == '2') instrucciones();
		else if(op == '3') exit(0);
		
	} while(1);
	
	return 0;
}

