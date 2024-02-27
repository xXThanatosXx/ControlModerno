int u;
int strEntero;
String cadena = "";
double xk =0;
double ukm1 = 0;
double xkm1 = 0;
double ukm2 = 0;
double xkm2 = 0;
int i = 1;

void setup() {
  Serial.begin(115200);
}

void loop() {
  while(Serial.available()>0)
  {
    int intChar = Serial.read();
    if(isDigit(intChar)) cadena+=(char)intChar; //almacena en cadena el caracter numero
    if(intChar=='\n'){
      
        strEntero = cadena.toInt();
        cadena ="";
      }  
  }

  static unsigned long tiempoInicial = 0;  // variable para almacenar el tiempo inicial
  unsigned long tiempoActual = millis();  // variable para almacenar el tiempo actual
  //Tiempo de muestreo 1 seg
  const int ts = 1000; 
  if (tiempoActual - tiempoInicial >= ts) {  // si ha pasado el tiempo deseado
      ProcessControl();
      tiempoInicial = tiempoActual;  // actualizar el tiempo inicial
  }
}

void ProcessControl()
{
  u = strEntero;
  //Planta de primer orden
   xk=ukm1*0.3679+ukm2*0.2642+xkm1*1.368-xkm2*0.3679; //Ts=1 seg

  if (i>1) {
    ukm2=ukm1;
    xkm2=xkm1; 
  }
  xkm1=xk;
  ukm1 = 1*u;

  i=+1;
  Serial.print(u);
  Serial.print(", ");
  Serial.println(xk);
  i+=1;
  
}
