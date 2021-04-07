#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

typedef struct Node_InfixToPostfix{
  char token;
  int precedence;
  struct Node_InfixToPostfix *next;
}Node_fix;

typedef struct Node_PostEvaluation{
  char input;
  double value;
  struct Node_PostEvaluation *next;
}Node_eva;

typedef Node_fix *Stack_fix;
typedef Node_eva *Stack_eva;

Stack_fix top = NULL;
Stack_eva top_eva = NULL;

void push(char data, int precedence){
  Stack_fix new_node;

  new_node = (Stack_fix)malloc(sizeof(Node_fix));
  new_node->token = data;
  new_node->precedence = precedence;
  new_node->next = top;
  top = new_node;
}

void push_number(double data){
    Stack_eva new_node;

    new_node = (Stack_eva)malloc(sizeof(Node_eva));
    new_node->value = data;
    new_node->next = top_eva;
    top_eva = new_node;
}

double pop_number(){
  Stack_eva ptr;
  double temp;

  ptr = top_eva;
  temp = ptr->value;
  top_eva = top_eva->next;
  free(ptr);
  return temp;
}

char pop(){
  Stack_fix ptr;
  char temp;

  ptr = top;
  temp = ptr->token;
  top = top->next;
  // printf("%c",temp);
  free(ptr);
  return temp;

}

char* Infix_Postfix(char *input,int length){
  char output[1000000];
  int input_precendence,j=0;
  push('_',-10);
  // int length = strlen(input); //Problems!!
  int HowManyTokens = length;
  // printf("\nWhile entering %d char :",HowManyTokens);
  // printf("\n");
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
      while(top->token != '('){
      output[j] = pop();
      j++;
      }
      pop();
    }

    if(i==length-1){
      while (top->token!='_') {
        output[j] = pop();
        j++;}
    }
  }

  char *transfer = (char*)malloc(sizeof(char)*HowManyTokens);
  transfer[0] = HowManyTokens;
  for(int i=0;i<HowManyTokens;i++){transfer[i+1]=output[i];}
  return transfer;
}

void Postfix_Evaluation(char *input_main,int length){
  char *input;
  int temp=0,sum=0,howmanyDigits=0;
  double answer;

  input = Infix_Postfix(input_main,length);

  int HowManyTokens = input[0];
  // printf("\nIn the function the input like : ");
  // for(int i=1;i<=HowManyTokens;i++){printf("%c",input[i]);}
  // printf("\n\nAnd then is the calculation~\n\n");

  // printf("\\\\End if input\n~~~%d\n",HowManyTokens);

  double front,back;
  for(int i=1;i<=HowManyTokens;i++){
    if(input[i] >= '1'&&input[i] <= '9'){
      howmanyDigits++;
      temp = (input[i] - '0');
      sum = sum  * 10;
      sum += temp;
      // printf("\nNow temp is : %d and sum is %d\n",temp,sum);
    }
    else if(input[i] == '0'){sum *= 10;howmanyDigits++;}
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
  if(HowManyTokens==howmanyDigits){answer = sum;}
  printf("%0.15f\n",answer);
  free(input);
}

int main(){
  char input_main[1000000];
  char *input;
  int i=0;
  while(scanf("%c",&input_main[i])!=EOF){
    if(input_main[i] == '\n'){
      input = (char*)malloc(sizeof(char)*i);
      // printf("\nStart!\n");
      for(int j=0;j<i;j++){input[j] = input_main[j];}
      // printf("\nEnding\n");
      Postfix_Evaluation(input,i);
      free(input); 
      for(int j=0;j<i;j++){input_main[j] = ' ';}
      i=0;
    }
    else
    {
      i++;
    }
    
  }

  // Basic String Version
  // while(scanf("%s",input_main)!=EOF){
  //   Postfix_Evaluation(input_main);}
  return 0;
}

