#include "graf.h"

void createGraph(graph &G){
    start(G) = nil;
};

adrNode createNode(infotype Kota){
    adrNode N = new elmNode;
    info(N) = Kota;
    nextNode(N) = nil;
    firstEdge(N) = nil;
    return N;
}

adrEdge createEdge(adrNode adrKota, float bobot){
    adrEdge E = new elmEdge;
    info(E) = adrKota;
    bobot(E) = bobot;
    nextEdge(E) = nil;
    return E;
};

adrNode findNode(graph G, infotype kota){
    adrNode temp = start(G);
    while (temp != nil){
        if (info(temp) == kota) {
            return temp;
        }
        temp = nextNode(temp);
    }
    return nil;
};

void addNode(graph &G, infotype kota){
    adrNode P = createNode(kota);
    if (start(G)==nil){
        start(G) = P;
    } else{
        adrNode last = start(G);
        while (nextNode(last) != nil){
            last = nextNode(last);
        }
        nextNode(last) = P;
    }
};


void addEdge(graph &G, infotype x, infotype y, float bobot){
    adrNode N1,N2;
    adrEdge E1,E2;

    N1 = findNode(G,x);
    N2 = findNode(G,y);


    E1 = createEdge(N1, bobot);
    E2 = createEdge(N2, bobot);

    if (N1 != nil && N2 != nil){
            if (firstEdge(N1) == nil){
                firstEdge(N1) = E2;
            } else{
                adrEdge tempChild  = firstEdge(N1);
                while (nextEdge(tempChild) != nil){
                    tempChild = nextEdge(tempChild);
                }
                nextEdge(tempChild) = E2;
            }

            if (firstEdge(N2) == nil){
                firstEdge(N2) = E1;
            } else{
                adrEdge tempChild  = firstEdge(N2);
                while (nextEdge(tempChild) != nil){
                    tempChild = nextEdge(tempChild);
                }
                nextEdge(tempChild) = E1;
            }
    } else{
        cout << "Node Tidak Ditemukan" << endl;
    }
};

void printGraph(graph G) {
    adrNode temp = start(G);

    while(temp != nil) {
        cout << "Nama Kota \t\t: " << info(temp) << endl;
        adrEdge E = firstEdge(temp);
        if (E != nil) {
            cout << "Daftar Tetangga \t: " << endl;
            while (E != nil) {
                cout << "\t==> " << info(info(E)) << " (" << bobot(E) << ") "<< endl;
                E = nextEdge(E);
            }
        }
        cout << endl;
        temp = nextNode(temp);
    }
}

void copyNodeToArray(graph G, dataKota &K) {
    K.N = 0;
    adrNode N = start(G);
    while (N != nil) {
        K.arrKota[K.N] = info(N);
        K.kodeKota[K.N] = K.N;
        K.N = K.N + 1;
        N = nextNode(N);
    }
}

float getBobot(graph G, infotype X, infotype Y) {
    adrEdge E = firstEdge(findNode(G, X));
    int bobot = -1;
    while (E != nil) {
        if (info(info(E)) == Y) {
            if (bobot(E) < bobot || bobot == -1) {
                bobot = bobot(E);
            }
        }
        E = nextEdge(E);
    }

    if (bobot == -1) {
        return 0;
    }
    return bobot;
};

bool isConnected(graph G, infotype kota1, infotype kota2){
    adrNode cari = findNode(G,kota1);
    adrEdge E = firstEdge(cari);
    if (cari != nil){
        while (E != NULL){
            if (info(info(E)) == kota2){
                return true;
            }
            E = nextEdge(E);
        }
    }
    return false;
}


void copyArrayToArray(tabBobot T1, int N, tabBobot &T2) {
    for (int i = 0; i < N; i++){
        T2[i] = T1[i];
    }
}

void sirkuitTerpendek(graph G, graph &result, float &bobot, tabBobot &T) {
    dataKota K;
    tabBobot temp;

    copyNodeToArray(G, K);

    int nMax = K.N;
    int minBobot = -1;
    bool sirkuit, status;
    int weight;

    do {
        sirkuit = isConnected(G, K.arrKota[K.kodeKota[0]], K.arrKota[K.kodeKota[nMax-1]]);
        if (sirkuit) {
            weight = getBobot(G, K.arrKota[K.kodeKota[0]], K.arrKota[K.kodeKota[nMax-1]]);
            temp[nMax-1] = weight;
            status = true;
            for (int i = 1; i < nMax && status; i++) {
                status = isConnected(G, K.arrKota[K.kodeKota[i]], K.arrKota[K.kodeKota[i-1]]);
                if (status) {
                    temp[i-1] = getBobot(G, K.arrKota[K.kodeKota[i]], K.arrKota[K.kodeKota[i-1]]);
                    weight = weight + temp[i-1];
                }
            }

            if ((weight < minBobot && status) || (minBobot == -1 && status) ) {
                createGraph(result);
                for (int i = 0; i < nMax; i++) {
                    addNode(result, K.arrKota[K.kodeKota[i]]);
                }
                addNode(result, K.arrKota[K.kodeKota[0]]);
                minBobot = weight;
                copyArrayToArray(temp, nMax, T);
            }
        }
    } while (next_permutation(K.kodeKota, K.kodeKota + nMax));

    if (minBobot != -1) {
        bobot = minBobot;
        adrNode P = start(result);
        int i = 0;
        while (P != nil) {
            cout << info(P);
            if (i < nMax) {
                cout << " ==> " << "(" << T[i] << ") ";
            }
            i++;
            P=nextNode(P);
        }
        cout << " ==> Total Bobot : " << bobot << endl;
    } else {
        bobot = 0;
        cout << "==========Tidak Terdapat Sirkuit Pada Graf==========" << endl;
    }
}

int menu(){
    int pilihan;
    cout << "\n====================MENU=====================" << endl;
    cout << "1. Masukkan kota ke dalam Graf" << endl;
    cout << "2. Hubungkan kota" << endl;
    cout << "3. Tampilkan Graf" << endl;
    cout << "4. Tampilkan Sirkuit Terpendek" << endl;
    cout << "0. Keluar dari program" << endl;

    cout << "Pilihan = ";
    cin >> pilihan;
    return pilihan;
};

void backToMenu(int &pilihan) {
    string confirm;

    cout << "Kembali ke menu utama (Y/N) ? : ";
    cin >> confirm;
    if (confirm == "Y") {
        pilihan = menu();
    } else if (confirm == "N") {
        pilihan = 0;
    } else {
        cout << "Pilihan Tidak Valid";
        backToMenu(pilihan);
    }
}
