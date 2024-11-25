//
// Created by asrip on 21/11/2024.
//

#include "UnitTest.h"

UnitTest& UnitTest::getInstance() {
    static UnitTest instance;
    return instance;
}

void UnitTest::registerTest(const std::string& testName, const std::function<void()>& testFunc) {
    tests.push_back({testName, testFunc});
}

void UnitTest::runTests() {
    int passed = 0;
    const int total = tests.size();

    cout << "Running " << total << " test(s)...\n";

    for (const auto& test : tests) {
        try {
            test.func();
            cout << "[PASS] " << test.name << "\n";
            passed++;
        } catch (const exception& e) {
            cout << "[FAIL] " << test.name << ": " << e.what() << "\n";
        } catch (...) {
            cout << "[FAIL] " << test.name << ": Unknown error\n";
        }
    }

    cout << "\nSummary: " << passed << "/" << total << " tests passed.\n";
}