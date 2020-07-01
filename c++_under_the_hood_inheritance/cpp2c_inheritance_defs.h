//
// Created by ruti on 6/16/20.
//

#ifndef C___UNDER_THE_HOOD_CPP2C_INHERITANCE_DEFS_H
#define C___UNDER_THE_HOOD_CPP2C_INHERITANCE_DEFS_H
#include "cpp2c_encapsulation_defs.h"

//// Materials ////////////

typedef enum Types
{
    PLASTIC,
    METAL,
    WOOD,
    PAPER,
    OTHER
}Types;

typedef struct Materials Materials;

struct Materials//TODO add char
{
    char a;
};

typedef struct Material_t Material_t;

struct Material_t
{
    Types material;
};

//// PhysicalBox ////////////

typedef struct Physical_box Physical_box;

struct Physical_box
{
    Box box;
    Material_t material;
};

void physical_box_ctorddd(Physical_box * const this, double l, double w, double h);

void physical_box_ctordddTypes(Physical_box * const this, double l, double w, double h, Types t);

void physical_box_ctorTypes(Physical_box * const this, Types t);

void physical_box_dtor(Physical_box * const this);

void physical_box_printp(const Physical_box * const this);

//// WeightBox ////////////

typedef struct Weight_box Weight_box;

struct Weight_box
{
    Box box;
    double weight;
};

void weight_box_ctordddd(Weight_box* const this, double l, double w, double h, double wgt);

void weight_box_ctorW(Weight_box* const this, const Weight_box* other);

Weight_box* weight_box_operator_equel(Weight_box* const this, const Weight_box* const other);

void weight_box_printw(const Weight_box* const this);

void weight_box_dtor(Weight_box* const this);

#endif //C___UNDER_THE_HOOD_CPP2C_INHERITANCE_DEFS_H
