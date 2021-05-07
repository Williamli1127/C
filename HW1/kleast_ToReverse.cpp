#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE{
    int value;
    struct NODE *next;
    struct NODE *previous;
}Node;

void add_node_tail(Node **start, int input){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = input;
    new_node->next = NULL;
    new_node->previous = NULL;

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
        new_node->previous = current;
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

void inverse_print_list(Node* node){
    while(node->next!=NULL){
        // printf("%d ",node->value);
        node = node->next;
    }
    while(node!=NULL){
      printf("%d ",node->value);
      node = node->previous;
    }
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
    if(ith == 1){
      new_node->next = current;
      *start = new_node;
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

  if(i == 1){
    *start = current->next;
    free(current);
    return;
  }

  while(current != NULL){
    if(orders+1 == i){
      temp = current->next;
      current->next = current->next->next;
      free(temp);
      return;
    }
    current = current->next;
    orders ++;
  }
}

Node* cut(int l,int r,Node* head){
    int orders=1,triger=0;
    Node* output = NULL;
    while(head!=NULL){
        if(orders == l){triger = 1;}
        if(triger==1){
            add_node_tail(&output,head->value);
            if(orders == r){break;}
        }
        orders++;
        head = head->next;
    }
    // printf("\nNow output is : ");
    // print_list(output);
    return output;
}

void Find_KLeast(int k,Node* start){
    int initial=0,number_previous=-1;
    while(initial!=k){
        if(start->value != number_previous){
            // printf("%d ",start->value);
            initial++;
            number_previous = start->value;
        }
        start = start->next;
    }
    if(initial == k){printf("%d\n",number_previous);}
}

void sort(Node** start){
    Node *temp1,*temp2;
    int comparison;
    for (temp1=*start;temp1!=NULL;temp1=temp1->next){
        for (temp2=temp1->next;temp2!=NULL;temp2=temp2->next){
        if(temp2->value < temp1->value){
            comparison = temp1->value;
            temp1->value = temp2->value;
            temp2->value = comparison;
        }
        }
    }
}


Node* reverse(int l ,int r,Node** head){
  int orders=1,triger=0;
  Node* current = *head;
  Node* next = NULL;
  Node* previous = NULL;
  while(current!=NULL){
    if(orders==l){triger=1;}
    if(triger==1){
      if(orders == r){triger=0;continue;}
      next = current->next;
      current->next = previous;
      previous = current;
      current = next;
    }
    else if(triger==0){current = current->next;}
  }
  return previous;
}

int main(){

    int n,q,j,k,l,r,input;
    scanf("%d %d",&n,&q);

    // Create Head
    int initial;
    Node *head = NULL;
    scanf("%d",&initial);
    add_node_tail(&head,initial);

    //Load other numbers
    for(int i=1;i<n;i++){
        // printf("---->%d\n",i+1);
        scanf("%d",&input);
        add_node_tail(&head,input);
    }

    // sort
    // sort(&head);

    //Console
    char console[20];
    for(int i =0;i<q;i++){
    // printf("\nPlease enter your command!\n");
    scanf(" %s", console);

    if(strcmp(console,"Delete")==0){
        scanf("%d",&j);
        Delete(j,&head);
        // print_list(head);
        }

    else if(strcmp(console,"Insert")==0){
        scanf("%d",&j);
        scanf("%d",&k);
        Insert(j,k,&head);
        // printf("???");
        // print_list(head);
        }
    else if(strcmp(console,"Query")==0){
        scanf("%d",&l);
        scanf("%d",&r);
        scanf("%d",&k);
        Node* temp = cut(l,r,head);
        sort(&temp);
        // printf("\nAfter sorting : ");
        // print_list(temp);
        // printf("\nThe answer is : ");
        Find_KLeast(k,temp);
        free(temp);
        }
    else if(strcmp(console,"Reverse")==0){
        scanf("%d",&l);
        scanf("%d",&r);
        // reverse(l,r,&head);
        Node *temp = reverse(l,r,&head);

        // print_list(temp);
        head = temp;
        printf("\nNow HEAD looks like : ");
        print_list(head);
        free(temp);
        }
    }

    //   }

    //   switch (console) {
    //     case 'd':{
    //       scanf("%d",&j);
    //       Delete(j,&head);
    //       // print_list(head);
    //       break;}

    //     case 'i':{
    //       scanf("%d",&j);
    //       scanf("%d",&k);
    //       Insert(j,k,&head);
    //       // printf("???");
    //       // print_list(head);
    //       break;}

    //     case 'c':{
    //       scanf("%d",&l);
    //       scanf("%d",&r);
    //       scanf("%d",&k);
    //       Node* temp = cut(l,r,head);
    //       sort(&temp);
    //       printf("\nAfter sorting : ");
    //       print_list(temp);
    //       printf("\nThe answer is : ");
    //       Find_KLeast(k,temp);
    //       free(temp);
    //       break;}

    //     case 'r':{
    //       scanf("%d",&l);
    //       scanf("%d",&r);
    //       Node *temp_r = cut(l,r,head);
    //       Node *last = temp_r;
    //       while(last->next!=NULL){
    //           last = last->next;
    //       }
    //       reverse(last);
    //       free(temp_r);
    //       free(last);
    //       break;}
    //   }
    // }


    // printf("\nFor now, it is like...");
    // print_list(head);
    // Node* last = head;
    // while(last->next!=NULL){
            //   last = last->next;
    // }
    // inverse_print_list(last);

    free_list(head);
    return 0;
}


///ref : https://medium.com/@racktar7743/%E8%B3%87%E6%96%99%E7%B5%90%E6%A7%8B-%E9%9B%99%E5%90%91%E9%8F%88%E7%B5%90%E4%B8%B2%E5%88%97%E6%95%99%E5%AD%B8-1-%E6%96%B0%E5%A2%9E%E8%88%87%E5%8D%B0%E5%87%BA-5454b5190ab8
