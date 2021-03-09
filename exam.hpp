//
// Created by Roman on 26.01.2020.
//

#ifndef EXAM_EXAM_HPP
#define EXAM_EXAM_HPP

#include <vector>
#include <numeric>

class Student{
    std::list<int> _marks;
public:
    Student() = default;
    Student(std::list<int> m){_marks = m;};


    void addMark(int mark){
        _marks.push_back(mark);
    };


    void average(){
        int avg = std::accumulate(_marks.begin(),_marks.end(),0);
        std::cout<<avg<<std::endl;
    };
};
class IExam{
public:
    virtual ~IExam() = default;
    virtual void asses(Student&) = 0;

};

class WrittenExam : public IExam{
public:
    WrittenExam() = default;
    void asses(Student& student) override {
        student.addMark(5);
    }

    ~WrittenExam() override = default;

};


class Course {
    std::unique_ptr<IExam> _exam;
    std::vector<Student*> _students;
public:
    Course(std::vector<Student*> students, std::unique_ptr<IExam> exam) : _students(students) ,_exam(std::move(exam)){};

    void carryOutExam() {
        for (auto &_student : _students) {
            _exam->asses(*_student);
        };
    };

};
class University {
    std::list<Course> _courses;
    std::vector<Student> _students;

    University() {
        _students.push_back(Student());
        std::vector<Student*> students_course1;
        for (auto& _st : _students){
            students_course1.push_back(&_st);
        }

        _courses.push_back(Course(students_course1 , std::make_unique<WrittenExam>()));
    };

    void recapitulateSemester() {
        for (auto &_course : _courses) {
            _course.carryOutExam();
        };
        for (auto &_student : _students) {
            _student.average();
        };
    }
};


#endif //EXAM_EXAM_HPP
