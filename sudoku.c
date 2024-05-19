#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   for (int row = 0; row < 9; row++) {
        int rowCheck[10] = {0};
        int colCheck[10] = {0};
        for (int col = 0; col < 9; col++) {
      
            if (n->sudo[row][col] != 0) {
                if (rowCheck[n->sudo[row][col]] == 1) return 0;
                rowCheck[n->sudo[row][col]] = 1;
            }
            
            if (n->sudo[col][row] != 0) {
                if (colCheck[n->sudo[col][row]] == 1) return 0;
                colCheck[n->sudo[col][row]] = 1;
            }
        }
    }
    
    for (int startRow = 0; startRow < 9; startRow += 3) {
        for (int startCol = 0; startCol < 9; startCol += 3) {
            int gridCheck[10] = {0};
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    int num = n->sudo[startRow + row][startCol + col];
                    if (num != 0) {
                        if (gridCheck[num] == 1) return 0;
                        gridCheck[num] = 1;
                    }
                }
            }
        }
    }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list = createList();

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (n->sudo[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    n->sudo[row][col] = num;
                    if (is_valid(n)) {
                        Node* newNode = copy(n);
                        pushBack(list, newNode);
                    }
                }
                n->sudo[row][col] = 0; 
                return list; 
            }
        }
    }

    return list;
}


int is_final(Node* n){
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (n->sudo[row][col] == 0) return 0;
        }
    }
    return is_valid(n);
}

Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
    push(stack, initial);

    while (!is_empty(stack)) {
        Node* current = pop(stack);
        (*cont)++;

        if (is_final(current)) {
            return current;
        }

        List* adjNodes = get_adj_nodes(current);
        ListNode* adjNode = first(adjNodes);
        while (adjNode) {
            push(stack, adjNode->data);
            adjNode = next(adjNodes);
        }

        destroyList(adjNodes);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    Node* initial = read_file("s12a.txt");

    int cont = 0;
    Node* final = DFS(initial, &cont);
    printf("iterations: %d\n", cont);
    print_node(final);

    return 0;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/