#include <stdio.h>
#define N 100

typedef struct {
    int codigo, idade, status;   // status: 1 = disponivel, 0 = nao
    float peso;
} Boi;

int buscar(Boi b[], int n, int cod) {
    for (int i = 0; i < n; i++)
        if (b[i].codigo == cod) return i;
    return -1;
}

void cadastrar(Boi b[], int *n) {
    if (*n == N) { printf("Cadastro cheio!\n"); return; }
    printf("Codigo: ");      scanf("%d", &b[*n].codigo);
    printf("Peso: ");        scanf("%f", &b[*n].peso);
    printf("Idade (meses): "); scanf("%d", &b[*n].idade);
    printf("Disponivel para venda? (1-sim 0-nao): ");
    scanf("%d", &b[*n].status);
    (*n)++;
}

void mostrar(Boi x) {
    printf("%d | %.1f kg | %d meses | %s\n", x.codigo, x.peso, x.idade,
           x.status ? "a venda" : "fora de venda");
}

float mediaPeso(Boi b[], int n, int status) {
    float soma = 0; int cont = 0;
    for (int i = 0; i < n; i++)
        if (b[i].status == status) { soma += b[i].peso; cont++; }
    return cont == 0 ? 0 : soma / cont;
}

int main() {
    Boi b[N];
    int n = 0, cod, pos, st;
    float media;
    char op;

    do {
        printf("\na-Cadastrar b-Listar c-Listar por status d-Media por status\n"
               "e-Pôr a venda f-Retirar de venda g-Atualizar h-Acima da media i-Sair\n");
        scanf(" %c", &op);

        switch (op) {
        case 'a': cadastrar(b, &n); break;
        case 'b':
            for (int i = 0; i < n; i++) mostrar(b[i]);
            break;
        case 'c':
            printf("Status (1-a venda 0-fora): "); scanf("%d", &st);
            for (int i = 0; i < n; i++)
                if (b[i].status == st) mostrar(b[i]);
            break;
        case 'd':
            printf("Status (1-a venda 0-fora): "); scanf("%d", &st);
            printf("Media de pesos: %.2f kg\n", mediaPeso(b, n, st));
            break;
        case 'e': case 'f': case 'g':
            printf("Codigo: "); scanf("%d", &cod);
            pos = buscar(b, n, cod);
            if (pos == -1) { printf("Nao encontrado!\n"); break; }
            if (op == 'e') b[pos].status = 1;
            else if (op == 'f') b[pos].status = 0;
            else {
                printf("Novo peso: ");  scanf("%f", &b[pos].peso);
                printf("Nova idade: "); scanf("%d", &b[pos].idade);
            }
            break;
        case 'h':
            media = mediaPeso(b, n, 1);
            for (int i = 0; i < n; i++)
                if (b[i].status == 0 && b[i].peso > media) mostrar(b[i]);
            break;
        }
    } while (op != 'i');
    return 0;
}
