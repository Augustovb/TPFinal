
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>              //son todas las librerias que se utilizaran
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "Final.h"

void copy_T9_lines (char texto[]);
char *escribiroracion (char *oracion);

/*Arreglos globales de almacenamiento*/

char tecleadousuario [100]; /*Aquí se esciben las teclas del usuario, expandidas*/
char escritura[20];     /*Arreglo donde escriben todas las posibilidades a partir de tecleadousuario */

char elecciones [140];      /*En este arreglo se esciben, consecutivamente, todas las posibles coincidencias*/
char muestra [100];         /*En este arreglo se escribe momentanemente la palabra que va seleccionando el usuario PARA ALLEGRO*/


unsigned int counter = 0;
char contadordecoincidencias = 0;          /*Contadores para switchers*/


char oracioningresada [200];               /*Aqui se escribe la oracion que se va tecleando*/

char ultimapalabra [50]; 
char ultimapalabra1 [50] = "cúyo";
char ultimapalabra2 [50] = "fútil";
char ultimapalabra3 [50] = "ítem";
char ultimapalabra4 [50] = "lúteo";         /*Ultimas palabras de los diccionarios*/
char ultimapalabra5 [50] = "óxido";
char ultimapalabra6 [50] = "súrtuba";
char ultimapalabra7 [50] = "vórtice";
char ultimapalabra8 [50] = "zúa";


char linea1T9 [18];
char linea2T9 [18];
char linea3T9 [18];
char linea4T9 [18];                     /*En estos arreglos se parte "oracioningresada" para ALLEGRO*/
char linea5T9 [18];
 
/*Punteros globales de file, a los diccionarios*/    

    FILE *diccionario;
    FILE *diccabc;
    FILE *diccdef;
    FILE *diccghi;
    FILE *diccjkl;
    FILE *diccmno;
    FILE *diccpqrs;
    FILE *dicctuv;
    FILE *diccwxyz;

    char *tecleadocopia = tecleadousuario;      /*Punteros cursores*/
    char *oracion = oracioningresada;

/*FUNCIONES DEL T9*/

int tecladoT9 (ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_BITMAP* pantalla,ALLEGRO_DISPLAY* display){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }else if(ev.type==ALLEGRO_EVENT_TIMER){
            ALLEGRO_BITMAP* mapa=NULL; mapa=al_create_bitmap(200,215); al_set_target_bitmap(mapa); al_clear_to_color(al_map_rgb(255,255,255));
        cambiopantalla(display,pantalla);
        al_draw_bitmap(mapa,0,50,0);
        ALLEGRO_FONT* fuente=NULL; 
        fuente=crearfuente(MEDIA); 
        if(fuente==NULL)
        { printf("Error");
        exit ;}
        al_draw_text(fuente,al_map_rgb(0,0,0),0,50,ALLEGRO_ALIGN_LEFT,linea1T9);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,90,ALLEGRO_ALIGN_LEFT,linea2T9);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,130,ALLEGRO_ALIGN_LEFT,linea3T9);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,170,ALLEGRO_ALIGN_LEFT,linea4T9);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,210,ALLEGRO_ALIGN_LEFT,linea5T9);
        
        al_draw_text(fuente,al_map_rgb(0,0,0),100,240,ALLEGRO_ALIGN_CENTRE,muestra);
        al_destroy_font(fuente);
        cambiopantalla(display,pantalla);
        al_destroy_bitmap(mapa);
        
        
        
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(ev.mouse.button & 1){
                //aca iran los ifs que veran el ev.mouse.x y el ev.mouse.y
                if(ev.mouse.x>30&&ev.mouse.x<110){      //pueden ser el select, llamar,1,4,7,*
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                              //se presiono la teclaselect
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                              //tecla verde, llamar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                   //tecla 1
                        
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        usertypes ('4');
                                   //tecla 4
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        usertypes ('7');
                                   //tecla7
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x>50){
                                 borrarpalabra (); puts (oracioningresada); //tecla asterisco
                    }    
                } else if(ev.mouse.x>110&&ev.mouse.x<208){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if(ev.mouse.y>450&&ev.mouse.y<460){
                              //tecla para arrriba
                    } else if (ev.mouse.y>525&&ev.mouse.y<540){
                            //teclaparaabajo
                    } else if(ev.mouse.y>460&&ev.mouse.y<540){  //der, izq o medio
                                if(ev.mouse.x<130){
                                         //hacia la izquierda
                                } else if(ev.mouse.x>188){
                                         option_switcher (elecciones); puts (muestra);   //la de la derecha
                                }  else {  oracion = escribiroracion (oracion); copy_T9_lines (oracioningresada); puts (oracioningresada);  }   //la del medio
                    } else if(ev.mouse.y>540&&ev.mouse.y<585){
                        usertypes ('2');
                                   //tecla 2
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        usertypes ('5');
                                   //tecla 5
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        usertypes ('8');
                                   //tecla8
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720){
                             Te9();                     
                        tecleadocopia = tecleadousuario;
                            counter=0;
                            cleararray (muestra);
                                 
                                //tecla 0
                    } 
                    
                } else if(ev.mouse.x>208&&ev.mouse.x<288){      //pueden ser back,colgar,3,6,9 o numeral
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                              //se presiono la tecla back
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                              //tecla roja,colgar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                        usertypes ('3');
                                   //tecla 3
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        usertypes ('6');
                                   //tecla 6
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        usertypes ('9');
                                   //tecla9
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x<268){
                                //tecla asterisco
                }
                
                }  
            }
        }
        
    }
    

   return 0;
}
int tecladoT92 (ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_BITMAP* pantalla,ALLEGRO_DISPLAY* display,INFOPANTALLA* mipantalla,int* pestadoconfiguracion){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }else if(ev.type==ALLEGRO_EVENT_TIMER){
            ALLEGRO_BITMAP* mapa=NULL; mapa=al_create_bitmap(200,215); al_set_target_bitmap(mapa); al_clear_to_color(al_map_rgb(255,255,255));
        cambiopantalla(display,pantalla);
        al_draw_bitmap(mapa,0,50,0);
        ALLEGRO_FONT* fuente=NULL; 
        fuente=crearfuente(MEDIA); 
        if(fuente==NULL){ printf("Error"); 
        exit ;}
        al_draw_text(fuente,al_map_rgb(0,0,0),0,50,ALLEGRO_ALIGN_LEFT,linea1T9);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,90,ALLEGRO_ALIGN_LEFT,linea2T9);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,130,ALLEGRO_ALIGN_LEFT,linea3T9);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,170,ALLEGRO_ALIGN_LEFT,linea4T9);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,210,ALLEGRO_ALIGN_LEFT,linea5T9);
        
        al_draw_text(fuente,al_map_rgb(0,0,0),100,240,ALLEGRO_ALIGN_CENTRE,muestra);
        al_destroy_font(fuente);
        cambiopantalla(display,pantalla);
        al_destroy_bitmap(mapa);
        
        
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(ev.mouse.button & 1){
                //aca iran los ifs que veran el ev.mouse.x y el ev.mouse.y
                if(ev.mouse.x>30&&ev.mouse.x<110){      //pueden ser el select, llamar,1,4,7,*
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                            strcpy(mipantalla->mensajepersonal,oracioningresada);  //se presiono la teclaselect
                            *pestadoconfiguracion=USUARIO;
                            break;
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                              //tecla verde, llamar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                   //tecla 1
                        
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        usertypes ('4');
                                   //tecla 4
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        usertypes ('7');
                                   //tecla7
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x>50){
                                 borrarpalabra (); puts (oracioningresada); //tecla asterisco
                    }    
                } else if(ev.mouse.x>110&&ev.mouse.x<208){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if(ev.mouse.y>450&&ev.mouse.y<460){
                              //tecla para arrriba
                    } else if (ev.mouse.y>525&&ev.mouse.y<540){
                            //teclaparaabajo
                    } else if(ev.mouse.y>460&&ev.mouse.y<540){  //der, izq o medio
                                if(ev.mouse.x<130){
                                         //hacia la izquierda
                                } else if(ev.mouse.x>188){
                                         option_switcher (elecciones); puts (muestra);   //la de la derecha
                                }  else {  oracion = escribiroracion (oracion); copy_T9_lines (oracioningresada); puts (oracioningresada); }   //la del medio
                    } else if(ev.mouse.y>540&&ev.mouse.y<585){
                        usertypes ('2');
                                   //tecla 2
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        usertypes ('5');
                                   //tecla 5
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        usertypes ('8');
                                   //tecla8
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720){
                             Te9();                     
                        tecleadocopia = tecleadousuario;
                            counter=0;
                            cleararray (muestra);
                                 
                                //tecla 0
                    } 
                    
                } else if(ev.mouse.x>208&&ev.mouse.x<288){      //pueden ser back,colgar,3,6,9 o numeral
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                              //se presiono la tecla back
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                              //tecla roja,colgar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                        usertypes ('3');
                                   //tecla 3
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        usertypes ('6');
                                   //tecla 6
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        usertypes ('9');
                                   //tecla9
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x<268){
                                //tecla asterisco
                }
                
                }  
            }
        }
        
    }
    

   return 0;
}



/*Funcion principal de este archivo*/
/*Funcion que funciona como un T9. En base a permutaciones de letras "adivina" las palabras del usuario*/
void Te9(void) {
    
    contadordecoincidencias = 0;

    init_dictionary ();

    cleararray (elecciones);
    cleararray (escritura);

    puts (tecleadousuario);            /*Leo los numeros que ingreso el usuario y los muestro (PARA TESTEAR)*/

    
    analisis_recursividad (tecleadousuario, escritura, 0, strlen (tecleadousuario)/4 , diccionario);   /*Funcion recursiva que analiza todas las variantes*/

    cleararray (tecleadousuario); 

    puts (elecciones);
    
}



/*Funcion que inicializa el diccionario correspondiente, segun el idioma elegio*/

void init_dictionary (void)
{

    
    if ((diccabc = fopen ("diccespanolabc.txt", "r")) == NULL) {
        fprintf (stderr, "Error al abrir el diccionario\n");    
        exit (1);
        }
        
    if ((diccdef = fopen ("diccespanoldef.txt", "r")) == NULL) {
        fprintf (stderr, "Error al abrir el diccionario\n");    
        exit (1);
        }
        
    if ((diccghi = fopen ("diccespanolghi.txt", "r")) == NULL) {
        fprintf (stderr, "Error al abrir el diccionario\n");    
        exit (1);
        }

    if ((diccjkl = fopen ("diccespanoljkl.txt", "r")) == NULL) {
        fprintf (stderr, "Error al abrir el diccionario\n");    
        exit (1);
        }

    if ((diccmno = fopen ("diccespanolmno.txt", "r")) == NULL) {
        fprintf (stderr, "Error al abrir el diccionario\n");    
        exit (1);
        }

    if ((diccpqrs = fopen ("diccespanolpqrs.txt", "r")) == NULL) {
        fprintf (stderr, "Error al abrir el diccionario\n");    
        exit (1);
        }

    if ((dicctuv = fopen ("diccespanoltuv.txt", "r")) == NULL) {
        fprintf (stderr, "Error al abrir el diccionario\n");    
        exit (1);
        }

    if ((diccwxyz = fopen ("diccespanolwxyz.txt", "r")) == NULL) {
        fprintf (stderr, "Error al abrir el diccionario\n");    
        exit (1);
        }

}


/*Funcion que busca en el diccionario si la palabra existe o no*/
/*Recibe un puntero de tipo FILE al diccionario y la palabra que se quiere buscar*/
/*Por ahora solo muestra en pantalla que existe*/

void checkfromdic (FILE *diccionario, char *palabra)
{
        char *buffertemporal = NULL;
        unsigned char caracter=0;
        unsigned char k=1;
        
        while (k)      /*Loop hasta llegar al final del archivo*/ 
            {
                unsigned int i=0;
                
                 if ((buffertemporal = (char *)calloc (50, sizeof(char))) == NULL){
                        printf ("Not enough memory to allocate the string\n");      /*Reservo dinamicamente el espacio para alojar momentaneamente la palabra del diccionario*/
                         exit (-1);
                      }


                while (((caracter = fgetc (diccionario)) != ' ') && (caracter != '\n'))
                    {
                        *(buffertemporal+i) = caracter;                             /*Junto letras hasta llegar a un espacio o a un enter. Busca las palabras. INEFICIENTE*/
                        i++;

                    }
                
                if (strcmp (ultimapalabra, buffertemporal)== 0)
                    k=0;

                if (strcmp (buffertemporal, palabra)==0) {
                    printf ("Se encontro coincidencia: %s\n", palabra);     /*Si encontro coicidencia con la palabra lo muestra en pantalla*/
                    
                    strcpy (&elecciones[contadordecoincidencias*strlen(palabra)], palabra);

                    contadordecoincidencias++;
                    
                }

                free (buffertemporal);
            }
            
           rewind (diccionario);    /*Devuelve el puntero al inicio del archivo para que se pueda volver a leer*/

}


/*Funcion recursiva que analiza todas las permutaciones de letras posibles*/
/*Recibe: puntero a donde esta la palabra, puntero a donde va a escribir la permutacion, puntero a diccionario*/
/*Recibe un offset (debe ser 0, arreglar esto despues*/
/*Recibe la cantidad de caracteres de la palabra a permutar (largo)*/
/*Si hay coincidencia, lo muestra en pantalla*/

void analisis_recursividad (char *destino, char *escritura, char offset, char largo, FILE *diccionario)
{
    int i=0;
    int c=0;
   
if (offset == largo) {
    if (permutacionvalida(escritura)) {          /*Checkeo si la permutacion tiene numeros o no para hacer mas eficiente el algoritmo*/
        diccionario = diccswitcher(escritura);
        checkfromdic (diccionario, escritura); 
        }
    }
else
    {
    for (i=0 ; i<4 ; i++)
        {
        *(escritura+offset) = *(destino+(4*offset) + i);   /*Aloja las permutaciones en el arreglo escritura*/
        analisis_recursividad (destino, escritura, offset+1, largo, diccionario);  /*Parte recursiva que anida fors para crear todas las permutaciones de letras*/
        }
    }

}


/*Funcion que recibe los numeros que teclea el usuario (que son en realidad letras de palabras)*/
/*Recibe un puntero a un arreglo donde dejara lo que el usuario tecleo*/
/*Devuelve LA EXPANSION de lo que el usuario tecleo.
Ejemplo: si se presiona un 2, el mismo se expande como abc2, para que queden todas las combinaciones posibles*/

void usertypes (char tecla)
{
    
            if (tecla == '2') {
                *tecleadocopia = 'a';
                *(++tecleadocopia) = 'b';
                *(++tecleadocopia) = 'c';
                *(++tecleadocopia) = '2';
                tecleadocopia++;
            }

            if (tecla == '3') {
                *tecleadocopia = 'd';
                *(++tecleadocopia) = 'e';
                *(++tecleadocopia) = 'f';
                *(++tecleadocopia) = '3';
                tecleadocopia++;
            }

            if (tecla == '4') {
                *tecleadocopia = 'g';
                *(++tecleadocopia) = 'h';
                *(++tecleadocopia) = 'i';
                *(++tecleadocopia) = '4';
                tecleadocopia++;
            }

            if (tecla == '5') {
                *tecleadocopia = 'j';
                *(++tecleadocopia) = 'k';        
                *(++tecleadocopia) = 'l';
                *(++tecleadocopia) = '5';
                tecleadocopia++;
            }
            
            if (tecla == '6') {
                *tecleadocopia = 'm';
                *(++tecleadocopia) = 'n';        
                *(++tecleadocopia) = 'o';
                *(++tecleadocopia) = '6';
                tecleadocopia++;
            }
            
            if (tecla == '7') {
                *tecleadocopia = 'p';
                *(++tecleadocopia) = 'q';       
                *(++tecleadocopia) = 'r';
                *(++tecleadocopia) = 's';
                tecleadocopia++;
            }
            
            if (tecla == '8') {
                *tecleadocopia = 't';
                *(++tecleadocopia) = 'u';      
                *(++tecleadocopia) = 'v';
                *(++tecleadocopia) = '8';
                tecleadocopia++;
            }
               
            if (tecla == '9') {
                *tecleadocopia = 'w';
                *(++tecleadocopia) = 'x';        
                *(++tecleadocopia) = 'y';
                *(++tecleadocopia) = 'z';
                tecleadocopia++;
            }
 }
       

/*Funcion que analiza si la permutación devuelta por la funcion permutacion es valida o no (tiene numeros o no)*/
/*Recibe un puntero al arreglo donde se aloja la permutacion*/
/*Devuelve TRUE si la permutacion es valida o FALSE si es invalida*/

int permutacionvalida (char *permutacion)
{
    unsigned int i=0;

    while (*(permutacion+i)) {
    
        if ((*(permutacion+i) >= '0') && (*(permutacion+i) <= '9'))
            return FALSE;
        i++;

    }

    return TRUE;
}


/*Funcion que establece a que seccion del diccionario recurrir para buscar la palabra (su finalidad es optimizar el algoritmo)*/
/*Recibe un puntero al array donde está la palabra que se quiere buscar*/
/*Devuelve el puntero a file del diccionario correspondiente*/

FILE *diccswitcher (char *palabra)
{

    if ((*palabra == 'a') || (*palabra == 'b') || (*palabra == 'c')) {
                    strcpy (ultimapalabra, ultimapalabra1);                 /*Segun entre a cada if, devuelve el puntero al diccionario correspondiente*/
                    return diccabc;
        }

    if ((*palabra == 'd') || (*palabra == 'e') || (*palabra == 'f')) {
                    strcpy (ultimapalabra, ultimapalabra2);
                    return diccdef;
        }

    if ((*palabra == 'g') || (*palabra == 'h') || (*palabra == 'i')) {
                    strcpy (ultimapalabra, ultimapalabra3);
                    return diccghi;
        }

    if ((*palabra == 'j') || (*palabra == 'k') || (*palabra == 'l')) {
                    strcpy (ultimapalabra, ultimapalabra4);
                    return diccjkl;
        }

    if ((*palabra == 'm') || (*palabra == 'n') || (*palabra == 'o')) {
                    strcpy (ultimapalabra, ultimapalabra5);
                    return diccmno;
        }

    if ((*palabra == 'p') || (*palabra == 'q') || (*palabra == 'r') || (*palabra == 's')) {
                    strcpy (ultimapalabra, ultimapalabra6);
                    return diccpqrs;
        }

    if ((*palabra == 't') || (*palabra == 'u') || (*palabra == 'v')) {
                    strcpy (ultimapalabra, ultimapalabra7);
                    return dicctuv;
        }

    if ((*palabra == 'w') || (*palabra == 'x') || (*palabra == 'y') || (*palabra == 'z')) {
                    strcpy (ultimapalabra, ultimapalabra8);
                    return diccwxyz;
        }

}


/*Funcion que limpia un array y lo deja todo en 0*/ 
/*Recibe: puntero al inicio del array*/
void cleararray (char *array)
{
    unsigned int i=0;
    
    for (i=0 ; *(array+i) != 0 ; i++)
        *(array+i) = 0;

}

void option_switcher (char *opcion)
{
    if (counter == contadordecoincidencias)     /*Este IF se encarga de que el contador no desborde, y hace que de la ultima opcion, se pase a la primera (en el selector)*/
        counter = 0;

    unsigned int i=0;
    
    while (i<strlen(escritura)) {
        muestra[i] = *(opcion+counter*strlen(escritura)+i);   /*Escribe la opcion en la que se encuentra el usuario, en vivo*/
        i++;
    }

    counter++;
   

}

/*Funcion que parte un arreglo en arreglos mas pequeños, que representan las lineas graficas en el celular*/
void copy_T9_lines (char texto[])
{

    unsigned int i=0;

    while(i<17) {
        linea1T9[i] = texto[i];
        i++;                        /*LINEA 1*/
    }
    i=0;
    linea1T9[18] = 0;



    while(i<17) {
        linea2T9[i] = texto[i+17];
        i++;                        /*LINEA 2*/
    }
    i=0;
    linea2T9[18] = 0;



    while(i<17) {
        linea3T9[i] = texto[i+2*17];    /*LINEA 3*/
        i++;
    }
    i=0;
    linea3T9[18] = 0;



    while(i<17) {
        linea4T9[i] = texto[i+3*17];
        i++;
    }                                   /*LINEA 4*/
    i=0;
    linea4T9[18] = 0;



    while(i<17) {
        linea5T9[i] = texto[i+4*17];
        i++;                            /*LINEA 5*/
    }
    i=0;
    linea5T9[18] = 0;

   
}


/*Escribe la palabra alojada en muestra en la oracion*/
char *escribiroracion (char *oracion)
{
    unsigned int i=0;

    while(muestra[i]) {
        *(oracion+i) = muestra[i];      /*Copia lo que se encuentra en muestra, al arreglo de oracion*/
        i++;
    }
    
     *(oracion+i) = ' ';    /*Inserta un espacio automaticamente*/

     return (oracion+i+1);  /*Devuelvo a la siguiente posicion libre*/
    
}

void borrarpalabra (void)
{

    while ((oracion!=oracioningresada) && ((*(oracion) == ' ') || (*(oracion) == 0)))
            oracion--;

    while ((oracion != oracioningresada) && (*(--oracion) != ' ')) {
            *(oracion) = 0;
        }

   if (oracion == oracioningresada)
    *oracion = 0;

   else
     oracion++;
    

}