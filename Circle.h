#ifndef _CIRCLE_
#define _CIRCLE_

/** Represents a Circle */
class Circle {
public:
	int x; /**< x-coordinate of the centre of Circle */
	int y; /**< y-coordinate of the centre of Circle */
	int radius; /**< radius of the Circle */
	/** Default constructor */
	Circle();

	/** 3-argument constructor
		@param xcoord integer assigned to the state variable x of the Circle
		@param ycoord integer assigned to the state variable y of the Circle
		@param r integer assigned to the state variable radius of the Circle */
	Circle(int xcoord, int ycoord, int r);

	/** obtains radius of the Circle
		@return The state variable radius of the Circle */
	int getRadius();

	/** obtains x-coordinate of the centre of the Circle
		@return The state varialbe x of the Circle*/
	int getX();

	/** obtains y coordinate of the centre of the Circle
		@return The state variable y of the Circle */
	int getY();

	/** draw this Circle */
	void draw();
};

#endif // _CIRCLE_