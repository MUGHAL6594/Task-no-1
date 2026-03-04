// ============================================================
//  main.cpp  –  Student Grade Calculator
//  Supports: manual input, random generation, file reading
// ============================================================

#include "Person.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

// ─────────────────────────────────────────────────────────────
//  Helpers
// ─────────────────────────────────────────────────────────────

static void printSeparator(int width = 54) {
    std::cout << std::string(width, '-') << '\n';
}

// Print table header for Average-only output (original format)
static void printAverageHeader() {
    std::cout << '\n'
              << std::left
              << std::setw(14) << "Name"
              << std::setw(14) << "Surname"
              << std::right << std::setw(20) << "Final_Point(Aver.)"
              << '\n';
    printSeparator(48);
}

// Print table header for Avg + Med output
static void printDualHeader() {
    std::cout << '\n'
              << std::left
              << std::setw(14) << "Name"
              << std::setw(16) << "Surname"
              << std::right
              << std::setw(14) << "Final (Avg.)"
              << " | "
              << std::setw(13) << "Final (Med.)"
              << '\n';
    printSeparator(60);
}

// Sort comparator: alphabetical by surname, then first name
static bool bySurname(const Person& a, const Person& b) {
    if (a.getSurname() != b.getSurname())
        return a.getSurname() < b.getSurname();
    return a.getFirstName() < b.getFirstName();
}

// ─────────────────────────────────────────────────────────────
//  Mode 1 – Manual input, average output
// ─────────────────────────────────────────────────────────────

static void modeManualAverage() {
    int n;
    std::cout << "\nHow many students? ";
    std::cin >> n;

    std::vector<Person> students(n);
    for (int i = 0; i < n; ++i) {
        std::cout << "\n--- Student " << (i + 1) << " ---\n";
        std::cin >> students[i];
    }

    std::sort(students.begin(), students.end(), bySurname);

    printAverageHeader();
    for (const auto& s : students) {
        std::cout << std::left
                  << std::setw(14) << s.getFirstName()
                  << std::setw(14) << s.getSurname()
                  << std::right
                  << std::setw(20) << std::fixed << std::setprecision(2)
                  << s.calcAverage()
                  << '\n';
    }
}

// ─────────────────────────────────────────────────────────────
//  Mode 2 – Manual input, user chooses Avg or Med
// ─────────────────────────────────────────────────────────────

static void modeManualChoice() {
    int n;
    std::cout << "\nHow many students? ";
    std::cin >> n;

    std::vector<Person> students(n);
    for (int i = 0; i < n; ++i) {
        std::cout << "\n--- Student " << (i + 1) << " ---\n";
        std::cin >> students[i];
    }

    char choice;
    std::cout << "\nCalculate final grade by [A]verage or [M]edian? ";
    std::cin >> choice;
    bool useAvg = (choice == 'A' || choice == 'a');

    std::sort(students.begin(), students.end(), bySurname);

    std::string method = useAvg ? "Average" : "Median";
    std::cout << '\n'
              << std::left
              << std::setw(14) << "Name"
              << std::setw(14) << "Surname"
              << std::right
              << std::setw(16) << ("Final (" + method + ")")
              << '\n';
    printSeparator(44);

    for (const auto& s : students) {
        double grade = useAvg ? s.calcAverage() : s.calcMedian();
        std::cout << std::left
                  << std::setw(14) << s.getFirstName()
                  << std::setw(14) << s.getSurname()
                  << std::right
                  << std::setw(16) << std::fixed << std::setprecision(2)
                  << grade << '\n';
    }
}

// ─────────────────────────────────────────────────────────────
//  Mode 3 – Random generation
// ─────────────────────────────────────────────────────────────

static void modeRandom() {
    int n, hw;
    std::cout << "\nHow many students? ";
    std::cin >> n;
    std::cout << "How many homework assignments per student? ";
    std::cin >> hw;

    // Seed once
    static bool seeded = false;
    if (!seeded) { std::srand(static_cast<unsigned>(std::time(nullptr))); seeded = true; }

    // Provide names for random students
    const std::vector<std::string> FIRST = {"Jonas","Petras","Antanas","Juozas","Mindaugas",
                                             "Laura","Inga","Ruta","Daina","Egle"};
    const std::vector<std::string> LAST  = {"Jonaitis","Petraitis","Kazlauskas","Jankauskas",
                                             "Paulauskas","Stankeviciene","Zdaneviciute",
                                             "Bernotas","Urbonas","Lukosius"};

    std::vector<Person> students;
    for (int i = 0; i < n; ++i) {
        std::vector<int> homework;
        for (int j = 0; j < hw; ++j)
            homework.push_back(rand() % 11);
        int exam = rand() % 11;
        std::string fn = FIRST[rand() % FIRST.size()];
        std::string sn = LAST [rand() % LAST.size() ];
        students.emplace_back(fn, sn, homework, exam);
    }

    std::sort(students.begin(), students.end(), bySurname);

    printDualHeader();
    for (const auto& s : students) {
        std::cout << std::left
                  << std::setw(14) << s.getFirstName()
                  << std::setw(16) << s.getSurname()
                  << std::right
                  << std::setw(14) << std::fixed << std::setprecision(2) << s.calcAverage()
                  << " | "
                  << std::setw(13) << std::fixed << std::setprecision(2) << s.calcMedian()
                  << '\n';
    }
}

// ─────────────────────────────────────────────────────────────
//  Mode 4 – Read from Students.txt
// ─────────────────────────────────────────────────────────────

static void modeFromFile() {
    std::string filename;
    std::cout << "\nFile name [Students.txt]: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, filename);
    if (filename.empty()) filename = "Students.txt";

    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "  [ERROR] Cannot open file: " << filename << '\n';
        return;
    }

    std::vector<Person> students;
    std::string line;

    // Skip header line
    std::getline(fin, line);

    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string fn, sn;
        iss >> fn >> sn;

        std::vector<int> homework;
        int val;
        // Read until last token (exam is the last integer on the line)
        std::vector<int> all;
        while (iss >> val) all.push_back(val);

        if (all.empty()) continue;

        // Last value is the exam; the rest are homework
        int exam = all.back();
        all.pop_back();
        homework = all;

        students.emplace_back(fn, sn, homework, exam);
    }

    if (students.empty()) {
        std::cout << "  No data found in " << filename << '\n';
        return;
    }

    std::sort(students.begin(), students.end(), bySurname);

    printDualHeader();
    for (const auto& s : students) {
        std::cout << std::left
                  << std::setw(14) << s.getFirstName()
                  << std::setw(16) << s.getSurname()
                  << std::right
                  << std::setw(14) << std::fixed << std::setprecision(2) << s.calcAverage()
                  << " | "
                  << std::setw(13) << std::fixed << std::setprecision(2) << s.calcMedian()
                  << '\n';
    }
}

// ─────────────────────────────────────────────────────────────
//  Main menu
// ─────────────────────────────────────────────────────────────

int main() {
    std::cout << "========================================\n"
              << "   Student Grade Calculator  v0.1\n"
              << "========================================\n";

    while (true) {
        std::cout << "\n  [1] Manual input  – show Average\n"
                  << "  [2] Manual input  – choose Avg or Med\n"
                  << "  [3] Random data   – show Avg & Med\n"
                  << "  [4] Read file     – show Avg & Med\n"
                  << "  [0] Exit\n"
                  << "\n  Choice: ";

        int choice;
        if (!(std::cin >> choice)) break;

        switch (choice) {
            case 1: modeManualAverage(); break;
            case 2: modeManualChoice();  break;
            case 3: modeRandom();        break;
            case 4: modeFromFile();      break;
            case 0:
                std::cout << "\nGoodbye!\n";
                return 0;
            default:
                std::cout << "  Invalid option. Try again.\n";
        }
    }

    return 0;
}
