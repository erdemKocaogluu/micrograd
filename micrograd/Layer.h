#ifndef LAYER_H
#define LAYER_H


#include <cmath>
#include <cstdlib>

#include "Value.h"


struct Neuron
{


    int weightNumber ;
    Value** weights ;




 // BİAS KOYACAĞIM , ÖNCE ŞU RELUYU BİTİREYİM. BİR AKTİVASYON FONKSİYONU OLMADAN ÇALIŞTIRDIĞIM İÇİN GRADIENT EXPLODE OLUYOR LOSS: NAN GÖZÜKÜYOR


    Neuron(){
        weightNumber = -1 ;
        weights = nullptr ;

    }
    ~Neuron(){
        delete[] weights ; // şu [] kullanmayı unutma !
    }


    void hey(int inputN ) {
        weightNumber = inputN ;
        weights = new Value*[weightNumber] ; 
        
        // bu HEY fonksiyonlarını kullandım çünkü array oluştururken bböyle default constructorla oluşturuyorum sonra 
        // aşağıda hey ile modifiye ediyorum ve bu sayede hiçbir leak olmuyor



        for (int i = 0 ; i < weightNumber ; i++ ) {


            


            double a = ((double)rand()/(double)RAND_MAX); // bunu stack overflowdan buldum, 0-1 arası uniformly üretiyomuş randomları

            weights[i] = new Value(a, ' ', NULL, NULL, "weight") ;  // bu weightlerin bir funcitonu yok çünkü bunlar sadece weightler ve bir fonksiyonla oluşmadı  sadece random olarak oluşturuldular




        }

    }


    Value* hesapla(Value** in ) { // bu array döndürmicek, her nöron aldığı dot productları sonucu bir tane double döndürücek ve her layerdaki nörnonların output ettiği doublelar
    // birleşerek sonraki layera girecek input arrayleri üretecekler
        // buradaki weightNumber = inputNumber'dır zaten --> dot product alıncak ya



 // buraya weightlerin visited larını resetleyen bir fonksiyon yazcam , aslında mlp.cpp deki loopdaki ilk turda burası anlamsız gibi gelebilir ama o loopun sonunda ben valuelari siliyorum ve onları silmek için tüm valueları
 // buna weightler de dahil --> topologic sıraya koyuyorum ve bunu yaparken de weightlerin de visited = true oluyor ve sonra bunları o loopun sonunda geri visited = false yapamıyorum çünkü weightler artık birbirlerine bağlı olmuyorlar
 // burada sıfırlamak daha mantıklı o yüzden direkt weights listesinden



        for (int i = 0 ; i < weightNumber ; i++ ) {

            weights[i] ->visited = false ;
            
        }




        Value** outFirst = new Value*[weightNumber] ; 
        
        for (int i = 0 ; i < weightNumber ; i++ ) {
            outFirst[i] = new Value((in[i]->data * weights[i]->data) , '*' , in[i], weights[i])  ;


        }

        

        int length  ;

        if (weightNumber % 2 == 0 ) {
            length = weightNumber / 2 ;
        }
        else {
            length = weightNumber / 2 + 1 ;
        }


        int beforeLength = weightNumber ; 

        while (length != 0 ) {

            if (length == 1 && beforeLength == 1 ) {
                break ;
            }


            Value** arr = new Value*[length] ;
            
            int a = 0 ;
            int b = 0 ;

            while ( a < beforeLength - 1 ) {

                arr[b++] = new Value((outFirst[a]->data + outFirst[a+1]->data) , '+' , outFirst[a], outFirst[a+1])  ;
                a++;
                a++;


            }

            if (a == beforeLength - 1 ) { // tek sayıda input varsa sonuncuyu direk alıyoruz
                arr[b++] = new Value (outFirst[a]->data, 'p' , outFirst[a], NULL) ; // 'p' --> pass demek yani direk alıyoruz, bir fonksiyonla oluşmadı
                a++;
            }

            int uzun = length ;


            if (length % 2 == 0 ) {
                length = length / 2 ;
            }
            else {
                length = length / 2 + 1 ;
            }

            beforeLength = uzun ;

            delete[] outFirst ; // buradaki delete -> value leri silmez sadece o arrayi siler , yani valueları ayrı ayrı new ile tanımladığımız için onlar silinmeyecek
            // zaten bizim istediğimiz de onların silinmemesi

            // burada value ları new ile tanımlamasak bu sefer bu delete[] outFirst ; satırı value leri de silerdi ve bu da istemediğimiz bir şey olurdu, silmesek de bu sefer de memory leak
            // olurdu o nedenle böyle yapmamız gerekiyordu

            outFirst = arr ; 
        }


        Value* out = outFirst[0] ;

        delete[] outFirst ;

        double afterReluData = 0.0 ;



        if (out -> data > 0 ) {
            afterReluData = out -> data ;
        }

        else {
            afterReluData = 0 ;

        }





        Value* afterRelu = new Value (afterReluData , 'r' , out , NULL ) ; // buunun da labelı -> "" olur. bu sayede ana main fonksiyon sonunda bu da silinecek ki --> silinmesi de lazım zaten


        return  afterRelu ;


    }













};




















//LAYYEERRRR


class Layer
{
private:
    /* data */
public:

    Neuron* neurons ;
    int neuronSize ;


    void hey(int inputNumber, int neuronNumber) ;
    Value*** hesapla( int inputNumber , Value*** in ) ; // bak önceki versiyona göre her double -> value* 'a dönüştü, çünkü artık her nöronun outputu 
    // bir value* olacak ve o value* lar birleşerek sonraki layera girecek input arraylerini oluşturacaklar



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

Value*** Layer:: hesapla( int inputNumber , Value*** in ) { // bu in --> 2 BOYUTLU ARRAY. İÇİNDE VALUE* OBJELERİ VAR




    Value*** outArr = new Value** [inputNumber] ; // bu input number -> inputların kaç dimensionlı oldğunu değil direkt o dimensionlı inputtan kaç tane var onu gösterir


    // şuan kurduğum mantığa göre row sayısı -> input number ,   column sayısı -> her bir inputun kaç classı olduğu , diğer bir deyişle her bir inputun kaç dimensionlı olduğudur

    for (int i = 0 ; i < inputNumber ; i++ ) {
        outArr[i] = new Value*[neuronSize] ; // bu neuronSize = o layerda kaç tane nöron olduğu olcak o nedenle bu da çıktının kaç boyutlu olacağını gösterir -> column sayısı
    }


    for (int a = 0 ; a < inputNumber ; a++ ) {

        Value** currentInput = in[ a ] ;


        for ( int i = 0 ; i < neuronSize; i++ ) {



            Value* out = neurons[i].hesapla(currentInput) ; // input size ı göndermemize gerek yok bunu zaten MLP yi oluştururken nöronun özelliklerine ekledik

            outArr[a][i] = out ;

        }

   



    }

 return outArr ;
  

}








Layer::~Layer()
{

    delete[] neurons ; // buna gerek var mı emin olamadım sonuçta nöronlar birer obje , ve ben onlardan oluşturdğum arraye bir tane * koyarak aslında onları statik olarak tanımlamış oluyorum
    // buna sonra bir daha bakıcam 

}










#endif