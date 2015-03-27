/**
 Course: CSE240
 Instructor: Dr. Chen
 Assignment Name: Homework 4 Solution
 Solved by: Garrett Gutierrez 2/7/2015
 **/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable: 4996)
#define MAX 100

// Changed: deploma to diploma.
typedef enum { diploma = 0, bachelor, master, doctor } education;

// A struct to hold attributes of a person
struct person {
    char name[30];
    char email[30];
    int phone;
    education degree;
};

/******************* Global Variable Section *******************/
struct person directory[MAX];	// an array of structures, 100 entries
int tail = 0;					// global variable

/******************* Foward Declaration Section *******************/
void branching(char c);
int delete_person();
void flush();
int insertion();
int print_person(int i);
int print_all();
int search_person();
void shift_data(char* name, char* email, int phone, education educationLevel);

int main()
{
    // Print a menu for selection
    char ch = 'i';
    
    ungetc('\n', stdin);			// Inject the newline character into input buffer
    
    do {
        printf("Enter your selection\n");
        printf("\ti: insert a new entry\n");
        printf("\td: delete an entry\n");
        printf("\ts: search an entry\n");
        printf("\tp: print all entries\n");
        printf("\tq: quit \n");
        flush();					// Flush the input buffer. To be discussed later
        ch = tolower(getchar());	// Convert any uppercase char to lowercase.
        branching(ch);
    } while (ch != 113);			// 113 is 'q' in ASCII
    
    return 0;
};

// Flush the input buffer. To be discussed later
void flush()
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
};

// Branch to different tasks: insert a person, search for a person, delete a person
// print all added persons.
void branching(char c)
{
    switch (c) {
        case 'i':
            insertion();
            break;
        case 's':
            search_person();
            break;
        case 'd':
            delete_person();
            break;
        case 'p':
            print_all();
            break;
        case 'q':
            break;
        default:
            printf("Invalid input\n");
    }
};

// Inserts the person lexigraphically. Note: A < a so all capital letters will be ordered first.
int insertion()
{
    education educationLevel = 0;
    char name[MAX], email[MAX];
    int i = 0, phone;
    
    // Case 1: The structure is filled.
    if (tail == MAX) {
        printf("There are no more places to insert.\n");
        return -1;
    }
    
    // Case 2: The structure still has unfilled slots.
    else
    {
        printf("Enter the name:\n");
        scanf("%s", name);
        printf("Enter the phone number:\n");
        scanf("%d", &phone, sizeof(directory[tail].phone));
        printf("Enter the e-mail:.\n");
        scanf("%s", email);
        //**********		Question 1		************
        do {
            printf("Enter the degree: select 0 for diploma, select 1 for bachelor, select 2 for master, or select 3 for doctor:\n");
            scanf("%d", &educationLevel);
            if (educationLevel < diploma || educationLevel > doctor)
            {
                printf("Please enter a value from 0 to 3.\n");
            }
        } while (educationLevel < diploma || educationLevel > doctor);
        //**********************************************
        //*********		Question 2			************
        shift_data(name, email, phone, educationLevel);
        //*****************************************
        tail++;
        printf("The number of entries = %d\n", tail);
    }
    
    return 0;
};

// Print the name, e-mail, phone, and education level of one person in the directory
int print_person(int i)
{
    printf("\n\nname = %s\n", directory[i].name);
    printf("email = %s\n", directory[i].email);
    printf("phone = %d\n", directory[i].phone);
    //************  Question 1  ******************
    switch (directory[i].degree)
    {
        case diploma:
            printf("degree = diploma\n");
            break;
            
        case bachelor:
            printf("degree = bachelor\n");
            break;
            
        case master:
            printf("degree = master\n");
            break;
            
        case doctor:
            printf("degree = doctor\n");
            break;
            
        default:
            printf("System Error: degree information corruption.\n");
            break;
    }
    //****************************************
    
    return 0;
}

// Print the name, e-mail, phone, and education level of each person in the directory
int print_all()
{
    int i;
    
    //Case 1: The structure is empty
    if (tail == 0)
    {
        printf("No entries found.");
    }
    
    // Case 2: The structure has at least one item in it
    else
    {
        for (i = 0; i < tail; i++) {
            print_person(i);
        }
        printf("\n");
    }
    
    return 0;
};

//**********	Question 3	 **************
//Find a person by comparing names.
int search_person()
{
    char sname[30];
    int  i = 0;
    struct person* iterator = directory;
    
    printf("Please enter the name to be searched for:\n");
    scanf("%s", sname); 										//sname is an array, no & needed
    while (i < tail)
    {
        if (strcmp(sname, iterator->name) == 0)
        {
            print_person(i);
            return i;
        }
        iterator++;
        i++;
    }
    printf("The name does not exist.\n");
    return -1;
};
//***************************************

// Delete a person after finding that person via their name.
int delete_person()
{
    int i, k;
    
    k = search_person();
    
    // Case 1: The person is not in the directory
    if (k == -1)
    {
        printf("The name does not exist.\n");
        return -1;
    }
    
    // Case 2: The person was found in the directory
    else {
        for (i = k; i<tail; i++)
        {
            strcpy(directory[i].name, directory[i + 1].name);
            directory[i].phone = directory[i + 1].phone;
            strcpy(directory[i].email, directory[i + 1].email);
            printf("The index deleted is: %d\n", k);
        }
        tail--;
        return k;
    }
};

void shift_data(char* name, char* email, int phone, education educationLevel)
{
    int i = 0, j = 0;
    
    // Case 1: Empty List
    if (tail == 0)
    {
        strcpy(directory[tail].name, name);
        strcpy(directory[tail].email, email);
        directory[tail].phone = phone;
        directory[tail].degree = educationLevel;
        return;
    }
    
    while (i < tail)
    {
        // Case 2: Beginning or middle of list
        if (strcmp(name, directory[i].name) < 0)
        {
            j = tail;
            while (j > i)
            {
                strcpy(directory[j].name, directory[j - 1].name);
                strcpy(directory[j].email, directory[j - 1].email);
                directory[j].phone = directory[j - 1].phone;
                directory[j].degree = directory[j - 1].degree;
                j--;
            }
            strcpy(directory[i].name, name);
            strcpy(directory[i].email, email);
            directory[i].phone = phone;
            directory[i].degree = educationLevel;
            return;
        }
        i++;
    }
    
    // Case 3: End of list
    strcpy(directory[tail].name, name);
    strcpy(directory[tail].email, email);
    directory[tail].phone = phone;
    directory[tail].degree = educationLevel;
};