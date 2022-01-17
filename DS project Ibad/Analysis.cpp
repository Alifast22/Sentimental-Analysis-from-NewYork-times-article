#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <sstream>
using namespace std;

class Node
{
    public:
    int key;
    string word;
    Node *left;
    Node *right;
    int height;
};
int co=0;
// A utility function to get maximum
// of two integers
class AVL{

public:
Node *root;

AVL()
{
    root=NULL;
}


 
// A utility function to get the
// height of the tree
  int height(Node * r) {
    if (r == NULL)
      return -1;
    else {

      int lheight = height(r -> left);
      int rheight = height(r -> right);

      if (lheight > rheight)
        return (lheight + 1);

      else return (rheight + 1);
    }
  }
 
// A utility function to get maximum
// of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
Node* newNode(string let)
{
    Node* node = new Node();
    node->word=let;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
   // cout<<node->key<<" "<<node->word<<endl;
    return(node);
}
 
// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return (height(N->left) - height(N->right));
}
 
// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
Node* insert(Node* node,string let)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(let));
 
    if (let < node->word)
       { node->left = insert(node->left,let);}

    else if (let > node->word)
        node->right = insert(node->right,let);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */

 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && let < node->left->word)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && let > node->right->word)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && let > node->left->word)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && let < node->right->word)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
// A utility function to print preorder
// traversal of the tree.
// The function also prints height
// of every node
void inOrder(Node *root)
{
    if(root != NULL&&co<5)
    {   
        inOrder(root->right);
        co++;
        cout << root->word <<endl;
        inOrder(root->left);
    }
}
    int search(Node *root, string data,int x)
    {
        if (root == NULL)
        {
            return x;
        }
        // if(root->dat == data)
        // {
        //     return true;
        // }
        if (root->word > data)
        {
            return search(root->left, data,x);
        }
        else if (root->word < data)
        {
            return search(root->right, data,x);
        }
        else if(root->word==data)
        {
          return ++x;
        }

        else
        return x;
    }

};

void fileop(string word,AVL *obj)
{
  ifstream ip(word);
  string comment;
  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
  while(ip.good()){
    
        fflush(stdin);
        getline(ip, comment, '\n');
        fflush(stdin);
        
        obj->root=obj->insert(obj->root,comment);
       
       // cout<<comment<<endl;
}   
  
}

int m=0;
int ind=0;
AVL clut[6];

//finding maximum count of emotion
int max(int arr[])
{

    for(int i=0;i<6;i++)
    {
      if(arr[i]>m)
      {
        m=arr[i];
        ind=i;
      }
    }
    m=0;
    return ind;
}

void cluster(string name,int x,AVL *obj)
{
  int senti[6]={0,0,0,0,0,0};
  
  string temp;
  //ofstream of(name+".csv",ios::app); 
  ifstream lp(name+".csv");
  string comment;
  //if(!lp.is_open()) std::cout << "ERROR: File Open" << '\n';
  while(lp.good()){
    
        fflush(stdin);
        getline(lp, comment, '\n');
        fflush(stdin);

        stringstream ss(comment);

        while (ss >> temp)
        {
            //cout<<temp<<endl;
        
              senti[0]=obj[0].search(obj[0].root,temp,senti[0]);
              senti[1]=obj[1].search(obj[1].root,temp,senti[1]);
              senti[2]=obj[2].search(obj[2].root,temp,senti[2]);
              senti[3]=obj[3].search(obj[3].root,temp,senti[3]);
              senti[4]=obj[4].search(obj[4].root,temp,senti[4]);
              senti[5]=obj[5].search(obj[5].root,temp,senti[5]);  
              ind=max(senti);
        }         
        
        
       // cout<<comment<<endl;
  }
   cout<<"Area name:  "<<name<<"  ,  "<<"No of comments: "<<x<<"  ,  "<<"General feeling in the area:   ";
   if(ind==0)
    cout<<"anger.";
   
   if(ind==1)
     cout<<"disgust.";

   if(ind==2)
    cout<<"fear."; 

   if(ind==3)
    cout<<"joy."; 

   if(ind==4)
    cout<<"sad."; 

   if(ind==5)
    cout<<"surprised."; 

    ind=0;
    cout<<endl<<endl;   
}

void clusterrecc(string name,AVL *obj)
{
  int senti[6]={0,0,0,0,0,0};
  
  string temp;
  //ofstream of(name+".csv",ios::app); 
  ifstream lp(name+".csv");
  string comment;
  string body;
  if(!lp.is_open()) std::cout << "ERROR: File Open" << '\n';
  while(lp.good()){
    
        fflush(stdin);
      getline(lp, comment, '|');
        body=comment;
        fflush(stdin);

        stringstream ss(comment);

        while (ss >> temp)
        {
            //cout<<temp<<endl;
        
              senti[0]=obj[0].search(obj[0].root,temp,senti[0]);
              senti[1]=obj[1].search(obj[1].root,temp,senti[1]);
              senti[2]=obj[2].search(obj[2].root,temp,senti[2]);
              senti[3]=obj[3].search(obj[3].root,temp,senti[3]);
              senti[4]=obj[4].search(obj[4].root,temp,senti[4]);
              senti[5]=obj[5].search(obj[5].root,temp,senti[5]);  
              ind=max(senti);
        }         
        
        
       // cout<<comment<<endl;
  }
   co++;
   if(body.size()>1)
   {
  // cout<<body<<endl<<endl;
   cout<<"Recommendations: "<<name<<" , "<<"General feeling of Sentiment: ";;
   if(ind==0)
    cout<<"anger";
   
   if(ind==1)
     cout<<"disgust";

   if(ind==2)
    cout<<"fear"; 

   if(ind==3)
    cout<<"joy"; 

   if(ind==4)
    cout<<"sad"; 

   if(ind==5)
    cout<<"surprised";

    cout<<endl<<endl;


    ind=0;
   }
     
}
class linnode{
public:

string co;
int re;
linnode *next=NULL;
linnode(string c,int r)
{
co=c;
re=r;
next=NULL;
}


};
class lin{

public:
linnode *head,*tail;
lin()
{
head=NULL;
tail=NULL;
}
void insert(string c,int re)
{
linnode *temp=new linnode(c,re);

if(head==NULL)
{
head=temp;
tail=temp;
}
else
{
    tail->next=temp;
    tail=tail->next;
}

}
void display(int rec)
{
if(head)
{
string x;
linnode *temp;
temp=head;

ofstream of(to_string(rec)+".csv",ios::app);

  while (temp != NULL)
  {
      of<< temp->co << "\n";
      temp = temp->next;
  }
}
}
};
class recnode
{

public:
int rec;
string comm;
lin obj;
recnode *left=NULL;
recnode *right=NULL;

};
class BSTrecc
{

public:
BSTrecc()
{

}
recnode *root=NULL;
recnode* insert(int num,string com,recnode *r)
{
recnode *temp=new recnode();
temp->comm=com;
temp->rec=num;
if(r==NULL)
{
r=temp;
return r;
}
else if(r->rec>num)
{
r->left=insert(num,com,r->left);
}
else if(r->rec<num)
{
r->right=insert(num,com,r->right);
}
else
{
r->obj.insert(com,num);
}
return r;
}

void inorder(recnode *r,AVL ob[])
{
if(r&&co<2)
{
inorder(r->right,ob);
ofstream of(to_string(r->rec)+".csv");
 of<< r->comm << "|";
cout<<endl;
r->obj.display(r->rec);
clusterrecc(to_string(r->rec),ob);
inorder(r->left,ob);
}
}
};

class comments{
    public:
    string cb;
    comments* next;
    comments(){
        cb="";
        next=NULL;
    }
    comments(string i){
        cb=i;
        next=NULL;
    }
};
class commentlist{
    public:
    comments* head;
    commentlist(){
        head=NULL;
    }
    void append(comments* n){
       if (head == NULL)
            {
                head = n;
            }
            else
            {

                comments *ptr = head;
                while (ptr->next != NULL)
                {
                    ptr = ptr->next;
                }
                ptr->next = n;
            }
    }



    void display()
        {
            if (head == NULL)
            {
                return;
            }
            else
            {
              
              

                comments *temp = head;

                while (temp != NULL)
                {
                    cout << "Comment: ";
                    cout << temp->cb << "\n\n";
                    temp = temp->next;
                }
                
            }
        }

        void writetoo(string name)
        {
            if (head == NULL)
            {
                return;
            }
            else
            {
              ofstream of(name+".csv",ios::app);

                comments *temp = head;

                while (temp != NULL)
                {
                    of<< "Comment: ";
                    of<< temp->cb << "\n";
                    temp = temp->next;
                }
                
            }
        }
};

class locnode{
    public:
    string loc;
    locnode *left, *right,*next;
    commentlist list;
    int count;
    locnode(){
        left = NULL;
        right = NULL;
        count=1;
    }
};
class loclist{
    public:
    locnode* head;
    loclist(){
        head=NULL;
    }
    void append(locnode* n){
       if (head == NULL)
            {
                head = n;
            }
            else
            {

                locnode *ptr = head;
                while (ptr->next != NULL)
                {
                    ptr = ptr->next;
                }
                ptr->next = n;
            }
    }
    locnode *gethead()
    {
    return head;
    }

        void writetofil(int count)
        {
         if (head== NULL)
            {
                return;
            }
            else
            {
              if(co>2)
            {
            return;
            }
            
                co++; 
                locnode *temp = head;

                while (temp != NULL)
                {
                 temp->list.writetoo(temp->loc);
                 cluster(temp->loc,count, &clut[0]);
                 temp=temp->next;
                }
                
            }
                
        }
        void display()
        {
        if(!head)
        {
        return;
        }
        co++;
        locnode *temp=head;
        while(temp)
        {
        cout<<"Location: "<<temp->loc<<endl;
        temp->list.display();
        temp=temp->next;
        }
        }
};

class countnode{
public:
int count;
countnode* left;
countnode* right;
loclist listl;
countnode(){
    count=0;
    left=NULL;
    right=NULL;
}
countnode(int i){
    count=i;
    left=NULL;
    right=NULL;
}
};

class countbst{
public:
    countnode *root;
    countbst()
    {
        root = NULL;
    }
    countbst(countnode *r)
    {
        root = r;
    }

    void add(countnode *r,locnode *node){
        if (r==NULL) return;
        add(r->left,node);
        if (r->count==node->count){
            locnode* n = new locnode();
            n->count = node->count;
            n->loc=node->loc;
            n->list=node->list;
            n->next=NULL;
            n->left = NULL;
            n->right = NULL;
            r->listl.append(n);
           
        }
        add(r->right,node);
        

    }
    void insert(countnode *n){

    
         if (root == NULL)
        {
            
            root = n;
            
           
        }
        else
        {

            countnode *r = root;

            while (r != NULL)
            {
                if (n->count==r->count)
                {
                       
                     
                    return;
                }
                else if ((r->count>n->count) && (r->left == NULL))
                {

                    r->left = n;
                   
                    break;
                }
                else if ((r->count>n->count))
                {

                    r = r->left;
                }
                else if ((r->count<n->count) && (r->right == NULL))
                {

                    r->right = n;
                     
                    break;
                }
                else
                {

                    r = r->right;
                }
            }
        }
    }
   
    
    void print(countnode *r) //(current node, Left, Right)
    { 
        if(r&&co<2)
        {
        print(r->right);
        r->listl.display();
        print(r->left);
        }
    }
    void writetof(countnode *r)
    {
        if(r&&co<2)
        {
        writetof(r->right);
        r->listl.writetofil(r->count);
        writetof(r->left);
        }
    
    }
};


class locbst{
public:
    locnode *root;
    locbst()
    {
        root = NULL;
    }
    locbst(locnode *r)
    {
        root = r;
    }
    void insert(locnode *n,string cbody){
         if (root == NULL)
        {
            
            root = n;
             comments *idnode=new comments();
                        idnode->cb=cbody;
                        
                     root->list.append(idnode);
           
        }
        else
        {

            locnode *r = root;

            while (r != NULL)
            {
                if ((n->loc.compare(r->loc)) == 0)
                {
                       
                     comments *idnode=new comments();
                        idnode->cb=cbody;
                    r->count++;
                     r->list.append(idnode);
                    return;
                }
                else if ((r->loc.compare(n->loc)) > 0 && (r->left == NULL))
                {

                    r->left = n;
                     comments *idnode=new comments();
                        idnode->cb=cbody;
                
                     n->list.append(idnode);
                    break;
                }
                else if ((r->loc.compare(n->loc)) > 0)
                {

                    r = r->left;
                }
                else if ((n->loc.compare(r->loc)) > 0 && (r->right == NULL))
                {

                    r->right = n;
                     comments *idnode=new comments();
                        idnode->cb=cbody;
           
                     n->list.append(idnode);
                    break;
                }
                else
                {

                    r = r->right;
                }
            }
        }
    }
   
    void preorder(locnode *r, countbst *obj)
    {
        
        if (r == NULL)
        {
            return;
        }
        
        obj->add(obj->root,r);

        
        
        preorder(r->left,obj);
        preorder(r->right,obj);
    }    
    void print(locnode *r) //(current node, Left, Right)
    {
        if (r == NULL)
            return;
        /* first print data of node */

        /* then recur on left sutree */
        print(r->left);
        cout<<"---------------";
       cout << r->loc<<" "<<r->count<<endl;
       cout <<" ";
       r->list.display();
       cout <<"\n";
        cout<<"---------------";
       
        /* now recur on right subtree */
        print(r->right);
    }
};



class wordbal_n
{
    public:
    int key;
    string word;
    wordbal_n *left;
    wordbal_n *right;
    int height;

    wordbal_n()
    {
        key=0;
        left=NULL;
        right=NULL;
    }
};
 
class wordbalance{

public:
wordbal_n *root;

wordbalance()
{
    root=NULL;
}


 
// A utility function to get the
// height of the tree
int height(wordbal_n *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum
// of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a
   new wordbal_n with the given key and
   NULL left and right pointers. */
wordbal_n* newwordbal_n(int key,string let)
{
    wordbal_n *n = new wordbal_n;
    n->key = key;
    n->word=let;
    n->left = NULL;
    n->right = NULL;
    n->height = 1; // new wordbal_n is initially
                      // added at leaf
    return(n);
}
 
// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
wordbal_n *rightRotate(wordbal_n *y)
{
    wordbal_n *x = y->left;
    wordbal_n *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
wordbal_n *leftRotate(wordbal_n *x)
{
    wordbal_n *y = x->right;
    wordbal_n *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of wordbal_n N
int getBalance(wordbal_n *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert a key
// in the subtree rooted with wordbal_n and
// returns the new root of the subtree.
wordbal_n* insert(wordbal_n* wordbal_n, int key,string let)
{
    /* 1. Perform the normal BST insertion */
    if (wordbal_n == NULL)
        return(newwordbal_n(key,let));
 
    if (key < wordbal_n->key)
        wordbal_n->left = insert(wordbal_n->left, key,let);
    else if (key > wordbal_n->key)
        wordbal_n->right = insert(wordbal_n->right, key,let);
    else // Equal keys are not allowed in BST
        return wordbal_n;
 
    /* 2. Update height of this ancestor wordbal_n */
    wordbal_n->height = 1 + max(height(wordbal_n->left),
                        height(wordbal_n->right));
 
    /* 3. Get the balance factor of this ancestor
        wordbal_n to check whether this wordbal_n became
        unbalanced */
    int balance = getBalance(wordbal_n);
 
    // If this wordbal_n becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < wordbal_n->left->key)
        return rightRotate(wordbal_n);
 
    // Right Right Case
    if (balance < -1 && key > wordbal_n->right->key)
        return leftRotate(wordbal_n);
 
    // Left Right Case
    if (balance > 1 && key > wordbal_n->left->key)
    {
        wordbal_n->left = leftRotate(wordbal_n->left);
        return rightRotate(wordbal_n);
    }
 
    // Right Left Case
    if (balance < -1 && key < wordbal_n->right->key)
    {
        wordbal_n->right = rightRotate(wordbal_n->right);
        return leftRotate(wordbal_n);
    }
 
    /* return the (unchanged) wordbal_n pointer */
    return wordbal_n;
}
 
// A utility function to print preorder
// traversal of the tree.
// The function also prints height
// of every wordbal_n
void inOrder(wordbal_n *root)
{
    if(root != NULL&&co<4)
    {
        
        inOrder(root->right);
        co++;
        cout << root->word<<" ";
        cout << root->key <<endl;
        inOrder(root->left);
    }
}

};


class bstnode
{
public:
    string dat;
    bstnode *left = NULL;
    bstnode *right = NULL;
    int freq = 0;

    bstnode()
    {
    }
};

class Words
{
    string word;
};
int cou;
class BST
{
public:
    bstnode *root = NULL;
    bstnode *insert(bstnode *n, string val)
    {
        if (n == NULL)
        {
            bstnode *obj = new bstnode();
            obj->dat = val;
            n = obj;
            return n;
        }
        if (val < n->dat)
        {
            n->left = insert(n->left, val);
        }
        else if (val > n->dat)
        {
            n->right = insert(n->right, val);
        }
        else
        {
            n->freq++;
        }
        return n;
    }
    
    bstnode *getbstnode(bstnode *root, string data)
    {
        if (root == NULL)
        {
            return NULL;
        }
        if (root->dat == data)
        {
            return root;
        }
        if (root->dat > data)
        {
            return getbstnode(root->left, data);
        }
        if (root->dat < data)
        {
            return getbstnode(root->right, data);
        }
        return NULL;
    }      
    void inorder(bstnode *r)
    {
        if (r == NULL||cou<3 )
        {
            return;
        }
        inorder(r->left);
        
        cout << r->dat << " ";
        cout << r->freq << " ";
        cou++;
        cout << endl;
        inorder(r->right);
    }

    void preorder(bstnode *r, wordbalance *obj)
    {
        if (r == NULL)
        {
            return;
        }
    
        obj->root=obj->insert(obj->root,r->freq,r->dat);

        preorder(r->left,obj);
        preorder(r->right,obj);
    }    
int size(bstnode* bstnode)
{
    if (bstnode == NULL)
        return 0;
    else
        return(size(bstnode->left) + 1 + size(bstnode->right));
}   
    bstnode *build(bstnode *root, string arr[], int x, int y)
    {
        if (x > y)
        {
            return NULL;
        }
        int mid = (y + x) / 2;
        bstnode *temp = new bstnode();
        temp->dat = arr[mid];
        root = temp;
        root->left = build(root->left, arr, x, mid - 1);
        root->right = build(root->right, arr, mid + 1, y);
        return root;
    }
    bool isdigit(int ch)
    {
        if(ch>=0 && ch<=1000000)
        {
            return true;
        }
        else
        return false;
    }
    bool search(bstnode *root, string data)
    {
        if (root == NULL)
        {
            return true;
        }
        // if(root->dat == data)
        // {
        //     return true;
        // }
        if (root->dat > data &&  (data[0]>=65 && data[0]<=90))
        {
            return search(root->left, data);
        }
        else if (root->dat < data  && (data[0]>=65 && data[0]<=90))
        {
            return search(root->right, data);
        }

        else
        return false;

        return false;
    }    


 
// A utility function to print the array
// representation of Heap


};

void modifiedbubblesort(string word[],int n)
{
for(int i=0; i<n; i++){
		int swaps=0;
		for(int j=0; j<n-i-1; j++){
			if(word[j]>word[j+1]){
				string t=word[j];
				word[j]=word[j+1];
				word[j+1]=t;
				swaps++;
			}
		}
		if(swaps==0)
			break;
	}
}


int main()
{
  string w[6]={"anger.txt","disgust.txt","fear.txt","joy.txt","sadness.txt","surprise.txt"};
  
 for(int i=0;i<6;i++)
 {
  fileop(w[i],&clut[i]);
 }
  
 //  cluster("NY", &obj[0]);
   BST words;
   BSTrecc rec;
    string wor[129] = {"He","We","But","At","AND","As","This","Mr.","It's","They","If","All","It","Even","According","I","And","ALL","A","a", "about", "after", "all", "also", "an", "and", "any", "as","are", "at", "back", "be", "because", "but", "by", "can", "come", "could","did", "day", "do", "even", "first", "for", "from", "get", "give", "go", "good","has","had", "have", "he", "her", "him", "his", "how", "i","I", "if", "in", "is", "into", "it", "it's", "just", "know", "like", "look", "make", "me", "most", "my","more", "new", "no", "not", "now", "of", "on", "one", "only", "or", "other", "our", "out", "over", "people", "say", "see", "she", "so", "some","The", "take", "than", "that", "the", "their", "them", "then", "there", "these", "they", "think", "this", "time", "to", "two", "up", "us", "use","was", "want", "way", "we", "well", "what", "when", "which", "who", "will", "with", "work", "would", "year", "you","your", "you"};

// Trump 61282
// Biden 22861
// We 20995
// He 15971
// American 13150
// America 8898
// Barrett 4835
// At 2896
// America. 1985
// ACA 1231
// AND 664


   modifiedbubblesort(wor,129);
    words.root = words.build(words.root, wor, 0, 128);
    BST obj;
    BST objfreq;
    locbst locationtree;
 
    ifstream ip("bgmix.csv");

    // if (!ip.is_open())
    //     cout << "ERROR: File Open" << '\n';
int i=0;
    string commentID;
    string status;
    string commentsequence;
    string userID;
    string userDisplayName;
    string userlocation;
    string usertitle;
    string commentbody;
    string createDate;
    string updateDate;
    string approveDate;
    string recommendations;
    string replyCount;
    string editorsSelection;
    string parentID;
    string parentUserDisplayName;
    string depth;
    string commentType;
    string trusted;
    string recommendedFlag;
    string permID;
    string isAnonymous;
    string articleID;

    string temp;

  while(ip.good()){
    
        fflush(stdin);
        getline(ip, commentID, '|');
        fflush(stdin);
        getline(ip, status, '|');
        fflush(stdin);
        getline(ip, commentsequence, '|');
        fflush(stdin);
        getline(ip, userID, '|');
        fflush(stdin);
        getline(ip, userDisplayName, '|');
        fflush(stdin);
        getline(ip, userlocation, '|');
        fflush(stdin);
        getline(ip, usertitle, '|');
        fflush(stdin);
        getline(ip, commentbody, '|');
        fflush(stdin);
        getline(ip, createDate, '|');
        fflush(stdin);
        getline(ip, updateDate, '|');
        fflush(stdin);
        getline(ip, approveDate, '|');
        fflush(stdin);
        getline(ip, recommendations, '|');
        fflush(stdin); 
        getline(ip, replyCount, '|');
        fflush(stdin); 
        getline(ip, editorsSelection, '|');
        fflush(stdin); 
        getline(ip, parentID, '|');
        fflush(stdin); 
        getline(ip, parentUserDisplayName, '|');
        fflush(stdin); 
        getline(ip, depth, '|');
        fflush(stdin); 
        getline(ip, commentType, '|');
        fflush(stdin); 
        getline(ip, trusted, '|');
        fflush(stdin); 
        getline(ip, recommendedFlag, '|');
        fflush(stdin); 
        getline(ip, permID, '|');
        fflush(stdin); 
        getline(ip, isAnonymous, '|'); 
        fflush(stdin); 
        getline(ip, articleID, '\n');                                                               

        i++;
        if(i>1)
        {
         stringstream st(recommendations);
    
            
        int x=0;
        st >> x;
        rec.root=rec.insert(x,commentbody,rec.root);

        stringstream ss(commentbody);
        while(ss>>temp)
        {
            if (words.search(words.root, temp))
            {
                obj.root = obj.insert(obj.root, temp);  
            }
        }
        fflush(stdin);
           locnode *n=new locnode();
           n->loc=userlocation;
           //cout << userlocation<<endl;
           locationtree.insert(n,commentbody);
          // locationtree.countindex(locationtree.root,comments,userlocation);
                fflush(stdin);

        }
     
      
  }

    //locationtree.print(locationtree.root);

    countbst counttree;
    for (int i=1;i<100;i++){
        countnode *n=new countnode(i);
        counttree.insert(n);
    }
    wordbalance extra;
    obj.preorder(obj.root,&extra);
     locationtree.preorder(locationtree.root,&counttree);
    ip.close();  

int x;
char y;

while(1)
{
system("CLS");
cout<<"Analysis of Comments of NewYork Times: "<<endl;
cout<<"Press 1 for seeing most Popular Words."<<endl;
cout<<"Press 2 for seeing areas with most active users and how they feel "<<endl;
cout<<"Press 3 for  seeing comments which prompted most positive feedback and the nature of those comments "<<endl;
cout<<"Press anything else to exit program "<<endl;
cout<<"Please enter your choice: ";
cin>>x;
switch(x)
{
 case 1:
 {
  system("CLS");
  co=0;
  cou=0;
cout<<"Most used words are: "<<endl;
 extra.inOrder(extra.root);
 cout<<"Press any key to continue: ";
  cin>>y;
  break;
 }
 case 2:
 {
   system("CLS");
  cou=0;
  co=0;
   counttree.writetof(counttree.root);
   cout<<endl<<"Press key to continue "<<endl;
  cin>>y;
   break;
 }
 case 3:
 {
  cou=0;
  co=0;
  system("CLS");
  rec.inorder(rec.root,clut);
  cout<<endl<<"Press key to continue "<<endl;
  cin>>y;
  break;
 }
default:
 {
system("CLS");
cout<<"Thankyou for viewing our code...."<<endl;
cout<<"Have a nice day! "<<endl;
//_sleep(300);
 exit(0);
 }
}

}

}