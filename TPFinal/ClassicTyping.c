#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>              //son todas las librerias que se utilizaran
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "Final.h"


#define LINEA 17




char palabraingresada [LINEA*5+5];



static char linea1 [18];
static char linea2 [18];
static char linea3 [18];
static char linea4 [18];
static char linea5 [18];

char *palabratecleada = palabraingresada;
char contador1=0;

char *cursor = palabraingresada;


int tecladoCLASSIC1 (ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_BITMAP* pantalla, ALLEGRO_DISPLAY* display, INFOPANTALLA* mipantalla, int* pestado, int* estadoconfiguracion){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { 
            exit (0);

        } else if(ev.type==ALLEGRO_EVENT_TIMER){
            ALLEGRO_BITMAP* mapa=NULL; mapa=al_create_bitmap(200,40); al_set_target_bitmap(mapa); al_clear_to_color(al_map_rgb(255,255,255));
        cambiopantalla(display,pantalla);
        al_draw_bitmap(mapa,0,100,0);
        cambiopantalla(display,pantalla);
        al_destroy_bitmap(mapa);
        ponerarrayenpantalla(linea1,0,100,display,pantalla);
        
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(ev.mouse.button & 1){
                //aca iran los ifs que veran el ev.mouse.x y el ev.mouse.y
                if(ev.mouse.x>30&&ev.mouse.x<110){      //pueden ser el select, llamar,1,4,7,*
                    if(ev.mouse.y>450&&ev.mouse.y<490){//se presiono la teclaselect
                            *linea1=*linea1-0x20;
                            strcpy(mipantalla->usuario,linea1); 
                            *estadoconfiguracion=FONDO;
                            break;
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                              //tecla verde, llamar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                palabratecleada = user_types_classically (palabratecleada, '1');
                                   //tecla 1
                        
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        palabratecleada = user_types_classically (palabratecleada, '4');
                                   //tecla 4
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        palabratecleada = user_types_classically (palabratecleada, '7');
                                   //tecla7
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x>50){
                            *(--palabratecleada)=0;      //tecla asterisco
                    }    
                } else if(ev.mouse.x>110&&ev.mouse.x<208){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if(ev.mouse.y>450&&ev.mouse.y<460){
                              //tecla para arrriba
                    } else if (ev.mouse.y>525&&ev.mouse.y<540){
                            //teclaparaabajo
                    } else if(ev.mouse.y>460&&ev.mouse.y<540){  //der, izq o medio
                                if(ev.mouse.x<130){
                                        
                                         contador1 = character_switcher_left (palabratecleada, contador1);    //hacia la izquierda
                                         
                                         
                                } else if(ev.mouse.x>188){

                                         contador1 = character_switcher_right (palabratecleada, contador1);    //la de la derecha
                                         
                                         
                                }else {*linea1=*linea1-0x20;
                                    strcpy(mipantalla->usuario,linea1); 
                            *estadoconfiguracion=FONDO;
                            break;}     //la del medio
                    } else if(ev.mouse.y>540&&ev.mouse.y<585){                       
                        palabratecleada = user_types_classically (palabratecleada, '2');                      
                                   //tecla 2
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        palabratecleada = user_types_classically (palabratecleada, '5');
                                   //tecla 5
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        palabratecleada = user_types_classically (palabratecleada, '8');
                                   //tecla8
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720){
                        
                        *(palabratecleada) = ' ';
                        palabratecleada++;
                        
                                              
                                 //tecla 0
                    } 
                    
                } else if(ev.mouse.x>208&&ev.mouse.x<288){      //pueden ser back,colgar,3,6,9 o numeral
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                            *estadoconfiguracion=USUARIO;  //se presiono la tecla back
                            break;
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                         *pestado=PANTALLAPRINCIPAL;     //tecla roja,colgar
                         break;
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                        palabratecleada = user_types_classically (palabratecleada, '3');
                                   //tecla 3
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        palabratecleada = user_types_classically (palabratecleada, '6');
                                   //tecla 6
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        palabratecleada = user_types_classically (palabratecleada, '9');
                                   //tecla9
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x<268){
                               //tecla numeral
                }
                
                }  
            }
        }
        
        copy_2_lines (palabraingresada);
        

    }
    clearclassicarray(palabraingresada);
    palabratecleada=palabraingresada;
}


int tecladoCLASSIC2 (ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_BITMAP* pantalla, ALLEGRO_DISPLAY* display, INFOPANTALLA* mipantalla, int* pestado, int* estadoconfiguracion){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { 
            exit (0);

        } else if(ev.type==ALLEGRO_EVENT_TIMER){
            ALLEGRO_BITMAP* mapa=NULL; mapa=al_create_bitmap(200,100); al_set_target_bitmap(mapa); al_clear_to_color(al_map_rgb(255,255,255));
        cambiopantalla(display,pantalla);
        al_draw_bitmap(mapa,0,100,0);
        cambiopantalla(display,pantalla);
        al_destroy_bitmap(mapa);
        ponerarrayenpantalla(linea1,0,100,display,pantalla);
        ponerarrayenpantalla(linea2,0,125,display,pantalla);
        ponerarrayenpantalla(linea3,0,150,display,pantalla);
        ponerarrayenpantalla(linea4,0,175,display,pantalla);
        
        }else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(ev.mouse.button & 1){
                //aca iran los ifs que veran el ev.mouse.x y el ev.mouse.y
                if(ev.mouse.x>30&&ev.mouse.x<110){      //pueden ser el select, llamar,1,4,7,*
                    if(ev.mouse.y>450&&ev.mouse.y<490){//se presiono la teclaselect
                            *palabraingresada=*palabraingresada-0x20;
                            strcpy(mipantalla->mensajepersonal,palabraingresada); 
                            *estadoconfiguracion=FONDO;
                            break;
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                              //tecla verde, llamar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                palabratecleada = user_types_classically (palabratecleada, '1');
                                   //tecla 1
                        
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        palabratecleada = user_types_classically (palabratecleada, '4');
                                   //tecla 4
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        palabratecleada = user_types_classically (palabratecleada, '7');
                                   //tecla7
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x>50){
                            *(--palabratecleada)=0;      //tecla asterisco
                    }    
                } else if(ev.mouse.x>110&&ev.mouse.x<208){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if(ev.mouse.y>450&&ev.mouse.y<460){
                              //tecla para arrriba
                    } else if (ev.mouse.y>525&&ev.mouse.y<540){
                            //teclaparaabajo
                    } else if(ev.mouse.y>460&&ev.mouse.y<540){  //der, izq o medio
                                if(ev.mouse.x<130){
                                        
                                         contador1 = character_switcher_left (palabratecleada, contador1);    //hacia la izquierda
                                         
                                         
                                } else if(ev.mouse.x>188){

                                         contador1 = character_switcher_right (palabratecleada, contador1);    //la de la derecha
                                         
                                         
                                }else {*palabraingresada=*palabraingresada-0x20;
                                    strcpy(mipantalla->mensajepersonal,palabraingresada); 
                            *estadoconfiguracion=FONDO;
                            break;}     //la del medio
                    } else if(ev.mouse.y>540&&ev.mouse.y<585){                       
                        palabratecleada = user_types_classically (palabratecleada, '2');                      
                                   //tecla 2
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        palabratecleada = user_types_classically (palabratecleada, '5');
                                   //tecla 5
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        palabratecleada = user_types_classically (palabratecleada, '8');
                                   //tecla8
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720){
                        
                        *(palabratecleada) = ' ';
                        palabratecleada++;
                        
                                              
                                 //tecla 0
                    } 
                    
                } else if(ev.mouse.x>208&&ev.mouse.x<288){      //pueden ser back,colgar,3,6,9 o numeral
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                            *estadoconfiguracion=USUARIO;  //se presiono la tecla back
                            break;
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                         *pestado=PANTALLAPRINCIPAL;     //tecla roja,colgar
                         break;
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                        palabratecleada = user_types_classically (palabratecleada, '3');
                                   //tecla 3
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        palabratecleada = user_types_classically (palabratecleada, '6');
                                   //tecla 6
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        palabratecleada = user_types_classically (palabratecleada, '9');
                                   //tecla9
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x<268){
                               //tecla numeral
                }
                
                }  
            }
        }
        
        copy_2_lines (palabraingresada);
        

    }
    clearclassicarray(palabraingresada);
}


/*Funcion que hacia variar los caracteres dentro de una tecla, hacia la izquierda*/
/*Recibe un puntero a la letra del arreglo que se quiere modificar, y un contador para limitar las opciones de la tecla*/
/*Devuelve el nuevo caracter al arreglo especificado*/
int character_switcher_right (char *letra, char contador)
{
            if((*(letra-1))== 's')
               (*(letra-1))='7'; 

           if((*(letra-1))=='z')
               (*(letra-1))='9';  
    
    if (contador<3) {
        
       if (contador==2)
       {
            if((*(letra-1))=='c')
                (*(letra-1))='2';
            
            if((*(letra-1))=='f')
                (*(letra-1))='3';
        
            if((*(letra-1))=='i')
                (*(letra-1))='4';

            if((*(letra-1))=='l')
                (*(letra-1))='5';

            if((*(letra-1))=='o')
                (*(letra-1))='6';

            if((*(letra-1))=='r')
                (*(letra-1))='s';
              
            if((*(letra-1))=='v')
                (*(letra-1))='8';

            if((*(letra-1))=='y')
                (*(letra-1))='z';
                

        }
        else {
        (*(letra-1))++;
        }
     contador++;
    }
    
    
    return contador;
}


/*Funcion que hacia variar los caracteres dentro de una tecla, hacia la izquierda*/
/*Recibe un puntero a la letra del arreglo que se quiere modificar, y un contador para limitar las opciones de la tecla*/
/*Devuelve el nuevo caracter al arreglo especificado*/
int character_switcher_left (char *letra, char contador)
{
            
if((*(letra-1))== '7'){
   (*(letra-1))='s'; 
    return contador;
 } 

if((*(letra-1))=='9') {
   (*(letra-1))='z'; 
    return contador;
    }

      if ((contador>0)&&(contador<4)) {
            contador--;
            if (contador==2)
                {
                    if((*(letra-1))=='2')
                        (*(letra-1))='c';
            
                    if((*(letra-1))=='3')
                        (*(letra-1))='f';
        
                    if((*(letra-1))=='4')
                        (*(letra-1))='i';

                    if((*(letra-1))=='5')
                        (*(letra-1))='l';

                    if((*(letra-1))=='6')
                        (*(letra-1))='o';

                    if((*(letra-1))=='s')
                        (*(letra-1))='r';

                    if((*(letra-1))=='8')
                        (*(letra-1))='v';

                    if((*(letra-1))=='z')
                        (*(letra-1))='y';
                
                }
        

        
        else {
        (*(letra-1))--;
        }
     
     }



    return contador;

}

/*Funcion en la que se escribe el primer caracter de cada tecla*/
/*Recibe eun puntero al arreglo donde se escribe la palabra y la tecla presionada*/
/*Devuelve el mismo puntero que recibio, pero incrementado en 1*/
char *user_types_classically (char *palabra, char tecla)
{

            if (tecla == '1') {
               *(palabra++)= '1';
               contador1=0;
            }

            if (tecla == '2') {
               *(palabra++)= 'a';
               contador1=0;
            }

            if (tecla == '3') {
                *(palabra++)= 'd'; 
                contador1=0;
            }

            if (tecla == '4') {
                *(palabra++)= 'g'; 
                contador1=0;
            }

            if (tecla == '5') {
                *(palabra++)= 'j';
                contador1=0;
            }
            
            if (tecla == '6') {
                *(palabra++)= 'm'; 
                contador1=0;
            }
            
            if (tecla == '7') {
                *(palabra++)= 'p';
                contador1=0;
            }
            
            if (tecla == '8') {
               *(palabra++)= 't';
               contador1=0;
            }
               
            if (tecla == '9') {
               *(palabra++)= 'w';
               contador1=0;
            }
    
            return palabra;

}

/*Funcion que limpia un array y lo deja todo en 0*/ 
/*Recibe: puntero al inicio del array*/
void clearclassicarray (char *array)
{
    unsigned int i=0;
    
    for (i=0 ; *(array+i) != 0 ; i++)
        *(array+i) = 0;

}



char *buscador_de_espacios (char *palabra)
{

    char *cursor = NULL;
    unsigned char i=0;

    while (i<17)
        {

            if (*(palabra++) == ' ')
                 cursor = palabra;

            i++;

        }

    return cursor;

}

void copy_2_lines (char texto[])
{

    unsigned int i=0;

    while(i<17) {
        linea1[i] = texto[i];
        i++;
    }
    i=0;
    linea1[18] = 0;



    while(i<17) {
        linea2[i] = texto[i+17];
        i++;
    }
    i=0;
    linea2[18] = 0;



    while(i<17) {
        linea3[i] = texto[i+2*17];
        i++;
    }
    i=0;
    linea3[18] = 0;



    while(i<17) {
        linea4[i] = texto[i+3*17];
        i++;
    }
    i=0;
    linea4[18] = 0;



    while(i<17) {
        linea5[i] = texto[i+4*17];
        i++;
    }
    i=0;
    linea5[18] = 0;

   
}
