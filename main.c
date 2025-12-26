#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define KOLON 6   // il, klinik, gun, ay, yil, saat

int randevular[MAX][KOLON];
int randevuSayisi = 0;
char ad[30], soyad[30];
void menu();
void yeniRandevu();
void bilgileriGuncelle();
void randevuIptal();
void randevulariGoruntule();
void dosyayaYaz();
void dosyadanOku();

int main() 
{
    int vatandas;
    char kimlik[12];

    printf("T.C. vatandasi misiniz?\n1-Evet\n2-Hayir\nSecim: ");
    scanf("%d", &vatandas);

    if (vatandas == 1)
        printf("11 haneli T.C. Kimlik No giriniz: ");
    else
        printf("99 ile baslayan 11 haneli YKN giriniz: ");
    scanf("%s", kimlik);

	dosyadanOku();
    printf("Adinizi giriniz: ");
    scanf("%s", ad);

    printf("Soyadinizi giriniz: ");
    scanf("%s", soyad);
  
    menu();
    return 0;
}

                /* MENU */
void menu() 
{
    int secim;
    do 
	{
        printf("\nHos geldiniz %s %s\n", ad, soyad);
        printf("\n--- MENU ---\n");
        printf("1- Yeni Randevu Al\n");
        printf("2- Randevu Iptal Et\n");
        printf("3- Randevulari Goruntule\n");
        printf("4- Bilgileri Guncelle\n");
        printf("5- Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        switch (secim) 
		{
            case 1: yeniRandevu(); break;
            case 2: randevuIptal(); break;
            case 3: randevulariGoruntule(); break;
            case 4: bilgileriGuncelle(); break;
            case 5: dosyayaYaz(); printf("Cikis yapiliyor...\n"); break;
            default: printf("Hatali secim!\n");
        }
    } while (secim != 5);
}

					 /* YENI RANDEVU */
void yeniRandevu() {
    if (randevuSayisi >= MAX) 
	{
        printf("Randevu listesi dolu!\n");
        return;
    }

    printf("Il (1-Bursa 2-Istanbul): ");
    scanf("%d", &randevular[randevuSayisi][0]);

    printf("Klinik (1-Dahiliye 2-Dis): ");
    scanf("%d", &randevular[randevuSayisi][1]);

    printf("Gun: ");
    scanf("%d", &randevular[randevuSayisi][2]);

    printf("Ay: ");
    scanf("%d", &randevular[randevuSayisi][3]);

    printf("Yil: ");
    scanf("%d", &randevular[randevuSayisi][4]);

    printf("Saat: ");
    scanf("%d", &randevular[randevuSayisi][5]);

    randevuSayisi++;
    printf("Randevu onaylandi!\n");
}

					 /* RANDEVU IPTAL */
void randevuIptal() 
{
    int secim;

    if (randevuSayisi == 0)
	{
        printf("Iptal edilecek randevu yok!\n");
        return;
    }

    randevulariGoruntule();
    printf("Iptal edilecek randevu numarasi: ");
    scanf("%d", &secim);

    if (secim < 1 || secim > randevuSayisi) 
	{
        printf("Hatali secim!\n");
        return;
    }
    int i,j;
    for ( i = secim - 1; i < randevuSayisi - 1; i++) 
	{
        for ( j = 0; j < KOLON; j++) 
		{
            randevular[i][j] = randevular[i + 1][j];
        }
    }

    randevuSayisi--;
    printf("Randevu iptal edildi.\n");
}

					 /* RANDEVULARI GORUNTULE */
void randevulariGoruntule() 
{
    if (randevuSayisi == 0) 
	{
        printf("Kayitli randevu yok.\n");
        return;
    }
	int i;
    for ( i = 0; i < randevuSayisi; i++) 
	{
        printf("\n%d. Randevu -> %s %s | Tarih: %02d/%02d/%d Saat:%d",
               i + 1,
               ad, soyad,
               randevular[i][2],
               randevular[i][3],
               randevular[i][4],
               randevular[i][5]);
    }
    printf("\n");
}
    
    			 	 /*BÝLGÝLERÝ GUNCELLE*/	
				
void bilgileriGuncelle() 
{
    int secim, onay;

    printf("\n--- BILGI GUNCELLE ---\n");
    printf("1- Ad\n");
    printf("2- Soyad\n");
    printf("3- Iptal\n");
    printf("Secim: ");
    scanf("%d", &secim);

    if (secim == 1) 
	{
        printf("Yeni ad: ");
        scanf("%s", ad);
    }
    else if (secim == 2) 
	{
        printf("Yeni soyad: ");
        scanf("%s", soyad);
    }
    else 
	{
        return;
    }

    printf("Degisiklikleri onayliyor musunuz?\n1-Evet\n2-Hayir\n");
    scanf("%d", &onay);

    if (onay == 1) 
	{
        printf("Bilgiler guncellendi.\n");
        dosyayaYaz();
    } 
	else 
	{
        printf("Degisiklik iptal edildi.\n");
    }
}

					 /* DOSYAYA YAZ */
void dosyayaYaz() {
    FILE *fp = fopen("randevu.txt", "w");
    if (fp == NULL) 
	{
        printf("Dosya acilamadi!\n");
        return;
    }

    fprintf(fp, "%s %s\n", ad, soyad);
    fprintf(fp, "%d\n", randevuSayisi);
	
	int i, j;
    for ( i = 0; i < randevuSayisi; i++) 
	{
        for ( j = 0; j < KOLON; j++) 
		{
            fprintf(fp, "%d ", randevular[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

					 /* DOSYADAN OKU */
void dosyadanOku() {
    FILE *fp = fopen("randevu.txt", "r");
    if (fp == NULL)
        return;

    fscanf(fp, "%s %s", ad, soyad);
    fscanf(fp, "%d", &randevuSayisi);
	
	int i, j;
    for ( i = 0; i < randevuSayisi; i++) 
	{
        for ( j = 0; j < KOLON; j++) 
		{
            fscanf(fp, "%d", &randevular[i][j]);
        }
    }
    fclose(fp);
}

