#include <stdio.h>
#include <string.h>

/* SOBRE PONTEIROS 
-> & aponta onde a var ta na memoria, te da o endereco que essa var
-> * acessa o conteudo dentro do ponteiro, entra no endereco passado
*/


/*variaveis globais*/
int tentativas = 0;
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

    chutes[tentativas] = chute;
    tentativas++;
}

int jachutou(char letra){
    int achou = 0;

    for (int j = 0; j < tentativas; j++){
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    
    return achou;
}

void desenhaforca(){
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

void escolhepalavra(){
    sprintf(palavrasecreta, "MELANCIA");
}

int main (){  
    int acertou = 0;
    int enforcou = 0;

    escolhepalavra();
    abertura();

    do {

        // imprime a palavra secreta
        desenhaforca();

        // captura um chute
        chuta();

    } while (!acertou && !enforcou);

}