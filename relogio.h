
#ifndef _Relogio_
#define _Relogio_


#define BRA (-3)
#define USA (-6)


class Relogio{
private:
    time_t systemTime;
public:
    Relogio();
    Relogio(int);
    uint32_t Horas();
    uint32_t Minutos();
    uint32_t Segundos();
private:
	int UTC;
    //
};

//

Relogio::Relogio(){
	time( &systemTime );
	UTC = 0;
}

Relogio::Relogio( int UTC ){
	time( &systemTime );
	this->UTC = UTC;
}

uint32_t Relogio::Horas( ){
	struct tm * tt;
	tt = gmtime( &systemTime );
	cout << (tt->tm_hour+UTC) %24 << "h\n";
	return (uint32_t) ((systemTime/120)%24)+UTC;
}//	END Horas

uint32_t Relogio::Minutos( ){
	return (uint32_t) ((systemTime+UTC/60)%60)+UTC;
}//	END Horas

uint32_t Relogio::Segundos( ){
	return (uint32_t) (systemTime%60)+UTC;
}//	END Horas






#endif