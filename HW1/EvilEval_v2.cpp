#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct Node{
  char value;
  double precedence;
  struct Node *next;
}Node;

typedef Node *Stack;
Stack top = NULL;
Stack top_eva = NULL;

int isEmpty(){
  if(top==NULL){
    return 1;
  }
  else{
    return 0;
  }
}

void push(char data, int precedence){
  Stack new_node;

  new_node = (Stack)malloc(sizeof(Node));
  new_node->value = data;
  new_node->precedence = precedence;
  new_node->next = top;
  top = new_node;
}

void push_number(double data){
    Stack new_node;

    new_node = (Stack)malloc(sizeof(Node));
    new_node->precedence = data;
    new_node->next = top_eva;
    top_eva = new_node;
}

double pop_number(){
  Stack ptr;
  double temp;

  ptr = top_eva;
  temp = ptr->precedence;
  top_eva = top_eva->next;
  free(ptr);
  return temp;
}

char pop(){
  Stack ptr;
  char temp;
  if(isEmpty()){
    // printf("Stack is empty!");
    return '0';
  }
  else{
    ptr = top;
    temp = ptr->value;
    top = top->next;
    // printf("%c",temp);
    free(ptr);
    return temp;
  }
}

char* Infix_Postfix(){
  char input[1000000],*output;
  int input_precendence,j=0;
  push('_',-10);
  scanf("%s",input);
  int length = strlen(input);
  output = (char*)malloc(sizeof(char)*length);

  for(int i=0;i<length;i++){
    // printf("\nNow it is : %d round\n",i+1);
    if(input[i] >= '0'&&input[i] <= '9'){
      // printf("%d",input[i]-48);
      output[j] = input[i];
      // printf("\nThis is %d place in output : %c\n",j+1,output[j]);
      j++;
    }
    else if(input[i] == '*' || input[i] =='/' || input[i] == '+' || input[i] == '-'){
      if(input[i] == '*' || input[i] =='/'){input_precendence = 1;}
      else if(input[i] == '+' || input[i] == '-'){input_precendence = 0;}
      while(top->precedence >= input_precendence){
        output[j] = pop();
        // printf("\nThis is %d place in output : %c\n",j+1,output[j]);
        if(j<length){j++;}
        }
      push(input[i],input_precendence);
    }
    else if(input[i] =='('){push('(',-20);}
    else if(input[i] ==')'){
      while(top->value != '('){
      output[j] = pop();
      // printf("\nThis is %d place in output : %c\n",j+1,output[j]);
      if(j<length){j++;}}
    }

    if(i==length-1){
      // printf("\nLast Round\n");
      while (top->value!='_') {
        if(top->value == '('){}
        output[j] = pop();
        // printf("\nThis is %d place in output : %c\n",j+1,output[j]);1+3
        if(j<length){j++;}
      }
    }
  }
  return output;
}

void Postfix_Evaluation(){
  char *input;
  int length;
  double answer;
  // int length = strlen

  input = Infix_Postfix();

  length = strlen(input);
  // printf("%s and length is : %d\n",input,length);

  double front,back;
  for(int i=0;i<length;i++){
    if(input[i] >= '0'&&input[i] <= '9'){push_number(input[i]-'0');}
    else if(input[i] == '*' || input[i] =='/' || input[i] == '+' || input[i] == '-'){
      back = pop_number()+0.0;
      front = pop_number()+0.0;
      // printf("\nBack is : %0.15f\nFront is : %0.15f\n",back,front);
      if(input[i] == '*'){answer = back * front;}
      else if(input[i] == '/'){answer = front / back;}    //除法小數可能有問題
      else if(input[i] == '+'){answer = back + front;}
      else if(input[i] == '-'){answer = front - back;}
      push_number(answer);
    }
  }

  printf("%0.15f\n",answer);
}

int main(){
  Postfix_Evaluation();






  return 0;
}


//Refference

// https://lakesd6531.pixnet.net/blog/post/332858496

//Problems
  //1.除法小數
  //2.Parentheses
  //3.輸入的T是多少
