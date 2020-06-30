#ifndef FUNCIONESGENERALA_H_INCLUDED
#define FUNCIONESGENERALA_H_INCLUDED
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "rlutil.h"
#include <dos.h>

using namespace std;
#define ABAJO 80 
#define ARRIBA 72 
#define ENTER 13 

void cargarVector(int v[], int tam) { // cargas el vector manualmente, funciona con la bandera "prueba = true "
int i;
for (i=0;i<tam;i++){
    cout << "Ingrese un numero:  "<<endl;
    cin >> v[i];
}
}
void cargarAleatorio(int v[], int tam, int limite){ // Carga el vector con numeros aleatorios 
  int i;
  srand(time(NULL));
  for( i=0; i<tam; i++ ){
        v[i]=(rand()%limite)+1;
  }
}
void mostrarVector(int v[], int tam){ // muestra el valor de los dados 
    int i;
    for(i=0;i<tam;i++){
        cout<<v[i]<<endl;
    }
}


void contarRepetidos(int v[],int tam,int contar[]){ //Funcion esencial para las distintas jugadas, dice cuantos dados iguales hay en el vector 
int i,x,contador=0;
for(i=0;i<tam;i++){
    for(x=0;x<tam;x++){
        if(v[i]==v[x]){contador++;}
    }
   contar[i]=contador;
   contador=0;
}
}

int full(int contar[],int tam){ //Caso de FULL
int i,cont=0,cont2=0;
for(i=0;i<tam;i++){
            if(contar[i]==2){cont++;}
            if(contar[i]==3){cont2++;}
           }
            if(cont==2 && cont2==3){return 1;}
            else{if(cont==3 && cont2==2){return 1;}
            else{return 0;}}
}
int poker(int contar[],int tam){ //Caso de POKER
int i,cont=0;
for(i=0;i<tam;i++){
            if(contar[i]==4){cont++;}
}
            if(cont==4){return 1;}
            else{return 0;}
}
int generala(int contar[],int tam){ //Caso de GENERALA 
int i,cont=0;
for(i=0;i<tam;i++){
            if(contar[i]==5){cont++;}
}
            if(cont==5){return 1;}
            else{return 0;}
}

void NumeroAleatorio(int dados[],int limite,int posicion){// cambiar dado que elige el usuario
srand(time(NULL));
dados[posicion]=rand()%limite+1;
}

int escalera(int dados[]){ //Caso de ESCALERA
int con=0;
 if(dados[con]==1 && dados[con+1]==2 && dados[con+2]==3 && dados[con+3]==4 && dados[con+4]==5){
    return 1;
 }
 else{if(dados[con]==2 && dados[con+1]==3 && dados[con+2]==4 && dados[con+3]==5 && dados[con+4]==6){return 1;}
 else{return 0;}
 }}


int juegos(int dados[]) { //Con esta funcion conseguimos los puntos en el caso de que tenga juego de numeros, ej 2-2 o 2-2-2 retornando el mayor
    int contar[5], puntuacion = 0, primerJuego = 0,segundoJuego=0, tercerJuego = 0, i,var;
    bool band = true; 
    contarRepetidos(dados, 5, contar);
    for (i = 0; i < 5; i++) { // 4 3 5 4 5
        
        if (contar[i] == 2 && band == true) { var = dados[i]; primerJuego = dados[i] * 2; band = false; } //If para asegurarse un primer juego de par
        if (contar[i] == 2 && dados[i] != var) { segundoJuego = dados[i] * 2; }//If con "var" con valor del anterior juego par asi da la posibilidad a un segundo juego
        if (contar[i] == 3) { tercerJuego = dados[i] * 3; } //If en el caso de que saque cualquier juego de 3
    }
    if (primerJuego > segundoJuego && primerJuego>tercerJuego) { return primerJuego; }
    else {
        if (segundoJuego > primerJuego && segundoJuego>tercerJuego) { return segundoJuego; }
        else { return tercerJuego; }
       
    }

}

int PuntosBasicos(int dados[]) { //Puntuacion en el caso de que no haya ninguna combinacion
    
    if (dados[0] > dados[1] && dados[0] > dados[2] && dados[0] > dados[3] && dados[0] > dados[4]) { return dados[0]; }
    if (dados[1] > dados[0] && dados[1] > dados[2] && dados[1] > dados[3] && dados[1] > dados[4]) { return dados[1]; }
    if (dados[2] > dados[0] && dados[2] > dados[1] && dados[2] > dados[3] && dados[2] > dados[4]) { return dados[2]; }
    if (dados[3] > dados[0] && dados[3] > dados[1] && dados[3] > dados[2] && dados[3] > dados[4]) { return dados[3]; }
    if (dados[4] > dados[0] && dados[4] > dados[1] && dados[4] > dados[2] && dados[4] > dados[3]) { return dados[4]; }
}





int MenuDePuntos(int dados[],int contar[]){ //Con esto se controlan TODAS las situaciones de puntos dadas posibles
    bool bandera,bandera2,bandera3,bandera4;
    int puntuacion; 
           //mostrarVector(dados,5); //MOSTRAR VALORES DE LOS DADOS
           puntuacion = juegos(dados);
           if (puntuacion == 0) { puntuacion = PuntosBasicos(dados); }
           bandera= escalera(dados);
           if(bandera==1){puntuacion=25;}
           bandera2= full(contar,5);
           if(bandera2==1){puntuacion=30;}
           bandera3=poker(contar,5);
           if(bandera3==1){puntuacion=40;}
           bandera4=generala(contar,5);
           if(bandera4==1){puntuacion=50;}
           return puntuacion;

}



//FUNCIONES PARA EL MENU 


void PasoDeTurno() { //Recuadro de informacíon
    int i, j;
    rlutil::setColor(rlutil::LIGHTRED);
    for (i = 30; i <= 100; i++) {
        rlutil::locate(i, 10); printf("%c", 205);
        rlutil::locate(i, 30); printf("%c", 205);
        for (j = 10; j <= 30; j++) {
            rlutil::locate(30, j); printf("%c", 186);
            rlutil::locate(100, j); printf("%c", 186);
        }
    }
    rlutil::locate(30, 30); printf("%c", 200); //ABAJO A LA IZQUIERDA
    rlutil::locate(30, 10); printf("%c", 201); //ARRIBA A LA IZQUIERDA
    rlutil::locate(100, 10); printf("%c", 187); //ARRIBA A LA DERECHA
    rlutil::locate(100, 30); printf("%c", 188); //ABAJO A LA DERECHA

    cout << endl;
    cout << endl;


}

void tituloAnimado() {

    int xcol;
   


    // primera linea 

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::locate(14, 2); printf("%c", 201);
    rlutil::locate(14, 3); printf("%c", 186);
    rlutil::locate(14, 4); printf("%c", 200);


    for (xcol = 15; xcol <= 116; xcol++) {

        rlutil::locate(xcol, 2); printf("%c", 205);
        rlutil::locate(xcol, 4); printf("%c", 205);

        Sleep(30);
    }

    rlutil::locate(116, 2); printf("%c", 187);
    rlutil::locate(116, 3); printf("%c", 186);
    rlutil::locate(116, 4); printf("%c", 188);

    //SEGUNDA LINEA

    char vtitulo[] = "BIENVENIDO A LA GENERALA !!";
    int vlongitud;
    vlongitud = strlen(vtitulo);
    int vcentro = (((80 - vlongitud) / 2) + 1);

    

    for (xcol = 49; xcol <= vcentro; xcol++) {

    }

        rlutil::locate(xcol, 3); printf(vtitulo);

    }

int MenuPrincipalGenerala() { 
    int x = 55, y = 18;
    tituloAnimado();
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::RED);
    rlutil::locate(50, 17); cout << endl;
    rlutil::locate(50, 18); cout << "      1-UN JUGADOR" << endl;
    rlutil::locate(50, 19); cout << "      2-DOS JUGADORES" << endl;
    rlutil::locate(50, 20); cout << "      3-MAYOR PUNTUACION" << endl;
    rlutil::locate(50, 21); cout << "      4-SALIR DEL JUEGO" << endl;
    rlutil::locate(31, 28); cout << "Produced By: Ramiro Alegre y Matias Vietez";
    rlutil::locate(31, 29); cout << "Estudiantes de: UTN TUP";
    PasoDeTurno();
  
  rlutil::locate(x, y); printf("*"); //a partir de aca es para utilizar las flechas del teclado 
    bool elegir = false;
    while (!elegir) {
        if (_kbhit()) {
            rlutil::locate(x, y); printf(" ");
            char tecla = _getch();
            if (tecla == ENTER) { elegir = true; return y; }
            if (tecla == ARRIBA && y > 18) rlutil::locate(x, y--);
            if (tecla == ABAJO && y < 21) rlutil::locate(x, y++);
            rlutil::locate(x, y); printf("*");
        }
    }
}






void dadouno() { // la funcion que dibuja al dado en la primera posicion 

    // HORIZONTAL
    for (int i = 2; i < 10; i++) {
        rlutil::locate(i, 3); printf("%c", 205);
        rlutil::locate(i, 7); printf("%c", 205);
    }
    // VERTICAL
    for (int i = 4; i < 7; i++) {
        rlutil::locate(2, i); printf("%c", 186);
        rlutil::locate(10, i); printf("%c", 186);
    }
    ///ESQUINAS
    rlutil::locate(2, 3); printf("%c", 201);
    rlutil::locate(2, 7); printf("%c", 200);
    rlutil::locate(10, 3); printf("%c", 187);
    rlutil::locate(10, 7); printf("%c", 188);


}
   



void dadoDos() {// la funcion que dibuja al dado en la segunda posicion 

    // HORIZONTAL
    for (int i = 13; i < 20; i++) {
        rlutil::locate(i, 3); printf("%c", 205);
        rlutil::locate(i, 7); printf("%c", 205);
    }
    // VERTICAL
    for (int i = 4; i < 7; i++) {
        rlutil::locate(12, i); printf("%c", 186);
        rlutil::locate(20, i); printf("%c", 186);
    }
    //ESQUINAS
    rlutil::locate(12, 3); printf("%c", 201);
    rlutil::locate(12, 7); printf("%c", 200);
    rlutil::locate(20, 3); printf("%c", 187);
    rlutil::locate(20, 7); printf("%c", 188);


    
}


void dadoTres() {// la funcion que dibuja al dado en la tercera posicion 

    // HORIZONTAL
    for (int i = 23; i < 30; i++) {
        rlutil::locate(i, 3); printf("%c", 205);
        rlutil::locate(i, 7); printf("%c", 205);
    }
    // VERTICAL
    for (int i = 4; i < 7; i++) {
        rlutil::locate(22, i); printf("%c", 186);
        rlutil::locate(30, i); printf("%c", 186);
    }
    //ESQUINAS
    rlutil::locate(22, 3); printf("%c", 201);
    rlutil::locate(22, 7); printf("%c", 200);
    rlutil::locate(30, 3); printf("%c", 187);
    rlutil::locate(30, 7); printf("%c", 188);


    
}


void dadoCuatro() {// la funcion que dibuja al dado en la cuarta posicion 

    // HORIZONTAL
    for (int i = 32; i < 40; i++) {
        rlutil::locate(i, 3); printf("%c", 205);
        rlutil::locate(i, 7); printf("%c", 205);
    }
    // VERTICAL
    for (int i = 4; i < 7; i++) {
        rlutil::locate(32, i); printf("%c", 186);
        rlutil::locate(40, i); printf("%c", 186);
    }
    //ESQUINAS
    rlutil::locate(32, 3); printf("%c", 201);
    rlutil::locate(32, 7); printf("%c", 200);
    rlutil::locate(40, 3); printf("%c", 187);
    rlutil::locate(40, 7); printf("%c", 188);


    
    
}


void dadoCinco() {// la funcion que dibuja al dado en la quinta posicion 

    // HORIZONTAL
    for (int i = 42; i < 50; i++) {
        rlutil::locate(i, 3); printf("%c", 205);
        rlutil::locate(i, 7); printf("%c", 205);
    }
    // VERTICAL
    for (int i = 4; i < 7; i++) {
        rlutil::locate(42, i); printf("%c", 186);
        rlutil::locate(50, i); printf("%c", 186);
    }
    //ESQUINAS
    rlutil::locate(42, 3); printf("%c", 201);
    rlutil::locate(42, 7); printf("%c", 200);
    rlutil::locate(50, 3); printf("%c", 187);
    rlutil::locate(50, 7); printf("%c", 188);
}
       

void NombreMaximo(char nombre[], char NombreMax[]) { // guarda el nombre del jugador que mas puntos saco
    int i;
    for (i = 0; i < 20; i++) {
        NombreMax[i] = nombre[i];
    }
}

void Gana(int puntuacion, int puntuacionTotal) {  // dibuja el cartel de final de la partida modo solitario
    PasoDeTurno();
    rlutil::locate(39, 18);  cout << "Felicidades, Acaba de completar el juego: LA GENERALA!!" << endl;
    rlutil::locate(51, 20);  cout << "Puntuacion:  " << puntuacion << endl;
    rlutil::locate(51, 21);  cout << "Puntuacion Total:  " << puntuacionTotal << endl;
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;

}

void GanaModo2jug(int puntuacion, int puntuacionTotal, char nombre[]) {// dibuja el cartel de final de la partida modo 2 jugadores
    system("pause");
    system("cls");
    PasoDeTurno();
    rlutil::locate(39, 18);  cout << "Felicidades "<<nombre<<" acaba de ganar el juego: LA GENERALA!!" << endl;
    rlutil::locate(51, 20);  cout << "Puntuacion:  " << puntuacion << endl;
    rlutil::locate(51, 21);  cout << "Puntuacion Total:  " << puntuacionTotal << endl;
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;

}
//La idea de esta funcion es dependiendo de el valor de i,mostrar el dado
void MenuDeDados(int dados[]) {    // dibujalos dados respecto a los valores que se le entreguen en las distintas posiciones 
    int i;
    dadouno(); dadoDos(); dadoTres(); dadoCuatro(); dadoCinco();
    for (i = 0; i <5; i++) {
        switch (dados[i]) {
        /*dado 1*/ case 1:
            if (i == 0) { rlutil::locate(6, 5); printf("%c", 254); }
            if (i == 1) { rlutil::locate(16, 5); printf("%c", 254); }
            if (i == 2) { rlutil::locate(26, 5); printf("%c", 254); }
            if (i == 3) { rlutil::locate(36, 5); printf("%c", 254); }
            if (i == 4) { rlutil::locate(46, 5); printf("%c", 254); }

            ; break;

        /*dado 2*/ case 2:
            if (i == 0) {
                rlutil::locate(4, 4); printf("%c", 254);
                rlutil::locate(8, 6); printf("%c", 254);
            }

            if (i == 1) {
                rlutil::locate(14, 4); printf("%c", 254);
                rlutil::locate(18, 6); printf("%c", 254);
            }
            if (i == 2) {
                rlutil::locate(24, 4); printf("%c", 254);
                rlutil::locate(28, 6); printf("%c", 254);
            }
            if (i == 3) {
                rlutil::locate(34, 4); printf("%c", 254);
                rlutil::locate(38, 6); printf("%c", 254);
            }
            if (i == 4) {
                rlutil::locate(44, 4); printf("%c", 254);
                rlutil::locate(48, 6); printf("%c", 254);
            }

            ; break;
        /*dado 3*/  case 3:
            if (i == 0) {
                rlutil::locate(6, 5); printf("%c", 254);
                rlutil::locate(8, 4); printf("%c", 254);
                rlutil::locate(4, 6); printf("%c", 254);
            }

            if (i == 1) {
                rlutil::locate(16, 5); printf("%c", 254);
                rlutil::locate(18, 4); printf("%c", 254);
                rlutil::locate(14, 6); printf("%c", 254);
            }

            if (i == 2) {
                rlutil::locate(26, 5); printf("%c", 254);
                rlutil::locate(28, 4); printf("%c", 254);
                rlutil::locate(24, 6); printf("%c", 254);
            }

            if (i == 3) {
                rlutil::locate(36, 5); printf("%c", 254);
                rlutil::locate(38, 4); printf("%c", 254);
                rlutil::locate(34, 6); printf("%c", 254);
            }

            if (i == 4) {
                rlutil::locate(46, 5); printf("%c", 254);
                rlutil::locate(48, 4); printf("%c", 254);
                rlutil::locate(44, 6); printf("%c", 254);
            }

            ; break;

        /*dado 4*/ case 4:
            if (i == 0) {
                rlutil::locate(4, 4); printf("%c", 254);
                rlutil::locate(4, 6); printf("%c", 254);
                rlutil::locate(8, 4); printf("%c", 254);
                rlutil::locate(8, 6); printf("%c", 254);
            }

            if (i == 1) {
                rlutil::locate(14, 4); printf("%c", 254);

                rlutil::locate(14, 6); printf("%c", 254);
                rlutil::locate(18, 4); printf("%c", 254);
                rlutil::locate(18, 6); printf("%c", 254);
            }

            if (i == 2)

            {
                rlutil::locate(24, 4); printf("%c", 254);
                rlutil::locate(24, 6); printf("%c", 254);
                rlutil::locate(28, 4); printf("%c", 254);
                rlutil::locate(28, 6); printf("%c", 254);
            }


            if (i == 3)

            {
                rlutil::locate(34, 4); printf("%c", 254);
                rlutil::locate(34, 6); printf("%c", 254);
                rlutil::locate(38, 4); printf("%c", 254);
                rlutil::locate(38, 6); printf("%c", 254);
            }
            if (i == 4) {
                rlutil::locate(44, 4); printf("%c", 254);
                rlutil::locate(44, 6); printf("%c", 254);
                rlutil::locate(48, 4); printf("%c", 254);
                rlutil::locate(48, 6); printf("%c", 254);
            }

            break;

        /*dado 5*/ case 5:
            if (i == 0)
            {
                rlutil::locate(4, 4); printf("%c", 254);
                rlutil::locate(4, 6); printf("%c", 254);
                rlutil::locate(8, 4); printf("%c", 254);
                rlutil::locate(6, 5); printf("%c", 254);
                rlutil::locate(8, 6); printf("%c", 254);
            }
            if (i == 1)
            {
                rlutil::locate(14, 4); printf("%c", 254);
                rlutil::locate(14, 6); printf("%c", 254);
                rlutil::locate(18, 4); printf("%c", 254);
                rlutil::locate(16, 5); printf("%c", 254);
                rlutil::locate(18, 6); printf("%c", 254);
            }
            if (i == 2)
            {
                rlutil::locate(24, 4); printf("%c", 254);
                rlutil::locate(24, 6); printf("%c", 254);
                rlutil::locate(28, 4); printf("%c", 254);
                rlutil::locate(26, 5); printf("%c", 254);
                rlutil::locate(28, 6); printf("%c", 254);
            }
            if (i == 3) {
                rlutil::locate(34, 4); printf("%c", 254);
                rlutil::locate(34, 6); printf("%c", 254);
                rlutil::locate(38, 4); printf("%c", 254);
                rlutil::locate(36, 5); printf("%c", 254);
                rlutil::locate(38, 6); printf("%c", 254);
            }
            if (i == 4)
            {
                rlutil::locate(44, 4); printf("%c", 254);
                rlutil::locate(44, 6); printf("%c", 254);
                rlutil::locate(48, 4); printf("%c", 254);
                rlutil::locate(46, 5); printf("%c", 254);
                rlutil::locate(48, 6); printf("%c", 254);
            }

            break;

        /*dado 6*/  case 6:
            if (i == 0) {
                rlutil::locate(4, 4); printf("%c", 254);
                rlutil::locate(4, 6); printf("%c", 254);
                rlutil::locate(8, 4); printf("%c", 254);
                rlutil::locate(4, 5); printf("%c", 254);
                rlutil::locate(8, 5); printf("%c", 254);
                rlutil::locate(8, 6); printf("%c", 254);
            }
            if (i == 1) {
                rlutil::locate(14, 4); printf("%c", 254);
                rlutil::locate(14, 6); printf("%c", 254);
                rlutil::locate(18, 4); printf("%c", 254);
                rlutil::locate(14, 5); printf("%c", 254);
                rlutil::locate(18, 5); printf("%c", 254);
                rlutil::locate(18, 6); printf("%c", 254);
            }
            if (i == 2) {
                rlutil::locate(24, 4); printf("%c", 254);
                rlutil::locate(24, 6); printf("%c", 254);
                rlutil::locate(28, 4); printf("%c", 254);
                rlutil::locate(24, 5); printf("%c", 254);
                rlutil::locate(28, 5); printf("%c", 254);
                rlutil::locate(28, 6); printf("%c", 254);
            }
            if (i == 3) {
                rlutil::locate(34, 4); printf("%c", 254);
                rlutil::locate(34, 6); printf("%c", 254);
                rlutil::locate(38, 4); printf("%c", 254);
                rlutil::locate(34, 5); printf("%c", 254);
                rlutil::locate(38, 5); printf("%c", 254);
                rlutil::locate(38, 6); printf("%c", 254);
            }
            if (i == 4) {
                rlutil::locate(44, 4); printf("%c", 254);
                rlutil::locate(44, 6); printf("%c", 254);
                rlutil::locate(48, 4); printf("%c", 254);
                rlutil::locate(44, 5); printf("%c", 254);
                rlutil::locate(48, 5); printf("%c", 254);
                rlutil::locate(48, 6); printf("%c", 254);
            }
            ; break;
        }
    }
}

    




    




#endif // FUNCIONESGENERALA_H_INCLUDED
