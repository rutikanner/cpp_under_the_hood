#ifndef C___UNDER_THE_HOOD_CPP2C_ENCAPSULATION_DEFS_H
#define C___UNDER_THE_HOOD_CPP2C_ENCAPSULATION_DEFS_H

#include <stdbool.h>
#define NUM_BOXES 3

/*Box*/

typedef struct Box Box;

struct Box{
    double length;
    double width;
    double height;
};

void box_ctord(Box* const this, double dim);

void box_ctorddd(Box* const this,double l, double w, double h);

void box_dtor(Box* const this);

void box_print(const Box* const this);

Box* box_operator_mult_equal(Box* const this,double mult);

/*Shelf*/

typedef struct Shelf Shelf;

struct Shelf{

    Box boxes[NUM_BOXES];

};

double shelf_get_volume(const Shelf* const this);

void shelf_set_box(Shelf* const this, int index, const Box *dims);

void shelf_print(const Shelf* const this);


#endif /*C___UNDER_THE_HOOD_CPP2C_ENCAPSULATION_DEFS_H*/
