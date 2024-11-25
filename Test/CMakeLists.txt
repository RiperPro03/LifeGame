# Ajouter un exécutable pour les tests unitaires
add_executable(UnitTests
        TestMain.cpp
        ModelTest/TestCell.cpp
        ModelTest/TestGrid.cpp
        ModelTest/TestGame.cpp
        ../Model/Cell/Cell.h
        ../Model/Cell/Cell.cpp
        ../Model/Grid/Grid.h
        ../Model/Grid/Grid.cpp
        ../Model/Game/Game.h
        ../Model/Game/Game.cpp
        UnitTest.h
        UnitTest.cpp
)

# Inclure les répertoires nécessaires pour accéder aux fichiers sources principaux et aux tests
target_include_directories(UnitTests PRIVATE
        ../../Model
        ../../Controller
        ../../View
        .
)

# Lier les bibliothèques nécessaires (par exemple, SFML si requis par les tests)
target_link_libraries(UnitTests PRIVATE sfml-graphics sfml-window sfml-system)

# Ajouter une option pour afficher les détails de la compilation des tests
message(STATUS "Unit tests have been configured.")