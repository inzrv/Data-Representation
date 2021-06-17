#include <iostream>
#include "list.cpp"
using namespace std;

using namespace List2; // какое пространство имен используем

class queue{ //класс очередь
public:
    queue();
    void makenull(); //подготовка к работе, делает список пустым
    int empty(); //проверка на пустоту
    int full(); //проверка на полноту (всегда 0)
    void enqueue(ad x); //вставка элемента в конец очереди
    void print_queue(); //печать очереди
    ad dequeue(); //удаление элемента из головы
    ad front(); //возвращает копию элемента с головы
private:
    list l;
};

queue::queue(){
    l.initialization();
}

void queue::makenull(){
    l.makenull();
}
int queue::empty(){ //проверка на пустоту
    return l.first() == l.end(); //во всех списках end() указатель на позицию после последнего (например NULL)
}

int queue::full(){ //проверка на полноту (всегда 0)
    return 0;
}

void queue::enqueue(ad x){ //вставка элемента в конец очереди
    position e = l.end();
    l.insert(x, e);
}

ad queue::dequeue(){ //удаление элемента из головы
    if(!empty()){
        ad temp = l.retrieve(l.first());
        position f = l.first();
        l.delete_from_pos(f);
        return temp;
    }
    return error_element.object;
}

ad queue::front(){ //возвращаем копию головы
    if (!empty()){
        return l.retrieve(l.first());
    }
    return error_element.object;
}

void queue::print_queue(){ //печать очереди
    if (empty())
        cout<<"Очередь пуста"<<endl;
    else
        l.printlist();
}


int main(){
    queue q;
    q.makenull();
    q.print_queue();
    ad a1("nastya","penza");
    ad a2("katya","saratov");
    q.enqueue(a1);
    q.enqueue(a2);
    q.print_queue();
    cout<<endl;
    ad x = q.dequeue();
    cout<<x.name<<" "<<x.address<<endl;
    cout<<endl;
    q.print_queue();
    q.dequeue();
    q.print_queue();
}
























