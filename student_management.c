/*
 ===================================================
 STUDENT MANAGEMENT SYSTEM
 Developed by: Elias Zananiri
 Description: Menu-driven program to manage student records
              using structures and file handling.
 ===================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.dat"

// Structure to store student details
typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

// Function prototypes
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void menu();

// Main function
int main() {
    printf("\n==========================================\n");
    printf("   WELCOME TO STUDENT MANAGEMENT SYSTEM\n");
    printf("         Developed by Elias Zananiri\n");
    printf("==========================================\n");
    menu();
    return 0;
}

// Menu driven interface
void menu() {
    int choice;
    
    do {
        printf("\n------------ MENU ------------\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student Record\n");
        printf("5. Delete Student Record\n");
        printf("6. Exit\n");
        printf("-----------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("\nExiting System. Goodbye! - Elias Zananiri\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 6);
}

// Add a new student record
void addStudent() {
    FILE *fp;
    Student s;
    
    fp = fopen(FILENAME, "ab");
    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    printf("\n--- Add New Student ---\n");
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    
    // Check if ID already exists
    FILE *temp = fopen(FILENAME, "rb");
    if(temp != NULL) {
        Student check;
        while(fread(&check, sizeof(Student), 1, temp)) {
            if(check.id == s.id) {
                printf("Student ID %d already exists! Use a different ID.\n", s.id);
                fclose(temp);
                fclose(fp);
                return;
            }
        }
        fclose(temp);
    }
    
    printf("Enter Student Name: ");
    getchar(); // clear input buffer
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // remove newline
    
    printf("Enter Student Marks: ");
    scanf("%f", &s.marks);
    
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    
    printf("\nStudent record added successfully!\n");
    printf("-- Developed by Elias Zananiri --\n");
}

// Display all student records
void displayAllStudents() {
    FILE *fp;
    Student s;
    int count = 0;
    
    fp = fopen(FILENAME, "rb");
    if(fp == NULL) {
        printf("\nNo records found! Database is empty.\n");
        return;
    }
    
    printf("\n========== ALL STUDENT RECORDS ==========\n");
    printf("%-10s %-30s %-10s\n", "ID", "NAME", "MARKS");
    printf("-----------------------------------------\n");
    
    while(fread(&s, sizeof(Student), 1, fp)) {
        printf("%-10d %-30s %-10.2f\n", s.id, s.name, s.marks);
        count++;
    }
    
    printf("-----------------------------------------\n");
    printf("Total Students: %d\n", count);
    printf("=========================================\n");
    printf("-- Developed by Elias Zananiri --\n");
    
    fclose(fp);
}

// Search for a student by ID
void searchStudent() {
    FILE *fp;
    Student s;
    int id, found = 0;
    
    fp = fopen(FILENAME, "rb");
    if(fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }
    
    printf("\n--- Search Student ---\n");
    printf("Enter Student ID to search: ");
    scanf("%d", &id);
    
    while(fread(&s, sizeof(Student), 1, fp)) {
        if(s.id == id) {
            printf("\n********** STUDENT FOUND **********\n");
            printf("ID    : %d\n", s.id);
            printf("Name  : %s\n", s.name);
            printf("Marks : %.2f\n", s.marks);
            printf("***********************************\n");
            found = 1;
            break;
        }
    }
    
    if(!found) {
        printf("Student with ID %d not found!\n", id);
    }
    printf("-- Developed by Elias Zananiri --\n");
    
    fclose(fp);
}

// Update student record
void updateStudent() {
    FILE *fp, *temp;
    Student s;
    int id, found = 0;
    
    fp = fopen(FILENAME, "rb");
    if(fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }
    
    temp = fopen("temp.dat", "wb");
    if(temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }
    
    printf("\n--- Update Student Record ---\n");
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    
    while(fread(&s, sizeof(Student), 1, fp)) {
        if(s.id == id) {
            found = 1;
            printf("\nCurrent Details:\n");
            printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
            
            printf("\nEnter New Details:\n");
            printf("Enter New Name: ");
            getchar();
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
            
            fwrite(&s, sizeof(Student), 1, temp);
            printf("\nRecord updated successfully!\n");
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    remove(FILENAME);
    rename("temp.dat", FILENAME);
    
    if(!found) {
        printf("Student with ID %d not found!\n", id);
    }
    printf("-- Developed by Elias Zananiri --\n");
}

// Delete student record
void deleteStudent() {
    FILE *fp, *temp;
    Student s;
    int id, found = 0;
    
    fp = fopen(FILENAME, "rb");
    if(fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }
    
    temp = fopen("temp.dat", "wb");
    if(temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }
    
    printf("\n--- Delete Student Record ---\n");
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    
    while(fread(&s, sizeof(Student), 1, fp)) {
        if(s.id == id) {
            found = 1;
            printf("\nDeleting Record:\n");
            printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
            printf("Record deleted successfully!\n");
            // Skip writing this record to temp file (deletion)
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    remove(FILENAME);
    rename("temp.dat", FILENAME);
    
    if(!found) {
        printf("Student with ID %d not found!\n", id);
    }
    printf("-- Developed by Elias Zananiri --\n");
}
