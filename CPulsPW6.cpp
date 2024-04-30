#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

const int MAX_SUBJECTS = 10;

class Student {
private:
    string group_name;
    string* subjects;
    int subjects_count = 0;
    int completed_assignments = 0;
    int debts_count = 0;

public:
    Student() : group_name(""), subjects(new string[MAX_SUBJECTS]), subjects_count(0), completed_assignments(0), debts_count(0) {}

    explicit Student(const string& group) : group_name(group), subjects(new string[MAX_SUBJECTS]), subjects_count(0), completed_assignments(0), debts_count(0) {}

    ~Student() {
        delete[] subjects;
    }

    string* getSubjects() const {
        return subjects;
    }

    int getSubjectsCount() const {
        return subjects_count;
    }

    void addSubject(const string& subject) {
        if (subjects_count < MAX_SUBJECTS) {
            subjects[subjects_count++] = subject;
        }
        else {
            cout << "Достигнуто максимальное количество дисциплин!" << endl;
        }
    }

    void submitAssignment() {
        ++completed_assignments;
    }

    void failAssignment() {
        ++debts_count;
    }

    void forgiveDebt() {
        if (debts_count > 0) {
            --debts_count;
        }
    }

    void undoSubmission() {
        if (completed_assignments > 0) {
            --completed_assignments;
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
    string groups[10];

public:
    Teacher() : subject("") {}

    explicit Teacher(const string& sub) : subject(sub) {}

    void addGroup(const string& group) {
        for (int i = 0; i < 10; ++i) {
            if (groups[i].empty()) {
                groups[i] = group;
                break;
            }
        }
    }

    string* getGroups() {
        return groups;
    }

    string getSubject() const {
        return subject;
    }
};

class Group {
private:
    string name;
    Student students[50];
    Teacher teachers[5];

public:
    Group() : name("") {}
    explicit Group(const string& group_name) : name(group_name) {}


    Student* getStudents() {
        return students;
    }

    void addStudent(const Student& student) {
        for (int i = 0; i < 50; ++i) {
            if (students[i].getGroupName().empty()) {
                students[i] = student;
                break;
            }
        }
    }

    void addTeacher(const Teacher& teacher) {
        for (int i = 0; i < 5; ++i) {
            if (teachers[i].getSubject().empty()) {
                teachers[i] = teacher;
                break;
            }
        }
    }

    string getName() const {
        return name;
    }
};

class School {
private:
    Teacher teachers[10];

public:
    Group groups[10];

    School() {}

    void addGroup(const Group& group) {
        for (int i = 0; i < 10; ++i) {
            if (groups[i].getName().empty()) {
                groups[i] = group;
                break;
            }
        }
    }

    void addTeacher(const Teacher& teacher) {
        for (int i = 0; i < 10; ++i) {
            if (teachers[i].getSubject().empty()) {
                teachers[i] = teacher;
                break;
            }
        }
    }

    void assignWork(Student& student) {
        student.submitAssignment();
    }

    void addDebt(Student& student) {
        student.failAssignment();
    }

    void showStudentsInGroup(Group& group) {
        cout << "Количество студентов в группе " << group.getName() << ": ";
        int count = 0;
        Student* students = group.getStudents();
        for (int i = 0; i < 50; ++i) {
            if (!students[i].getGroupName().empty()) {
                ++count;
            }
            else {
                break;
            }
        }
        cout << count << endl;
    }

    void showStudentInfo(const Student& student) {
        cout << "Информация о студенте:" << endl;
        cout << "Название группы: " << student.getGroupName() << endl;
        cout << "Дисциплины: ";
        string* subjects = student.getSubjects();
        for (int i = 0; i < student.getSubjectsCount(); ++i) {
            cout << subjects[i] << ", ";
        }
        cout << endl;
        cout << "Количество выполненных работ: " << student.getCompletedAssignments() << endl;
        cout << "Количество долгов: " << student.getDebtsCount() << endl;
    }

    void showAllGroups() const {
        cout << "Все группы:" << endl;
        for (int i = 0; i < 10; ++i) {
            if (!groups[i].getName().empty()) {
                cout << groups[i].getName() << endl;
            }
        }
    }

    bool groupExists(const string& group_name) const {
        for (int i = 0; i < 10; ++i) {
            if (groups[i].getName() == group_name) {
                return true;
            }
        }
        return false;
    }

    bool subjectExists(const string& subject) {
        for (int i = 0; i < 10; ++i) {
            Student* students = groups[i].getStudents();
            for (int j = 0; j < 50; ++j) {
                if (!students[j].getGroupName().empty()) {
                    string* subjects = students[j].getSubjects();
                    for (int k = 0; k < students[j].getSubjectsCount(); ++k) {
                        if (subjects[k] == subject) {
                            return true;
                        }
                    }
                }
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

    cout << "\n>>> ДОБРО ПОЖАЛОВАТЬ В ШАРАГУ <<<\n";
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

            for (int i = 0; i < 10; ++i) {
                Student* students = school.groups[i].getStudents();
                for (int j = 0; j < 50; ++j) {
                    if (!students[j].getGroupName().empty()) {
                        students[j].addSubject(new_subject);
                    }
                    else {
                        break;
                    }
                }
            }

            cout << "\nДисциплина успешно добавлена!\n" << endl;

            break;
        }
        case '9':
            cout << "\nГруппе был прощен один долг!";
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
