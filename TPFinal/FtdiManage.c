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

char getFTDIdata (struct ftdi_context ftdic);
void writeFTDIdata (char data, struct ftdi_context ftdic);

void writeFTDIdata (char data, struct ftdi_context ftdic)
{
	char x;
	x = data; 
	ftdi_write_data(&ftdic, &x, 1);

}

char getFTDIdata (struct ftdi_context ftdic)

 {
   
	int f = 0;     
	unsigned char buf[1024];
   
	f = ftdi_read_data(&ftdic, buf, sizeof(buf));

	return buf[0];        
                 
}