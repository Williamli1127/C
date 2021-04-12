#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"


//Ref
// https://zh.wikipedia.org/wiki/%E5%BC%82%E6%88%96%E9%93%BE%E8%A1%A8
// https://www.techiedelight.com/xor-linked-list-overview-implementation-c-cpp/

typedef struct Node
{
    int value;
    struct Node* link;
}Node;

typedef struct Node* track;

track XOR(track x, track y) {
    return (track)((uintptr_t)(x) ^ (uintptr_t)(y));
}

void show_track(track whichone){
  if(whichone == NULL){printf("\n");return;}
  track current = whichone;
  track previous = NULL;
  track next;

  while(current!=NULL){
    printf("%d ",current->value);
    next = XOR(previous,current->link);
    previous = current;
    current = next;
  }
  printf("\n");
}

void enter(Node** which_train,int label){
  track new_node = (track)malloc(sizeof(Node));
  new_node ->value = label;
  new_node ->link = *which_train;

  if(*which_train!=NULL){
    (*which_train)->link = XOR(new_node,(*which_train)->link);
  }

  *which_train = new_node;
}

int leave(Node** which_train){
  if((*which_train)==NULL){return 1;}
  if(!(*which_train)){
    return 1;
  }
  int data = (*which_train)->value;
  track temp = (*which_train)->link;
  if(temp){
    temp->link = XOR((*which_train),temp->link);
  }
  free(*which_train);
  *which_train = temp;
  return data;
}

int isemptytrack(Node** which_train){
  if((*which_train)==NULL){return 0;}
  else{return 1;}
}

void migrate(Node** A_train,Node** B_train){
  if((*A_train)==NULL){return;}
  else if((*B_train)==NULL){
    (*B_train) = (*A_train);
    Node *current = *B_train;
    Node *previous = NULL;
    Node *next;
    while(current!=NULL){
      // printf("%d ",current->value);
      next = XOR(previous,current->link);
      previous = current;
      current = next;
    } // previous == last && current == NULL
    *B_train = previous;
    (*A_train) = NULL;}

  else{
    Node *current = *A_train;
    Node *previous = NULL;
    Node *next;

    while(current!=NULL){
    // printf("%d ",current->value);
    next = XOR(previous,current->link);
    previous = current;
    current = next;
    } // previous == last && current == NULL

    (*B_train)->link = XOR((*A_train),XOR(NULL,(*B_train)->link));
    (*A_train)->link = XOR((*B_train),XOR(NULL,(*A_train)->link));

    *B_train = previous;
    (*A_train) = NULL;
  }
}

void output(Node* target){
  if(target==NULL){printf("\n");return;}
  Node *current = target;
  Node *previous = NULL;
  Node *next;

  while(current!=NULL){
    // printf("%d ",current->value);
    next = XOR(previous,current->link);
    previous = current;
    current = next;
  } // previous == last && current == NULL

  while(previous!=NULL){
    printf("%d ",previous->value);
    next = XOR(current,previous->link);
    current = previous;
    previous = next;
  }

  printf("\n");
}


int main(){
  int k,n,r,l,r_a,r_b;
  char input[10];
  scanf("%d %d",&k,&n);
  track *rails = (track*)malloc(sizeof(track)*k);
  for(int i=0;i<k;i++){rails[i] = NULL;}

  for(int i=0;i<n;i++){
    scanf("%s",input);
    if(strcmp(input,"enter") == 0){
      scanf("%d %d",&r,&l);
      enter(&rails[r],l);
    }
    else if(strcmp(input,"leave") == 0){
      scanf("%d",&r);
      leave(&rails[r]);
      // printf("\n~~%d\n",leave(&rails[r]));
    }
    else if(strcmp(input,"migrate") == 0){
      scanf("%d %d",&r_a,&r_b);
      migrate(&rails[r_a],&rails[r_b]);
      // printf("\nNow is the real shit\n");
      // show_track(rails[r_a]);
      // show_track(rails[r_b]);

    }
  }
  for(int i=0;i<k;i++){output(rails[i]);}
  // for(int i=0;i<k;i++){show_track(rails[i]);}
  return 0;
}
