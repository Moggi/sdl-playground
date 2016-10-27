
//


#include "includes.h"




class MyException{
private:
    int x;
public:
    MyException(){}
    MyException(int a){ x=a; }
    int what(){ return x; }
};

int divide(int a, int b){
    if(b==0)
        throw MyException(b);
    return a/b;
}

int isdst(tm * ptm){
    return ptm->tm_isdst > 0 ? 1 : 0;
}

/*
 *  void relogio( ){
 *      minA = ptm->tm_min;
 *      if( minD!=minA ){
 *          printf("Horario : %2d:%02d\n", (ptm->tm_hour+BRA+isdst(ptm))%24, ptm->tm_min);
 *          minD = minA;
 *      }
 *      time ( &rawtime );
 *      ptm = gmtime ( &rawtime );
 *  }
 */

int main()
{
    /*
    time_t rawtime;
    int minA, minD = 0;
    time ( &rawtime );
    minD = minA = rawtime/60;
    //
    while( true ){
        time ( &rawtime );
        minA = rawtime/60;
        if( minD != minA ){
            printf("Minutos : %02d\n", minA%60);
            minD = minA;
        }
    }
    */
    Relogio Timer(BRA);
    cout << Timer.Horas() << "h -\n";

    /*
    try{
        divide(2,0);
    }
    catch(MyException & e){
        cout << "Dividendo = " << e.what() << endl;
        //
    }
    */
    return 0;
}







//