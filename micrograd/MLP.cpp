#include "MLP.h"
#include "Value.h"


void MLP::hesapla (int inputNumber , Value*** in, Value*** & out ) {


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


void MLP:: deleteValues ( Value* & head ) {





    if (head == NULL || head -> visited == true ) return ;


    head-> visited = true ;
    
    

    deleteValues(head->nextTopological) ;


    if (head -> label == "") { // -> bu sayede inputları ve weightleri silmeyiz

        delete head ;



    }





}


// input girmek
// loss hesaplamak

// loss.backward() ile gradleri hesaplamak

/*

forward pass yapcaz sonra loss bulcaz sonra gradları sıfırlıcaz sonra back prop ile gradları bulcaz sonra gradleri kullanarak weightleri update edicez sonra tekrar --> gradient descent deniyo buna
// şu gradları sıfırlamayı unutursan baya bir gradyan birikir bu terim --> gradient accumulation olur bu nedenle sıfırlamamız laızm çünkü grad hesaplarken += kullanıyoruz ya
// her iterationda birikir sıfırlamazsak

her gradient descent iterasyonunda valueleri silmemiz lazım -> weight ve inputlar hariç
çünkü neuron classındaki hesapla() -> fonksiyonumuzda o value ağacı tekrar kuruluyor


*/




int main() {

    int length = 50 ;
    double lengthDoubleVersion = (double) length ;

    int dimension = 5 ;

    Value*** input = new Value** [length] ; // 50 tane input var diyelim


    for (int i = 0 ; i < length ; i++ ) {
        input[i] = new Value*[dimension] ;  // -> her input 5 boyutlu olsun 

        for (int a = 0 ; a < dimension ; a++ ) { 
            input[i][a] = new Value(((double)rand()*10)/(double)RAND_MAX , "input") ; // bunu stack overflowdan buldum iyi random ürettiriyoruz 0-10 arası
        }







    }


    // inputlarımızı rastgele oluşturduk şimdi MLP yi kurcaz ve inputları ona verecez,

    int* layerSizes = new int[4] ;
    layerSizes[0] = 4 ;
    layerSizes[1] = 3 ;
    layerSizes[2] = 2 ;
    layerSizes[3] = 1 ;
    // şimdilik son layera 1 tane nöron koyuyorum çünkü lossu tek bir double olarak almak istiyorum, yani son layerdaki nöron sayısı = output dimension olacak
    // ama sonraki dosyalarda bigram falan kurarken bu son layer nöron sayısı değişecek çünkü oradaki output dimension 1 olmamalı
    // muhtemelen orada alfabedeki harf sayısı kadar nöron olacak çünkü her harf bir output dimension olacak falan // neyse şimdilik 1 tane nöron koyuyorum son layera


    MLP* mlp = new MLP(4, layerSizes, 5) ; // 4 layer var , layer sizes arrayi , input dimension = 5








    for (int step = 0 ; step < 500 ; step++ ) {

 

        
        Value*** output = nullptr ;









        mlp->hesapla(length, input, output) ; // bu direkt output u değiştircek şekilde yaptım, & ile alıyor ya method , ondan dolayı bu fonskyion
        //  bittiğinde output artık mlp nin outputu olacak şekilde değişmiş olacak

        // şuanki örnekte 50 tane input ve her biri 1 boyutlu olarak çıkacak olduğu için output arrayi 50x1 boyutlu olacak






        // şimdi bir desired output yazıcam Andrej Karpathy nin yaptığı gibi --> sonra onun üzerinden averaj lossu hesaplıcam ve back prop yaptırıcaz falan

        Value*** desiredOutput = new Value** [length] ;


        for (int i  = 0 ; i < length ; i++ ) {

            desiredOutput[i] = new Value*[1 ] ; // outputların column sayısı 1 olacak çünkü her output 1 boyutlu olacak

            desiredOutput[i][0] = new Value(10) ; // 10 sayısını rastgele koydum diyelim ki makine öğrenmesi gereken değer 10 olsun, yani outputların 10 olmasını istiyoruz diyelim

        }


        // double loss = 0.0 ;


        // for (int i = 0 ; i < length ; i++   ) {
        //     loss += (output[i][0] -> data - desiredOutput[i][0] -> data) * (output[i][0] -> data - desiredOutput[i][0] -> data) ;
        // }


        // Value* loss = new Value(0.0, "loss") ;

        Value** temp = new Value*[length] ;


        for (int i = 0 ; i < length ; i++   ) {

        
            Value* diff = new Value((output[i][0] -> data - desiredOutput[i][0] -> data) , '-' , output[i][0], desiredOutput[i][0]) ;

            temp[i] = diff ;


        }

            Value** diffSquares = new Value*[length] ;



        for (int i = 0 ; i < length ; i++   ) {

        
            Value* diffSquare =  new Value(temp[i] -> data * temp[i] -> data ,  '*' , temp[i] , temp[i]) ;


            diffSquares[i] = diffSquare ;


        }




        // şuan biz tempi sadece arrayi için kullanıyoruz yani bizim için önemli olan şey valueları birbirine bağlayabilmek
        delete[] temp ; // bunu silmek o yüzden önemli değil , içindeki valuelar silinmiyor çünkü value leri de ayrı new ile tanımladık

        int beforeLength = length ;

        int afterLength ;

         if (length % 2 == 0 ) {

                    afterLength = length / 2 ;

                }

                else {

                    afterLength = ( length / 2 )  + 1 ;


                }

        

        Value** afterArr ;

            while (afterLength != 0) {

                if (afterLength == 1 && beforeLength == 1 ) {
                    
                    break ;
                }

                if (beforeLength % 2 == 0 ) {

                    afterLength = beforeLength / 2 ;

                }

                else {

                    afterLength = ( beforeLength / 2 )  + 1 ;


                }

                if (afterLength == 0 ) break ;


                afterArr = new Value*[afterLength ] ;


                int b = 0 ;

                int a = 0 ;


                    while (a < beforeLength -1) {



                        afterArr[ b++ ] =  new Value( diffSquares[a] -> data + diffSquares[a + 1 ] -> data  , '+' , diffSquares[a] , diffSquares[a+1] ) ;



                        a++;
                        a++;




                    }


                    if (a == beforeLength - 1 ) {

                        afterArr[b++ ]  = new Value(diffSquares[a] -> data , 'p' , diffSquares[a] , NULL  ) ;



                    }

                
                beforeLength = afterLength ;
                delete[] diffSquares ;
                diffSquares = afterArr ; 



            }

                        Value* lossSum = new Value(afterArr[0] -> data , 'p' , afterArr[0], NULL) ; // bu pass demek


                        Value* lengthValue = new Value (lengthDoubleVersion ) ;

                        Value* loss = new Value (lossSum -> data / lengthDoubleVersion , '/' ,  lossSum , lengthValue ) ; // bak buna da label koymadım , en son valuelar silinirken bu da silinecek




            delete[] diffSquares ;










            Value* m = loss ;



        m -> resetGrads (m) ;

        m -> resetVisited( m ) ;


            // BAK BU LOSS GRADI 1 YAPMAK ÇOK ÖNEMLİ, 0 OLURSA ONDAN AKAN GRAD DEĞERLERİ DE 0 OLUR , ZATEN MATEMATİĞE GÖRE DE dLOSS / dLOSS = 1 ' DİR
            loss -> grad = 1 ;

            loss->backward() ;

            //şimdi weight değerlerini güncelleyelim, birden fazla kez olmasın her birine diye, bunda da topological order kullanmayı düşünüyorum


            Value* head = nullptr ;


            loss->buildTopological(loss, head ) ;

            Value* t = head ;


            while (t != NULL ) {

                if ( t->label == "weight" ) {
                    t -> data -= t -> grad * 0.00001 ; // --> LEARNİNG RATE'İ 0.00001 OLARAK KOYDUM KEYFİ
                    // gradyanına tersi yönde learning rate kadar değiştiriyoruz ağırlıkları (nudging the weights deniyormuş buna ingilizcede) 


                    // BİAS VE AKTİVASYON FONKSYİONU EKLEMEM GEREKİYORRRR, O ŞİMDİ AKLIMA GELDİ

                }





                t = t -> nextTopological ;

            }

            Value* l = loss ;


            loss->resetVisited(l) ; // bu ilk loss-> yazıyor ya orası önemli değil sadece value classının methodu olarak tanımlamıştım o methoda erişebilmek için bir value classından kullanmak
            // gerekyior yoksa oradaki loss yazması falan önemli değil













            cout << "loss: "<< loss->data << " , step: " << step << endl ; 



            // her seferinde nöronların içinde arrayler ve nöronlar oluşturduğumuz için (arrayleri oralarda silioyruz ama o forward path i oluşturan valuelar duruyor 
            // bak biz 2 şekilde yapabilirdik :
            // 1. --> bir kere o pathi oluşturup falan sonra o pathteki valuelarin datalarını güncellemek 
            // 2. --> şimdi yaptığımız gibi her seferinde o pathi bir daha kurmak. bu nedenle her stepte aslında biz,  bu pathteki o valueları silmeliyiz çünkü eğer silmezsek sonrakinde yine yenileri oluşurken eskiler
            // memory leake sebep olur, buna dikkat etmemiz lazım.





            
           
            Value* thisHead = nullptr ; // burada da build topological yapmamız gerekecek çünkü aynı value birden fazla parenta bağlıysa delete ederken sadece lossdan left right ile gidersek ona iki kere geliriz
            // ve ilkinde silip delete ettiğimiz için ikinci gelişim

            loss -> buildTopological (loss, thisHead ) ;


            loss -> resetVisited ( loss ) ;




            mlp -> deleteValues (thisHead ) ;

            for (int i = 0 ; i < length ; i ++  ) {

                for (int a = 0 ; a < dimension ; a++ ) {






                    input[i][a] -> visited = false ;



                }







            }


            





















    }










    delete mlp ;
    return 0 ;



}










