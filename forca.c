#include <stdio.h>
#include <string.h>

/* SOBRE PONTEIROS 
-> & aponta onde a var ta na memoria, te da o endereco que essa var
-> * acessa o conteudo dentro do ponteiro, entra no endereco passado
*/

void abertura(){
    printf("*****************\n");
    printf("* Jogo de Forca *\n");
    printf("*****************\n\n");
}

void chuta(char chutes[26], int* tentativas) {
    char chute;
    scanf(" %c", &chute);

    chutes[*tentativas] = chute;
    (*tentativas)++;
}

int jachutou(char letra, char chutes[26], int tentativas){
    int achou = 0;

    for (int j = 0; j < tentativas; j++){
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    
    return achou;
}

void desenhaforca(char palavrasecreta[20], char chutes[26], int tentativas){
    for(int i = 0; i < strlen(palavrasecreta); i++){

        // a letra ja foi chutada?
        int achou = jachutou(palavrasecreta[i], chutes, tentativas);
        
        if(achou){
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
        
    }
    printf("\n");
}

void escolhepalavra(char palavrasecreta[20]){
    sprintf(palavrasecreta, "MELANCIA");
}

int main (){
    char palavrasecreta[20];

    int acertou = 0;
    int enforcou = 0;

    //armazena as letras que foram chutadas
    char chutes[26];

    int tentativas = 0;
    
    escolhepalavra(palavrasecreta);
    abertura();

    do {

        // imprime a palavra secreta
        desenhaforca(palavrasecreta, chutes, tentativas);

        // captura um chute
        chuta(chutes, &tentativas);

    } while (!acertou && !enforcou);

}