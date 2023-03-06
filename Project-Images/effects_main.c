#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Kendi baslik dosyalarimizi include ediyoruz */
#include "pgm.h"
#include "effects.h"

/* PROGRAMIN ORNEK KULLANIMI:
 *
 *      $ ./pgm_efekt
 *      Usage: ./pgm_efekt <invert|binarize|noise|smooth> <PGM image 1> <PGM image 2> ... <PGM image N>
 *
 *      $ ./pgm_efekt invert effect_images/man_ascii.pgm
 *      (Invert efekti uygulanan resim effect_images/man_ascii.pgm.invert olarak kaydedilir)
 */

int main(int argc, char *argv[])
{
    /* Program efekt adi ve EN AZ 1 resim dosyasi olmak uzere EN AZ
     * 2 arguman istemektedir.
     */
    if (argc < 3)
    {
        printf("Usage: %s <invert|binarize|noise|contrast|grey> <PGM image 1> <PGM image 2> ... <PGM image N>\n", argv[0]);
        exit(1);
    }
    int i;
    /* Komut satirindan gelen efekt adi */
    char *effect_name = argv[1];
    srand(time(NULL));
    /* Bazi efektlerin ihtiyac duyabilecegi rand() rassal
     * sayi ureteci seed edilir.
     */
    int threshold = 67 + rand() % 121;

    PGMInfo pgm_info;
    char effectedPhoto[LINE_MAX];
    int return_val;
    if (strcmp(effect_name, "invert") == 0)
    {
        for (i = 2; i < argc; i++)
        {
            pgm_info = pgm_read(argv[i]);
            // Efektli dosyanin ismi olusturulur.
            strcpy(effectedPhoto, argv[i]);
            strcat(effectedPhoto, ".invert");

            // Dosya okunurken hata ciktiysa uyari verilir.
            if (pgm_info.error != 0)
            {
                printf("%s\n", pgm_error_messages[pgm_info.error]);
            }
            else
            {
                // Dosyanin baslik bilgileri yazdirilir.
                pgm_print_header(pgm_info);
                // İstenen efektin fonksiyonu cagrilir.
                effect_invert(pgm_info.pixels, pgm_info.width, pgm_info.height);
                // PGM dosyasi olusturulur
                return_val = pgm_write(effectedPhoto, pgm_info);
                if (return_val == 1)
                {
                    printf("PGM dosyasi olusturulurken hata meydana geldi.");
                }

                free(pgm_info.pixels);
            }
        }
    }
    else if (strcmp(effect_name, "binarize") == 0)
    {
        for (i = 2; i < argc; i++)
        {
            pgm_info = pgm_read(argv[i]);
            // Efektli dosyanin ismi olusturulur.
            strcpy(effectedPhoto, argv[i]);
            strcat(effectedPhoto, ".binarize");
            // Dosya okunurken hata ciktiysa uyari verilir.
            if (pgm_info.error != 0)
            {
                printf("%s\n", pgm_error_messages[pgm_info.error]);
            }
            else
            {
                // Dosyanin baslik bilgileri yazdirilir.
                pgm_print_header(pgm_info);
                // İstenen efektin fonksiyonu cagrilir.
                effect_threshold(pgm_info.pixels, pgm_info.width, pgm_info.height, threshold);
                // PGM dosyasi olusturulur
                return_val = pgm_write(effectedPhoto, pgm_info);
                if (return_val == 1)
                {
                    printf("PGM dosyasi olusturulurken hata meydana geldi.");
                }

                free(pgm_info.pixels);
            }
        }
    }
    else if (strcmp(effect_name, "noise") == 0)
    {
        for (i = 2; i < argc; i++)
        {
            pgm_info = pgm_read(argv[i]);

            strcpy(effectedPhoto, argv[i]);
            strcat(effectedPhoto, ".noise");
            // Dosya okunurken hata ciktiysa uyari verilir.
            if (pgm_info.error != 0)
            {
                printf("%s\n", pgm_error_messages[pgm_info.error]);
            }
            else
            {
                // Dosyanin baslik bilgileri yazdirilir.
                pgm_print_header(pgm_info);
                // İstenen efektin fonksiyonu cagrilir.
                effect_random_noise(pgm_info.pixels, pgm_info.width, pgm_info.height);
                // PGM dosyasi olusturulur
                return_val = pgm_write(effectedPhoto, pgm_info);

                if (return_val == 1)
                {
                    printf("PGM dosyasi olusturulurken hata meydana geldi.");
                }

                free(pgm_info.pixels);
            }
        }
    }
    else if (strcmp(effect_name, "contrast") == 0)
    {
        for (i = 2; i < argc; i++)
        {
            pgm_info = pgm_read(argv[i]);

            strcpy(effectedPhoto, argv[i]);
            strcat(effectedPhoto, ".contrast");
            // Dosya okunurken hata ciktiysa uyari verilir.
            if (pgm_info.error != 0)
            {
                printf("%s\n", pgm_error_messages[pgm_info.error]);
            }
            else
            {
                // Dosyanin baslik bilgileri yazdirilir.
                pgm_print_header(pgm_info);
                // İstenen efektin fonksiyonu cagrilir.
                effect_contrast(pgm_info.pixels, pgm_info.width, pgm_info.height);
                // PGM dosyasi olusturulur
                return_val = pgm_write(effectedPhoto, pgm_info);

                if (return_val == 1)
                {
                    printf("PGM dosyasi olusturulurken hata meydana geldi.");
                }

                free(pgm_info.pixels);
            }
        }
    }
    else if (strcmp(effect_name, "grey") == 0)
    {
        for (i = 2; i < argc; i++)
        {
            pgm_info = pgm_read(argv[i]);

            strcpy(effectedPhoto, argv[i]);
            strcat(effectedPhoto, ".grey");
            // Dosya okunurken hata ciktiysa uyari verilir.
            if (pgm_info.error != 0)
            {
                printf("%s\n", pgm_error_messages[pgm_info.error]);
            }
            else
            {
                // Dosyanin baslik bilgileri yazdirilir.
                pgm_print_header(pgm_info);
                // İstenen efektin fonksiyonu cagrilir.
                effect_grey(pgm_info.pixels, pgm_info.width, pgm_info.height);
                // PGM dosyasi olusturulur
                return_val = pgm_write(effectedPhoto, pgm_info);

                if (return_val == 1)
                {
                    printf("PGM dosyasi olusturulurken hata meydana geldi.");
                }

                free(pgm_info.pixels);
            }
        }
    }

    return 0;
}
