# 🎓 Student Grade Calculator

A **C++ console application** for managing and calculating student academic performance based on homework assignments and examination results.

---

## 📋 About the Application

This application allows educators and students to:

- **Input** student personal data (first name & surname), homework scores, and exam results
- **Calculate** final grades using either the **average** or **median** of homework scores
- **Generate** random homework and exam scores for testing purposes
- **Read** student data from structured text files (`Students.txt`)
- **Display** sorted, nicely formatted result tables

---

## 📐 Grade Calculation Formula

The final grade is calculated based on two components:

| Component         | Weight |
|-------------------|--------|
| Homework (Avg/Med)| **40%** |
| Exam Result       | **60%** |

### Average-based Final Grade

$$\text{Final}_{avg} = 0.4 \times \frac{\sum_{i=1}^{n} HW_i}{n} + 0.6 \times \text{Exam}$$

### Median-based Final Grade

$$\text{Final}_{med} = 0.4 \times \text{median}(HW_1, HW_2, \ldots, HW_n) + 0.6 \times \text{Exam}$$

Where:
- $HW_i$ — score of the *i-th* homework assignment (0–10)
- $n$ — total number of homework assignments
- $\text{Exam}$ — exam result (0–10)
- $\text{median}$ — middle value of sorted homework scores

---

## 🗂️ Project Structure

```
student-grades/
├── README.md           ← Project documentation
├── main.cpp            ← Main program entry point
├── Person.h            ← Person class declaration
├── Person.cpp          ← Person class implementation
├── Students.txt        ← Sample student data file
└── Makefile            ← Build configuration
```

---

## ⚙️ Build & Run

```bash
# Build the project
make

# Run the application
./student_grades
```

Or compile manually:

```bash
g++ -std=c++17 -Wall -o student_grades main.cpp Person.cpp
```

---

## 📄 Input File Format (`Students.txt`)

```
Name        Surname    HW1   HW2   HW3   HW4   HW5   Exam
Name1       Surname1     8     9    10     6    10      9
Name2       Surname2     7    10     8     5     4      6
```

---

## 🖥️ Sample Output

```
Name      Surname        Final (Avg.) | Final (Med.)
----------------------------------------------------
Jonas     Jonaitis               8.20 |         8.40
Petras    Petraitis              7.16 |         7.00
...
```

---

## 🔧 Features

- ✅ **Rule of Three** — Copy constructor, assignment operator, destructor
- ✅ **Overloaded I/O** — Custom `cin`/`cout` operators for `Person`
- ✅ **Dynamic homework count** — Uses `std::vector<int>` for flexible HW entries
- ✅ **Dual calculation** — Average and Median side-by-side
- ✅ **Random generation** — Auto-fill scores for quick testing
- ✅ **File I/O** — Read structured data from `Students.txt`
- ✅ **Sorted output** — Students listed alphabetically by surname

---

## 📌 Version History

| Version | Description |
|---------|-------------|
| `v0.1`  | Initial implementation with all core features |

---

## 👨‍💻 Author

Student Grades Project — University C++ Programming Assignment
