#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/school.h"

void init_school(School *s, const char *name) {
    strncpy(s->school_name, name, 99);
    s->school_name[99] = '\0';
    s->class_count = 0;
    s->teacher_count = 0;
    for(int i=0; i<MAX_CLASSES; i++) s->classes[i] = NULL;
    for(int i=0; i<MAX_TEACHERS; i++) s->teachers[i] = NULL;
}

void add_class_to_school(School *s, Classroom *c) {
    if (s->class_count < MAX_CLASSES) {
        s->classes[s->class_count++] = c;
    } else {
        printf("Cannot add more classes.\n");
    }
}

void remove_class_from_school(School *s, const char *class_no) {
    int found = -1;
    for (int i = 0; i < s->class_count; i++) {
        if (strcmp(s->classes[i]->class_no, class_no) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        // Note: In a real app we might need to free memory if it was malloc'd. 
        // Here we assume memory is managed elsewhere or static for simplicity, 
        // but typically we should free the Classroom* if we own it.
        // For this conversion, we'll just remove the pointer from the list.
        for (int i = found; i < s->class_count - 1; i++) {
            s->classes[i] = s->classes[i+1];
        }
        s->classes[s->class_count - 1] = NULL;
        s->class_count--;
    }
}

void add_teacher_to_school(School *s, Teacher *t) {
    if (s->teacher_count < MAX_TEACHERS) {
        s->teachers[s->teacher_count++] = t;
    } else {
        printf("Cannot add more teachers.\n");
    }
}

void remove_teacher_from_school(School *s, int teacher_id) {
    int found = -1;
    for (int i = 0; i < s->teacher_count; i++) {
        if (s->teachers[i]->teacher_id == teacher_id) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        for (int i = found; i < s->teacher_count - 1; i++) {
            s->teachers[i] = s->teachers[i+1];
        }
        s->teachers[s->teacher_count - 1] = NULL;
        s->teacher_count--;
    }
}

void view_school_class_details(School *s, const char *class_no) {
    Classroom *c = get_class_from_school(s, class_no);
    if (c) {
        view_class_details(c);
    } else {
        printf("Class not found.\n");
    }
}

void view_school_teacher_details(School *s, int teacher_id) {
    Teacher *t = get_teacher_from_school(s, teacher_id);
    if (t) {
        view_teacher_details(t);
    } else {
        printf("Teacher not found.\n");
    }
}

Student* find_student_in_school(School *s, int entry_number) {
    for (int i = 0; i < s->class_count; i++) {
        Student *st = get_student_from_class(s->classes[i], entry_number);
        if (st) return st;
    }
    return NULL;
}

void view_all_students(const School *s) {
    printf("\n========== ALL STUDENTS ==========\n");
    int found = 0;
    for (int i = 0; i < s->class_count; i++) {
        if (s->classes[i]->student_count > 0) {
            found = 1;
            printf("Class %s:\n", s->classes[i]->class_no);
            view_class_students(s->classes[i]);
        }
    }
    if (!found) {
        printf("No students enrolled in any class.\n");
    }
    printf("================================\n\n");
}

void view_all_teachers(const School *s) {
    printf("\n========== ALL TEACHERS ==========\n");
    if (s->teacher_count == 0) {
        printf("No teachers in the system.\n");
    } else {
        for (int i = 0; i < s->teacher_count; i++) {
            printf("ID: %d, Name: %s, Subject: %s\n", 
                   s->teachers[i]->teacher_id, s->teachers[i]->name, s->teachers[i]->subject);
        }
    }
    printf("================================\n\n");
}

Classroom* get_class_from_school(School *s, const char *class_no) {
    for (int i = 0; i < s->class_count; i++) {
        if (strcmp(s->classes[i]->class_no, class_no) == 0) {
            return s->classes[i];
        }
    }
    return NULL;
}

Teacher* get_teacher_from_school(School *s, int teacher_id) {
    for (int i = 0; i < s->teacher_count; i++) {
        if (s->teachers[i]->teacher_id == teacher_id) {
            return s->teachers[i];
        }
    }
    return NULL;
}
