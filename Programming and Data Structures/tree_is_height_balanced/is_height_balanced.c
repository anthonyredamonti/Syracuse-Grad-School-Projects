#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct TreeNode {
   int value;
   struct TreeNode* left;
   struct TreeNode* right;
} TreeNode;

typedef struct Tree {
   TreeNode* root;
} Tree;

TreeNode* createTreeNode(int data){
   TreeNode* node;
   node = (TreeNode*)(malloc(sizeof(TreeNode)));
   node->left = NULL;
   node->right = NULL;
   node->value = data;
   return(node);
}
  
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 

// return 1 for balanced. return 0 for not balanced.
int isheightbalanced(Tree* tree) {
   if(tree->root == NULL)
   {
      printf("The tree's roots is NULL.");
      return 0;
   }
   int answer = recursive_height_checker(tree->root);
   return(answer);
}

int recursive_height_checker(TreeNode* root){
   if((root->left==NULL) && (root->right == NULL)){
	   return 1;
   }
   if((root->left == NULL) && (root->right != NULL)){
	   if((root->right->right != NULL) || (root->right->left) != NULL) {
		   return 0;
	   }
   }
   if((root->left != NULL) && (root->right == NULL)){
	   if((root->left->right != NULL) || (root->left->left) != NULL) {
		   return 0;
	   }
   }
   if(root->left != NULL){
	   return(recursive_height_checker(root->left));
   }
   if(root->right != NULL){
	   return(recursive_height_checker(root->right));
   }
}


/* Driver program to test above functions */
int main() 
{ 

   Tree tree1;
   tree1.root = createTreeNode(2);
   tree1.root->left = createTreeNode(3);
   tree1.root->right = createTreeNode(60);
   tree1.root->left->left = createTreeNode(2);
   //tree1.root->left->left->right = createTreeNode(5);

	Tree* pntr = &tree1;
   int answer = isheightbalanced(pntr);

printf ("hi");
    return 0; 
} 