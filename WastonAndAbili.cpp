#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct Node{
  int value;
  struct Node *next;
}node;

typedef Node *Stack;
Stack top = NULL;

int isEmpty(){
  if(top==NULL){
    return 1;
  }
  else{
    return 0;
  }
}

void push(char data){
  Stack new_node;

  new_node = (Stack)malloc(sizeof(Node));
  new_node->value = data;
  new_node->next = top;
  top = new_node;
}

char pop(Stack WhichRail){
  printf("\nNow\n");
  Stack ptr;
  char temp;
  printf("\nNow we pop : \n");
  ptr = WhichRail;
  temp = ptr->value;
  top = top->next;
  printf("%c",temp);
  free(ptr);
  return temp;

}

void Enter(int line,int label,Stack **rails){
  Stack new_node;
  new_node = (Stack)malloc(sizeof(Node));
  new_node->value = label;
  new_node->next = rails[line];
  rails[line] = new_node;

  //test pop
  // Stack ptr;
  // int temp;
  // while(rails[line]!=NULL){
  //   printf("\ntest!!\n");
  //   ptr = rails[line];
  //   temp = ptr->value;
  //   rails[line] = rails[line]->next;
  //   printf("--%d\n",temp);
  // }
  // free(ptr);


  // rails[line]->value = label;
  // rails[line] = rails[line]->next;
}

int main(){
  int k,n,r,l,r_a,r_b;
  char input[10];
  scanf("%d %d",&k,&n);

  Stack *rails = (Stack*)malloc(sizeof(Stack)*k);
  for(int i=0;i<k;i++){rails[i] = NULL;}


  for(int i=0;i<n;i++){
    scanf("%s",input);

    if(strcmp(input,"enter") == 0){
      printf("ENTER : \n");
      scanf("%d %d",&r,&l);
      Enter(r,l,&rails);
      pop(rails[r]);
    }
    else if(strcmp(input,"leave") == 0){
      printf("LEAVE :　\n");
      scanf("%d",&r);
    }
    else if(strcmp(input,"migrate") == 0){
      printf("MIGRATE : \n");
      scanf("%d %d",&r_a,&r_b);
    }

  }



  return 0;
}
