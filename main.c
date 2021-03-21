#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//DIMENSIONI DEL FILE
#define ROW 3
#define COL 4

#define lung_parola 10 //caratteri che compongono una parola
#define BUFF 1024  //lunghezza della riga del fila

//PROTOTIPI
char **definizione_Row(void);
void ricerca(char **row, char *buffer, FILE *fp, const char *argv[]);
char *eliminaSeparatori(char *buffer);
int lettura_colonna_ricerca(const char *argv[]);
char *lettura_parola_ricerca(const char *argv[]);
int matching(int num_col, char *str, char **row);
void stampa(char **row);

int main(int argc, const char * argv[]) {
    
    /* APERTURA FILE */
    FILE *fp = fopen(argv[1], "r");
    
    char **row =  definizione_Row();
    
    char *buffer = malloc(BUFF * sizeof(char));
    
    ricerca(row, buffer, fp, argv);
   
    fclose(fp);
    
    return 0;
}

char **definizione_Row(){
    char **row;
    row = malloc(COL * sizeof(char *));
    for(int i = 0; i<COL; i++)
        row[i] = malloc(lung_parola * sizeof(char));
    
    return row;
}

void ricerca(char **row, char *buffer, FILE *fp, const char *argv[]){
    int j=0, match=0;
    while( fscanf(fp, "%s", buffer) != EOF){
        //Eliminazione separatori: virgole e punti e virgole
        buffer = eliminaSeparatori(buffer);

        sscanf(buffer, "%s %s %s %s", row[j], row[j+1], row[j+2], row[j+3]);

        int num_col = lettura_colonna_ricerca(argv);
        char *str = lettura_parola_ricerca(argv);
        
        match = matching(num_col, str, row);
        
        if(match==1)
            stampa(row);
    }
    
    if(match==0)
        printf("Nessuna corrispondenza trovata\n");
}

char *eliminaSeparatori(char *buffer){
    for(int i=0; i< BUFF; i++){
        if(buffer[i] == ',')
            buffer[i] = ' ';
        if(buffer[i] == ';')
            buffer[i] = '\n';
    }

    return buffer;
}

int lettura_colonna_ricerca(const char *argv[]){
    int num_col = atoi(argv[2]);
    return num_col;
}

char *lettura_parola_ricerca(const char *argv[]){
    char *str = malloc(lung_parola * sizeof(char));
    strcpy(str, argv[3]);
    return str;
}

int matching(int num_col, char *str, char **row){
    int j=0, match=0;
    if(strcmp(row[j+num_col], str) == 0){
        match=1;
        return match;
    }
    return match;
}

void stampa(char **row){
    int j=0;
    printf("%s,%s,%s,%s;\n", row[j], row[j+1], row[j+2], row[j+3]);
}
