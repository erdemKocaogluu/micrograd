
#ifndef MLP_H
#define MLP_H

#include "Layer.h"
#include <cmath>

#include <cstdlib>


class MLP
{
private:
    /* data */
public:
    int* layerSizes ;
    int layerNumber ;
    Layer* layers ;
    int inputDim ;


    void hesapla(int inputNumber , double** in, double** & out  ) ;



    MLP(int layerNum , int* layerSiz, int inputDimension);
    ~MLP();
};

MLP::MLP(int layerNum , int* layerSiz, int inputDimension )  { //buna girdi nöronları dahil değil


    layerNumber = layerNum ; // bu layer number aslında kaç tane layer oldığunu gösterir yani layer sizes arrayinin size ı dır. ilk input veren nöronları layer sizesa dahil etmiyoruz

    layerSizes = layerSiz ;

    inputDim = inputDimension ;

    int x = inputDim ;

    layers = new Layer[layerNum] ;

    for (int i = 0 ; i < layerNum ; i++ ) {
        layers[i].hey(x , layerSizes[i]) ; // --> bu şunu yapar --> her bir layerın kaç tane nöronu olacağıyla birlikte her layer a o kadar nöron koyar
        // ve bu layer classındaki hey methodunda aynı zmaanda nöron structının hey methodunu çağırdığımız ve onun weightlerini de rastgele falan ayarladığımız için
        // aslında burası tüm o mlp sistemini kuran yerdir.
        x = layerSizes[i] ; // BU X --> MLP'DE LAYERLARIN İNPUT SAYILARI FARKLI OLABİLDİĞİ İÇİN
        // HER LAYERDA KENDİNDEN BİR ÖNCEKİNDEN GELEN İNPUTLARI SAYAR VE SONRAKİ LAYERA ONU İNPUT NUMBER OLARAK GÖNDERİR
        //BAK ERDEM BU ÇOK ÖNEMLİ KATMANLAR ARASI GİRDİ BOYUTLARI DEĞİŞEBLİLYOR BUNU UNUTMAA
    }


















}





MLP::~MLP()
{

    delete[] layerSizes ; // bu layer sizes falan hep new ile oluşturcam, bunları silmemiz lazızm nett
    delete[] layers ;
}


#endif