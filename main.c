
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


const char* genID()
{
    static char alfabet[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char c[6];

    int i;
    for(i=0;i<6;i++)
        {int aux = rand() % strlen(alfabet) ;
        c[i]=alfabet[aux];}

    c[6]='\0';

    return c;

}

const char* encID(char id[])
{
    int k=rand()%26;
    while(k==0)
    {
        k=rand()%26;
    }
    char cc[strlen(id)];
    strcpy(cc,id);

    int i;
    for(i=0;i<strlen(cc);i++)
        cc[i]+=k;

    cc[strlen(cc)]='\0';

    return cc;

}

const char* decID(char id[],int k)
{
    int i;
    char cr[strlen(id)];
    strcpy(cr,id);
    for(i=0;i<strlen(id);i++)
        cr[i]=cr[i]-k;

    cr[strlen(cr)]='\0';

    return cr;

}

struct Nod
{
    char id[15];
    char cuv[30];
    struct Nod *urm;
};

typedef struct Nod TNod;
typedef TNod *ref;
ref p,q,r,s;

struct tablou
{
    struct Nod *pntr;
    char id_enc[15];

};

struct tablou tab[100];

int nr=0;
int size=0;

void creare(char cuvant[])
{
    q=(ref) malloc (sizeof(TNod));
    strcpy(q->id,genID());
    strcpy(q->cuv,cuvant);

    q->urm=NULL;
    p=q;
}

void inserare(char cuvant[])
{
    s=(ref)malloc(sizeof(TNod));
    strcpy(s->id, genID());
    strcpy(s->cuv,cuvant);

    s->urm=NULL;
    q->urm=s;
    q=s;

}

int j=0;

void parcurgere()
{
    r=p;
    while(r!=NULL)
    {
        j=j+1;
        char z[6];
        strcpy(z,encID(r->id));
        strcpy(tab[j].id_enc,z);
        tab[j].pntr=r;

       // printf("\nCuvant: %s\tID: %s\tID_E: %s\n",r->cuv,r->id,tab[j].id_enc);
        r=r->urm;
    }
}

void afisare(int n)
{
    printf("\n");
    int i;
    for (i=1;i<=n;i++)
        printf("Cuvantul %d: %s\nID: %s\tID Encriptat: %s\n\n",i,tab[i].pntr->cuv,tab[i].pntr->id,tab[i].id_enc);

}

int main()
{
    char text[300];

    printf("*** CRIPTARE / DECRIPTARE ***\n\n");
    printf("Partea 1: CRIPTARE\n\n");
    printf("Pentru a introduce un text de la tastatura apasa '1';\nPentru a folosi un exemplu dat apasa '2'.\n\n");
    printf("Raspuns: ");
    int rasp;
    scanf("%d",&rasp);

    while(rasp!=1 && rasp!=2)
    {
        printf("\n!! Prelucrare imposibila !!\n");
        printf("Pentru a introduce un text de la tastatura apasa '1';\nPentru a folosi un exemplu dat apasa '2'.\n\n");
        printf("Raspuns: ");
        scanf("%d",&rasp);
    }

    if(rasp==1)
        {printf("Introduce-ti textul:\n\n");
        fflush(stdin);
        fgets(text,sizeof(text),stdin);
        }
        else
            {strcpy(text,"Trei inele pentru stapanii elfi cei de sub soare, Sapte pentru ei, gnomii de vita din sali de stanca, Noua, Oamenilor care stiu ca-n lumea lor se moare, Unul pentru el, Seniorul Intunecimii-n noaptea lui adanca.");
            printf("Exemplu de text pe care il vom folosi:\n\n");
            printf("Trei inele pentru stapanii elfi cei de sub soare,\nSapte pentru ei, gnomii de vita din sali de stanca,\nNoua, Oamenilor care stiu ca-n lumea lor se moare,\nUnul pentru el, Seniorul Intunecimii-n noaptea lui adanca.\n\n");
            }


    char *x;
    x=strtok(text," ");
    nr++;
    creare(x);
    x=strtok(NULL," ");
    while(x!=NULL)
        {nr++;
        inserare(x);
        x=strtok(NULL," ");}

    size=nr;

    parcurgere();

    char rasp2;
    printf("\nFiecare cuvant a primit un ID care a fost encriptat.\nVizualizare lista? (D/N): ");
    fflush(stdin);
    scanf("%c",&rasp2);

    if(rasp2=='D' || rasp2=='d')
        afisare(size);


    printf("\nApasa orice tasta pentru a continua...");
    getch();

    system("cls");

    printf("Partea 2: DECRIPTARE\n");
    printf("Obs: Presupunem ca putem vedea doar tabloul cu id-uri encriptate si id-urile normale.\n\n\n");

    printf("Apasa orice tasta pentru a continua...\n\n\n");
    getch();

    int k,i,ex=0;
    char aux[6];


    for(i=1;i<=size;i++)
        {  printf("Se incearca pentru cuvantul %d cheia: ",i);
        for(k=1;k<=26;k++)
            {if(k==1)
                printf("%d",k);
                else
                    printf(", %d",k);
            strcpy(aux,decID(tab[i].id_enc,k));
            if( strcmp(aux,tab[i].pntr->id)==0 )
                {printf("\nS-a decriptat cuvantul %d cu cheia %d\nCuvantul este: %s\n\n",i,k,tab[i].pntr->cuv);
                ex++;
                break;
                }
            }
        }

    if(ex==size)
        {printf("S-au decriptat toate cuvintele!\n\nMesajul a fost:\n\n");
        for(i=1;i<=size;i++)
            printf("%s ",tab[i].pntr->cuv);
        printf("\n\n");
        }

    else
        printf("Eroare! Nu s-au decriptat toate cuvintele\n\n");


    getch();
    printf("Gabriel Totan, Facultatea de Matematica si Informatica, Universitatea de Vest din Timisoara.");
    return 0;
}
