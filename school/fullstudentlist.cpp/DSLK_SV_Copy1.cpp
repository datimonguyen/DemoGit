#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unordered_set>
#include "mylib.h"
using namespace std;
 
struct Sinhvien {
  int maso; 
  char ho [51];
  char ten[11];
  float dtb;
  int hang;
   
 };

 struct node {
  Sinhvien sv;
  node *next;
};
typedef  node* PTR;

//const int MAXLIST =100;

const int so_item = 16;
const int dong =5;
const int cot = 40 ;
char thucdon [so_item][100] = {"1. Nhap danh sach sinh vien         ",
			                  "2. Liet ke danh sach                ",
			                  "3. Them ve dau danh sach            ",
			                  "4. Them sv o vi tri i               ",
			                  "5. Xoa sinh vien theo ma so         ",
			                  "6. Them 1 sv vao danh sach co thu tu",
			                  "7. Loc SV trung theo ten            ",
			                  "8. Sap xep dssv theo ma so tang dan ",
							  "9. Save DSSV                        ", 
							  "10.Load DSSV                        ",
							  "11.Xep hang theo DTB                ",
							  "12.Xoa sinh vien theo ten           ",
							  "13.Dao nguoc danh sach              ",
							  "14.Copy danh sach                   ",
							  "15. In DSSV tang dan theo ten (giu nguyen ds)",
							  "16.Ket thuc chuong trinh            "};





int Insert_After(PTR p, Sinhvien x)   { // them vao cuoi
   PTR q;
   if(p == NULL)		return 0;
      q =new node;
      q->sv = x;
      q->next = p->next ;
      p->next = q;
   return 1;
}
int Delete_First (PTR  &First) { // xoa o dau
	PTR p;
    if (First == NULL)      return 0;
    p = First;    // nut can xoa la nut dau
    First = p->next;
    delete p; 
    return 1;
}
int Menu (char td [so_item][100]) { // show menu
	system("cls");   int chon =0;
	int i;
	for ( i=0; i< so_item ; i++)
	{ gotoxy(cot, dong +i);
		cout << td[i];
	}
	Nhaplai:
	gotoxy (cot, dong + so_item);
	cout << "Ban chon 1 so (1.."<< so_item << ") :    ";
	gotoxy (wherex()-4, wherey());
	cin >> chon;
	if (chon <1 || chon >so_item) goto Nhaplai;
	return chon;

}
void BaoLoi (const char *s){
  int x=wherex() , y=wherey();
  gotoxy (10,24);
  cout <<s;
  Sleep(2000);
  gotoxy(10,24);
  clreol();
  gotoxy(x,y);
}
PTR Search(PTR First, int x) { // tra ve sinh vien co ms trung vs x
	for (PTR p = First;  p  != NULL ; p=p->next )
              if ( p->sv.maso == x  ) return p;
	return NULL;
}
int NhapSV(PTR First , Sinhvien &sv){
 NhaplaiMaSV:
		cout << "\nMa so sinh vien (<=0 dung nhap):" ;
		cin >> sv.maso ;
		if (sv.maso <=0 ) return 0;
		if (Search (First, sv.maso)!= NULL)  {
			BaoLoi( "Ma so sinh vien bi trung. Ban nhap lai. ");
			goto NhaplaiMaSV;
		}
		cin.ignore();
		cout << "Ho sinh vien  :" ; cin.getline(sv.ho, 51);
		cout << "Ten sinh vien :" ; cin.getline(sv.ten, 11);
		cout << "Diem TB :" ; cin >>sv.dtb;
		sv.hang =0;
		return 1;
}
void Insert_First(PTR &First,Sinhvien &sv){
        PTR p = new node ;
		p->sv = sv ; 
		p->next=First;
		First = p;
}
void NhapSV_VeDau (PTR &First) {
	system ("cls");
	PTR p ; Sinhvien sv; int err;
	while (1) {
		err=NhapSV(First, sv) ;
		if (err==0) return;
		Insert_First(First,sv);
   }
}
void Nhap_DSSV (PTR &First) { // them ve cuoi
	system ("cls");
	PTR p, Last ; Sinhvien sv; int err;
    if(First !=NULL)
       for (Last = First ; Last->next !=NULL; Last=Last->next) ;
       
	while (true) {
		err=NhapSV(First, sv) ;
		if (err==0) return;
	 
		p = new node ;
		p->sv = sv ; p->next=NULL;
		if (First==NULL) First = p;
		else Last -> next = p;
		Last = p;
   }
}
void LietKe (PTR First) { // show danh sach sv
	int dem =0 ; system ("cls");
	printf ("MaSV        Ho              Ten      DTB     Hang\n");
	for (PTR p = First ; p !=NULL; p=p->next)
	{	printf ("%5d %-20s %-10s %.1f %5d\n",
	       p->sv.maso , p->sv.ho, p->sv.ten, p->sv.dtb, p->sv.hang );
		dem ++;
	
	}
	cout << "\nSo luong Sv =" <<dem;
	getch();
}
int Reccount (PTR First) { // so luong sinh vien
	int dem =0 ;  
	for (PTR p = First ; p !=NULL; p=p->next)
		dem ++;
	return dem;
}
int SaveFile (PTR First, char *tenfile) { // luu file
	FILE *f = fopen (tenfile, "wb");
	if (f==NULL) return 0;
	for (PTR p=First ; p!=NULL ; p=p->next)
	  fwrite (&p->sv, sizeof (Sinhvien), 1, f);
	fclose (f);
	return 1;  
}
void InsertLast (PTR &First , Sinhvien sv) { // them vao cuoi
	    PTR p = new node ;
		p->sv = sv ; p->next=NULL;
		if (First==NULL) First = p;
		else { PTR Last;
		       for (Last = First;Last->next !=NULL; Last=Last->next) ;		
		       Last->next = p;
		     }
}
int OpenFile (PTR &First, char *tenfile) { // mo file
	PTR p;  Sinhvien sv ;
	FILE *f = fopen (tenfile, "rb");
	if (f==NULL) return 0; // mo file khong duoc
	
	while (First!= NULL) {
		p= First ; First = p->next ; delete p ;
	}
	while  (fread (&sv, sizeof (Sinhvien), 1, f)== 1 ) 
	   InsertLast (First , sv); 
	fclose (f);
	return 1;  
}
bool XacNhan (char *S) {
	cout << S;  char kt;
	do {
	   kt = toupper(getch());	
	} while (kt!='Y' && kt !='N');
	cout <<kt  ;
	return kt=='Y';
}
void Insert_Order(PTR &First, Sinhvien x) {
   PTR p, t, s;  // t la nut truoc, s la nut sau
   p=new node;
   p->sv=x;
   for(s = First; s != NULL && s->sv.maso < x.maso  ; t=s, s = s->next)   ;
   if(s == First)  // them nut vao dau danh sach lien ket
   {
      p->next = First;
      First = p;
   }
   else           // them nut p vao truoc nut s
   {
      p->next= s;
      t->next= p;
   }
}
int  Delete_after(PTR p) {   
	PTR q;
	if((p == NULL) || (p->next == NULL))	
	return 0;
	q = p->next;  // q chi nut can xoa
	p->next = q->next;
	delete q;
	return 1;
}
int Xoa_SV_theo_Masv(PTR &First, int MS) { // xóa sinh viên theo MS
	if (Search(First, MS) == NULL) return 0;
	if (First->sv.maso == MS) {
		Delete_First(First);
		return 1;
	}
	PTR p = First;
	PTR q = p->next;
	while (q != NULL) {
		if (q->sv.maso == MS) {
			PTR temp = q;
			q = q->next;
			p->next = q;
			delete temp;
			return 1;
		}
		p = p->next;
		q = q->next;
	}
	return 0;
}
int XoatheotenSV(PTR &First, const char tensv[]) { // xóa sinh viên theo tên
	if (First == NULL) return 0;
	char temp[63];
	strcpy(temp, First->sv.ho);
	strcat(temp, " ");
	strcat(temp, First->sv.ten);
	if (strcmp(tensv, temp) == 0) {
		Delete_First(First);
		return 1;
	}
	PTR p = First;
	PTR q = p->next;
	while (q != NULL) {
		char temp[63];
		strcpy(temp, q->sv.ho);
		strcat(temp, " ");
		strcat(temp, q->sv.ten);
		if (strcmp(tensv, temp) == 0) {
			PTR tempt = q;
			q = q->next;
			p->next = q;
			delete tempt;
			return 1;
		}
		p = p->next;
		q = q->next;
	}
	return 0;
}
void xepHang(PTR First) { // xếp hạng sinh viên theo điểm số 
	PTR current = First;
	while (current != NULL){
		int hang = 1;
		PTR compare = First;
		while (compare != NULL) {
			if (compare != current && compare->sv.dtb > current->sv.dtb) 
				hang++;
			compare = compare->next;
		}
		current->sv.hang = hang;
		current = current->next;
	}
}
PTR filter(PTR First) {
	unordered_set <string> hash;
	string ho(First->sv.ho);
	string ten(First->sv.ten);
	string hoten = ho + " " + ten;
	hash.insert(hoten);
	PTR current = First;
	while (current->next != NULL) {
		string ho(current->next->sv.ho);
		string ten(current->next->sv.ten);
		string hoten = ho + " " + ten;
		if (hash.find(hoten) != hash.end()) {
			PTR temp = current->next;
			current->next = temp->next;
			delete temp;
		} else {
			hash.insert(hoten);
			current = current->next;
		}
	}
	return First;
}





int main (){
  char filename[80]="D:\\DSSV_DTB.TXT"; int x;
  char tensv[16];
   int so;int chon;  
  PTR head; PTR First=NULL;   PTR First1=NULL, First2=NULL;
  int i ; Sinhvien sv; int maso;
  do
  {
    chon = Menu (thucdon);
    switch (chon ){
    case 1: cin.ignore(); Nhap_DSSV(First) ; break;
    case 2: LietKe(First) ; break;
    case 3: printf("So luong sinh vien =%d", Reccount(First));
    		getch();
    		break;
	case 4:{
			NhapSV(First, sv);
			Insert_Order(First, sv);
			break; 
            }
    case 5: {
		
	        cout << "Ma so SV muon xoa :" ; cin >> maso;
            int err= Xoa_SV_theo_Masv (First, maso);
            if (err==1)
              BaoLoi("Da xoa sinh vien co ma so trong DSSV.");
            else BaoLoi ("Ma so SV khong co trong danh sach."); 
			break;
		}
         
    case 7: {	
	         head= filter(First) ;
	         for (PTR i=head;i!=NULL;i=i->next) 
		       printf ("%-10s ",  i->sv.ten );
			getch();
            break;
        }

    case 8: SapXepTangTheoTenVaHo(First ); 
            BaoLoi("Da sap xep xong DSSV theo ten+ho tang dan"); 
	        break;
    case 9: system ("cls");
	        if (SaveFile(First, filename)==0) cout << "Loi mo file de ghi ";
	        else cout << "Da ghi xong danh sach sinh vien vao file.";
	        Sleep(2000);
	        break;

    case 10:  system ("cls");
	        if (OpenFile(First, filename)==0) cout << "Loi mo file de doc ";
	        else cout << "Da doc xong danh sach sinh vien tu file.";
	        Sleep(2000);
	        break; 

	case 11: { system ("cls");
			xepHang(First);
	        break;  
	        }
	case 12: { 
	        system ("cls");
	        cout << "Ten SV muon xoa :" ; cin.ignore(); cin.getline(tensv, 16);
	        cout << "So SV da xoa =" << XoatheotenSV(First,tensv); 
			getch(); 
	        break;	
	    }
/*
	case 13: {
	 
	         reverseLinkedList(First);
	         cout << "Da dao nguoc danh sach xong"; getch(); 
            break;
	        }

	case 14: {
		    First2= SaoChepDanhSach(First) ;
		    LietKe(First2);
	        break;   
			}  
	   
		case 15: {
	 
	         InDSSVTangTheoTen(First);
	         break;
	        }
	*/
    case so_item : { // clearlist(First); clearlist(First2); 
	                 return 0; 
                   }
  } 
} while (1);
  
  return 0;
  }			 
