#include "Person.h"

#include <algorithm>   // sort, copy
#include <numeric>     // accumulate
#include <stdexcept>
#include <iomanip>
#include <cstdlib>     // rand
#include <ctime>

// ─────────────────────────────────────────────────────────────
//  Constructors / Rule-of-Three
// ─────────────────────────────────────────────────────────────

Person::Person()
    : firstName_(""), surname_(""), exam_(0) {}

Person::Person(const std::string& firstName,
               const std::string& surname,
               const std::vector<int>& homework,
               int exam)
    : firstName_(firstName), surname_(surname),
      homework_(homework), exam_(exam) {}

// Copy constructor
Person::Person(const Person& other)
    : firstName_(other.firstName_),
      surname_(other.surname_),
      homework_(other.homework_),
      exam_(other.exam_) {}

// Copy-assignment operator
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        firstName_ = other.firstName_;
        surname_   = other.surname_;
        homework_  = other.homework_;
        exam_      = other.exam_;
    }
    return *this;
}

// Destructor
Person::~Person() {
    // std::vector cleans itself up; nothing manual required
}

// ─────────────────────────────────────────────────────────────
//  Private helpers
// ─────────────────────────────────────────────────────────────

double Person::hwAverage() const {
    if (homework_.empty()) return 0.0;
    double sum = std::accumulate(homework_.begin(), homework_.end(), 0.0);
    return sum / static_cast<double>(homework_.size());
}

double Person::hwMedian() const {
    if (homework_.empty()) return 0.0;
    std::vector<int> tmp(homework_);
    std::sort(tmp.begin(), tmp.end());
    size_t n = tmp.size();
    if (n % 2 == 1)
        return static_cast<double>(tmp[n / 2]);
    else
        return (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
}

// ─────────────────────────────────────────────────────────────
//  Public grade calculation
// ─────────────────────────────────────────────────────────────

double Person::calcAverage() const {
    return 0.4 * hwAverage() + 0.6 * static_cast<double>(exam_);
}

double Person::calcMedian() const {
    return 0.4 * hwMedian() + 0.6 * static_cast<double>(exam_);
}

// ─────────────────────────────────────────────────────────────
//  Overloaded >> (interactive input)
// ─────────────────────────────────────────────────────────────

std::istream& operator>>(std::istream& in, Person& p) {
    std::cout << "  First name : ";
    in >> p.firstName_;
    std::cout << "  Surname    : ";
    in >> p.surname_;

    p.homework_.clear();
    std::cout << "  Enter homework scores one by one.\n"
              << "  Type a negative number or 'done' when finished.\n";

    int score;
    int idx = 1;
    while (true) {
        std::cout << "  HW" << idx << " score (0-10, or -1 to stop): ";
        if (!(in >> score)) {
            // Non-integer token: clear error and skip it
            in.clear();
            std::string dummy;
            in >> dummy;
            break;
        }
        if (score < 0) break;   // valid negative sentinel – stop without consuming more
        p.homework_.push_back(score);
        ++idx;
    }

    std::cout << "  Exam score (0-10): ";
    in >> p.exam_;
    return in;
}

// ─────────────────────────────────────────────────────────────
//  Overloaded << (formatted output, single student)
// ─────────────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << std::left
        << std::setw(14) << p.firstName_
        << std::setw(14) << p.surname_
        << "Avg: " << std::fixed << std::setprecision(2) << p.calcAverage()
        << "  Med: " << p.calcMedian();
    return out;
}

// ─────────────────────────────────────────────────────────────
//  Random score generator
// ─────────────────────────────────────────────────────────────

void Person::randomize(int numHomework) {
    homework_.clear();
    for (int i = 0; i < numHomework; ++i)
        homework_.push_back(rand() % 11);   // 0–10
    exam_ = rand() % 11;
}
