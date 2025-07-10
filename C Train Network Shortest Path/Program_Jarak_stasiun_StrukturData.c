#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
// Definisi struktur data untuk graf
typedef struct Jalur {
int tujuan;
int bobot;
struct Jalur* berikutnya;
} Jalur;
typedef struct Stasiun {
int idStasiun;
Jalur* jalur;
struct Stasiun* berikutnya;
} Stasiun;
typedef struct Graf {
Stasiun* kepala;
} Graf;
// Fungsi untuk menambahkan stasiun ke graf
void tambahStasiun(Graf* graf, int idStasiun) {
Stasiun* stasiunBaru =
(Stasiun*)malloc(sizeof(Stasiun));
stasiunBaru->idStasiun = idStasiun;
stasiunBaru->jalur = NULL;
stasiunBaru->berikutnya = graf->kepala;
graf->kepala = stasiunBaru;
}
// Fungsi untuk menambahkan jalur ke graf
void tambahJalur(Graf* graf, int asal, int tujuan, int
bobot) {
Stasiun* stasiunAsal = graf->kepala;
while (stasiunAsal != NULL && stasiunAsal->idStasiun !=
asal) {
stasiunAsal = stasiunAsal->berikutnya;
}
if (stasiunAsal == NULL) return;
Jalur* jalurBaru = (Jalur*)malloc(sizeof(Jalur));
jalurBaru->tujuan = tujuan;
jalurBaru->bobot = bobot;
jalurBaru->berikutnya = stasiunAsal->jalur;
stasiunAsal->jalur = jalurBaru;
}
// Fungsi untuk menemukan stasiun dengan jarak minimum yang belum dikunjungi
int jarakMinimum(int jarak[], bool setSPT[], int V) {
int min = INT_MAX, indeksMin;
for (int v = 0; v < V; v++)
if (setSPT[v] == false && jarak[v] <= min)
min = jarak[v], indeksMin = v;
return indeksMin;
}
// Implementasi Algoritma Dijkstra
void dijkstra(Graf* graf, int asal, int V) {
int jarak[V];
bool setSPT[V];
for (int i = 0; i < V; i++) {
jarak[i] = INT_MAX;
setSPT[i] = false;
}
jarak[asal] = 0;
for (int count = 0; count < V - 1; count++) {
int u = jarakMinimum(jarak, setSPT, V);
setSPT[u] = true;
Stasiun* stasiunU = graf->kepala;
while (stasiunU != NULL && stasiunU->idStasiun !=
u) {
stasiunU = stasiunU->berikutnya;
}
if (stasiunU == NULL) continue;
Jalur* e = stasiunU->jalur;
while (e != NULL) {
if (!setSPT[e->tujuan] && jarak[u] != INT_MAX
&&
jarak[u] + e->bobot < jarak[e->tujuan]) {
jarak[e->tujuan] = jarak[u] + e->bobot;
}
e = e->berikutnya;
}
}
printf("Stasiun \t Jarak dari Asal\n");
for (int i = 0; i < V; i++)
printf("%d \t\t %d\n", i, jarak[i]);
}
int main() {
int V = 6; // Jumlah stasiun
Graf* graf = (Graf*)malloc(sizeof(Graf));
graf->kepala = NULL;
// Menambahkan stasiun ke graf
for (int i = 0; i < V; i++) {
tambahStasiun(graf, i);
}
// Menambahkan jalur ke graf
tambahJalur(graf, 0, 1, 10);
tambahJalur(graf, 0, 4, 15);
tambahJalur(graf, 1, 2, 10);
tambahJalur(graf, 1, 4, 20);
tambahJalur(graf, 2, 3, 10);
tambahJalur(graf, 3, 4, 5);
tambahJalur(graf, 3, 5, 10);
tambahJalur(graf, 4, 5, 30);
// Menjalankan Algoritma Dijkstra dari stasiun 0
dijkstra(graf, 0, V);
// Membersihkan memori yang dialokasikan
Stasiun* tempStasiun;
while (graf->kepala != NULL) {
tempStasiun = graf->kepala;
graf->kepala = graf->kepala->berikutnya;
Jalur* tempJalur;
while (tempStasiun->jalur != NULL) {
tempJalur = tempStasiun->jalur;
tempStasiun->jalur =
tempStasiun->jalur->berikutnya;
free(tempJalur);
}
free(tempStasiun);
}
free(graf);
return 0;
}
