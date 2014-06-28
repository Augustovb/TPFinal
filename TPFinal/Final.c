/* 
 * File:   Final.c
 * Author: augustovb
 *
 * Created on June 25, 2014, 12:48 AM
 */

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



/*Estructura utilizada para chequear la data personalisable del usuario*/
typedef struct{ 
    char usuario[20];
    int compania;   
    ALLEGRO_COLOR colorfondo;         //si empieza en 0, es el default, de la compania
    char mensajepersonal[140];  //podra tener un mensaje personal de 140 caracteres
    ALLEGRO_COLOR colormensaje;
    int tamanomensaje;          // si es mayor al del que entraria en la pantalla, se toma como el predeterminado(12)
}INFOPANTALLA;

#define MOVISTAR    0
#define PERSONAL    1
#define CLARO       2
#define NEXTEL      3
#define PEQUENA     12
#define MEDIA       22
#define GRANDE      36
#define GIGANTE     72




void iniciarpantalla(INFOPANTALLA datos, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla);
/*Crea una fuente (del estilo predeterminado) del tamaño pedido*/
ALLEGRO_FONT* crearfuente (int tamano);


/*
 *Main
 */
int main(int argc, char** argv) {

    int condiciones=0;      //por lo que me devuelva la funcion setear comienzo
    
    if(inicializar()){
        return -1;
    }
    
    ALLEGRO_DISPLAY* display=NULL;
    ALLEGRO_EVENT_QUEUE* eventos=NULL;      //Son basicamente los punteros a estructuras propias de Allegro para la inicializacion de lo 
    ALLEGRO_TIMER*  timer=NULL;             //basico y necesario para hacer funcionar las funciones de esta libreria
    
    display=getdisplay(PANTALLA_ANCHO,PANTALLA_ALTO);
    eventos=geteventqueue();                              //llamo las funciones que crearan los displays y eventos
    timer=gettimer(1.0/FPS);
    if(display==ERROR||eventos==ERROR||timer==ERROR){
        return -1;                                      //si fallo alguna de las funciones llamadas, retorno del main, mostrando que hubo un error
    }
    
    al_register_event_source(eventos, al_get_display_event_source(display));

    al_register_event_source(eventos, al_get_timer_event_source(timer));     //registro los eventos
 
    al_register_event_source(eventos, al_get_mouse_event_source()); 
    
    al_register_event_source(eventos,al_get_keyboard_event_source());
    
    ALLEGRO_BITMAP* imagencelular=NULL;
    
    imagencelular=al_load_bitmap("foto_celular.png");
    if(imagencelular==NULL){fprintf(stderr,"No se pudo cargar la imagen\n");return -1;}     //chequeo que no haya habido errores
    
    al_draw_bitmap(imagencelular,-40,-20,0);
    al_flip_display();
    
    ALLEGRO_BITMAP* pantalla=NULL;      //a partir de ahora, solo trabajaremos graficamente en la pantalla
    pantalla=al_create_bitmap(220,288); //tiene el tamaño de la pantalla
    
    cambiopantalla(display,pantalla);
    al_clear_to_color(al_map_rgb(255,255,255));             //siempre que quiera modificar al bitmap pantalla para despues "pegarlo"
    cambiopantalla(display,pantalla);
    
    /*
     *  La secuencia que realizamos aqui... al_set_target_bitmap(pantalla);
     *                                      
     *                                      CAMBIOS ASOCIADOS A LA PANTALLA
     * 
     *                                      al_set_target_bitmap(al_get_backbuffer(display));
     *                                      al_draw_bitmap(pantalla,48,118,0);
     *                                      al_flip_display();
     * es la que esta comprimida en estas dos funciones
     * 
     */

    
    // getuserdata();  esta funcion lo que hara es de un archivo leer cual es la data que configuro el usuario. Lo que devuelve es una estructura del tipo infopantalla
    
    // iniciarpantalla(estructura, ALLEGRO_DISPLAY* , ALLEGRO_BITMAP*);     a esta funcion se le pasara la estructura del tipo pedido y lo que hara es segun esta estructura, modificar la pantalla
    //las ultimas dos opciones son para la funcion cambio pantalla
    
    al_start_timer(timer);   //inicializo el timer
    
    INFOPANTALLA mipantalla={"Augusto",PERSONAL,al_map_rgb(0,0,0),"",al_map_rgb(0,0,255),14};
    
    iniciarpantalla(mipantalla,display,pantalla);
    
    analizarteclado(eventos);
    
    return (EXIT_SUCCESS);
}


ALLEGRO_FONT* crearfuente (int tamano){
    ALLEGRO_FONT* fuente=NULL;
    
    fuente=al_load_ttf_font("PTS55F.ttf",tamano,0);      //cargo la fuente predeterminada con el tamano pedido
    
    
    if (fuente==NULL){
        fprintf(stderr,"No se pudo cargar la imagen, el programa finalizara.\n");
        sleep(2);
        exit -1;
    }
    
    return fuente;
    
}

void iniciarpantalla(INFOPANTALLA datos, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla){       //chequear que el mensaje personal no se pase de 140
    ALLEGRO_BITMAP* compania;
    ALLEGRO_FONT* fuente;
    ALLEGRO_BITMAP* partearriba=NULL;        //sera un bitmp color grisaceo para darle mas armonia al menu principal
    
    partearriba=al_create_bitmap(285,15);
    if(partearriba==NULL){fprintf(stderr,"Error al cargar el bitmap.\nEXITING PROGRAM \n"); exit-1;}
    
    al_set_target_bitmap(partearriba);
    al_clear_to_color(al_map_rgb(50,50,200));
    
    
    /*En datos. compania no debe haber otra cosa mas que un 0 1 2 o 3, si no, esto no tiene sentido*/
    if (datos.compania==PERSONAL){                  //si me dice que la persona es usuario de personal
        compania=al_load_bitmap("personal.png");
        fuente=crearfuente(PEQUENA);
        
        cambiopantalla(display,pantalla);                                               //prendo la pantalla con su nombre
        al_draw_bitmap(compania,-60,0,0);
        cambiopantalla(display,pantalla);
        
        sleep(2);                               //espero 2 segundos de manera que parezca que se esta prendiendo
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Personal");
        cambiopantalla(display,pantalla);
        
        
    } else if(datos.compania==MOVISTAR){            //mismo procedimiento con movistar, nextel o claro
        compania=al_load_bitmap("movistar.png");
        fuente=crearfuente(PEQUENA);
        
        cambiopantalla(display,pantalla);                                               //prendo la pantalla con su nombre
        al_draw_bitmap(compania,-60,0,0);
        cambiopantalla(display,pantalla);
        
        sleep(2);                               //espero 2 segundos de manera que parezca que se esta prendiendo
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Movistar");
        cambiopantalla(display,pantalla); 
        
        
    } else if(datos.compania==CLARO){            
        compania=al_load_bitmap("claro.png");
        fuente=crearfuente(PEQUENA);
        
        cambiopantalla(display,pantalla);                                               
        al_draw_bitmap(compania,-60,0,0);
        cambiopantalla(display,pantalla);
        
        sleep(2);                               
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Claro");
        cambiopantalla(display,pantalla); 
        
        
    } else if(datos.compania==NEXTEL){              //es solo para agregar variedad, ya que no tiene sentido un nokia con compania NEXTEL         
        compania=al_load_bitmap("nextel.png");
        fuente=crearfuente(PEQUENA);
        
        cambiopantalla(display,pantalla);                                               //prendo la pantalla con su nombre
        al_draw_bitmap(compania,-60,0,0);
        cambiopantalla(display,pantalla);
        
        sleep(2);                               //espero 2 segundos de manera que parezca que se esta prendiendo
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Nextel");
        cambiopantalla(display,pantalla); 
    }
    
    //me encargare del nombre del usuario
    
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),106,0,ALLEGRO_ALIGN_CENTRE,datos.usuario);    //106 es para que este en el medio del bitmap (long 213 de x) y datos.usuario es un char*
    al_draw_text(fuente,al_map_rgb(0,0,0),213,0,ALLEGRO_ALIGN_RIGHT,__TIME__);
    cambiopantalla(display,pantalla);
    
    cambiopantalla(display,pantalla);           //aqui se escribira el mensaje personal elegido por el usuario, e su color elegido y tamaño
    fuente=crearfuente(datos.tamanomensaje);
    al_draw_text(fuente,datos.colormensaje,0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);
    cambiopantalla(display,pantalla);
    
    
    fuente=crearfuente(MEDIA);
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Menu");         //creo boton menu o cualquier otro boton que quiera poner
    cambiopantalla(display,pantalla);
    
    
}

void cambiopantalla (ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla){
    static bool modificopantalla=false;
    if(!modificopantalla){
        al_set_target_bitmap(pantalla);
        
        modificopantalla=!modificopantalla;
    } else if(modificopantalla){
        al_set_target_bitmap(al_get_backbuffer(display));       
        al_draw_bitmap(pantalla,48,118,0);
        al_flip_display();  
        
        modificopantalla=!modificopantalla;
    }
    
}

int analizarteclado (ALLEGRO_EVENT_QUEUE* eventos){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    int teclaselect=0,teclallamar=0,tecla1=0,tecla2=0,tecla3=0,tecla4=0,tecla5=0,tecla6=0,tecla7=0,tecla8=0,tecla9=0,teclanum=0,tecla0=0,teclaast=0,teclaup=0,tecladown=0,teclaizq=0,teclader=0,teclamed=0,teclaback=0,teclacolg=0;
    
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(ev.mouse.button & 1){
                //aca iran los ifs que veran el ev.mouse.x y el ev.mouse.y
                if(ev.mouse.x>30&&ev.mouse.x<110){      //pueden ser el select, llamar,1,4,7,*
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                        ++teclaselect;      //se presiono la teclaselect
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                        ++teclallamar;      //tecla verde, llamar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                        ++tecla1;           //tecla 1
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        ++tecla4;           //tecla 4
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        ++tecla7;           //tecla7
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x>50){
                        ++teclaast;         //tecla asterisco
                    }    
                } else if(ev.mouse.x>110&&ev.mouse.x<208){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if(ev.mouse.y>450&&ev.mouse.y<460){
                        ++teclaup;      //tecla para arrriba
                    } else if (ev.mouse.y>525&&ev.mouse.y<540){
                        ++tecladown;    //teclaparaabajo
                    } else if(ev.mouse.y>460&&ev.mouse.y<540){  //der, izq o medio
                                if(ev.mouse.x<130){
                                    ++teclaizq;     //hacia la izquierda
                                } else if(ev.mouse.x>188){
                                    ++teclader;         //la de la derecha
                                } else{++teclamed;}     //la del medio
                    } else if(ev.mouse.y>540&&ev.mouse.y<585){
                        ++tecla2;           //tecla 2
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        ++tecla5;           //tecla 5
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        ++tecla8;           //tecla8
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720){
                        ++tecla0;         //tecla 0
                    } 
                    
                } else if(ev.mouse.x>208&&ev.mouse.x<288){      //pueden ser back,colgar,3,6,9 o numeral
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                        ++teclaback;      //se presiono la tecla back
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                        ++teclacolg;      //tecla roja,colgar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                        ++tecla3;           //tecla 3
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                        ++tecla6;           //tecla 6
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                        ++tecla9;           //tecla9
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x<268){
                        ++teclanum;         //tecla asterisco
                }
                
                }  
            }
        }
    }
    

    printf("Seleccionar:%d,\n LLamar:%d\n,1:%d,\n4:%d,\n7:%d\n,asterisco:%d.\nArriba:%d\n,Abajo:%d,\nMedio:%d\n,izq%d\n,der%d\n,2:%d\n,5:%d\n,8:%d\n,0:%d\nback:%d\n,colgar:%d\n,3:%d\n,6:%d\n,9:%d\n,numeral:%d\n",teclaselect,teclallamar,tecla1,tecla4,tecla7,teclaast,teclaup,tecladown,teclamed,teclaizq,teclader,tecla2,tecla5,tecla8,tecla0,teclaback,teclacolg,tecla3,tecla6,tecla9,teclanum);
    return 0;
}

ALLEGRO_DISPLAY* getdisplay(int ancho, int alto){
    
    ALLEGRO_DISPLAY* display=NULL;
    
    display=al_create_display(ancho,alto);
    if(display==NULL){
        fprintf(stderr,"No se pudo inicializar el display\n"); 
        return ERROR;
    }    //inicializar display
    
    return display;
}

ALLEGRO_EVENT_QUEUE* geteventqueue (void){
    
    ALLEGRO_EVENT_QUEUE* eventos=NULL;
    
    eventos=al_create_event_queue();
    
    if(eventos==NULL){
        fprintf(stderr,"No se inicializo el event queue.\n");
        
        return ERROR;
        
    }     //inicializo el event queue
    
    return eventos;
    
}

ALLEGRO_TIMER* gettimer (float periodo){
    ALLEGRO_TIMER* timer=NULL;
    
    timer=al_create_timer(periodo);
    if(timer==NULL){
        fprintf(stderr,"No se pudo inicializar el timer\n");
        return ERROR;
    }
    
    return timer;
    
}




int inicializar (void){
    
    if(!al_init()){
        fprintf(stderr,"No se pudo inicializar Allegro\n");
        return 1;
    }
    
    al_install_keyboard();
    al_install_mouse();     //instalo los perifericos
    al_install_audio();
    
    al_init_font_addon();    // inicializo el font addon
    
    
    
    if(!al_init_ttf_addon()){
        fprintf(stderr,"No se inicializo el addon ttf.\n");
        return -1;     
        
        
    }// inicializo el True Type Font addon
    
    
    if(!al_init_acodec_addon()){
        fprintf(stderr,"No se inicializo el addon de acodec\n");
        return -1;
    }           //es el addon de audio
    
    if(!al_init_image_addon()){
        fprintf(stderr,"No se inicializo el addon de imagenes\n");
        return -1;
    }           //addon de imagenes
    
    
    if(!al_init_primitives_addon()){
        fprintf(stderr,"No se inicializo el addon de acodec\n");
        return -1;
    }       //por ultimo el de primitivas
    
    
    
    return 0;
}