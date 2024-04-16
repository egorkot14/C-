#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
int size = 80;

char field[8][8] = {
		'L','H','B','Q','K','B','H','L',
		'P','P','P','P','P','P','P','P',
		'E','E','E','E','E','E','E','E',
		'E','E','E','E','E','E','E','E',
		'E','E','E','E','E','E','E','E',
		'E','E','E','E','E','E','E','E',
		'p','p','p','p','p','p','p','p',
		'l','h','b','k','q','b','h','l'
};
//Функция для хождения пешек по правилам
bool PawnGo(int x, int y, int i, int j, bool &white){
	if (((x - i) == 2) && ((y - j) == 0) && (field[6][y] == 'p') && ((x - i) != -2) && (field[x][y] == 'p') && (white) && (field[x - 1][y] != 'P')) {
		white = !white;
		return true;
	}
	else if ((((x - i) == -2) && (y - j) == 0) && (field[1][y] == 'P') && ((x - i) != 2) && (field[x][y] == 'P') && (!white) && (field[x + 1][y] != 'p')) {
		white = !white;
		return true;
	}
	else if (((x - i) == 1) && ((y - j) == 0) && (field[x][y] == 'p') && ((x - i) != -1) && (white)) {
		white = !white;
		return true;
	}
	else if ((((x - i) == -1) && (y - j) == 0) && (field[x][y] == 'P') && ((x - i) != 1) && (!white)) {
		white = !white;
		return true;
	}
	else return false;
	return false;
}

bool PawnCutW(int x, int y, int i, int j, bool &white) {
	if (field[x][y] == 'p' && white){
		if (field[i][j] != 'p' || field[i][j] != 'p') {
			return true;
		}
	}
	return false;
}

bool PawnCutB(int x, int y, int i, int j, bool &white) {
	if (field[x][y] == 'P' && !white) {
		if (field[i][j] != 'P' || field[i][j] != 'P') {
			return true;
		}
	}
	return false;
}

void Paint(sf::Sprite x, sf::RenderWindow &window, sf::Sprite &figures) {
	x.setPosition(0, 0);
	window.draw(x);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (field[i][j] == 'L') {
				figures.setTextureRect(sf::IntRect(0, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'H') {
				figures.setTextureRect(sf::IntRect(1 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'B') {
				figures.setTextureRect(sf::IntRect(2 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'Q') {
				figures.setTextureRect(sf::IntRect(3 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'K') {
				figures.setTextureRect(sf::IntRect(4 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'P') {
				figures.setTextureRect(sf::IntRect(5 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'l') {
				figures.setTextureRect(sf::IntRect(6 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'h') {
				figures.setTextureRect(sf::IntRect(7 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'b') {
				figures.setTextureRect(sf::IntRect(8 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'q') {
				figures.setTextureRect(sf::IntRect(9 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'k') {
				figures.setTextureRect(sf::IntRect(10 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'p') {
				figures.setTextureRect(sf::IntRect(11 * size, 0, size, size));
				figures.setPosition(j * size, i * size);
			}
			else if (field[i][j] == 'E') {
				continue;
			}
			else
				continue;
			window.draw(figures);
		}
}

void PaintReal(sf::Sprite x, sf::RenderWindow &window, int i, int j, int u, int h) {
	if (field[j][i] == 'L') {
		x.setTextureRect(sf::IntRect(0, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'H') {
		x.setTextureRect(sf::IntRect(1 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'B') {
		x.setTextureRect(sf::IntRect(2 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'Q') {
		x.setTextureRect(sf::IntRect(3 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'K') {
		x.setTextureRect(sf::IntRect(4 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'P') {
		x.setTextureRect(sf::IntRect(5 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'l') {
		x.setTextureRect(sf::IntRect(6 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'h') {
		x.setTextureRect(sf::IntRect(7 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'b') {
		x.setTextureRect(sf::IntRect(8 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'q') {
		x.setTextureRect(sf::IntRect(9 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'k') {
		x.setTextureRect(sf::IntRect(10 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	else if (field[j][i] == 'p') {
		x.setTextureRect(sf::IntRect(11 * size, 0, size, size));
		x.setPosition(u * size, h * size);
	}
	window.draw(x);
}



int main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	bool white = true;
	int posX = 404;
	int posY = 404;
	sf::RenderWindow window(sf::VideoMode(640, 640), L"Шахматы ультра-мега харош", sf::Style::Close);
	sf::Image icon;
	icon.loadFromFile("media/icon.png");
	window.setIcon(512, 512, icon.getPixelsPtr());
	sf::Texture bg;
	bg.loadFromFile("media/field.png");
	sf::Sprite background(bg);
	sf::Texture fig;
	fig.loadFromFile("media/figures.png");
	sf::Sprite figures(fig);
	while (window.isOpen()) {
		Paint(background, window, figures);
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int x = pos.x / size;
		int y = pos.y / size;
		sf::Event click;
		while (window.pollEvent(click))
		{
			if (click.type == sf::Event::Closed)
				window.close();
			if (click.type == sf::Event::MouseButtonPressed) {
				if (click.key.code == sf::Mouse::Left) {
					if (field[y][x] != 'E') {
						posX = x;
						posY = y;
					}
				}
			}
			if(click.type == sf::Event::MouseButtonReleased){
				if (click.key.code == sf::Mouse::Left) {
					if (posY != y || posX != x) {
						if (field[y][x] == 'E') {
							if (PawnGo(posY, posX, y, x, white) && ((field[posY][posX] == 'P') || (field[posY][posX] == 'p'))) {
								field[y][x] = field[posY][posX];
								field[posY][posX] = 'E';
							}
						}
						if (white && (field[posY][posX] == 'l' || field[posY][posX] == 'h' || field[posY][posX] == 'b' || field[posY][posX] == 'q' || field[posY][posX] == 'k')) {
							field[y][x] = field[posY][posX];
							field[posY][posX] = 'E';
							white = !white;
						}
						else if (!white && (field[posY][posX] == 'L' || field[posY][posX] == 'H' || field[posY][posX] == 'B' || field[posY][posX] == 'Q' || field[posY][posX] == 'K')) {
							field[y][x] = field[posY][posX];
							field[posY][posX] = 'E';
							white = !white;
						}
						if (PawnCutW(posY, posX, y, x, white) && white) {
							if (field[y][x] == 'P' || field[y][x] == 'L' || field[y][x] == 'H' || field[y][x] == 'B' || field[y][x] == 'Q' || field[y][x] == 'K') {
								if ((posY - y == 1) && (posX - x == -1) || (posY - y == 1) && (posX - x == 1)) {
									field[y][x] = field[posY][posX];
									field[posY][posX] = 'E';
									white = !white;
								}
							}
						}
						if (PawnCutB(posY, posX, y, x, white) && !white) {
							if (field[y][x] == 'p' || field[y][x] == 'l' || field[y][x] == 'h' || field[y][x] == 'b' || field[y][x] == 'q' || field[y][x] == 'k')
								if ((posY - y == -1) && (posX - x == 1) || (posY - y == -1) && (posX - x == -1)) {
									field[y][x] = field[posY][posX];
									field[posY][posX] = 'E';
									white = !white;
								}
						}
					}
					posX = 404;
					posY = 404;
				}
			}
		}
		if (posX != 404 && posY != 404 && PawnGo) {
			PaintReal(figures, window, posX, posY, x, y);
		}
		window.display();
	}
}