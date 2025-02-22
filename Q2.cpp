#include <iostream>
#include <string>
using namespace std;

class Ball {
private:
    int x, y;
public:
    Ball(int x = 0, int y = 0) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void resetBall() {
        x = 0;
        y = 0;
    }

    void getPosition() const {
        cout << "(" << x << ", " << y << ")";
    }
};

class Goal {
private:
    int x, y;
public:
    Goal(int x, int y) : x(x), y(y) {}

    bool isGoalReached(int ballX, int ballY) const {
        return (x == ballX && y == ballY);
    }
};

class Robot {
private:
    string name;
    int hits;
public:
    Robot(string name) : name(name), hits(0) {}

    int getHits() const { return hits; }

    void hitBall(Ball &ball, const string &direction) {
        hits++;
        if (direction == "up") ball.move(0, 1);
        else if (direction == "down") ball.move(0, -1);
        else if (direction == "left") ball.move(-1, 0);
        else if (direction == "right") ball.move(1, 0);
        else {
            hits--;
            cout << "Invalid direction!" << endl;
        }
    }
};

class Team {
private:
    string teamName;
    Robot robot;
public:
    Team(string name, Robot robot) : teamName(name), robot(robot) {}

    Robot &getRobot() { return robot; }
    string getTeamName() const { return teamName; }
};

class Game {
private:
    Team teams[2];
    Ball ball;
    Goal goal;
public:
    Game(Team t1, Team t2, Ball ball, Goal goal)
        : teams{t1, t2}, ball(ball), goal(goal) {}

    void startGame() {
        int turn = 0;
        while (!goal.isGoalReached(ball.getX(), ball.getY())) {
            play(teams[turn]);
            turn = 1 - turn;
        }
        cout << teams[turn].getTeamName() << " Goaled :)" << endl;
        ball.resetBall();
    }

    void play(Team &team) {
        string direction;
        cout << "Enter direction (left, right, up, down) for "
             << team.getTeamName() << " ";
        ball.getPosition();
        cout << ": ";
        cin >> direction;
        team.getRobot().hitBall(ball, direction);
    }

    void declareWinner() {
        int hits1 = teams[0].getRobot().getHits();
        int hits2 = teams[1].getRobot().getHits();

        cout << teams[0].getTeamName() << " Hits: " << hits1 << endl;
        cout << teams[1].getTeamName() << " Hits: " << hits2 << endl;

        if (hits1 < hits2)
            cout << "Team " << teams[0].getTeamName() << " Won!" << endl;
        else if (hits1 > hits2)
            cout << "Team " << teams[1].getTeamName() << " Won!" << endl;
        else
            cout << "TIE" << endl;
    }
};

int main() {
    Robot roboAdeel("Adeel");
    Robot roboMuaz("Muaz");
    Team team1("Adeel", roboAdeel);
    Team team2("Muaz", roboMuaz);
    Goal goal(3, 3);
    Ball ball(0, 0);
    Game game(team1, team2, ball, goal);

    game.startGame();
    game.declareWinner();

    return 0;
}

