// C program to insert a node in AVL tree
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
 
// An AVL tree node
typedef struct Dados
{
    int index;
    int ip;
} Dados_t;

struct Node
{
    //int key;
    Dados_t dados;
    struct Node *left;
    struct Node *right;
    int height;
};

struct Lista
{
    Dados_t dados;
    struct Lista *next;
};

/* Programa principal para testes

*/
int main()
{
    struct Node *root = NULL;
    struct Lista *root_lista = NULL;
    int i, level = 0; 
    struct Dados dados, result;

    /*
    struct sockaddr_in antelope;
    char *some_addr;
    
    inet_aton("0.0.0.1", &antelope.sin_addr); // store IP in antelope
    cout << antelope.sin_addr.s_addr << endl;
    
    some_addr = inet_ntoa(antelope.sin_addr); // return the IP
    printf("%s\n", some_addr); // prints "10.0.0.1"
    
    // and this call is the same as the inet_aton() call, above:
    antelope.sin_addr.s_addr = inet_addr("10.0.0.1");

    vector<string> file_data;
    */

    read_file("input.txt", file_data);
    cout << "Size:" << file_data.size() << endl;
    for (i = 0; i < file_data.size(); i++)
    {
        dados.index = i;
        stringstream str(file_data.at(i));
        str >> dados.ip;
        //cout << dados.ip << endl;
        root = insert(root, dados);
    }

    cout << "Preorder: " << endl;

    preOrder(root, root_lista);

    result = getNode(root, 10101);
    if (result.ip != 0)
    {
        cout << "\n\nEncontrou o " << result.ip << " no indice: " << result.index << endl;
    }
    //display(root, level);
    
    return 0;
}
 
// A utility function to get maximum of two integers
int max(int a, int b);
 
// A utility function to get height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(Dados_t dados)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->dados  = dados;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Dados_t getNode(struct Node *root, int key)
{
    Dados_t dados_null;
    if (root == NULL)
    {
        return dados_null;
    }
    else if (key == root->dados.ip)
    {
        return root->dados;
    }
    else if (key < root->dados.ip)
    {
        return getNode(root->left, key);
    }
    else
    {
        return getNode(root->right, key);
    }
}
 
// Recursive function to insert key in subtree rooted
// with node and returns new root of subtree.
struct Node* insert(struct Node* node, Dados_t dados)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(dados));
 
    if (dados.ip < node->dados.ip)
        node->left  = insert(node->left, dados);
    else if (dados.ip > node->dados.ip)
        node->right = insert(node->right, dados);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && dados.ip < node->left->dados.ip)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && dados.ip > node->right->dados.ip)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && dados.ip > node->left->dados.ip)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && dados.ip < node->right->dados.ip)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree, return the
   node with minimum key value found in that tree.
   Note that the entire tree does not need to be
   searched. */
   struct Node * minValueNode(struct Node* node)
   {
       struct Node* current = node;
    
       /* loop down to find the leftmost leaf */
       while (current->left != NULL)
           current = current->left;
    
       return current;
   }

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct Node* deleteNode(struct Node* root, Dados_t dados)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( dados.ip < root->dados.ip )
        root->left = deleteNode(root->left, dados);
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( dados.ip > root->dados.ip )
        root->right = deleteNode(root->right, dados);
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node* temp = minValueNode(root->right);
 
            // Copy the inorder successor's data to this node
            root->dados.ip = temp->dados.ip;
 
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->dados);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}
 
// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(struct Node *root, struct Lista *root_lista)
{
    struct Lista *current = root_lista;
    if(current == NULL)
    current = (struct Lista*) malloc(sizeof(struct Lista));

    if(root != NULL && current != NULL)
    {
        cout << "(" << root->dados.index << "," << root->dados.ip << ")" << endl;
        
        /*
        while (current->next != NULL)
        {
            current = current->next;
        }
        
        
        struct Lista* lista = (struct Lista*) malloc(sizeof(struct Lista));

        lista->dados = root->dados;
        lista->next = NULL;
        current->next = lista;
        */

        preOrder(root->left, current);
        preOrder(root->right, current);
        
    }
}

void display(struct Node *root, int level)
{
    int i, tmp;
    //if (root != NULL)
    //{
        if (root->right)
        { 
            tmp = level ++;
            printf ("level: %d.\n",tmp);
            display(root->right, tmp);
            for (i=0; i<tmp; i++) printf ("\t");
            printf ("    /");
            
        }
        //for (i=0; i<tmp; i++) printf ("\t");
        printf ("%d\n", root->dados.ip);

        if (root->left)
        { 
            tmp = level ++;
            display(root->left, tmp);
            for (i=0; i<tmp; i++) printf ("\t");
            printf ("    \\");
            
        }
        //for (i=0; i<tmp; i++) printf ("\t");
        printf ("%d\n", root->dados.ip);
    //}
}

void read_file(string file_name, std::vector<string> &t_lines)
{
    fstream file;
    string line;

    file.open (file_name, ios::in);
    if (!file.is_open())
    {
        cout << "Erro ao carregar o arquivo";
        return;
    }

    while(getline(file, line ))
    {
        // Remover os '.' dos IPs
        line.erase(remove(line.begin(), line.end(), '.'), line.end());
        t_lines.push_back(line);
        //cout << t_lines[i];
    }

}

