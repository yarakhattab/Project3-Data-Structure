// yara khattab 1210520
//sec 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct for the avl tree
typedef struct myAVLnode {
    char district[50];
    char town[50];
    int population;
    int elevation;
    char hasmunicipality[4];
    struct myAVLnode *left;
    struct myAVLnode *right;
    int height;
};

typedef struct myAVLnode *avltree;

//functions for the avl tree
int height(avltree tree);//function to get the height of the tree
int Max(int a, int b);// function to get the max
avltree CreateNode(char *district, char *town, int population, int elevation, char *hasmunicipality);// create a node in the tree
avltree singleleftrotation(avltree x);//single left rotation on the avl tree to fix balance if exist
avltree singlerightrotation(avltree y);//single right rotation on the avl tree to fix balance if exist
avltree doubleLeftRotation(avltree z);//double left rotation on the avl tree to fix balance if exist.
avltree doubleRightRotation(avltree y);//double right rotation on the avl tree to fix balance if exist.
avltree Insert(char *district, char *town, int population, int elevation, char *hasmunicipality, avltree tree);// function to insert a new node to the avl tree
void printinalphabeticalorder (avltree tree);// function to print the towns in alphabetical order
void readtheinputfile(avltree *root, char *filename);// get the data from the input file
avltree SearchforaTown(avltree tree, char *searchedtown);// search for a town in the avl tree
void updatetowninformation(avltree root);// update the information of a given town
void printtownswithpopulation(avltree tree, int minvaluepopulation);// print the town based on a given population
void printtownsgivenstatus(avltree tree, char *givenstatus);// print the town based on a given status (yes or no )
avltree deletegiventown(avltree tree, char *town);//delete a given town from the tree
void savetooutputfile(avltree tree, FILE *file);// function to save to output file


// struct for the hash
typedef struct myhashnode {
    char district[50];//the district
    char town[50];// the town
    int population;// the population
    int elevation; // the elevation
    char hasmunicipality[4]; // if the town has a Municipality
    int istaken;  //flag to check for the slot in the table
} myhashnode;

//define the hash table
typedef struct myhash {
    myhashnode *table;  // HashNodes
    int tablesize;         // Size of the hash table
} myhash;

//create the hash table
void createhashTable(myhash *hashTable, int size) {
    hashTable->tablesize = size;  // set the size of the hash table
    hashTable->table = (myhashnode *)malloc(size * sizeof(myhashnode));  // allocate memory for the table

    // Initialize all the table slots to default values
    for (int i = 0; i < size; i++) {
        hashTable->table[i].istaken = 0;  // set the istaken flag to 0 (not taken)
    }
}

//functions to the hash
void createhashTable(myhash *hashTable, int size);//create a hash table
int thehashfunction(int tableSize,char *town);// Hash function to have the first 5 characters only of the town name
int isnumprime(int num);//to check if a given number is prime or not
int nextpeimenum(int num); // find the next prime number
void inserttothetable(myhash *hashtable, char *district, char *town, int population, int elevation, char *hasmunicipality);// insert into the hash table using open addressing (linear probing)
void printhashtable(myhash *hashtable);// print the hash table
void insertthefiletohashtable(myhash *hashTable, char *filename);// function to read the output file and insert the data into the hash table
void printthesizeandloadfactor(myhash *hashtable);// function to print the size and load factor of the hash table
void inserttohashtable(myhash *hashtable);// insert a new record into the hash table
void Searchfortowninhash(myhash *hashtable, char *town);// search for a town in the hash table and print the number of collisions
void deletefromhashtable(myhash *hashtable, char *town);// delete a record from the hash table
void savefromtabletofile(myhash *hashtable,  char *filename);// save data in the hash table to a file


//******************implementation of the hash functions*****************************

// the hash function to have the first 5 characters only of the town name
int thehashfunction(int tableSize,char *town) {
    int theslothashvalue = 0;
    // calculate hash for the first 5 characters or less if the town is less than 5
    for (int i = 0; i < 5 && town[i] != '\0'; i++) {
        theslothashvalue = (theslothashvalue + town[i]) % tableSize; // formula
    }
    return theslothashvalue;
}

//check if a number is prime
int isnumprime(int num) {
    if (num < 2)
        return 0; // Not prime
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) // if it divide with reminder =0 so not prime
        return 0; // not prime
    }
    return 1; // prime
}

//find the next prime number after a given number
int nextpeimenum(int num) {
    while (!isnumprime(num)) { // check if it is not  prime
        num++; // move to the next num
    }
    return num;
}

// insert into the hash table using open addressing (linear probing)
void inserttothetable(myhash *hashtable, char *district, char *town, int population, int elevation, char *hasmunicipality) {
    int theslot = thehashfunction(hashtable->tablesize, town);  // get the first slot
    int originalslot = theslot; // store the first slot
    // linear probing to find an available slot
    while (hashtable->table[theslot].istaken) { // check if the slot is taken
        theslot = (theslot + 1) % hashtable->tablesize;  // linear probing
        if (theslot == originalslot) {  // check if the hash table full if reach the first slot
            printf(" THE HASH TABLE IS FULL!!!\n");
            return;
        }
    }
    // Insert data if an empty slot is found
    strcpy(hashtable->table[theslot].district, district);//copy the district into the table
    strcpy(hashtable->table[theslot].town, town);//copy the town into the table
    hashtable->table[theslot].population = population;//insert the popilaution
    hashtable->table[theslot].elevation = elevation;//insert the elevation
    strcpy(hashtable->table[theslot].hasmunicipality, hasmunicipality);//copy the status into the table
    hashtable->table[theslot].istaken = 1;  // mark this slot that is taken

}


// print the hash table
void printhashtable(myhash *hashtable) {
    printf("\nHASH TABLE CONTENTS:\n");
    for (int i = 0; i < hashtable->tablesize; i++) {  // for loop go through each slot in the table
        if (hashtable->table[i].istaken) {  // If the slot is taken => have a data so print it
            printf("SLOT %d: Town: %s, Population: %d, Elevation: %d, Has Municipality: %s\n",
                   i, hashtable->table[i].town, hashtable->table[i].population, hashtable->table[i].elevation, hashtable->table[i].hasmunicipality);
        } else {
            printf("SLOT %d: [THIS SLOT IS EMPTY!!]\n", i);  // If the slot is empty also print it
        }
    }
}



// function to read the output file and insert the data into the hash table
void insertthefiletohashtable(myhash *hashTable,char *filename ) {
    FILE *file = fopen(filename, "r");//start reading the file
    if (!file) { // check the file if exist
        printf("CAN NOT OPEN THE FILE!");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) { // read line by line from the file
        // remove newline character, if present
        line[strcspn(line, "\n")] = '\0';

        // split the line using (:)
        char *district = strtok(line, ":");//get the district
        char *town = strtok(NULL, ":"); // get the town  (key of the hash table)
        char *population = strtok(NULL, ":");//get the population as string
        char *elevation = strtok(NULL, ":");//get the elevation as string
        char *hasmunicipality = strtok(NULL, ":"); //get the hasMunicipality

        if (!district || !town || !population || !elevation || !hasmunicipality) { //check if there missing information in the line,skip it and continue
           printf("MISSING DATA IN THE LINE\n");
            continue;
        }

        // Convert population and elevation to integers
        int populationvalue = atoi(population);
        int elevationvalue = atoi(elevation);


        // Insert data to the hash table
        inserttothetable(hashTable, district,town, populationvalue, elevationvalue, hasmunicipality);


    }


    fclose(file);//close the file

}


// function to print the size and load factor of the hash table
void printthesizeandloadfactor(myhash *hashtable) {
    int takenncount = 0;  // count the number of taken slots in the table
    for (int i = 0; i < hashtable->tablesize; i++) {
        if (hashtable->table[i].istaken) {
            takenncount++;  // increment counter if the slot is taken
        }
    }

    double loadFactor = (double)takenncount / hashtable->tablesize;  // calculate load factor

    printf("THE HASH TABLE SIZE IS: %d\n", hashtable->tablesize);  // Print the table size
    printf("THE NUMBER OF TAKEN SLOTS (NUMBER OF TOWNS IN THE TABLE): %d\n", takenncount);  // Print number of taken slots
    printf("THE LOAD FACTOR: %.2f\n", loadFactor);  // print the load factor
}

// insert a new record into the hash table
void inserttohashtable(myhash *hashTable) {
    char town[50], hasmunicipality[4],district[50];
    int population, elevation;

    printf("PLEASE ENTER THE DISTRICT NAME: ");
    scanf("%s", district);//get the new district name

    printf("PLEASE ENTER THE TOWN NAME: ");
    scanf("%s", town);//get the new town name

    printf("PLEASE ENTER THE POPULATION: ");
    scanf("%d", &population);//get the population value

    printf("PLEASE ENTER THE ELEVATION: ");
    scanf("%d", &elevation); //get the elevation value

    printf("IT HAS MUNICIPALITY (yes/no): ");
    scanf("%s", hasmunicipality); //get the municipality status

    // insert the record into the hash table
    inserttothetable(hashTable,district, town, population, elevation, hasmunicipality);//insert to the table
    printf("RECOED INSERTED SUCCESSFULLY TO THE TABLE!!!\n");
}

// search for a town in the hash table and print the number of collisions
void Searchfortowninhash(myhash *hashtable,  char *town) {
    int theslot = thehashfunction(hashtable->tablesize, town); // get the slot
    int originalIndex = theslot;  // store the original slot
    int collisions = 0;//to count the number of collisions

    // Search for the town in the hash table using linear probing
    while (hashtable->table[theslot].istaken) {
        if (strcmp(hashtable->table[theslot].town, town) == 0) { // Compare the given town with the town in the table
            printf("TOWN '%s' FOUND IN SLOT %d.\n", town, theslot);
            printf("NUMBER OF COLLISIONS FOR THIS TOWN IS: %d\n", collisions);
            return;  // Town found
        }
        collisions++;  // Increment collisions if the slot is taken but not the given town
        theslot = (theslot + 1) % hashtable->tablesize;  // Linear probing to the next slot
        if (theslot == originalIndex) {
            break;  //if the table is full
        }
    }

    printf("TOWN '%s' NOT FOUND.\n", town);
}

// delete a record from the hash table
void deletefromhashtable(myhash *hashtable, char *town) {
    int theslot = thehashfunction(hashtable->tablesize, town);  // get the slot
    int originalIndex = theslot;  // Store the original slot
    int collisions = 0;//count the number of collisions

    // Search for the town in the hash table using linear probing
    while (hashtable->table[theslot].istaken) {
        if (strcmp(hashtable->table[theslot].town, town) == 0) { //compare the givven town with thhe town in th table
            hashtable->table[theslot].istaken = 0;  // if it is the town so delete it
            printf("TOWN '%s' DELETED FROM SLOT %d.\n", town, theslot);
            return;  // Town found and deleted
        }
        collisions++;  // Increment collisions if the slot is taken but not the given town
        theslot = (theslot + 1) % hashtable->tablesize;  // Linear probing to the next slot
        if (theslot == originalIndex) {
            break;
        }
    }

    printf("TOWN '%s' NOT FOUND IN THE HASH TABLE.\n", town);  // If town is not found
}

// save data in the hash table to a file
void savefromtabletofile(myhash *hashtable, char *filename) {
    FILE *file = fopen(filename, "w");  // Open the file for writing
    if (file == NULL) {
        printf("CAN NOT OPEN THE FILE!!");
        return;
    }

    // Save each taken record to the file
    for (int i = 0; i < hashtable->tablesize; i++) {  // for loop go through the table
        if (hashtable->table[i].istaken) {  // Check if the slot is taken,if it taken so print the info to the output file
            fprintf(file, "%s: %s: %d: %d: %s\n",
                    hashtable->table[i].district,
                    hashtable->table[i].town,
                    hashtable->table[i].population,
                    hashtable->table[i].elevation,
                    hashtable->table[i].hasmunicipality);
        }
    }

    fclose(file);  // Close the file after writing
    printf("DATA SAVED TO %s SUCCESSFULLY\n", filename);
}

//******************implementation of the avl tree functions*****************************
//function to get the height of the tree
int height(avltree tree) {
        if (tree == NULL) { // if statment to check if the tree is null
        return -1;
    }

    else {
        return tree->height; // if the tree is not null so return it's height
    }
}

// function to get the max
int Max(int a, int b) {
        if (a > b) { // check if a > b then return the max => a
        return a;
    }

    else {
        return b; // b is max so return it
    }

}

// create a node in the tree
avltree CreateNode(char *district, char *town, int population, int elevation, char *hasmunicipality) {
    avltree newNode = (avltree)malloc(sizeof(struct myAVLnode));  // allocate memory for the avl node
    if (newNode == NULL) {
        printf("OUT OF MEMORY!!!!\n");
        exit(1);
    }
    strcpy(newNode->district, district);// get the district
    strcpy(newNode->town, town);// get the twon
    newNode->population = population;//get the population
    newNode->elevation = elevation;//get the evalution
    strcpy(newNode->hasmunicipality, hasmunicipality); // get the municipality , yes or no
    newNode->left = newNode->right = NULL; //make the left and right for the node = null
    newNode->height = 0;// hight = 0
    return newNode;
}

//single left rotation on the avl tree to fix balance if exist
avltree singleleftrotation(avltree x) {
    avltree y = x->left; // make y the new root
    x->left = y->right;  //make the y right to be the x left
    y->right = x;        // make the x to be the right of y

    //updates the heights for x and y
    x->height = Max(height(x->left), height(x->right)) + 1;
    y->height = Max(height(y->left), x->height) + 1;

    return y;
}

//single right rotation on the avl tree to fix balance if exist
avltree singlerightrotation(avltree y) {
    avltree x = y->right; // make x the new root
    y->right = x->left; // make the left of x to be the right of y
    x->left = y;       // make the y to be the left of x

    //updates the heights of x and y
    y->height = Max(height(y->left), height(y->right)) + 1;
    x->height = Max(height(x->right), y->height) + 1;

    return x;
}

//double left rotation on the avl tree to fix balance if exist.
avltree doubleLeftRotation(avltree z) {
    z->left = singlerightrotation(z->left); // make right single rotation on the left child.
    return singleleftrotation(z);          // make left single rotation on z.
}

//double right rotation on the avl tree to fix balance if exist.
avltree doubleRightRotation(avltree y) {
    y->right = singleleftrotation(y->right); // make left single rotation on the right child.
    return singlerightrotation(y);          // make right single rotation on y.
}

// function to insert a new node to the avl tree
avltree Insert(char *district, char *town, int population, int elevation, char *hasmunicipality, avltree tree) {
    if (tree == NULL) { // if statment to check if the tree is null
        return CreateNode(district, town, population, elevation, hasmunicipality);
    }

    int c = strcmp(town, tree->town);// compare the new town with the town in the tree using strcmp
    if (c < 0) { // if the new town is less, then it will be insert in the left
        tree->left = Insert(district, town, population, elevation, hasmunicipality, tree->left);// insert the new town in the left
        if (height(tree->left) - height(tree->right) == 2) { // check the balance after insert the new town
            if (strcmp(town, tree->left->town) < 0) // If the new town is less than the left town,so make a single left rotation.
                tree = singleleftrotation(tree);
            else
                tree = doubleLeftRotation(tree); // if not make a double left rotation
        }
    }
    else if (c > 0) { // if the new town is greater, then it will be insert in the right
        tree->right = Insert(district, town, population, elevation, hasmunicipality, tree->right);// insert the new town in the right
        if (height(tree->right) - height(tree->left) == 2) { // check the balance after insert the new town
            if (strcmp(town, tree->right->town) > 0)   //If the new town is greater than the right town,so make a single right rotation.
                tree = singlerightrotation(tree);
            else
                tree = doubleRightRotation(tree);// if not make a double right rotation
        }
    }
    // update the height for the avl tree
    tree->height = Max(height(tree->left), height(tree->right)) + 1;
    return tree;
}

// function to print the towns in alphabetical order
void printinalphabeticalorder (avltree tree) {
    if (tree != NULL) { // if stetment to check if the tree is null
        printinalphabeticalorder (tree->left);// print the left subtree first (small twon first)
        printf("District: %s, Town: %s, Population: %d, Elevation: %d, Has Municipality: %s\n",
               tree->district, tree->town, tree->population, tree->elevation, tree->hasmunicipality);// print them with all information
        printinalphabeticalorder (tree->right); // then print the right subtree
    }
}

// get the data from the input file
void readtheinputfile(avltree *root, char *filename) { // get the pointer to the tree and the file name
    FILE *file = fopen(filename, "r"); // read from the input file
    if (file == NULL) { // check if the file exist
        printf("CAN NOT OPEN THE FILE!!");
        return;
    }

    char line[200];//read line by line from the file
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        char district[50], town[50], hasmunicipality[4];
        int population, elevation;

        sscanf(line, "%49[^:]:%49[^:]:%d:%d:%3s", district, town, &population, &elevation, hasmunicipality);

        *root = Insert(district, town, population, elevation, hasmunicipality, *root);
    }

    fclose(file);
}

// search for a town in the avl tree
avltree SearchforaTown(avltree tree, char *searchedtown) {
    if (tree == NULL) // check if the tree is null
        return NULL;

    int compare = strcmp(searchedtown, tree->town);// compare the town that i want to search with other towns in the tree
    if (compare == 0) // reach the town i want
        return tree;

    else if (compare < 0)
    return SearchforaTown(tree->left, searchedtown);// if the town i want is less,so go to search in the left subtree

    else
    return SearchforaTown(tree->right, searchedtown);// if the town i want is greater,so go to search in the right subtree
}

// update the information of a given town
void updatetowninformation(avltree root) {
    char town[50];
    printf("ENTER THE NAME OF THE TOWN THAT YOU WANT TO UPDATE IT'S INFORMATION: ");
    scanf("%s", town);

    avltree townNode = SearchforaTown(root, town);
    if (townNode == NULL) { // check if the town exist
        printf("Town not found!\n");
        return;
    }

    printf("ENTER NEW POPULATION: ");//get the new population value
    scanf("%d", &townNode->population);
    printf("ENTER NEW ELEVATION: ");//get the new elevation value
    scanf("%d", &townNode->elevation);
    printf("UPDATE MUNICIPALITY STATUS, yes or no: ");//get the new municipality status
    scanf("%s", townNode->hasmunicipality);

    printf("Town INFORMATION HAS UPDATED SUCCESSFULLY\n");
}

// print the town based on a given population
void printtownswithpopulation(avltree tree, int minvaluepopulation) {
    if (tree != NULL) {
        printtownswithpopulation(tree->left, minvaluepopulation); //start with left subtree
        if (tree->population > minvaluepopulation) {
            printf("District: %s, Town: %s, Population: %d, Elevation: %d, Has Municipality: %s\n",
                   tree->district, tree->town, tree->population, tree->elevation, tree->hasmunicipality);// check the population , if greater the the given one so print it
        }
        printtownswithpopulation(tree->right, minvaluepopulation);// then go to the right subtree and do the same
    }
}

// print the town based on a given status (yes or no )
void printtownsgivenstatus(avltree tree, char *givenstatus) {
    if (tree != NULL) { // check if the tree is null
        printtownsgivenstatus(tree->left, givenstatus); // start with the left subtree
        if (strcmp(tree->hasmunicipality, givenstatus) == 0) {
            printf("District: %s, Town: %s, Population: %d, Elevation: %d, Has Municipality: %s\n",
                   tree->district, tree->town, tree->population, tree->elevation, tree->hasmunicipality);// compare the given status with the towns status,if equal so print it
        }
        printtownsgivenstatus(tree->right, givenstatus);//then go to right subtree and do the same
    }
}

//delete a given town from the tree
avltree deletegiventown(avltree tree, char *town) {
    avltree temp; //

    if (tree == NULL) // check if the tree is null
        return NULL;

    int compres = strcmp(town, tree->town);//compare the given town with the root town in the tree
    if (compres < 0)
        tree->left = deletegiventown(tree->left, town); // if the given town is less,then do to the left side
    else if
    (compres > 0) tree->right = deletegiventown(tree->right, town);// if the given town is greater,then do to the right side

    else {
    if (tree->left == NULL || tree->right == NULL) { // if the node has one child
        // if there is a left child, assign it to temp
        if (tree->left) {
            temp = tree->left;
        }
        else {
            temp = tree->right;//otherwise, assign the right child
        }


        if (temp == NULL) { // check if the temp is null so the node has no children
            temp = tree;   // assign the node to the temp
            tree = NULL;   // remove the node from the tree
        }
         else {
            //  if there is a child then copy the data from the child node into the current node
            *tree = *temp;
        }

        // free the memory of the removed node
        free(temp);
    }
    else {
        // If the node has two children
        avltree temp = tree->right;// find the leftmost node in the right subtree
        while (temp->left != NULL)
            temp = temp->left; // Go to the leftmost node

        // Copy the town name
        strcpy(tree->town, temp->town);

        // delete the node
        tree->right = deletegiventown(tree->right, temp->town);
    }
}

// If the tree is empty, return NULL
if (tree == NULL)
    return NULL;

// update the height
tree->height = Max(height(tree->left), height(tree->right)) + 1;
return tree;

}

// function to save to output file
void savetooutputfile(avltree tree, FILE *file) {
    if (tree != NULL) { // check if the tree is not null
        savetooutputfile(tree->left, file);//start saving from the left side of the tree
        fprintf(file, "%s:%s:%d:%d:%s\n", tree->district, tree->town, tree->population, tree->elevation, tree->hasmunicipality);//write to the file
        savetooutputfile(tree->right, file);//then go to the right side
    }
}


//******************MAIN*****************************
int main() {
    avltree root = NULL; // create a tree
    int cho;//variable to hold the user choice operation


    // while loop to go through the menu
    while (1) {
        printf("\n______________WELLCOME_______________\n\n");
        printf("PLEASE CHOOSE THE OPERATION YOU WANT FROM 1 TO 15:\n\n");
        printf("1.  READ THE INPUT FILE\n");
        printf("2.  INSERT A NEW TOWN\n");
        printf("3.  UPDATE TOWN INFORMATIONS\n");
        printf("4.  LIST TOWNS IN ALPHABETICAL ORDE\n");
        printf("5.  LIST TOWNS WITH POPULATION GREATER THAN A GIVEN NUMBER\n");
        printf("6.  LIST TOWNS WITH A GIVEN MUNICIPALITIES STATUS\n");
        printf("7.  DELETE A TOWN\n");
        printf("8.  SAVE THE DATA TO THE OUTPUT FILE => TOWNS.TXT\n");
        printf("9.  PRINT HASH TABLE\n");
        printf("10. PRINT THE SIZE AND LOAD FACTOR OF HASH TABLE\n");
        printf("11. INSERT NEW RECORED TO THE HASH TABLE \n");
        printf("12. FIND A TOWN IN THE HASH TABLE\n");
        printf("13. Delete A Record From The Hash Table\n");
        printf("14. SAVE THE HASH TABLE BACK TO TOWNS.TXT\n");
        printf("15. EXIT FROM THE PROGRAM\n");
        printf("===>PLEASE ENTER YOUR CHOICE:");
        scanf("%d", &cho);

        switch (cho) {
            case 1:
                readtheinputfile(&root, "district.txt");
                printf("DATA FROM FILE READ SUCCESSFULLY\n");
                break;

            case 2: {
                char district[50], town[50], hasMunicipality[4];
                int population, elevation;
                printf("ENTER DISTRICT: ");
                scanf("%s", district);
                printf("ENTER TOWN NAME: ");
                scanf("%s", town);
                printf("ENTER POPULATION: ");
                scanf("%d", &population);
                printf("ENTER ELEVATION: ");
                scanf("%d", &elevation);
                printf("IF THE TOWN HAS MUNICIPALITY ENTER yes OTHERS ENTER no: ");
                scanf("%s", hasMunicipality);
                root = Insert(district, town, population, elevation, hasMunicipality, root);
                break;
            }

            case 3:
                updatetowninformation(root);
                break;

            case 4:
                printinalphabeticalorder (root);
                break;

            case 5: {
                int minPopulation;
                printf("ENTER MINMUM POPULATON: ");
                scanf("%d", &minPopulation);
                printtownswithpopulation(root, minPopulation);
                break;
            }

            case 6: {
                char status[4];
                printf("ENTER MUNICIPALITY STATUS(yes/no): ");
                scanf("%s", status);
                printtownsgivenstatus(root, status);
                break;
            }

            case 7: {
                char town[50];
                printf("ENTER TOWN NAME TO DELETE: ");
                scanf("%s", town);
                root = deletegiventown(root, town);
                break;
            }

            case 8: {
                // to save the data from the tree to output file
                FILE *filee = fopen("towns.txt", "w");
                if (filee != NULL) {
                    savetooutputfile(root, filee);  // Save data to towns.txt
                    fclose(filee);
                    printf("DATA SAVED TO TOWNS.TXT SUCCESSFULLY\n");
                }

                // to read the file to make the hash function and get the size of it
                FILE *file = fopen("towns.txt", "r");//start reading the file
                if (!file) { // check the file if exist
                    printf("CAN NOT OPEN THE FILE!! \n");
                    return;
                }

                char line[256];
                int hashTableSize;//variable to hold the hash size
                int linecount=0; // variable to count the number of lines in the file
                while (fgets(line, sizeof(line), file) != NULL) { // read line by line from the file
                    // remove newline character, if present
                    line[strcspn(line, "\n")] = '\0';
                    linecount++;// increment the number of lines when read a new line
                }
                fclose(file);
                // the size for the hash table is the number of lines in the file * 2 and the result should be a prime number
                // multiply line count by 2
                int theres = linecount * 2;

                //find the size of the hash table
                // check if the res itself is prime or not
                if (isnumprime(theres)) {
                    hashTableSize = theres;
                } else {
                    hashTableSize = nextpeimenum(theres); // if the res is not prime so find the next prime of it
                }

                // create the hash table with the calculated size
                myhash hashTable;
                createhashTable(&hashTable, hashTableSize);
                insertthefiletohashtable(&hashTable,"towns.txt" ); // make the hash table from the output file
                break;

            case 9: {
                printhashtable(&hashTable);  // print the hash table including empty spots
                break;

            case 10:
                printthesizeandloadfactor(&hashTable);  // Print the size and load factor
                break;

            case 11:
                inserttohashtable(&hashTable);  // insert a new record to the hash table
                break;

            case 12:
                    {
                        char town[50];
                        printf("ENTER TOWN NAME TO SEARCH: ");
                        scanf("%s", town);
                        Searchfortowninhash(&hashTable, town);  // search and count collisions
                        break;
                    }

            case 13:
                    {
                        char town[50];
                        printf("ENTER TOWN NAME TO DELETE FROM HASH TABLE: ");
                        scanf("%s", town);
                        deletefromhashtable(&hashTable, town);  // delete the record from hash table
                        break;
                    }

            case 14: {
                        // save the data to towns.txt
                        savefromtabletofile(&hashTable, "towns.txt");
                        break;
                    }

            case 15:
                exit(0);

            default:
                printf("WRONG CHOICE , PLEASE TRY AGAIN.\n");
        }
    }
  }
}

    return 0;

}


