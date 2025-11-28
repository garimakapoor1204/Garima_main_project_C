#include <stdio.h>
#include <string.h>
#include "../include/admin.h"

void init_admin(Admin *a, const char *username, const char *password, School *school) {
    strncpy(a->username, username, MAX_NAME_LEN - 1);
    a->username[MAX_NAME_LEN - 1] = '\0';
    
    strncpy(a->password, password, MAX_PASS_LEN - 1);
    a->password[MAX_PASS_LEN - 1] = '\0';
    
    a->school = school;
}

int authenticate_admin(const Admin *a, const char *username, const char *password) {
    return (strcmp(a->username, username) == 0 && strcmp(a->password, password) == 0);
}

void admin_view_school_details(const Admin *a) {
    printf("\n========== SCHOOL INFORMATION ==========\n");
    printf("School Name: %s\n", a->school->school_name);
    printf("\nClasses (%d):\n", a->school->class_count);
    for (int i = 0; i < a->school->class_count; i++) {
        printf("  Class Number: %s, Incharge: %s\n", 
               a->school->classes[i]->class_no, a->school->classes[i]->incharge);
    }
    printf("\nTeachers (%d):\n", a->school->teacher_count);
    for (int i = 0; i < a->school->teacher_count; i++) {
        printf("  Teacher ID: %d, Name: %s, Subject: %s\n", 
               a->school->teachers[i]->teacher_id, a->school->teachers[i]->name, a->school->teachers[i]->subject);
    }
    printf("========================================\n\n");
}

void admin_add_teacher(Admin *a, Teacher *t) {
    add_teacher_to_school(a->school, t);
}

void admin_remove_teacher(Admin *a, int teacher_id) {
    remove_teacher_from_school(a->school, teacher_id);
}

void admin_add_class(Admin *a, Classroom *c) {
    add_class_to_school(a->school, c);
}

void admin_remove_class(Admin *a, const char *class_no) {
    remove_class_from_school(a->school, class_no);
}

void admin_view_fee_record(const Admin *a) {
    printf("\n========== FEE RECORDS ==========\n");
    int found = 0;
    for (int i = 0; i < a->school->class_count; i++) {
        if (a->school->classes[i]->student_count > 0) {
            found = 1;
            printf("Class %s:\n", a->school->classes[i]->class_no);
            for (int j = 0; j < a->school->classes[i]->student_count; j++) {
                Student *s = a->school->classes[i]->students[j];
                printf("  Student ID: %d, Name: %s, Fees: $%.2f\n", 
                       s->entry_number, s->name, s->fees);
            }
        }
    }
    if (!found) {
        printf("No students enrolled in any class.\n");
    }
    printf("================================\n\n");
}

int admin_update_student_fee(Admin *a, int entry_number, float new_fee) {
    Student *s = find_student_in_school(a->school, entry_number);
    if (s) {
        s->fees = new_fee;
        return 1;
    }
    return 0;
}

int admin_update_teacher_password(Admin *a, int teacher_id, const char *old_pass, const char *new_pass) {
    Teacher *t = get_teacher_from_school(a->school, teacher_id);
    if (t) {
        return update_teacher_password(t, old_pass, new_pass);
    }
    return 0;
}

void admin_update_password(Admin *a, const char *new_pass) {
    strncpy(a->password, new_pass, MAX_PASS_LEN - 1);
    a->password[MAX_PASS_LEN - 1] = '\0';
}
