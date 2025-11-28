#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LEN 50
#define MAX_PASS_LEN 20
#define MAX_SUBJECTS 10

typedef struct {
    char name[MAX_NAME_LEN];
    float grade;
} Subject;

typedef struct {
    char name[MAX_NAME_LEN];
    char class_name[10];
    int entry_number;
    float fees;
    Subject subjects[MAX_SUBJECTS];
    int subject_count;
    float gpa;
    char password[MAX_PASS_LEN];
} Student;

void init_student(Student *s, const char *name, const char *class_name, int entry_number, const char *password);
void add_subject(Student *s, const char *subject, float grade);
void remove_subject(Student *s, const char *subject);
float calculate_gpa(Student *s);
void view_subjects(const Student *s);
int authenticate_student(const Student *s, const char *password);
void display_student_info(const Student *s);
int update_student_password(Student *s, const char *old_pass, const char *new_pass);

#endif
