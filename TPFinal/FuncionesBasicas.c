
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>              //son todas las librerias que se utilizaran
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <string.h>
#include "Final.h"
#include <ftdi.h>
#include <unistd.h>


int analizarteclado (ALLEGRO_EVENT_QUEUE* eventos){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    
    
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
                              //se presiono la teclaselect
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                              //tecla verde, llamar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                  //tecla 1
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 4
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla7
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x>50){
                                //tecla asterisco
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
                                             //la de la derecha
                                } else{}     //la del medio
                    } else if(ev.mouse.y>540&&ev.mouse.y<585){
                                   //tecla 2
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 5
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla8
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720){
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
                                   //tecla 3
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 6
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
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

INFOPANTALLA getuserdata(void){
    FILE* miarchivo=NULL;
    unsigned int i=0,j=0;   //contadores
    INFOPANTALLA pantalla;
    ALLEGRO_COLOR color;
    unsigned int check=0;       //esta varible sera para ver el numero con el que se pide el color
    char ayuda[5]={0,0,0,0,0};      //este arreglo para lo que sirve es para ir guardando los ascii para despues pasarlos a ints
    char caracter;
    
    char defaults[140];
    
    
    miarchivo=fopen("configuracion.txt","r");
    if(miarchivo==NULL){
        miarchivo=fopen("default.txt","r");
        while (((caracter = fgetc (miarchivo)) != '\n')) { 
                    *(defaults+j) = caracter;
                    j++; 
        }
        defaults[j]=0;
        j=0;
        strcpy(pantalla.usuario,defaults);
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.compania=atoi(ayuda);
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        check=atoi(ayuda);
        if(check==NOCAMBIO){
            pantalla.fondo.entro=0;
        }else if(check==ROJO){
            pantalla.fondo.entro=ROJO;
            pantalla.fondo.colorfondo=al_map_rgb(255,0,0);
        }else if(check==AMARILLO){
            pantalla.fondo.entro=AMARILLO;
            pantalla.fondo.colorfondo=al_map_rgb(255,255,0);
        }else if(check==VERDE){
            pantalla.fondo.entro=VERDE;
            pantalla.fondo.colorfondo=al_map_rgb(0,255,0);
        }else if(check==MORADO){
            pantalla.fondo.entro=MORADO;
            pantalla.fondo.colorfondo=al_map_rgb(255,0,255);
        }else if(check==CELESTE){
            pantalla.fondo.entro=CELESTE;
            pantalla.fondo.colorfondo=al_map_rgb(102,255,255);
        }else if(check==NARANJA){
            pantalla.fondo.entro=NARANJA;
            pantalla.fondo.colorfondo=al_map_rgb(255,153,0);
        }else if(check==ROSA){
            pantalla.fondo.entro=ROSA;
            pantalla.fondo.colorfondo=al_map_rgb(255,153,153);
        }
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        while (((caracter = fgetc (miarchivo)) != '\n')) { 
                    *(defaults+j) = caracter;
                    j++; 
        }
        defaults[j]=0;
        j=0;
        strcpy(pantalla.mensajepersonal,defaults);
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        check=atoi(ayuda);
        if(check==NOCAMBIO){
            pantalla.mensajecolor.colormensaje=al_map_rgb(0,0,0);
            pantalla.mensajecolor.tipocolor=NOCAMBIO;
        }else if(check==ROJO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,0,0);
            pantalla.mensajecolor.tipocolor=ROJO;
        }else if(check==AMARILLO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,255,0);
            pantalla.mensajecolor.tipocolor=AMARILLO;
        }else if(check==VERDE){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(0,255,0);
            pantalla.mensajecolor.tipocolor=VERDE;
        }else if(check==MORADO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,0,255);
            pantalla.mensajecolor.tipocolor=MORADO;
        }else if(check==CELESTE){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(102,255,255);
            pantalla.mensajecolor.tipocolor=CELESTE;
        }else if(check==NARANJA){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,153,0);
            pantalla.mensajecolor.tipocolor=NARANJA;
        }else if(check==ROSA){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,153,153);
            pantalla.mensajecolor.tipocolor=ROSA;
        }
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.tamanomensaje=atoi(ayuda);
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.tipoescritura=atoi(ayuda);   
    } else {
        while (((caracter = fgetc (miarchivo)) != '\n')) { 
                    *(defaults+j) = caracter;
                    j++; 
        }
        defaults[j]=0;
        j=0;
        strcpy(pantalla.usuario,defaults);
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.compania=atoi(ayuda);
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        check=atoi(ayuda);
        if(check==NOCAMBIO){
            pantalla.fondo.entro=0;
        }else if(check==ROJO){
            pantalla.fondo.entro=ROJO;
            pantalla.fondo.colorfondo=al_map_rgb(255,0,0);
        }else if(check==AMARILLO){
            pantalla.fondo.entro=AMARILLO;
            pantalla.fondo.colorfondo=al_map_rgb(255,255,0);
        }else if(check==VERDE){
            pantalla.fondo.entro=VERDE;
            pantalla.fondo.colorfondo=al_map_rgb(0,255,0);
        }else if(check==MORADO){
            pantalla.fondo.entro=MORADO;
            pantalla.fondo.colorfondo=al_map_rgb(255,0,255);
        }else if(check==CELESTE){
            pantalla.fondo.entro=CELESTE;
            pantalla.fondo.colorfondo=al_map_rgb(102,255,255);
        }else if(check==NARANJA){
            pantalla.fondo.entro=NARANJA;
            pantalla.fondo.colorfondo=al_map_rgb(255,153,0);
        }else if(check==ROSA){
            pantalla.fondo.entro=ROSA;
            pantalla.fondo.colorfondo=al_map_rgb(255,153,153);
        }
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        while (((caracter = fgetc (miarchivo)) != '\n')) { 
                    *(defaults+j) = caracter;
                    j++; 
        }
        defaults[j]=0;
        j=0;
        strcpy(pantalla.mensajepersonal,defaults);
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        check=atoi(ayuda);
        if(check==NOCAMBIO){
            pantalla.mensajecolor.colormensaje=al_map_rgb(0,0,0);
            pantalla.mensajecolor.tipocolor=NOCAMBIO;
        }else if(check==ROJO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,0,0);
            pantalla.mensajecolor.tipocolor=ROJO;
        }else if(check==AMARILLO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,255,0);
            pantalla.mensajecolor.tipocolor=AMARILLO;
        }else if(check==VERDE){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(0,255,0);
            pantalla.mensajecolor.tipocolor=VERDE;
        }else if(check==MORADO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,0,255);
            pantalla.mensajecolor.tipocolor=MORADO;
        }else if(check==CELESTE){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(102,255,255);
            pantalla.mensajecolor.tipocolor=CELESTE;
        }else if(check==NARANJA){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,153,0);
            pantalla.mensajecolor.tipocolor=NARANJA;
        }else if(check==ROSA){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,153,153);
            pantalla.mensajecolor.tipocolor=ROSA;
        }
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.tamanomensaje=atoi(ayuda);
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.tipoescritura=atoi(ayuda);
    }
    
    return pantalla;
    fclose(miarchivo);
}
void putuserdata (INFOPANTALLA mipantalla){
    FILE* miarchivo=NULL;
    miarchivo=fopen("configuracion.txt","w");       //siempre destruyo si ya existe
    if (miarchivo==NULL){
        fprintf(stderr,"No se pudo abrir el archivo\n");
        exit -1;
    }
    fprintf(miarchivo,"%s\n",mipantalla.usuario);
    
    fprintf(miarchivo,"%d\n",mipantalla.compania);
    fprintf(miarchivo,"%d\n",mipantalla.fondo.entro);
    fprintf(miarchivo,"%s\n",mipantalla.mensajepersonal);
    fprintf(miarchivo,"%d\n",mipantalla.mensajecolor.tipocolor);
    fprintf(miarchivo,"%d\n",mipantalla.tamanomensaje);
    fprintf(miarchivo,"%d\n",mipantalla.tipoescritura);
    
    return ;
    
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
        
        sleep(4);                               //espero 2 segundos de manera que parezca que se esta prendiendo
        
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
        
        sleep(4);                               //espero 2 segundos de manera que parezca que se esta prendiendo
        
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
        
        sleep(4);                               
        
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
        
        sleep(4);                               //espero 2 segundos de manera que parezca que se esta prendiendo
        
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
    al_draw_text(fuente,datos.mensajecolor.colormensaje,0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);
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
void ponerarrayenpantalla (char* arreglo,int x,int y,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla) {
    ALLEGRO_FONT* fuente=NULL;
    fuente=crearfuente(MEDIA);
    
    
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),x,y,ALLEGRO_ALIGN_LEFT,arreglo);
    cambiopantalla(display,pantalla);
            
            
    al_destroy_font(fuente);
}
