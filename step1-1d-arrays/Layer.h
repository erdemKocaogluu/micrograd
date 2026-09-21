#ifndef LAYER_H
#define LAYER_H


#include <cmath>
#include <cstdlib>


struct Neuron
{


    int weightNumber ;
    double* weights ;





    Neuron(){
        weightNumber = -1 ;
        weights = nullptr ;
    }
    ~Neuron(){
        delete[] weights ; // şu [] kullanmayı unutma !
    }


    void hey(int inputN ) {
        weightNumber = inputN ;
        weights = new double[weightNumber] ;



        for (int i = 0 ; i < weightNumber ; i++ ) {


            double a = ((double)rand()/(double)RAND_MAX); // bunu stack overflowdan buldum, 0-1 arası uniformly üretiyomuş randomları

            weights[i] = a ;




        }

    }


    double hesapla(double* in ) { // bu array döndürmicek, her nöron aldığı dot productları sonucu bir tane double döndürücek ve her layerdaki nörnonların output ettiği doublelar
    // birleşerek sonraki layera girecek input arrayleri üretecekler
        // buradaki weightNumber = inputNumber'dır zaten --> dot product alıncak ya
        double out = 0.0 ;
        for (int i = 0 ; i < weightNumber ; i++ ) {
            out += in[i] * weights[i] ;
        }

        return out ;
    }













};




class Layer
{
private:
    /* data */
public:

    Neuron* neurons ;
    int neuronSize ;


    void hey(int inputNumber, int neuronNumber) ;
    double* hesapla( double* in ) ;



    Layer() ;
    Layer(int inputNumber, int neuronNumber); // bu neuronNumber == layersize
    ~Layer();
};


Layer::Layer() {
    neurons = nullptr ;

}



void Layer::hey(int inputNumber, int neuronNumber){

    // buradaki input number direkt kullancağımız weight matrisinin her bir nöronunun ayrı ayrı sahip olacağı weight sayısı kadardır


    neurons = new Neuron[neuronNumber] ;
    neuronSize = neuronNumber ;


    for (int i = 0 ; i < neuronNumber ; i++ ) { // mesela normal nöron initializer'ı leak e sebep oluyor olsa burada leak olacak mıydı?
        neurons[i].hey(inputNumber) ;
    }



}

double* Layer:: hesapla( double* in ) {


    double* outArr = new double[neuronSize] ;


    for ( int i = 0 ; i < neuronSize; i++ ) {



        double out = neurons[i].hesapla(in) ; // input size ı göndermemize gerek yok bunu zaten MLP yi oluştururken nöronun özelliklerine ekledik

        outArr[i] = out ;

    }

    return outArr ;

}








Layer::~Layer()
{

    delete[] neurons ; // buna gerek var mı emin olamadım sonuçta nöronlar birer obje , ve ben onlardan oluşturdğum arraye bir tane * koyarak aslında onları statik olarak tanımlamış oluyorum
    // buna sonra bir daha bakıcam 

}










#endif