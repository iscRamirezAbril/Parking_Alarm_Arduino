// Pines a utilizar.
# define Green_LED 2
# define Yellow_LED 3
# define Red_LED 4
# define Trigger 5 // Para sensor ultrasonido.
# define Echo 6 // Para sensor ultrasonido.
# define Buzzer 9

// Declaración de constantes.
const float sonido = 34300.0; // Velocidad del sonido en cm/s.
const float umbral1 = 30.0;
const float umbral2 = 20.0;
const float umbral3 = 10.0;

// Función "setup".
void setup() {
  // Se inicia el monitor en serie.
  Serial.begin(9600);

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

  // Condición que solo funcionará sí y sólo sí la distancia es mayor al valor de la constante "umbral1".
  if(distancia < umbral1){
    // Se llama a la función "alertas".
    alertas(distancia);
  }
  }
}
