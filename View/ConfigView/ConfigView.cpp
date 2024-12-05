#include "ConfigView.h"

void ConfigView::configView() {
    sf::RenderWindow configWindow(sf::VideoMode(configWindowWidth, configWindowHeight), "Configuration de la grille");

    // Création de nos 'sliders'
    sf::RectangleShape gridSizeSlider(sf::Vector2f(200, 10));
    gridSizeSlider.setPosition(100, 50);
    gridSizeSlider.setFillColor(sf::Color::White);

    sf::CircleShape gridSizeHandle(10);
    gridSizeHandle.setFillColor(sf::Color::Red);
    gridSizeHandle.setPosition(gridSizeSlider.getPosition().x + (gridSize - minGridSize) * 200 / (maxGridSize - minGridSize) - 10, gridSizeSlider.getPosition().y - 5);

    sf::RectangleShape cellSizeSlider(sf::Vector2f(200, 10));
    cellSizeSlider.setPosition(100, 120);
    cellSizeSlider.setFillColor(sf::Color::White);

    sf::CircleShape cellSizeHandle(10);
    cellSizeHandle.setFillColor(sf::Color::Red);
    cellSizeHandle.setPosition(cellSizeSlider.getPosition().x + (cellSize - minCellSize) * 200 / (maxCellSize - minCellSize) - 10, cellSizeSlider.getPosition().y - 5);

    // Création de nos police pour les textes de la fenêtre
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Erreur: Police 'arial.ttf' non trouvée !" << std::endl;
        return;
    }

    sf::Text gridSizeInput, gridSizeLabel, cellSizeInput, cellSizeLabel, delayGenInput, delayGenLabel, corpLabel;
    gridSizeInput.setFont(font);
    gridSizeInput.setCharacterSize(20);
    gridSizeInput.setFillColor(sf::Color::White);
    gridSizeInput.setPosition(320, 40);
    gridSizeLabel.setFont(font);
    gridSizeLabel.setString("Taille de la grille (c*c) :");
    gridSizeLabel.setCharacterSize(20);
    gridSizeLabel.setFillColor(sf::Color::White);
    gridSizeLabel.setPosition(100, 10);

    cellSizeLabel.setFont(font);
    cellSizeLabel.setString("Taille des cellules :");
    cellSizeLabel.setCharacterSize(20);
    cellSizeLabel.setFillColor(sf::Color::White);
    cellSizeLabel.setPosition(100, 80);
    cellSizeInput.setFont(font);
    cellSizeInput.setCharacterSize(20);
    cellSizeInput.setFillColor(sf::Color::White);
    cellSizeInput.setPosition(320, 110);

    delayGenInput.setFont(font);
    delayGenInput.setCharacterSize(20);
    delayGenInput.setFillColor(sf::Color::White);
    delayGenInput.setPosition(180, 170);

    delayGenLabel.setFont(font);
    delayGenLabel.setString("Temps entre les generations (ms) :");
    delayGenLabel.setCharacterSize(20);
    delayGenLabel.setFillColor(sf::Color::White);
    delayGenLabel.setPosition(70, 140);

    corpLabel.setFont(font);
    corpLabel.setString("CESI TLS - All right reserved");
    corpLabel.setCharacterSize(10);
    corpLabel.setFillColor(sf::Color::White);
    corpLabel.setPosition(275, 230);

    // Création du boutton 'Construire'
    sf::RectangleShape buildButton(sf::Vector2f(120, 40));
    buildButton.setPosition(140, 200);
    buildButton.setFillColor(sf::Color::White);

    sf::Text buildText;
    buildText.setFont(font);
    buildText.setString("Construire");
    buildText.setCharacterSize(20);
    buildText.setFillColor(sf::Color::Black);
    buildText.setPosition(155, 205);

    // Variables pour les intéractions (sliders)
    bool draggingGridSize = false, draggingCellSize = false;
    bool editingGridSize = false, editingCellSize = false, editingDelayGen = false;

    std::string gridSizeBuffer = std::to_string(gridSize);
    std::string cellSizeBuffer = std::to_string(cellSize);
    std::string delayGenBuffer = std::to_string(delayGen);

    while (configWindow.isOpen()) {
        sf::Event event;
        while (configWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                configWindow.close();
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(configWindow);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (gridSizeHandle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    draggingGridSize = true;
                } else if (cellSizeHandle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    draggingCellSize = true;
                } else if (gridSizeInput.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    editingGridSize = true;
                    editingCellSize = false;
                    editingDelayGen = false;
                } else if (cellSizeInput.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    editingCellSize = true;
                    editingGridSize = false;
                    editingDelayGen = false;
                } else if (delayGenInput.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    editingDelayGen = true;
                    editingGridSize = false;
                    editingCellSize = false;
                } else if (buildButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Boutton 'Construire' pressé 
                    configWindow.close();
                    drawView();
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                draggingGridSize = false;
                draggingCellSize = false;
            }

            if (event.type == sf::Event::MouseMoved) {
                if (draggingGridSize) {
                    int x = std::clamp(mousePos.x, 100, 300);
                    gridSizeHandle.setPosition(x - 10, gridSizeSlider.getPosition().y - 5);
                    gridSize = minGridSize + ((x - 100) * (maxGridSize - minGridSize)) / 200; // Intervalle entre 4 et 32
                    gridSizeBuffer = std::to_string(gridSize);
                } else if (draggingCellSize) {
                    int x = std::clamp(mousePos.x, 100, 300);
                    cellSizeHandle.setPosition(x - 10, cellSizeSlider.getPosition().y - 5);
                    cellSize = minCellSize + ((x - 100) * (maxCellSize - minCellSize)) / 200; //Intervalle entre 10 et 50
                    cellSizeBuffer = std::to_string(cellSize);
                }
            }

            if (event.type == sf::Event::TextEntered) {
                if (editingGridSize || editingCellSize || editingDelayGen) {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                        if (editingGridSize && gridSizeBuffer.size() < 3)
                            gridSizeBuffer += static_cast<char>(event.text.unicode);
                        else if (editingCellSize && cellSizeBuffer.size() < 3)
                            cellSizeBuffer += static_cast<char>(event.text.unicode);
                        else if (editingDelayGen && delayGenBuffer.size() < 5)
                            delayGenBuffer += static_cast<char>(event.text.unicode);
                    } else if (event.text.unicode == '\b') {
                        if (editingGridSize && !gridSizeBuffer.empty())
                            gridSizeBuffer.pop_back();
                        else if (editingCellSize && !cellSizeBuffer.empty())
                            cellSizeBuffer.pop_back();
                        else if (editingDelayGen && !delayGenBuffer.empty())
                            delayGenBuffer.pop_back();
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (editingGridSize) {
                    int newGridSize = std::stoi(gridSizeBuffer);
                    gridSize = std::clamp(newGridSize, minGridSize, maxGridSize);
                    gridSizeBuffer = std::to_string(gridSize);
                    editingGridSize = false;
                    gridSizeHandle.setPosition(100 + (gridSize - minGridSize) * 200 / (maxGridSize - minGridSize) - 10, gridSizeSlider.getPosition().y - 5);
                } else if (editingCellSize) {
                    int newCellSize = std::stoi(cellSizeBuffer);
                    cellSize = std::clamp(newCellSize, 10, 50);
                    cellSizeBuffer = std::to_string(cellSize);
                    editingCellSize = false;
                    cellSizeHandle.setPosition(100 + (cellSize - minCellSize) * 200 / (maxCellSize - minCellSize) - 10, cellSizeSlider.getPosition().y - 5);
                } else if (editingDelayGen) {
                    int newDelayGen = std::stoi(delayGenBuffer);
                    delayGen = std::clamp(newDelayGen, 1, 10000);
                    delayGenBuffer = std::to_string(delayGen);
                    editingDelayGen = false;
                }
            }
        }

        // Màj de l'affichage
        configWindow.clear(sf::Color::Black);

        configWindow.draw(gridSizeSlider);
        configWindow.draw(gridSizeHandle);
        configWindow.draw(cellSizeSlider);
        configWindow.draw(cellSizeHandle);

        gridSizeInput.setString(editingGridSize ? gridSizeBuffer + "|" : std::to_string(gridSize));
        cellSizeInput.setString(editingCellSize ? cellSizeBuffer + "|" : std::to_string(cellSize));
        delayGenInput.setString(editingDelayGen ? delayGenBuffer + "|" : std::to_string(delayGen));

        configWindow.draw(gridSizeLabel);
        configWindow.draw(gridSizeInput);
        
        configWindow.draw(cellSizeLabel);
        configWindow.draw(cellSizeInput);
        
        configWindow.draw(delayGenLabel);
        configWindow.draw(delayGenInput);
        configWindow.draw(corpLabel);

        configWindow.draw(buildButton);
        configWindow.draw(buildText);

        configWindow.display();
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

        int cellX = mousePos.x / cellSize;
        int cellY = mousePos.y / cellSize;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    grid[cellY][cellX] = 1;
                } 
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    grid[cellY][cellX] = 0;
                }
            }
    
            if (event.type == sf::Event::KeyPressed) {
                if (mousePos.x >= 0 && mousePos.y >= 0 && mousePos.x < windowSize && mousePos.y < windowSize) {
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
                            outFile.close();
                            window.close();
                        }
                    }

                    if (event.key.code == sf::Keyboard::LShift) {
                                grid[cellY][cellX] = 2;
                    }
                    else if (event.key.code == sf::Keyboard::LControl) {
                        grid[cellY][cellX] = 3;
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
                if (grid[y][x] == 0 || grid[y][x] == 1){
                    cell.setFillColor(grid[y][x] == 1 ? sf::Color::White : sf::Color::Transparent);
                }
                else{
                cell.setFillColor(grid[y][x] == 2 ? sf::Color::Red : sf::Color::Green);
                }
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Red);
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

int ConfigView::getGridSize(){
    return gridSize;
}
int ConfigView::getCellSize(){
    return cellSize;
}

int ConfigView::getDelayGen(){
    return delayGen;
}

int ConfigView::getMinGridSize(){
    return minGridSize;
}
int ConfigView::getMaxGridSize(){
    return maxGridSize;
}
int ConfigView::getMinCellSize(){
    return minCellSize;
}
int ConfigView::getMaxCellSize(){
    return maxCellSize;
}

void ConfigView::setMinGridSize(int minGridSize){
    this->minGridSize = minGridSize;
}
void ConfigView::setMaxGridSize(int maxGridSize){
    this->maxGridSize = maxGridSize;
}
void ConfigView::setMinCellSize(int minCellSize){
    this->minCellSize = minCellSize;
}
void ConfigView::setMaxCellSize(int maxCellSize){
    this->maxCellSize = maxCellSize;
}