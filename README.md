# 🎓 ScholarSync - School Management System

A comprehensive C-based school management system designed to streamline administrative tasks, manage student and teacher information, and facilitate seamless communication within educational institutions.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [User Roles & Access](#user-roles--access)
- [Project Structure](#project-structure)
- [Future Enhancements](#future-enhancements)
- [Contact](#contact)

## 🌟 Overview

ScholarSync simplifies school management through an intuitive command-line interface. Built with object-oriented principles, it provides role-based access for administrators, teachers, and students, ensuring each user can efficiently perform their designated tasks. The modular architecture makes it easy to extend and customize for various educational settings.

## ✨ Features

### 👨‍💼 Admin Features
- 🏫 **School Management**: View comprehensive school details
- 👥 **Teacher Management**: Add, remove, and view all teachers
- 📚 **Class Management**: Create, remove, and view class details
- 🎓 **Student Management**: Add students and view across all classes
- 💰 **Fee Management**: Track and update student fee records
- 🔐 **Security**: Change admin password

### 👨‍🏫 Teacher Features
- 📊 **Personal Dashboard**: View personal details and assigned classes
- 👀 **Class Overview**: View students in assigned classes with statistics
- ✏️ **Grade Management**: Update student grades for their subject
- 🔒 **Account Security**: Change password

### 👨‍🎓 Student Features
- 📝 **Personal Information**: View profile including GPA and class details
- 📈 **Academic Records**: View all subjects and grades
- 💳 **Fee Status**: Check current fee status
- 🔑 **Password Management**: Update account password

### 🔧 Core System Features
- Secure role-based authentication system
- Dynamic GPA calculation
- Comprehensive data management for students, teachers, and classes
- User-friendly command-line interface

> **Note**: Current version stores data in memory. Data is not persisted between sessions. Future updates will include database integration.

## 🚀 Installation

### Prerequisites
- gcc installed on your system

### Steps

1. **Clone the repository**
   ```bash
   git clone https://github.com/garimakapoor1204/Garima_main_project_C.git
   ```

2. **Navigate to the project directory**
   ```bash
   cd Garima_main_project_C
   ```

3. **Run the application**
   ```bash
   make

   ./school_management.exe
   ```

No additional dependencies required! 🎉

## 💻 Usage

When you launch the application, you'll see the main menu:

```
===== Garima Kapoor's School of Science and Technology =====
1. Admin Login
2. Teacher Login
3. Student Login
4. Exit
Enter your choice:
```

### Default Login Credentials

#### Admin Access
- **Username**: `admin`
- **Password**: `admin123`

#### Teacher & Student Access
Teachers and students receive their credentials when added to the system by the administrator.

## 👥 User Roles & Access

### Administrator
**Full system control** including:
- Teacher and student management
- Class creation and management
- Fee tracking and updates
- School-wide data access

### Teacher
**Class-specific access** including:
- View assigned classes and students
- Update grades for their subject
- Access student performance data

### Student
**Personal data access** including:
- View academic records and grades
- Check GPA and fee status
- Update account password

## 📁 Project Structure

## 🔮 Future Enhancements

- 📊 Database integration for persistent data storage
- 🌐 Web-based interface using Flask/Django
- 📱 Mobile application support
- 📧 Email notifications for important updates
- 📈 Advanced analytics and reporting
- 📅 Attendance tracking system
- 📖 Assignment and homework management
- 🔔 Parent portal for student monitoring

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. **Commit your changes**
   ```bash
   git commit -m "Add your descriptive commit message"
   ```
4. **Push to your branch**
   ```bash
   git push origin feature/your-feature-name
   ```
5. **Open a Pull Request**

For major changes, please open an issue first to discuss your proposed modifications.

## 📧 Contact

**Garima Kapoor**

- 📧 Email: [garimakapoor.work@gmail.com](mailto:garimakapoor.work@gmail.com)
- 💼 GitHub: [@garimakapoor1204](https://github.com/garimakapoor1204)

---

<div align="center">
  
**Made with ❤️ for better education management**

If you find this project helpful, please consider giving it a ⭐!

</div>


