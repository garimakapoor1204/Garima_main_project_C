#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "student.h"

#define MAX_STUDENTS_PER_CLASS 50

typedef struct {
    char class_no[10];
    char incharge[MAX_NAME_LEN];
    Student *students[MAX_STUDENTS_PER_CLASS]; // Pointers to students
    int student_count;
} Classroom;

void init_classroom(Classroom *c, const char *class_no, const char *incharge);
void add_student_to_class(Classroom *c, Student *s);
void remove_student_from_class(Classroom *c, int entry_number);
void view_class_students(const Classroom *c);
float calculate_class_average(const Classroom *c);
void view_class_details(const Classroom *c);
Student* get_student_from_class(Classroom *c, int entry_number);

#endif
