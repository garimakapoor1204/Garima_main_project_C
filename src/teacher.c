#include <stdio.h>
#include <string.h>
#include "../include/teacher.h"

void init_teacher(Teacher *t, int id, const char *name, const char *subject, const char *password) {
    t->teacher_id = id;
    strncpy(t->name, name, MAX_NAME_LEN - 1);
    t->name[MAX_NAME_LEN - 1] = '\0';
    
    strncpy(t->subject, subject, MAX_NAME_LEN - 1);
    t->subject[MAX_NAME_LEN - 1] = '\0';
    
    t->class_count = 0;
    
    strncpy(t->password, password, MAX_PASS_LEN - 1);
    t->password[MAX_PASS_LEN - 1] = '\0';
}

int authenticate_teacher(const Teacher *t, const char *password) {
    return strcmp(t->password, password) == 0;
}

void view_teacher_details(const Teacher *t) {
    printf("\n========== TEACHER INFORMATION ==========\n");
    printf("ID: %d\n", t->teacher_id);
    printf("Name: %s\n", t->name);
    printf("Subject: %s\n", t->subject);
    printf("Classes to Teach: ");
    if (t->class_count == 0) {
        printf("None");
    } else {
        for (int i = 0; i < t->class_count; i++) {
            printf("%s", t->classes_to_teach[i]);
            if (i < t->class_count - 1) printf(", ");
        }
    }
    printf("\n========================================\n\n");
}

int update_teacher_password(Teacher *t, const char *old_pass, const char *new_pass) {
    if (authenticate_teacher(t, old_pass)) {
        strncpy(t->password, new_pass, MAX_PASS_LEN - 1);
        t->password[MAX_PASS_LEN - 1] = '\0';
        return 1;
    }
    return 0;
}

void add_class_to_teach(Teacher *t, const char *class_no) {
    for (int i = 0; i < t->class_count; i++) {
        if (strcmp(t->classes_to_teach[i], class_no) == 0) {
            return; // Already exists
        }
    }
    if (t->class_count < MAX_CLASSES_TO_TEACH) {
        strncpy(t->classes_to_teach[t->class_count], class_no, 9);
        t->classes_to_teach[t->class_count][9] = '\0';
        t->class_count++;
    }
}

void remove_class_to_teach(Teacher *t, const char *class_no) {
    int found = -1;
    for (int i = 0; i < t->class_count; i++) {
        if (strcmp(t->classes_to_teach[i], class_no) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        for (int i = found; i < t->class_count - 1; i++) {
            strcpy(t->classes_to_teach[i], t->classes_to_teach[i+1]);
        }
        t->class_count--;
    }
}
