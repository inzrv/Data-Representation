#include <iostream>
#include "list.cpp"
using namespace std;

using namespace List4; // какое пространство имен используем

typedef char* domaintype;
typedef char* rangetype;


class mapping{
public:
    mapping();
    void makenull(); //делаем отображение пустым
    void assign(const domaintype d, const rangetype r); //получили имя человека d, добавили пару или заменили
    bool compute(const domaintype d, rangetype r);
    void print_mapping();
private:
    position search(const domaintype d); //по строке имени ищем позицию элемента в списке
    list l;
    
};

mapping::mapping(){
    l.initialization();
}

void mapping::makenull(){ //делаем отображение пустым
    l.makenull();
}

position mapping::search(const domaintype d){
    position x = l.first();
    while(x != l.end()){
        if (strcmp(l.retrieve(x).name,d) == 0) //если имя адресанта == искомому
            return x; // возвращаем позицию элемента
        x = l.next(x); //иначе ищем дальше
    }
    return x; //возвращаем l.end() если не нашли
}

void mapping::assign(const domaintype d, const rangetype r){
    position x = search(d); //ищем элемент - пару с ключом d
    if (x == l.end()){ //если ключа d в отображении нет, то создаем элемент и добавляем его в отображение
        ad temp(d,r);
        position f = l.first();
        l.insert(temp, f); //добавляем в начало
    }
    else{ //если нашли элемент-пару с ключем d
        l.delete_from_pos(x); //удаляем старую пару
        ad temp(d,r);
        l.insert(temp, l.first()); //добавляем новую
    }
}

bool mapping::compute(const domaintype d, rangetype r){
    position x = search(d);
    if (x == l.end())
        return false;
    strcpy(r,l.retrieve(x).address); //? так???
    return true;
}

void mapping::print_mapping(){
    if (l.first() == l.end()){
        cout<<"Отображение пусто"<<endl;
        return;
    }
    
    l.printlist();
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
    m.assign(masha, pnz);
    m.print_mapping();
    cout<<endl;
    char r[AS] = "";
    m.compute(dasha, r);
    cout<<r<<endl;
    m.makenull();
    m.print_mapping();
}












