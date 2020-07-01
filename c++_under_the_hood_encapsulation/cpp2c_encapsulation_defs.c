#include "stdio.h"
#include "cpp2c_encapsulation_defs.h"

//const char* const DEF_MSG = "The total volume held on the shelf is";
char* message = "The total volume held on the shelf is";


/*Box*/

void box_ctord(Box* const this, double dim){
    this->length = dim;
    this->height = dim;
    this-> width = dim;
    box_print(this);
}

void box_ctorddd(Box * const this,double l, double w, double h){
    this->length = l;
    this->height = h;
    this-> width = w;
    box_print(this);
}

void box_dtor(Box* const this){
    printf("Box destructor, %f x %f x %f\n", this->width,this->height,this->length);
}


void box_print(const Box* const this){
    printf("Box: %f x %f x %f\n", this->length, this->width, this->height);
}

Box* box_operator_mult_equal(Box* const this,double mult)
{
    this->width *= mult;
    this->height *= mult;
    this->length *= mult;
    return this;
}

/*Shelf*/


void shelf_set_box(Shelf* const this, int index, const Box *dims)
{
    this->boxes[index] = *dims;
}


double shelf_get_volume(const Shelf* const this){
    double vol = 0;
    size_t i;
    for (i= 0; i < NUM_BOXES; ++i)
        vol += (this->boxes[i].width * this->boxes[i].length * this->boxes[i].height);
    return vol;
}

void shelf_print(const Shelf* const this){
    printf("%s %f\n", message, shelf_get_volume(this));
}
