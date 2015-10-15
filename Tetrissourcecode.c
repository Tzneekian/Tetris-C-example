/*Tetris*/
/*TESTO:Tetris.
Si vuole implementare un programma per la simulazione del gioco del tetris.
Si consideri per semplicità che l’utente abbia a disposizione solo oggetti quadrati (formati da 4 quadratini) e lineari (3 quadratini) da inserire in una griglia. Ad ogni istante l’utente può scegliere di ruotare l’oggetto lineare creato casualmente, a destra o sinistra. Se si completa una linea sul fondo della griglia l’utente guadagna un punto e l’intera linea viene eliminata. Il gioco finisce dopo la creazione casuale di 20 oggetti o se l’utente non può inserire più oggetti. Nella simulazione mostrare le fasi del gioco.
Effettuare almeno 5 test, visualizzando le fasi del gioco (con almeno una vincita e almeno una perdita).*/
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <dos.h>
#include <time.h>

#define RIGA 21
#define COLONNA 10
#define DESTRA 77
#define SINISTRA 75
#define GIU 80
#define SU 72
//Qusta function ci permette di spostare il pezzo all'interno del campo di gioco
void GotoXY(int x, int y)
{
    COORD CursorPos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, CursorPos);
}

int i, j; 
int sposta, random; 
int punti = 0; 
int contatore_pezzi = 1; 
char campo_gioco[21][10]; 
char linea[3][1] = {{'X'},
                    {'X'},
                    {'X'}};
char quadrato[2][2] = {{'X', 'X'}, 
                    {'X', 'X'}};

//Array vuoto
void caricaArray() 
{
    for (i = 0; i < RIGA; i++)
    {
        for (j = 0; j < COLONNA; j++)
        {
            campo_gioco[i][j] = ' ';
        }
    }
}

//Dichiaro i prototipi

void Inserisci_pos();
void elimina_linea();
void Crea_campo();
void spostamento_pezzi();
void spostamento_pezzi_2();
int main()
{
  
    printf("-------------------!!!TETRIS!!!------------------\n");
    printf("-Per giocare usare i tasti freccia della tastiera(DESTRA/SINISTRA/SU)-\n-Si totalizza un punto quando una linea viene cancellata-\n");
    system("PAUSE");
    
    
    caricaArray();
    spostamento_pezzi();
    printf("\n\n");
    return 0;
}
//Stampa i bordi del campo di gioco
void Crea_campo() 
{
    for(i=1;i<=19;i++)
    {
        GotoXY(i,22); putch('*');
        GotoXY(i,0); putch('*');
    }
    
    for (j=1;j<22; j++) {
        GotoXY(0,j); putch('*');
        GotoXY(20,j); putch('*');
    }
    printf("\n\n     STATISTICHE \n");
    printf("**********************");
     printf("\n* PUNTI:%d ** PEZZO:%d *\n", punti, contatore_pezzi);
     printf("**********************\n");
}
//Con questa Function rallentiamo il movimento dei pezzi verso il basso
void rallentamento()
{
    long double i;
    for(i=0;i<=(35000000);i++);
}

//Function che visualizza l'array ad ogni istante
void visualizzaArray() 
{
    printf("\n");
    for (i = 0; i < RIGA; i++)
    {
        printf(" "); 
        for (j = 0; j < COLONNA; j++)
        {
            printf("%c ", campo_gioco[i][j]);
        }
        printf("\n");
    }
        Crea_campo();
}
//Function che genera un dei due pezzi a caso e verifica la presenza di una linea piena
void spostamento_pezzi()
{
    do {
        elimina_linea(); 
       int  r = 0; 
       int  c = 4;
        srand(time(NULL));
        random = rand() % 2;
        visualizzaArray();
        spostamento_pezzi_2();
    } while ( sposta != 27 && contatore_pezzi != 20 );
}
//Function che ci permette di spostare verso sinistra o verso destra i pezzi, se il pezzo generato è la linea questa ruota
void spostamento_pezzi_2()
{
     int  r = 0; 
       int  c = 4;
        do {
            if ( contatore_pezzi == 20 )
            {
                system("cls");
                printf("LIMITE RAGGIUNTO\n.");  
                system("PAUSE");
                break;             
            }
            
            r++;
            system("cls");
            if (random == 0) {
                campo_gioco[r-1][c] = ' '; 
                campo_gioco[r-1][c+1] = ' ';
                campo_gioco[r][c] = quadrato[0][0]; 
                campo_gioco[r][c+1] = quadrato[0][1];
                campo_gioco[r+1][c] = quadrato[1][0];
                campo_gioco[r+1][c+1] = quadrato[1][1];
            }
            if (random == 1) {
                if ( campo_gioco[r-1][c+1] == ' ' )
                {
                    campo_gioco[r-2][c+1] = ' ';
                }
                campo_gioco[r-1][c] = ' ';
                campo_gioco[r][c] = linea[0][0]; 
                campo_gioco[r+1][c] = linea [1][0];
                campo_gioco[r+2][c] = linea [2][0];
            }
            visualizzaArray();
            rallentamento();
            //Se si preme il stato SU/DESTA/SINISTRA ilpezzo cambia posizione
            if ( kbhit() ) 
                {
                    sposta = getch();
                    if ( sposta==SU ) 
                        {
                            if ( random == 1 )
                            {
                                campo_gioco[r+2][c] = ' ';
                                while ( campo_gioco[r+1][c-1] != 'X' || campo_gioco[r+1][c] != 'X' || campo_gioco[r+1][c+1] != 'X' ) 
                                {
                                    if ( r==20 ) { 
                                        contatore_pezzi++;
                                        return spostamento_pezzi();
                                    }
                                    r++;
                                    system("cls");
                                    if ( kbhit() ) {
                                        sposta = getch();
                                        if ( sposta == SU) {
                                            campo_gioco[r-1][c] = ' ';
                                            campo_gioco[r-1][c-1] = ' ';
                                            return spostamento_pezzi_2();
                                        }
                                        if ( sposta == SINISTRA) {
                                            c--;
                                           campo_gioco[r-1][c+2] = ' ';
                                            if (c-1<0) { c++; } 
                                        }
                                        if ( sposta == DESTRA) {
                                            c++;
                                            campo_gioco[r-1][c-2] = ' ';
                                            if (c+1>COLONNA-1) { c--; } 
                                        }
                                    }
                                    campo_gioco[r-1][c-1] = ' ';
                                    campo_gioco[r-1][c] = ' ';
                                    campo_gioco[r-1][c+1] = ' ';
                                    campo_gioco[r][c-1] = 'X';
                                    campo_gioco[r][c] = 'X';
                                    campo_gioco[r][c+1] = 'X';
                                    visualizzaArray();
                                    rallentamento();
                                    if ( campo_gioco[r+1][c] == 'X' || campo_gioco[r+1][c-1] == 'X' || campo_gioco[r+1][c+1] == 'X' ) {
                                        contatore_pezzi++;
                                        return spostamento_pezzi();
                                    }
                                }
                            }
                        }

                    if (sposta == DESTRA ) 
                    {
                        c++; 
                        system("cls");
                        if (random == 0) {
                            if (c+1>COLONNA-1) { c--; } 
                            campo_gioco[r][c-1] = ' '; 
                            campo_gioco[r+1][c-1] = ' ';
                        }
                        else if (random == 1) {
                        if (c>COLONNA-1) { c--; }
                        campo_gioco[r-2][c-1] = ' ';
                        campo_gioco[r-1][c-1] = ' ';
                        campo_gioco[r][c-1] = ' ';
                        campo_gioco[r+1][c-1] = ' ';
                        campo_gioco[r+2][c-1] = ' ';
                        }
                        visualizzaArray(); 
                    }
                    if (sposta == SINISTRA ) 
                    {
                        c--; 
                        if (c<0) { c++; } 
                        system("cls");
                        if (random == 0) {
                        campo_gioco[r][c+2] = ' '; 
                        campo_gioco[r+1][c+2] = ' ';
                        }
                        else if (random == 1) {
                        campo_gioco[r-1][c+2] = ' '; 
                        campo_gioco[r-1][c+1] = ' ';
                        campo_gioco[r][c+1] = ' ';
                        campo_gioco[r+1][c+1] = ' ';
                        campo_gioco[r+2][c+1] = ' ';
                        }
                        visualizzaArray();
                    }
                }
            if (random == 0) {
            if (campo_gioco[r+2][c] == 'X' || campo_gioco[r+2][c+1] == 'X') 
            {
                if (campo_gioco[0][c] == 'X' || campo_gioco[1][c] == 'X') 
                {
                    system("cls");
                    printf("LIMITE PEZZI RAGGIUNTO!\n.");
                    system("PAUSE");
                  exit(0);
                 
                }
                contatore_pezzi++;
                return spostamento_pezzi(); 
            }
            }
            if (random == 1) {
                if (campo_gioco[r+3][c] == 'X') {
                    if (campo_gioco[0][c] == 'X' || campo_gioco[1][c] == 'X')
                    {
                        system("cls");
                        printf("LIMITE PEZZI RAGGIUNTO!\n");
                         system("PAUSE");
                        exit(0);
                    
                    }
                    contatore_pezzi++;
                    return spostamento_pezzi();
                }
            }
            if (random == 0) {
            if (r+1==20) { 
                contatore_pezzi++;
                return spostamento_pezzi(); }
            }
            else if (random == 1) {
            if (r+2==20) { 
                contatore_pezzi++;
                return spostamento_pezzi(); }
            }
        } while ( sposta != 27 );
}


//Function per  inserire un pezzo nella posizione iniziale
void Inserisci_pos()
{
    int i1 = 0;
    int j1 = 4;
    if (random==0) {
    campo_gioco[i1][j1] = quadrato[0][0]; 
    campo_gioco[i1][j1+1] = quadrato[0][1];
    campo_gioco[i1+1][j1] = quadrato[1][0];
    campo_gioco[i1+1][j1+1] = quadrato[1][1];
    }
    if (random==1) {
        campo_gioco[i1][j1] = linea[0][0];
        campo_gioco[i1+1][j1] = linea [1][0];
        campo_gioco[i1+2][j1] = linea [2][0];
    }
}
//Function per eliminare una riga se piena
void elimina_linea() 
{
    int k;
    int cont_riga;
    int colonna;
    char aus[COLONNA];
    for (cont_riga=0; cont_riga<=20; cont_riga++)
    {
        if (campo_gioco[cont_riga][0] == 'X' && campo_gioco[cont_riga][1] == 'X' && campo_gioco[cont_riga][2] == 'X' && campo_gioco[cont_riga][3] == 'X' && campo_gioco[cont_riga][4] == 'X' && campo_gioco[cont_riga][5] == 'X' && campo_gioco[cont_riga][6] == 'X' && campo_gioco[cont_riga][7] == 'X' && campo_gioco[20][8] == 'X' && campo_gioco[20][9] == 'X')
        {
            for (colonna=0; colonna<10; colonna++) {
                aus[colonna] = campo_gioco[cont_riga-1][colonna];
            }
            for (colonna=0; colonna<10; colonna++) {
                campo_gioco[cont_riga][colonna] = aus[colonna];
            }
            for (colonna=0; colonna<10; colonna++) {
                campo_gioco[cont_riga-1][colonna] = ' ';
            }
            punti++;
            for (k=2; k<11; k++) {
            if (campo_gioco[cont_riga-k][0] == 'X' || campo_gioco[cont_riga-k][1] == 'X' || campo_gioco[cont_riga-k][2] == 'X' || campo_gioco[cont_riga-k][3] == 'X' || campo_gioco[cont_riga-k][4] == 'X' || campo_gioco[cont_riga-k][5] == 'X' || campo_gioco[cont_riga-k][6] == 'X' || campo_gioco[cont_riga-k][7] == 'X' || campo_gioco[cont_riga-k][8] == 'X' || campo_gioco[cont_riga-k][9] == 'X' )
                {
                    for (colonna=0; colonna<10; colonna++) {
                    aus[colonna] = campo_gioco[cont_riga-k][colonna];
                    }
                    for (colonna=0; colonna<10; colonna++) {
                    campo_gioco[cont_riga-k+1][colonna] = aus[colonna];
                    }
                    for (colonna=0; colonna<10; colonna++) {
                    campo_gioco[cont_riga-k][colonna] = ' ';
                    }
                }
            }
            system("cls");
            visualizzaArray();
        }
    }
}

