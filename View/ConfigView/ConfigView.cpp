#include "ConfigView.h"

void ConfigView::configView() {
    sf::RenderWindow configWindow(sf::VideoMode(configWindowWidth, configWindowHeight), "Configuration de la grille");

    // Création des "sliders" qui permettront la sélection de la taille de la grille et des cellules
    sf::RectangleShape gridSizeSlider(sf::Vector2f(200, 10));
    gridSizeSlider.setPosition(100, 50);
    gridSizeSlider.setFillColor(sf::Color::White);

    sf::CircleShape gridSizeHandle(10);
    gridSizeHandle.setFillColor(sf::Color::Red);

    sf::RectangleShape cellSizeSlider(sf::Vector2f(200, 10));
    cellSizeSlider.setPosition(100, 100);
    cellSizeSlider.setFillColor(sf::Color::White);

    sf::CircleShape cellSizeHandle(10);
    cellSizeHandle.setFillColor(sf::Color::Red);

    // Chargement de la police
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Erreur: Police 'arial.ttf' non trouvée !" << std::endl;
        return;
    }

    bool draggingGridSize = false;
    bool draggingCellSize = false;

    while (configWindow.isOpen()) {
        sf::Event event;
        while (configWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                configWindow.close();
            }

            // Gère les intéraction de l'utilisateur avec les sliders
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(configWindow);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (gridSizeHandle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        draggingGridSize = true;
                    } else if (cellSizeHandle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        draggingCellSize = true;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    draggingGridSize = false;
                    draggingCellSize = false;
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(configWindow);
                if (draggingGridSize) {
                    int x = std::clamp(mousePos.x, 100, 300);
                    gridSizeHandle.setPosition(x - 10, gridSizeSlider.getPosition().y - 5);
                    gridSize = 4 + ((x - 100) * 28) / 200; // Intervalle entre 4-32
                } else if (draggingCellSize) {
                    int x = std::clamp(mousePos.x, 100, 300);
                    cellSizeHandle.setPosition(x - 10, cellSizeSlider.getPosition().y - 5);
                    cellSize = 10 + ((x - 100) * 40) / 200; // Intervalle entre 10-50
                }
            }
        }

        // Mise à jour de la taille de/des grille/cellules
        gridSizeHandle.setPosition(100 + (gridSize - 4) * 200 / 28 - 10, gridSizeSlider.getPosition().y - 5);
        cellSizeHandle.setPosition(100 + (cellSize - 10) * 200 / 40 - 10, cellSizeSlider.getPosition().y - 5);

        // Affiche le tout sur la fenêtre
        configWindow.clear(sf::Color::Black);
        sf::Text gridSizeText, cellSizeText, confirmText;
        drawSlider(configWindow, gridSizeSlider, gridSizeHandle, gridSizeText, gridSize, 4, 32, font, {100, 20});
        drawSlider(configWindow, cellSizeSlider, cellSizeHandle, cellSizeText, cellSize, 10, 50, font, {100, 70});

        confirmText.setFont(font);
        confirmText.setString("Appuyer 'Entrée' pour continuer ...");
        confirmText.setCharacterSize(20);
        confirmText.setPosition(80, 150);
        configWindow.draw(confirmText);

        configWindow.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            configWindow.close();
            drawView();
        }
    }
}

void ConfigView::drawView() {
    int windowSize = cellSize * gridSize;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Editeur de grille");
    window.setFramerateLimit(60);

    std::vector<std::vector<int>> grid(gridSize, std::vector<int>(gridSize, 0));
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
                if (mousePos.x >= 0 && mousePos.y >= 0 && mousePos.x < windowSize && mousePos.y < windowSize) {
                    int cellX = mousePos.x / cellSize;
                    int cellY = mousePos.y / cellSize;

                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            grid[cellY][cellX] = 1;
                        } else if (event.mouseButton.button == sf::Mouse::Right) {
                            grid[cellY][cellX] = 0;
                        }
                    }

                    if (event.key.code == sf::Keyboard::Enter) {
                    // Sauvegarde la grille
                    std::ofstream outFile(this->path);
                        if (outFile.is_open()) {
                            for (const auto& row : grid) {
                                for (int cell : row) {
                                    outFile << cell;
                                }
                                outFile << "\n";
                            }
                            std::cout << "Grille sauvegardée dans " << this->path << std::endl;
                        }
                    }
                    // Gestion des divers patern de base
                    if (event.key.code == sf::Keyboard::G) { // Glider
                    std::vector<std::vector<int>> glider = {
                        {1, 1, 1},
                        {0, 0, 1},
                        {0, 1, 0}
                    };
                    for (int y = 0; y < glider.size(); ++y) {
                        for (int x = 0; x < glider[y].size(); ++x) {
                            if (cellY + y < gridSize && cellX + x < gridSize)
                                grid[cellY + y][cellX + x] = glider[y][x];
                        }
                    }
                    } else if (event.key.code == sf::Keyboard::P) { // Block
                        std::vector<std::vector<int>> block = {
                            {1, 1},
                            {1, 1}
                        };
                        for (int y = 0; y < block.size(); ++y) {
                            for (int x = 0; x < block[y].size(); ++x) {
                                if (cellY + y < gridSize && cellX + x < gridSize)
                                    grid[cellY + y][cellX + x] = block[y][x];
                            }
                        }
                    } else if (event.key.code == sf::Keyboard::R) { // Ruche
                        std::vector<std::vector<int>> ruche = {
                            {0, 1, 0},
                            {1, 0, 1},
                            {1, 0, 1},
                            {0, 1, 0}
                        };
                        for (int y = 0; y < ruche.size(); ++y) {
                            for (int x = 0; x < ruche[y].size(); ++x) {
                                if (cellY + y < gridSize && cellX + x < gridSize)
                                    grid[cellY + y][cellX + x] = ruche[y][x];
                            }
                        }
                    } else if (event.key.code == sf::Keyboard::B) { // Bar
                        std::vector<std::vector<int>> bar = {  
                            {1, 1, 1},
                            

                        };
                        for (int y = 0; y < bar.size(); ++y) {
                            for (int x = 0; x < bar[y].size(); ++x) {
                                if (cellY + y < gridSize && cellX + x < gridSize)
                                    grid[cellY + y][cellX + x] = bar[y][x];
                            }
                        }
                    }

                    else if (event.key.code == sf::Keyboard::C) { // CESI easter egg
                        std::vector<std::vector<int>> cesi = {  
                            {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
                            {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
                            {1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
                            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
                            {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
                        };
                        for (int y = 0; y < cesi.size(); ++y) {
                            for (int x = 0; x < cesi[y].size(); ++x) {
                                if (cellY + y < gridSize && cellX + x < gridSize)
                                    grid[cellY + y][cellX + x] = cesi[y][x];
                            }
                        }
                    }

                    else if (event.key.code == sf::Keyboard::Subtract) { // Supprimer les éléments de la grille
                        for (int y = 0; y < gridSize; ++y) {
                            for (int x = 0; x < gridSize; ++x) {
                                grid[y][x] = 0;
                            }
                        }
                    }

                    else if (event.key.code == sf::Keyboard::BackSpace) {
                        window.close();
                        configView();
                    }
                }
            }
        }

        // Afficher la grille
        window.clear(sf::Color::Black);
        for (int y = 0; y < gridSize; ++y) {
            for (int x = 0; x < gridSize; ++x) {
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(grid[y][x] == 1 ? sf::Color::White : sf::Color::Transparent);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Green);
                window.draw(cell);
            }
        }
        if (mousePos.x >= 0 && mousePos.x < windowSize && mousePos.y >= 0 && mousePos.y < windowSize) {
            int hoverX = mousePos.x / cellSize;
            int hoverY = mousePos.y / cellSize;

            cell.setPosition(hoverX * cellSize, hoverY * cellSize);
            cell.setFillColor(sf::Color::Yellow);
            window.draw(cell);
        }

        window.display();
    }
}

void ConfigView::drawSlider(sf::RenderWindow& window, sf::RectangleShape& slider, sf::CircleShape& handle, sf::Text& label, int value, int min, int max, sf::Font& font, const sf::Vector2f& position) {
    label.setFont(font);
    label.setString(std::to_string(value));
    label.setCharacterSize(20);
    label.setPosition(position);

    window.draw(slider);
    window.draw(handle);
    window.draw(label);
}
