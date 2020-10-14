//Program untk mencari jalan tercepat untuk keluar dari maze
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
char mp[20][20]; //maze untuk mencari jalan dan waktu terpendek
char sol[20][20]; //maze solusi untuk mendapatkan jalur tercepat
int T[100]; //array untuk menyimpan waktu yang dibutuhkan
int k=0; //sebagai counter index array untuk menyimpan waktu
//rekursi untuk mendapatkan waktu terpendek menuju titik tujuan
void sj(int n, int i, int j, int x2, int y2, int time)
{
 if(i==x2&&j==y2)
 {
 T[k]=time; //masukkan semua kemungkinan waktu ke dalam array
 k++;
 }
 else
 {
 mp[i][j]='#';
 time++;
 // cek area sekitar
 if (mp[i-1][j]!='#'&&i-1>0)sj(n,i-1,j,x2,y2,time);
 if (mp[i+ 1][j]!='#'&&i+1<=n)sj(n,i+1,j,x2,y2,time);
 if (mp[i][j-1]!='#'&&j-1>0)sj(n,i,j-1,x2,y2,time);
 if (mp[i][j+1]!='#'&&j+1<=n)sj(n,i,j+1,x2,y2,time);
 }
}
//rekursi untuk mendapatkan lintasan dari waktu minimum
bool change(int n, int i, int j, int x2, int y2, int time, int mintime)
{
 // cek jika telah mencapai titik yang dituju
 if(i==x2&&j==y2&&time==mintime)
 {
 sol[i][j] = '1'; //ubah titik tujuan menjadi '1'
 return true;
 }

 // Cek apakah belum melewati waktu minimum
 if(time<=mintime)
 { 
 time++; //increment waktu agar dapat dibadingkan dengan waktu minimum
 // cek area sekitar dan ubah jalur yang benar menjadi '1'
 if (sol[i-1][j]!='#'&&i-1>0&&change(n,i-1,j,x2,y2,time,mintime))
 {
 sol[i][j] = '1';
 return true;
 }
 if (sol[i+1][j]!='#'&&i+1<=n&&change(n,i+1,j,x2,y2,time,mintime))
 {
 sol[i][j] = '1';
 return true;
 }
 if (sol[i][j-1]!='#'&&j-1>0&&change(n,i,j-1,x2,y2,time,mintime))
 { sol[i][j] = '1';
 return true;
 }
 if
(sol[i][j+1]!='#'&&j+1<=n&&change(n,i,j+1,x2,y2,time,mintime))
 {
 sol[i][j] = '1';
 return true;
 }

 // Backtrack arah lain yang tidak mencapai tujuan sesuai waktu minimum
 sol[i][j]='.';
 return false;
 }
 return false;
}
//Fungsi untuk Print array
void print(int n)
{
 for(int i=1;i<=n;i++)
 {
 for(int j=1;j<=n;j++)
 {
 cout<<sol[i][j]; //output maze solusi
 }
 cout<<endl;
 }
}

int main()
{
 int n,x1,x2,y1,y2,time=0; //n untuk panjang dan lebar maze, x1 titik x asal, x2 titik x tujuan,
 cin>>n; // y1 titik y asal, y2 titik y tujuan, time untuk waktu tempuh.
 if(n<30)//error trapping agar maze yang diinput tidak terlalu besar
 {
 memset(mp,0,sizeof (mp));
 memset(sol,0,sizeof (sol)); //set semua maze agar bernilai default (0)
 for(int i=1;i<=n;i++)
 {
 for(int j=1;j<=n;j++)
 {
 cin>>mp[i][j]; //inputkan maze
 }
 }
 copy (mp,mp+n*n,sol);
 cin>>x1>>y1>>x2>>y2; //inputkan titik awal dan titik tujuan
 sj(n,x1+1,y1+1,x2+1,y2+1,time); //cari waktu dari semua kemungkinan menuju tujuan
 sort(T,T+k); //sort untuk mendapatkan waktu tercepat
 time=0;
 int mintime=T[0];
 change(n,x1+1,y1+1,x2+1,y2+1,time,mintime); //ubah maze solusi agar menunjukkan jalan tercepat
 print(n);
 }

 return 0;
} 
