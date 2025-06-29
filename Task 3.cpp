#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

using namespace sf;
using namespace std;

// Constants
const int blockSize = 20;
const int width = 800;
const int height = 600;
int speed = 100;

// Movement direction
Vector2i direction(1, 0); // Initially move right

// Snake segment structure
struct SnakeSegment {
    Vector2i position;
    SnakeSegment(int x, int y) {
        position = Vector2i(x, y);
    }
};

// Main Game Class
class SnakeGame {
private:
    RenderWindow window;
    vector<SnakeSegment> snake;
    Vector2i food;
    RectangleShape block;
    Clock clock;
    Time lastMove;
    SoundBuffer eatBuffer;
    Sound eatSound;
    Font font;
    Text scoreText;
    int score = 0;

public:
    SnakeGame() : window(VideoMode(width, height), "Snake Game") {
        window.setFramerateLimit(60);
        block.setSize(Vector2f(blockSize - 1, blockSize - 1));
        block.setFillColor(Color::Green);

        resetSnake();
        generateFood();

        // Load sound
        if (!eatBuffer.loadFromFile("eat.wav")) {
            cout << "Failed to load sound!" << endl;
        }
        eatSound.setBuffer(eatBuffer);

        // Load font
        if (!font.loadFromFile("arial.ttf")) {
            cout << "Font loading failed!" << endl;
        }
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(10, 10);

        srand(time(0));
    }

    void resetSnake() {
        snake.clear();
        snake.push_back(SnakeSegment(5, 5));
        snake.push_back(SnakeSegment(4, 5));
        snake.push_back(SnakeSegment(3, 5));
        direction = Vector2i(1, 0);
        score = 0;
        speed = 100;
    }

    void generateFood() {
        food.x = rand() % (width / blockSize);
        food.y = rand() % (height / blockSize);
    }

    void moveSnake() {
        Vector2i headPos = snake[0].position + direction;

        // Check wall collision
        if (headPos.x < 0 || headPos.x >= width / blockSize || headPos.y < 0 || headPos.y >= height / blockSize) {
            gameOver();
            return;
        }

        // Check self collision
        for (size_t i = 1; i < snake.size(); ++i) {
            if (snake[i].position == headPos) {
                gameOver();
                return;
            }
        }

        // Move body
        for (size_t i = snake.size() - 1; i > 0; --i) {
            snake[i].position = snake[i - 1].position;
        }

        // Move head
        snake[0].position = headPos;

        // Eat food
        if (headPos == food) {
            snake.push_back(SnakeSegment(-1, -1));
            generateFood();
            eatSound.play();
            score++;
            if (score % 5 == 0 && speed > 30)
                speed -= 10;
        }
    }

    void draw() {
        window.clear(Color::Black);

        // Draw snake
        for (auto &segment : snake) {
            block.setPosition(segment.position.x * blockSize, segment.position.y * blockSize);
            window.draw(block);
        }

        // Draw food
        block.setFillColor(Color::Red);
        block.setPosition(food.x * blockSize, food.y * blockSize);
        window.draw(block);
        block.setFillColor(Color::Green);

        // Draw score
        stringstream ss;
        ss << "Score: " << score;
        scoreText.setString(ss.str());
        window.draw(scoreText);

        window.display();
    }

    void gameOver() {
        cout << "Game Over! Final Score: " << score << endl;
        window.close();
    }

    void run() {
        lastMove = clock.getElapsedTime();

        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close();

                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::Up && direction != Vector2i(0, 1)) direction = Vector2i(0, -1);
                    else if (e.key.code == Keyboard::Down && direction != Vector2i(0, -1)) direction = Vector2i(0, 1);
                    else if (e.key.code == Keyboard::Left && direction != Vector2i(1, 0)) direction = Vector2i(-1, 0);
                    else if (e.key.code == Keyboard::Right && direction != Vector2i(-1, 0)) direction = Vector2i(1, 0);
                }
            }

            if (clock.getElapsedTime() - lastMove > milliseconds(speed)) {
                moveSnake();
                lastMove = clock.getElapsedTime();
            }

            draw();
        }
    }
};

int main() {
    SnakeGame game;
    game.run();
    return 0;
}


