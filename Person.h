#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <iostream>

// ============================================================
//  Person – stores one student's data and computes the grade
// ============================================================
class Person {
public:
    // ── Constructors / Rule-of-Three ──────────────────────
    Person();                                      // default constructor
    Person(const std::string& firstName,
           const std::string& surname,
           const std::vector<int>& homework,
           int exam);                              // parameterised constructor
    Person(const Person& other);                   // copy constructor
    Person& operator=(const Person& other);        // copy-assignment operator
    ~Person();                                     // destructor

    // ── Getters ───────────────────────────────────────────
    std::string getFirstName()  const { return firstName_; }
    std::string getSurname()    const { return surname_;   }
    int         getExam()       const { return exam_;      }
    const std::vector<int>& getHomework() const { return homework_; }

    // ── Grade computation ─────────────────────────────────
    double calcAverage()  const;   // homework average  * 0.4 + exam * 0.6
    double calcMedian()   const;   // homework median   * 0.4 + exam * 0.6

    // ── I/O operator overloads ────────────────────────────
    friend std::istream& operator>>(std::istream& in,  Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

    // ── Random data generator ─────────────────────────────
    void randomize(int numHomework = 5);

private:
    std::string       firstName_;
    std::string       surname_;
    std::vector<int>  homework_;   // dynamic: user decides when to stop
    int               exam_;

    // ── Helpers ───────────────────────────────────────────
    double hwAverage() const;
    double hwMedian()  const;
};

#endif // PERSON_H

// Version marker: v0.1 – median/choice + random generation added
