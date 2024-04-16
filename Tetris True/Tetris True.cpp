#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>

struct coordinates 
{ //Создание структур ОсновнаяФигуа Фантом(для реализации границ) и следующейФигуры (для вывода в окошко)
	int x;
	int y;
} oneFigure[4], phantom[4], nextFigure[4];

const int width = 10;
const int height = 20; //Размерность поля

int figures[7][4] = { //Масси для фигур (их кординат)
		4, 14, 24, 34, //I
		4, 14, 15, 24, //T
		4, 14, 24, 25, //L
		5, 15, 24, 25, //J
		4, 5, 14, 15, //O
		4, 14, 15, 25, //S
		5, 14, 15, 24, //Z
};
int nextFigures[7][4] = { //Масси для фигур (их кординат только для некстФигуры)
		38, 64, 90, 116, //I
		38, 64, 65, 90, //T
		38, 64, 90, 91, //L
		39, 65, 90, 91, //J
		38, 39, 64, 65, //O
		38, 64, 65, 91, //S
		39, 64, 65, 90, //Z
};
int nextFigureRandom = rand() % 7; //Выбор некстФигуры рандомно
int field[width][height] = { 0 }; //Заднее поле цвет его
bool gameOver = false;
bool win = false;
int figureRandom = rand() % 7; //Выбор Фигуры рандомно
int color = rand() % 8 + 1;	//Выбор цвета для Фигуры рандомно
int newColor = rand() % 8 + 1; //Выбор цвета для некстФигуры рандомно

bool check() { //Создание буливой функции (Возвращает True/False)
	for (int i = 0; i < 4; i++) {
		if ((oneFigure[i].x < 0) || (oneFigure[i].x > (width - 1)) || (oneFigure[i].y > (height - 1))) //Если основная фигура вышла за границу тогда False
			return false;
		if (field[oneFigure[i].x][oneFigure[i].y])
			return false;
	}
}

void revers() {
	if (!check()) //Если функция check возвращает False тогда основная фигура возвращается на место фантома
		for (int i = 0; i < 4; i++)
			oneFigure[i] = phantom[i];
}

void nextSpawn() { //Спавн фигуры в окошечке для отображения следующей фигуры 
	srand(time(0));
	if ((!win) && (!gameOver)) {
		for (int i = 0; i < 4; i++) {  
			nextFigure[i].x = nextFigures[nextFigureRandom][i] % (width * 2 + 6);
			nextFigure[i].y = nextFigures[nextFigureRandom][i] / (width * 2 + 6);
		}
	}
}

void spawn() { //Спавн фигуры на поле
	srand(time(0));
	if ((!win) && (!gameOver))
		for (int i = 0; i < 4; i++) {
			oneFigure[i].x = figures[figureRandom][i] % width;
			oneFigure[i].y = figures[figureRandom][i] / width;
		}
}

int main() {
	srand(time(0)); //Обнуление рандома
	const int size = 34; //Он нас хотел подставить но не вышло))
	sf::RenderWindow window(sf::VideoMode((width + 6) * size, height * size), L"Тетрис Р-153", sf::Style::Close);
	//Подгрузка
	sf::Texture textureBlock;
	textureBlock.loadFromFile("texture.png");
	sf::Sprite block(textureBlock);
	sf::Image icon;
	icon.loadFromFile("icon.png");
	window.setIcon(512, 512, icon.getPixelsPtr());
	sf::Font font;
	font.loadFromFile("font.ttf");
	//Подгрузка

	//Создание объектов текста и задание ему свойств
	sf::Text scoreText("", font, size);
	sf::Text gameOverText("", font, size * 2);
	sf::Text winText("", font, size * 2);
	scoreText.setFillColor(sf::Color::Color(192, 192, 192, 255));
	gameOverText.setFillColor(sf::Color::Color(192, 192, 192, 255));
	gameOverText.setStyle(sf::Text::Bold);
	winText.setFillColor(sf::Color::Color(192, 192, 192, 255));
	winText.setStyle(sf::Text::Bold);
	//Создание объектов текста и задание ему свойств

	int blockX = 0;
	int score = 0;
	bool rotate = false;
	float delay = 0.5;
	float time = 0;
	sf::Clock watch;
	while (window.isOpen()) {
		sf::Time timer = watch.getElapsedTime();
		time += timer.asSeconds();
		sf::Event press;
		while (window.pollEvent(press)) {
			if (press.type == sf::Event::Closed)
				window.close();
			if (press.type == sf::Event::KeyPressed) {
				if ((press.key.code == sf::Keyboard::A) || (press.key.code == sf::Keyboard::Left))
					blockX--;
				else if ((press.key.code == sf::Keyboard::D) || (press.key.code == sf::Keyboard::Right))
					blockX++;
				else if ((press.key.code == sf::Keyboard::Space) || (press.key.code == sf::Keyboard::Up))
					rotate = true;
				else if (press.key.code == sf::Keyboard::LShift)
					delay = 0;
			}
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))))
			delay = 0.2;
		for (int i = 0; i < 4; i++) {
			phantom[i] = oneFigure[i];
			oneFigure[i].x += blockX;
		}
		revers(); //Если вышел за границы то ты не вышел за границы КРЧ просто вызов функции revers
		if ((time >= delay) && (!win) && (!gameOver)) { //Опа а это нам сегодня повторяли так что вот А так эт для падения фигуры задержка 
			for (int i = 0; i < 4; i++) {
				phantom[i] = oneFigure[i];
				oneFigure[i].y++;
			}
			if (!check()) { //Фигура упала и осталась на месте и сразу генерация некст фигуры и рандом новой фигуры в окошечке)
				for (int i = 0; i < 4; i++)
					field[phantom[i].x][phantom[i].y] = color;
				figureRandom = nextFigureRandom;
				color = newColor;
				spawn();
				nextFigureRandom = rand() % 7;
				newColor = rand() % 8 + 1;
				nextSpawn();
			}
			time = 0;
		}
		if (rotate) { //Aффинные преобразования
			coordinates centerBlock = oneFigure[1];
			for (int i = 0; i < 4; i++) {
				int newX = oneFigure[i].y - centerBlock.y;
				int newY = oneFigure[i].x - centerBlock.x;
				oneFigure[i].x = centerBlock.x - newX;
				oneFigure[i].y = centerBlock.y + newY;
			}
		}
		revers(); //Если у тебя поворот на границе то он не даёт повенуть 
		if (oneFigure[0].y == 0) { //Тоже спавн новой фигуры но тут для нижней граници 
			spawn();
			nextSpawn();
		}
		int line = height - 1;
		for (int i = line; i > 0; i--) { //Удаление линий 
			int blockCount = 0; //Счётчик для условия (Если линия полная то удаление её)
			for (int j = 0; j < width; j++) {
				if (field[j][i] != 0)
					blockCount++;
				field[j][line] = field[j][i];
			}
			if (blockCount != width) //Если не полностью заполнена тогда он её скипает
				line--;
			else
				score += 100;
		}
		if (score >= 100)
			win = true;
		for (int i = 0; i < 4; i++)
			if ((field[phantom[i].x][phantom[i].y] == color) && (field[oneFigure[i].x][oneFigure[i].y])) //Если фигура заспавнилась в фигуре то проигрышь 
				gameOver = true;
		watch.restart();
		rotate = false; //Для афинных преобразований 
		blockX = 0; //Для передвижения фигурки реализовано (-1/+1)
		delay = 0.5;
		window.clear();
		for (int i = 0; i < width; i++) //Чёрное поле
			for (int j = 0; j < height; j++) {
				block.setTextureRect(sf::IntRect(field[i][j] * size, 0, size, size));
				block.setPosition(i * size, j * size);
				window.draw(block);
			}
		for (int i = 0; i < 4; i++) { //Для фигуры 
			block.setTextureRect(sf::IntRect(color * size, 0, size, size));
			block.setPosition(oneFigure[i].x * size, oneFigure[i].y * size);
			window.draw(block);

		}
		for (int i = 0; i < 4; i++) { //Для некст фигуры
			block.setTextureRect(sf::IntRect(newColor * size, 0, size, size));
			block.setPosition(nextFigure[i].x * size, nextFigure[i].y * size);
			window.draw(block);
		}
		if (gameOver) { 
			gameOverText.setString("!YOU LOSE!");
			gameOverText.setPosition((width / 4) * size - 40, height);
			window.draw(gameOverText);
		}
		if (win) {
			winText.setString("!YOU WIN!");
			winText.setPosition((width / 4) * size - 10, height);
			window.draw(winText);
		}
		std::ostringstream scoreStream;
		scoreStream << score;
		scoreText.setString("Score:\n" + scoreStream.str());
		scoreText.setPosition((width + 1) * size, 6 * size);	
		window.draw(scoreText);
		window.display();
	}
}