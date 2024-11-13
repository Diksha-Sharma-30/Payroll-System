#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100

// Define the Employee struct
typedef struct {
    int employee_id;
    char name[50];
    char position[30];
    char department[30];
    float base_salary;
    float hours_worked;
    float bonus;
    float deductions;
} Employee;

// Function prototypes
void addEmployee(Employee employees[], int *employee_count);
void removeEmployee(Employee employees[], int *employee_count, int employee_id);
void updateEmployee(Employee employees[], int employee_count, int employee_id);
void calculatePayroll(Employee *employee);
void searchEmployee(Employee employees[], int employee_count, char *name);
void sortEmployees(Employee employees[], int employee_count);
void saveToFile(Employee employees[], int employee_count, const char *filename);
void loadFromFile(Employee employees[], int *employee_count, const char *filename);

// Main function
int main() {
    Employee employees[MAX_EMPLOYEES];
    int employee_count = 0;

    loadFromFile(employees, &employee_count, "employees.dat");

    int choice;
    do {
        printf("\nPayroll System Menu:\n");
        printf("1. Add Employee\n2. Remove Employee\n3. Update Employee\n");
        printf("4. Generate Payroll\n5. Search Employee\n6. Sort Employees\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(employees, &employee_count); break;
            case 2: {
                int id;
                printf("Enter Employee ID to remove: ");
                scanf("%d", &id);
                removeEmployee(employees, &employee_count, id);
                break;
            }
            case 3: {
                int id;
                printf("Enter Employee ID to update: ");
                scanf("%d", &id);
                updateEmployee(employees, employee_count, id);
                break;
            }
            case 4: {
                int id;
                printf("Enter Employee ID to generate payroll: ");
                scanf("%d", &id);
                for (int i = 0; i < employee_count; i++) {
                    if (employees[i].employee_id == id) {
                        calculatePayroll(&employees[i]);
                        break;
                    }
                }
                break;
            }
            case 5: {
                char name[50];
                printf("Enter Employee Name to search: ");
                scanf("%s", name);
                searchEmployee(employees, employee_count, name);
                break;
            }
            case 6: sortEmployees(employees, employee_count); break;
            case 7: saveToFile(employees, employee_count, "employees.dat"); break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 7);

    return 0;
}

// Function to add an employee
void addEmployee(Employee employees[], int *employee_count) {
    if (*employee_count >= MAX_EMPLOYEES) {
        printf("Employee list is full.\n");
        return;
    }

    Employee new_employee;
    printf("Enter Employee ID: ");
    scanf("%d", &new_employee.employee_id);
    printf("Enter Name: ");
    scanf("%s", new_employee.name);
    printf("Enter Position: ");
    scanf("%s", new_employee.position);
    printf("Enter Department: ");
    scanf("%s", new_employee.department);
    printf("Enter Base Salary: ");
    scanf("%f", &new_employee.base_salary);
    new_employee.hours_worked = 0;
    new_employee.bonus = 0;
    new_employee.deductions = 0;

    employees[*employee_count] = new_employee;
    (*employee_count)++;
    printf("Employee added successfully.\n");
}

// Function to remove an employee
void removeEmployee(Employee employees[], int *employee_count, int employee_id) {
    int found = 0;
    for (int i = 0; i < *employee_count; i++) {
        if (employees[i].employee_id == employee_id) {
            for (int j = i; j < *employee_count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            (*employee_count)--;
            found = 1;
            printf("Employee removed successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Employee not found.\n");
    }
}

// Function to update an employee
void updateEmployee(Employee employees[], int employee_count, int employee_id) {
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].employee_id == employee_id) {
            printf("Enter new hours worked: ");
            scanf("%f", &employees[i].hours_worked);
            printf("Enter new bonus: ");
            scanf("%f", &employees[i].bonus);
            printf("Enter new deductions: ");
            scanf("%f", &employees[i].deductions);
            printf("Employee updated successfully.\n");
            return;
        }
    }
    printf("Employee not found.\n");
}

// Function to calculate payroll
void calculatePayroll(Employee *employee) {
    float total_salary = employee->base_salary + employee->bonus - employee->deductions;
    printf("\nPayroll for %s:\n", employee->name);
    printf("Base Salary: %.2f\n", employee->base_salary);
    printf("Bonus: %.2f\n", employee->bonus);
    printf("Deductions: %.2f\n", employee->deductions);
    printf("Total Salary: %.2f\n", total_salary);
}

// Function to search for an employee
void searchEmployee(Employee employees[], int employee_count, char *name) {
    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].name, name) == 0) {
            printf("Employee found: ID %d, Name: %s, Position: %s\n",
                   employees[i].employee_id, employees[i].name, employees[i].position);
            return;
        }
    }
    printf("Employee not found.\n");
}

// Function to sort employees by ID
void sortEmployees(Employee employees[], int employee_count) {
    for (int i = 0; i < employee_count - 1; i++) {
        for (int j = i + 1; j < employee_count; j++) {
            if (employees[i].employee_id > employees[j].employee_id) {
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
    printf("Employees sorted by ID.\n");
}

// Function to save employees to file
void saveToFile(Employee employees[], int employee_count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(&employee_count, sizeof(int), 1, file);
    fwrite(employees, sizeof(Employee), employee_count, file);
    fclose(file);
    printf("Data saved to file.\n");
}

// Function to load employees from file
void loadFromFile(Employee employees[], int *employee_count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("No previous data found.\n");
        return;
    }
    fread(employee_count, sizeof(int), 1, file);
    fread(employees, sizeof(Employee), *employee_count, file);
    fclose(file);
    printf("Data loaded from file.\n");
}
