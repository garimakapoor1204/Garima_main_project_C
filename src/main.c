#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/admin.h"
#include "../include/school.h"
#include "../include/student.h"
#include "../include/teacher.h"
#include "../include/classroom.h"

// Global objects for simplicity in this conversion
School school;
Admin admin;
// We need storage for objects since School/Classroom hold pointers
Classroom classrooms[MAX_CLASSES];
Teacher teachers[MAX_TEACHERS];
Student students[MAX_CLASSES * MAX_STUDENTS_PER_CLASS];
int global_student_count = 0;

void admin_login();
void teacher_login();
void student_login();
void admin_menu();
void teacher_menu(Teacher *t);
void student_menu(Student *s);

// Helper functions for menu actions
void action_add_teacher();
void action_remove_teacher();
void action_add_class();
void action_remove_class();
void action_view_class_details();
void action_add_student();
void action_update_student_fee();
void action_change_admin_password();

void action_teacher_view_classes(Teacher *t);
void action_teacher_view_students(Teacher *t);
void action_teacher_update_grade(Teacher *t);
void action_teacher_change_password(Teacher *t);

void action_student_view_grades(Student *s);
void action_student_view_fee(Student *s);
void action_student_change_password(Student *s);

int main() {
    init_school(&school, "Sitender's School of Science and Technology");
    init_admin(&admin, "admin", "admin123", &school);

    while (1) {
        clear_screen();
        printf("===== %s =====\n", school.school_name);
        printf("1. Admin Login\n");
        printf("2. Teacher Login\n");
        printf("3. Student Login\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        int choice = get_int_input();

        if (choice == 1) {
            admin_login();
        } else if (choice == 2) {
            teacher_login();
        } else if (choice == 3) {
            student_login();
        } else if (choice == 4) {
            printf("Thank you for using the system. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
            pause_screen();
        }
    }
    return 0;
}

void admin_login() {
    clear_screen();
    printf("===== ADMIN LOGIN =====\n");
    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
    
    printf("Username: ");
    get_string_input(username, MAX_NAME_LEN);
    printf("Password: ");
    get_string_input(password, MAX_PASS_LEN);

    if (authenticate_admin(&admin, username, password)) {
        admin_menu();
    } else {
        printf("Invalid credentials.\n");
        pause_screen();
    }
}

void admin_menu() {
    while (1) {
        clear_screen();
        printf("===== ADMIN MENU =====\n");
        printf("1. View School Details\n");
        printf("2. Add Teacher\n");
        printf("3. Remove Teacher\n");
        printf("4. View All Teachers\n");
        printf("5. Add Class\n");
        printf("6. Remove Class\n");
        printf("7. View Class Details\n");
        printf("8. Add Student\n");
        printf("9. View All Students\n");
        printf("10. View Fee Records\n");
        printf("11. Update Student Fee\n");
        printf("12. Change Admin Password\n");
        printf("13. Back to Main Menu\n");
        printf("Enter your choice: ");

        int choice = get_int_input();

        if (choice == 1) {
            admin_view_school_details(&admin);
            pause_screen();
        } else if (choice == 2) {
            action_add_teacher();
        } else if (choice == 3) {
            action_remove_teacher();
        } else if (choice == 4) {
            view_all_teachers(&school);
            pause_screen();
        } else if (choice == 5) {
            action_add_class();
        } else if (choice == 6) {
            action_remove_class();
        } else if (choice == 7) {
            action_view_class_details();
        } else if (choice == 8) {
            action_add_student();
        } else if (choice == 9) {
            view_all_students(&school);
            pause_screen();
        } else if (choice == 10) {
            admin_view_fee_record(&admin);
            pause_screen();
        } else if (choice == 11) {
            action_update_student_fee();
        } else if (choice == 12) {
            action_change_admin_password();
        } else if (choice == 13) {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
            pause_screen();
        }
    }
}

void action_add_teacher() {
    clear_screen();
    printf("===== ADD TEACHER =====\n");

    if (school.teacher_count >= MAX_TEACHERS) {
        printf("Cannot add more teachers.\n");
        pause_screen();
        return;
    }

    char name[MAX_NAME_LEN];
    char subject[MAX_NAME_LEN];
    int teacher_id;
    char password[MAX_PASS_LEN];

    printf("Enter teacher name: ");
    get_string_input(name, MAX_NAME_LEN);
    printf("Enter subject: ");
    get_string_input(subject, MAX_NAME_LEN);
    printf("Enter teacher ID: ");
    teacher_id = get_int_input();
    
    if (teacher_id == -1) {
        printf("Invalid ID.\n");
        pause_screen();
        return;
    }

    if (get_teacher_from_school(&school, teacher_id) != NULL) {
        printf("Teacher ID already exists.\n");
        pause_screen();
        return;
    }

    if (school.class_count == 0) {
        printf("No classes available. Please add classes first.\n");
        pause_screen();
        return;
    }

    printf("Available classes: ");
    for(int i=0; i<school.class_count; i++) {
        printf("%s ", school.classes[i]->class_no);
    }
    printf("\n");

    printf("Enter class numbers (separated by spaces): ");
    char classes_input[100];
    get_string_input(classes_input, 100);
    
    // Parse classes
    char *token = strtok(classes_input, " ");
    char class_nos[MAX_CLASSES_TO_TEACH][10];
    int count = 0;
    int all_exist = 1;

    while (token != NULL && count < MAX_CLASSES_TO_TEACH) {
        if (get_class_from_school(&school, token) == NULL) {
            printf("Class %s does not exist.\n", token);
            all_exist = 0;
        } else {
            strcpy(class_nos[count++], token);
        }
        token = strtok(NULL, " ");
    }

    if (!all_exist) {
        printf("Some classes don't exist. Teacher not added.\n");
        pause_screen();
        return;
    }

    printf("Enter password: ");
    get_string_input(password, MAX_PASS_LEN);

    // Use next available slot in static array
    int slot = -1;
    // Simple strategy: use teacher_count as index since we don't support deleting from the static array effectively in this simple version
    // But we need to find an empty slot if we want to be robust. 
    // For this conversion, let's just use the current count index assuming no fragmentation or just append.
    // Actually, we are storing pointers in School, so we need actual storage.
    // We can use the global `teachers` array.
    
    // Find a free slot in global array
    // Since we don't track "free" slots in global array explicitly, let's just use a simple counter or scan.
    // We will just use school.teacher_count as the index into our global storage for simplicity, 
    // assuming we don't run out of global storage before MAX_TEACHERS.
    
    Teacher *new_teacher = &teachers[school.teacher_count]; 
    init_teacher(new_teacher, teacher_id, name, subject, password);
    
    for(int i=0; i<count; i++) {
        add_class_to_teach(new_teacher, class_nos[i]);
    }

    admin_add_teacher(&admin, new_teacher);
    printf("Teacher added successfully.\n");
    pause_screen();
}

void action_remove_teacher() {
    clear_screen();
    printf("===== REMOVE TEACHER =====\n");
    if (school.teacher_count == 0) {
        printf("No teachers in the system.\n");
        pause_screen();
        return;
    }
    view_all_teachers(&school);
    printf("Enter teacher ID to remove: ");
    int id = get_int_input();
    if (get_teacher_from_school(&school, id) == NULL) {
        printf("Teacher not found.\n");
    } else {
        admin_remove_teacher(&admin, id);
        printf("Teacher removed successfully.\n");
    }
    pause_screen();
}

void action_add_class() {
    clear_screen();
    printf("===== ADD CLASS =====\n");
    if (school.class_count >= MAX_CLASSES) {
        printf("Cannot add more classes.\n");
        pause_screen();
        return;
    }

    char class_no[10];
    char incharge[MAX_NAME_LEN];

    printf("Enter class number: ");
    get_string_input(class_no, 10);

    if (get_class_from_school(&school, class_no) != NULL) {
        printf("Class already exists.\n");
        pause_screen();
        return;
    }

    printf("Enter class incharge: ");
    get_string_input(incharge, MAX_NAME_LEN);

    Classroom *new_class = &classrooms[school.class_count];
    init_classroom(new_class, class_no, incharge);
    admin_add_class(&admin, new_class);
    printf("Class added successfully.\n");
    pause_screen();
}

void action_remove_class() {
    clear_screen();
    printf("===== REMOVE CLASS =====\n");
    if (school.class_count == 0) {
        printf("No classes in the system.\n");
        pause_screen();
        return;
    }
    
    printf("Available classes: ");
    for(int i=0; i<school.class_count; i++) printf("%s ", school.classes[i]->class_no);
    printf("\n");

    char class_no[10];
    printf("Enter class number to remove: ");
    get_string_input(class_no, 10);

    if (get_class_from_school(&school, class_no) == NULL) {
        printf("Class does not exist.\n");
    } else {
        admin_remove_class(&admin, class_no);
        printf("Class removed successfully.\n");
    }
    pause_screen();
}

void action_view_class_details() {
    clear_screen();
    printf("===== VIEW CLASS DETAILS =====\n");
    if (school.class_count == 0) {
        printf("No classes in the system.\n");
        pause_screen();
        return;
    }
    
    printf("Available classes: ");
    for(int i=0; i<school.class_count; i++) printf("%s ", school.classes[i]->class_no);
    printf("\n");

    char class_no[10];
    printf("Enter class number: ");
    get_string_input(class_no, 10);
    
    view_school_class_details(&school, class_no);
    pause_screen();
}

void action_add_student() {
    clear_screen();
    printf("===== ADD STUDENT =====\n");
    if (school.class_count == 0) {
        printf("No classes in the system. Please add a class first.\n");
        pause_screen();
        return;
    }

    printf("Available classes: ");
    for(int i=0; i<school.class_count; i++) printf("%s ", school.classes[i]->class_no);
    printf("\n");

    char class_no[10];
    printf("Enter class number: ");
    get_string_input(class_no, 10);

    Classroom *c = get_class_from_school(&school, class_no);
    if (c == NULL) {
        printf("Class does not exist.\n");
        pause_screen();
        return;
    }

    if (global_student_count >= MAX_CLASSES * MAX_STUDENTS_PER_CLASS) {
        printf("Global student limit reached.\n");
        pause_screen();
        return;
    }

    char name[MAX_NAME_LEN];
    int entry_number;
    char password[MAX_PASS_LEN];

    printf("Enter student name: ");
    get_string_input(name, MAX_NAME_LEN);
    printf("Enter entry number: ");
    entry_number = get_int_input();

    if (find_student_in_school(&school, entry_number) != NULL) {
        printf("Entry number already exists.\n");
        pause_screen();
        return;
    }

    printf("Enter password: ");
    get_string_input(password, MAX_PASS_LEN);

    Student *new_student = &students[global_student_count++];
    init_student(new_student, name, class_no, entry_number, password);

    int num_subjects;
    printf("Enter number of subjects: ");
    num_subjects = get_int_input();

    for (int i = 0; i < num_subjects; i++) {
        char subject[MAX_NAME_LEN];
        float grade;
        printf("Enter subject name %d: ", i+1);
        get_string_input(subject, MAX_NAME_LEN);
        printf("Enter grade for %s: ", subject);
        grade = get_float_input();
        if (grade < 0 || grade > 100) {
            printf("Invalid grade. Using 0.0\n");
            grade = 0.0;
        }
        add_subject(new_student, subject, grade);
    }

    add_student_to_class(c, new_student);
    printf("Student added successfully.\n");
    pause_screen();
}

void action_update_student_fee() {
    clear_screen();
    printf("===== UPDATE STUDENT FEE =====\n");
    printf("Enter student entry number: ");
    int entry_number = get_int_input();
    
    Student *s = find_student_in_school(&school, entry_number);
    if (s == NULL) {
        printf("Student not found.\n");
        pause_screen();
        return;
    }

    printf("Current fee: $%.2f\n", s->fees);
    printf("Enter new fee amount: $");
    float new_fee = get_float_input();
    
    if (new_fee < 0) {
        printf("Invalid fee amount.\n");
        pause_screen();
        return;
    }

    if (admin_update_student_fee(&admin, entry_number, new_fee)) {
        printf("Fee updated successfully.\n");
    } else {
        printf("Failed to update fee.\n");
    }
    pause_screen();
}

void action_change_admin_password() {
    clear_screen();
    printf("===== CHANGE ADMIN PASSWORD =====\n");
    char current_pass[MAX_PASS_LEN];
    printf("Enter current password: ");
    get_string_input(current_pass, MAX_PASS_LEN);

    if (!authenticate_admin(&admin, admin.username, current_pass)) {
        printf("Incorrect current password.\n");
        pause_screen();
        return;
    }

    char new_pass[MAX_PASS_LEN];
    char confirm_pass[MAX_PASS_LEN];
    printf("Enter new password: ");
    get_string_input(new_pass, MAX_PASS_LEN);
    printf("Confirm new password: ");
    get_string_input(confirm_pass, MAX_PASS_LEN);

    if (strcmp(new_pass, confirm_pass) != 0) {
        printf("Passwords do not match.\n");
        pause_screen();
        return;
    }

    admin_update_password(&admin, new_pass);
    printf("Password changed successfully.\n");
    pause_screen();
}

void teacher_login() {
    clear_screen();
    printf("===== TEACHER LOGIN =====\n");
    printf("Enter Teacher ID: ");
    int id = get_int_input();
    
    Teacher *t = get_teacher_from_school(&school, id);
    if (t == NULL) {
        printf("Teacher not found.\n");
        pause_screen();
        return;
    }

    char password[MAX_PASS_LEN];
    printf("Enter Password: ");
    get_string_input(password, MAX_PASS_LEN);

    if (authenticate_teacher(t, password)) {
        teacher_menu(t);
    } else {
        printf("Invalid password.\n");
        pause_screen();
    }
}

void teacher_menu(Teacher *t) {
    while (1) {
        clear_screen();
        printf("===== TEACHER MENU =====\n");
        printf("Welcome, %s!\n", t->name);
        printf("1. View My Details\n");
        printf("2. View My Classes\n");
        printf("3. View Students in a Class\n");
        printf("4. Update Grade for a Student\n");
        printf("5. Change Password\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");

        int choice = get_int_input();

        if (choice == 1) {
            view_teacher_details(t);
            pause_screen();
        } else if (choice == 2) {
            action_teacher_view_classes(t);
        } else if (choice == 3) {
            action_teacher_view_students(t);
        } else if (choice == 4) {
            action_teacher_update_grade(t);
        } else if (choice == 5) {
            action_teacher_change_password(t);
        } else if (choice == 6) {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
            pause_screen();
        }
    }
}

void action_teacher_view_classes(Teacher *t) {
    clear_screen();
    printf("===== MY CLASSES =====\n");
    if (t->class_count == 0) {
        printf("You are not assigned to any classes.\n");
    } else {
        printf("You teach the following classes:\n");
        for (int i = 0; i < t->class_count; i++) {
            Classroom *c = get_class_from_school(&school, t->classes_to_teach[i]);
            if (c) {
                printf("Class: %s, Incharge: %s\n", c->class_no, c->incharge);
                printf("Number of students: %d\n", c->student_count);
                printf("Class Average GPA: %.2f\n\n", calculate_class_average(c));
            }
        }
    }
    pause_screen();
}

void action_teacher_view_students(Teacher *t) {
    clear_screen();
    printf("===== VIEW STUDENTS IN CLASS =====\n");
    if (t->class_count == 0) {
        printf("You are not assigned to any classes.\n");
        pause_screen();
        return;
    }
    
    printf("Your classes: ");
    for(int i=0; i<t->class_count; i++) printf("%s ", t->classes_to_teach[i]);
    printf("\n");

    char class_no[10];
    printf("Enter class number: ");
    get_string_input(class_no, 10);

    int teaches_class = 0;
    for(int i=0; i<t->class_count; i++) {
        if(strcmp(t->classes_to_teach[i], class_no) == 0) {
            teaches_class = 1;
            break;
        }
    }

    if (!teaches_class) {
        printf("You don't teach this class.\n");
        pause_screen();
        return;
    }

    Classroom *c = get_class_from_school(&school, class_no);
    if (c) {
        printf("Students in class %s:\n", class_no);
        view_class_students(c);
    } else {
        printf("Class not found.\n");
    }
    pause_screen();
}

void action_teacher_update_grade(Teacher *t) {
    clear_screen();
    printf("===== UPDATE STUDENT GRADE =====\n");
    if (t->class_count == 0) {
        printf("You are not assigned to any classes.\n");
        pause_screen();
        return;
    }

    printf("Your classes: ");
    for(int i=0; i<t->class_count; i++) printf("%s ", t->classes_to_teach[i]);
    printf("\n");

    char class_no[10];
    printf("Enter class number: ");
    get_string_input(class_no, 10);

    int teaches_class = 0;
    for(int i=0; i<t->class_count; i++) {
        if(strcmp(t->classes_to_teach[i], class_no) == 0) {
            teaches_class = 1;
            break;
        }
    }

    if (!teaches_class) {
        printf("You don't teach this class.\n");
        pause_screen();
        return;
    }

    Classroom *c = get_class_from_school(&school, class_no);
    if (!c) {
        printf("Class not found.\n");
        pause_screen();
        return;
    }

    if (c->student_count == 0) {
        printf("No students in this class.\n");
        pause_screen();
        return;
    }

    printf("Students in class %s:\n", class_no);
    view_class_students(c);

    printf("Enter student entry number: ");
    int entry_number = get_int_input();
    
    Student *s = get_student_from_class(c, entry_number);
    if (!s) {
        printf("Student not found in this class.\n");
        pause_screen();
        return;
    }

    int has_subject = 0;
    for (int i = 0; i < s->subject_count; i++) {
        if (strcmp(s->subjects[i].name, t->subject) == 0) {
            has_subject = 1;
            break;
        }
    }

    if (!has_subject) {
        printf("This student is not enrolled in %s.\n", t->subject);
        printf("Do you want to add this subject? (y/n): ");
        char choice[10];
        get_string_input(choice, 10);
        if (choice[0] != 'y' && choice[0] != 'Y') {
            pause_screen();
            return;
        }
    }

    printf("Enter new grade for %s: ", t->subject);
    float grade = get_float_input();
    if (grade < 0 || grade > 100) {
        printf("Invalid grade.\n");
        pause_screen();
        return;
    }

    if (has_subject) {
        for (int i = 0; i < s->subject_count; i++) {
            if (strcmp(s->subjects[i].name, t->subject) == 0) {
                s->subjects[i].grade = grade;
                break;
            }
        }
        s->gpa = calculate_gpa(s);
    } else {
        add_subject(s, t->subject, grade);
    }
    printf("Grade updated successfully.\n");
    pause_screen();
}

void action_teacher_change_password(Teacher *t) {
    clear_screen();
    printf("===== CHANGE PASSWORD =====\n");
    char old_pass[MAX_PASS_LEN];
    char new_pass[MAX_PASS_LEN];
    char confirm_pass[MAX_PASS_LEN];

    printf("Enter current password: ");
    get_string_input(old_pass, MAX_PASS_LEN);
    printf("Enter new password: ");
    get_string_input(new_pass, MAX_PASS_LEN);
    printf("Confirm new password: ");
    get_string_input(confirm_pass, MAX_PASS_LEN);

    if (strcmp(new_pass, confirm_pass) != 0) {
        printf("Passwords do not match.\n");
        pause_screen();
        return;
    }

    if (update_teacher_password(t, old_pass, new_pass)) {
        printf("Password changed successfully.\n");
    } else {
        printf("Current password is incorrect.\n");
    }
    pause_screen();
}

void student_login() {
    clear_screen();
    printf("===== STUDENT LOGIN =====\n");
    printf("Enter Entry Number: ");
    int entry_number = get_int_input();

    Student *s = find_student_in_school(&school, entry_number);
    if (!s) {
        printf("Student not found.\n");
        pause_screen();
        return;
    }

    char password[MAX_PASS_LEN];
    printf("Enter Password: ");
    get_string_input(password, MAX_PASS_LEN);

    if (authenticate_student(s, password)) {
        student_menu(s);
    } else {
        printf("Invalid password.\n");
        pause_screen();
    }
}

void student_menu(Student *s) {
    while (1) {
        clear_screen();
        printf("===== STUDENT MENU =====\n");
        printf("Welcome, %s!\n", s->name);
        printf("1. View My Information\n");
        printf("2. View My Subjects and Grades\n");
        printf("3. Check Fee Status\n");
        printf("4. Change Password\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");

        int choice = get_int_input();

        if (choice == 1) {
            display_student_info(s);
            pause_screen();
        } else if (choice == 2) {
            action_student_view_grades(s);
        } else if (choice == 3) {
            action_student_view_fee(s);
        } else if (choice == 4) {
            action_student_change_password(s);
        } else if (choice == 5) {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
            pause_screen();
        }
    }
}

void action_student_view_grades(Student *s) {
    clear_screen();
    printf("===== MY SUBJECTS AND GRADES =====\n");
    view_subjects(s);
    printf("GPA: %.2f\n", s->gpa);
    pause_screen();
}

void action_student_view_fee(Student *s) {
    clear_screen();
    printf("===== FEE STATUS =====\n");
    printf("Name: %s\n", s->name);
    printf("Class: %s\n", s->class_name);
    printf("Entry Number: %d\n", s->entry_number);
    printf("Fee Amount: $%.2f\n", s->fees);
    pause_screen();
}

void action_student_change_password(Student *s) {
    clear_screen();
    printf("===== CHANGE PASSWORD =====\n");
    char old_pass[MAX_PASS_LEN];
    char new_pass[MAX_PASS_LEN];
    char confirm_pass[MAX_PASS_LEN];

    printf("Enter current password: ");
    get_string_input(old_pass, MAX_PASS_LEN);
    printf("Enter new password: ");
    get_string_input(new_pass, MAX_PASS_LEN);
    printf("Confirm new password: ");
    get_string_input(confirm_pass, MAX_PASS_LEN);

    if (strcmp(new_pass, confirm_pass) != 0) {
        printf("Passwords do not match.\n");
        pause_screen();
        return;
    }

    if (update_student_password(s, old_pass, new_pass)) {
        printf("Password changed successfully.\n");
    } else {
        printf("Current password is incorrect.\n");
    }
    pause_screen();
}
