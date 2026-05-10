//natanielly ricardo amorim


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define menu_2          0
#define AUX_OFFSET      ( menu_2 + sizeof ( int ) )
#define CABECA_OFFSET   ( AUX_OFFSET + sizeof ( int ) )
#define BUFFER_MIN_SIZE ( CABECA_OFFSET + sizeof ( void* ) )

#define TAM_NOME  50
#define TAM_EMAIL 50

#define OFFSET_NOME      0
#define OFFSET_IDADE     ( OFFSET_NOME + TAM_NOME )
#define OFFSET_EMAIL     ( OFFSET_IDADE + sizeof ( int ) )
#define OFFSET_PROX      ( OFFSET_EMAIL + TAM_EMAIL )
#define TAM_NO           ( OFFSET_PROX + sizeof ( void* ) )

void insere(void *pBuffer) {

    void *novoNo = malloc ( TAM_NO );

    printf("Nome: ");
    scanf(" %49s", (char*)novoNo + OFFSET_NOME);

    printf("Idade: ");
    scanf("%d", (int*)((char*)novoNo + OFFSET_IDADE));

    printf("Email: ");
    scanf(" %49s", (char*)novoNo + OFFSET_EMAIL);

    *( void ** ) ( ( char* ) novoNo + OFFSET_PROX ) = *( void ** ) ( ( char* ) pBuffer + CABECA_OFFSET );

    *( void ** ) ( ( char* ) pBuffer + CABECA_OFFSET ) = novoNo;
}

void listar ( void *pBuffer ) {

    void *no = *( void ** ) ( ( char* ) pBuffer + CABECA_OFFSET );

    while ( no != NULL ) {

        printf("Nome: %s\n", (char*)no + OFFSET_NOME);
        printf("Idade: %d\n", *(int*)((char*)no + OFFSET_IDADE));
        printf("Email: %s\n\n", (char*)no + OFFSET_EMAIL);

        no = *( void ** ) ( ( char* ) no + OFFSET_PROX );
    }
}

void remover ( void *pBuffer ) {

    char nomeBusca[TAM_NOME];
    printf("Digite o nome da pessoa a remover: ");
    scanf(" %49s", nomeBusca);

    void **cabeca = ( void ** ) ( ( char* ) pBuffer + CABECA_OFFSET );
    void *atual = *cabeca;
    void *anterior = NULL;

    while ( atual && strcmp ( ( char* ) atual + OFFSET_NOME, nomeBusca ) != 0 ) {
        anterior = atual;
        atual = *( void ** ) ( ( char* )atual + OFFSET_PROX );
    }

    if ( !atual ) {
        printf("pessoa não encontrada.\n");
        return;
    }

    if ( !anterior )
        *cabeca = *( void ** ) ( ( char* ) atual + OFFSET_PROX );
    else
        *( void ** ) ( ( char* ) anterior + OFFSET_PROX ) = *( void ** ) ( ( char* ) atual + OFFSET_PROX );

    free ( atual );
    printf("removido\n");
}

void buscar( void *pBuffer ) {

    char nomeBusca [ TAM_NOME ];
    printf("Digite o nome da pessoa: ");
    scanf(" %49s", nomeBusca);

    void *atual = *( void ** ) ( ( char* ) pBuffer + CABECA_OFFSET );

    while (atual) {
        if ( strcmp ( ( char* ) atual + OFFSET_NOME, nomeBusca ) == 0 ) {
            printf("Nome: %s\n", (char*)atual + OFFSET_NOME);
            printf("Idade: %d\n", *(int*)((char*)atual + OFFSET_IDADE));
            printf("Email: %s\n", (char*)atual + OFFSET_EMAIL);
            return;
        }

        atual = *( void ** ) ( ( char* ) atual + OFFSET_PROX );
    }

    printf("pessoa não encontrada\n");
}

void liberarLista( void *pBuffer ) {

    void *no = *( void ** ) ( ( char* ) pBuffer + CABECA_OFFSET );
    void *prox;

    while (no) {
        prox = * ( void ** ) ( ( char* ) no + OFFSET_PROX );
        free ( no );
        no = prox;
    }
}

void menu ( void *pBuffer ) {

    printf("\n-- MENU:\n");
    printf(" 1. Adicionar pessoa\n");
    printf(" 2. Remover pessoa\n");
    printf(" 3. Buscar pessoa\n");
    printf(" 4. Listar todos\n");
    printf(" 5. Sair\n");
    printf("-- Digite sua escolha: ");

    scanf("%d", (int*)((char*)pBuffer + menu_2));
}

int main() {

    void *pBuffer = malloc ( BUFFER_MIN_SIZE );

    *( void ** ) ( ( char* ) pBuffer + CABECA_OFFSET ) = NULL;

    do {
        menu(pBuffer);

        switch ( * ( int* ) ( ( char* ) pBuffer + menu_2 ) ) {

            case 1: 
				insere(pBuffer); 
                break;
            case 2: 
                remover(pBuffer); 
                break;
            case 3: 
                buscar(pBuffer); 
                break;
            case 4: 
                listar(pBuffer); 
                break;
            case 5:
                printf("Saindo\n");
                break;
        }

    } while ( * ( int* ) ( ( char* ) pBuffer + menu_2 ) != 5) ;

    liberarLista ( pBuffer );
    free ( pBuffer );
    return 0;
}
