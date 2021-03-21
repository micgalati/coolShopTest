#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//DIMENSIONI DEL FILE
#define ROW 3
#define COL 4

#define wordLenght 10 //caratteri che compongono una parola
#define BUFF 1024  //lunghezza della riga del fila

//PROTOTIPI
char **rowDefinition(void);
void search(char **row, char *buffer, FILE *fp, const char *argv[]);
char *deleteSeparator(char *buffer);
int readColumn(const char *argv[]);
char *readWord(const char *argv[]);
int matching(int num_col, char *str, char **row);
void print(char **row);

int main(int argc, const char * argv[]) {
    
    /* APERTURA FILE */
    FILE *fp = fopen(argv[1], "r");
    
    char **row =  rowDefinition();
    
    char *buffer = malloc(BUFF * sizeof(char));  
    
    search(row, buffer, fp, argv);
   
    fclose(fp);
    
    return 0;
}

//DEFINIZIONE DELLA STRUTTURA DATI PER LA LETTURA DEL FILE
char **rowDefinition(){
    char **row;
    row = malloc(COL * sizeof(char *));
    for(int i = 0; i<COL; i++)
        row[i] = malloc(wordLenght * sizeof(char));
    
    return row;
}

//RICERCA NEL FILE RISPETTANDO I PARAMETRI INSERITI
void search(char **row, char *buffer, FILE *fp, const char *argv[]){
    int j=0, match=0;
    while( fscanf(fp, "%s", buffer) != EOF){
        //Eliminazione separatori: virgole e punti e virgole
        buffer = deleteSeparator(buffer);

        sscanf(buffer, "%s %s %s %s", row[j], row[j+1], row[j+2], row[j+3]);

        int numCol = readColumn(argv);
        char *str = readWord(argv);
        
        match = matching(numCol, str, row);
        
        if(match==1)
            print(row);
    }
    
    if(match==0)
        printf("Nessuna corrispondenza trovata\n");
}

char *deleteSeparator(char *buffer){
    for(int i=0; i< BUFF; i++){
        if(buffer[i] == ',')
            buffer[i] = ' ';
        if(buffer[i] == ';')
            buffer[i] = '\n';
    }

    return buffer;
}

//LETTURA DEL PARAMETRO DI RICERCA PER COLONNA
int readColumn(const char *argv[]){
    int numCol = atoi(argv[2]);
    return numCol;
}

//LETTURA DEL PARAMETRO DI RICERCA PER PAROLA
char *readWord(const char *argv[]){
    char *str = malloc(wordLenght * sizeof(char));
    strcpy(str, argv[3]);
    return str;
}

//CONDIZIONE DI MATCH
int matching(int num_col, char *str, char **row){
    int j=0, match=0;
    if(strcmp(row[j+num_col], str) == 0){
        match=1;
        return match;
    }
    return match;
}

//OUTPUT
void print(char **row){
    int j=0;
    printf("%s,%s,%s,%s;\n", row[j], row[j+1], row[j+2], row[j+3]);
}
