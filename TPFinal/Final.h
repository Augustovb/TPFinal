/* 
 * File:   Final.h
 * Author: augustovb
 *
 * Created on June 25, 2014, 1:30 AM
 */
#ifndef LODELAFT
#define LODELAFT
void writeFTDI (unsigned char data);
unsigned char readFTDI (void);
int readBUTTONS (void);
#define ARRIBA			1		
#define IZQUIERDA		2
#define DERECHA			3
#define MEDIO			4
#define ABAJO			5
#endif

#ifndef FINAL_H
#define	FINAL_H

#define IO 0x1F


/*Estructura utilizada para chequear la data personalisable del usuario*/
typedef struct{ 
    char usuario[20];
    int compania;
    struct{
        ALLEGRO_COLOR colorfondo;         //si empieza en 0, es el default, de la compania
        int entro;
    }fondo;
    char mensajepersonal[140];  //podra tener un mensaje personal de 140 caracteres
    struct{
        ALLEGRO_COLOR colormensaje;
        int tipocolor;
    }mensajecolor;    
    int tamanomensaje;          // si es mayor al del que entraria en la pantalla, se toma como el predeterminado(12)
    int tipoescritura;
}INFOPANTALLA;

/*
 * Definicion de funciones
 */




/*Toma la data inicial del userdata*/
INFOPANTALLA getuserdata(void);




/*Pone la data principal*/
void putuserdata (INFOPANTALLA mipantalla);





/*Configura el mantenerconfiguracion*/
void mantenerconfiguracion(int * estadoconfiguracion,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla,ALLEGRO_EVENT_QUEUE* eventos, int* pestado,INFOPANTALLA* mipantalla);

int analizartecladofiesta (ALLEGRO_EVENT_QUEUE* eventos, int* pestado ,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla);
void dontstoptheparty (int* pestado, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla);
void fiesta (ALLEGRO_EVENT_QUEUE* eventos, int* pestado ,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla);

/*analiza el eclado estando en la configuracion*/
int analizartecladoconfiguracion (ALLEGRO_EVENT_QUEUE* eventos,int* estadoconfiguracion, int* pestado,INFOPANTALLA* pantalla);





/*Analiza el teclado cuando esta en el menu*/
int analizartecladomenu (ALLEGRO_EVENT_QUEUE* eventos,int* pestado,int* estadomenu);





/*Mantiene el menu*/
void mantenermenu(int* pestado, int* estadomenu,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla, INFOPANTALLA mipantalla);






/*Es la forma de ver el teclado mientras se esta en este estado*/
int analizartecladopantalla (ALLEGRO_EVENT_QUEUE* eventos,int* pestado,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla);






/*Cada vez que se vuelve al estado de pantalla, se actualiza segn los datos*/
void mantenerpantalla(INFOPANTALLA datos,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla);






/* La idea es que el usuario tenga cosas personalizables, que se guardaran en la estructura llamada pantalla, esta funcion
 * dependiendo de las configuraciones niniciales, hara lo mismo
 *
 */

void iniciarpantalla(INFOPANTALLA datos, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla);



int tecladoCLASSIC3 (ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_BITMAP* pantalla, ALLEGRO_DISPLAY* display, INFOPANTALLA* mipantalla, int* pestado);
void escribirmensaje(ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_DISPLAY* display,ALLEGRO_BITMAP* pantalla,int*pestado,INFOPANTALLA* mipantalla);



/*Crea una fuente (del estilo predeterminado) del tamaño pedido*/
ALLEGRO_FONT* crearfuente (int tamano);






/*Inicializara los componentes de allegro*/







/*Estas res funciones devuelven un puntero a estructuras de tipo allegro*/
ALLEGRO_DISPLAY* getdisplay(int ancho, int alto);   //devuelve el display con el alto y ancho pedido
ALLEGRO_EVENT_QUEUE* geteventqueue (void);
ALLEGRO_TIMER* gettimer (float periodo);             //un timer que genera eventos por cada periodo




/*      cambiopantalla()
 *  Esta funcion es muy importante para realizarle cambios a la pantalla de nuestro celular.
 * SE DEBE LLAMAR A ESTA FUNCION DOS VECES, para modificar cierto bitmap, en nuestro caso la pantala
 * una vez antes de realizar los cambios, y otra despues. 
 * 
 * Esta fucion automatiza la cantidad de veces que deberemos actualizar la pantalla
 * 
 */

void cambiopantalla (ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla);





/*      analizarteclado()
 *      Esta funcion se encarga de analizar, por medio del mouse, las teclas que se aprietan en el teclado virtual de el celular
 * 
 */

int analizarteclado (ALLEGRO_EVENT_QUEUE* eventos);



/*Escribe el contenido deun array en pantalla */
void ponerarrayenpantalla (char* arreglo,int x,int y,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla);

/*Funciones para manejo de tecladoclasico */
int tecladoCLASSIC1 (ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_BITMAP* pantalla, ALLEGRO_DISPLAY* display, INFOPANTALLA* mipantalla, int* pestado, int* estadoconfiguracion);
int tecladoCLASSIC2 (ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_BITMAP* pantalla, ALLEGRO_DISPLAY* display, INFOPANTALLA* mipantalla, int* pestado, int* estadoconfiguracion);
int character_switcher_right (char *letra, char contador);
int character_switcher_left (char *letra, char contador);
char *user_types_classically (char *palabra, char tecla);
void clearclassicarray (char *array);
char *buscador_de_espacios (char *);
void copy_2_lines (char texto[]);



/*Constantes del t9*/
/*Constantes*/

#define TRUE 1
#define FALSE 0

/*Prototipos*/

/*Funcion principal de este archivo*/
/*Funcion que funciona como un T9. En base a permutaciones de letras "adivina" las palabras del usuario*/
void Te9 (void);


int tecladoT9 (ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_BITMAP* pantalla,ALLEGRO_DISPLAY* display);
int tecladoT92 (ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_BITMAP* pantalla,ALLEGRO_DISPLAY* display,INFOPANTALLA* mipantalla,int* pestadoconfiguracion);

/*Funcion que inicializa el diccionario correspondiente, segun el idioma elegio*/
void init_dictionary (void);


/*Funcion que busca en el diccionario si la palabra existe o no*/
/*Recibe un puntero de tipo FILE al diccionario y la palabra que se quiere buscar*/
/*Por ahora solo muestra en pantalla que existe*/
void checkfromdic (FILE *diccionario, char *);


/*Funcion recursiva que analiza todas las permutaciones de letras posibles*/
/*Recibe: puntero a donde esta la palabra, puntero a donde va a escribir la permutacion, puntero a diccionario*/
/*Recibe un offset (debe ser 0, arreglar esto despues*/
/*Recibe la cantidad de caracteres de la palabra a permutar (largo)*/
/*Si hay coincidencia, lo muestra en pantalla*/
void analisis_recursividad (char *destino, char *escritura, char offset, char largo, FILE*);


/*Funcion que recibe los numeros que teclea el usuario (que son en realidad letras de palabras)*/
/*Recibe un puntero a un arreglo donde dejara lo que el usuario tecleo*/
/*Devuelve LA EXPANSION de lo que el usuario tecleo.
Ejemplo: si se presiona un 2, el mismo se expande como abc2, para que queden todas las combinaciones posibles*/
void usertypes (char);


/*Funcion que analiza si la permutación devuelta por la funcion permutacion es valida o no (tiene numeros o no)*/
/*Recibe un puntero al arreglo donde se aloja la permutacion*/
/*Devuelve TRUE si la permutacion es valida o FALSE si es invalida*/
int permutacionvalida (char *);


/*Funcion que establece a que seccion del diccionario recurrir para buscar la palabra (su finalidad es optimizar el algoritmo)*/
/*Recibe un puntero al array donde está la palabra que se quiere buscar*/
/*Devuelve el puntero a file del diccionario correspondiente*/
FILE *diccswitcher (char *);


/*Funcion que limpia un array y lo deja todo en 0*/ 
/*Recibe: puntero al inicio del array*/
void cleararray (char *array);

/*Funcion que divide un arreglo (que es una oracion) en arreglos mas pequeños que representan lineas, para mandar a ALLEGRO*/
/*Recibe: el arreglo que se desea particionar*/
/*Devuelve el texto partido en 5 arreglos diferentes*/
void copy_T9_lines (char texto[]);

/*Funcion que le permite al usuario elegir las distintas coincidencias del diccionario*/
/*Recibe un puntero que sirve de cursor entre las opciones*/
/*Devuelve la opcion escrita (en vivo) al arreglo de muestra*/
void option_switcher (char *opcion);

/*Funcion que se encarga de ir escribiendo la oracion, agregando espacios entre palabras*/
char *escribiroracion (char *oracion);

/*Funcion que borra palabras*/
void borrarpalabra (void);

int analizartecladolinterna(ALLEGRO_EVENT_QUEUE* eventos, int* pestado);
void mantenerlinterna(int* pestado,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla, INFOPANTALLA mipantalla);

/*
 * Definicion de constantes que serviran para diferenes motivos
 */
#define ERROR           NULL
#define FPS             20
#define PANTALLA_ANCHO  330
#define PANTALLA_ALTO   765
#define MOVISTAR    0
#define PERSONAL    1
#define CLARO       2
#define NEXTEL      3

#define PEQUENA     12
#define MEDIA       22          //tipos de letras
#define GRANDE      36
#define GIGANTE     72

#define PANTALLAPRINCIPAL   0
#define MENU                1
#define MENSAJE             2
#define PERSONALIZAR        3
#define LINTERNA              4
#define FIESTA 5
#define FINALIZAR           -1

#define PVOLVER         0
#define PMENSAJE        1
#define PPERSONALIZAR   2       //estas variables tienen que ver con a donde se apuntara, cual sera el proximo estado
#define PSTAY           3
#define PJUEGO          4

#define POS1            50
#define POS2            100
#define POS3            150     //constantes para menu
#define POS4            200


#define NOCAMBIO    0
#define ROJO        1
#define AMARILLO    2
#define VERDE       3             //colores
#define MORADO      4
#define CELESTE     5
#define NARANJA     6
#define ROSA        7


#define T9              0
#define MODOLIBRE       1       //tipo de teclado usado
#define TECLADOANALOGO  2

#define USUARIO             0
#define COMPANIA            1
#define MENSAJEPERSONAL     2
#define TIPOESCRITURA       3
#define FONDO               4
#define INUSUARIO           5
#define INCOMPANIA          6
#define MPCOLOR             7
#define MPTEXTO             8           //estos defines son para manejar el estadoconfiguracion
#define MPTAMANO            9
#define TT9                 10
#define CLASICO             11
#define TECLADONORMAL       12
#define FBLANCO             13   
#define FROJO               14
#define FAMARILLO           15
#define FVERDE              16
#define FMORADO             17
#define FCELESTE            18
#define FNARANJA            19
#define FROSA               20
#define CMOVISTAR           21
#define CPERSONAL           22
#define CCLARO              23
#define CNEXTEL             24
#define MPBLANCO            25   
#define MPROJO              26
#define MPAMARILLO          27
#define MPVERDE             28
#define MPMORADO            29
#define MPCELESTE           30
#define MPNARANJA           31
#define MPROSA              32
#define MPPEQUENA           33
#define MMEDIA              34
#define MGRANDE             35
#define MGIGANTE            36
#define INGRESARTEXTO       37

#define CONF1   20
#define CONF2   55
#define CONF3   90          //tambien para mantener configuracion
#define CONF4   125
#define CONF5   160



#endif	/* FINAL_H */

