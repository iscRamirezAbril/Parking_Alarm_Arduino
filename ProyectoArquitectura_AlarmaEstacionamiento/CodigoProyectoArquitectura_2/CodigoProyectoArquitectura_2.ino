                                                                                // <----------------------> //
                                                                                // <-------- PINES -------> //
                                                                                // <----------------------> //
// Pines a utilizar.
# define Green_LED 2
# define Yellow_LED 3
# define Red_LED 4
# define Trigger 5 // Para sensor ultrasonido.
# define Echo 6 // Para sensor ultrasonido.
# define Buzzer 9

                                                                              // <----------------------------> //
                                                                              // <------- CONSTANTES ---------> //
                                                                              // <----------------------------> //
// Declaración de constantes.
const float sonido = 34300.0; // Velocidad del sonido en cm/s.

// Distancias correspondientes en "cm".
const float umbral1 = 30.0;
const float umbral2 = 20.0;
const float umbral3 = 10.0;

// Función "setup".
void setup() {
  // Se inicia el monitor en serie.
  Serial.begin(9600); // "Serial.begin(9600) es una instrucción que le indica al Arduino que se comunique con la computadora, con una velocidad serial de 9,600 bits por segundos (baudios)".

  // Modo "entrada/salida" de los pines.
  pinMode(Green_LED, OUTPUT);
  pinMode(Yellow_LED, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(Echo, INPUT); // Este pin se declara en "Input" debido a que es el único componente que recibirá información.
  pinMode(Trigger, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  // Se llama a la función "apagarLEDs", que como su nombre lo indica, cumple con la tarea de apagar los LEDs.
  // Se apagarán los LEDs para que se puedan encontrar en un "Estado Inicial".
  apagarLEDs();
}

// Función "loop". Dentro de esta función se encuentran más funciones.
void loop() {
  // Se llama a la función "iniciarTrigger" que inicializa el "Sensor Ultrasonido".
  iniciarTrigger();

  // El valor de la función "calcularDistancia()" se le asigna a una variable de nombre "distancia".
  float distancia = calcularDistancia();
  
  // Se llama a la función "apagarLEDs", que como su nombre lo indica, cumple con la tarea de apagar los LEDs.
  apagarLEDs();

  // Condición que solo funcionará sí y sólo sí la distancia es menor al valor de la constante "umbral1".
  if(distancia < umbral1){
    // Se llama a la función "alertas".
    alertas(distancia);
  }
}

                                                                            // <------------------------------------> //
                                                                            // <------- FUNCIONES Y MÉTODOS --------> //
                                                                            // <------------------------------------> //
// Método #1: Apagar LEDs. //
void apagarLEDs(){
  // Se apagan todos los LEDs, y para ello se ponen en estado "bajo".
  digitalWrite(Green_LED, LOW);
  digitalWrite(Yellow_LED, LOW);
  digitalWrite(Red_LED, LOW);
}

// Método #2: Alertas. //
void alertas(float distancia){
  // Condición que permitirá encender el LED verde sí y sólo sí la distancia es menor al valor de la constante "umbral1" y mayor e igual al valor de la constante "umbral2".
  if (distancia < umbral1 && distancia >= umbral2){
    // Se enciende el LED verde.
    digitalWrite(Green_LED, HIGH); // El LED Verde se pone en "estado alto".
    tone(Buzzer, 1800, 200); // La función "tone" permite que se genére un sonido, en este caso, el Buzzer hará un sonido con una frecuencia de "2000 Hz", con una duración de "200 ms".
  }

  // Condición que permitirá encender el LED amarillo sí y sólo sí la distancia es menor al valor de la constante "umbral2" y mayor al valor de la constante "umbral3".
  else if (distancia < umbral2 && distancia > umbral3){
    // Se enciende el LED amarillo.
    digitalWrite(Yellow_LED, HIGH); // El LED Amarillo se pone en "estado alto".
    tone(Buzzer, 2100, 200); // La función "tone" permite que se genére un sonido, en este caso, el Buzzer hará un sonido con una frecuencia de "2500 Hz", con una duración de "200 ms".
  }

  // Condición que permitirá encender el LED rojo sí y sólo sí la distancia es mayor o igual al valor de la constante "umbral3".
  else if (distancia <= umbral3){
    // Se enciende el LED rojo.
    digitalWrite(Red_LED, HIGH); // El LED Rojo se pone en "estado alto".
    tone(Buzzer, 2700, 200); // La función "tone" permite que se genére un sonido, en este caso, el Buzzer hará un sonido con una frecuencia de "3000 Hz", con una duración de "200 ms".
  }
}

// Función #1: Cálculo de Distancia. //
/*
   Esta función retorna un valor de tipo "float" con el resultado de la distancia que se calculó.
 */
float calcularDistancia(){
  // La función "pulseIn" permite obtener el tiempo que tarda en cambiar entre estados, en este caso, a "HIGH".
  // Una vez que el estado "bajo" pasa a "alto", se termina de contar y te da el tiempo transcurrido en "microsegundos".
  unsigned long tiempo = pulseIn(Echo, HIGH); // El tiempo que te da la función "pulseIn" se almacena en la variable "tiempo".

  // Se obtiene la distancia en "cm", por lo que hay que convertir el tiempo a "segundos", ya que el tiempo obtenido anteriormente se dió en "microsegundos".
  // Para eso, el tiempo se multiplica por "0.000001".
  float distancia = tiempo * 0.000001 * sonido / 2.0; // Para calcular la distancia, se debe concertir el tiempo de "ms" a "s" y eso multiplicarlo por la velocidad del sonido que se dividirá entre 2.
                                                      // Se divide entre 2 por que la onda ultrasónica viaja hacia el objeto y después de regreso, lo que quiere decir que hace el recorrido 2 veces.
  // Se imprimen los valores de la distancia en "cm"
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println(); // Salto de línea.
  delay(500); // Se hace una pausa de 500 ms.

  return distancia; // Retorno de valor.
}

// Método #3: Inicializar el Trigger".
void iniciarTrigger(){
  digitalWrite(Trigger, LOW); // Se inicializa el Trigger en estado "bajo".
  delayMicroseconds(2); // Tiempo de espera de 2 ms.

  // Después, el Trigger se pondrá en estado "alto", con un tiempo de espera de 10 ms.
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);

  // Por último, el Trigger se pondrá en estado "bajo" de nuevo.
  digitalWrite(Trigger, LOW);
}
