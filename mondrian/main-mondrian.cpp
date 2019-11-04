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


void draw_triangle(ct::Point a, ct::Point b, ct::Point c, ct::Color color, ct::Turtle& mond_turtle) {
	mond_turtle.fillcolor(color);
	mond_turtle.penup();
	mond_turtle.goTo(a.x, a.y);
	mond_turtle.pendown();
	mond_turtle.begin_fill();
	mond_turtle.goTo(c.x, c.y);
	mond_turtle.goTo(b.x, b.y);
	mond_turtle.goTo(a.x, a.y);
	mond_turtle.end_fill();
}

void draw_rectangle(int minX, int maxX, int minY, int maxY, ct::Turtle& mond_turtle) { // drawing the screen rectangle.
	mond_turtle.penup();
	mond_turtle.goTo(minX, minY);
	mond_turtle.pendown();
	mond_turtle.goTo(minX, maxY);
	mond_turtle.goTo(maxX, maxY);
	mond_turtle.goTo(maxX, minY);
	mond_turtle.goTo(minX, minY);
	mond_turtle.penup();
	mond_turtle.goTo(maxX / 2, minY);
	mond_turtle.pendown();
	mond_turtle.goTo(maxX / 2, maxY);




}

void mondrain(int minX, int maxX, int minY, int maxY, ct::Turtle& mond_turtle) {
	const std::string colormap[] = { "white", "red", "green","white","yellow","blue"};
	Getrandom randcolor(5);

	int randval = randcolor.roll();
	int randx = rand() % (maxX - minX + 1) + minX;
	int randy = rand() % (maxY - minY + 1) + minY;

	mond_turtle.fillcolor(colormap[randval]);
	mond_turtle.width(3);
	mond_turtle.speed(0);	
	mond_turtle.penup();
	mond_turtle.begin_fill();
	mond_turtle.goTo(minX, maxY);
	mond_turtle.pendown();	
	mond_turtle.goTo(maxX, maxY);	
	mond_turtle.penup();
	mond_turtle.goTo(maxX, minY);
	mond_turtle.pendown();
	mond_turtle.goTo(minX, minY);
	mond_turtle.end_fill();

	

	

	 if ((maxX - minX) > 400 && (maxY - minY) > 300) { // The screen size is 800 by 600 so when the width >400 and height > 300 this runs
		mondrain(minX, randx, randy, maxY, mond_turtle);
		mondrain(randx, maxX, randy, maxY, mond_turtle);
		mondrain(randx, maxX, minY, randy, mond_turtle);
		mondrain(minX, randx, minY, randy, mond_turtle);
		
	 }
	
	else if ((maxX - minX) > 400) { // When the region is greater than 400 (width)
		 mond_turtle.width(3);
		mondrain(minX, randx, minY, maxY, mond_turtle);
		mondrain(randx, maxX, minY, maxY, mond_turtle);
	}
	else if ((maxY - minY) > 300) { // when the height is greater than 300
		mondrain(minX, maxX, randy, maxY, mond_turtle);
		mondrain(minX, maxX, minY, randy, mond_turtle);
	}
	else if ((maxX - minX) > 150 && (maxY - minY) > 100) { // another random conditon chosen to break the region
		 mond_turtle.width(5);
		mondrain(minX, randx, randy, maxY, mond_turtle);
		mondrain(randx, maxX, randy, maxY, mond_turtle);
		mondrain(randx, maxX, minY, randy, mond_turtle);
		mondrain(minX, randx, minY, randy, mond_turtle);
	}
	else if ((maxX - minX) > 100) { // this runs when the region is wide enough to split.
		mondrain(minX, randx, minY, maxY, mond_turtle);
		mondrain(randx, maxX, minY, maxY, mond_turtle);

	}
	else if ((maxY - minY) > 50) { // When the height is tall enough to split.
		mondrain(minX, maxX, randy, maxY, mond_turtle);
		mondrain(minX, maxX, minY, randy, mond_turtle);

	 }
	else if ((maxX - minX) > 10 && (maxY - minY) >20) { // When the height is tall enough to split.
		 mondrain(minX, maxX, randy, maxY, mond_turtle);
		mondrain(minX, maxX, minY, randy, mond_turtle);
	}
	else {
		mond_turtle.penup();		
		mond_turtle.begin_fill();
		mond_turtle.goTo(minX, maxY);
		mond_turtle.pendown();			
		mond_turtle.goTo(maxX, maxY);		
		mond_turtle.goTo(maxX, minY);		
		mond_turtle.goTo(minX, minY);
		mond_turtle.goTo(minX, maxY);
		mond_turtle.end_fill();
		

	}
}


int main() {
	int min_X = -400;
	int max_X = 400;
	int min_Y = -300;
	int max_Y = 300;
	ct::TurtleScreen scr; //makes screen
	ct::Turtle rt(scr);   //makes Turtle on screen
	draw_rectangle(-400, 400, -300, 300,rt);
	//rt.penup();
	mondrain(min_X, max_X, min_Y, max_Y, rt);
	//scr.bgcolor({ "black" });

	Getrandom newrandom(4);

	//graphing commands go below here
	ct::Point myPoints[] = { {-200, -100}, {0, 200}, {200, -100} };
	//sierpinski(myPoints[0], myPoints[1], myPoints[2], newrandom.roll(), rt);

	scr.exitonclick();  //exists graphics screen
	return 0;
}