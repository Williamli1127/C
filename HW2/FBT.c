#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int key;
  struct node* left;
  struct node* right;
}Node;

Node* root = NULL;

void inorder_traversal(Node* root) {
   if(root != NULL) {
      inorder_traversal(root->left);
      printf("%d ",root->key);
      inorder_traversal(root->right);
   }
}

Node* insertion(int key,int orientation,Node** current){
  Node* temp = (Node*)malloc(sizeof(Node));
  Node* parent;
  temp->key = key;
  temp->right = NULL;
  temp->left = NULL;

  if(root == NULL){root = temp;} // Creating root
  else{
    // current = root;
    parent = NULL;
    while(1){
      parent = *current;
      if(orientation == 1){ // LEFT SIDE
        *current = (*current)->left;
        if((*current)->left==NULL){
          parent->left = temp;
          return (*current);
        }
      }
      else if(orientation == 2){ // RIGHT SIDE
        *current = (*current)->right;
        if(*current == NULL){
          parent->right = temp;
          return temp;
        }
      }
    }
  }
}

int main(){
  int HowManynode,left_child,right_child,input_key;
  scanf("%d",&HowManynode);
  int key_base[HowManynode];
  Node* Current;
  for(int i=0;i<HowManynode;i++){key_base[i]=0;}

  for(int i=0;i<2;i++){
    scanf("%d %d %d",&key_base[i],&left_child,&right_child);
    if(i==0){Current = insertion(key_base[i],0,&Current);} // initial tree

    if(left_child!=-1){ // 1 -> Left
      Current = insertion(0,1,&Current);
      if(left_child == i+1){Current = insertion(0,1,&Current);printf("\nAdd new left\n");}
    }

    if(right_child!=-1){ // 2 -> Right
      // if(key_base[i]!=0){input_key = key_base[i];}
      // else{input_key = 0;}
      Current = insertion(0,2,&Current);
    }
 }

 //test for constructing the print_tree
  inorder_traversal(root);
}
