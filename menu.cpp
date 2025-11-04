#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "menu.h"
using namespace std;

void mostrarMenu() {
    sf::RenderWindow ventana(sf::VideoMode(900, 600), "Imperio Romano: Batalla por la Gloria");
    ventana.setFramerateLimit(60);

    // Fondo
    sf::Texture fondoTex;
    if (!fondoTex.loadFromFile("imagenes/portada.png")) {
        cout << "Error: no se pudo cargar la imagen de fondo." << endl;
        return;
    }
    sf::Sprite fondo(fondoTex);

    // Fuente
    sf::Font fuente;
    if (!fuente.loadFromFile("C:/Windows/Fonts/times.ttf")) {
        cout << "Error: no se pudo cargar la fuente." << endl;
        return;
    }

    // Música
    sf::Music musica;
    if (!musica.openFromFile("sonidos/batalla.wav")) {
        cout << "Error: no se pudo cargar la música." << endl;
    } else {
        musica.setLoop(true);
        musica.setVolume(50);
        musica.play();
    }

    // Opciones
    sf::Text opciones[3];
    string textos[3] = {"JUGAR", "ESCOGER NIVEL", "SALIR"};
    for (int i = 0; i < 3; i++) {
        opciones[i].setFont(fuente);
        opciones[i].setString(textos[i]);
        opciones[i].setCharacterSize(40);
        opciones[i].setFillColor(sf::Color::White);
        opciones[i].setPosition(350, 350 + i * 70);
    }

    int seleccion = -1;

    // Bucle principal
    while (ventana.isOpen()) {
        sf::Event evento;
        sf::Vector2i mouse = sf::Mouse::getPosition(ventana);

        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();

            if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
                for (int i = 0; i < 3; i++) {
                    sf::FloatRect area = opciones[i].getGlobalBounds();
                    if (area.contains(mouse.x, mouse.y))
                        seleccion = i;
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            sf::FloatRect area = opciones[i].getGlobalBounds();
            if (area.contains(mouse.x, mouse.y))
                opciones[i].setFillColor(sf::Color(200, 120, 40));
            else
                opciones[i].setFillColor(sf::Color::White);
        }

        if (seleccion == 0) {
            cout << "Iniciando juego..." << endl;
            seleccion = -1;
        } else if (seleccion == 1) {
            cout << "Abriendo selector de niveles..." << endl;
            seleccion = -1;
        } else if (seleccion == 2) {
            ventana.close();
        }

        ventana.clear();
        ventana.draw(fondo);
        for (int i = 0; i < 3; i++)
            ventana.draw(opciones[i]);
        ventana.display();
    }
}

