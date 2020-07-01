#include "stdio.h"
#include "cpp2c_encapsulation_defs.h"
extern char* message;
static Box largeBox;
Box box99;
Box box88;

//void thisFunc()
//{
//    std::printf("\n--- thisFunc() ---\n\n");
//    static Box box99(99, 99, 99);
//    box99 *= 10;
//}

void thisFunc()
{
    printf("\n--- thisFunc() ---\n\n");
    static char flag = 0;

    if(flag == 0)
        box_ctorddd(&box99, 99, 99, 99);
    box_operator_mult_equal(&box99, 10);
    flag ++;
}

//void thatFunc()
//{
//    std::printf("\n--- thatFunc() ---\n\n");
//    static Box box88(88, 88, 88);
//    box88 *= 10;
//}

void thatFunc()
{
    printf("\n--- thatFunc() ---\n\n");
    static char flag = 0;

    if(flag == 0)
        box_ctorddd(&box88,88, 88, 88);
    box_operator_mult_equal(&box88, 10);
    flag ++;
}


//void doBoxes()
//{
//    std::printf("\n--- Start doBoxes() ---\n\n");
//
//    Box b1(3);
//    Box b2(4, 5, 6);
//
//    std::printf("b1 volume: %f\n", b1.getVolume());
//    std::printf("b2 volume: %f\n", b2.getVolume());
//
//    b1 *= 1.5;
//    b2 *= 0.5;
//
//    std::printf("b1 volume: %f\n", b1.getVolume());
//    std::printf("b2 volume: %f\n", b2.getVolume());
//
//    Box b3 = b2;
//    Box b4 = 3 * b2;
//    std::printf("b3 %s b4\n", b3 == b4 ? "equals" : "does not equal");
//
//    b3 *= 1.5;
//    b4 *= 0.5;
//    std::printf("Now, b3 %s b4\n", b3 == b4 ? "equals" : "does not equal");
//
//    std::printf("\n--- End doBoxes() ---\n\n");
//}
//

void doBoxes()
{
    printf("\n--- Start doBoxes() ---\n\n");

    Box b1;
    box_ctord(&b1, 3);
    Box b2;
    box_ctorddd(&b2, 4, 5, 6);

    printf("b1 volume: %f\n", (b1.width * b1.length * b1.height));
    printf("b2 volume: %f\n", (b2.width * b2.length * b2.height));

    box_operator_mult_equal(&b1, 1.5);
    box_operator_mult_equal(&b2, 0.5);

    printf("b1 volume: %f\n", (b1.width * b1.length * b1.height));
    printf("b2 volume: %f\n", (b2.width * b2.length * b2.height));

    Box b3 = b2;
    Box b4 = b2;

    box_operator_mult_equal(&b4, 3);
    printf("b3 %s b4\n", (b3.length==b4.length && b3.height == b4.height && b3.width == b4.width) ? "equals" : "does not equal");

    box_operator_mult_equal(&b3, 1.5);
    box_operator_mult_equal(&b4, 0.5);
    printf("Now, b3 %s b4\n", (b3.length==b4.length && b3.height == b4.height && b3.width == b4.width) ? "equals" : "does not equal");

    printf("\n--- End doBoxes() ---\n\n");

    box_dtor(&b4);
    box_dtor(&b3);
    box_dtor(&b2);
    box_dtor(&b1);
}

//void doShelves()
//{
//    std::printf("\n--- start doShelves() ---\n\n");
//
//    Box aBox = 5;
//
//    Shelf aShelf;
//
//    aShelf.print();
//    aShelf.setBox(1, largeBox);
//    aShelf.setBox(0, aBox);
//
//    aShelf.print();
//    aShelf.setMessage("This is the total volume on the shelf:");
//    aShelf.print();
//    Shelf::setMessage("Shelf's volume:");
//    aShelf.print();
//
//    aShelf.setBox(1, Box(2, 4, 6));
//
//    aShelf.setBox(2, 2);
//    aShelf.print();
//
//    std::printf("\n--- end doShelves() ---\n\n");
//}

void doShelves()
{
    printf("\n--- start doShelves() ---\n\n");

    Box aBox;
    box_ctord(&aBox, 5);

    Shelf aShelf;
    box_ctord(&aShelf.boxes[0], 1);
    box_ctord(&aShelf.boxes[1], 1);
    box_ctord(&aShelf.boxes[2], 1);

    shelf_print(&aShelf);
    shelf_set_box(&aShelf, 1, &largeBox);
    shelf_set_box(&aShelf, 0, &aBox);

    shelf_print(&aShelf);
    message = "This is the total volume on the shelf:";
    shelf_print(&aShelf);
    message = "Shelf's volume:";
    shelf_print(&aShelf);

    Box b1;
    box_ctorddd(&b1, 2, 4, 6);
    shelf_set_box(&aShelf, 1, &b1);
    box_dtor(&b1);

    Box b2;
    box_ctord(&b2, 2);
    shelf_set_box(&aShelf, 2, &b2);
    box_dtor(&b2);
    shelf_print(&aShelf);

    printf("\n--- end doShelves() ---\n\n");

    box_dtor(&aShelf.boxes[2]);
    box_dtor(&aShelf.boxes[1]);
    box_dtor(&aShelf.boxes[0]);
    box_dtor(&aBox);
}

//int main()
//{
//    box_ctorddd(&largeBox,10, 20, 30);
//    printf("\n--- Start main() ---\n\n");
//
//    doBoxes();
//
//    thisFunc();
//    thisFunc();
//    thisFunc();
//    thatFunc();
//    thatFunc();
//
//    doShelves();
//
//    printf("\n--- End main() ---\n\n");
//
//    box_dtor(&box88);
//    box_dtor(&box99);
//    box_dtor(&largeBox);
//
//    return 0;
//}

