#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

class Student {
private:
    string group_name;
    vector<string> subjects;
    int completed_assignments;
    int debts_count;
public:
    Student(const string& group) : group_name(group), completed_assignments(0), debts_count(0) {}

    vector<string> getSubjects() const {
        return subjects;
    }

    void addSubject(const string& subject) {
        if (subjects.end() == find(subjects.begin(), subjects.end(), subject))
            subjects.push_back(subject);
        else
            cout << "Дисциплина \"" << subject << "\" уже есть у студента" << endl;
    }

    void submitAssignment() {
        completed_assignments++;
    }

    void failAssignment() {
        debts_count++;
    }

    void forgiveDebt() {
        if (debts_count > 0) {
            debts_count--;
        }
        else {
            debts_count = debts_count;
        }
    }

    void undoSubmission() {
        if (completed_assignments > 0) {
            completed_assignments--;
        }
        else {
            completed_assignments = completed_assignments;
        }
    }

    int getDebtsCount() const {
        return debts_count;
    }

    string getGroupName() const {
        return group_name;
    }

    int getCompletedAssignments() const {
        return completed_assignments;
    }
};

class Teacher {
private:
    string subject;
    vector<string> groups;
public:
    Teacher(const string& subject) : subject(subject) {}

    void addGroup(const string& group) {
        groups.push_back(group);
    }

    vector<string> getGroups() const {
        return groups;
    }

    string getSubject() const {
        return subject;
    }
};

class Group {
private:
    string name;
    vector<Student> students;
    vector<Teacher> teachers;
public:
    Group(const string& name) : name(name) {}

    vector<Student>& getStudents() {
        return students;
    }

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void addTeacher(const Teacher& teacher) {
        teachers.push_back(teacher);
    }

    string getName() const {
        return name;
    }
};

class School {
private:
    vector<Teacher> teachers;
public:
    vector<Group> groups;

    void addGroup(const Group& group) {
        groups.push_back(group);
    }

    void addTeacher(const Teacher& teacher) {
        teachers.push_back(teacher);
    }

    void assignWork(Student& student) {
        student.submitAssignment();
    }

    void addDebt(Student& student) {
        student.failAssignment();
    }

    void showStudentsInGroup(Group& group) {
        cout << "Количество студентов в группе " << group.getName() << ": " << group.getStudents().size() << endl;
    }

    void showStudentInfo(const Student& student) {
        cout << "Информация о студенте:" << endl;
        cout << "Название группы: " << student.getGroupName() << endl;
        cout << "Дисциплины: ";
        for (const auto& subject : student.getSubjects()) {
            cout << subject << ", ";
        }
        cout << endl;
        cout << "Количество выполненных работ: " << student.getCompletedAssignments() << endl;
        cout << "Количество долгов: " << student.getDebtsCount() << endl;
    }

    void showAllStudentsInfo() {
        for (auto& group : groups) {
            for (auto& student : group.getStudents()) {
                showStudentInfo(student);
                cout << endl;
            }
        }
    }

    void showAllGroups() const {
        cout << "Все группы:" << endl;
        for (const auto& group : groups) {
            cout << group.getName() << endl;
        }
    }

    bool groupExists(const string& group_name) const {
        for (const auto& group : groups) {
            if (group.getName() == group_name) {
                return true;
            }
        }
        return false;
    }

    bool subjectExists(const string& subject) {
        for (auto& group : groups) {
            for (auto& student : group.getStudents()) {
                if (find(student.getSubjects().begin(), student.getSubjects().end(), subject) != student.getSubjects().end())
                    return true;
            }
        }
        return false;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "");

    School school;

    cout << "\n>>> ДОБРО ПОЖАЛОВАТЬ В ШКОЛУ <<<\n";
    string group_name;
    cout << "\nВведите название группы: ";
    cin >> group_name;

    Group group(group_name);

    Student student1(group_name);

    string subject;
    cout << "Введите дисциплину для группы: ";
    cin >> subject;
    student1.addSubject(subject);

    Teacher teacher1(subject);

    string group_for_teacher;

    do {
        cout << "Введите название группы для преподователя: ";

        cin >> group_for_teacher;

        if (group_for_teacher != group_name) {
            cout << "Группы с таким названием не существует! Пожайлуста, попробуйте ещё раз! \n";
        }
    } while (group_for_teacher != group_name);

    teacher1.addGroup(group_for_teacher);
    group.addStudent(student1);
    group.addTeacher(teacher1);
    school.addGroup(group);
    school.addTeacher(teacher1);
    char choice;

    do {
        cout << "\nВыберите действие : \n 1 - Назначить работу группе\n 2 - Добавить долг группе\n 3 - Посмотреть количество студентов в группе\n 4 - Показать информацию о группе\n 5 - Добавить студента в группу\n 6 - Добавить новую группу\n 7 - Показать все группы\n 8 - Добавить новую дисциплину\n 9 - Простить долги группе\n s - Отметить практическую работу выполненной\n q - Выйти\n";
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "\nГруппе была назначена новая практическая работа\n";
            school.assignWork(student1);
            break;
        case '2':
            cout << "\nГруппе был добавлен новый долг\n";
            school.addDebt(student1);
            break;
        case '3':
            school.showStudentsInGroup(group);
            break;
        case '4':
            school.showStudentInfo(student1);
            break;
        case '5':
        {
            string new_student_group;
            cout << "\nВведите название группы для нового студента: ";
            cin >> new_student_group;

            if (!school.groupExists(new_student_group)) {
                cout << "\nГруппа с таким названием не существует!\n" << endl;
            }
            else {
                Student new_student(new_student_group);
                group.addStudent(new_student);
            }
            break;
        }
        case '6':
        {
            string new_group_name;
            cout << "\nВведите название новой группы: ";
            cin >> new_group_name;

            if (school.groupExists(new_group_name)) {
                cout << "\nГруппа с таким названием уже существует!\n" << endl;
            }
            else {
                Group new_group(new_group_name);
                school.addGroup(new_group);
            }
            break;
        }
        case '7':
            school.showAllGroups();
            break;
        case '8':
        {
            string new_subject;
            cout << "\nВведите название новой дисциплины: ";
            cin >> new_subject;

            student1.addSubject(new_subject);

            for (Student& student : group.getStudents()) {
                student.addSubject(new_subject);
            }

            cout << "\nДисциплина успешно добавлена!\n" << endl;

            break;
        }
        case '9':
            cout << "\nГруппе был прощен один долг, Вам кинули респект!";
            student1.forgiveDebt();
            break;
        case 's':
            student1.undoSubmission();
            cout << "\nСтуденты выполнили практическую работу!\n";
            break;
        case 'q':
            cout << "Вы вышли из программы!";
            break;
        default:
            cout << "\nТакого в меню нет!\n" << endl;
            break;
        }

    } while (choice != 'q');

    return 0;
}