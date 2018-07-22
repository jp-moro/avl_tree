// C program to insert a node in AVL tree
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Graph.cpp"
#include "SequentialBFS_AvlTree.cpp"

using namespace std;
 
// An AVL tree node
typedef struct tDados
{
    int index;
    int ip;
}Dados;

typedef struct tNode
{
    struct tDados dados;
    struct tNode *left;
    struct tNode *right;
    int height;
}Node;

 
// A utility function to get maximum of two integers
int max(int a, int b);
 
// A utility function to get height of the tree
int height(Node *N)
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
 Node* newNode(Dados dados)
{
    Node* node = (Node*)
                        malloc(sizeof(Node));
    node->dados  = dados;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
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
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
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
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Dados getNode(Node *root, int key)
{
    Dados dados_null;
    //cout << key << "|" << root->dados.ip << endl;
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
Node* insert(Node* node, Dados dados)
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
Node * minValueNode(Node* node)
{
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
Node* deleteNode(Node* root, Dados dados)
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
            Node *temp = root->left ? root->left : root->right;
 
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
            Node* temp = minValueNode(root->right);
 
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

// Inicializa um novo grafo
Graph criaGrafo(int qtdNos)
{
    Graph G;
    double posx,posy,normaliza;
    int i;

    G.V.resize(qtdNos);
    G.Value.resize(qtdNos);
    G.posX.resize(qtdNos);
    G.posY.resize(qtdNos);
    G.listAdj.resize(qtdNos);

    return G;
}
 
// Percorre a árvore em preorder
// Armazenando um vetor com os nós
// E preenchendo o grafo
void preOrder(Node *root, vector<Dados> lista, Graph *G)
{
    Dados dados_no;
    List elemento_G;

    if(root != NULL)
    {
        //cout << "(" << root->dados.index << "," << root->dados.ip << ")" << endl;
        
        dados_no = root->dados;

        G->V[dados_no.index] = dados_no.index;
        G->Value[dados_no.index] = dados_no.ip;
        //cout << "Vértice: " << dados_no.index;
        cout << "Vértice: (" << dados_no.index << "," << dados_no.ip << ")";
        if (root->left != NULL)
        {
            elemento_G.v = root->left->dados.index;
            elemento_G.cost = 1;
            G->listAdj[dados_no.index].push_back(elemento_G);
            //cout << " Esquerda: " << elemento_G.v;
            cout << " Esquerda: (" << root->left->dados.index << "," << root->left->dados.ip << ")" ;
        }
        if (root->right != NULL)
        {
            elemento_G.v = root->right->dados.index;
            elemento_G.cost = 1;
            G->listAdj[dados_no.index].push_back(elemento_G);
            //cout << " Direita: " << elemento_G.v;
            cout << " Direita: (" << root->right->dados.index << "," << root->right->dados.ip << ")" ;
        }

        cout << endl;

        lista.push_back(dados_no);

        preOrder(root->left, lista, G);
        preOrder(root->right, lista, G);
    }
}

void escreveSaidaTree (string saida, Graph G, int root_key)
{
    fstream arquivoSaida;
    string headerListAdj = "LINKS_SOURCE_DESTINATION_DISTANCE";
    string headerCoord = "COORD_X_Y";
    int links = 0;

    arquivoSaida.open(saida.data(),ios::out);

    arquivoSaida << headerCoord << " " << G.V.size() << endl;
    for(int i=0;i<G.posX.size();i++)
        arquivoSaida << setw(9) << G.posX[i] << " " << setw(9) << G.posY[i] << endl;

    for(int i=0;i<G.listAdj.size();i++)
        links += G.listAdj[i].size();
    
    arquivoSaida << headerListAdj << " " << links << endl;
    //arquivoSaida << headerListAdj << " " << links << " " << root_key << endl; //Gravar raiz da árvore

    for(int i=0;i<G.listAdj.size();i++)
    {
        for(int j=0;j<G.listAdj[i].size();j++)
        {
            arquivoSaida << setw(6) << i << " " << setw(6) << G.listAdj[i][j].v << " " << setw(6) << G.listAdj[i][j].cost << endl;
        }
    }
    arquivoSaida.close();
}

vector<string> read_file(string file_name)
{
    fstream file;
    string line_file, line;
    const char* line_c;
    struct sockaddr_in line_ip;
    vector<string> t_lines;

    file.open (file_name, ios::in);
    if (!file.is_open())
    {
        cout << "Erro ao carregar o arquivo";
        return t_lines;
    }

    while(getline(file, line_file))
    {
        /*
        // Transformar os IPs em inteiros, para serem inseridos na árvore
        line_c = NULL;
        line.clear();

        line_c = line_file.c_str();

        //cout << line_c << endl; // IPs
        inet_aton(line_c, &line_ip.sin_addr); // get integer IP
        line = to_string(line_ip.sin_addr.s_addr);
        //cout << line << endl; // Inteiros
        t_lines.push_back(line);
        */   
        t_lines.push_back(line_file);
    }
    return t_lines;
}

void read_file_to_tree(string file_name, vector<string> &t_lines, Node *root)
{
    Dados dados;
    int len;

    t_lines = read_file(file_name);
    len = t_lines.size();

    //cout << "Size:" << len << endl;
    //for (int i=0; i<len; i++)
    //{
        cout << "teste";
        dados.index = 1;
        
        stringstream str(t_lines.at(1));
        str >> dados.ip;
        //cout << dados.ip << endl;
        cout << "teste";
        root = insert(root, dados);
    //}
}

/* Programa principal para testes

*/
int main(int argc, char** argv)
{
    int i, level = 0;
    int root_key = 0, key_to_find;
    string file_name_grafo = "GraphAVLTree.txt";
    Node *root = NULL;
    Graph G;

    vector<string> file_data;
    vector<Dados> root_lista;

    if (argc < 3)
    {
        cout << "Informe o arquivo e o nº buscado." << endl;
        return 0;
    }
    else
    {
        key_to_find = atoi(argv[2]);
    }

    //read_file("input.txt", file_data);
    /*
    read_file(argv[1], file_data);
    cout << "Size:" << file_data.size() << endl;
    for (i = 0; i < file_data.size(); i++)
    {
        dados.index = i;
        stringstream str(file_data.at(i));
        str >> dados.ip;
        //cout << dados.ip << endl;
        root = insert(root, dados);
    }
    */
    read_file_to_tree(argv[1], file_data, root);

    root_key = root->dados.index;

    cout << "Root: (" << root_key << "," << root->dados.ip << ")" << endl;
    cout << "Preorder Tree:" << endl;

    G = criaGrafo(file_data.size());

    preOrder(root, root_lista, &G);

    escreveSaidaTree(file_name_grafo, G, root_key);

    cout << endl << "Adjacent List:" << endl;
    bfs(G, root_key, key_to_find);
    
    return 0;
}