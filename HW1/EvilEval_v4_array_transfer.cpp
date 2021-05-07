#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

typedef struct Node{
  char value;
  double precedence;
  struct Node *next;
}Node;

typedef Node *Stack;
Stack top = NULL;
Stack top_eva = NULL;

// Stack stack_initial(){
//   Stack init = (Stack)malloc(sizeof(Node)*1000);
//   return init;
// }
int isEmpty(){
  if(top==NULL){
    return 1;
  }
  else{
    return 0;
  }
}

// push(Stack stack, char data, int pre){
//
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

void show_stack(){
  while(top!=NULL){
    printf("\n-->%c\n",top->value);
    top = top->next;
  }
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

char* Infix_Postfix(char *input){
  char output[1000000];
  int input_precendence,j=0;
  push('_',-10);
  int length = strlen(input);
  int HowManyTokens = length;

  for(int i=0;i<length;i++){
    if(input[i] >= '0'&&input[i] <= '9'){
      output[j] = input[i];
      j++;
    }
    else if(input[i] >= 42 && input[i]<=47){
      HowManyTokens++;
      output[j] = ',';
      j++;
      if(input[i] == '*' || input[i] =='/'){input_precendence = 1;}
      else if(input[i] == '+' || input[i] == '-'){input_precendence = 0;}
      while(top->precedence >= input_precendence){
        output[j] = pop();
        j++;
        }
      push(input[i],input_precendence);
    }
    else if(input[i] =='('){push('(',-200);HowManyTokens--;}
    else if(input[i] ==')'){
      HowManyTokens--;
      while(top->value != '('){
      output[j] = pop();
      j++;
      }
      pop();
    }

    if(i==length-1){
      while (top->value!='_') {
        if(top->value == '('){
          // continue;
        }
        output[j] = pop();
        j++;}

    }
  }

  char *transfer = (char*)malloc(sizeof(char)*HowManyTokens);
  transfer[0] = HowManyTokens;
  for(int i=0;i<HowManyTokens;i++){transfer[i+1]=output[i];}
  return transfer;
}

void Postfix_Evaluation(char *input_main){
  char *input;
  int temp=0,sum=0;
  double answer;

  input = Infix_Postfix(input_main);

  int HowManyTokens = input[0];
  for(int i=1;i<=HowManyTokens;i++){printf("%c",input[i]);}

  // printf("\n~~~%d\n",HowManyTokens);

  double front,back;
  for(int i=1;i<=HowManyTokens;i++){
    // printf("\nThis is %d Round :\n",i);
    if(input[i] >= '1'&&input[i] <= '9'){
      temp = (input[i] - '0');
      sum = sum  * 10;
      sum += temp;
      // printf("\nNow temp is : %d and sum is %d\n",temp,sum);
    }
    else if(input[i] == '0'){sum *= 10;}
    else if(input[i] == ','){
      if(input[i-1]!='*'&&input[i-1]!='/'&&input[i-1]!='+'&&input[i-1]!='-'){
        push_number(sum);
        // printf("\nNow we push %d into stack\n",sum);
      }
      temp = 0;
      sum = 0;}
    else if(input[i] == '*' || input[i] =='/' || input[i] == '+' || input[i] == '-'){
      if(sum!=0){push_number(sum);sum = 0;}
      back = pop_number()+0.0;
      front = pop_number()+0.0;
      // printf("\nBack is : %0.15f\nFront is : %0.15f\n",back,front);
      if(input[i] == '*'){answer = back * front;}
      else if(input[i] == '/'){answer = front / back;}
      else if(input[i] == '+'){answer = back + front;}
      else if(input[i] == '-'){answer = front - back;}
      // printf("\nNow we push %lf into stack\n",answer);
      push_number(answer);
    }
    else if(input[i] == ','){continue;}

  }

  printf("%0.15f\n",answer);
}

int main(){
  char input_main[1000000];
  while(scanf("%s",input_main)!=EOF){
    Postfix_Evaluation(input_main);
    // Infix_Postfix(input_main);
  }







  return 0;
}


//Refference

// https://lakesd6531.pixnet.net/blog/post/332858496
