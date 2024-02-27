int u;
int strEntero;
String cadena = "";
double xk =0;
double ukm1 = 0;
double xkm1 = 0;
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
  //Tiempo de muestreo
  const int ts = 500; //Tiempo de muestreo 500 ms
  if (tiempoActual - tiempoInicial >= ts) {  // si ha pasado el tiempo deseado
      ProcessControl();
      tiempoInicial = tiempoActual;  // actualizar el tiempo inicial
  }
}

void ProcessControl()
{
  u = strEntero;
  //Planta de primer orden
  xk = ukm1*0.3938+xkm1*0.6063;//T=0.5 segundos 
  xkm1 = xk;
  ukm1 = 10*u;
 
  Serial.print(u);
  Serial.print(", ");
  Serial.println(xk);
  i+=1;
  
}
