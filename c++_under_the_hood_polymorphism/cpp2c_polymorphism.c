//
// Created by ruti on 6/18/20.
//
#include "stdio.h"
#include "cpp2c_polymorphism_defs.h"

void doPrePostFixer()
{
    printf("\n--- start doPrePostFixer() ---\n\n");
    //static binding
    Pre_post_fixer angle_brackets;
    pre_post_fixer_ctor(&angle_brackets,"<<< ", " >>>");
    pre_post_fixer_printc(&angle_brackets,"Hello World!");
    pre_post_fixer_printlc(&angle_brackets,-777,'\0');
    pre_post_fixer_printlc(&angle_brackets,350, '#');
    pre_post_fixer_printlc(&angle_brackets,(long int)3.14,'\0');

    printf("\n--- end doPrePostFixer() ---\n\n");

    pre_post_fixer_dtor(&angle_brackets);
}

void doPrePostDollarFixer()
{
    //static binding
    printf("\n--- start doPrePostDollarFixer() ---\n\n");
    Pre_post_dollar_fixer asterisks;
    pre_post_dollar_fixer_ctorcc(&asterisks, "***** ", " *****");

    pre_post_dollar_fixer_printic(&asterisks,-777,'$');
    pre_post_dollar_fixer_printic(&asterisks,350, '#');
    pre_post_dollar_fixer_printdc(&asterisks,3.14f,'$');

    printf("\n--- end doPrePostDollarFixer() ---\n\n");

    pre_post_dollar_fixer_dtor(&asterisks);
}

void doPrePostChecker()
{
    printf("\n--- start doPrePostChecker() ---\n\n");

    Pre_post_checker check;
    pre_post_checker_ctor(&check);
    pre_post_checker_printThisSymbolUsingFunc(&check);
    pre_post_checker_printThisSymbolDirectly(&check);
    pre_post_checker_printDollarSymbolByCastDirectly(&check);
    pre_post_checker_printDollarSymbolByScopeDirectly(&check);
    pre_post_checker_printDollarSymbolByCastUsingFunc(&check);
    pre_post_checker_printDollarSymbolByScopeUsingFunc(&check);

    printf("\n--- end doPrePostChecker() ---\n\n");

    pre_post_checker_dtor(&check);
}

void doPrePostFloatDollarFixer()
{
    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    Pre_post_float_dollar_fixer hashes;
    pre_post_float_dollar_fixer_ctor(&hashes,"### ", " ###");
    pre_post_float_dollar_printf(&hashes,-777);
    pre_post_float_dollar_printfc(&hashes,350, '#');
    pre_post_float_dollar_printf(&hashes,3.14f);

    Pre_post_dollar_fixer hashes2;
    pre_post_dollar_fixer_ctorP(&hashes2,&hashes.pre_post_dollar_fixer);

    pre_post_dollar_fixer_printdc(&hashes2,7.5,'$');
    pre_post_dollar_fixer_printic(&hashes2,100,'$');

    printf("\n--- start doPrePostFloatDollarFihxer() ---\n\n");

    pre_post_dollar_fixer_dtor(&hashes2);
    pre_post_float_dollar_fixer_dtor(&hashes);
}

void runAsPrePostFixerRef(const Pre_post_fixer* const pp)
{
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");
    pp->d.t.vptr[2](pp, 123, '\0');
//    pp.print(123);

    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerRef(const Pre_post_dollar_fixer* const  pp)
{
    printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");
    pre_post_dollar_fixer_printic(pp, 123,'$');
//    pp->pre_post_fixer.d.t.vptr[2](pp,123,'\0');
//    pp.print(123);

    printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerObj(const Pre_post_dollar_fixer* const pp)
{
    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");

    pp->pre_post_fixer.d.t.vptr[2](pp,123,'\0');
//    pp.print(123);

    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");
}

void runAsPrePostHashFixerRef(const Pre_post_hash_fixer* const pp)
{
    printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");

    pp->pre_post_dollar_fixer.pre_post_fixer.d.t.vptr[2](pp,123,'\0');
//    pp.print(123);

    printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}

extern funPtr multiplier_virtual_table;

void doMultiplier()
{
    printf("\n--- start doMultiplier() ---\n\n");

    Multiplier m1;
    default_text_formatter_ctor(&m1.d);
    m1.d.t.vptr = multiplier_virtual_table;
    m1.times = 3;
    printf("--- Multiplier CTOR: times = %d\n", 3);

    Multiplier m2;
    default_text_formatter_ctor(&m2.d);
    m2.d.t.vptr = multiplier_virtual_table;
    m2.times = 5;
    printf("--- Multiplier CTOR: times = %d\n", 5);

    Multiplier m3;
    default_text_formatter_ctorD(&m3.d, &m1.d);
    m3.times = m1.times;

    Multiplier m4;
    default_text_formatter_ctorD(&m4.d, &m2.d);
    m4.times = m2.times;
//    default_text_formatter_ctor(&m4.d);
//    printf("--- Multiplier CTOR: times = %d\n", 2);

    multiplier_print(&m1,"abc ");
    multiplier_print(&m2,"abc ");
    multiplier_print(&m3,"abc ");
    multiplier_print(&m4,"abc ");


    printf("\n--- start doMultiplier() ---\n\n");

    multiplier_dtor(&m4);
    multiplier_dtor(&m3);
    multiplier_dtor(&m2);
    multiplier_dtor(&m1);

}

void doFormatterArray()
{
    printf("\n--- start doFormatterArray() ---\n\n");

    /*DefaultTextFormatter formatters[] =
            {
                    PrePostDollarFixer("!!! ", " !!!"),
                    Multiplier(4),
                    PrePostChecker()
            };

    for (int i = 0; i < 3; ++i)
        formatters[i].print("Hello World!");*/

    printf("\n--- end doFormatterArray() ---\n\n");



    Default_text_formatter formatters[3];

    Pre_post_dollar_fixer prePostDollarFixerTmp, prePostDollarFixerTmp1;

    Multiplier multiplierTmp, multiplierTmp1;

    Pre_post_checker prePostChecker, postCheckerTmp1;

    pre_post_dollar_fixer_ctorcc(&prePostDollarFixerTmp, "!!! ", " !!!");

    pre_post_dollar_fixer_ctorP(&prePostDollarFixerTmp1, &prePostDollarFixerTmp);

    pre_post_dollar_fixer_dtor(&prePostDollarFixerTmp);

    default_text_formatter_ctor((Default_text_formatter*)&multiplierTmp);
//    /*default ctor*/ DefaultTextFormatter_Ctor((DefaultTextFormatter *)&multiplierTmp);

    multiplierTmp.times = 4;

    printf("--- Multiplier CTOR: times = %d\n", multiplierTmp.times); /*default ctor*/

/*Multiplier_Dtor(&multiplierTmp);

PrePostChecker_Ctor(&prePostChecker);

PrePostChecker_Dtor()*/

    printf("\n--- start doFormatterArray() ---\n\n");

/*formatters[0] =


for (int i = 0; i < 3; ++i)
formatters[i].print("Hello World!");*/

    printf("\n--- end doFormatterArray() ---\n\n");

}

///*
//void doFormatterPtrs()
//{
//    printf("\n--- start doFormatterPtrs() ---\n\n");
//
//    DefaultTextFormatter* pfmt[] =
//            {
//                    new PrePostDollarFixer("!!! ", " !!!"),
//            new Multiplier(4),
//            new PrePostChecker()
//            };
//
//    for (int i = 0; i < 3; ++i)
//        pfmt[i]->print("Hello World!");
//
//    for (int i = 2; i >= 0; --i)
//        delete pfmt[i];
//
//    printf("\n--- end doFormatterPtrs() ---\n\n");
//}
//*/
//
//void doFormatterDynamicArray()
//{
//    int i = 0;
//    DefaultTextFormatter* formatters;
//
//    printf("\n--- start doFormatterDynamicArray() ---\n\n");
//
//    formatters = generateFormatterArray();
//
//    for (; i < 3; ++i)
//        DefaultTextFormatter_Ctor(&formatters[i]);
//
//    for (i = 0; i < 3; ++i)
//        DefaultTextFormatter_Print(&formatters[i], "Hello World!");
//
//    for(i = 2; i >= 0; --i)
//    {
//        DefaultTextFormatter_Dtor(&formatters[i]);
//    }
//
//    /*free(&formatters[0]);
//    free(&formatters[1]);*/
//    free(&formatters[2]);
//    printf("\n--- start doFormatterDynamicArray() ---\n\n");
//}

//void doFormatterArray()
//{
//    printf("\n--- start doFormatterArray() ---\n\n");
//
//    DefaultTextFormatter formatters[] =
//            {
//                    PrePostDollarFixer("!!! ", " !!!"),
//                    Multiplier(4),
//                    PrePostChecker()
//            };
//
//    for (int i = 0; i < 3; ++i)
//        formatters[i].print("Hello World!");
//
//    printf("\n--- end doFormatterArray() ---\n\n");
//}
//
//void doFormatterPtrs()
//{
//    printf("\n--- start doFormatterPtrs() ---\n\n");
//
//    DefaultTextFormatter* pfmt[] =
//            {
//                    new PrePostDollarFixer("!!! ", " !!!"),
//            new Multiplier(4),
//            new PrePostChecker()
//            };
//
//    for (int i = 0; i < 3; ++i)
//        pfmt[i]->print("Hello World!");
//
//    for (int i = 2; i >= 0; --i)
//        delete pfmt[i];
//
//    printf("\n--- end doFormatterPtrs() ---\n\n");
//}
//
//void doFormatterDynamicArray()
//{
//    printf("\n--- start doFormatterDynamicArray() ---\n\n");
//
//    DefaultTextFormatter* formatters = generateFormatterArray();
//
//    for (int i = 0; i < 3; ++i)
//        formatters[i].print("Hello World!");
//
//    delete[] formatters;
//
//    printf("\n--- start doFormatterDynamicArray() ---\n\n");
//}


int main()
{
    printf("\n--- Start main() ---\n\n");

    doPrePostFixer();//Work!
    doPrePostDollarFixer();//Work!
    doPrePostFloatDollarFixer();//Work!

    doPrePostChecker();//Work!

    Pre_post_hash_fixer hfix;
    pre_post_hash_fixer_ctor(&hfix,4);
    runAsPrePostFixerRef(&hfix.pre_post_dollar_fixer.pre_post_fixer);//Work!
    runAsPrePostDollarFixerRef(&hfix.pre_post_dollar_fixer);
    runAsPrePostDollarFixerObj(&hfix.pre_post_dollar_fixer);
    runAsPrePostHashFixerRef(&hfix);

    doMultiplier();
//
    doFormatterArray();
//    doFormatterPtrs();
//    doFormatterDynamicArray();

    printf("\n--- End main() ---\n\n");

    return 0;
}