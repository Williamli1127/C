#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE{
    int value;
    struct NODE *next;
}Node;

void add_node_tail(Node **start, int input){
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
        // if(start->value != number_previous){
            // printf("%d ",start->value);
            initial++;
            number_previous = start->value;
        // }
        start = start->next;
    }
    if(initial == k){printf("%d\n",number_previous);}
}

void sort(Node** start){ //Not effiecient enough
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

void Split(Node*head,Node**front,Node**back);
Node* SortedMerge(Node*a ,Node*b);

void MergeSort(Node** head){
  Node* current = *head;
  Node* a;
  Node* b;
  if(current==NULL){return;}
  if(current->next==NULL){return;}

  Split(current,&a,&b);
  MergeSort(&a);
  MergeSort(&b);
  (*head) = SortedMerge(a,b);
}

Node* SortedMerge(Node*a ,Node*b){
  Node* result = NULL;
  if(a==NULL){return b;}
  else if(b==NULL){return a;}

  if(a->value<=b->value){
    result = a;
    result->next = SortedMerge(a->next,b);
  }
  else{
    result = b;
    result->next = SortedMerge(a,b->next);
  }
  return result;
}

void Split(Node*head,Node**front,Node**back){
  Node* fast;
  Node* slow;
  slow = head;
  fast = head->next;

  while(fast!=NULL){
    fast = fast->next;
    if(fast!=NULL){
      slow = slow->next;
      fast = fast->next;
    }
  }

  *front = head;
  *back = slow->next;
  slow->next = NULL;
}


Node* reverse(int l ,int r,Node** head){
    Node* previous = NULL;
    Node* current = *head;
    int orders=1;
    if(head ==NULL){return (*head);}
    if(l==r){return (*head);}
    while(current && (orders<l)){
      previous = current;
      current = current->next;
      orders++;
    }
    Node* temp1 = previous;
    Node* temp2 = current;
    while(current && (orders<(r+1))){
      Node* next = current->next;
      current->next = previous;
      previous = current;
      current = next;
      orders++;
    }
    if(temp1 != NULL){temp1->next = previous;}
    if(temp2 != NULL){temp2->next = current;}
    if(l==1){(*head)=previous;}
    return (*head);
}

int main(){

    int n,q,j,k,l,r,input;
    scanf("%d %d",&n,&q);
    Node *head = NULL;

    //Load other numbers
    for(int i=0;i<n;i++){
        // printf("---->%d\n",i+1);
        scanf("%d",&input);
        add_node_tail(&head,input);
    }

    //Console
    char console[20];
    for(int i =0;i<q;i++){
    scanf(" %s", console);

    if(strcmp(console,"Delete")==0){
        scanf("%d",&j);
        Delete(j,&head);
        }

    else if(strcmp(console,"Insert")==0){
        scanf("%d",&j);
        scanf("%d",&k);
        Insert(j,k,&head);
        }
    else if(strcmp(console,"Query")==0){
        scanf("%d",&l);
        scanf("%d",&r);
        scanf("%d",&k);
        Node* temp = cut(l,r,head);
        MergeSort(&temp);
        Find_KLeast(k,temp);
        free(temp);
        }
    else if(strcmp(console,"Reverse")==0){
        scanf("%d",&l);
        scanf("%d",&r);
        Node *temp = reverse(l,r,&head);
        head = temp;
        // print_list(temp);
        // printf("\nNow HEAD looks like : ");
        // print_list(head);
        }
    // else if(strcmp(console,"MergeSort")==0){
    //   MergeSort(&head);
    //   printf("\nNow after mergesort : \n");
    //   print_list(head);
    // }
    }

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

//Version 2.0

///ref : https://medium.com/@racktar7743/%E8%B3%87%E6%96%99%E7%B5%90%E6%A7%8B-%E9%9B%99%E5%90%91%E9%8F%88%E7%B5%90%E4%B8%B2%E5%88%97%E6%95%99%E5%AD%B8-1-%E6%96%B0%E5%A2%9E%E8%88%87%E5%8D%B0%E5%87%BA-5454b5190ab8
//https://www.srcmake.com/home/reverse-linked-list
