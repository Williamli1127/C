#include <stdio.h>
#include <stdlib.h>

struct Node{
  char value;
  int precedence;
  struct Node *next;
};

typedef struct Node Node;
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

void push(int data, int precedence){
  Stack new_node;

  new_node = (Stack)malloc(sizeof(Node));
  new_node->value = data;
  new_node->precedence = precedence;
  new_node->next = top;
  top = new_node;
}

char pop(){
  Stack ptr;
  char temp;
  if(isEmpty()){
    printf("Stack is empty!");
    return '0';
  }
  else{
    ptr = top;
    temp = ptr->value;
    top = top->next;
    printf("%c",temp);
    free(ptr);
    return temp;
  }
}

void Infix_Postfix(){

}


int main(){
  char input[1000000];
  int i=0,input_precendence=-1;
  float answer;
  top->precedence = 0;

  while(1){
    printf("\nPlease Enter your culculation:\n\n");
    scanf(" %c",&input[i]);
    if(input[i] >= '0'&&input[i] <= '9'){
      printf("%d",input[i]-48);
    }
    else if(input[i] == ' '){}
    else if(input[i] == '*' || input[i] =='\\' || input[i] == '+' || input[i] == '-'){
      if(input[i] == '*' || input[i] =='\\'){input_precendence = 1;}
      else if(input[i] == '+' || input[i] == '-'){input_precendence =0;}
      printf("%d",top->precedence);
      // printf("Now precedence is %d\n",input_precendence);
      // while(top->precedence >= input_precendence){
        // printf("!!!!\n\n");
      // }
      //   pop();}
      // push(input[i], input_precendence);
    }

    i++;
    if(input[i] == 'o'){break;} // How to end Undecided!!
  }

  return 0;
}


//Refference

// https://lakesd6531.pixnet.net/blog/post/332858496
