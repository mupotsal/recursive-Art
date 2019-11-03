/* Authors: Liberty Mupotsa
   Python version of Sierpinski's triangle by Jan Pearce; Conversion to C++ by Jesse W. Walker
   C-Turtle by Jesse  W.  Walker, Getrandom by Jan Pearce
*/

#include "CTurtle.hpp"   //This brings in the CTurtle library for use
#include <iostream> //for input & output
#include <random> //needed for Getrandom
#include <chrono> //needed for Getrandom's seed
#include <cmath>
namespace ct = cturtle;  //This makes it possible to use the CTurtle commands using ct::
using namespace std;

// The screen is defined below and is the one used by all turtles in the drawings
ct::TurtleScreen scr; //makes screen
ct::Turtle mand(scr);

class Getrandom {
	/** Uses <random> and <chrono> from C++11 to return a random integer in range [1..size] */
public:
	Getrandom(int size) {
		auto seed = chrono::system_clock::now().time_since_epoch().count(); //gets a new seed for the randomness
		default_random_engine generator(seed);			//seeds our randomness
		uniform_int_distribution<int> intdist(1, size); //a distibution to make each in-range integer equally likely
		self_rand_int_ = intdist(generator);			//generates the randme number
	}
	int roll() {
		return self_rand_int_;
	}
private:
	int self_rand_int_;
};


void draw_triangle(ct::Point a, ct::Point b, ct::Point c, ct::Color color, ct::Turtle& myTurtle) {
	myTurtle.fillcolor(color);
	myTurtle.penup();
	myTurtle.goTo(a.x, a.y);
	myTurtle.pendown();
	myTurtle.begin_fill();
	myTurtle.goTo(c.x, c.y);
	myTurtle.goTo(b.x, b.y);
	myTurtle.goTo(a.x, a.y);
	myTurtle.end_fill();
}


void mondrain(int minX, int maxX, int minY, int maxY, ct::Turtle& turtle) {
	const std::string colormap[] = { "blue", "red", "green", "white" };
	Getrandom randcolor(3);

	int randval = randcolor.roll();
	int randx = rand() % (maxX - minX + 1) + minX;
	int randy = rand() % (maxY - minY + 1) + minY;

	turtle.fillcolor(colormap[randval]);
	turtle.penup();
	turtle.goTo(minX, maxY);
	turtle.pendown();
	turtle.begin_fill();
	turtle.goTo(maxX, maxY);
	//turtle.end_fill();
	turtle.goTo(maxX, minY);
	turtle.goTo(minX, minY);
	

	if ((maxX - minX) > 400 && (maxY - minY) > 300) {
		mondrain(minX, randx, randy, maxY, turtle);
		mondrain(randx, maxX, randy, maxY, turtle);
		mondrain(randx, maxX, minY, randy, turtle);
		mondrain(minX, randx, minY, randy, turtle);
	}
	else if ((maxX - minX) > 400) {
		mondrain(minX, randx, minY, maxY, turtle);
		mondrain(randx, maxX, minY, maxY, turtle);
	}
	else if ((maxY - minY) > 300) {
		mondrain(minX, maxX, randy, maxY, turtle);
		mondrain(minX, maxX, minY, randy, turtle);
	}
	else if ((maxX - minX) > 150 && (maxY - minY) > 100) {
		mondrain(minX, randx, randy, maxY, turtle);
		mondrain(randx, maxX, randy, maxY, turtle);
		mondrain(randx, maxX, minY, randy, turtle);
		mondrain(minX, randx, minY, randy, turtle);
	}
	else if ((maxX - minX) > 150) {
		mondrain(minX, randx, minY, maxY, turtle);
		mondrain(randx, maxX, minY, maxY, turtle);

	}
	else if ((maxY - minY) > 100) {
		mondrain(minX, maxX, randy, maxY, turtle);
		mondrain(minX, maxX, minY, randy, turtle);
	}
	else {
		turtle.penup();		
		turtle.begin_fill();
		turtle.goTo(minX, maxY);
		turtle.pendown();			
		turtle.goTo(maxX, maxY);		
		turtle.goTo(maxX, minY);		
		turtle.goTo(minX, minY);
		turtle.goTo(minX, maxY);
		turtle.end_fill();
		

	}
}


int main() {
	int min_X = -400;
	int max_X = 400;
	int min_Y = -300;
	int max_Y = 300;
	ct::TurtleScreen scr; //makes screen
	ct::Turtle rt(scr);   //makes Turtle on screen

	mondrain(min_X, max_X, min_Y, max_Y, rt);


	Getrandom newrandom(4);

	//graphing commands go below here
	ct::Point myPoints[] = { {-200, -100}, {0, 200}, {200, -100} };
	//sierpinski(myPoints[0], myPoints[1], myPoints[2], newrandom.roll(), rt);

	scr.exitonclick();  //exists graphics screen
	return 0;
}