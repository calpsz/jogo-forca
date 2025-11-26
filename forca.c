#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

/* SOBRE PONTEIROS 
-> & aponta onde a var ta na memoria, te da o endereco que essa var
-> * acessa o conteudo dentro do ponteiro, entra no endereco passado
*/


/*variaveis globais*/
int chutesdados = 0;
char palavrasecreta[20];
    
//armazena as letras que foram chutadas
char chutes[26];


void abertura(){
    printf("*****************\n");
    printf("* Jogo de Forca *\n");
    printf("*****************\n\n");
}

void chuta() {
    char chute;
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra){
    int achou = 0;

    for (int j = 0; j < chutesdados; j++){
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    
    return achou;
}

int acertou() {
    for(int i = 0; i < strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}

int enforcou() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++){
        int existe = jachutou(palavrasecreta[i]);


        if(!existe) erros++;
    }

    //retorna true caso >= 5, false caso contrario
    return erros >= 5;
}

void desenhaforca() {
    for(int i = 0; i < strlen(palavrasecreta); i++){

        // a letra ja foi chutada?
        int achou = jachutou(palavrasecreta[i]);
        
        if(achou){
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
        
    }
    printf("\n");
}

void adicionapalavra(){

    char quer;

    printf("Deseja adicionar uma nova palavra no banco de dados? (S/N)\n");
    scanf(" %c", &quer);

    if(quer == 'S'){

        char novapalavra[20];
        printf("Digite a nova palavra: ");
        scanf("%s", novapalavra);

        FILE* f;

        // r+ -> vai ler e escrever no arquivo
        f = fopen("palavras.txt", "r+");
        if(f == 0){
            printf("Desculpe, banco de dados n∆o dispon°vel :(\n\n");
            exit(1);
        }

        int qntd;
        fscanf(f, "%d", &qntd);
        qntd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qntd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }

    printf("\nObrigada por jogar! <3\n");
}

void escolhepalavra(){
    //fopen devolve pra gente um ponteiro do arquivo, por isso tem que colocar numa var ponteiro
    FILE* f = fopen("palavras.txt", "r");

    if(f == 0){
        printf("Desculpe, banco de dados n∆o dispon°vel :(\n\n");
        exit(1);
    }

    int qntdpalavras;
    fscanf(f, "%d", &qntdpalavras);

    srand(time(0));
    int randomico = rand() % qntdpalavras;

    for (int i = 0; i <= randomico; i++){
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

int main (){  

    escolhepalavra();
    abertura();

    do {

        // imprime a palavra secreta
        desenhaforca();

        // captura um chute
        chuta();

    } while (!acertou() && !enforcou());

    adicionapalavra();
}