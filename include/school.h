#ifndef SCHOOL_H
#define SCHOOL_H

#include "classroom.h"
#include "teacher.h"

#define MAX_CLASSES 20
#define MAX_TEACHERS 20

typedef struct {
    char school_name[100];
    Classroom *classes[MAX_CLASSES];
    int class_count;
    Teacher *teachers[MAX_TEACHERS];
    int teacher_count;
} School;

void init_school(School *s, const char *name);
void add_class_to_school(School *s, Classroom *c);
void remove_class_from_school(School *s, const char *class_no);
void add_teacher_to_school(School *s, Teacher *t);
void remove_teacher_from_school(School *s, int teacher_id);
void view_school_class_details(School *s, const char *class_no);
void view_school_teacher_details(School *s, int teacher_id);
Student* find_student_in_school(School *s, int entry_number);
void view_all_students(const School *s);
void view_all_teachers(const School *s);
Classroom* get_class_from_school(School *s, const char *class_no);
Teacher* get_teacher_from_school(School *s, int teacher_id);

#endif
