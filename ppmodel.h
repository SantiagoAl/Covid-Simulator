#ifndef PPMODEL_H
#define PPMODEL_H

#include "mobility_model.h"

class Location;

#define NUM_POPULAR_PLACES 15

// Fraction of the people practicing distancing
#define DISTANCING_PROBABILITY 0.8

// Home probabilities for those distancing and those not
#define DISTANCING_HOME_PROBABILITY 0.997
#define NOT_DISTANCING_HOME_PROBABILITY 0.2

// The maximum speed a person can move
#define PP_TOP_SPEED 20

// Maximum time a person will stay at a place
#define MAX_STAY 4

class PopularPlacesModel : MobilityModel
{
private:
	Location *waypoint;
	Location *home;
	int speed, stay;
	double home_probability;

public:
	PopularPlacesMode();

	void pick_new_waypoint();
	void move();
};

#endif // PP_MODEL_H