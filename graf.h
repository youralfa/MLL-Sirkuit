#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED

#include <iostream>
//#include <bits/stdc++.h>

using namespace std;

#define info(X) X->info
#define firstEdge(X) X->firstEdge
#define nextNode(X) X->nextNode
#define bobot(X) X->bobot
#define nextEdge(X) X->nextEdge
#define start(G) G.start
#define nil NULL


typedef string infotype;
typedef struct elmNode *adrNode;
typedef struct elmEdge *adrEdge;

struct elmNode{
    infotype info;
    adrNode nextNode;
    adrEdge firstEdge;
};

struct elmEdge{
    adrNode info;
    float bobot;
    adrEdge nextEdge;
};

struct graph {
    adrNode start;
};

struct dataKota {
    string arrKota[2023];
    int kodeKota[2023];
    int N;
};

typedef float tabBobot[2023];

void createGraph(graph &G);
adrNode createNode(infotype kota);
adrEdge createEdge(adrNode adrKota, float bobot);
void addNode(graph &G, infotype kota);
void addEdge(graph &G, infotype x, infotype y, float bobot);
adrNode findNode(graph G, infotype kota);
void printGraph(graph G);
bool isConnected(graph G, infotype kota1, infotype kota2);
float getBobot(graph G, infotype X, infotype Y);
void copyNodeToArray(graph G, dataKota&K);
void sirkuitTerpendek(graph G, graph &result, float &bobot, tabBobot &T);
int menu();
void backToMenu(int &pilihan);


#endif // GRAF_H_INCLUDED

