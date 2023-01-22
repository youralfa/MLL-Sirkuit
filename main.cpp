#include "graf.h"

int main(){

    int pilihan, N, iteration;

    infotype kota1, kota2;
    graph G,result;
    dataKota K;
    tabBobot temp;
    float bobot;

    createGraph(G);

//    addNode(G,"Hegarmanah");
//    addNode(G,"Dago");
//    addNode(G,"Ciumbuleuit");
//    addNode(G,"Cimanuk");
//    addNode(G, "Supratman");
//
//    addEdge(G, "Hegarmanah", "Ciumbuleuit", 20);
//    addEdge(G, "Hegarmanah", "Dago", 25);
//    addEdge(G, "Hegarmanah", "Cimanuk", 35);
//
//    addEdge(G, "Ciumbuleuit", "Dago", 37);
//    addEdge(G, "Ciumbuleuit", "Cimanuk", 13);
//    addEdge(G, "Ciumbuleuit", "Supratman", 17);
//
//    addEdge(G, "Cimanuk", "Supratman", 15);
//    addEdge(G, "Dago", "Cimanuk", 22);

    pilihan = menu();
    while (pilihan != 0) {
        switch(pilihan){
        case 1:
            cout << "================TAMBAH KOTA==================" << endl;
            cout << "Banyak Kota yang ingin dimasukkan: ";
            cin >> N;
            iteration = 1;
            while (iteration <= N){
                cout << "[" << iteration << "]" << " ";
                cout << "Masukkan nama kota: ";
                cin >> kota1;
                addNode(G,kota1);
                iteration++;
            }
            break;
        case 2:
            cout << "===============HUBUNGKAN KOTA=================" << endl;
            cout << "Banyak Kota yang Ingin Saling Dihubungkan : ";
            cin >> N;
            iteration = 1;
            while (iteration <= N){
                cout << endl << "[" << iteration << "]" << endl;
                cout << "Kota Asal\t: ";
                cin >> kota1;
                cout << "Kota Tujuan\t: ";
                cin >> kota2;
                cout << "Jarak Kota\t: ";
                cin >> bobot;
                addEdge(G, kota1, kota2, bobot);
                iteration++;
            }
            break;
        case 3:
            cout << "=================DAFTAR KOTA==================" << endl;
            printGraph(G);
            break;
        case 4:
            cout << "==============SIRKUIT TERPENDEK===============" << endl;
            if (start(G) != nil) {
                sirkuitTerpendek(G, result, bobot,temp);
            } else {
                cout << "Graph Kosong" << endl;
            }
            break;
        default :
            cout << "Mohon Inputkan Pilihan dari 0-4" << endl;
            pilihan = menu();
            break;
        }
        backToMenu(pilihan);
    }

    return 0;
}
