#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "slider.h"
#include "zone.h"
#include "ball.h"
#include "key.h"

using namespace std;

#define EASY_SPEED 200
#define MEDIUM_SPEED 160
#define HARD_SPEED 128
#define MAX_OBSTACLES 2
#define GAME_DURATION 120
int main() {
	int sliderSize;
	int goalWidth;
	int level;
	initscr();
	srand(time(0));
	printw("Welcome to 2-Player Air Hockey!\n");
	printw("Controls: Arrow keys for Player 1, W/A/S/D for Player 2.\n");
	printw("Press 't' to start the game.\n");
	refresh();
	while (getch() != 't');

	clear();
	refresh();
	mvprintw(0, 0, "Enter slider size (4 to 7): ");
	refresh();
	mvscanw(1,0,"%d", &sliderSize);
	if (sliderSize < 4 || sliderSize > 7) sliderSize = 4;

	clear();
	refresh();

	clear();
	refresh();
	mvprintw(0, 0, "Enter goal width (less than zone width): ");
	refresh();
	mvscanw(1,0,"%d", &goalWidth);
	if (goalWidth <= 0 || goalWidth >= ZONE_WIDTH) goalWidth = ZONE_WIDTH;
	clear();
	refresh();
	mvprintw(0, 0, "Enter level of game: ");
	refresh();
	mvscanw(1,0,"%d", &level);
	if (level <= 0||level>=4) level = 1; 
	clear();
	refresh();  
	Zone zone(goalWidth);
	zone.initialize();
	Slider player1(1, sliderSize);
	Slider player2(2, sliderSize);
	Ball ball(goalWidth);
	int player1Score = 0, player2Score = 0;
	bool paused = false;
	time_t startTime=time(NULL);
	int speed = (level == 1) ? EASY_SPEED : (level == 2) ? MEDIUM_SPEED : HARD_SPEED;
	vector<Obstacle> obstacles;
	if (level == 3) {
		for (int i = 0; i < MAX_OBSTACLES; ++i) {
			obstacles.emplace_back(rand() % COLS, rand() % LINES);
		}
	}
	while (true) {
		time_t currentTime = time(NULL);
		double elapsedTime = difftime(currentTime, startTime);
		double remainingTime = GAME_DURATION - elapsedTime;
		if (remainingTime <= 0) {
			endwin();
			cout << "Time's up! Game Over!\n";
			cout << "Player 1: " << player1Score << "\n";
			cout << "Player 2: " << player2Score << "\n";
			cout << "Winner: " << (player1Score > player2Score ? "Player 1" : "Player 2") << "\n";
			return 0;}
		if (!paused) {
			zone.draw();
			player1.draw();
			player2.draw();
			ball.draw();
			for (auto& obs : obstacles) obs.draw();
			int ch=getch();
			if(ch=='q'||ch=='Q')break;
			switch (ch) {
				case KEY_LEFT: player1.moveLeft(); break;
				case KEY_RIGHT: player1.moveRight(); break;
				case KEY_UP: player1.moveUp(); break;
				case KEY_DOWN: player1.moveDown(); break;
				case 'w': player2.moveUp(); break;
				case 'a': player2.moveLeft(); break;
				case 's': player2.moveDown(); break;
				case 'd': player2.moveRight(); break;
				case 'p': case 'P': paused = !paused; break;
			}

			if (ball.update(player1, player2, obstacles)) {
				if (ball.getLastTouchedBy() == 1) ++player1Score;
				else if(ball.getLastTouchedBy()==2) ++player2Score;
			}

			mvprintw(0, 0, "Player 1: %d  Player 2: %d", player1Score, player2Score);
			mvprintw(1, 0, "Remaining time: %.0f seconds", remainingTime);
			refresh();
			usleep(speed * 1000);
		}
		else {
			int ch = getch();
			if (ch == 'p' || ch == 'P') paused = !paused;
			if(ch=='q'||ch=='Q')break;
		}
	}
	attroff(COLOR_PAIR(1));
	endwin();
	cout << "Game Over!\n";
	cout << "Player 1: " << player1Score << "\n";
	cout << "Player 2: " << player2Score << "\n";
	if(player1Score==player2Score) cout<<"dead heat"<<"\n";
	else {cout << "Winner: " << (player1Score > player2Score ? "Player 1" : "Player 2") << "\n";}

vector<int> bestScores;
ifstream inputFile("./saves/save_best_10.game");
if (inputFile.is_open()) {
	int score;
	while (inputFile >> score) bestScores.push_back(score);
	inputFile.close();
}
bestScores.push_back(max(player1Score, player2Score));
sort(bestScores.begin(), bestScores.end(), greater<int>());
if (bestScores.size() > 10) bestScores.resize(10);

ofstream outputFile("./saves/save_best_10.game");
for (int score : bestScores) {
	outputFile << score << "\n";
}
outputFile.close();

return 0;
}
