 /* Authors: Liberty Mupotsa
    Python version of Sierpinski's triangle by Jan Pearce; Conversion to C++ by Jesse W. Walker
	C-Turtle by Jesse  W.  Walker, Getrandom by Jan Pearce

 */

#include "CTurtle.hpp"   //This brings in the CTurtle library for use
#include <iostream> //for input & output
#include <random> //needed for Getrandom
#include <chrono> //needed for Getrandom's seed
namespace ct = cturtle;  //This makes it possible to use the CTurtle commands using ct::
using namespace std;

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


void draw_triangle(ct::Point a, ct::Point b, ct::Point c, ct::Color color, ct::Turtle& myTurtle){
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
class MondrianArt {

public:
	MondrianArt();
		// Constructor should initialize instance variables.
		// This may include a list of colors you can use, e.g {“white”, “blue”, “red”, “yellow”}

		void  setup_turtle() {
		}
		// Moves the turtle to the top left hand side of the screen (goTo -400, -300

		void mondrian() {
		}
		// The recursive mondrian function that holds all the steps found above.


		void reset() {

		}
		// Optional. You can use this to keep creating pieces of art until you find one you like!
		// e.g, turtle.reset()

private:
	string colorList[];
	turtleScreen;
	turtle(must be constructed with turtleScreen);
};


//getMid already defined as "middle" function in C-Turtle namespace :)

void sierpinski(ct::Point a, ct::Point b, ct::Point c, int degree, ct::Turtle& myTurtle){
    const std::string colormap[] = {"blue", "red", "green", "white", "yellow", "violet", "orange"};
    draw_triangle(a,b,c, {colormap[degree]}, myTurtle);
    if(degree > 0){ // The base case is 0. When the degree is less than one then the recursion stops.
        sierpinski(a, ct::middle(a, b), ct::middle(a, c), degree - 1, myTurtle);
        sierpinski(b, ct::middle(a, b), ct::middle(b, c), degree - 1, myTurtle);
        sierpinski(c, ct::middle(c, b), ct::middle(a, c), degree - 1, myTurtle);
    }
}

int main() {
    ct::TurtleScreen scr; //makes screen
    ct::Turtle rt(scr);   //makes Turtle on screen

	Getrandom newrandom(4);
    
	//graphing commands go below here
    ct::Point myPoints[] = {{-200, -100}, {0, 200}, {200, -100}};
    sierpinski(myPoints[0], myPoints[1], myPoints[2], newrandom.roll(), rt);
    
    scr.exitonclick();  //exists graphics screen
    return 0;
}
