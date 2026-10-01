#include "MLP.h"


void MLP::hesapla (int inputNumber , double** in, double** & out ) {


    // int inSize = this -> inputNumber ;



    int layerNumber = this -> layerNumber ;

    for (int i = 0 ; i < layerNumber ; i++ ) {

        out = this->layers[i].hesapla(inputNumber,  in) ;






        if (i >= 1 ) {

            for (int a = 0 ; a < inputNumber ; a++ ) {
                delete[] in[a] ;
            }
            delete[] in ;
        }

        // ilk bize verilen in verisini silmicez ama ara katmanlarda oluşan arrayleri silmeliyiz çünkü layerdaki hesaplamada new ile oluşturuyoruz arrayleri

        in = out ;

    }





}




int main() {



    return 0 ;
}








