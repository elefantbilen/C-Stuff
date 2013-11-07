#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct
{
	double data;
	struct node *next;
	struct node *previous;
} node;

int getUserChoice();
void userIO();
double getDouble();
void traverseChain();
int getCount();
void deleteNode();
node *addNodeUlti(node* nodePointer);
node* head = NULL;

int main()
{
    int looper = 1;

	while(looper)
    {
        userIO();
		switch(getUserChoice())
		{
			case 1: head = addNodeUlti(head);
			break;
			case 2: deleteNode();
			break;
			case 3: traverseChain();
			break;
            case 4: looper = 0;
			break;
			default: printf("Only 1-4 permitted\n");
			break;
		}
    }
	getchar();
	return 0;
}

void deleteNode()
{
    if(head == 0)
    {
        printf("You don't have any nodes to delete.\n");
        return;
    }

    traverseChain();
    printf("which nodes do you want to delete,\n"
            "choose between 1 and %d\n", getCount());
    int choice;
    choice = getUserChoice();

    if(choice < 1 || choice > getCount())
    {
        printf("You must choose between 1 and %d\n", getCount());
        return;
    }
    else
    {
        node* tempNode = head;
        int i = 1;

        for(i; i < choice; i++)
            tempNode = tempNode->next;

        printf("Node %i: %f Deleted\n",i, tempNode->data);

        if(getCount() == 1)
        {
            printf("\nVid en ensam\n");
            free(head);
            head = NULL;
        }
        else if(getCount() > 1 && choice == 1)
        {
            printf("\nVid första men fler i listan\n");
            node *temp = head;
            head = head->next;
            head->previous = 0;
            free(temp);
            temp = NULL;
            //Ta bort första
            //Sätt prev på 2 till 0
            //sätt head som nummer två
        }
        else if(choice == getCount())
        {
            printf("\nTa bort sista noden\n");
            node* temp = tempNode->previous;
            free(tempNode);
            tempNode = NULL;
            temp->next = 0;
            //Ta bort sista
            //Sätt next på näst sista som noll
        }
        else
        {
            printf("\nI mitten någonstans\n");
            node* temp = tempNode->previous;
            temp->next = tempNode->next;
            temp = tempNode->next;
            temp->previous = tempNode->previous;
            free(tempNode);
        }
    }
}

void traverseChain()
{
    node* nodePointer = head;
    int i = 1;
    printf("List of all nodes saved:\n"
           "----------------------------\n");
    while(nodePointer != 0)
    {
        printf("Node %i: %f\n",i, nodePointer->data);
        nodePointer = nodePointer->next;
        i++;
    }
}

int getCount()
{
    int i = 0;
    node *nodePointer = head;

    while(nodePointer != 0)
    {
        nodePointer = nodePointer->next;
        i++;
    }

    return i;
}

node *addNodeUlti(node* nodePointer)
{
    if(nodePointer == NULL)
    {
        node* tempNode = malloc( sizeof(node));
        double userData;
		while((userData = getDouble()) < 0);
		
        tempNode->data = userData;
        tempNode->previous = 0;
        tempNode->next = 0;
        return tempNode;
    }
    else
    {
        node* tempNode = nodePointer;
        while(tempNode->next != 0)
            tempNode = tempNode->next;

        node* newNode = malloc( sizeof(node));
        double userData;
        userData = getDouble();
        newNode->data = userData;
        newNode->previous = tempNode;
        newNode->next = 0;
        tempNode->next = newNode;

        return nodePointer;
    }
}

double getDouble()
{
    char buff[BUFSIZ];	//Create temporary buffer
	double d;
    printf("What data do you want to store (in double)");
	fgets(buff, BUFSIZ, stdin);	// Place user input in buffer
	buff[strlen(buff) -1] = '\0';	// Terminate the string

	int i = 0;
	int decCounter = 0;
	for(i; i < strlen(buff); i++)		// Iterate through the string
	{
		if(buff[i] == '.')
			decCounter++;

		if(buff[i] != '.' && !isdigit(buff[i]))	// a character is neither an interger or a dot it is not a double...
			return - 1;							//... if so, return -1 to tell the program so
	}

	sscanf(buff, "%lf", &d);					// If everything went fine we can return the double
	return d;
}

void userIO()
{
	printf("You have: %d nodes, choose an operation: \n "
	"1) Create new node, if already created. Append one at the end\n "
	"2) Delete a node at your choice of place\n "
	"3) Walk through the chain and print every value\n "
	"4) Quit program\n"
	"Choice: ", getCount());
}

int getUserChoice()
{
	char buff[BUFSIZ];
	int i = 0;
	fgets(buff, sizeof(buff), stdin);
	printf("\n");
	for(i; i < strlen(buff) -1; i++)
	{
		if(!isdigit(buff[i]))
			return -1;
	}
	return atoi(buff);
}
