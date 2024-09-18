# Wind Farm Simulation Project

## Project Overview

This project simulates the production of a wind farm under varying wind conditions. The aim is to model the behavior of wind turbines and their energy output, as well as account for potential malfunctions and maintenance costs due to high wind speeds. The simulation runs over a set time period (e.g., one year) and provides key results such as total energy production, daily output, and maintenance expenses.

## Features

- **Wind Speed Modeling**: Wind speed varies daily and follows a predefined transition matrix. There are three wind speed states: no wind, medium wind, and strong wind.
- **Energy Production**: Each turbine produces energy based on wind speed:
  - No wind: 0 MW
  - Medium wind: 0.4 MW
  - Strong wind: 0.65 MW
- **Turbine Failures**: If wind speed is strong, turbines have a 15% chance of failure. Failed turbines undergo a 3-day maintenance period, during which they do not produce energy.
- **Maintenance Costs**: Maintenance for each turbine failure costs 150,000 € and cannot proceed when the wind is strong.

## Data Structure

The simulation is based on a linked list structure, `ListeParc`, which represents the wind farm over time. Each node in `ListeParc` corresponds to one day in the simulation and is represented by a `ParcEo`. The `ParcEo` nodes contain the following attributes:
- **Day**: The specific day of the simulation.
- **Wind Speed**: The wind speed on that day.
- **Next Park**: A pointer to the next `ParcEo` in the list, which corresponds to the next day.
- **ListeEolienneCourante**: A linked list of wind turbines operating on that day.

Within each `ParcEo`, there is another linked list representing the turbines in the wind farm. Each node in this list is an individual wind turbine, with the following attributes:
- **Turbine Number**: A unique identifier for each wind turbine.
- **State**: The operational state of the turbine (e.g., working or under repair).
- **Repair Time**: The number of days remaining for repair if the turbine is under maintenance.
- **Next Turbine**: A pointer to the next turbine in the list.

This linked list structure allows the simulation to easily iterate over the days and turbines, updating wind conditions, production levels, and maintenance statuses accordingly.

## Data Parameters

The following key parameters can be adjusted to observe their influence on the wind farm's performance:
- Wind speed transition matrix (`V`):
  ```txt
  V = [0.2 0.73 0.07]
      [0.11 0.74 0.15]
      [0.04 0.61 0.35]
- Failure probability (p = 0.15) under strong wind.
- Production levels for different wind speeds: [0, 0.4, 0.65] MW.
- Maintenance duration: 3 days
- Maintenance cost: 150 k€

## Simulation Objectives


The goal of this simulation is to:

- Calculate total energy production over the given time period (e.g., one year).
- Track daily maximum and minimum production levels.
- Measure maintenance costs and downtime due to turbine failures.
- Provide a flexible and modular framework for adjusting wind farm parameters.



## Future Improvements
- Add a graphical representation of production data over time.
- Extend the simulation to account for different weather patterns and seasonal variations in wind speed.
- Introduce variable maintenance costs depending on the severity or frequency of turbine failures.


