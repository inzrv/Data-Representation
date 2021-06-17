//очередь на массиве. ограниченная
#include <iostream>
using namespace std;
enum{
    NS = 100,
    AS = 100
};

struct ad{ //один адрес
    char name[NS]; //длина строки для имени адресата
    char address[AS]; //длина строки для адреса
    ad(){strcpy(name, "none"); strcpy(address, "none");} //конструктор по умолчанию
    ad(const char n[], const char a[]){strcpy(name, n); strcpy(address, a);} //конструктор по строкам
    ad(const char e[]){strcpy(name, e); strcpy(address, e);}; //конструктор для фиктивного элемента
};

typedef int  position;

ad error_element("error");

class queue{
public:
    int empty(); //проверка на пустоту
    int full(); //проверка на полноту
    void makenull(); //подготовка очереди к работе
    void enqueue(ad x); //добавление в хвост //по ссылке?
    ad dequeue(); //извлечение объекта из головы очереди, возвращаем копию объекта
    ad front(); //возвращаем копию объекта из головы
    void print_queue(); //печать очереди
    
private:
    static const int Q_SIZE = 4; //размер массива
    ad array[Q_SIZE];
    int head; //указатель на голову
    int tail; //указатель на хвост
};

int queue::empty(){ //проверка очереди на пустоту
    return head == tail;
}

int queue::full(){
    return tail == Q_SIZE; //такая проверка? не берем остаток от деления на Q_SIZE?
}

void queue::makenull(){ //подготовка очереди к работе
    head = 0;
    tail = 0;
}

void queue::enqueue(ad x){ //добавление в хвост
    if (!full()){
        array[tail] = x;
        tail++;
    }
}

ad queue::dequeue(){ //извлечение объекта из начала (головы)
    if (!empty()){
        ad x = array[head];
        ad y; //создаем пустой элемент //можно убрать эти две строки
        array[head] = y; //можно убрать эти две строки
        head++;
        return x;
    }
    return error_element;
}

ad queue::front(){ //копия из головы
    if (!empty()){
        return array[head];
    }
    return error_element;
}

void queue::print_queue(){ //печать очереди
    if (empty()){
        cout<<"Очередь пуста"<<endl;
    }
    for(int i = 0; i < Q_SIZE; i++){
        cout<<i<<". "<<array[i].name<<" "<<array[i].address<<endl;
    }
    cout<<"head = "<<head<<endl;
    cout<<"tail = "<<tail<<endl;
}

int main() {
    queue q;
    q.makenull();
    ad a1("oleg","lensk");
    ad a2("nastya","penza");
    ad a3("vanya","spb");
    ad a4("nikolay", "lopatino");
    q.enqueue(a1);
    q.enqueue(a2);
    q.enqueue(a3);
    q.enqueue(a4);
    q.print_queue();
    cout<<endl;
    ad temp = q.dequeue();
    cout<<"Извлекли: "<<temp.name<<" "<<temp.address<<endl;
    cout<<endl;
    q.print_queue();
}
































