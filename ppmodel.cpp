#include "ppmodel.h"
#include "Location.h"
#include "simulator.h"
#include "person.h"
#include <stdlib.h>

static Location popularPlaces[NUM_POPULAR_PLACES];

PopularPlacesModel::PopularPlacesModel() : MobilityModel()
{
	speed = -1;
	home = new Location();

	if (try_event(DISTANCING_PROBABILITY))
	{
		// Some distancing going on here
		home_probability = DISTANCING_HOME_PROBABILITY;
	}
	else
	{
		// Not so keen on the distancing here
		home_probability = NOT_DISTANCING_HOME_PROBABILITY;
	}
}

void PopularPlacesModel::move()
{
	if (speed < 0)
	{
		person->location.setX(home->getX());
		person->location.setY(home->getY());
		pick_new_waypoint();
	}
	else if (person->location.at_location(*waypoint))
	{
		stay--;
		if (stay <= 0)
			pick_new_waypoint();
	}
	else
	{
		person->location.move_toward(*waypoint, speed);
	}
}

void PopularPlacesModel::pick_new_waypoint()
{
	speed = arc4random_uniform(PP_TOP_SPEED) + 1;
	stay = arc4random_uniform(MAX_STAY);

	if (try_event(home_probability))
	{
		waypoint = home;
	}
	else
	{
		// Pick a random popular place and go there.
		int place = arc4random_uniform(NUM_POPULAR_PLACES);
		waypoint = &(popularPlaces[place]);
	}
}