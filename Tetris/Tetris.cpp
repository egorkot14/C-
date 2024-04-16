#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "windows.h"

int main() {
	srand(time(0));
	const int square = 20;
	const int size = 32;
	sf::RenderWindow window(sf::VideoMode(size * square, size * square), L"Змейка", sf::Style::Close);
	sf::Image icon;
	icon.loadFromFile("Multimedia/icon.png");
	window.setIcon(512, 512, icon.getPixelsPtr());
	sf::Texture textureSnake;
	textureSnake.loadFromFile("Multimedia/snake.png");
	sf::Sprite python(textureSnake);
	sf::Texture textureFruit;
	textureFruit.loadFromFile("Multimedia/texture.jpg");
	sf::Sprite fruit(textureFruit);
	sf::Texture textureGO;
	textureGO.loadFromFile("Multimedia/gameOver.bmp");
	sf::Sprite gameOver(textureGO);
	sf::Texture textureWin;
	textureWin.loadFromFile("Multimedia/win.jpg");
	sf::Sprite winner(textureWin);
	sf::SoundBuffer sound;
	sound.loadFromFile("Multimedia/bite.wav");
	sf::Sound bite(sound);
	sf::Music music;
	music.openFromFile("Multimedia/");
	music.play();
	music.setLoop(true);
	sf::Font font;
	font.loadFromFile("Multimedia/font.ttf");
	sf::Text textScore("", font, size);
	textScore.setFillColor(sf::Color::Green);
	sf::Text textTime("", font, size);
	textTime.setFillColor(sf::Color::Green);
	sf::Clock clock;
	int time = 0;
	int score = 0;
	struct {
		int x;
		int y;
	} snake[square * square];
	snake[0].x = square / 2;
	snake[0].y = square / 2;
	int delay = 250;
	char go = 's';
	int fruitX = rand() % square;
	int fruitY = rand() % square;
	int food[1] = { rand() % 7 + 1 };
	int lenght = 1;
	bool game = true;
	bool win = false;
	while (window.isOpen()) //Цикл отвечающий за всю игру(Пока окно открыто)
	{
		sf::Event press;
		while (window.pollEvent(press))
		{
			if (press.type == sf::Event::Closed)
				window.close();
			if ((press.type == sf::Event::KeyPressed) && (game) && (!win)) //Отслеживание нажатия кнопок
			{
				if ((press.type == sf::Keyboard::W) || (press.key.code == sf::Keyboard::Up) && (go!='d'))
					go = 'u';//Up
				else if ((press.type == sf::Keyboard::D) || (press.key.code == sf::Keyboard::Right) && (go != 'l'))
					go = 'r';//Right
				else if ((press.type == sf::Keyboard::A) || (press.key.code == sf::Keyboard::Left) && (go != 'r'))
					go = 'l';//Left
				else if ((press.type == sf::Keyboard::S) || (press.key.code == sf::Keyboard::Down) && (go != 'u'))
					go = 'd';//Down
			}
		}

		if ((game) && (!win))
		{
			sf::Time timer = clock.getElapsedTime();
			time = timer.asSeconds();
			for (int i = lenght - 1; i > 0; i--) //Цикл отвечающий за увеличение змейки 
			{
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}

			switch (go) //Оператор выбора для перемещении змейки 
			{
			case 'u':
				python.setRotation(270);
				snake[0].y--;
				Sleep(delay);
				break;
			case 'l':
				python.setRotation(180);
				snake[0].x--;
				Sleep(delay);
				break;
			case 'd':
				python.setRotation(90);
				snake[0].y++;
				Sleep(delay);
				break;
			case 'r':
				python.setRotation(0);
				snake[0].x++;
				Sleep(delay);
				break;
			}
		}

		for (int i = 0; i < square; i++) //Цикл для отрисовки текстуры заднего поля
			for (int j = 0; j < square; j++)
			{
				fruit.setTextureRect(sf::IntRect(0, 0, size, size));
				fruit.setPosition(i * size, j * size);
				window.draw(fruit);
			}
		fruit.setTextureRect(sf::IntRect(food[0] * size, 0, size, size)); //Изначальная отрисовка фруктов 
		fruit.setPosition(fruitX * size, fruitY * size);
		window.draw(fruit);

		for (int i = 0; i < lenght; i++) //Цикл для отрисовки змейки и её тела 
		{
		//Portal
			if ((snake[0].x) > (square - 1))
				snake[0].x = 0;
			else if (snake[0].x < 0)
				snake[0].x = square - 1;
			else if (snake[0].y > (square - 1))
				snake[0].y = 0;
			else if (snake[0].y < 0)
				snake[0].y = square - 1;
		//Portal

			if (i == 0)//Отрисовка головы
				python.setTextureRect(sf::IntRect(size, 0, size, size));
			else if (i == lenght - 1)//Отрисовка хвоста*
				python.setTextureRect(sf::IntRect(size * 2, 0, size, size));
			else//Отрисовка тела
				python.setTextureRect(sf::IntRect(0, 0, size, size));

			python.setOrigin(size / 2, size / 2); //Смещает точку поворота спрайта на середину
			python.setPosition((snake[i].x * size) , (snake[i].y * size)); //Установка позиции змейки(Сделано для того чтобы змейка не проходила около еды а шла на её центр и поедала её)
			window.draw(python);

			if ((snake[0].x == fruitX) && (snake[0].y == fruitY)) //Реализация поедания еды
			{
				if (food[0] == 7)
					score -= 10;
				else if (food[0] == 6)
				{
					score += 50;
					lenght++;
				}
				else
				{
					score += 10;
					lenght++;
				}
				clock.restart();
				bite.play();
				food[0] = rand() % 7 + 1;
				fruitX = rand() % square;
				fruitY = rand() % square;
				fruit.setPosition(fruitX * size, fruitY * size);
				if (delay >= 50)
					delay -= 10;
			}
			if (i > 0)
				if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y)) //Проверка на столкновение головы и тела для Смерти
					game = false;
			if ((fruitX == snake[i + 1].x) && (fruitY == snake[i + 1].y)) //Проверка для того чтобы еда не генирировалась внутри тела
			{
				food[0] = rand() % 7 + 1;
				fruitX = rand() % square;
				fruitY = rand() % square;
				fruit.setPosition(fruitX * size, fruitY * size);
			}
			if (lenght == ((square * square) - 1)) //Реализация победы
				win = true;
		}
		if (win) //Победа (При победе Открывается фоточка пельменя на весь экран)
		{
			music.stop();
			winner.setScale(0.54, 0.73);
			window.draw(winner);
		}
		if (!game) //Порожение (Мне лень писать, думаю тут понятно)
		{
			music.stop();
			gameOver.setScale(1.03, 1.03);
			window.draw(gameOver);
		}
		if (time == 5) //При прохождении 5 секунд еда меняет свою позицию 
		{
			clock.restart();
			food[0] = rand() % 7 + 1;
			fruitX = rand() % square;
			fruitY = rand() % square;
			fruit.setPosition(fruitX * size, fruitY * size);
		}
		std::ostringstream streamScore;
		streamScore << score;
		textScore.setString("Score: " + streamScore.str());
		textScore.setPosition(1, 0);
		window.draw(textScore);
		std::ostringstream streamTime;
		streamTime << time;
		textTime.setString("Time: " + streamTime.str());
		textTime.setPosition(490, 0);
		window.draw(textTime);
		window.display();
	}
}