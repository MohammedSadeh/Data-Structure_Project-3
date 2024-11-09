/*
Name : Mohammed Jamil Saada.
ID : 1221972
Section : 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE 100

struct node;
struct queue;
typedef struct node* AVLTree;
typedef struct queue* ptq;
typedef struct cell Cell;
typedef struct Hash* hash;

// Struct of AVL tree
struct node{
    char* str;
    int frequency;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

// Struct of Queue
struct queue{
    char* token;
    ptq next;
    ptq front;
    ptq rear;
};

// Struct of the cell in hash table
struct cell{
    char* str;
    char status;
    int frequency;
};

// Struct of the Hash, contains array of Cells and number of loaded data, and the table size
struct Hash{
    Cell* hash_table;
    int loaded_Data;
    int table_size;
};

//functions prototype
//***************************************************
void display_menu();
int checkAlpha(char);
char* removeNoneAlpha(char*);
char* shiftLeft(char* str, int from);
ptq createQueue();
void EnQueue(ptq Q, char* tok);
ptq DeQueue(ptq Q);
void loadFile(ptq Q);
int getHeight(AVLTree);
int MAX(int, int);
AVLTree singleRotateLeft(AVLTree);
AVLTree singleRotateRight(AVLTree);
AVLTree doubleRotateLeft(AVLTree);
AVLTree doubleRotateRight(AVLTree);
AVLTree insert(AVLTree, char* token,int freq);
AVLTree Find_min(AVLTree T);
AVLTree delete_from_AVL(AVLTree T, char* token);
void printInOrder(AVLTree);
AVLTree createTree(ptq);
AVLTree insertNewWord(AVLTree);
AVLTree searchNode(char*, AVLTree);
int Find_Nodes_Num(AVLTree T,int sum);
unsigned int hash_index(char* token, unsigned int H_Size, int i);
int isPrime(int);
int prime_greater_than(int x);
hash initialize_hashTable(int table_size);
hash insert_to_hashTable(char* token, int freq, hash b);
hash insert_from_AVL_to_Hash(hash H,AVLTree T);
hash create_Hash(AVLTree T);
hash rehash(hash H);
int search_from_hashTable(char* token, hash H);
hash insert_newWord_toHash(hash H);
hash delete_word_from_hashTable(hash H);
int printUnique(AVLTree T,int sum);
AVLTree mostFreq(AVLTree T, AVLTree h);
int print_repeated_more_than(AVLTree T, int threshold, int sum);
void printWordStatisticsFromAVL(AVLTree T);
void printWordStatisticsFromHash(hash H);
//***************************************************

int main()
{
    ptq Q = createQueue();
    AVLTree T = NULL;
    hash H = NULL;
    int choice;
    printf("Welcome to Project 3 ... AVL tree & Hash Table\n");
    display_menu();
    scanf("%d",&choice);
    //before loaded the input file, you can't do any operation
    while(choice != 1 && choice != 12){
        printf("You can't do any operation before loaded the input file..\n");
        display_menu();
        scanf("%d",&choice);
        }
    while(choice != 12){
        switch(choice){
            case 1 : loadFile(Q);
                     break;
            case 2 : if(T != NULL){
                     printf("The AVL tree already created..\n");
                     break;
                     }
                     else{
                            T = createTree(Q);
                            printf("AVL Tree created Successfully..\n");
                            break;
                     }
            case 3 : if(T == NULL){
                      printf("You can't do this operation before create the AVL tree.\n");
                      break;
                      }
                      else{
                        T = insertNewWord(T);
                        break;
                      }
            case 4 : if(T == NULL){
                      printf("You can't do this operation before create the AVL tree.\n");
                      break;
                      }
                      else{
                        char token[20];
                        printf("Enter what you want to delete from AVL tree.\n");
                        scanf("%s",token);
                        AVLTree temp = searchNode(token,T);
                        if(temp != NULL){
                            if(temp->frequency > 1){
                                int x;
                                printf("%s ----> frequency = %d\n",token,temp->frequency);
                                printf("1- Delete the word.\n");
                                printf("2- Reduce the word frequency.\n");
                                scanf("%d",&x);
                                switch(x){
                                case 1 : T = delete_from_AVL(T,token);
                                         printf("%s deleted successfully from AVL Tree..\n",token);
                                         break;
                                case 2 : printf("Enter the number that you want to reduce frequency by\n");
                                         int f;
                                         scanf("%d",&f);
                                         temp->frequency -=f;
                                         printf("%s frequency reduced by %d..\n",token,f);
                                         break;
                                default : printf("Invalid option\n");
                                }
                            }
                            else{
                                printf("%s ----> frequency = 1 , so delete it.\n",token);
                                T = delete_from_AVL(T,token);
                                printf("%s deleted successfully from AVL tree\n",token);
                            }
                          }
                          else
                            printf("%s is not exist in the AVL Tree..\n",token);
                          break;
                      }
            case 5 : if(T == NULL){
                      printf("You can't do this operation before create the AVL tree.\n");
                      break;
                      }
                      else{
                        printInOrder(T);
                        printf("\n");
                        break;
                      }
            case 6 : if(T == NULL){
                      printf("You can't do this operation before create the AVL tree.\n");
                      break;
                      }
                      else{
                        if(H != NULL){
                            printf("The Hash table already created..\n");
                            break;
                        }
                        else{
                            H = create_Hash(T);
                            printf("Hash table created successfully..\n");
                            break;
                        }
                      }
            case 7 : if(H==NULL){
                     printf("You can't do this operation before create the Hash table.\n");
                     break;
                     }
                     else{
                        H = insert_newWord_toHash(H);
                        break;
                     }
            case 8 : if(H==NULL){
                     printf("You can't do this operation before create the Hash table.\n");
                     break;
                     }
                     else{
                        H = delete_word_from_hashTable(H);
                        break;
                     }
            case 9 : if(H==NULL){
                     printf("You can't do this operation before create the Hash table.\n");
                     break;
                     }
                     else{
                        char* token[20];
                        printf("Enter what you want to search in the Hash table.\n");
                        scanf("%s",token);
                        int i = search_from_hashTable(token,H);
                        if(i == -1)
                            printf("%s is not found in the Hash table.\n",token);
                        else
                            printf("%s ---> frequency = %d\n",H->hash_table[i].str,H->hash_table[i].frequency);
                        break;
                     }
            case 10 : if(T == NULL)
                            printf("you can't do this operation before create the AVL Tree.\n");
                        else
                            printWordStatisticsFromAVL(T);
                      break;
            case 11 : if(H == NULL)
                            printf("you can't do this operation before create the Hash table.\n");
                      else
                            printWordStatisticsFromHash(H);
                      break;
            default : printf("Invalid operation, try again...\n");
        }
        display_menu();
        scanf("%d",&choice);
    }

    printf("Exit from the program...\n");
    printf("Thank you for using my program...\n");
    //when exit the program, free the memory size that allocated for this program
    free(Q);
    free(T);
    free(H);

    return 0;
}
//function to display the menu
void display_menu(){
    printf("1- Load data from the file.\n");
    printf("2- Create the AVL tree.\n");
    printf("3- Insert a word to the AVL tree.\n");
    printf("4- Delete a word from the AVL tree.\n");
    printf("5- Print the words as sorted in the AVL tree.\n");
    printf("6- Create the Hash table.\n");
    printf("7- Insert a word to the Hash table.\n");
    printf("8- Delete a word from the Hash table.\n");
    printf("9- Search for a word in the hash table and print its frequency.\n");
    printf("10- Print words statistics from AVL Tree.\n");
    printf("11- Print words statistics from Hash table.\n");
    printf("12- Exit the application.\n");
}

//function to clean the text from non alphabetical character
char* removeNoneAlpha(char* str){
    for(int i=0; i < strlen(str); i++){
        if(!checkAlpha(str[i])){
            str = shiftLeft(str,i);
            i--;
        }
    }
    return strdup(str);
}

//function to check alphabetical character
int checkAlpha(char c){
    if((c>= 'a' && c<= 'z') || (c>= 'A' && c<= 'Z'))
        return 1;

    else
        return 0;

}

//function to left shift character in string (to remove thing in specific place in string)
char* shiftLeft(char* str,int from){
        int i;
        int len = strlen(str);
        char a[len];
        strcpy(a,str);
        for (i = from; i <len; i++){
            a[i] = a[i+1];
        }
        str = a;
        return strdup(str);
}

//function to create Queue
ptq createQueue(){
    ptq T = (ptq)malloc(sizeof(struct queue));
    if(T==NULL){
        printf("Out of size..\n");
        return NULL;
        }
    else {
        T->next = NULL;
        T->front = T->next;
        T->rear = T->next;
        return T;
        }
}

//function to enqueue node to queue
void EnQueue(ptq Q, char* tok){
    if(Q == NULL)
        printf("Queue not exist..\n");
    else {
            ptq New = (ptq)malloc(sizeof(struct queue));
            New->token = tok;
            New->front = NULL;
            New->rear = NULL;
            ptq temp = Q->rear;
            if(temp != NULL){
                temp->next = New;
                New->next = NULL;
                Q->rear = New;
                Q->front = Q->next;
            }
            else {
                Q->next = New;
                New->next = NULL;
                Q->front = New;
                Q->rear = New;
            }
    }

}

//function to dequeue node from queue
ptq DeQueue(ptq Q){
    if(Q == NULL){
        printf("Queue not exist..\n");
        return NULL;
    }
    else {
        if(Q->front == NULL){
            printf("Queue is Empty..\n");
            return NULL;
        }
        else {
            ptq temp = Q->front;
            Q->next = temp->next;
            Q->front = Q->next;
            if(Q->front==NULL)
                Q->rear = NULL;
            temp->next = NULL;
            return temp;
        }
    }
}

//function to load text from file and store each word in the queue data structure
void loadFile(ptq Q){
    FILE* input = fopen("input.txt","r");
        if(input==NULL)
            printf("The file can't be opened..\n");
        else{
            char* myString[LINE];
            char* s = fgets(myString,LINE,input);
            while(s!=NULL){

                char* temp = strtok(s," ");
                while(temp != NULL){
                    temp = removeNoneAlpha(temp);
                    if(strlen(temp) != 0 && temp[0] != '\n')
                        EnQueue(Q,strdup(temp));
                    temp = strtok(NULL," ");
                }
                    s = fgets(myString,LINE,input);
            }
                printf("Data loaded successfully from the file..\n");
                fclose(input);
        }
}

//function to return height to specific node in th AVL tree
int getHeight(AVLTree tree){
    if(tree==NULL)
        return -1;
    else
        return tree->Height;
}

//function to return a max integer from two integers
int MAX(int x, int y){
    if(x>y)
        return x;
    else
        return y;
}

//function to Single Rotate Left the AVL tree
AVLTree singleRotateLeft(AVLTree x){
    AVLTree y;
    y = x->Right;
    x->Right = y->Left;
    y->Left = x;

    x->Height = 1 + MAX(getHeight(x->Left) , getHeight(x->Right));
    y->Height = 1 + MAX(getHeight(x) , getHeight(y->Right));

    return y;
}

//function to Single Rotate Right the AVL tree
AVLTree singleRotateRight(AVLTree y){
    AVLTree x;
    x = y->Left;
    y->Left = x->Right;
    x->Right = y;

    y->Height = 1 + MAX(getHeight(y->Right) , getHeight(y->Left));
    x->Height = 1 + MAX(getHeight(y) , getHeight(x->Left));

    return x;
}

//function to double Rotate Left - Right the AVL tree
AVLTree doubleRotateLeft(AVLTree tree){
    tree->Left = singleRotateLeft(tree->Left);
    return singleRotateRight(tree);
}

//function to double Rotate Right - Left the AVL tree
AVLTree doubleRotateRight(AVLTree tree){
    tree->Right = singleRotateRight(tree->Right);
    return singleRotateLeft(tree);
}

//function to insert node to the AVL tree
AVLTree insert(AVLTree t, char* token, int freq){
    //reach to the appropriate place to insert after recursion
    if(t==NULL){
        t = (AVLTree)malloc(sizeof (struct node));
        t->str = strdup(token);
        t->Height=0;
        t->frequency = freq;
        t->Left= t->Right=NULL;
    }
    //if the node is already exist, add 1 to its frequency
    else if(strcasecmp(token,t->str) == 0){
        t->frequency += freq;
        return t;
    }
    //if the node is less than the specific node (root) add it to the left of this root by recursion
    else if(strcasecmp(token,t->str) < 0){
        t->Left=insert(t->Left,token,freq);
        //check the balance after insert the node
        if(getHeight(t->Left) - getHeight(t->Right) >= 2 || getHeight(t->Left) - getHeight(t->Right) <= -2){
            //if the balance is not -1,0,1
            //case Left - Left ----> Single Right Rotation
            if(strcasecmp(token,t->Left->str) < 0)
                t=singleRotateRight(t);
            //case Left - Right ----> Double Left - Right Rotation
            else
                t=doubleRotateLeft(t);
        }
    }
    //if the node is greater than the specific node (root) add it to the right of this root by recursion
    else if(strcasecmp(token,t->str) > 0){
        t->Right = insert(t->Right , token, freq);
        //check the balance after insert the node
        if(getHeight(t->Right) - getHeight(t->Left) >= 2 || getHeight(t->Left) - getHeight(t->Right) <= -2){
            //if the balance is not -1,0,1
            //case Right - Right ----> Single Left Rotation
            if(strcasecmp(token,t->Right->str) > 0)
                t=singleRotateLeft(t);
            //case Right - Left ----> Double Right - Left Rotation
            else
                t=doubleRotateRight(t);
        }
    }
    //after insert the node update the height of the node
    t->Height = 1 + MAX(getHeight(t->Right) , getHeight(t->Left));

    return t;
}

//function to find minimum node in the AVL tree
AVLTree Find_min(AVLTree T){
    if(T == NULL)
        return NULL;
    else
        if(T->Left == NULL)
            return T;
    else
        return Find_min(T->Left);
}

//function to delete node from the AVL tree
AVLTree delete_from_AVL(AVLTree T, char* token){
    AVLTree temp, child;
    //after search by recursion if reach to the NULL, then the word is not exist
    if(T == NULL){
        printf("The word that you want to delete don't exist..\n");
        return T;
    }
    //if the node to be deleted is less than the root then search left by recursion
    else if(strcasecmp(token,T->str) < 0)
        T->Left = delete_from_AVL(T->Left,token);
    //if the node to be deleted is greater than the root then search right by recursion
    else if(strcasecmp(token,T->str) > 0)
        T->Right = delete_from_AVL(T->Right,token);
    //if reach to the node to be deleted
    else if(T->Left && T->Right){ //the node has two children
        temp = Find_min(T->Right); //Find minimum node in the right of the node to be deleted
        T->str = strdup(temp->str); //copy the minimum node in the right to the node to be deleted
        T->frequency = temp->frequency;
        T->Right = delete_from_AVL(T->Right,temp->str); //delete the minimum node in the right (the node that copied to the node that we want to delete)
    }
    else { //the node has no children or has one children
        temp = T;
        //copy the children (if exist)
        if(T->Left == NULL)
            child = T->Right;
        else if(T->Right == NULL)
            child = T->Left;
        free(temp); //delete the node
        return child;
    }
    //after delete the node if exist, update the balance
    T->Height = MAX(getHeight(T->Right) , getHeight(T->Left)) + 1;
    //check the new balance
    if(getHeight(T->Left) - getHeight(T->Right) >= 2 || getHeight(T->Left) - getHeight(T->Right) <= -2){
        //if the balance is not -1,0,1
        // Left - Left Case ----> Single Right Rotation
        if(getHeight(T->Left) >= getHeight(T->Right) && getHeight(T->Left->Left) >= getHeight(T->Left->Right))
            T = singleRotateRight(T);
        // Right - Right Case ----> Single Left Rotation
        else if (getHeight(T->Right) >= getHeight(T->Left) && getHeight(T->Right->Right) >= getHeight(T->Right->Left))
            T = singleRotateLeft(T);
        // Left - Right Case ----> Double Left - Right Rotations
        else if(getHeight(T->Left) >= getHeight(T->Right) && getHeight(T->Left->Right) >= getHeight(T->Left->Left))
            T = doubleRotateLeft(T);
        // Right - Left Case ----> Double Right - Left Rotations
        else if(getHeight(T->Right) >= getHeight(T->Left) && getHeight(T->Right->Left) >= getHeight(T->Right->Right))
            T = doubleRotateRight(T);

    }
    return T;
}

//print the AVL tree in order
// Left - Root - Right
void printInOrder(AVLTree t){
    if(t!= NULL){
       printInOrder(t->Left); //Left
       printf("%s -> frequency = %d\n",t->str,t->frequency); //Root
       printInOrder(t->Right); // Right
    }
}

//function to create AVL tree, and store the date from the Queue (data in File)
AVLTree createTree(ptq Q){
    AVLTree tree = NULL;
    while (Q->front != NULL){
        ptq temp = DeQueue(Q);
        tree = insert(tree,strdup(temp->token),1);
        free(temp);
    }
    return tree;
}

//function to insert word to the AVL tree from user
AVLTree insertNewWord(AVLTree T){
    char newWord[20];
    printf("Enter the word that you want to insert\n");
    scanf("%s",newWord);
    strcpy(newWord,removeNoneAlpha(newWord)); //clean the word from non alphabetical character
    if(strlen(newWord) == 0) //after clean if the word length is zero, so the word don't exist any alpha character
        printf("The word you entered hasn't alphabetical character..\n");
    else{
        printf("Enter the frequency for this word..\n");
        int freq=1;
        scanf("%d",&freq);
        if(searchNode(newWord,T) != NULL)
            printf("%s is already exist, increase its frequency by %d\n",newWord,freq);
        else
            printf("%s inserted to the AVL tree successfully..\n",newWord);
        T = insert(T,newWord,freq);
    }
    return T;
}

//function to search about the node in the AVL tree by it's value
AVLTree searchNode(char* tok, AVLTree t){
    if(t == NULL)
    // if the word is not exist return NULL
        return NULL;
    if(strcasecmp(tok,t->str) < 0)
    // if the word is less than this node search left by recursion
        return searchNode(tok,t->Left);
    else if(strcasecmp(tok,t->str) > 0)
    // if the word is greater than this node search right by recursion
        return searchNode(tok,t->Right);
    else
    // if the word is equal to this node, so we found it, return it
        return t;
}

//function to find the number of nodes in the AVL tree to use it in building the Hash table
int Find_Nodes_Num(AVLTree T,int sum){
    if (T != NULL){
        sum = Find_Nodes_Num(T->Left,sum);
        sum ++;
        sum = Find_Nodes_Num(T->Right,sum);
    }
    return sum;
}

//function to find the hash index to the word, depending on its character value
unsigned int hash_index(char* token, unsigned int H_Size, int i){
    // i is use if there is a collision then increment i by 1 and calculate the next possible index
    unsigned int hashValue = 0;
    char* newTok = strdup(token);
    strlwr(newTok); //calculate the index to the word by its lower alphabetical character, case not sensitive <capital is the same to the small>
    int h,hp;
    while(*newTok != '\0')
        hashValue = (hashValue << 5) + *newTok++; //shift right 5 bit, multiple by 32

    h = hashValue % H_Size;
    hp = 1 + (hashValue % (H_Size - 1));

    hashValue = (h + i * hp) % H_Size; //if there is a collision we increment i by 1 to calculate the second possible index
    return hashValue;

}

//function to check integer is prime or not
int isPrime(int x){
    if(x < 2)
        return 0;
    for (int i = 2; i <= x/2; i++){
        if(x%i == 0)
            return 0;
    }

    return 1;
}

//function to find a prime integer greater than the specific integer
int prime_greater_than(int x){
    if(isPrime(x))
        return x;
    else
        return prime_greater_than(x+1);
}

//function to initialize the hash table
hash initialize_hashTable(int table_size){
    hash H = (hash)malloc(sizeof(struct Hash)); //to allocate the appropriate size to the has
    if(H==NULL){
        // if there is no enough memory size
        printf("out of space..\n");
        return NULL;
    }
    else{
        H->hash_table = (Cell*)malloc(sizeof(Cell) * table_size); //to allocate size of memory to the hash table <array of cells>
        if(H->hash_table == NULL){
            //if there is no enough memory size
            printf("out of space..\n");
            return NULL;
        }
        else{
            for(int i=0; i<table_size; i++)
                H->hash_table[i].status = 'E'; //initialize all cells in the table by status E <empty>
            H->table_size = table_size;
            H->loaded_Data = 0; //initialize the loaded data by zero
            return H;
        }
    }

}

//function to insert a word to the hash table
hash insert_to_hashTable(char* token, int freq, hash b){
    int index = search_from_hashTable(token,b);
    if(index != -1){ // if the word already exist
        b->hash_table[index].frequency+=freq; //increment its frequency
    }
    else if(index == -1){
        index = hash_index(token,b->table_size,0); //calculate the index to the word to be inserted with i = 0
        if(b->hash_table[index].status == 'E' || b->hash_table[index].status == 'D'){ //if this index is empty or deleted, then insert to it
            b->hash_table[index].str = strdup(token);
            b->hash_table[index].frequency = freq;
            b->hash_table[index].status = 'O';
            b->loaded_Data++;
        }
        else {
            //if the first index is occupied (collision), then calculate the first possible index
            int i = 1;
            while(b->hash_table[index].status != 'E' && b->hash_table[index].status != 'D'){
                index = hash_index(token,b->table_size,i++);
            }
            b->hash_table[index].str = strdup(token);
            b->hash_table[index].frequency = freq;
            b->hash_table[index].status = 'O';
            b->loaded_Data++;
            }
        //after insert calculate the load Factor
        double loadFactor = (double)b->loaded_Data / b->table_size ;
        //if the load factor is greater than 0.65, then Rehash the hash table
        if(loadFactor >= 0.65)
            b = rehash(b);
    }
    return b;
}

//function to insert the AVL nodes to the hash table
hash insert_from_AVL_to_Hash(hash H,AVLTree T){
    if(T != NULL){
        H = insert_from_AVL_to_Hash(H,T->Left);
        H = insert_to_hashTable(T->str,T->frequency,H);
        H = insert_from_AVL_to_Hash(H,T->Right);
    }
    return H;
}

//function to create the Hash table
hash create_Hash(AVLTree T){
    int Nodes_Number = Find_Nodes_Num(T,0); //find the number of nodes in the AVL tree <the nodes that will added to the hash table>
    int hash_Size = (prime_greater_than(2*Nodes_Number)); //find the appropriate size of table by multiple number of nodes by 2 and find the fist prime greater than it
    hash H = initialize_hashTable(hash_Size); //initialize the hash table by the size that we calculate
    H = insert_from_AVL_to_Hash(H,T); //insert each node in the AVL to the Hash table
    return H;
}

//function to ReHash the table if the loaded factor is greater than 0.65
hash rehash(hash H){
    int newSize = prime_greater_than((2*H->table_size)); //calculate the new size by find the first prime number greater than 2 * old size
    hash newHash = initialize_hashTable(newSize); //initialize the new hash with new size
    for(int i=0; i<H->table_size; i++){ //insert each cell from the old hash table to the new one
        if(H->hash_table[i].status == 'O'){
            insert_to_hashTable(H->hash_table[i].str,H->hash_table[i].frequency,newHash);
        }
    }
    free(H); //free <delete> the old hash table
    printf("The loaded Factor is greater than 65%, So the REHASH is done.\n");
    return newHash;
}

//function to search about word in the hash table
int search_from_hashTable(char* token, hash H){
    int i = 0;
    int index;
    do{
        index = hash_index(token,H->table_size,i++); //calculate the index that expected contain the word
        if(H->hash_table[index].status == 'E') //if this index is empty, so the word is not exist return -1
            return -1;
        else if(H->hash_table[index].status == 'D' && (strcasecmp(H->hash_table[index].str,token)) == 0)
        // if this index is deleted and contain the word that we search about, then the word is not exist <deleted>
            return -1;
        else if(H->hash_table[index].status == 'O' && (strcasecmp(H->hash_table[index].str,token)) == 0)
        //if this index contain the word, then return this index
            return index;
    }while(H->hash_table[index].status != 'E'); //until we don't reach to empty cell and don't reach to the word that we search about,
                                                //calculate the next index that may contain the word and check it.
}

//function to insert a new word to hash table from user
hash insert_newWord_toHash(hash H){
    char token[20];
    int freq;
    printf("Enter the word that you want to insert to the Hash Table..\n");
    scanf("%s",token);
    printf("Enter the word frequency..\n");
    scanf("%d",&freq);
    strcpy(token,removeNoneAlpha(token)); //remove all non alphabetical character <clean the word>
    if(strlen(token) == 0) //after clean the word if the length is zero, then the word don't contain any alphabetical character
        printf("The word you entered don't exist an alphabetical character..\n");
    else{
        int i = search_from_hashTable(token,H);
        if(i != -1)
            printf("%s is already exist, the frequency increased by %d\n",token,freq);
        else
            printf("%s inserted to the Hash table successfully..\n",token);
        H  = insert_to_hashTable(token,freq,H);
    }
    return H;
}

//function to delete word from hash table by user
hash delete_word_from_hashTable(hash H){
    printf("Enter the word that you want to delete from the Hash table..\n");
    char tok[20];
    scanf("%s",tok);
    int index = search_from_hashTable(tok,H); //search about the word in the hash table
    if(index == -1) //if the word is not exist
        printf("The word that you want to delete is not exist..\n");
    else{
        if(H->hash_table[index].frequency > 1){
            int x;
            printf("%s ----> frequency = %d\n",tok,H->hash_table[index].frequency);
            printf("1- Delete the word.\n");
            printf("2- Reduce the word frequency.\n");
            scanf("%d",&x);
            switch(x){
                case 1 : H->hash_table[index].status = 'D';
                        printf("%s deleted from the Hash table successfully..\n",tok);
                        H->loaded_Data--;
                        break;
                case 2 : printf("Enter the number that you want to reduce frequency by it\n");
                         int f;
                         scanf("%d",&f);
                         if(H->hash_table[index].frequency - f < 1){
                            H->hash_table[index].status = 'D';
                            H->loaded_Data--;
                            printf("%s frequency is less than 1, so it deleted\n",tok);
                         }
                         else{
                            H->hash_table[index].frequency -= f;
                            printf("%s frequency reduced by %d..\n",tok,f);
                         }
                         break;
                default : printf("Invalid option, try again..\n");
            }
            }
        else {
            H->hash_table[index].status = 'D'; // if the word is exist update the status to D <deleted>
            printf("%s frequency is 1, so deleted from the Hash table..\n",tok);
            H->loaded_Data--; //update the number of loaded data by decrement 1 from it
        }
    }
    return H;
}

//function to print the unique words (frequency = 1) and return the total sum of these words
int printUnique(AVLTree T,int sum){
    if(T != NULL){
        sum = printUnique(T->Left,sum);
        if(T->frequency == 1){
            printf("%s ----> frequency = %d\n",T->str,T->frequency);
            sum++;
        }
        sum = printUnique(T->Right,sum);
    }
    return sum;
}

//function to return the node of the word that is most frequented
AVLTree mostFreq(AVLTree T, AVLTree h){
    if(T != NULL){
        h = mostFreq(T->Left,h);
        if(T->frequency > h->frequency)
            h = T;
        h = mostFreq(T->Right,h);
    }
    return h;
}

//function to print the word that repeated more then threshold and return the total sum of these words
int print_repeated_more_than(AVLTree T, int threshold, int sum){
    if(T != NULL){
        sum = print_repeated_more_than(T->Left,threshold,sum);
        if(T->frequency > threshold){
            printf("%s ----> frequency = %d\n",T->str,T->frequency);
            sum++;
        }
        sum = print_repeated_more_than(T->Right,threshold,sum);
    }
    return sum;
}

//function to print the word statistics from the AVL tree
void printWordStatisticsFromAVL(AVLTree T){
    int threshold;
    printf("Enter the threshold number to print the words that repeated more than it..\n");
    scanf("%d",&threshold);
    printf("The words statistics from the AVL Tree :\n\n");
    printf("The unique words are :\n");
    int sum = printUnique(T,0);
    printf("Total number of unique words = %d\n\n",sum);
    AVLTree temp = mostFreq(T,temp);
    printf("The most frequent word is\n%s ---> frequency = %d\n\n",temp->str,temp->frequency);
    printf("The word(s) repeated more than threshold = %d, are :\n",threshold);
    int k = print_repeated_more_than(T,threshold,0);
    if(k==0)
        printf("No words\n");
    printf("Total number of words repeated more than threshold (%d) is %d\n\n",threshold,k);
}

//function to print the word statistics from the Hash table
void printWordStatisticsFromHash(hash H){
    int threshold;
    printf("Enter the threshold number to print the words that repeated more than it..\n");
    scanf("%d",&threshold);
    printf("The words statistics from the Hash Table :\n\n");
    printf("The unique words are :\n");
    int total_unique = 0, total_threshold = 0;
    for(int i=0; i<H->table_size; i++){
        if(H->hash_table[i].status == 'O' && H->hash_table[i].frequency == 1){
            printf("%d %s ----> frequency = %d\n",i,H->hash_table[i].str,H->hash_table[i].frequency);
            total_unique++;
        }
    }
    printf("Total number of unique words = %d\n\n",total_unique);
    int index_most = 0;
    for(int i=0; i<H->table_size; i++){
        if(H->hash_table[i].status == 'O' && H->hash_table[i].frequency > H->hash_table[index_most].frequency)
            index_most = i;
    }
    printf("The most frequent word is\n%s ---> frequency = %d\n\n",H->hash_table[index_most].str,H->hash_table[index_most].frequency);
    printf("The word(s) repeated more than threshold = %d, are :\n",threshold);
    for(int i=0; i<H->table_size; i++){
        if(H->hash_table[i].status == 'O' && H->hash_table[i].frequency > threshold){
            printf("%d %s ----> frequency = %d\n",i,H->hash_table[i].str,H->hash_table[i].frequency);
            total_threshold++;
        }
    }
    if(total_threshold == 0)
        printf("No word\n");
    printf("Total number of words repeated more than threshold (%d) is %d\n\n",threshold,total_threshold);
}
