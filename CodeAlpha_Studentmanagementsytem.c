#include <stdio.h>
#include <stdlib.h>

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

void addStudent();
void deleteStudent();
void updateStudent();
void searchStudent();
void displayStudents();

int main() {
    int choice;

    do {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====");
        printf("\n1. Add Student");
        printf("\n2. Delete Student");
        printf("\n3. Update Student");
        printf("\n4. Search Student");
        printf("\n5. Display All Students");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: deleteStudent(); break;
            case 3: updateStudent(); break;
            case 4: searchStudent(); break;
            case 5: displayStudents(); break;
            case 6: printf("\nExiting Program...\n"); break;
            default: printf("\nInvalid Choice!\n");
        }
    } while (choice != 6);

    return 0;
}

void addStudent() {
    struct Student s;
    FILE *fp = fopen("student.dat", "ab");

    if (fp == NULL) {
        printf("\nFile Error!");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);  // allow spaces
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent Record Added Successfully!");
}

void deleteStudent() {
    struct Student s;
    int roll, found = 0;
    FILE *fp = fopen("student.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        fclose(temp);
        return;
    }

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.rollNo != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    if (found)
        printf("\nStudent Record Deleted Successfully!");
    else
        printf("\nStudent Record Not Found!");
}

void updateStudent() {
    struct Student s;
    int roll, found = 0;
    FILE *fp = fopen("student.dat", "rb+");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.rollNo == roll) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
        printf("\nStudent Record Updated Successfully!");
    else
        printf("\nStudent Record Not Found!");
}

void searchStudent() {
    struct Student s;
    int roll, found = 0;
    FILE *fp = fopen("student.dat", "rb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.rollNo == roll) {
            printf("\nRoll No: %d", s.rollNo);
            printf("\nName: %s", s.name);
            printf("\nMarks: %.2f", s.marks);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nStudent Record Not Found!");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen("student.dat", "rb");

    if (fp == NULL) {
        printf("\nNo Records Found!");
        return;
    }

    printf("\n===== STUDENT RECORDS =====\n");
    int count = 0;
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll No: %d", s.rollNo);
        printf("\nName: %s", s.name);
        printf("\nMarks: %.2f\n", s.marks);
        count++;
    }

    if (count == 0)
        printf("\nNo Records Found!");

    fclose(fp);
}
