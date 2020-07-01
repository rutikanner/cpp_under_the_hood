//
// Created by ruti on 6/18/20.
//

#ifndef C___UNDER_THE_HOOD_CPP2C_POLYMORPHISM_DEFS_H
#define C___UNDER_THE_HOOD_CPP2C_POLYMORPHISM_DEFS_H

#include "stdio.h"
#define DEFAULT_SYMBOL '$';
//// TextFormatter ////////////

typedef void (*funPtr)();

typedef struct Text_formatter
{
    funPtr *vptr;

}Text_formatter;

/*virtual*/ void text_formatter_dtor(Text_formatter* const this);

/*pure virtual*/ void text_formatter_print(const Text_formatter* const this,const char* text);

void text_formatter_ctor(Text_formatter* const this);

//// DefaultTextFormatter ////////////



typedef struct Default_text_formatter{

    Text_formatter t;
    int id;

}Default_text_formatter;

void default_text_formatter_ctor(Default_text_formatter* const this);

void default_text_formatter_ctorD(Default_text_formatter* const this,const Default_text_formatter* other);

Default_text_formatter* default_text_formatter_operator_equel(Default_text_formatter* const this,const Default_text_formatter* d);

void default_text_formatter_dtor(Default_text_formatter* const this);

/*virtual*/void default_text_formatter_print(const Default_text_formatter* const this,const char* text);

Default_text_formatter* default_text_formatter_generate_array();


//// PrePostFixer ////////////

typedef struct Pre_post_fixer Pre_post_fixer;

struct Pre_post_fixer{
//    void *virtual_table;
    Default_text_formatter d;
    /*const*/ char* pre;
    /*const*/ char* post;
};

//// PrePostFixer Defs ////////////

void pre_post_fixer_ctor(Pre_post_fixer*const this,const char* prefix, const char* postfix);

void pre_post_fixer_dtor(Pre_post_fixer*const this);

/*virtual*/ void pre_post_fixer_printc(const Pre_post_fixer*const this,const char* text);

/*virtual*/ void pre_post_fixer_printlc(const Pre_post_fixer*const this,long num, char symbol);//TODO inline

/*virtual*/ char pre_post_fixer_get_default_symbol(const Pre_post_fixer*const this);

//// PrePostDollarFixer ////////////

typedef struct Pre_post_dollar_fixer Pre_post_dollar_fixer;

struct Pre_post_dollar_fixer
{
    Pre_post_fixer pre_post_fixer;
};

//// PrePostDollarFixer Defs ////////////

void pre_post_dollar_fixer_ctorcc(Pre_post_dollar_fixer* const this,const char* prefix, const char* postfix);
void pre_post_dollar_fixer_ctorP(Pre_post_dollar_fixer* const this,const Pre_post_dollar_fixer* other);
void pre_post_dollar_fixer_dtor(Pre_post_dollar_fixer* const this);
void pre_post_dollar_fixer_printic(const Pre_post_dollar_fixer* const this,int num, char symbol);
void pre_post_dollar_fixer_printlc(const Pre_post_dollar_fixer* const this,long num, char symbol);
void pre_post_dollar_fixer_printdc(const Pre_post_dollar_fixer* const this,double num, char symbol);
char pre_post_dollar_fixer_get_default_symbol(const Pre_post_dollar_fixer* const this);

//// PrePostHashFixer ////////////

typedef struct Pre_post_hash_fixer Pre_post_hash_fixer;

struct Pre_post_hash_fixer
{

    Pre_post_dollar_fixer pre_post_dollar_fixer;
    int precision;
};

//// PrePostHashFixer Defs ////////////

void pre_post_hash_fixer_ctor(Pre_post_hash_fixer * const this,int prc);
void pre_post_hash_fixer_dtor(Pre_post_hash_fixer * const this);
void pre_post_hash_fixer_printic(Pre_post_hash_fixer * const this,int num, char symbol);
void pre_post_hash_fixer_printlc(Pre_post_hash_fixer * const this,long num, char symbol);
//void pre_post_hash_fixer_printdc(Pre_post_hash_fixer * const this,long num, char symbol);
char pre_post_hash_fixer_get_default_symbol(const Pre_post_hash_fixer* const this);

//// PrePostFloatDollarFixer ////////////

typedef struct Pre_post_float_dollar_fixer Pre_post_float_dollar_fixer;

struct Pre_post_float_dollar_fixer
{
//                static const char DEFAULT_SYMBOL = '@';
    Pre_post_dollar_fixer pre_post_dollar_fixer;
};

//// PrePostFloatDollarFixer Defs ////////////

void pre_post_float_dollar_fixer_ctor(Pre_post_float_dollar_fixer * const this,const char* prefix, const char* postfix);
void pre_post_float_dollar_fixer_dtor(Pre_post_float_dollar_fixer * const this);
void pre_post_float_dollar_printf(const Pre_post_float_dollar_fixer * const this,float num);
void pre_post_float_dollar_printfc(const Pre_post_float_dollar_fixer * const this,float num, char symbol);


////// PrePostChecker ////////////

typedef struct Pre_post_checker
{
    Pre_post_float_dollar_fixer pre_post_float_dollar_fixer;
}Pre_post_checker;


void pre_post_checker_ctor(Pre_post_checker* const this);
void pre_post_checker_dtor(Pre_post_checker* const this);

void pre_post_checker_printThisSymbolUsingFunc(const Pre_post_checker* const this);
void pre_post_checker_printThisSymbolDirectly(const Pre_post_checker* const this);
void pre_post_checker_printDollarSymbolByCastUsingFunc(const Pre_post_checker* const this);
void pre_post_checker_printDollarSymbolByScopeUsingFunc(const Pre_post_checker* const this);
void pre_post_checker_printDollarSymbolByCastDirectly(const Pre_post_checker* const this);
void pre_post_checker_printDollarSymbolByScopeDirectly(const Pre_post_checker* const this);

////// Multiplier ////////////

typedef struct Multiplier Multiplier;

struct Multiplier
{
    Default_text_formatter d;
    int times;
};

//// Multiplier Defs ////////////
void multiplier_dtor(Multiplier* const this);

void multiplier_print(const Multiplier* const this,const char*);

#endif //C___UNDER_THE_HOOD_CPP2C_POLYMORPHISM_DEFS_H
