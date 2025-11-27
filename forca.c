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
char palavrasecreta[TAMANHO_PALAVRA];
    
//armazena as letras que foram chutadas
char chutes[26];


void abertura(){
    printf("*****************\n");
    printf("* Jogo de Forca *\n");
    printf("*****************\n\n");
}

void chuta() {
    char chute;
    printf("Digite a letra: ");
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
    //retorna true caso >= 5, false caso contrario
    return chuteserrados() >= 6;
}

int chuteserrados(){
    int erros = 0;

    for(int i = 0; i < chutesdados; i++){
        //int existe = jachutou(palavrasecreta[i]);

        int existe = 0;

        for(int j = 0; j < strlen(palavrasecreta); j++){
            if(chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }

        if(!existe) erros++;
    }

    return erros;
}

void desenhaforca() {

    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >=1 ? '(' : ' '), (erros >=1 ? '_' : ' '), (erros >=1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >=3 ? '\\' : ' '), (erros >=2 ? '|' : ' '), (erros >=4 ? '/' : ' '));
    printf(" |       %c     \n", (erros >=2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >=5 ? '/' : ' '), (erros >=6 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");


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

        char novapalavra[TAMANHO_PALAVRA];
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

    if(acertou()){
        printf("\n\n");
        printf(" =========================================  \n");
        printf("               .-=========-.               \n");
        printf("               \\'-=======-'/               \n");
        printf("               _|   .=.   |_               \n");
        printf("              ((|  {{1}}  |))              \n");
        printf("               \\|   /|\\   |/               \n");
        printf("                \\__ '`' __/                \n");
        printf("                  _`) (`_                  \n");
        printf("                _/_______\\_                \n");
        printf("               /___________\\               \n");
        printf(" =========================================  \n");
        printf("\n        PARABêNS!! VOC“ GANHOU!!!!         \n");
        printf("         A PALAVRA ERA: %s           \n\n", palavrasecreta);
        printf(" =========================================  \n");
    }
    else {
        printf("\n\n");
        printf(" ================================================  \n");
        printf("                       ______ \n");
        printf("                    .-'      '-. \n");
        printf("                   /            \\ \n");
        printf("       _          |              |          _ \n");
        printf("      ( \\         |,  .-.  .-.  ,|         / ) \n");
        printf("       > '=._     | )(__/  \\__)( |     _.=' < \n");
        printf("      (_/'=._'=._ |/     /\\     \\| _.='_.='\\_) \n");
        printf("             '=._ (_     ^^     _)'_.=' \n");
        printf("                 '=\\__|IIIIII|__/=' \n");
        printf("                _.='| \\IIIIII/ |''=._ \n");
        printf("      _     _.='_.='\\          /'=._'=._     _ \n");
        printf("     ( \\_.='_.='     `--------`     '=._'=._/ ) \n");
        printf("      > _.='                            '=._ < \n");
        printf("     (_/                                    \\_) \n");
        printf(" ================================================  \n");
        printf("\n                  FOI DE BASE D:                \n");
        printf("               A PALAVRA ERA: %s                \n\n", palavrasecreta);
        printf(" ================================================ \n");
    }

    adicionapalavra();
}