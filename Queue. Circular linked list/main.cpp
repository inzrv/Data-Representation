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
};

typedef int  position;

struct err_ad{
    ad object;
    position address;
    err_ad(); //конструктор для фиктивного элемента
};

err_ad error_element;

err_ad::err_ad():object("error","error"),address(-101){ //конструктор для фиктивного элемента
}

struct node{ //элемент = объект + адрес
    ad object; //объект (адрес адресата + имя адресата)
    node* next; // (указатель на следующий нод)
    node(); //конструктор по умолчанию
    node(const char n[], const char a[], node* nxt = NULL); //конструктор нода по адресу и имени
    node(node const &); //копия объекта
};

node::node():object("none","none"),next(NULL){ //конструктор нода по умолчанию
}

node::node(const char n[], const char a[], node* nxt):object(n,a),next(nxt){ //конструктор нода по адресу
}

node::node(node const &n){ //копирующий конструктор
    object  = n.object;
    next = n.next;
}


class queue{
public:
    queue();
    ~queue();
    int full(); //проверка на полноту, в этой реализации всегда 0
    int empty(); //проверка на пустоту
    void enqueue(ad x); //добавление элемента
    ad dequeue(); //извлечение объекта из очереди
    ad front(); //возвращает копию объекта в голове очереди
    void print_queue(); //печать очереди
    void makenull(); //делает очередь пустой
private:
    node* head; //указатель на голову
    node* tail; //указатель на хвост
};

queue::queue(){
    head = NULL;
    tail = NULL;
}

queue::~queue(){
    makenull();
}

void queue::makenull(){
    if (head != NULL){
        node* x = head;
        node* y = x;
        while (x != tail){
            y = x;
            x = x->next;
            delete [] y;
        }
        delete [] x;
        head = NULL; //как тут можно сделать?
    }
}

int queue::full(){ //проверка на полноту, в этой реализации всегда 0
    return 0;
}

int queue::empty(){ //проверка на пустоту
    if (head == NULL)
        return 1;
    return 0;
}
void queue::enqueue(ad x){
    if (empty()){ //если очередь пустая
        head = new node(x.name, x.address); //создаем голову
        tail = head;
        head->next = tail;
    }
    else{ //если в очереди есть элементы
        node* temp = new node(x.name, x.address); //создаем новый нод
        tail->next = temp;
        tail = temp; //теперь это новый хвост
        temp->next = head; //он указывает на голову
    }
}

ad queue::dequeue(){ //извлечение объекта из очереди
    if (!empty()){
        ad x = head->object; //запоминаем
        if (head == tail){ //если у нас один элемент, удаляем его
            delete [] head;
            head = NULL;
        }
        else{ //если элементов минимум два
            node* temp = head;
            head = head->next;
            tail->next = head;
            delete [] temp;
        }
        return x;
    }
    return error_element.object;
}

ad queue::front(){ //возвращает копию объекта в голове очереди
    if (!empty())
        return head->object;
    return error_element.object;
}

void queue::print_queue(){
    if (head == NULL)
        cout<<"Очередь пуста"<<endl;
    else{
        node* temp = head;
        while(temp != tail){
            cout<<temp->object.name<<" "<<temp->object.address<<endl;
            temp = temp->next;
        }
        cout<<temp->object.name<<" "<<temp->object.address<<endl;
    }
}

int main() {
    queue q;
    q.makenull();
    q.print_queue();
    ad a1("oleg","lensk");
    ad a2("masha","lopatino");
    ad a3("nastya","penza");
    q.enqueue(a1);
    q.enqueue(a2);
    q.enqueue(a3);
    cout<<endl;
    q.print_queue();
    q.dequeue();
    cout<<endl;
    q.print_queue();
    cout<<endl;
    q.dequeue();
    q.print_queue();
    cout<<q.empty()<<endl;
    q.makenull();
    q.print_queue();
}









