#include <iostream>
using namespace std;
enum{
    NS = 100,
    AS = 100
};

typedef char* domaintype;
typedef char* rangetype;

struct node{
    char name[NS]; //имя человека
    char address[AS]; //адрес проживания
    node* next;
    node();
    node(domaintype d, rangetype r, node* nxt = NULL); //конструктор по имени и адресу
};

node::node(){
    strcpy(name, "none");
    strcpy(address, "none");
}

node::node(domaintype d, rangetype r, node* nxt){
    strcpy(name, d);
    strcpy(address, r);
    next = nxt;
}

class mapping{ //класс отображения
public:
    mapping(); //конструктор по умолчанию
    ~mapping(); //деструктор
    void makenull(); //делает отображение пустым
    void assign(domaintype d, rangetype r); //создание пары или замена
    bool compute(domaintype d, rangetype r); //считаем m(d)
    void print_mapping(); //печать всего отображения
private:
    node* head; //указатель на голову списка
    void delete_mapping(); //удаление отображения
    node* search(domaintype d); //поиск пары по ключу d
    void print_pair(node*);//печать пары
};

mapping:: mapping(){ //конструктор по умолчанию
    head = NULL;
}

void mapping::delete_mapping(){ //удаление отображения
    node* x = head;
    node* y = x;
    while (x != NULL){
        y = x;
        x = x->next;
        delete [] y;
    }
}

mapping::~mapping(){ //деструктор
    if (head !=  NULL)
        delete_mapping();
}

void mapping::makenull(){ //делает отображение пустым
    delete_mapping();
    head = NULL;
}

node* mapping::search(domaintype d){ //поиск пары по ключу d, возвращаем указатель на нод или NULL
    node* x = head;
    while (x != NULL){
        if (strcmp(x->name,d) == 0){ //если нашли совпадение по имени
            return x; //возвращаем адрес узла
        }
        x = x->next;
    }
    return NULL; //не нашли, вернули NULL
}

void mapping::assign(domaintype d, rangetype r){ //создание пары или замена
    node* x = search(d); //ищем пару с таким ключем
    if (x == NULL){ //если пары с таким ключем нет, добавляем в начало пару
        node* temp = new node(d,r,head); //имя = d, адрес =r, указывает на head;
        head = temp; //новая голова
    }
    else{ //если нашли такую пару
        strcpy(x->address, r); //меняем адрес
    }
}

bool mapping::compute(domaintype d, rangetype r){
    node* x = search(d); //ищем пару
    if (x == NULL)
        return false;
    else{
        strcpy(r, x->address);
        return true;
    }
}

void mapping::print_pair(node* x){
    cout<<"Name: "<<x->name<<" address: "<<x->address<<endl;
}

void mapping::print_mapping(){
    node* x = head;
    if (x == NULL)
        cout<<"Отображение пусто"<<endl;
    else{
        int i = 0;
        while (x != NULL) {
            cout<<i++<<". ";
            print_pair(x);
            x = x->next;
        }
    }
}

int main(){
    mapping m;
    m.makenull();
    char masha[NS] = "masha";
    char dasha[NS] = "dasha";
    char sasha[NS] = "sasha";
    char msk[AS] = "msk";
    char spb[AS] = "spb";
    char pnz[AS] = "pnz";
    char ekb[AS] = "ekb";
    m.assign(masha, spb);
    m.assign(dasha, msk);
    m.assign(sasha, ekb);
    m.print_mapping();
    cout<<endl;
    char temp[AS]="";
    m.compute(masha, temp);
    cout<<temp<<endl;
    m.assign(masha, pnz);
    cout<<endl;
    m.print_mapping();
}











