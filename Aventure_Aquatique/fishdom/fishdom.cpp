// Aventure Aquatique.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
//#include <math.h>
using namespace sf;
using namespace std;
int main()
{
	RenderWindow window(VideoMode(1200,850), "MyGame");
	window.setFramerateLimit(60);
	bool gameover = false;
	bool gameStarted = false;
	//double pi = 3.14159265358979323846;
	int score = 0;
	int nbr_food_mangee = 0;
	//***********importer font************
	Font font;
	font.loadFromFile("ressources/font/arial.ttf");
	Text scoreText;
	scoreText.setFont(font);
	Text commencerText;
	commencerText.setFont(font);
	// *************** Audio *****************
	Music gameMusic;
	gameMusic.openFromFile("ressources/audios/background_music.ogg");
	gameMusic.setVolume(15);
	gameMusic.play();
	gameMusic.setLoop(true); //loop the audio
	Music gameoverMusic;
	gameoverMusic.openFromFile("ressources/audios/gameover_music.ogg");
	// *************** Graphiques *****************
// Background -----------------------------------------------------------
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("ressources/images/background.png");
	Sprite backgroundSprite(backgroundTexture);
// gameover -----------------------------------------------------------
	Texture gameoverTexture;
	gameoverTexture.loadFromFile("ressources/images/gameover.png");
	Sprite gameoverSprite(gameoverTexture);
// firstground -----------------------------------------------------------
	Texture firstgroundTexture;
	firstgroundTexture.loadFromFile("ressources/images/firstground.png");
	Sprite firstgroundSprite(firstgroundTexture);
//attributs -----------------------------------------------------------
	//**fish**
	Texture fishTexture;
	fishTexture.loadFromFile("ressources/images/fish1.png");
	Sprite fishSprite(fishTexture);
	float volume_initiale = 0.5f;
	fishSprite.setScale(0.5f,0.5f);//volume initiale
	
	//**food**
	Texture foodTexture;
	foodTexture.loadFromFile("ressources/images/food2.png");
	Sprite foodSprite(foodTexture);
	// génération d'une position initiale pour la foodSprite
	float x = 200;
	float y = 200;
	foodSprite.setPosition(x, y);
	
	//**bombe**
	Texture bombeTexture;
	bombeTexture.loadFromFile("ressources/images/bombe1.png");
	Sprite bombeSprite(bombeTexture);
	bombeSprite.setPosition(float(rand() % 1100 + 50), -25.f);

	//**shark**
	Texture sharkTexture;
	sharkTexture.loadFromFile("ressources/images/shark1.png");
	Sprite sharkSprite(sharkTexture);
	sharkSprite.setScale(0.7f, 0.7f);
	sharkSprite.setPosition(-25.f, float(rand() % 750 + 50));

	// Définir les limites de la position de la fishSprite
	
	Vector2u windowSize = window.getSize();
	float spriteWidth = fishSprite.getGlobalBounds().width;
	float spriteHeight = fishSprite.getGlobalBounds().height;
	float xMin = 0;
	float xMax = windowSize.x- spriteWidth / 2.0f;
	float yMin = 0;
	float yMax = windowSize.y -spriteHeight / 2.0f;
	
	
	while (window.isOpen())
	{
		Event event;
		while (!gameStarted)
		{
			sf::Event event1;
			while (window.pollEvent(event1))
			{

				if (event1.type == sf::Event::KeyPressed && event1.key.code == sf::Keyboard::Enter)
				{
					gameStarted = true;
				}
				if (event1.type == Event::Closed)
				{
					window.close();
					gameMusic.stop();
				}

				break;
			}
			window.clear();
			window.draw(firstgroundSprite);
			commencerText.setCharacterSize(60);
			commencerText.setPosition(225, 425);
			commencerText.setFillColor(sf::Color::Red);
			commencerText.setString("taper enter pour commencer");
			window.draw(commencerText);
			window.display();
		}
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//Evènement déclenché lorsque l'utilisateur souhaite fermer la fenêtre
				case Event::Closed:
					window.close();
					break;
				/*if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
						window.close();
				}
				// controler la fishSprite par clavier
				case Event::KeyPressed:
					switch (event.key.code)
					{
						case Keyboard::Left:
							fishSprite.move(-15.f, 0.f); // déplacer le vaisseau spatial vers la gauche
							if (fishSprite.getPosition().x < xMin)
							{
								fishSprite.setPosition(xMin, fishSprite.getPosition().y);
							}
							break;
						case Keyboard::Right:
							fishSprite.move(15.f, 0.f); // déplacer le vaisseau spatial vers la droite
							if (fishSprite.getPosition().x > xMax)
							{
								fishSprite.setPosition(xMax, fishSprite.getPosition().y);
							}
							break;
						case Keyboard::Up:
							fishSprite.move(0.f, -15.f); // déplacer le vaisseau spatial 10px vers le haut
							if (fishSprite.getPosition().y < yMin)
							{
								fishSprite.setPosition(fishSprite.getPosition().x, yMin);
							}
							break;
						case Keyboard::Down:
							fishSprite.move(0.f, 15.f); // déplacer le vaisseau spatial 10px vers le bas
							if (fishSprite.getPosition().y > yMax)
							{
								fishSprite.setPosition(fishSprite.getPosition().x, yMax);
							}
							break;
					}
					break;
				}*/
				case Event::MouseMoved:
					// Obtenir les coordonnées de la souris
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

					// Définir les coordonnées du sprite en fonction de la position de la souris
					fishSprite.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

					// Faire tourner la poisson dans la direction de la souris
					//float angle = std::atan2(mousePosition.y - window.getSize().y / 2.f, mousePosition.x - window.getSize().x / 2.f);
					//fishSprite.setRotation(angle * 180.f / pi);
			}
		}
		//******************Animation********************
		
		//deplacement de la bombe
		bombeSprite.move(0.f, 5.f);
		if (bombeSprite.getPosition().y > 850)
			bombeSprite.setPosition(float(rand() % 1100 + 50), -25.f);
		//deplacement du shark
		sharkSprite.move(5.f, 0.f);
		if (sharkSprite.getPosition().x > 1200)
			sharkSprite.setPosition(-25.f, float(rand() % 750 + 50));
		
		//collision entre fish et (shark ou bombe)
		if (fishSprite.getGlobalBounds().intersects(sharkSprite.getGlobalBounds()) or fishSprite.getGlobalBounds().intersects(bombeSprite.getGlobalBounds()))
		{
			gameover = true;
		}
		//animation de foodSprite --------------------------------------

		//collision entre fish et food
		if (fishSprite.getGlobalBounds().intersects(foodSprite.getGlobalBounds()))
		{
			// Collision détectée !
			score = score + 10;
			nbr_food_mangee++;
			// Augmentation de la taille du sprite du poisson en fonction du nombre de nourriture mangée
			float scaleFactor = 0.5f + (0.05f * nbr_food_mangee); // Augmente la taille de 0.1 à chaque fois que le poisson mange de la nourriture
			fishSprite.setScale(scaleFactor, scaleFactor);
			// génération d'une position aléatoire pour la foodSprite
			float x = rand() % (static_cast<int>(window.getSize().x - foodSprite.getGlobalBounds().width));
			float y = rand() % (static_cast<int>(window.getSize().y - foodSprite.getGlobalBounds().height));
			foodSprite.setPosition(x, y);
		}
		window.clear();
		if (!gameover)
		{
			window.draw(backgroundSprite);
			window.draw(fishSprite);
			window.draw(bombeSprite);
			window.draw(sharkSprite);
			window.draw(foodSprite);
			scoreText.setCharacterSize(60);
			scoreText.setPosition(50, 50);
			scoreText.setFillColor(sf::Color::Black);
			scoreText.setString("Score : " + to_string(score));
			window.draw(scoreText);
		}
		else
		{
			// if (gameover)
			window.draw(gameoverSprite);
			gameMusic.stop();
			gameoverMusic.play();
			gameoverMusic.setVolume(15);
			scoreText.setCharacterSize(60);
			scoreText.setPosition(150, 500);
			scoreText.setFillColor(sf::Color::White);
			scoreText.setString("Score final : " + to_string(score));
			window.draw(scoreText);
		}
		window.display();
	}
	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
