//
// Created by ruti on 6/18/20.
//

#include "cpp2c_polymorphism_defs.h"
#include "stdlib.h"

//// TextFormatter Defs ////////////

funPtr text_formatter_virtual_table[2] = {(funPtr)text_formatter_dtor, (funPtr)text_formatter_print};

void text_formatter_dtor(Text_formatter* const this){}

void text_formatter_ctor(Text_formatter* const this){
    this->vptr = text_formatter_virtual_table;
}

void text_formatter_print(const Text_formatter* const this,const char* text)
{

}


//// DefaultTextFormatter Defs ////////////TODO inherit from TextFormatter

funPtr default_text_formatter_virtual_table[2] = {(funPtr)default_text_formatter_dtor, (funPtr)default_text_formatter_print};

int next_id = 0;

void default_text_formatter_ctor(Default_text_formatter* const this)
{
    text_formatter_ctor((Text_formatter*)this);
    this->t.vptr = default_text_formatter_virtual_table;
    this -> id = (next_id++);
    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->id);
}

void default_text_formatter_dtor(Default_text_formatter* const this)
{
    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", this->id);
    this->t.vptr = text_formatter_virtual_table;
    text_formatter_dtor((Text_formatter*)this);
}

void default_text_formatter_ctorD(Default_text_formatter* const this,const Default_text_formatter* other)
{
    text_formatter_ctor((Text_formatter*)this);
    this->t.vptr = default_text_formatter_virtual_table;
    this -> id = (next_id++);
    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other->id, this->id);
}

Default_text_formatter* default_text_formatter_operator_equel(Default_text_formatter* const this,const Default_text_formatter* other)
{
    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other->id, this->id);
    return this;
}

void default_text_formatter_print(const Default_text_formatter* const this,const char* text)
{
    printf("%-60s | ", "[DefaultTextFormatter::print(const char*)]");
    printf("%s\n", text);
}

Default_text_formatter* default_text_formatter_generate_array()
{
    return malloc(sizeof(Default_text_formatter) * 3);
}

//// PrePostFixer Defs ////////////TODO inherit from DefaultTextFormatter

funPtr pre_post_fixer_virtual_table[4] = {(funPtr)pre_post_fixer_dtor, (funPtr)pre_post_fixer_printc ,(funPtr)pre_post_fixer_printlc, (funPtr)pre_post_fixer_get_default_symbol};

void pre_post_fixer_ctor(Pre_post_fixer*const this,const char* prefix, const char* postfix)
{
    default_text_formatter_ctor((Default_text_formatter*)this);
    this->d.t.vptr = pre_post_fixer_virtual_table;
    this->pre = (char *)prefix;
    this->post = (char *)postfix;
    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this->pre, this->post);

}

void pre_post_fixer_dtor(Pre_post_fixer*const this)
{
    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", this->pre, this->post);
    this->d.t.vptr = default_text_formatter_virtual_table;
    default_text_formatter_dtor((Default_text_formatter*)this);
}

void pre_post_fixer_printc(const Pre_post_fixer*const this,const char* text)
{
    printf("%-60s | ", "[PrePostFixer::print(const char*)]");
    printf("%s%s%s\n", this->pre, text, this->post);
}

void pre_post_fixer_printlc(const Pre_post_fixer*const this,long num, char symbol)
{
    printf("%-60s | ", "[PrePostFixer::print(long, char)]");
    printf("-->\n");
    if (symbol)
    {
        printf("%-60s | ", "[PrePostFixer::print_num(long, char)]");
        printf("%s%c%ld%s\n", this->pre, symbol, num, this->post);
    }

    else
    {
        printf("%-60s | ", "[PrePostFixer::print_num(long)]");
        printf("%s%ld%s\n", this->pre, num, this->post);
    }
}

char pre_post_fixer_get_default_symbol(const Pre_post_fixer*const this)
{
    return '\0';
}

//// PrePostDollarFixer Defs ////////////TODO inherit from PrePostFixer

funPtr pre_post_dollar_fixer_virtual_table[4] = {(funPtr)pre_post_dollar_fixer_dtor , (funPtr)pre_post_fixer_printc, (funPtr)pre_post_dollar_fixer_printlc, (funPtr)pre_post_dollar_fixer_get_default_symbol};

void pre_post_dollar_fixer_ctorcc(Pre_post_dollar_fixer* const this,const char* prefix, const char* postfix)
{
    pre_post_fixer_ctor((Pre_post_fixer*)this,prefix,postfix);
    this->pre_post_fixer.d.t.vptr = pre_post_dollar_fixer_virtual_table;
    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", ((Pre_post_fixer*)this)->pre, ((Pre_post_fixer*)this)->post);
}

void pre_post_dollar_fixer_ctorP(Pre_post_dollar_fixer* const this,const Pre_post_dollar_fixer* other)
{
    default_text_formatter_ctorD(&this->pre_post_fixer.d , &other->pre_post_fixer.d);
    this->pre_post_fixer.d.t.vptr = pre_post_dollar_fixer_virtual_table;
    this->pre_post_fixer.pre = other->pre_post_fixer.pre;
    this->pre_post_fixer.post = other->pre_post_fixer.post;
    printf("--- PrePostDollarFixer Copy CTOR: \"%s\"...\"%s\"\n", this->pre_post_fixer.pre, this->pre_post_fixer.post);
}

void pre_post_dollar_fixer_dtor(Pre_post_dollar_fixer* const this)
{
    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", ((Pre_post_fixer*)this)->pre, ((Pre_post_fixer*)this)->post);
    this->pre_post_fixer.d.t.vptr = pre_post_fixer_virtual_table;
    pre_post_fixer_dtor((Pre_post_fixer*)this);
}

void pre_post_dollar_fixer_printic(const Pre_post_dollar_fixer* const this,int num, char symbol)
{
    printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");
    this->pre_post_fixer.d.t.vptr[2](this,(long )num,symbol);

}


void pre_post_dollar_fixer_printlc(const Pre_post_dollar_fixer* const this,long num, char symbol){
    printf("%-60s | ", "[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");
//    this->pre_post_fixer.d.t.vptr[2](this, num, symbol);

    pre_post_fixer_printlc((Pre_post_fixer*)this, num, symbol);
}

void pre_post_dollar_fixer_printdc(const Pre_post_dollar_fixer* const this,double num, char symbol)
{
    printf("%-60s | ", "[PrePostDollarFixer::print(double, char)]");
    printf("%s%c%f%s\n", ((Pre_post_fixer*)this)->pre, symbol, num,((Pre_post_fixer*)this)->post);
}

char pre_post_dollar_fixer_get_default_symbol(const Pre_post_dollar_fixer* const this)
{
    return '$';
}

//// PrePostHashFixer Defs ////////////TODO inherit from pre_post_dollar_fixer

funPtr pre_post_hash_fixer_virtual_table[4] = {(funPtr)pre_post_hash_fixer_dtor , (funPtr)pre_post_fixer_printc,(funPtr)pre_post_hash_fixer_printlc, (funPtr)pre_post_hash_fixer_get_default_symbol};


void pre_post_hash_fixer_ctor(Pre_post_hash_fixer * const this,int prc)
{
    pre_post_dollar_fixer_ctorcc((Pre_post_dollar_fixer*)this,"===> ", " <===");
    this->pre_post_dollar_fixer.pre_post_fixer.d.t.vptr = pre_post_hash_fixer_virtual_table;
    this->precision = prc;
    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", this->pre_post_dollar_fixer.pre_post_fixer.pre, this->pre_post_dollar_fixer.pre_post_fixer.post, this->precision);
//    pre_post_hash_fixer_printdc((Pre_post_dollar_fixer*)this,9999.9999, '#');
    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this->pre_post_dollar_fixer.pre_post_fixer.pre, '#', this->precision, 9999.9999,this->pre_post_dollar_fixer.pre_post_fixer.post);
}
void pre_post_hash_fixer_dtor(Pre_post_hash_fixer * const this)
{
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", this->pre_post_dollar_fixer.pre_post_fixer.pre, this->pre_post_dollar_fixer.pre_post_fixer.post);
    this->pre_post_dollar_fixer.pre_post_fixer.d.t.vptr = pre_post_dollar_fixer_virtual_table;
    pre_post_dollar_fixer_dtor((Pre_post_dollar_fixer*)this);
}
void pre_post_hash_fixer_printic(Pre_post_hash_fixer * const this,int num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(int, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this->pre_post_dollar_fixer.pre_post_fixer.pre, symbol, this->precision, (double)num,this->pre_post_dollar_fixer.pre_post_fixer.post);
}
void pre_post_hash_fixer_printlc(Pre_post_hash_fixer * const this,long num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(long, char)]");
    printf("-->\n");
//    pre_post_hash_fixer_printdc(this,(double)num, symbol);
    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this->pre_post_dollar_fixer.pre_post_fixer.pre, symbol, this->precision, (double)num,this->pre_post_dollar_fixer.pre_post_fixer.post);
}

char pre_post_hash_fixer_get_default_symbol(const Pre_post_hash_fixer* const this)
{
    return '#';
}

//// PrePostFloatDollarFixer Defs ////////////TODO pre_post_dollar_fixer

funPtr pre_post_float_dollar_fixer_virtual_table[4] = {(funPtr)pre_post_float_dollar_fixer_dtor,(funPtr)pre_post_fixer_printc,(funPtr)pre_post_dollar_fixer_printlc,(funPtr)pre_post_dollar_fixer_get_default_symbol};

void pre_post_float_dollar_fixer_ctor(Pre_post_float_dollar_fixer * const this,const char* prefix, const char* postfix)
{
    pre_post_dollar_fixer_ctorcc((Pre_post_dollar_fixer*)this,prefix,postfix);
    this->pre_post_dollar_fixer.pre_post_fixer.d.t.vptr = pre_post_float_dollar_fixer_virtual_table;
    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", this->pre_post_dollar_fixer.pre_post_fixer.pre, this->pre_post_dollar_fixer.pre_post_fixer.post);
}
void pre_post_float_dollar_fixer_dtor(Pre_post_float_dollar_fixer * const this)
{
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n", this->pre_post_dollar_fixer.pre_post_fixer.pre, this->pre_post_dollar_fixer.pre_post_fixer.post);
    this->pre_post_dollar_fixer.pre_post_fixer.d.t.vptr = pre_post_dollar_fixer_virtual_table;
    pre_post_dollar_fixer_dtor((Pre_post_dollar_fixer*)this);
}
void pre_post_float_dollar_printf(const Pre_post_float_dollar_fixer * const this,float num)
{
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float)]");
    printf("-->\n");
    pre_post_float_dollar_printfc(this,num, '@');
}

void pre_post_float_dollar_printfc(const Pre_post_float_dollar_fixer * const this,float num, char symbol)
{
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float, char)]");
    printf("%s%c%.2f%s\n", this->pre_post_dollar_fixer.pre_post_fixer.pre, symbol, num, this->pre_post_dollar_fixer.pre_post_fixer.post);
}

////// PrePostChecker Defs ////////////TODO inherit from pre_post_float_dollar

funPtr pre_post_checker_virtual_table[4] = {(funPtr)pre_post_checker_dtor,(funPtr)pre_post_fixer_printc,(funPtr)pre_post_dollar_fixer_printlc,(funPtr)pre_post_dollar_fixer_get_default_symbol};

void pre_post_checker_ctor(Pre_post_checker* const this)
{
    pre_post_float_dollar_fixer_ctor((Pre_post_float_dollar_fixer*)this,"[[[[ ", " ]]]]");
    this->pre_post_float_dollar_fixer.pre_post_dollar_fixer.pre_post_fixer.d.t.vptr = pre_post_checker_virtual_table;
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", this->pre_post_float_dollar_fixer.pre_post_dollar_fixer.pre_post_fixer.pre, this->pre_post_float_dollar_fixer.pre_post_dollar_fixer.pre_post_fixer.post);

}
void pre_post_checker_dtor(Pre_post_checker* const this)
{
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", this->pre_post_float_dollar_fixer.pre_post_dollar_fixer.pre_post_fixer.pre, this->pre_post_float_dollar_fixer.pre_post_dollar_fixer.pre_post_fixer.post);
    this->pre_post_float_dollar_fixer.pre_post_dollar_fixer.pre_post_fixer.d.t.vptr = pre_post_float_dollar_fixer_virtual_table;
    pre_post_float_dollar_fixer_dtor(&this->pre_post_float_dollar_fixer);
}

void pre_post_checker_printThisSymbolUsingFunc(const Pre_post_checker* const this)
{
    printf("%-60s | ", "[PrePostChecker::printThisSymbolUsingFunc()]");
    printf("Default symbol is %c\n", '@');
}

void pre_post_checker_printThisSymbolDirectly(const Pre_post_checker* const this)
{
    printf("%-60s | ", "[PrePostChecker::printThisSymbolDirectly()]");
    printf("Default symbol is %c\n", '@');
}

void pre_post_checker_printDollarSymbolByCastUsingFunc(const Pre_post_checker* const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastUsingFunc()]");
    printf("Default symbol is %c\n", pre_post_dollar_fixer_get_default_symbol(((Pre_post_dollar_fixer*)(this))));

}
void pre_post_checker_printDollarSymbolByScopeUsingFunc(const Pre_post_checker* const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");
    printf("Default symbol is %c\n", pre_post_dollar_fixer_get_default_symbol(&(this->pre_post_float_dollar_fixer.pre_post_dollar_fixer)));
}
void pre_post_checker_printDollarSymbolByCastDirectly(const Pre_post_checker* const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastDirectly()]");
    printf("Default symbol is %c\n", '$');
}
void pre_post_checker_printDollarSymbolByScopeDirectly(const Pre_post_checker* const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeDirectly()]");
    printf("Default symbol is %c\n", '$');
}

//// Multiplier Defs ////////////

funPtr multiplier_virtual_table[2] = {(funPtr)multiplier_dtor , (funPtr)multiplier_print};

void multiplier_dtor(Multiplier * const this)
{
    printf("--- Multiplier DTOR: times = %d\n", this->times);
    this->d.t.vptr = default_text_formatter_virtual_table;
    default_text_formatter_dtor((Default_text_formatter*)this);
}

void multiplier_print(const Multiplier * const this, const char* text)
{
    printf("%-60s | ", "[Multiplier::print(const char*)]");
    for (int i = 0; i < this->times; ++i)
        printf("%s", text);
    printf("\n");
}