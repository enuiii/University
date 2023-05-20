#include <SFML/Graphics.hpp> 
#include <string> 
#include <iostream> 
#include <ctime> 

class AnimatedText {
private:
	std::string text; // текст анимации
	int duration;     // время, за которое текст полностью проявится

public:
	AnimatedText(const std::string& _text, const int& _duration) {
		text = _text;         // сохраняем текст анимации
		duration = _duration; // сохраняем продолжительность анимации
	}

	std::string get_text(int current_time) {
		// определяем, какая часть текста должна быть видна в данный момент
		int seconds = current_time % (duration + 1);
		std::string end_text = text.substr(0, text.size() * seconds / duration);
		return end_text;
	}
};

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 600), "AnimatedText");

	int duration = 13;             // время анимации (секунды)
	std::string text_output = "Hello, world"; // текст анимации
	AnimatedText animated_text = AnimatedText(text_output, duration); // создаем объект анимированного текста

	sf::Text text;
	sf::Font font;
	font.loadFromFile("AZfont.ttf"); // загружаем шрифт
	text.setFont(font);
	text.setCharacterSize(60);
	text.setColor(sf::Color::Red);

	float current_time; // текущее время (в миллисекундах)

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close(); // закрываем окно при нажатии на крестик
		}

		current_time = std::clock(); // получаем текущее время

		text.setPosition(400, 400); // устанавливаем позицию текста
		text.setString(animated_text.get_text(current_time / 1000)); // получаем текущую видимую часть текста

		window.clear();
		window.draw(text);
		window.display();
	}

	return 0;
}
