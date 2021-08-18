#include <iostream>
#include <math.h>
#include <assert.h>

#include "simulator.h"
#include "person.h"
#include "location.h"
#include <stdlib.h>
#include "ui.h"

using namespace std;

bool saturated = false;

bool try_event(double probability)
{
	assert(probability >= 0.0 && probability <= 1.0);
	// probably doesn't matter what this is, as long as it is big
	const int resolution = 100000; 

	double rnum = arc4random_uniform(resolution);
	rnum = rnum / (double)resolution;

	return rnum <= probability;
}

int sim_main()
{
	// Set up the simulation
	Person people[NUM_PEOPLE];
	int infection_history[SIM_HOURS];

	// zero out the history
	memset(infection_history, 0, sizeof(infection_history));

	// initial infections
	for (int i = 0; i < INITIAL_INFECTIONS; i++)
	{
		people[i].status = INFECTED;
	}

	int max_infected_at_once = 0;

	for (int i = 0; i < SIM_HOURS; i++)
	{
		// Re-draw the UI, so you can see it happen
		if ((i % 2) == 0)
		{
			ui_redraw(people, NUM_PEOPLE, infection_history, SIM_HOURS);
		}

		// Move people
		for (int p = 0; p < NUM_PEOPLE; p++)
		{
			if (people[p].is_alive())
			{
				people[p].mobility_model->move();
				people[p].progress_disease();
			}
		}

		// Try to infect
		for (int p = 0; p < NUM_PEOPLE; p++)
		{
			if (people[p].is_alive())
			{
				for (int p2 = 0; p2 < NUM_PEOPLE; p2++)
				{
					if (p != p2 && people[p2].is_alive())
					{
						people[p].try_infect(people[p2]);
					}
				}
			}
		}

		// Report status
		int num_infected = 0;
		int num_immune = 0;
		int num_dead = 0;
		int num_vulnerable = 0;

		for (int p = 0; p < NUM_PEOPLE; p++)
		{
			if (!people[p].is_alive())
			{
				num_dead++;
			}

			if (people[p].status == INFECTED)
			{
				num_infected++;
			}

			if (people[p].status == VULNERABLE)
			{
				num_vulnerable++;
			}
		}

		if (num_infected > max_infected_at_once)
		{
			max_infected_at_once = num_infected;
		}

		// Set whether or not the medical system is currently saturated
		saturated = (num_infected > SATURATION_THRESHOLD);

		if ((i % 10) == 0 || num_infected == 0)
		{
			cout << num_vulnerable << "\t" << num_infected << "\t" << num_immune
				<< "\t" << num_dead << "\t" << (num_dead * 100.0 / NUM_PEOPLE) << endl;
		}
		
		infection_history[i] = num_infected;
		
		if (num_infected == 0) break;
	}

	cout << "Peak infections - " << max_infected_at_once << endl;
}

int main(void)
{
	return start_ui(sim_main);
}