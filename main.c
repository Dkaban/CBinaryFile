/////////////////////////////////////////
///
///  Author: Dustin Kaban
///  Student ID: T00663749
///  Date: February 2nd, 2021
///  Course: COMP 2131
///
/////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Struct to contain all the students information
struct Student
{
    char id[10];
    char name[30];
    char emailId[10];
    char courseId[10];
    char grade[5];
};
FILE *studentFile;

bool exitMenu = false;

//Method declarations
void displayMainMenu();
int makeChoice();
void createRecord();
void displayRecord();
void seekRecord();
void updateRecord();
void deleteRecord();
int checkFileExists(const char * filename);

int main()
{
    //Only exit when the user presses the number 6 as an option
    while(!exitMenu)
    {
        displayMainMenu();
        makeChoice();
    }
    return 0;
}

void displayMainMenu()
{
    //Display the menu to the user
    printf("\tM A I N  M E N U");
    printf("\n1. Create the Binary File");
    printf("\n2. Display the contents of the file");
    printf("\n3. Seek a specific record");
    printf("\n4. Update the contents of a record");
    printf("\n5. Delete a record for the specific name");
    printf("\n6. Exit");
    printf("\n\n\t Please Enter your choice .... ");
}

int makeChoice()
{
    //Ask the user to make their choice
    int choice = 0;
    scanf("%d", &choice);
    while((getchar() != '\n'));

    //If the choice is not within the limits, keep asking until a proper choice is made
    while(choice < 1 || choice > 6)
    {
        printf("Invalid choice, Choose from options 1 to 6: ");
        scanf("%d", &choice);
        while((getchar() != '\n'));
    }

    switch(choice)
    {
        case 1:
            //Create the Binary File
            createRecord();
            break;
        case 2:
            //Display the contents of the file
            //First validate that the file exists
            if(checkFileExists("studentFile.bin")==1)
            {
                displayRecord();
            }
            break;
        case 3:
            //Seek a specific record
            //First validate that the file exists
            if(checkFileExists("studentFile.bin")==1)
            {
                seekRecord();
            }
            break;
        case 4:
            //Update a record for the specific name
            //First validate that the file exists
            if(checkFileExists("studentFile.bin")==1)
            {
                updateRecord();
                displayRecord();
            }
            break;
        case 5:
            //Delete a record for the specific name
            //First validate that the file exists
            if(checkFileExists("studentFile.bin")==1)
            {
                deleteRecord();
                displayRecord();
            }
            break;
        case 6:
            //Exit
            exitMenu = true;
            break;
        default:
            break;
    }
    return choice;
}

void createRecord()
{
    studentFile = fopen("studentFile.bin","ab");

    struct Student student;

    //Display to the user what they need to enter and accept input
    printf("Enter Student ID: ");
    scanf("%9s",student.id);
    while((getchar() != '\n'));

    printf("Enter Student Name: ");
    scanf("%29s",student.name);
    while((getchar() != '\n'));

    printf("Enter Email ID: ");
    scanf("%9s",student.emailId);
    while((getchar() != '\n'));

    printf("Enter Course ID: ");
    scanf("%9s",student.courseId);
    while((getchar() != '\n'));

    printf("Enter Grade: ");
    scanf("%4s",student.grade);
    while((getchar() != '\n'));

    //Write the information to the file
    fwrite(&student,sizeof(student),1,studentFile);
    fclose(studentFile);
}

void displayRecord()
{
    //Open the file and display the contents to the user
    studentFile=fopen("studentFile.bin","rb");
    struct Student student;
    while(fread(&student,sizeof(student),1,studentFile))
    {
        printf("\n------------------------------------------\n");
        printf("Student ID: %s",student.id);
        printf("\nStudent Name: %s",student.name);
        printf("\nEmail ID: %s",student.emailId);
        printf("\nCourse ID: %s",student.courseId);
        printf("\nGrade: %s",student.grade);
        printf("\n------------------------------------------\n");
    }
    fclose(studentFile);
}

void seekRecord()
{
    //Ask the user for input then display the record, if found
    struct Student student;
    char id[10];
    printf("Enter Student ID: ");
    scanf("%s",id);
    while((getchar() != '\n'));

    studentFile = fopen("studentFile.bin","rb");
    bool recordFound = false;

    while(fread(&student,sizeof(student),1,studentFile))
    {
        if(strcmp(student.id,id)==0)
        {
            printf("\tStudent Record Found.");
            printf("\n------------------------------------------\n");
            printf("Student ID: %s",student.id);
            printf("\nStudent Name: %s",student.name);
            printf("\nEmail ID: %s",student.emailId);
            printf("\nCourse ID: %s",student.courseId);
            printf("\nGrade: %s",student.grade);
            printf("\n------------------------------------------\n");
            recordFound = true;
            break;
        }
    }

    if(!recordFound)
    {
        printf("\tRecord not found.\n");
    }
}

void updateRecord()
{
    //Open the file, create a temporary file with the new information, then overwrite existing file
    FILE *tempFile;
    char id[10];
    printf("Enter Student ID: ");
    scanf("%9s",id);
    while(getchar() != '\n');

    studentFile=fopen("studentFile.bin","rb");
    tempFile = fopen("tempFile.bin","wb");

    struct Student student;
    while(fread(&student,sizeof(student),1,studentFile))
    {
        if(strcmp(student.id,id)==0)
        {
            printf("Enter Updated Student ID: ");
            scanf("%9s",student.id);
            while((getchar() != '\n'));

            printf("Enter Updated Student Name: ");
            scanf("%29s",student.name);
            while((getchar() != '\n'));

            printf("Enter Updated Email ID: ");
            scanf("%9s",student.emailId);
            while((getchar() != '\n'));

            printf("Enter Updated Course ID: ");
            scanf("%9s",student.courseId);
            while((getchar() != '\n'));

            printf("Enter Updated Grade: ");
            scanf("%4s",student.grade);
            while((getchar() != '\n'));

            fwrite(&student,sizeof(student),1,tempFile);
        }
        else
        {
            fwrite(&student,sizeof(student),1,tempFile);
        }
    }
    fclose(studentFile);
    fclose(tempFile);
    remove("studentFile.bin");
    rename("tempFile.bin","studentFile.bin");
}

void deleteRecord()
{
    //Similar to update record, create temporary file, write the left over info from the existing file
    //Then set the temporary file as the current working file
    FILE *tempFile;
    struct Student student;
    char name[30];
    printf("Enter Student Name: ");
    scanf("%29s",name);
    while((getchar() != '\n'));

    studentFile = fopen("studentFile.bin","rb");
    tempFile = fopen("tempFile.bin","wb");

    while(fread(&student,sizeof(student),1,studentFile))
    {
        if(strcmp(student.name,name) !=0)
        {
            fwrite(&student,sizeof(student),1,tempFile);
        }
    }

    fclose(studentFile);
    fclose(tempFile);
    remove("studentFile.bin");
    rename("tempFile.bin","studentFile.bin");
}

int checkFileExists(const char * filename)
{
    //Check to see if the file exists, if not, we can't open it.  Error checking.
    FILE *file;
    //Try to open the file
    if(file = fopen("studentFile.bin", "r"))
    {
        fclose(file);
        return 1;
    }

    printf("\nFile does not exist, please create a file first.\n");
    return 0;
}