#ifndef GPS_H
#define GPS_H

enum direction{
forward,
left,
right,
backward
}

typedev struct GPS_node{
	int max_speed;
	direction dir;
	int distance;
};

int aantal_nodes;
GPS_node* track;
	
#endif
