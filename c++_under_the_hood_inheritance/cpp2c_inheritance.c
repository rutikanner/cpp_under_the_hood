#include "stdio.h"
#include "cpp2c_inheritance_defs.h"
static Box largeBox;

void doMaterials()
{
    printf("\n--- Start doMaterials() ---\n\n");

    Materials mat;
    printf("Size of Materials: %lu\n", sizeof(Materials));
    printf("Size of mat: %lu\n", sizeof(Materials));
    printf("Size of Materials::Types: %lu\n", sizeof(Types));
    printf("Size of Material_t: %lu\n", sizeof(Material_t));

    struct MatTest{ Materials mat; Material_t mat_t; };
    printf("Size of Materials + Material_t: %lu\n", sizeof(struct MatTest));

    Material_t mat1;
    mat1.material = OTHER;
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("Material created, set to %s\n", names[mat1.material]);
    Material_t mat2;
    mat2.material = METAL;
    printf("Material created, set to %s\n", names[mat2.material]);

    printf("\n--- End doMaterials() ---\n\n");
}

void doPhysicalBox()
{
    printf("\n--- Start doPhysicalBox() ---\n\n");

    Physical_box pb1;
    physical_box_ctordddTypes(&pb1,8, 6, 4, PLASTIC);
    Physical_box pb2;
    physical_box_ctorTypes(&pb2,WOOD);
    Physical_box pb3;
    physical_box_ctorddd(&pb3,7, 7, 7);

    printf("\npb4 is copy-constructed from pb1\n");
    Physical_box pb4;
    pb4 = pb1;
    physical_box_printp(&pb4);
    physical_box_printp(&pb1);
//    printf("pb4 %s pb1\n",(((const Box*)&pb4.width) == ((const Box*)&pb1.width) && (Box*)&pb4.length == (Box*)&pb1.length && (Box*)&pb4.height == (Box*)&pb1.height)&& pb4.material.material == pb1.material.material? "equals" : "does not equal");

    printf("\npb4 is copy-assigned from pb3\n");
    pb4 = pb3;
    physical_box_printp(&pb4);
    physical_box_printp(&pb3);
//    printf("pb4 %s pb3\n", (((const Box*)&pb4 == (const Box*)&pb3) && (pb4.material.material) == (pb3.material.material)) ? "equals" : "does not equal");
    printf("\n--- End doPhysicalBox() ---\n\n");
    physical_box_dtor(&pb4);
    physical_box_dtor(&pb3);
    physical_box_dtor(&pb2);
    physical_box_dtor(&pb1);

}

void doWeightBox()
{
    printf("\n--- Start doWeightBox() ---\n\n");

    Weight_box pw1;
    weight_box_ctordddd(&pw1,8, 6, 4, 25);
    Weight_box pw2;
    weight_box_ctordddd(&pw2,1, 2, 3,0.0);
    Weight_box pw3;
    weight_box_ctordddd(&pw3,10, 20, 30, 15);

    printf("\npw4 is copy-constructed from pw1\n");
    Weight_box pw4;
//    box_ctorddd((Box*)&pw4, 1, 1, 1);
    weight_box_ctorW(&pw4, &pw1);
    weight_box_printw(&pw4);
    weight_box_printw(&pw1);
//    printf("pw4 %s pw1\n", (const Box*)&pw4 == (const Box*)&pw1 && pw4.weight == pw1.weight ? "equals" : "does not equal");

    printf("\npw4 is copy-assigned from pw3\n");
    weight_box_operator_equel(&pw4,&pw3);
    weight_box_printw(&pw4);
    weight_box_printw(&pw3);

//    printf("pw4 %s pw3\n", (const Box*)&pw4 == (const Box*)&pw3 && pw4.weight == pw3.weight ? "equals" : "does not equal");

    printf("\n--- End doWeightBox() ---\n\n");
    weight_box_dtor(&pw4);
    weight_box_dtor(&pw3);
    weight_box_dtor(&pw2);
    weight_box_dtor(&pw1);
}



int main()
{
    box_ctorddd(&largeBox,10, 20, 30);
    printf("\n--- Start main() ---\n\n");

    doMaterials();

    doPhysicalBox();

    doWeightBox();

    printf("\n--- End main() ---\n\n");

    box_dtor(&largeBox);
}
