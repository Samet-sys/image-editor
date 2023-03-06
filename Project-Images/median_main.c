#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgm.h"

#define N_IMAGES 9

/* Pixels dizisi siralanir ve ortanca elemanin degeri geri dondurulur */

/* Sedgewick tarafindan belirlenen gap serisiyle calisan shell sort */
unsigned char sort_and_get_median(unsigned char *pixels, int size)
{

    int gaps[] = {4193, 1073, 281, 77, 23, 8, 1};
    int gaps_sizes = sizeof(gaps) / sizeof(int);
    int i, j, k, pivot, current_gap;
    for (i = 0; i < gaps_sizes; i++)
    {
        current_gap = gaps[i];
        for (j = current_gap; j < size; j++)
        {
            pivot = pixels[j];
            k = j;
            while (k >= current_gap && pixels[k - current_gap] > pivot)
            {
                pixels[k] = pixels[k - current_gap];
                k = k - current_gap;
            }
            pixels[k] = pivot;
        }
    }
    return pixels[size / 2];
}

int main(int argc, const char *argv[])
{
    int i;

    /* 9 adet resim var */
    PGMInfo images[N_IMAGES];
    // Program ornek kullanimi
    if (argc > 1)
    {
        printf("Usage: %s \n", argv[0]);
        exit(1);
    }

    for (i = 0; i < N_IMAGES; i++)
    {
        // 9 adet fotograf isimlerini degiskene atiyoruz.
        char img_name[25];
        char s[2];
        sprintf(s, "%d", i + 1);
        strcpy(img_name, "median_images/");
        strcat(img_name, s);
        strcat(img_name, ".pgm");

        // Fotograflar images[] dizisine okunuyor.
        images[i] = pgm_read(img_name);
        if (images[i].error != 0)
        {
            printf("%s\n", pgm_error_messages[images[i].error]);
            exit(1);
        }
        pgm_print_header(images[i]);
    }

    /* Temizlenmis resim icin baslik kismini hazirlayalim */
    PGMInfo temizlenmis_pgm;

    strcpy(temizlenmis_pgm.signature, images[0].signature);
    strcpy(temizlenmis_pgm.comment, images[0].comment);
    temizlenmis_pgm.max_pixel_value = images[0].max_pixel_value;
    temizlenmis_pgm.height = images[0].height;
    temizlenmis_pgm.width = images[0].width;
    /* Temizlenmis resmin pikselleri icin yer ayiralim */
    temizlenmis_pgm.pixels = malloc(images[0].width * images[0].height);

    /* Median filtreleme */
    unsigned char pixels_value[N_IMAGES];
    for (i = 0; i < images[0].width * images[0].height; i++)
    {
        for (int j = 0; j < N_IMAGES; j++)
        {
            pixels_value[j] = images[j].pixels[i];
        }
        temizlenmis_pgm.pixels[i] = sort_and_get_median(pixels_value, N_IMAGES);
    }

    /* Temizlenmis resim kaydedilir */
    pgm_write("median_images/filtered.pgm", temizlenmis_pgm);

    /*  Temizlenmis resmin piksel alani free() edilir */
    free(temizlenmis_pgm.pixels);

    /* Tum fotograflarin piksel alanlarini free() edilir */
    for (i = 0; i < N_IMAGES; i++)
    {
        free(images[i].pixels);
    }

    return 0;
}
