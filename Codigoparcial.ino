#define SER 5
#define RCLX 2
#define SRLK 3
String mensaje0 = "1 - Verificar matriz, 2 - Ingresar una Imagen, 3 - Secuencia patrones predefindios";
String mensaje1 = "Ingrese una opcion: ";
void borrarPatron(int *ptr) {
    delete []ptr;
}
void *verificacion(){
    unsigned int cantsecuencia;
    unsigned long t=time();
    cantsecuencia=Cantsecuencia();
  int bin;
    int *apuntador= new int[8];
    for(int fil = 0;fil < 8; fil++){
        bin=0b00000000;
    apuntador[fil]=bin;
            }
  printmatrizbasica(t,cantsecuencia,apuntador);
}
void *imagen(){
  unsigned int cantsecuencia;
  unsigned long t=time();
  cantsecuencia=Cantsecuencia();
  int n;
  int *apuntador= new int[8];
  for (int i=0;i<8;i++){
    n=convertirbin();
    apuntador[i]=n;
  }
  printmatrizbasica(t,cantsecuencia,apuntador);
}
int convertirbin(){
  int n;
  Serial.print("Ingrese un numero entre 0 y 255");
  Serial.print("\n");
  while(Serial.available() == 0){}
    n = Serial.parseInt();
    if((n >= 0) && (n <= 255)) {
        n=n-255;
      n=n*-1;
      return n;
    }else{
      Serial.println("Valor incorrecto");
    }
  
}
unsigned long time(){
    unsigned int t;
    while(true) {
        Serial.println("Ingrese cuantos segundos hasta el cambio de estado");
        while(Serial.available() == 0){}
        t = Serial.parseInt();
        if(t > 0) {
            Serial.print("El valor ingresado fue de: ");
            Serial.println(t);
            break;
        }
        else {
            Serial.println("No se puede ingresar tiempo negativo intente de nuevo");
        }
    }
    return t*1000;
}
unsigned int Cantsecuencia(){
    unsigned int cc;
    while(true) {
        Serial.println("Ingrese cuantas repeticiones hay que realizar: ");
        while(Serial.available() == 0){}
        cc = Serial.parseInt();
        if(cc > 0) {
            break;
        }
        else {
            Serial.println("No se puede ingresar una cant de repecticiones negativas");
        }
    }
    return cc;
}
void printmatrizbasica(unsigned long tiempo,unsigned int Cantsecuencia,int *columna){
  unsigned long long checkpoint=millis();
  int fila[] = {128,64,32,16,8, 4, 2,1},cc=0;
  bool state= true;
  while(true){
    if((millis()-checkpoint)>tiempo){
      checkpoint=millis();
      state=!state;
      cc=cc+1;
    }if(cc>=((2*Cantsecuencia)-1))
    {break;}
    if(state){
      for(int i = 0; i < 8; i++) {
      shiftOut(SER,RCLX,LSBFIRST,*(columna+i));
      shiftOut(SER,RCLX,MSBFIRST,fila[i]);
      digitalWrite(SRLK,HIGH);
      digitalWrite(SRLK,LOW);
      }}else{
       for(int i = 0; i < 8; i++) {
      shiftOut(SER,RCLX,LSBFIRST,255);
      shiftOut(SER,RCLX,MSBFIRST,fila[i]);
      digitalWrite(SRLK,HIGH);
      digitalWrite(SRLK,LOW);
       }}
  }
   borrarPatron(columna);
}
int *patron1(){
   int Contadorespacio=3,bin,contadorleds=2,l=1;
  int *apuntador= new int[8];
    for (int col=0;col<4;col++){
        int contadorparcialleds=0,contparcialespacios=0;
        bin=0b11111111;
        for (int fil=0;fil<8;fil++){
            if(contparcialespacios<Contadorespacio){
                contparcialespacios=contparcialespacios+1;

            }else if(contadorparcialleds<contadorleds){
                bitWrite(bin, fil, 0);
                contadorparcialleds=contadorparcialleds+1;
                if(contadorparcialleds==contadorleds)
                    contparcialespacios=0;
            }
            }
            Contadorespacio=Contadorespacio-1;
            contadorleds=contadorleds+2;
          apuntador[col]=bin;
}
      for(int col=4;col<8;col++){
            apuntador[col]=apuntador[col-l];
            l=l+2;
        }
  return apuntador;
}
int *patron3(){
  int v=0,bin;
  int *apuntador= new int[8];
    for (int col=0;col<8;col++){
        bin = 0b11111111;
        for (int fil=7;fil>=0;fil--){
            if(col%2==0){
                if(fil==7){
                    if(v==1)
                        v=0;
                }
                if(v!=2){
                    bitWrite(bin, fil, 0);
                    v=v+1;
                }else{
                    v=0;
                }
            }else{
                if(fil==7){
                    if(v==2)
                        v=0;
                    else
                        v=2;
                }
                if(v!=2){
                    bitWrite(bin, fil, 0);
                    v=v+1;
                }else{
                    v=0;
                }
            } 
        }
      apuntador[col]=bin;
    }
  return apuntador;
}
int *patron4(){
  int l=1,bin;
  int *apuntador= new int[8];
    char arre[8]={1,1,1,1,0,0,0,0};
    for(int fil = 0;fil < 4; fil++){
      bin=0b00000000;
        for(int col = 0;col < 8; col++){
            bitWrite(bin, col, arre[col]);
        }for(int k=0;k<8;k++){
            arre[k]=arre[k+1];
        }apuntador[fil]=bin;
      arre[7]=1;
    }
    for(int fil=4;fil<8;fil++){
        for (int col=0;col<8;col++){
            apuntador[fil]=apuntador[fil-l];
        }l=l+2;
    }
  return apuntador;
}
int *patron2(){
    int bin;
    int *apuntador= new int[8];
    for(int fil = 0;fil < 8; fil++){
        bin=0b11111111;
         for(int col = 0;col < 8; col++){
            if(fil==col||fil+col==7){
                bitWrite(bin, col, 0);
            }
            }
      apuntador[fil]=bin;
    }
  return apuntador;
}
void imprimirConTiempo(unsigned long tiempo,int *columna){
  unsigned long long checkpoint=millis();
  int fila[] = {128,64,32,16,8, 4, 2,1};
  bool state=true;
  while(true){
  if((millis()-checkpoint)>tiempo){
    break;}
  if(state){
    for(int i = 0; i < 8; i++) {
    shiftOut(SER,RCLX,LSBFIRST,*(columna+i));
    shiftOut(SER,RCLX,MSBFIRST,fila[i]);
    digitalWrite(SRLK,HIGH);
    digitalWrite(SRLK,LOW);
      }
  }}
   borrarPatron(columna);
}
void secuencia(){
  unsigned int cantsecuencia;
  unsigned long t=time();
  cantsecuencia=Cantsecuencia();
  int *patro1=patron1(),*patro2=patron2(),*patro3=patron3(),*patro4=patron4();
  for (int i=0;i<cantsecuencia;i++){
    imprimirConTiempo(t,patro1);
    imprimirConTiempo(t,patro2);
    imprimirConTiempo(t,patro3);
    imprimirConTiempo(t,patro4);
  }
}
void publik(){
   Serial.println(mensaje0);
    while(Serial.available() == 0){}
    int opcion = Serial.parseInt();
    switch(opcion) {
      case 1:{
        verificacion();
        break;}
      case 2:{
        imagen();
        break;}
      case 3:{
        secuencia();
        break;}
      default:{
        Serial.println("Valor incorrecto, intente otra vez");} 
    }}
void setup()
{
  pinMode(SER, OUTPUT);
  pinMode(RCLX, OUTPUT);
  pinMode(SRLK, OUTPUT);
  Serial.begin(9600);
}
int ControlFil[] = {128,64,32,16,8, 4, 2, 1};
int *ControlCol;
static int kk=0;
void loop()
{
  publik();
  
  }
