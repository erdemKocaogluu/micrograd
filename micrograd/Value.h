#ifndef VALUE_H
#define VALUE_H

#include <cmath>
#include <string>
#include <iostream>

using namespace std ;

class Value



{
private:
    /* data */
public:


Value* left ;
Value* right ;
double data ;
double grad ;
char func ;
string label ;

bool visited ;
Value* nextTopological ;

void write(Value* loss) ;
void backward() ;

void resetGrads(Value* val) ;



friend Value operator*(Value& left, Value& right);
friend Value operator+(Value& left, Value& right);
friend Value operator-(Value& left, Value& right);
friend Value operator/(Value& left, Value& right);





    Value() ;
    Value (double val) ;
    Value(double val, string lab);
    Value (double val , char funct , Value* value1, Value* value2, string lab) ;
    Value (double val , char funct , Value* value1, Value* value2)  ;
    Value (double val , char funct, string lab ) ;


    void hey(double val , char funct , Value* value1    , Value* value2, string lab) ;

    Value tanjant() ;
    Value relu() ;
    ~Value();








static void play() ;
void buildTopological(Value* current , Value* & head) ;

void resetVisited(Value* head) ;



};





// Value:: Value (double data1 , char funct ) {
//     data = data1 ;
//     func = funct ;
// }






#endif