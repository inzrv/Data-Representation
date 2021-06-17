#include <iostream>
#include "list.cpp"
using namespace std;

using namespace List3; // какое пространство имен используем

class stack{
public:
    stack();
    void push(ad& x); //поместить x в стек //ссылку
    ad pop(); //извлекаем значение с вершины стека
    ad top();
    int full();
    int empty();
    void makenull();
    void print_stack();
private:
    list l;
};

stack::stack(){
    l.initialization();
}

void stack::makenull(){
    l.makenull(); // t = l.end()
}

void stack::push(ad& x){
    position f = l.first();
    l.insert(x, f);
}

void stack::print_stack(){
    if (empty())
        cout<<"Стек пуст"<<endl;
    l.printlist();
}

int stack::empty(){
    return l.first() == l.end();
}

int stack::full(){
    return 0;
}

ad stack::pop(){
    if (empty() == 0){
        ad temp = l.retrieve(l.first());
        position p = l.first();
        l.delete_from_pos(p);
        return temp;
    }
    return error_element.object;
}

ad stack::top(){
    if (!empty()){
        return l.retrieve(l.first());
    }
    return error_element.object;
}


int main() {
    stack s;
    s.makenull();
    ad a1("alena", "penza");
    ad a2("diana", "msk");
    ad a3("oleg","lensk");
    s.push(a1);
    s.push(a2);
    s.push(a3);
    s.print_stack();
    s.pop();
    s.top();
    cout<<endl;
    s.print_stack();
}














