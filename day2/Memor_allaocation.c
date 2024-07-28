#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee_data.dat"
#define RECORD_SIZE sizeof(struct Employee)

struct Employee
{
    int empId;
    char empName[50];
    float empSalary;
};

void addEmployee();
void displayAllEmployees();
void modifyEmployee();

int main()
{
    int choice;

    while (1)
    {
        printf("\nEmployee Database\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Modify Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addEmployee();
            break;

        case 2:
            displayAllEmployees();
            break;

        case 3:
            modifyEmployee();
            break;

        case 4:
            printf("Exiting the program.\n");
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addEmployee()
{
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    struct Employee emp;

    printf("Enter Employee ID: ");
    scanf("%d", &emp.empId);

    printf("Enter Employee Name: ");
    scanf("%s", emp.empName);

    printf("Enter Employee Salary: ");
    scanf("%f", &emp.empSalary);

    fwrite(&emp, RECORD_SIZE, 1, file);

    fclose(file);

    printf("Employee added successfully.\n");
}

void displayAllEmployees()
{
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    struct Employee emp;

    printf("\nEmployee Details\n");
    printf("--------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-10s |\n", "Employee ID", "Employee Name", "Salary");
    printf("--------------------------------------------------------\n");

    while (fread(&emp, RECORD_SIZE, 1, file) == 1)
    {
        printf("| %-10d | %-20s | %-10.2f |\n", emp.empId, emp.empName, emp.empSalary);
    }

    printf("--------------------------------------------------------\n");

    fclose(file);
}

void modifyEmployee()
{
    FILE *file = fopen(FILENAME, "r+b");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    int empId;
    struct Employee emp;

    printf("Enter Employee ID to modify: ");
    scanf("%d", &empId);

    int found = 0;

    while (fread(&emp, RECORD_SIZE, 1, file) == 1)
    {
        if (emp.empId == empId)
        {
            found = 1;
            printf("Enter new Employee Name: ");
            scanf("%s", emp.empName);

            printf("Enter new Employee Salary: ");
            scanf("%f", &emp.empSalary);

            fseek(file, -RECORD_SIZE, SEEK_CUR);
            fwrite(&emp, RECORD_SIZE, 1, file);

            printf("Employee details modified successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Employee with ID %d not found.\n", empId);
    }

    fclose(file);
}
