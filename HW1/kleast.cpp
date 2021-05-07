#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    int value;
    struct NODE *next;
    struct NODE *previous;
}Node;

void add_node(Node **start, int input){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = input;
    new_node->next = NULL;

    if(*start == NULL){
        *start = new_node;
        return;
    }
    else{
        Node *current;
        current = *start;
        while(current->next!=NULL){
            current = current->next;
        }
        current->next = new_node;
        return;
    }
};

void print_list(Node *node){
    while(node != NULL){
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

void free_list(Node *node){
  Node *current, *temp;
  current = node;
  while(current != NULL){
    temp = current;
    current = current->next;
    free(temp);
  }
}

void Insert(int ith,int x,Node **start){
  int orders = 1;
  Node *current = *start;
  Node* new_node = (Node*)malloc(sizeof(Node));
  new_node->value = x;

  while(current!=NULL){
    printf("~~~\n");
    if(ith == 1){ /////////////////////////////////////BUG////////////////////////////////
      new_node->next = current;
      return;
    }

    if(orders+1 == ith){
      new_node->next = current->next;
      current->next = new_node;
      return;
    }

    orders++;
    current = current->next;
  }
}

void Delete(int i,Node **start){
  int orders = 1;
  Node *current = *start;
  Node *temp;
  printf("-------Removing %dth number\n",i);

  if(i == 1){
    *start = current->next;
    free(current);
    return;
  }

  while(current != NULL){
    if(orders+1 == i){
      printf("Right!!! :%d\n",orders+1);
      temp = current->next;
      current->next = current->next->next;
      free(temp);
      return;
    }
    current = current->next;
    orders ++;
  }
}

void Query(int l ,int r ,int k ,Node*start){
  Node *current = start;
  Node *temp1,*temp2;
  int orders = 1,triger=0;
  int comparison,cut_numbers = r-l+1;
  Node *temp_node = (Node*)malloc(sizeof(Node)*cut_numbers);
  temp_node->next = NULL;

  // while(current != NULL){
  //     printf("%d ", current->value);
  //     current = current->next;
  // }

  // Cut
  while(current->next!=NULL){  //traversal
    if(l == 1){
      printf("Wait Wati Wait!!\n");
      if(orders+1 == r){
        current->next->next = NULL;
        break;
      }
    }
    else{

      if(orders+1 == l && orders+1 == r){
      }
      else if(orders+1 == l){
        printf("Head is %dth :\n",orders+1);
        temp_node->value = current->next->value;
        triger++;
        // temp_node = current->next;
      }
      else if(orders+1 == r){
        printf("Tail is %dth :\n",orders+1);
        temp_node ->next ->next= NULL;
        break;
      }
      else if(triger == 1 && orders+1 > l){
        printf("\n-----\n");
        while(temp_node->next != NULL){
          temp_node = temp_node->next;
        }
        temp_node->next = current->next;
      }

    }
    orders ++;
    current = current->next;
  }

  while(temp_node != NULL){
      printf("%d ", temp_node->value);
      temp_node = temp_node->next;
  }

  free(temp_node);

  // Sort
  // for (temp1=*start;temp1!=NULL;temp1=temp1->next){
  //   for (temp2=temp1->next;temp2!=NULL;temp2=temp2->next){
  //     if(temp2->value < temp1->value){
  //       comparison = temp1->value;
  //       temp1->value = temp2->value;
  //       temp2->value = comparison;
  //     }
  //   }
  // }

  // Print
  // for(int i=0;i<k;i++){
  //   printf("%d\n",current->value);
  //   current = current->next;
  // }

  printf("\n\nFuction Ends~\n\n");
}

void Cut(int l ,int r,Node* start){
  Node *current = start;
  Node *temp;
  int orders=1;

  // Find Head & Tail
  while(current->next!=NULL){
    if(orders+1 == l){
      temp = current->next;
    }
    else if(orders+1 == r){
      // saving = current -> next ->next ;
      temp ->next->next = NULL;
      break;
    }
    current = current->next;
    orders++;
  }

  // Print
    while(temp != NULL){
        printf("%d ", temp->value);
        temp = temp->next;
    }

  // End

  printf("\nEnd of Cut Function!\n\n");

}




int main(){

    int n,q,j,k,l,r,input;
    scanf("%d %d",&n,&q);

    // Create Head
    int initial;
    Node *head = NULL;
    scanf("%d",&initial);
    add_node(&head,initial);

    //Load other numbers
    for(int i=1;i<n;i++){
        // printf("---->%d\n",i+1);
        scanf("%d",&input);
        add_node(&head,input);
    }

    // sort
    // sort(&head);



    //Console
    char console;
    for(int i =0;i<q;i++){
      printf("Please enter your command: \n");
      scanf(" %c", &console);

      switch (console) {
        case 'd':
          scanf("%d",&j);
          Delete(j,&head);
          print_list(head);
          break;

        case 'i':
          scanf("%d",&j);
          scanf("%d",&k);
          Insert(j,k,&head);
          // printf("???");
          print_list(head);
          break;

        case 'k':
          scanf("%d",&l);
          scanf("%d",&r);
          scanf("%d",&k);
          Query(l,r,k,head);

        case 'c':
          scanf("%d",&l);
          scanf("%d",&r);
          Cut(l,r,head);
      }
    }


    printf("For now, it is like...");
    print_list(head);

    free_list(head);
    return 0;
}
