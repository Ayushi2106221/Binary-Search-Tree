#include <iostream>
#include <stdio.h>
using namespace std;
#define EMPTY_TREE 1; //macro
#define Data_not_found 2;
//create a node
struct node{
    node *left;
    int item;
    node* right;
};

class BST{
    private:
    node* root;
    void recursivePreorder(node*);
    void recursivePostorder(node*);
    void recursiveInorder(node*);
    void inorderCopy(BST& ,node*);

    public:
    BST();
    bool isEmpty();
    void insertElement(int);
    void inorederalTraversal();
    void preorederalTraversal();
    void postorederalTraversal();
   // void createNode(int);
    node* search(int);
    void del(int);
    ~BST();
    BST(BST&);
    BST& operator=(BST&);

};

//constructor
BST::BST(){
    root=NULL;
}

//check if tree is empty
bool BST::isEmpty(){
    return root==NULL;
}


// //to create a new node 
// void BST::createNode(int data){
//         node *n=new node();
//         n->item=data;
//         n->left=NULL;
//         n->right=NULL;
// }

//insert a new element in BST
void BST::insertElement(int data){
   
    //check if root is null
    if(root==NULL){
        node *n=new node();
        n->item=data;
        n->left=NULL;
        n->right=NULL;
        root=n;
        
    }

   else {
    node *ptr;
    ptr=root;
    bool flag=true;
    while(flag){               //loop starts here
        if(data==ptr->item){//node pahle nahi bna rahe h kyuki isse hoga ki memory leak ho jayega when data is duplicate
            flag=false;
        }
        if(ptr->item>data){
            //go to left subtree
            if(ptr->left!=NULL){
                ptr=ptr->left;
            }
            else{
                node *n=new node();
                n->item=data;
                n->left=NULL;
                n->right=NULL;
                ptr->left=n;
                flag=false;
            }
        }
        //else go to right subtree
        else{
            if(ptr->right!=NULL){
                ptr=ptr->right;
            }
            else{
                node *n=new node();
                n->item=data;
                n->left=NULL;
                n->right=NULL;
                ptr->right=n;
                flag=false;
            }
        }
    }       //loop ends here
}
}





//user will call it without passing any root to it
//pre order traversal
void BST::preorederalTraversal(){
    recursivePreorder(root);
}

void BST::recursivePreorder(node *root ){
    if(root){
        cout<<root->item<<" ";
        recursivePreorder(root->left);
        recursivePreorder(root->right);
    }
}



//post order traversal
void BST::postorederalTraversal(){
    recursivePostorder(root);
}

void BST::recursivePostorder(node *root ){
    if(root){
        recursivePostorder(root->left);
        recursivePostorder(root->right);
        cout<<root->item<<" ";
    }
}




//in order traversal
void BST::inorederalTraversal(){
    recursiveInorder(root);
}

void BST::recursiveInorder(node *root ){
    if(root){
        recursiveInorder(root->left);
        cout<<root->item<<" ";
        recursiveInorder(root->right);
    }
}

    
//to search any element
node* BST::search(int data){
    node *ptr;
    ptr=root;
    while(ptr){
        if(ptr->item==data)
        return ptr;

        else if(ptr->item>data)
        ptr=ptr->left;

        else
        ptr=ptr->right;
    }
    return NULL;
}


//to delete any element
void BST::del(int data){
    node *ptr, *parptr;
    //no deletion if tree is empty
    if(root==NULL){
        throw EMPTY_TREE;
    }
    parptr=NULL;
    ptr=root;

    //this loop is to search the item to be deleted
    while(ptr){
        if(ptr->item==data){
            break;
        }

        if(data<ptr->item){
            parptr=ptr; //parent ptr updation
            ptr=ptr->left;
        }
        else{
            parptr=ptr;  //parent ptr updation
            ptr=ptr->right;
        }
    }
    //if node mile hi nhi
    if(ptr==NULL){
        throw Data_not_found;
    }
    //if root node is to be deleted
    if(parptr==NULL && ptr!=NULL)  
        {
            //for no child
            if(ptr->left==NULL && ptr->right==NULL){
                delete ptr;
                root=NULL;
            }
            //for two child
           else if(ptr->left && ptr->right){
            node *succ, *parentsucc;
            succ=ptr->right;
            parentsucc=ptr;
            while(succ->left!=NULL){
                parentsucc=succ;
                succ=succ->left;
            }
            ptr->item=succ->item;
                if(succ==parentsucc->left)
                parentsucc->left=succ->right;
                else
                parentsucc->right=succ->right;
                //at last we do the deletion
                delete succ;



            }
            //for single child
            else{
            
                if(ptr->left!=NULL){
                    root=ptr->left;
                    
                }
                else{
                    root=ptr->right;
                }
                delete ptr;
            }
    }

    //node to be deleted is not a root node
    else{

        //case 1 ----no child
        if(ptr->left==NULL && ptr->right==NULL){
           //here we only need to see ki ptr left child hai parent ka ya right child h
            if(parptr->left==ptr)  //ptr is left child of parent ptr
                parptr->left=NULL;
            else   //ptr is right child of parent ptr
                parptr->right=NULL;

            delete ptr;
        }

        //case ----2 two child
        else if(ptr->left && ptr->right){
            node *succ, *parentsucc;
            succ=ptr->right;
            parentsucc=ptr;
            while(succ->left!=NULL){
                parentsucc=succ;
                succ=succ->left;
            }
            ptr->item=succ->item;
            //now we need to delete the successor 
            //here for deletion we will again have 2 cases
            //here we cannot call this function again as we have now two nodes with same value
            //ptr and succ now have same value 
            //so there will be confusion so as to delete which node
                //successor ka left toh hoga hi nhi 
                //sifr right me ya toh null ya toh koi node hoga
                //so simply check ki succ parent ka left child hai ya right
                if(succ==parentsucc->left)
                parentsucc->left=succ->right;
                else
                parentsucc->right=succ->right;
                //at last we do the deletion
                delete succ;
        }

        //case 3--- single child
        else{
            //check if it is a left child
            if(ptr==parptr->left){
                //now check ki delte karne walle node ke konse taraf child hai
                if(ptr->left)
                    parptr->left=ptr->left;
                
                else
                    parptr->left=ptr->right;
                
                delete ptr;
            }
            else{
                 //now check ki delte karne walle node ke konse taraf child hai
                if(ptr->left)
                    parptr->right=ptr->left;
                else
                    parptr->right=ptr->right;
                
                delete ptr;
            }

            
        }
    }

}


//destructor to release memory
BST::~BST(){
    while(root){
        del(root->item);
    }
}
   
void BST::inorderCopy(BST &b, node *ptr){
    if(ptr){
        inorderCopy(b,ptr->left);
        b.insertElement(ptr->item);
        inorderCopy(b,ptr->right);
    }
}
//copy constructor to implement deep copy
 BST::BST(BST &bst){
    root=NULL;
    if(bst.root){
        bst.inorderCopy(*this,bst.root);
    }
 }
   


//copy assignment operator to implement deep copy
 BST& BST::operator=(BST &bst){
    while(root){
        del(root->item);

    }
    bst.inorderCopy(*this,bst.root);
    return *this;
 }

 int main(){
    BST b;

    b.insertElement(50);
    b.insertElement(40);
    b.insertElement(32);
    b.insertElement(48);
    b.insertElement(70);
    b.insertElement(65);
    b.insertElement(80);
    cout<<"Inorder traversal is : " ;
    b.inorederalTraversal();
    cout<<endl;
    cout<<"Postorder traversal is : ";
    b.postorederalTraversal();
    cout<<endl;
    cout<<"Preorder traversal is : ";
    b.preorederalTraversal();
    cout<<endl;
    cout<<"after deletion ";
    b.del(80);
    cout<<"Inorder traversal is : " ;
    b.inorederalTraversal();
    cout<<endl;
    return 0;
 }