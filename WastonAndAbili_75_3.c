#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"


//Ref
// https://zh.wikipedia.org/wiki/%E5%BC%82%E6%88%96%E9%93%BE%E8%A1%A8
// https://www.techiedelight.com/xor-linked-list-overview-implementation-c-cpp/
// https://www.geeksforgeeks.org/xor-linked-list-reversal-of-a-list/

typedef struct Node
{
    int value;
    struct Node* link;
}Node;

typedef struct First_train{
    int value;
    struct Node* link;
}first;

typedef struct Node* track;

track XOR(track x, track y) {
    return (track)((uintptr_t)(x) ^ (uintptr_t)(y));
}

void show_track(track whichone,Node* first){
  if(whichone == NULL){printf("\n");return;}
  track current = whichone;
  track top = first;
  track previous = NULL;
  track next;

  while(current!=NULL){
    printf("%d ",top->value);
    next = XOR(previous,top->link);
    printf("\n@@@%d\n",next->value);
    previous = top;
    current = next;
  }
  printf("\n");
}

void enter(Node** which_train,int label,int which_track,Node** first){
  track new_node = (track)malloc(sizeof(Node));
  track new_node_first = (track)malloc(sizeof(Node));

  new_node ->value = label;
  new_node ->link = *which_train;

  new_node_first ->value = label;
  new_node_first ->link = *which_train;

  if(*which_train==NULL){
    *which_train = new_node;
    *first = new_node_first;
    return;
  }
  if(*which_train!=NULL){
    (*which_train)->link = XOR(new_node,(*which_train)->link);
  }
  *which_train = new_node;

}

int leave(Node** which_train,Node **first){
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


Node* reverse(Node** head,Node* first){
  if((*head)==NULL){return NULL;}
  else if(first!=NULL){
    // printf("\n!!%d\n",first->value);
    return first;
    }
  // else{
  //   Node* previous = NULL;
  //   Node* next;
  //   while(XOR(previous,current->link)!=NULL){
  //     next = XOR(previous,current->link);
  //     previous = current;
  //     current = next;
  //   }
  //   *head = current;
  //   return *head;
  // }
}

void migrate(Node** A_train,Node** B_train,Node* first_a,Node* first_b){
  if((*A_train)==NULL){return;}
  else if((*B_train)==NULL){
    reverse(A_train,first_a);
    (*B_train) = (*A_train);
    (*A_train) = NULL;
  }
  else{
    reverse(A_train,first_a);
    Node *current = *A_train;
    Node *previous = NULL;
    Node *next;
    printf("\nReversing~~\n");
    while(current!=NULL){
    printf("%d ",current->value);
    next = XOR(previous,current->link);
    previous = current;
    current = next;
    } // previous == last && current == NULL

    (*B_train)->link = XOR(previous,XOR(NULL,(*B_train)->link));
    previous->link = XOR((*B_train),XOR(NULL,previous->link));

    *B_train = *A_train;
    (*A_train) = NULL;
  }
}

void output(Node* target,int which_track,Node** first){
  if(target==NULL){printf("\n");return;}
  Node *temp;
  reverse(&target,first[which_track]);
  show_track(target,first[which_track]);
}



int main(){
  int k,n,r,l,r_a,r_b;
  char input[10];
  scanf("%d %d",&k,&n);
  track *rails = (track*)malloc(sizeof(track)*k);
  track *first = (track*)malloc(sizeof(track)*k);
  for(int i=0;i<k;i++){rails[i] = NULL;first[i]=NULL;}

  for(int i=0;i<n;i++){
    scanf("%s",input);
    if(strcmp(input,"enter") == 0){
      scanf("%d %d",&r,&l);
      enter(&rails[r],l,r,&first[r]);
    }
    else if(strcmp(input,"leave") == 0){
      scanf("%d",&r);
      leave(&rails[r],&first[r]);
      // printf("\n~~%d\n",leave(&rails[r]));
    }
    else if(strcmp(input,"migrate") == 0){
      scanf("%d %d",&r_a,&r_b);
      migrate(&rails[r_a],&rails[r_b],first[r_a],first[r_b]);
      // printf("\nNow is the real shit\n");
      // show_track(rails[r_a]);
      // show_track(rails[r_b]);
    }
    else if(strcmp(input,"reverse")==0){
      scanf("%d",&r);
      show_track(reverse(&rails[r],first[r]),first[r]);
    }
  }
  for(int i=0;i<k;i++){output(rails[i],i,&first[i]);}
  // for(int i=0;i<k;i++){show_track(rails[i]);}
  return 0;
}
