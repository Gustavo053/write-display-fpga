#include <stdio.h>
#include <string.h>
#include "altera_avalon_pio_regs.h"
//#include <altera_avalon_lcd_16207.h>
//#include <altera_avalon_lcd_16207_regs.h>
//#include <altera_avalon_lcd_16207_fd.h>
#include "system.h"
#include <unistd.h> // usleep.h

typedef unsigned char byte
byte palavra[8] = {0x07,0x08,0x21,0x12,0x41,0x0E,0x2F,0x2B}; // tAdSUFrn
int sw1 = 0;

/**
    TENTAR IMPRIMIR O APELIDO "GUGU".

    LETRA G => 1 0 1 1 1 1 1
    LETRA U => 0 1 1 1 1 1 0

    *Estava tendo na conversação do binário para
     hexadecimal no próprio display de 7 segmentos.
**/

int main() {
    /*Nios II acessa o controlador de LCD como um dispositivo STDOUT, e pode ser acessado com métodos de arquivo, such as printf().
    O controlador LCD pode ser facilmente integrado à arquitetura no QSYS. Se escolher no BSP Reduced Drives, não usa LCD*/
    double x = 10.2;
    FILE *lcd_d;
    lcd_d = fopen(LCD_NAME, "w");
    if (lcd_d == NULL) {
        fprintf(stderr, "Erro abertura\n");
        return 0;
    }
    fprintf(lcd_d, "TADS UFRN \n"); // se o tamanho da string exibida não ultrapassar 16, não gera scroll
    fprintf(lcd_d, "x: %.2f", x); // segunda linha
    fclose(lcd_d);

    int cont = 0;
    while(1) { // Este laço exibe permanentemente a frase TADS UFRN nos displays de 7 segmentos
        if(sw1 == 1 && cont == 0) {
            cont = 8;
            fprintf(lcd_d, "<<<<< \n")
        }            
        if(cont == 8 && sw1 == 0) {
            cont = 0;
            fprintf(lcd_d, ">>>>> \n")
        }
        if(sw1 == 0) {
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_7_BASE, palavra[cont]); // t
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_6_BASE, palavra[cont+1]); // A
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_5_BASE, palavra[cont+2]); // d
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_4_BASE, palavra[cont+3]); // S
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_3_BASE, palavra[cont+4]); // U
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_2_BASE, palavra[cont+5]); // F
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_1_BASE, palavra[cont+6]); // r
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_0_BASE, palavra[cont+7]); // n
        } else {
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_7_BASE, palavra[cont]); // t
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_6_BASE, palavra[cont-1]); // A
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_5_BASE, palavra[cont-2]); // d
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_4_BASE, palavra[cont-3]); // S
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_3_BASE, palavra[cont-4]); // U
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_2_BASE, palavra[cont-5]); // F
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_1_BASE, palavra[cont-6]); // r
            IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_0_BASE, palavra[cont-7]); // n
        }        

        sw1 == 0 ? cont++ : cont--;

        usleep(50000);
    }
    return 0;
}
