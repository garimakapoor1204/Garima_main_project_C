#ifndef ADMIN_H
#define ADMIN_H

#include "school.h"

typedef struct {
    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
    School *school;
} Admin;

void init_admin(Admin *a, const char *username, const char *password, School *school);
int authenticate_admin(const Admin *a, const char *username, const char *password);
void admin_view_school_details(const Admin *a);
void admin_add_teacher(Admin *a, Teacher *t);
void admin_remove_teacher(Admin *a, int teacher_id);
void admin_add_class(Admin *a, Classroom *c);
void admin_remove_class(Admin *a, const char *class_no);
void admin_view_fee_record(const Admin *a);
int admin_update_student_fee(Admin *a, int entry_number, float new_fee);
int admin_update_teacher_password(Admin *a, int teacher_id, const char *old_pass, const char *new_pass);
void admin_update_password(Admin *a, const char *new_pass);

#endif
