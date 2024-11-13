#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Employee struct to hold employee information
struct Employee {
    int id;
    string name;
    string position;
    string department;
    double base_salary;
    double hours_worked;
    double bonus;
    double deductions;
};

// Global vector to hold employees
vector<Employee> employees;

// Function to print with color
void print_color(const string& text, const string& color) {
    if (color == "green") {
        cout << "\033[32m" << text << "\033[0m";
    } else if (color == "red") {
        cout << "\033[31m" << text << "\033[0m";
    } else if (color == "yellow") {
        cout << "\033[33m" << text << "\033[0m";
    } else if (color == "cyan") {
        cout << "\033[36m" << text << "\033[0m";
    } else {
        cout << text;
    }
}

// Function to display a decorative header
void display_header(const string& title) {
    print_color("=====================================\n", "cyan");
    print_color("      " + title + "\n", "green");
    print_color("=====================================\n", "cyan");
}

// Function to add a new employee
void add_employee() {
    display_header("Add New Employee");

    Employee emp;
    cout << "Enter Employee ID: ";
    cin >> emp.id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, emp.name);
    cout << "Enter Position: ";
    getline(cin, emp.position);
    cout << "Enter Department: ";
    getline(cin, emp.department);
    cout << "Enter Base Salary: ";
    cin >> emp.base_salary;
    emp.hours_worked = 0;
    emp.bonus = 0;
    emp.deductions = 0;
    
    employees.push_back(emp);
    print_color("\nEmployee added successfully!\n", "green");
}

// Function to update an employee's work details
void update_employee() {
    display_header("Update Employee Details");

    int id;
    cout << "Enter Employee ID: ";
    cin >> id;

    for (auto &emp : employees) {
        if (emp.id == id) {
            cout << "Enter Hours Worked: ";
            cin >> emp.hours_worked;
            cout << "Enter Bonus: ";
            cin >> emp.bonus;
            cout << "Enter Deductions: ";
            cin >> emp.deductions;
            print_color("\nEmployee updated successfully!\n", "yellow");
            return;
        }
    }
    print_color("Employee not found!\n", "red");
}

// Function to display all employees in a table format
void display_employees() {
    display_header("Employee List");

    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Position"
         << setw(15) << "Department" << setw(12) << "Base Salary" << endl;
    print_color("-------------------------------------------------------------------------------\n", "cyan");

    for (const auto& emp : employees) {
        cout << left << setw(10) << emp.id << setw(20) << emp.name << setw(15) << emp.position
             << setw(15) << emp.department << setw(12) << emp.base_salary << endl;
    }
}

// Function to generate payroll for an employee
void generate_payroll() {
    display_header("Generate Payroll");

    int id;
    cout << "Enter Employee ID: ";
    cin >> id;

    for (const auto& emp : employees) {
        if (emp.id == id) {
            double total_salary = emp.base_salary + emp.bonus - emp.deductions;
            print_color("\nPayroll Details\n", "green");
            cout << "Name: " << emp.name << "\nPosition: " << emp.position
                 << "\nBase Salary: $" << fixed << setprecision(2) << emp.base_salary
                 << "\nHours Worked: " << emp.hours_worked
                 << "\nBonus: Rs." << emp.bonus
                 << "\nDeductions: Rs." << emp.deductions
                 << "\nTotal Salary: Rs." << total_salary << "\n";
            return;
        }
    }
    print_color("Employee not found!\n", "red");
}

// Function to remove an employee
void remove_employee() {
    display_header("Remove Employee");

    int id;
    cout << "Enter Employee ID: ";
    cin >> id;

    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->id == id) {
            employees.erase(it);
            print_color("Employee removed successfully!\n", "red");
            return;
        }
    }
    print_color("Employee not found!\n", "red");
}

// Function to insert demo employees
void insert_demo_employees() {
    employees.push_back({1, "Diksha Sharma", "Developer", "Engineering", 5000, 0, 0, 0});
    employees.push_back({2, "David Lee", "Manager", "HR", 5500, 0, 0, 0});
    employees.push_back({3, "Matt Rife", "Designer", "Design", 4800, 0, 0, 0});
    print_color("\nDemo employees added successfully!\n", "yellow");
}

// Main menu
void main_menu() {
    int choice;
    do {
        display_header("Payroll System Menu");

        print_color("1. Add Employee\n", "yellow");
        print_color("2. Update Employee\n", "yellow");
        print_color("3. Display Employees\n", "yellow");
        print_color("4. Generate Payroll\n", "yellow");
        print_color("5. Remove Employee\n", "yellow");
        print_color("6. Insert Demo Employees\n", "yellow");
        print_color("7. Exit\n", "yellow");
        print_color("Enter your choice: ", "cyan");
        cin >> choice;

        switch (choice) {
            case 1:
                add_employee();
                break;
            case 2:
                update_employee();
                break;
            case 3:
                display_employees();
                break;
            case 4:
                generate_payroll();
                break;
            case 5:
                remove_employee();
                break;
            case 6:
                insert_demo_employees();
                break;
            case 7:
                print_color("Exiting Payroll System.\n", "red");
                return;
            default:
                print_color("Invalid choice, please try again.\n", "red");
        }
    } while (true);
}

// Main function
int main() {
    print_color("\nWelcome to the Payroll System!\n", "green");
    main_menu();
    return 0;
}
