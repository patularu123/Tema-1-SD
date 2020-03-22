#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");
#define nmax 10000003
void copiere(long long v[],long long c[],int n)
{
    for( int i = 1 ; i <= n; i++)
        v[i]=c[i];
}
void BubbleSort(long long v[],int lungime)
{
    int i,j;
    for(i = 1; i <= lungime ; i++)
        for(j = 1; j <= lungime ; j++)
            if(v[i] < v[j])
                swap(v[i],v[j]);
}
void CountSort(long long v[],int lungime)
{
    int maxim=0,cnt=0;
    for(int i = 1; i <= lungime ; i++)
        if(v[i] > maxim)
            maxim = v[i];
    int *frecventa = new int[maxim + 1];
    for(int i = 0; i <= maxim ; i++)
        frecventa[i]=0;
    for(int i = 1; i <= lungime ; i++)
        frecventa[v[i]]++;
    for(int i = 0; i <= maxim ; i++)
        for(int j = 1; j <= frecventa[i] ; j++)
            v[++cnt]=i;
}
long long vector_final[nmax];
void Interclasare(long long v[], int st, int dr)
{
    int i, j, cnt=0, m = (st + dr) / 2;
    i = cnt = st;
    j = m + 1;
    while (i <= m && j <= dr)
    {
        if (v[i] <= v[j])
            vector_final[cnt++] = v[i++];
        else
            vector_final[cnt++] = v[j++];
    }
    while (i <= m)
        vector_final[cnt++] = v[i++];
    while (j <= dr)
        vector_final[cnt++] = v[j++];
    for (cnt = st; cnt <= dr; cnt++)
        v[cnt] = vector_final[cnt];
}
void MergeSort(long long v[], int st, int dr)
{
    int i;
    if (st == dr)
    {
        return;
    }
    int m = (st + dr) / 2;
    MergeSort(v, st, m);
    MergeSort(v, m + 1, dr);
    Interclasare(v, st, dr);
}

void QuickSort(long long v[], int st, int dr)
{
    if(st < dr)
    {
        int m = (st + dr) / 2;
        int aux = v[st];
        v[st] = v[m];
        v[m] = aux;
        int i = st, j = dr, d = 0;
        while(i < j)
        {
            if(v[i] > v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSort(v, st, i - 1);
        QuickSort(v, i + 1, dr);
    }
}

void RadixSort(long long v[],int n,int p)
{
    vector <long long> Bucket[256];
    long long Shift = p*8;
    long long Mask = 255;
    for(int i = 1; i <= n; ++i)
        Bucket[(v[i] >> Shift) & Mask].push_back(v[i]);
    int cnt= 0;
    for(int i = 0; i <= 255; ++i)
        for(int j = 0; j < (int)Bucket[i].size(); ++j)
            v[++cnt] = Bucket[i][j];
}
void Generare_numere(int n, long long v[], bool negativ, long long Max)
{
    srand(time(NULL));
    long long aux;
    for (int i = 1; i <= n ; i++)
    {
        if (negativ == 0)
        {
            aux = 1LL * rand() * rand() % (2*Max + 1) - Max;
        }
        else
        {
            aux = 1LL * rand() * rand() % (Max + 1);
        }
        v[i]=(aux);
    }
}
bool Verificare(long long *v,int &n)
{
    int ok=1;
    for(int i=0; i<n-1; i++)
        if(v[i]>v[i+1])
            return 0;
    return 1;
}
int main()
{
    int n;
    fout<<setprecision(15)<<fixed;
    int i,q;
    long long *v = new long long[nmax];
    long long *c = new long long[10000005];
    long long val_max;
    int tip;//pentru numere negative
    int nrteste;
    fin>>nrteste;
    for(q = 1; q <= nrteste ; q++)
    {
        fin >>n >> val_max >> tip;
        fout<<"Avem de sortat " << n << " numere " << " cu valoarea maxima de " << val_max << '\n';
        Generare_numere(n,v,tip,val_max);
        copiere(c,v,n);
        clock_t start,end;
        start=clock();
        MergeSort(v,1,n);
        end=clock();
        double duration = double(end-start);
        if(Verificare(v,n ) == true )
            fout<<"MergeSort a sortat corect in "<<(double) duration<<'\n';
        else
            fout<<"MergeSort nu a sortat corect"<<'\n';
        copiere(v,c,n);
        start=clock();
        QuickSort(v,1,n);
        end=clock();
        duration = double(end-start);
        if(Verificare(v,n) == true )
            fout<<"QuickSort a sortat corect in "<<(double) duration<<'\n';
        else
            fout<<"QuickSort nu a sortat corect"<<'\n';
        copiere(v,c,n);

        if(val_max <= 10000005 && tip == 1)
        {
            start=clock();
            CountSort(v,n);
            end=clock();
            duration = double(end-start);
            if(Verificare(v,n ) == true )
                fout<<"CountSort a sortat corect in "<<(double) duration<<'\n';
            else
                fout<<"CountSort nu a sortat corect"<<'\n';
            copiere(v,c,n);
        }
        else
            fout<<"CountSort nu poate sorta deoarece val_max este prea mare sau apar numere negative"<<'\n';

        if(n <= 100000)
        {
            start=clock();
            BubbleSort(v,n);
            end=clock();
            duration = double(end-start);
            if(Verificare(v,n ) == true )
                fout<<"BubbleSort a sortat corect in "<<(double) duration<<'\n';
            else
                fout<<"BubbleSort nu a sortat corect"<<'\n';
            copiere(v,c,n);
        }
        else
            fout<<"BubbleSort nu poate sorta deoarece sunt prea multe numere"<<'\n';
        start=clock();
        sort(v+1,v+n+1);
        end=clock();
        duration = double(end-start);
        if(Verificare(v ,n ) == true )
            fout<<"StlSort a sortat corect in "<<(double) duration <<'\n';
        else
            fout<<"StlSort nu a sortat corect"<<'\n';
        copiere(v,c,n);
        if(tip == 1)
        {
            start=clock();
            for(int j = 0 ; j < 4 ; j++)
                RadixSort(v,n,j);
            end=clock();
            duration = double(end-start);
            if(Verificare(v,n ) == true )
                fout<<"RadixSort a sortat corect in "<<(double) duration<<'\n';
            else
                fout<<"RadixSort nu a sortat corect"<<'\n';
        }
        else
            fout<<"RadixSort nu poate sorta deoarece apar numere negative"<<'\n';
        fout<<'\n';
    }
    return 0;
}
