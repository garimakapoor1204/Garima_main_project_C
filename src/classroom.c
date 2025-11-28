#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/classroom.h"

void init_classroom(Classroom *c, const char *class_no, const char *incharge) {
    strncpy(c->class_no, class_no, 9);
    c->class_no[9] = '\0';
    
    strncpy(c->incharge, incharge, MAX_NAME_LEN - 1);
    c->incharge[MAX_NAME_LEN - 1] = '\0';
    
    c->student_count = 0;
    for (int i = 0; i < MAX_STUDENTS_PER_CLASS; i++) {
        c->students[i] = NULL;
    }
}

void add_student_to_class(Classroom *c, Student *s) {
    if (c->student_count < MAX_STUDENTS_PER_CLASS) {
        c->students[c->student_count++] = s;
    } else {
        printf("Class is full.\n");
    }
}

void remove_student_from_class(Classroom *c, int entry_number) {
    int found = -1;
    for (int i = 0; i < c->student_count; i++) {
        if (c->students[i]->entry_number == entry_number) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        // Shift remaining students
        for (int i = found; i < c->student_count - 1; i++) {
            c->students[i] = c->students[i+1];
        }
        c->students[c->student_count - 1] = NULL;
        c->student_count--;
    }
}

void view_class_students(const Classroom *c) {
    if (c->student_count == 0) {
        printf("  No students in this class.\n");
        return;
    }
    
    // Simple bubble sort for display (sorting by entry number)
    // Note: We are sorting a temporary array of pointers to avoid messing up the main array order if it matters,
    // but here order in main array doesn't strictly matter. Let's just print them.
    // To match Python's sorted output, we should sort.
    
    Student *temp_students[MAX_STUDENTS_PER_CLASS];
    for(int i=0; i<c->student_count; i++) temp_students[i] = c->students[i];
    
    for (int i = 0; i < c->student_count - 1; i++) {
        for (int j = 0; j < c->student_count - i - 1; j++) {
            if (temp_students[j]->entry_number > temp_students[j+1]->entry_number) {
                Student *temp = temp_students[j];
                temp_students[j] = temp_students[j+1];
                temp_students[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < c->student_count; i++) {
        printf("  Name: %s, Entry Number: %d\n", temp_students[i]->name, temp_students[i]->entry_number);
    }
}

float calculate_class_average(const Classroom *c) {
    if (c->student_count == 0) return 0.0;
    float total = 0.0;
    for (int i = 0; i < c->student_count; i++) {
        total += c->students[i]->gpa;
    }
    return total / c->student_count;
}

void view_class_details(const Classroom *c) {
    printf("\n========== CLASS INFORMATION ==========\n");
    printf("Class Number: %s\n", c->class_no);
    printf("Incharge: %s\n", c->incharge);
    printf("Number of students: %d\n", c->student_count);
    printf("Students:\n");
    view_class_students(c);
    printf("Class Average GPA: %.2f\n", calculate_class_average(c));
    printf("======================================\n\n");
}

Student* get_student_from_class(Classroom *c, int entry_number) {
    for (int i = 0; i < c->student_count; i++) {
        if (c->students[i]->entry_number == entry_number) {
            return c->students[i];
        }
    }
    return NULL;
}
