#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
 struct Personel{
    char isim[100];
    char tcKimlikNo[100];
    char telefon[100];
    char eposta[100];
    char adres[100];
 };

char secim();
int a=1;
int sayac=0;
int main()
	{
    setlocale(LC_ALL, "Turkish");
    if(a==1){
        a++;
        dosyaOlustur();
    }

    menu();
    switch(secim()){
        case '1':kayitEkle();main();
        case '2':personelListele();main();
        case '3':kayitDuzenleme();main();
        case '4':TcNoKayitBul();main();
        case '5':isimKayitBul();main();
        case '6':kayitSil();main();
        case '0':cikis();main();
        default:
        system("cls");
        printf("Yaln�� se�im yapt�n�z tekrar deneyiniz l�tfen...\n\n");
        main();
    }
    return 0;
}
void menu(){

    printf("\n\t**Bir Se�im Yap*\n");
    printf("\n\t1. Kay�t Ekle\n\t2. Personel Listele\n\t3. Kay�t D�zenle\n\t4. TC Kimlik No ile Kay�t Bul");
    printf("\n\t5. �sim ile Kay�t Bul\n\t6. Kay�t Sil\n\t0. ��k��");
    printf("\n\n\t******\n");
    printf("\nSe�iminizi giriniz:");
}
char secim(){
    char tuss;
    scanf("%s",&tuss);
    return tuss;

}
void kayitEkle()
{
    sayac=sayac+1;
    system("cls");
    printf("\n----------------------Kay�t Ekleme----------------------\n\n");
    struct Personel personel;
    printf("Personel ismini giriniz-> ");
    scanf("%s",&personel.isim);
    printf("Personel TC'sini giriniz-> ");
    scanf("%s",&personel.tcKimlikNo);
    printf("Personel Telefon numaras�n� giriniz-> ");
    scanf("%s",&personel.telefon);
    printf("Personel eposta adresini giriniz-> ");
    scanf("%s",&personel.eposta);
    printf("Personel adresini giriniz-> ");
    scanf("%s",&personel.adres);

    FILE *fp;
    fp = fopen("personel.txt", "a");

    fwrite(&personel, sizeof(personel), 1, fp);
    fclose(fp);
    system("cls");
    printf("Personel Kayd� Ba�ar�yla Eklendi...\n\n");

}
void personelListele(){

    system("cls");
    if(sayac==0)
    {
        printf("Personel kayd� yap�n�z...\n\n");
        return ;
    }
    printf("--------------------------------Personel Listesi-------------------------------\n\n");
    FILE *fp1;

    int i=1;
    fp1 = fopen("personel.txt", "rb");
    struct Personel personel;


    while (fread(&personel, sizeof(personel), 1, fp1)==1)
	{
        printf("\n�sim:%s\nTC Kimlik No:%s\nTelefon:%s\nEposta:%s\nAdres:%s\n", personel.isim, personel.tcKimlikNo, personel.telefon, personel.eposta, personel.adres);
        fseek(fp1,i* sizeof(personel),SEEK_SET);
        i++;
    }

    fclose(fp1);
    printf("\n\nAna men�ye d�nmek i�in bir tusa bas�n�z:");
    if(secim()!='jjvcj'){
       system("cls");
       main();
    }



}
void dosyaOlustur(){
    FILE *fp;
    fp = fopen("personel.txt", "w");
    fclose(fp);


}
void kayitDuzenleme(){
    system("cls");
    if(sayac==0)
    {
        printf("Personel kayd� yap�n�z...\n\n");
        return ;
    }


    printf("-----------------------------Kay�t D�zenleme----------------------------\n\n");
    char isimm[100];
    printf("\nG�ncellenek kayd�n ismini giriniz:");
    scanf("%s",&isimm);

    FILE *fp1;
    int i=1, deger=0;
    fp1 = fopen("personel.txt", "rb+");


    struct Personel personel;
    struct Personel personel2[sayac];


    rewind(fp1);
    while (fread(&personel, sizeof(personel), 1, fp1)==1){
        if(!strcmp(isimm,personel.isim)){
            printf("\nKay�t bulundu\n\n");
            fwrite(&personel, sizeof(personel), 1, fp1);
            printf("\n�sim:%s\nTC Kimlik No:%s\nTelefon:%s\nEposta:%s\nAdres:%s\n", personel.isim, personel.tcKimlikNo, personel.telefon, personel.eposta, personel.adres);
           printf("\n\nPersonel ismini giriniz:");
            scanf("%s",&personel2[i-1].isim);
            printf("Personel TC'sini giriniz:");
            scanf("%s",&personel2[i-1].tcKimlikNo);
            printf("Personel Telefon numaras�n� giriniz:");
            scanf("%s",&personel2[i-1].telefon);
            printf("Personel eposta adresini giriniz:");
            scanf("%s",&personel2[i-1].eposta);
            printf("Personel adresini giriniz:");
            scanf("%s",&personel2[i-1].adres);


        }else{
            strcpy(personel2[i-1].isim,personel.isim);
            strcpy(personel2[i-1].tcKimlikNo,personel.tcKimlikNo);
            strcpy(personel2[i-1].telefon,personel.telefon);
            strcpy(personel2[i-1].eposta,personel.eposta);
            strcpy(personel2[i-1].adres,personel.adres);
            deger=1;
        }
        fseek(fp1,i* sizeof(personel),SEEK_SET);
        i++;


    }
    if(deger==1){
        printf("\n\nGirmi� oldugunuz isimde personel bulunmamakta tekrar arama yapmak istermisiniz: e: ");
        if(secim()=='e'){
        system("cls");
        kayitDuzenleme();
        }else{
        system("cls");
        main();
        }
    }
    int b;
    fclose(fp1);

    FILE *fp2;
    fp2 = fopen("personel.txt", "wb+");
    i=1;
    for(b=0; b<sayac; b++)
    {
        fwrite(&personel2[b], sizeof(personel2[b]), 1, fp2);
        fseek(fp1,i* sizeof(personel),SEEK_SET);
        i++;

    }
    fclose(fp2);
    system("cls");
    printf("Kay�t ba�ar�yla g�ncellendi....\n\n");

 }
void TcNoKayitBul(){
    system("cls");
    int kontrol=0;
    if(sayac==0)
    {
        printf("Personel kayd� yap�n�z...\n\n");
        return ;
    }
    printf("\n---------------------TC ile Kay�t Bulma---------------------\n\n");
    char isimm[100];
    printf("\n Aranacak TC'yi giriniz=");
    scanf("%s",&isimm);

    FILE *fp1;
    int i=1;
    fp1 = fopen("personel.txt", "rb+");
    struct Personel personel;



    rewind(fp1);

    while (fread(&personel, sizeof(personel), 1, fp1)==1){

	    if(!strcmp(isimm,personel.tcKimlikNo)){

            printf("\n�sim:%s\nTC Kimlik No:%s\nTelefon:%s\nEposta:%s\nAdres:%s\n", personel.isim, personel.tcKimlikNo, personel.telefon, personel.eposta, personel.adres);
            kontrol=1;

        }
        fseek(fp1,i* sizeof(personel),SEEK_SET);
        i++;


    }
    if(kontrol==0)
    {
        printf("Kay�t bulanamad�...\n");
    }
     printf("\n\nAna men�ye d�nmek i�in bir tusa bas�n�z:");
    if(secim()!='asdbasdhghghgsdabsdba'){
       system("cls");
       main();
    }


}
void isimKayitBul(){
    system("cls");
    if(sayac==0)
    {
        printf("Personel kayd� yap�n�z...\n\n");
        return ;
    }
    printf("---------------------�sim ile Kay�t Bulma---------------------\n\n");
    char isimm[100];
    printf("\n Aranacak ismi giriniz=");
    scanf("%s",&isimm);

    FILE *fp1;
    int i=1;
    fp1 = fopen("personel.txt", "rb+");
    struct Personel personel;



    rewind(fp1);
    while (fread(&personel, sizeof(personel), 1, fp1)==1){
        if(!strcmp(isimm,personel.isim)){

            printf("\n�sim:%s\nTC Kimlik No:%s\nTelefon:%s\nEposta:%s\nAdres:%s\n", personel.isim, personel.tcKimlikNo, personel.telefon, personel.eposta, personel.adres);


        }
        fseek(fp1,i* sizeof(personel),SEEK_SET);
        i++;


    }
     printf("\n\nAna men�ye d�nmek i�in bir tusa bas�n�z:");
    if(secim()!='bvbvbv'){
       system("cls");
       main();
    }



}
void kayitSil(){
    system("cls");
    if(sayac==0)
    {
        printf("Personel kayd� yap�n�z...\n\n");
        return ;
    }
    printf("\n--------------------------------Kayit Silme---------------------------\n\n");
    char isimm[100];
    printf("\nSilinecek Personelin TC Kimlik Numaras�n� Giriniz:");
    scanf("%s",&isimm);

    FILE *fp1;
    int i=1, kontrol=0;
    fp1 = fopen("personel.txt", "rb+");
    struct Personel personel;
    struct Personel personel2[sayac];


    rewind(fp1);
    while (fread(&personel, sizeof(personel), 1, fp1)==1){
        if(!strcmp(isimm,personel.tcKimlikNo)){
            printf("isim bulundu\n");

            sayac=sayac-1;

        }else{
            strcpy(personel2[i-1].isim,personel.isim);
            strcpy(personel2[i-1].tcKimlikNo,personel.tcKimlikNo);
            strcpy(personel2[i-1].telefon,personel.telefon);
            strcpy(personel2[i-1].eposta,personel.eposta);
            strcpy(personel2[i-1].adres,personel.adres);
            kontrol=1;
            fseek(fp1,i* sizeof(personel),SEEK_SET);
            i++;
        }





    }
    if(kontrol==1){
        printf("\n Kay�t bulanamad� tekrar arama yapmak istermisiniz: e:");
        if(secim()=='e'){
            system("cls");
            kayitSil();
        }else
        {
            system("cls");
            main();

        }
    }
    int b;
    fclose(fp1);

    FILE *fp2;
    fp2 = fopen("personel.txt", "wb+");

    i=1;
    for(b=0; b<sayac; b++)
    {
        fwrite(&personel2[b], sizeof(personel2[b]), 1, fp2);
        fseek(fp1,i* sizeof(personel),SEEK_SET);
        i++;

    }
    fclose(fp2);
    system("cls");
    printf("Kay�t ba�ar�yla silindi...\n\n");
}
void cikis(){
    printf("\n C�kmak isted�inize eminmisiniz: (e/E)");
    if(secim()=='e'|| secim()=='E'){
        exit(1);
    }else{main();}

}
