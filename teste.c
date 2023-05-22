#include <stdio.h>
#include <stdlib.h>

#define NUM_MISSIONARIES 3
#define NUM_CANNIBALS 3

// Estrutura para representar o estado do problema
typedef struct {
    int missionaries_left;  // número de missionários na margem esquerda
    int cannibals_left;     // número de canibais na margem esquerda
    int boat;               // 1 se o barco estiver na margem esquerda, 0 caso contrário
} State;

// Verifica se o estado é válido de acordo com as regras do problema
int is_valid_state(const State* state) {
    // Verifica se há mais canibais do que missionários em qualquer margem
    if ((state->missionaries_left > 0 && state->missionaries_left < state->cannibals_left) ||
        (NUM_MISSIONARIES - state->missionaries_left > 0 &&
         NUM_MISSIONARIES - state->missionaries_left < NUM_CANNIBALS - state->cannibals_left)) {
        return 0;  // Estado inválido
    }
    return 1;  // Estado válido
}

// Verifica se o estado é o estado final do problema
int is_goal_state(const State* state) {
    return (state->missionaries_left == 0 && state->cannibals_left == 0 && state->boat == 0);
}

// Função para imprimir o estado
void print_state(const State* state) {
    printf("Missionarios na margem esquerda: %d\n", state->missionaries_left);
    printf("Canibais na margem esquerda: %d\n", state->cannibals_left);
    if (state->boat) {
        printf("Barco na margem esquerda\n");
    } else {
        printf("Barco na margem direita\n");
    }
    printf("\n");
}

// Estrutura para representar um nó do grafo
typedef struct {
    State* state;           // Estado do problema
    struct Node* parent;    // Nó pai
} Node;

// Função para criar um novo nó
Node* create_node(const State* state, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->state = (State*)malloc(sizeof(State));
    *(node->state) = *state;
    node->parent = parent;
    return node;
}

// Função para verificar se um estado já foi visitado
int is_visited(const State* state, const Node** visited, int num_visited) {
    for (int i = 0; i < num_visited; i++) {
        if (state->missionaries_left == visited[i]->state->missionaries_left &&
            state->cannibals_left == visited[i]->state->cannibals_left &&
            state->boat == visited[i]->state->boat) {
            return 1;  // Estado já visitado
        }
    }
    return 0;  // Estado não visitado
}

void bfs() {
    Node** queue = (Node**)malloc(sizeof(Node*) * 1000);  // Fila para a busca em largura
    int front = 0;  // Índice da frente da fila
    int rear = 0;   // Índice da parte traseira da fila

    // Estado inicial
    State initial_state = {NUM_MISSIONARIES, NUM_CANNIBALS, 1};
    Node* initial_node = create_node(&initial_state, NULL);

    queue[rear++] = initial_node;  // Insere o nó inicial na fila

    Node** visited = (Node**)malloc(sizeof(Node*) * 1000);  // Array para rastrear estados visitados
    int num_visited = 0;  // Número de estados visitados

    while (front < rear) {
        Node* current_node = queue[front++];  // Remove o nó da frente da fila

        const State* current_state = current_node->state;

        // Verifica se é o estado final
        if (is_goal_state(current_state)) {
            // Imprime a sequência de estados
            while (current_node != NULL) {
                print_state(current_node->state);
                current_node = current_node->parent;
            }
            break;
        }

        // Gera todos os possíveis estados vizinhos
        for (int i = 0; i <= current_state->missionaries_left; i++) {
            for (int j = 0; j <= current_state->cannibals_left; j++) {
                // Gera o próximo estado
                State next_state = {
                    current_state->missionaries_left - i,
                    current_state->cannibals_left - j,
                    !current_state->boat
                };

                // Verifica se o próximo estado é válido e não foi visitado
                if (is_valid_state(&next_state) && !is_visited(&next_state, visited, num_visited)) {
                    Node* next_node = create_node(&next_state, current_node);
                    queue[rear++] = next_node;  // Insere o próximo nó na fila
                    visited[num_visited++] = next_node;  // Marca o próximo estado como visitado
                }
            }
        }
    }

    // Libera a memória alocada
    for (int i = 0; i < rear; i++) {
        free(queue[i]->state);
        free(queue[i]);
    }
    free(queue);
    free(visited);
}

int main() {
bfs(); // Executa a busca em largura
return 0;
}