#include<iostream>
using namespace std;

class Node
{	
	public:	
		int data;
		Node* left;//pointers to point left child
		Node* right;//pointers to point right child
		Node * parent;
		//default constructor
		Node(int value)
		{
			left=NULL;//initializing the value to null
			right=NULL;//initializing the value to null
			data=value;
			parent = NULL;
		}
};

class BiST
	{	
	public:	
		Node* root;
		//default constructor
		BiST()
		{
			root=NULL;
		}
		
		//insert()
		void insert(int value)
		{
			insert2(root,value);
		}
		void insert2(Node* curr, int value)
		{
			//base case 
			if(root==NULL)
			{
				root = new Node(value);
			}
			//else compare the data
			
			else if(value<curr->data)
			{
				//If left is null, insert it.
				if(curr->left==NULL)
				{
					curr->left = new Node(value);
					curr->left->parent = curr; 
				}
				//else move left by calling insert2 by recursion
				else insert2(curr->left, value);
			}
			else
			{
				//If right is null, insert it.
				if(curr->right==NULL) 
				{
					curr->right = new Node(value);
					curr->right->parent = curr;
				}	
				//else move right by calling insert2 by recursion
				else insert2(curr->right, value);
			}
		}
		
		//display()
		void display(){
			cout<<"printing traversal in inorder";
			cout<<endl;
    		display2(root);
    		cout<<endl<<endl;
		    cout<<"printing traversal in preorder";
		    cout<<endl;
		    display3(root);
		    cout<<endl<<endl;
			cout<<"printing traversal in postorder";
			cout<<endl;
		    display4(root);
			cout<<endl<<endl;	
		}
		//inorder 
		void display2(Node* curr){
			//Base condition
			if(curr==NULL) return;
			//display left
			display2(curr->left);
			//Display current
			cout << curr->data <<",";
			//display right
			display2(curr->right);
		}
		//preorder
		void display3(Node* curr){
			//Base condition
			if(curr==NULL) return;
			//Display current
			cout << curr->data <<",";
			//display left
			display3(curr->left);
			//display right
			display3(curr->right);
		}
		//postorder
		void display4(Node* curr){
			//Base condition
			if(curr==NULL) return;
			//display left
			display4(curr->left);
			//display right
			display4(curr->right);
			//Display current
			cout << curr->data <<",";
		}
		
		void displayfancy()
		{
			displayfancy2(root,0);
		}
		
		void displayfancy2 (Node* curr,int spaces)
		{
			// to get the right end value
			if (curr==NULL) return;
			//display right
			displayfancy2(curr->right,spaces+1);
			//inceraese number of spaces
			for(int i=0;i<5*spaces;i++)
			{
				cout<<" ";
			}
			//print req spaces
			//display curr
			cout<<curr->data<<endl;
			//display left
			displayfancy2(curr->left,spaces+1);
			
			/*sample output
					16
				14
					12
			10
					8
				6
					4
			*/
		}
		
		//search()
		Node* search(int value)
		{
			search2(value, root);
		}
		Node* search2(int value, Node* curr)
		{
			//match
			if(value==curr->data) return curr;
			//smaller
			else if(value<curr->data) return search2(value,curr->left);
			//larger
			else if(value>curr->data) return search2(value,curr->right);
			//not found
			else{
				return NULL;
			}
		}
		//minimum	
		Node* findMin(Node* curr)
    	{
	        if(curr->left!=NULL)//upto left node of the subtree
	        return findMin(curr->left);//it is traversed in left side
	        else
	        return curr;//the curr node is the leftmost and after it is null
	    }
		//count
		int count(Node* curr)
	    {
	        if(curr!=NULL) //when it is at root and sub branches
	        return (1+count(curr->left)+count(curr->right));
	        else    //when it is at leaflet
	        return 0;
	    }
		//replace withn parents(node * ptre,node* ptr)
		void replaceAtParent(Node* A, Node* B)
	    {
	        if(A->parent->left==A)
	        A->parent->left=B;//replacing the parnet at left
	        else if(A->parent->right==A)
	        A->parent->right=B;//replacimng the parent at right
	        if(B!=NULL)
	        B->parent=A->parent;//replaced the parent of A with parent of B
	        A->parent=NULL;
	    }
		//deletion
		void delet(int value)
	    {
	        root=delet(root,value);
	        cout<<value<<" deleted "<<endl;
	    }
	    //helper delete
	    Node* delet(Node* curr,int value)
	    {
	        if(curr==NULL)//if current is null 
	        {
	            cout<<"The value is not present in the tree."<<endl;//the value which is to be deleted is not there
	            return curr;//the recursion stops
	        }
	        else if(curr->data==value)// reached to the node  to be deleted
	        {
	            Node* ptr1=curr->left;//pointer to the left subtree of the current node
	            Node* ptr2=curr->right;//pointer to the right subtree of the current node
	            if(ptr1==NULL&&ptr2==NULL)//if the node is leaf
	            {
	                delete curr;// node deleted
	                return NULL;
	            }
	            else if(ptr1==NULL)//if the node has a right subtree
	            {
	                delete curr;//node deleted
	                return ptr2;//its right subtree is attached to the remain tree
	            }
	            else if(ptr2==NULL)//if the node has a left subtree
	            {
	                delete curr;// node deleted
	                return ptr1;//its left subtree is attached to the tree
	            }
	            else   //if the node has a right subtree and a left subtree
	            {
	                 findMin(ptr2)->left=ptr1;
					 //the minimum of the right subtree is moved to the current position with its left subtree being the current left subtree
	                 delete curr;//current node deleted
	                 return ptr2;//the right subtree is attached to the current node
	            }
	        }
	        
	        else if(value<curr->data)  //if the value to the deleted is lesser than the value at the current node
	        curr->left=delet(curr->left,value);   //the node to be deleted might be on the left subtree 
	        
	        else     //if the value to the deleted is greater than the value at the current node
	        curr->right=delet(curr->right,value);  //the node to be deleted might be on the right subtree
	        
	        return curr;   //the current node is returned to be attached to the tree
	    }
	    //height of tree
	    int height()
	    {
	        return height(root);
	    }
	    //helper for height
	    int height(Node* curr)
	    {
	        if(curr==NULL)
	        return 0;
	        else 
	        {
	            int leftHeight=height(curr->left);
	            int rightHeight=height(curr->right);
	            if(leftHeight>rightHeight)
	            return (1+leftHeight);
	            else
	            return (1+rightHeight);
	        }
	    }
	    //range search 
	    int rangeeSearch(int k1,int k2)
	    {
	        return rangeSearch(root,k1,k2);
	    }
	    // helper for range search
	    int rangeSearch(Node* curr,int k1,int k2)
	    {
	    	if(curr!=NULL)
	        {
	            if(curr->data>k1&&curr->data<k2)
		    	{
	           	cout<<curr->data<<", ";//it is printed
	            	return (1+rangeSearch(curr->left,k1,k2)+rangeSearch(curr->right,k1,k2));//and counted along with those in its left subtree and the right subtree
		    	}
		    	else
		    	return rangeSearch(curr->left,k1,k2)+rangeSearch(curr->right,k1,k2);//elements in the range of its left subtree and right subtree and counted 
			}
	        else//if the end of the tree is reached
	        return 0;//base case 
		}
};

int main(){
	
	BiST b1;
	
	b1.insert(10);
	b1.insert(14);
	b1.insert(6);
	b1.insert(4);
	b1.insert(8);
	b1.insert(12);
	b1.insert(16);
	
	b1.display();
	cout<<"*******************************"<<endl;
	b1.displayfancy();
	cout<<"*******************************"<<endl;
	Node* ptr=b1.search(10);
	if(b1.search(10) != NULL)
	{
        cout << endl << b1.search(10)->data << " found." << endl;
        cout << "the entered value is present at address "<<ptr<<endl;
    }
    cout<<"*******************************"<<endl;
    int v = b1.count(b1.root);
    cout<<"the count is "<<v<<endl;
    
   	cout<<"*******************************"<<endl;
    cout<<"the minimum is "<<b1.findMin(b1.root)->data<<endl;
    cout<<"*******************************"<<endl;
    cout<<"the height is "<<b1.height()<<endl;
    cout<<"*******************************"<<endl;
    cout<<b1.rangeeSearch(4,14)<</" present in between the given range 4 to 14."endl;
    
    b1.delet(8);
    
    cout<<"*******************************"<<endl;
    b1.display();
    cout<<"*******************************"<<endl;
	b1.displayfancy();
	cout<<"*******************************"<<endl;
    
    int w = b1.count(b1.root);
    cout<<"the count is "<<w<<endl;
    
   	cout<<"*******************************"<<endl;
    cout<<"the minimum is "<<b1.findMin(b1.root)->data<<endl;
    cout<<"*******************************"<<endl;
   
	return 0;
}