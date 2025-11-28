#include <stdio.h>
#include <string.h>
#include "../include/student.h"

void init_student(Student *s, const char *name, const char *class_name, int entry_number, const char *password) {
    strncpy(s->name, name, MAX_NAME_LEN - 1);
    s->name[MAX_NAME_LEN - 1] = '\0';
    
    strncpy(s->class_name, class_name, 9);
    s->class_name[9] = '\0';
    
    s->entry_number = entry_number;
    s->fees = 1000.0;
    s->subject_count = 0;
    s->gpa = 0.0;
    
    strncpy(s->password, password, MAX_PASS_LEN - 1);
    s->password[MAX_PASS_LEN - 1] = '\0';
}

void add_subject(Student *s, const char *subject, float grade) {
    if (s->subject_count < MAX_SUBJECTS) {
        strncpy(s->subjects[s->subject_count].name, subject, MAX_NAME_LEN - 1);
        s->subjects[s->subject_count].name[MAX_NAME_LEN - 1] = '\0';
        s->subjects[s->subject_count].grade = grade;
        s->subject_count++;
        s->gpa = calculate_gpa(s);
    } else {
        printf("Cannot add more subjects.\n");
    }
}

float calculate_gpa(Student *s) {
    if (s->subject_count == 0) return 0.0;
    float total = 0.0;
    for (int i = 0; i < s->subject_count; i++) {
        total += s->subjects[i].grade;
    }
    return total / s->subject_count;
}

void view_subjects(const Student *s) {
    printf("Subjects: \n");
    if (s->subject_count == 0) {
        printf("  No subjects enrolled\n");
        return;
    }
    for (int i = 0; i < s->subject_count; i++) {
        printf("  %s - %.2f\n", s->subjects[i].name, s->subjects[i].grade);
    }
}

int authenticate_student(const Student *s, const char *password) {
    return strcmp(s->password, password) == 0;
}

void display_student_info(const Student *s) {
    printf("\n========== STUDENT INFORMATION ==========\n");
    printf("Name: %s\n", s->name);
    printf("Class: %s\n", s->class_name);
    printf("Entry Number: %d\n", s->entry_number);
    printf("GPA: %.2f\n", s->gpa);
    printf("Fees: $%.2f\n", s->fees);
    view_subjects(s);
    printf("========================================\n\n");
}

int update_student_password(Student *s, const char *old_pass, const char *new_pass) {
    if (authenticate_student(s, old_pass)) {
        strncpy(s->password, new_pass, MAX_PASS_LEN - 1);
        s->password[MAX_PASS_LEN - 1] = '\0';
        return 1;
    }
    return 0;
}
