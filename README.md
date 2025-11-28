# ScholarSync: A School Management System

**ScholarSync** is a Python-based school management system designed to streamline administrative tasks, manage student and teacher information, and facilitate communication within a school environment. It provides role-based access for admins, teachers, and students, ensuring each user can perform their designated tasks efficiently. The system includes classes such as `Student`, `Teacher`, `Classroom`, `School`, `Admin`, and an `Interface` class to handle user interactions.

---

## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [User Manual](#user-manual)
   - [Admin](#admin)
   - [Teacher](#teacher)
   - [Student](#student)
6. [Contributing](#contributing)
7. [License](#license)
8. [Contact](#contact)

---

## Project Overview
**ScholarSync** simplifies school management by offering a command-line interface for admins, teachers, and students. Built in Python, it supports tasks like adding/removing teachers and students, managing classes, updating grades, tracking fees, and more. The system is object-oriented, with distinct classes handling different entities and their interactions, making it modular and easy to extend.

---

## Features

### Admin Features
- View school details (name, classes, teachers)
- Add, remove, and view teachers
- Add, remove, and view classes
- Add students to classes
- View all students across classes
- View and update fee records
- Change admin password

### Teacher Features
- View personal details (ID, name, subject, assigned classes)
- View assigned classes (with student count and average GPA)
- View students in a specific class
- Update student grades for their subject
- Change password

### Student Features
- View personal information (name, class, entry number, GPA, fees, subjects)
- View subjects and grades
- Check fee status
- Change password

### General Features
- Secure login system for all roles (username/password authentication)
- Data management for students, teachers, and classes
- **Note:** Data is not persisted between sessions in this version. Future updates may include database integration.

---

## Installation
To run **ScholarSync**, you need Python 3.x installed on your system. Follow these steps:

1. **Clone or Download the Repository**
   - Clone the repository using Git:
     ```bash
     git clone https://github.com/sitendernarwal/ScholarSync-A-School-Management-System
     ```
   - Or download the source code as a ZIP file and extract it.

2. **Navigate to the Project Directory**
   ```bash
   cd ScholarSync-A-School-Management-System
   ```

3. **Run the Main Script**
   - The entry point is `main.py`. Run it with:
     ```bash
     python main.py
     ```

No additional dependencies are required beyond a standard Python installation.

---

## Usage
When you run `main.py`, the system displays the main menu:

```
===== Sitender's School of Science and Technology =====
1. Admin Login
2. Teacher Login
3. Student Login
4. Exit
Enter your choice:
```

- **Option 1:** Log in as an Admin
- **Option 2:** Log in as a Teacher
- **Option 3:** Log in as a Student
- **Option 4:** Exit the program

Each role has its own menu with specific options, detailed in the [User Manual](#user-manual) section below.

---

## User Manual

### Admin

#### Login Credentials
- **Username:** `admin`
- **Password:** `admin123`

#### Admin Menu Options
After logging in, the admin sees:

```
===== ADMIN MENU =====
1. View School Details
2. Add Teacher
3. Remove Teacher
4. View All Teachers
5. Add Class
6. Remove Class
7. View Class Details
8. Add Student
9. View All Students
10. View Fee Records
11. Update Student Fee
12. Change Admin Password
13. Back to Main Menu
```

1. **View School Details**
   - Displays the school name, list of classes (with incharges), and list of teachers (with IDs, names, subjects).

2. **Add Teacher**
   - Prompts for:
     - Teacher name
     - Subject
     - Teacher ID (must be unique)
     - Class numbers to teach (space-separated, must exist)
     - Password
   - Adds the teacher to the system.

3. **Remove Teacher**
   - Lists all teachers, then prompts for a teacher ID to remove.

4. **View All Teachers**
   - Displays a list of all teachers with their IDs, names, and subjects.

5. **Add Class**
   - Prompts for:
     - Class number (e.g., "10A", must be unique)
     - Incharge name
   - Adds the class to the system.

6. **Remove Class**
   - Lists available classes, then prompts for a class number to remove.

7. **View Class Details**
   - Prompts for a class number and displays its incharge, student list, and average GPA.

8. **Add Student**
   - Prompts for:
     - Class number (must exist)
     - Student name
     - Entry number (must be unique)
     - Password
     - Number of subjects
     - Subject names and grades (0-100)
   - Adds the student to the specified class.

9. **View All Students**
   - Lists all students across all classes, grouped by class number.

10. **View Fee Records**
    - Displays fee records for all students, showing entry number, name, and fee amount.

11. **Update Student Fee**
    - Prompts for:
      - Student entry number
      - New fee amount (must be non-negative)
    - Updates the student’s fee.

12. **Change Admin Password**
    - Prompts for current password, new password, and confirmation.
    - Updates the admin password if the current password is correct.

13. **Back to Main Menu**
    - Returns to the main login screen.

---

### Teacher

#### Login
- **Teacher ID:** Assigned when added by the admin
- **Password:** Set when added by the admin

#### Teacher Menu Options
After logging in, the teacher sees:

```
===== TEACHER MENU =====
Welcome, <Teacher Name>!
1. View My Details
2. View My Classes
3. View Students in a Class
4. Update Grade for a Student
5. Change Password
6. Back to Main Menu
```

1. **View My Details**
   - Displays teacher ID, name, subject, and assigned classes.

2. **View My Classes**
   - Shows details of assigned classes, including incharge, number of students, and average GPA.

3. **View Students in a Class**
   - Prompts for a class number (must be one they teach).
   - Lists students in that class by name and entry number.

4. **Update Grade for a Student**
   - Prompts for:
     - Class number (must be one they teach)
     - Student entry number
     - New grade (0-100) for their subject
   - Adds the subject if not already enrolled, or updates the existing grade.

5. **Change Password**
   - Prompts for current password, new password, and confirmation.
   - Updates the password if the current password is correct.

6. **Back to Main Menu**
   - Returns to a main login screen.

---

### Student

#### Login
- **Entry Number:** Assigned when added by the admin
- **Password:** Set when added by the admin

#### Student Menu Options
After logging in, the student sees:

```
===== STUDENT MENU =====
Welcome, <Student Name>!
1. View My Information
2. View My Subjects and Grades
3. Check Fee Status
4. Change Password
5. Back to Main Menu
```

1. **View My Information**
   - Displays name, class, entry number, GPA, fees, and subjects with grades.

2. **View My Subjects and Grades**
   - Lists all subjects and their grades, plus the overall GPA.

3. **Check Fee Status**
   - Shows the student’s name, class, entry number, and current fee amount.

4. **Change Password**
   - Prompts for current password, new password, and confirmation.
   - Updates the password if the current password is correct.

5. **Back to Main Menu**
   - Returns to the main login screen.

---

## Contributing
Contributions to **ScholarSync** are welcome! To contribute:
1. Fork the repository.
2. Create a branch for your feature or bug fix:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Description of changes"
   ```
4. Push to your fork:
   ```bash
   git push origin feature-name
   ```
5. Submit a pull request.

For major changes, please open an issue first to discuss your ideas.

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Contact
For inquiries or support, please contact:
- 🧑‍💻 **Name:** <a href="mailto:garimakapoor.work@gmail.com"><strong>Garima Kapoor</strong></a>

- **Email:** [📧 Email Me](mailto:sitendermax@gmail.com)

