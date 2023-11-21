#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int secretNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;
    int maxAttempts = 10;

    sf::RenderWindow window(sf::VideoMode(400, 200), "Jogo de Adivinhacao");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Erro ao carregar a fonte." << std::endl;
        return EXIT_FAILURE;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    sf::Clock clock;
    sf::Time elapsedTime;
    bool outOfAttempts = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!outOfAttempts) {
            elapsedTime = clock.getElapsedTime();
            if (elapsedTime.asSeconds() >= 30) { // Contagem regressiva de 30 segundos
                outOfAttempts = true;
                text.setString("Tempo Esgotado!");
            } else {
                window.clear(sf::Color::Black);
                text.setString("Tente adivinhar o numero entre 1 e 100.\n");
                window.draw(text);
                window.display();

                std::cout << "Digite seu palpite: ";
                std::cin >> guess;
                attempts++;

                if (guess > secretNumber) {
                    std::cout << "Muito alto!\n";
                } else if (guess < secretNumber) {
                    std::cout << "Muito baixo!\n";
                } else {
                    std::cout << "Parabens! Voce acertou o numero em " << attempts << " tentativas!\n";
                    break;
                }

                if (attempts >= maxAttempts) {
                    outOfAttempts = true;
                    text.setString("Numero de tentativas excedido!");
                }
            }
        } else {
            window.clear(sf::Color::Black);
            window.draw(text);
            window.display();
        }
    }

    return 0;
}
