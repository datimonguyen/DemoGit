#include<iostream>
#include<string>
using namespace std;

struct Student{
    int id;
    string name;
    float score;
    int rank;
    string surname;
};

struct Node{
    Student st;
    Node* next ;
};
typedef Node* PTR;
int count  =0;

const int ItemQuanity = 16;

char Menu [ItemQuanity][50] {"1. Nhap danh sach sinh vien         ",
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

void RakingStudent(PTR &head){
    for(PTR p = head; p != NULL ; p = p->next){
        int hang = 1;
        for ( PTR j = head ; j != NULL ; j = j ->next){
            if (p->st.score < j->st.score){
                hang++;
            }
        }
        p->st.rank = hang;
    }
}

void Reverse(PTR &head){
    PTR temp1 = NULL;
    PTR prev = head;
    while ( prev != NULL){
        PTR temp2 = prev ->next;
        prev->next = temp1;
        temp1  = prev;
        prev = temp2;   
    }
    head = temp1;
}

// xóa sinh viên theo tên
void RemoveStudentByName(PTR &head, string name ,string surname){
    if(head != NULL && name == head->st.name && surname == head->st.surname ){
        PTR temp = head;
        head = temp ->next;
        delete temp;
    }
    PTR prev = head;
    while(prev != NULL && prev->next != NULL){
        if(prev->next->st.name == name && prev->next->st.surname == surname){
            PTR temp = prev->next;
            prev->next = temp ->next;
            delete temp;
        }
        else {
            prev = prev ->next;
        }
    }
}

// loại tên bị trùng nhau
void FilterTheSameName(PTR &head){
    for(PTR p = head ; p != NULL ; p= p->next){
        for (PTR j = p ; j->next != NULL;){
            if(p->st.name == j->next->st.name && p->st.surname == j->next->st.surname ){ // trùng tên thì xóa, xóa xong thì cái tiếp theo đã thục vào không cần chuyển tới cái tiếp
                PTR temp = j ->next;
                j->next = temp->next;
                delete temp;
            }
            else {
                j = j ->next; // nếu không giống thì sẽ chuyển cái tiếp theo  
            }
        }        
    }
}

//sắp xếp theo ID
void SortingStudentByID(PTR &head) {
    if (head == NULL || head->next == NULL) return; // danh sách rỗng hoặc chỉ có 1 node

    bool swapped;
    do {
        swapped = false;
        PTR a = head;
        while (a->next != NULL) {           
            if (a->st.id > a->next->st.id) {
                Student temp = a->st;
                a->st = a->next->st;
                a->next->st = temp;
                swapped = true;
            }
            a = a->next;
        }
    } while (swapped); // lặp lại cho đến khi không còn đổi chỗ
}

int strcmp(const char *str1, const char *str2){
    int i = 0;
    while ( str1[i] == '\0' && str2[i] == '\0' ){
        if (str1[i] != str2[i]){
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}      

void SortByName(PTR &head){ 
    for ( PTR p = head; p != NULL; p = p->next){
        for( PTR j = p->next; j != NULL; j=j->next){
            if (p->st.name == j->st.name){
                if (strcmp(p->st.surname.c_str(),j->st.surname.c_str())){
                    Student temp = p->st;
                    p->st = j->st;
                    j->st = temp;
                }    
            }else if (strcmp(p->st.name.c_str(),j->st.name.c_str()) > 0){
                Student temp = p->st;
                p->st = j->st;
                j->st = temp;
            }
        }
    }
}

// In cái danh sách ra
void PrintTheList(PTR  &head){
    int count = 0;
    for (PTR p = head; p != NULL; p = p->next){
        cout << p->st.id << " | "
             << p->st.surname << " | "
             << p->st.name << " | "
             << p->st.score << " | "
             << "Rank: " << p->st.rank<<endl; 
        count ++;
    }
    cout << "Counting: " << count << " students "<< endl;}

// kiểm tra coi ID có bị trùng không
PTR CheckID(PTR FRIST , int x){
    for (PTR p = FRIST ; p != NULL ; p = p -> next){
        if( p->st.id == x ){return p;}
    }
    return NULL;
}

//nhập sinh viên vào đầu danh sách 
void AddingOnHeadList( PTR  &head, Student data ){
    PTR newnode = new Node;
    newnode ->st = data;
    newnode -> next = head;
    head = newnode;
}

void AddingOnList (PTR &head , Student data){
    PTR newnode = new Node;
    newnode ->st = data;
    newnode ->next = NULL;
    if (head == NULL){
        head = newnode;
    }
    else{
        PTR temp = head;
        while ( temp->next != NULL ){
            temp = temp ->next;
        }
        temp ->next = newnode;
    }
}

bool InputStudent(PTR head, Student &st) {
    cout << " - Enter your ID (enter <=0 to exit): ";
    cin >> st.id;
    if (st.id <= 0) return false;
    if (CheckID(head, st.id) != NULL) {
        cout << " This ID has already been taken !!!" << endl;
        return false; // báo nhập sai, không thêm
    }
    cout << " - Enter your surname: ";
    cin.ignore();
    getline(cin, st.surname);
    cout << " - Enter your name: ";
    getline(cin, st.name);
    cout << " - Enter your score: ";
    cin >> st.score;
    st.rank = 0;
    return true;
}

//nhập học sinh vào giữa danh sách
void AddStudentSelectedPlace(PTR &head, int place, Student data){
    PTR newnode= new Node;
    newnode->st = data;
    newnode->next = NULL;
    if (place < 0){cout << " Invalid place to put !!! " <<endl; }
    if (place == 0){
        newnode->next = head;
        head = newnode;
    }
    PTR prev = head;
    while (  (place-1)> 0  && prev != NULL && prev->next !=NULL){
        prev = prev->next;
        place --;
    }
    newnode -> next = prev -> next;
    prev -> next = newnode;
}

void AddingOnASorted(PTR &head ,int id ,Student data ){  //  5 7 8 10
    PTR newnode = new Node;                              //      9 10
    newnode ->st = data;
    newnode -> next = NULL;

    if(head != NULL && head->st.id > id ){
        newnode -> next = head;
        head = newnode;
    }
    PTR prev = head;
    while (prev -> next != NULL &&  prev->next->st.id < id ){
        prev = prev -> next;
    }
    newnode -> next = prev -> next;
    prev -> next = newnode;
}

void InsertTheStudent1(PTR &head) {
    Student st;
    while (InputStudent(head, st)) {
        AddingOnList(head, st);
    }
}

// thêm vào đầu
void InsertTheStudent3(PTR &head) {
    Student st;
    while (InputStudent(head, st)) {
        AddingOnHeadList(head, st);
    }
}

// thêm tại vị trí bất kỳ
void InsertTheStudent4(PTR &head, int place) {
    Student st;
    while (InputStudent(head, st)) {
        AddStudentSelectedPlace(head, place, st);
    }
}

// thêm theo thứ tự ID tăng dần
void InsertTheStudent6(PTR &head) {
    Student st;
    while (InputStudent(head, st)) {
        AddingOnASorted(head, st.id, st);
    }
}

// xóa học học sinh theo ID
void RemoveStudentByID(PTR &head, int selectedid){
    if ( head == NULL){return;}
    while (head != NULL && head ->st.id == selectedid){
        PTR temp = head;
        head = head->next;
        delete temp;
    }
    PTR prev = head;
    while (prev != NULL && prev ->next !=NULL ){
        if (prev ->next ->st.id == selectedid )
        {
            PTR temp = prev ->next;
            prev ->next = temp->next; 
            delete temp;
        }
        else{
            prev = prev ->next;
        }
    }
}

int SaveFile (PTR First, char *tenfile) {
	FILE *f = fopen (tenfile, "wb");
	if (f==NULL) return 0;
	for (PTR p=First ; p!=NULL ; p=p->next)
	  fwrite (&p->st, sizeof (Student), 1, f);
	fclose (f);
	return 1;  
}

int OpenFile (PTR &First, char *tenfile) {
	PTR p;  Student st ;
	FILE *f = fopen (tenfile, "rb");
	if (f==NULL) return 0; // mo file khong duoc
	
	while (First!= NULL) {
		p= First ; First = p->next ; delete p ;
	}
	while  (fread (&st, sizeof (Student), 1, f)== 1 ) 
	   AddingOnList (First , st); 
	fclose (f);
	return 1;  
}

// Thể hiện MENU
void ShowMenu( char li [ItemQuanity][50]  ){
    cout << " ===== THE MENU =====" <<endl;
    for( int i = 0; i < ItemQuanity ; i++){
        cout<<  li[i] <<  endl;
    }
}

int main(){
    Student st;
    int choice;
    PTR head = NULL;
    char filename[80]="D:\\DSSV_DTB.TXT";int x;
    do{
        ShowMenu(Menu);
        cout << " - Choose a number (1-16): ";
        cin >> choice;
        switch (choice)
        {
        case 1:{
            InsertTheStudent1(head);
            break;}
        case 2:{
            PrintTheList(head);
            break;}
        case 3:{
            InsertTheStudent3(head);
            }
            break;
        case 4:{
            int place;
            cout << " - Enter the place to add: " ;
            cin >> place ;
            InsertTheStudent4(head, place );
            break;
        }
            break;
        case 5:{
            int selectedid;
            cout << " - Enter the ID: ";
            cin>> selectedid;
            RemoveStudentByID(head,selectedid);
            break;
        }
        case 6:
            {
            int id;
            cout << " - Enter the ID: ";
            cin>> id;
            InsertTheStudent6(head);
            break;
        }
        case 7: {
            FilterTheSameName(head);
            break;}
        case 8:{
            SortingStudentByID(head);
            break;}
        case 9:
            {
            if (SaveFile(head, filename)==0) cout << "Loi mo file de ghi ";
	        else cout << "Da ghi xong danh sasch sinh vien vao file.";
            break;
        }
  
        case 10:
            {
            if (OpenFile(head, filename)==0) cout << "Loi mo file de doc ";
	        else cout << "Da doc xong danh sasch sinh vien tu file.";    

            }
            break;
        case 11:
            {RakingStudent(head);}
            break;
        case 12:{
            string selectedname, surname;
            cout<< " - Enter the surname: ";
            cin >> surname;
            cout<< " - Enter the name: ";
            cin >>selectedname;
            
            RemoveStudentByName(head,selectedname ,surname) ;
            break;}
        case 13:
            {Reverse(head);}
            break;
        case 14:
            {}
            break;
        case 15:
            {
                SortByName(head);
                break;
            }

        default:
            break;
        }
    }while ( choice != 16);
}