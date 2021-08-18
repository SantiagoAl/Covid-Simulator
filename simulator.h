// Contains general defines for the simulator

#ifndef SIMULATOR_H
#define SIMULATOR_H

// physical limites to the simulated space
#define X_LIMIT 5000
#define Y_LIMIT 5000

// general simulation parameters
#define SIM_HOURS 5000
#define NUM_PEOPLE 1000

// stages of the disease
enum disease_status { VULNERABLE, INFECTED, IMMUNE, DEAD };

// How many hours the infection lasts
#define INFECTION_TIME (24 * 20)

// Likelihood of infection when exposed
#define INFECTION_PROBABILITY 0.5

// Disease dynamics
#define NORMAL_FATAILITY_RATE 0.01 // You can get medical help
#define SATURATED_FATALITY_RATE 0.06 // You can't get medical attention
#define INFECTION_PROXIMITY 5.0 // How close for transmission
#define INITIAL_INFECTIONS 5

// How many sick people at a time can the health system
// can handle, before saturating
#define SATURATION_THRESHOLD (NUM_PEOPLE / 5)

// is the system saturated?
extern bool saturated;

// Roll the dice, return true if the even occured, false otherwise
bool try_event(double probability);

#endif // SIMULATOR_H