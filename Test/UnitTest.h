//
// Created by asrip on 21/11/2024.
//

#ifndef UNITTEST_H
#define UNITTEST_H

#include <iostream>
#include <vector>
#include <functional>
#include <string>

using namespace std;

/**
 *  Classe centrale pour gérer les tests
 *  Macro :
 *   - TEST_CASE(name) : pour définir un test
 *   - ASSERT_TRUE(condition) : pour vérifier une condition
 *   - ASSERT_EQ(expected, actual) : pour vérifier une égalité
 *   - RUN_ALL_TESTS() : pour exécuter tous les tests
 *
 */
class UnitTest {
private:
    // Structure pour stocker un test
    struct Test {
        string name;
        function<void()> func;
    };

    vector<Test> tests;

    // Constructeur privé (singleton)
    UnitTest() = default;
public:
    // Singleton pour gérer l'unique instance
    static UnitTest& getInstance();

    // Méthode pour enregistrer un test
    void registerTest(const string& testName, const function<void()>& testFunc);

    // Méthode pour exécuter tous les tests
    void runTests();
};

// Macros pour simplifier l'écriture des tests

/**
 * Pour définir un test unitaire
 * @param name : nom du test
 */
#define TEST_CASE(name) \
    void name(); \
    static bool _##name##_registered = [](){ \
        UnitTest::getInstance().registerTest(#name, name); \
        return true; \
    }(); \
    void name()

/**
 * Pour vérifier une condition
 * @param condition : condition à vérifier
 */
#define ASSERT_TRUE(condition) \
    if (!(condition)) throw runtime_error("Assertion failed: " #condition)

/**
 * Pour vérifier une égalité
 * @param expected : valeur attendue
 * @param actual : valeur à tester
 */
#define ASSERT_EQ(expected, actual) \
    if ((expected) != (actual)) throw runtime_error("Assertion failed: " #expected " == " #actual)

// Point d'entrée principal pour exécuter les tests
#define RUN_ALL_TESTS() UnitTest::getInstance().runTests()



#endif //UNITTEST_H
