//******************************************************************************/
//**************************Para Executar no hardware***************************/
//******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "altera_avalon_pio_regs.h"
#include <altera_avalon_lcd_16207.h>
#include <altera_avalon_lcd_16207_regs.h>
#include <altera_avalon_lcd_16207_fd.h>
#include "system.h"
#include <unistd.h> // usleep.h

int main() {
    /*Nios II acessa o controlador de LCD como um dispositivo STDOUT, e pode ser acessado com métodos de arquivo, such as printf().
    O controlador LCD pode ser facilmente integrado à arquitetura no QSYS. Se escolher no BSP Reduced Drives, não usa LCD*/

    typedef unsigned char alt_u8;
    alt_u8 palavra[8] = {0x07,0x08,0x21,0x12,0x41,0x0E,0x2F,0x2B}; // tAdSUFrn
    int swInputs = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_BASE);
    int sw1 = (swInputs & 0b000000000000000010);
    int cont = sw1 == 1 ? 8 : 0;

    FILE *lcd_d;
    lcd_d = fopen(LCD_NAME, "w");
    if (lcd_d == NULL) {
        fprintf(stderr, "Erro abertura\n");
        return 0;
    }

    sw1 == 0? fprintf(lcd_d, "<<<<< \n") : fprintf(lcd_d, ">>>>> \n"); 
    
    while(1) { // Este laço exibe permanentemente a frase TADS UFRN nos displays de 7 segmentos

        IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_7_BASE, palavra[cont]); // t
        IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_6_BASE, palavra[cont+1]); // A
        IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_5_BASE, palavra[cont+2]); // d
        IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_4_BASE, palavra[cont+3]); // S
        IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_3_BASE, palavra[cont+4]); // U
        IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_2_BASE, palavra[cont+5]); // F
        IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_1_BASE, palavra[cont+6]); // r
        IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_0_BASE, palavra[cont+7]); // n

        sw1 == 0 ? cont++ : cont--;

        usleep(50000);

        if(sw1 == 1 && cont < 0) {
            cont = 8;
            fprintf(lcd_d, ">>>>> \n");
        }   

        if(cont == 8 && sw1 == 0) {
            cont = 0;
            fprintf(lcd_d, "<<<<< \n");            
        }
    }
    return 0;
}

//******************************************************************************/
//**************************Para Executar no console****************************/
//******************************************************************************/

// #include <stdio.h>
// #include <string.h>
// #include <unistd.h> // usleep.h

// int main() {
//     int sw1 = 1;
//     char palavra[8] = {'T','A','D','S','U','F','R','N'}; // tAdSUFrn

//     int cont = sw1 == 1 ? 8 : 0;
//     while(1) { // Este laço exibe permanentemente a frase TADS UFRN nos displays de 7 segmentos
//         printf("%c", palavra[cont]); // t
//         usleep(50000);
//         printf("%c", palavra[cont+1]); // A
//         usleep(50000);
//         printf("%c", palavra[cont+2]); // d
//         usleep(50000);
//         printf("%c", palavra[cont+3]); // S
//         usleep(50000);
//         printf("%c", palavra[cont+4]); // U
//         usleep(50000);
//         printf("%c", palavra[cont+5]); // F
//         usleep(50000);
//         printf("%c", palavra[cont+6]); // r
//         usleep(50000);
//         printf("%c", palavra[cont+7]); // n

//         sw1 == 0 ? cont++ : cont--;
//         printf("\n");

//         usleep(50000);

//         if(sw1 == 1 && cont < 0) {
//             cont = 8;
//             printf(">>>>> \n");
//         }   

//         if(cont == 8 && sw1 == 0) {
//             cont = 0;
//             printf("<<<<< \n");
//         }
//     }
    
//     return 0;
// }