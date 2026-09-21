#include "Value.h"
#include <iostream>
#include <string> 



using namespace std ;


// NORMALDE BU DOSYA BOYUNCA VALUE LARI DİNAMİK OLMAYACAK ŞEKİLDE TANIMILCAKTIM BU SAYEDE DELETE E GEREK KALMAZDI AMA BÖYLE YAPAMADIM BU PROJEYİ ÇÜNKÜ 
// BİZ BU VALUELARI TÜM NÖRONLARIN ÇIKTILARINI MESELA TOPLARKEN BİR ARRAYE KOYMAMIZ GEREKİYOR SONRA ÇIKANI YİNE İLK ARRAYİN YARISI KADAR BİR ARRATE KOYMAMIZ GEREKİYOR TOPLUCA HEPSİNİ TOPLAYAMIYORUZ ÇÜNKÜ 
// BİZ VALUELARDA "+" OPERATORINI TANIMLARKEN LEFT VE RİGHT İKİ TANE GİRİŞİ OLACAK DİYE OVERLOAD ETTİK VE BUNA GÖRE BACKPROPAGATİON ALGORİTMASINI VE TÜREB İŞLEMLERİNİ (GRAD DEĞERLERİNİ ) YAZDIK O VALUELARIN
// EE SONUÇ OLARAK BUNLARI İKİLİ İKİLİ TOPLAMAMIZ GEREKECEK VE BUNUN İÇİN DE HER LAYERDA BİR SÜRÜ BUNLARI ARRAYE KOYMAK GEREKECEKTİ. BU İŞİN SIKINTISI ŞU Kİ EĞER BUNLARI ARRAYE KOYARSAM VE BU VALUE LAR DİNAMİK OLMAZSA
// SONRA ARRAYİ SİLMEM GEREKTİĞİNDE ARRAYİ DELETE DERSEM , BU VALUE LAR DA SİLİNİR , AMA BU VALUELAR DİNAMİK OLDUKALRINDA HİÇ BÖYLE BİR SIKINTI ÇIKMIYOR , ARRAYİ RAHATÇA SİLEBİLİYORUM AMA TABİ DİNAMİK YAPTIĞIM İÇİN VALUELERİ
// ONLARIN DELETELERİNİ DOĞRU YAPMAKLA BAYA UĞRAŞMAM GEREKTİ


// ARRAYİ DE DİNAMİK OLARAK TANIMLAMAK ZORUNDAYIM ÇÜNKÜ DİNAMİK TANIMLAMADĞIM DURUM MÜMKÜN DEĞİL ÇÜNKÜ WEİGHTNUMBER , LENGTH GİBİ ŞEYLER RUNTİME'DA BELİRLENİYOR , (MESELA BOYUTU DERLEME ANINDA BİLİNMİYOR)
// AYRICA DİYLEİM Kİ ARRAYLERİ HİÇ DELETE ETMEYECEK (Kİ ZATEN YUKARIDA AÇIKLADĞIĞIM SEBEPTEN DOLAYI DİNAMİK OLMAK ZORUNDALAR) ŞEKİLDE İÇİNDEKİ VALUE LAR DA DİNAMİK OLMADAN ARRAYDE DURUYORLAR DİYELİM
// O ZAMAN DA BU DA ÇALIŞMAZ ÇÜNKÜ BİR SÜRE SONRA TRAİNİNG BOYUNCA BU ARRAYLER MEMORY Yİ AŞIRI DOLDURUR
// SİLİNMEDEN ÖYLE DURDUKLARI İÇİN BİR SÜRE SONRA OUT OF MEMORY YERİZ (TAMAM ARRAY İN ÖMRÜ KISA AMA İÇİNDEKİ VALUELAR BACKWARD() FONKSİYONU BİTENE KADAR HAYATTA KALMALILAR , EN EN EN SON SİLİNMELİLER --> YANİ ARRAYLERLE VALUELARIN ÖMRÜ FARKLI)




void Value:: backward() {


    // önce toplogic sort yapp erdem


    Value* topoHead = nullptr ;



    buildTopological(this, topoHead ) ;
    Value* x = topoHead ;


    while (topoHead != NULL ) {




        // topoHead -> func == ' ' ise -> bundan daha fazla geri gidilemez. yani bu weight ya da inputtur  // ondan dolayı o kısım if (topoHead -> func != NULL ) 'da eleniyor zaten giremez o ife





        if (topoHead->left != NULL ) { // bu aşağıdaki commentli ifler yanlış olurdu çünkü onlar topologic sortinge uymazdı böyle düzelttim


            if (topoHead->func == '*') {


                topoHead->left->grad  += topoHead->right->data * topoHead->grad  ; // bak bu gradla çarpmayı unutma --> chain rule var

                topoHead->right -> grad += topoHead->left -> data * topoHead->grad ;



                    // if (left -> left != NULL  ) ( left -> left )->backward() ;
                    // if (left -> right != NULL ) ( left -> right ) -> backward() ;



                    // if (right -> left != NULL  ) ( right -> left )->backward() ;
                    // if (right -> right != NULL ) ( right -> right ) -> backward() ;






            }

            else if (topoHead->func == 't') { // tan

                topoHead->left -> grad += ((1.0 - topoHead->data * topoHead-> data)) * topoHead->grad ;



                // if (left -> left != NULL  ) ( left -> left )->backward() ;
                // if (left -> right != NULL ) ( left -> right ) -> backward() ;



                
            }

            else if (topoHead->func == 'p') { // pass --> direk alındıysa yani bir fonksiyonla oluşmadıysa


                topoHead -> left -> grad += topoHead -> grad ;

            }

            else if (topoHead->func == '/') { // --> left / right

                topoHead->left-> grad += (1 / topoHead->right-> data ) * topoHead->grad ;

                topoHead->right -> grad += -1 * (topoHead->left -> data / (topoHead->right -> data * topoHead->right -> data )) * topoHead->grad ;




                // if (left -> left != NULL  ) ( left -> left )->backward() ;
                // if (left -> right != NULL ) ( left -> right ) -> backward() ;



                // if (right -> left != NULL  ) ( right -> left )->backward() ;
                // if (right -> right != NULL ) ( right -> right ) -> backward() ;


                
            }

            else if (topoHead->func == '-') { // --> left - right


                topoHead->left -> grad += 1 * topoHead->grad ;

                topoHead->right -> grad += -1 * topoHead->grad ;




                    // if (left -> left != NULL  ) ( left -> left )->backward() ;
                    // if (left -> right != NULL ) ( left -> right ) -> backward() ;



                    // if (right -> left != NULL  ) ( right -> left )->backward() ;
                    // if (right -> right != NULL ) ( right -> right ) -> backward() ;



                
            }

            else if (topoHead->func == '+') {


                topoHead->left -> grad += 1 * topoHead->grad ;

                topoHead->right -> grad += 1 * topoHead->grad ;




                // if (left -> left != NULL  ) ( left -> left )->backward() ;
                // if (left -> right != NULL ) ( left -> right ) -> backward() ;



                // if (right -> left != NULL  ) ( right -> left )->backward() ;
                // if (right -> right != NULL ) ( right -> right ) -> backward() ;



                
                
            }


            else if (topoHead->func == 'r') { // relu --> relu ile oluştuysa left'i var , right'ı = NULL olacak


                if (topoHead->left -> data > 0  ) { // data = left -> data

                    topoHead->left -> grad += topoHead->grad ;


                // if (left -> left != NULL  ) ( left -> left )->backward() ;
                // if (left -> right != NULL ) ( left -> right ) -> backward() ;



                }

                else { // data = 0

                    topoHead->left -> grad += 0 ; // çünkü bundaki değişim bir şeyi etkilemicek zaten sonuca 0 koyuyoruz bu left -> data negatif olduğu için!!!





                    // if (left -> left != NULL  ) ( left -> left )->backward() ;
                    // if (left -> right != NULL ) ( left -> right ) -> backward() ;



                }

                // bu if statementların içinde topohead -> nextTopological değil de normal direkt topohead -> left ya da topohead -> right falan yazmalısın çünkü gradyan akışı gerçekten o valueları oluşturanlara doğru kaymalı
                // bu build topological sadece hepsini bir kez ve sondan başa doğru ziyaret edebilmemizi sağlıyor


                
            }




    }


        

        topoHead = topoHead->nextTopological ;

    }






    
resetVisited(x) ;



}



    Value:: Value (double val , char funct, string lab ) {

        this->data = val ;
        this->func = funct ;
        this->left = NULL ;
        this->right = NULL ;
        this->grad = 0.0 ;
        this -> label = lab ;
        this->visited = false;
        this->nextTopological = nullptr;
        

    }


    Value:: Value (double val , char funct , Value* value1, Value* value2 , string lab)  {
        this->data = val ;
        this->func = funct ;
        this->left = value1 ;
        this->right = value2 ;
        this->grad = 0.0 ;
        this -> label = lab ;
        this->visited = false;
        this->nextTopological = nullptr;
    }

    Value :: Value (double val ) {



    this->data = val ;
    this->left = NULL ;
    this->right = NULL ;
    this->func = ' ' ;
    this->grad = 0.0 ;
    this->label = "" ;
    this->visited = false;
    this->nextTopological = nullptr;


    }


    Value:: Value (double val , char funct , Value* value1, Value* value2)  {
        this->data = val ;
        this->func = funct ;
        this->left = value1 ;
        this->right = value2 ;
        this->grad = 0.0 ;
        this->visited = false;
        this->nextTopological = nullptr;
        this -> label = "" ;
    }


    Value::Value(double data1 , string lab)
{
    this -> grad = 0.0 ;

    this -> data = data1 ;

    this->left  = NULL ;
    this->right = NULL ;


    this-> func = ' ' ;
    this -> label = lab ;
    this->visited = false;
    this->nextTopological = nullptr;





}

Value:: Value() {
    this->data = 0.0 ;
    this->left = NULL ;
    this->right = NULL ;
    this->func = ' ' ;
    this->grad = 0.0 ;
    this->label = "" ;
    this->visited = false;
    this->nextTopological = nullptr;
}



void Value:: hey(double val , char funct , Value* value1, Value* value2, string lab) {
    this->data = val ;
    this->func = funct ;
    this->left = value1 ;
    this->right = value2 ;
    this->grad = 0.0 ;
    this -> label = lab ;
    this->visited = false;
    this->nextTopological = nullptr;

}


Value::~Value()
{


}







Value operator* (Value& left , Value& right ) {
    return Value (left.data*right.data , '*' , &left, &right ) ;
}


 Value operator+ (Value& left , Value& right) {
    return Value (left.data + right.data , '+' , &left, &right ) ;

}

 Value operator- (Value& left , Value& right) {
    return Value (left.data - right.data , '-' , &left, &right ) ;

}

 Value operator/ (Value& left , Value& right) {
    
    return Value (left.data / right.data , '/' , &left, &right ) ;

}




Value Value:: tanjant() {

    return Value(tanh(data) , 't' , this, NULL) ;



}


Value Value:: relu() {

        return Value(data > 0 ? data : 0   , 'r' , this, NULL) ;
    
}




// void buildTopological(Value* loss ) {

//     Value* head = nullptr ;
//     Value* tail = nullptr ;


    
//     Value* temp = loss ;




//     while ( temp != NULL ){

//         if (loss -> visited = false ) {
//             temp = loss ;
//         }

//         while ( temp-> left != NULL ||  temp -> right != NULL  ) {

//             if (temp -> left == NULL && temp -> right -> visited == false  ) temp = temp -> right ;

//             else if (temp -> right == NULL&& temp -> left -> visited == false  ) {
//                 temp = temp -> left ;

//             }

            

//         }

//         temp -> visited = true ;

//         if (head == nullptr ){
//             head = temp ;
//             tail = temp ;

//         }

//         else {


//             tail -> nextTopological = temp ;
//             tail = tail->nextTopological ;
            

//         }


//     }






// }




void Value :: buildTopological(Value* current , Value* & head ) { // bu ters şekilşde koyar yani son durumda head = loss olur, bu sayede tekrar terse çevirmeye gerek kalmadan direkt bunun
// sırasıyla backward() yani back propagation yapacağız
    if ( current == NULL || current -> visited == true) return ;

    current -> visited = true ;

    buildTopological(current->left , head ) ;
    buildTopological(current -> right , head ) ;

    current -> nextTopological = head ;
    head = current ;













}





void Value :: resetVisited(Value* head ) {
    if (head == NULL || head -> visited == false ) return ; // buradaki visited kontrolü de önemli . sonsuz döngüye girmesin diye! buna dikkat et , unutma

    head -> visited = false ;

    resetVisited(head -> left ) ;
    resetVisited(head -> right ) ;




    
}


void Value:: play() {



Value a(2.0 ,  "a" ) ;
Value b (-3.0 ,"b" ) ;


Value c (10.0, "c" ) ;
Value e = a * b ;
e.label = "e" ;
Value d = c * e ;
d.label = "d" ;

Value f (-2.0 , "f" ) ;


Value L = f * d ;
L.label = "L" ;




Value x1(2.0, "x1" ) ;
Value x2(0.0 , "x2");

Value w1(-3.0 , "x3") ;
Value w2(1.0, "x4") ;


Value bias(6.8813735870195432, "bias") ;

Value x1w1 = x1 * w1 ;
x1w1.label ="x1w1" ;
Value x2w2 = x2 * w2 ;
x2w2.label = "x2w2" ;


Value x1w1x2w2 = x1w1 + x2w2 ;
x1w1x2w2.label = "x1w1x2w2" ;

Value n = x1w1x2w2 +  bias ;
n.label = "n" ;
Value o = n.tanjant() ;
o.label = "o" ;
o.resetGrads(&o) ;

o.grad = 1 ; // sonuncunun gradı 1 olmalı onu unutma


o.resetVisited(&o) ;


o.backward() ;

    

o.write(&o) ; // BAK BÖYLE ADRES GÖNDEREBİLİRSİN ORADA POİNTER ALIYOR , POİNTER BUNU GÖSTERECEK




}

 void Value:: write(Value* loss) {
    if (loss == NULL ) {
        return ;
    }

    else {



        cout << "data: " << ( loss -> data)  << " , grad: " << (loss -> grad ) << " , label: " << loss -> label  << endl ;

        write((loss->left)) ;
        write(loss-> right ) ;


    }


}


void Value:: resetGrads(Value* val ) {


    if (val == NULL || val -> visited == true ) return ;


    val-> visited = true ;
    val -> grad = 0 ;

    resetGrads(val->left) ;
    resetGrads(val-> right) ;





}







