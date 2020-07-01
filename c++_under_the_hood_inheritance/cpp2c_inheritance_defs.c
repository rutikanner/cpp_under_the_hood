//
// Created by ruti on 6/16/20.
//
#include "stdio.h"
#include "cpp2c_inheritance_defs.h"

void physical_box_ctorddd(Physical_box* const this, double l, double w, double h)
{
    box_ctorddd((Box*)this, l, w, h);
    this -> material.material = OTHER;
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("Material created, set to %s\n", names[this -> material.material]);//TODO replace names[...] to Other
    physical_box_printp(this);
}

void physical_box_ctordddTypes(Physical_box * const this, double l, double w, double h, Types t)
{
    box_ctorddd((Box*)this, l, w, h);
    this -> material.material = t;
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("Material created, set to %s\n", names[this -> material.material]);
    physical_box_printp(this);
}

void physical_box_ctorTypes(Physical_box * const this, Types t)
{
    box_ctorddd((Box*)this,1, 1, 1);
    this -> material.material = t;
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("Material created, set to %s\n", names[this -> material.material]);
    physical_box_printp(this);
}

void physical_box_dtor(Physical_box * const this)
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("PhysicalBox dtor, %f x %f x %f, %s; ", this->box.length, this->box.width, this->box.height, names[this -> material.material]);
    box_dtor((Box*)this);
}

void physical_box_printp(const Physical_box * const this)
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("PhysicalBox, made of %s; ", names[this -> material.material]);
    box_print((Box*)this);
}

void weight_box_ctordddd(Weight_box* const this, double l, double w, double h, double wgt)
{
    box_ctorddd((Box*)this,l,w,h);
    this->weight = wgt;
    weight_box_printw(this);
}

void weight_box_ctorW(Weight_box* const this, const Weight_box* other)
{
    box_ctorddd((Box*)this,1,1,1);
    this->weight = other->weight;
    weight_box_printw(this);

}

void weight_box_dtor(Weight_box* const this)
{
    printf("Destructing WeightBox; ");
    weight_box_printw(this);
    box_dtor((Box*)this);
}

Weight_box* weight_box_operator_equel(Weight_box* const this, const Weight_box* const other)
{
    this->weight = other->weight;
    return this;
}

void weight_box_printw(const Weight_box* const this)
{
    printf("WeightBox, weight: %f; ", this->weight);
    box_print((Box*)this);

}