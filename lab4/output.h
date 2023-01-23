/* Julia Pittner */

#include "structs.h"

#ifndef OUTPUT_H
#define OUTPUT_H

int ok_to_print(double ET, double delta_time);

void print_alien_header(struct Sim *sim_ptr);

void print_alien(void *alien);

void draw_alien(struct Sim *sim_ptr);

void master_output(struct Sim *sim_ptr);

void final_output(struct Sim *sim_ptr);

void text_output(struct Sim *sim_ptr); 

void graphic_output(struct Sim *sim_ptr);

void display_alien(void *data);

void base_and_bolt(double ET, double delta_time);

void keep_drawing(struct Sim *sim_ptr);
#endif
