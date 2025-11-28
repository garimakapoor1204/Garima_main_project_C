#ifndef TEACHER_H
#define TEACHER_H

#include "student.h" // For MAX_NAME_LEN, MAX_PASS_LEN

#define MAX_CLASSES_TO_TEACH 10

typedef struct {
    int teacher_id;
    char name[MAX_NAME_LEN];
    char subject[MAX_NAME_LEN];
    char classes_to_teach[MAX_CLASSES_TO_TEACH][10]; // List of class numbers/names
    int class_count;
    char password[MAX_PASS_LEN];
} Teacher;

void init_teacher(Teacher *t, int id, const char *name, const char *subject, const char *password);
int authenticate_teacher(const Teacher *t, const char *password);
void view_teacher_details(const Teacher *t);
int update_teacher_password(Teacher *t, const char *old_pass, const char *new_pass);
void add_class_to_teach(Teacher *t, const char *class_no);
void remove_class_to_teach(Teacher *t, const char *class_no);

#endif
