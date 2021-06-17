#include <iostream>
#include <fstream>
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

int equality(ad x, ad y){ //сравнение двух адресов
    if (strcmp(x.address, y.address) == 0 && strcmp(x.name, y.name) == 0)
        return 1;
    return 0;
}



///-------------------------------  М   А   С   С   И   В   -----------------------------///
///-------------------------------  Н   А   Ч   А   Л   О   -----------------------------///


namespace List1{ //реализация списка на массиве
    typedef int  position;
    
    struct err_ad{
        ad object;
        position address;
        err_ad(); //конструктор для фиктивного элемента
    };
    
    err_ad error_element;
    
    class list{
    public:
        list(); //конструктор
        position end(); //возвращаем конец списка, а именно первый свободный
        void  insert(ad x, position p); //вставка элемента в список
        position locate(ad x); //возвращает позицию объекта x в списке. Если несколько x-ов, то возвращаем первый, если x-ов нет, то end()
        ad retrieve(position p); //возвращает объект с места p. Результат не определен, если p не существует или если p = end()
        void delete_from_pos(position p); //удаление объекта в позиции p
        position next(position p); //позиция следующего элемента
        position previous(position p); //позиция предыдущего элемента
        //если p - последняя позиция в списке, то next(p) = end(), если p = end(), то результат не определен
        //если p = 1, то previous(p) - не определен, previous(end()) не определен
        //обе функции не определены, если p нет в списке
        position makenull(); //делает список пустым, возвращает end()
        position first(); //возвращает первую позицию в списке
        void printlist(); //печать списка
        void initialization(){}; //ввод списка
    private:
        static const int SIZE = 100; //размер массива
        ad l[SIZE]; //массив адресов
        int last = 0; //переменная разделяет свободную и занятую часть (позицию первого свободного)
    };
}

List1::err_ad::err_ad():object("error","error"),address(-101){ //конструктор для фиктивного элемента
}

List1::list::list(){ //конструктор списка на массиве
    last = 0; //первый свободный
}

List1::position List1::list::end(){ //возвращем конец списка
    return last;
}

void List1::list::insert(ad x, position p){ //вставка элемента
    if (p >= 0 && p <= last){ //если такая позиция существует, то вставляем в нее
        for (int i = last - 1; i >= p; i--){
            l[i+1] = l[i];
        }
        l[p] = x; //присваивание нужно посмотреть
        last++; //количество элементов массива увеичилось
    }
}

List1::position List1::list::locate(ad x){ //поиск элемента
    for (int i = 0; i < last; i++){ //проходим по массиву
        if (equality(x, l[i])) //если адреса совпадают, то возвращаем позицию
            return i;
    }
    return last;
}

ad List1::list::retrieve(position p){ //возвращает объект с места p
    if (p < 0 && p >= last)
        return error_element.object;
    return l[p];
}

void List1::list::delete_from_pos(position p){ //удаление объекта с места p
    if (p >= 0 && p < last){ //если место для удаления корректно
        for (int i = p+1; i < last; i++){ //сдвигаем
            l[i-1] = l[i];
        }
        last--;
    }
}

void List1::list::printlist(){ //печать листа
    if (last == 0){
        cout<<"Список пуст"<<endl;
        return;
    }
    for (int i = 0; i < last; i++){
        cout<<i<<". Name: "<<l[i].name<<" address: "<<l[i].address<<endl;
    }
}

List1::position List1::list::first(){ //возвращает позицию первого элемента
    return 0;
}

List1::position List1::list::next(position p){
    if (p > last || p < 0)
        return -1; // адрес фиктивного элемента
    return p+1;
}

List1::position List1::list::previous(position p){
    if (p >= last || p <= 0)
        return error_element.address; //адрес фиктивного элмента
    return p-1;
}

List1::position List1::list::makenull(){
    for(int i = 0; i < last; i++){
        strcpy(l[i].name, "none");
        strcpy(l[i].name, "none");
    }
    last = 0;
    return last;
}
///-------------------------------  М   А   С   С   И   В   -----------------------------///
///-------------------------------  К   О   Н   Е   Ц   !   -----------------------------///





///-------------------------------  С   П   И   С   О   К  (1)   -----------------------------///
///-------------------------------  Н   А   Ч   А   Л   О   -----------------------------///

namespace List2 { //реализация списка на односвязном списке
    
    struct node{ //элемент = объект + адрес
        ad object; //объект (адрес адресата + имя адресата)
        node* next; // (указатель на следующий нод)
        node(); //конструктор фиктивного элемента
        node(const char n[], const char a[], node* nxt = NULL); //конструктор нода по адресу и имени
        node(node const &); //копия объекта
    };
    
    typedef node*  position; //позиция, теперь это указатель на нод
    
    node error_element; //глобальный фиктивный элемент
    
    class list{
    public:
        list(); //конструктор
        ~list();
        position end(); //возвращаем конец списка (null)
        void insert(ad x, position &p); //вставка элемента в список
        position locate(ad x); //возвращает позицию объекта x в списке. Если несколько x-ов, то возвращаем первый, если x-ов нет, то end()
        ad retrieve(position p); //возвращает объект с места p. Результат не определен, если p не существует или если p = end()
        void delete_from_pos(position &p); //удаление объекта в позиции p
        position next(position p); //позиция следующего элемента
        position previous(position p); //позиция предыдущего элемента
        position makenull(); //делает список пустым, возвращает end()
        position first(); //возвращает первую позицию в списке
        void printlist(); //печать списка
        void printel(position p); //печать одного элемента
        void initialization(){}; //ввод списка
    private:
        node* head;
        void delete_list();
        position check(position p); //проверка, есть ли такая позиция в списке
        position gotoend(); //возвращает предпоследний элемент или голову
    };
}

List2::node::node():object("error","error"),next(this){ //конструктор фиктивного элемента
}


List2::node::node(const char n[], const char a[], node* nxt){ //конструктор нода по адресу и имени
    strcpy(object.name, n);
    strcpy(object.address, a);
    next = nxt;
}

List2::node::node(node const &n){ //копирующий конструктор
    object  = n.object;
    next = n.next;
}


List2::list::list(){ //конструктор для списка
    head = NULL;
}

List2::list::~list(){ //деструктор для списка
    delete_list();
}


void List2::list::delete_list(){ //функция удаления списка
    node* pointer_1 = head;
    node* pointer_2 = pointer_1;
    while (pointer_1 != NULL){
        pointer_1 = pointer_1 -> next;
        delete [] pointer_2;
        pointer_2 = pointer_1;
    }
}

List2::position List2::list::makenull(){ //очистка списка
    if (head != NULL)
        delete_list();
    head = NULL;
    return head;
}

List2::position List2::list::end(){ //конец списка
    return NULL;
}

List2::position List2::list::first(){ //начало списка
    return head;
}

List2::position List2::list::check(position p){ //проверка позиции в списке
    position x = head;
    if (x == NULL || p == NULL)
        return NULL; //если список пустой, то возврщаем NULL
    position y = x;
    while (x != NULL){
        if (x == p){
            return y;
        }
        y = x;
        x = x->next;
    }
    return NULL; //если позиция в списке есть, то голова или предыдущий, иначе NULL
}

List2::position List2::list::locate(ad a){ //возвращает позицию объекта в
    position x = head;
    if (x == NULL)
        return NULL; //если список пустой, то возврщаем конец
    while (x != NULL){
        if (equality(x->object, a)){
            return x;
        }
        x = x->next;
    }
    return NULL; //если адрес в списке есть, вернем его позицию
}

ad List2::list::retrieve(position p){ //возвращем объект с позиции p
    position c = check(p); //проверяем позицию p
    if (c == NULL)
        return error_element.object; //если такой позиции нет, возвращаем фиктивный элемент
    if (p == head)
        return head->object;
    else
        return c->next->object;
}

List2::position List2::list::gotoend(){ //поиск последнего в непустом списке
    position x = head;
    position y = x;
    while (x != NULL){
        y = x;
        x = x->next;
    }
    return y; //возвращаем адрес последнего элемента
}

List2::position List2::list::next(position p){ //возвращаем следующий элемент
    position c = check(p);
    if (c == NULL) //если такой позиции в списке нет, то возвращаем ошибку
        return error_element.next;
    // если чек не равен нулю, то такая позиция в списке есть
    //тогда c либо голова, либо предыдущий
    if (p == head)
        return head->next;
    return c->next->next;
}

List2::position List2::list::previous(position p){ //предыдущая позиция
    position c = check(p); //проверяем, есть ли такая позиция
    if (c == NULL)
        return error_element.next;
    if (p == head)
        return error_element.next;
    return c;
    
}

void List2::list::insert(ad x, position &p){ //вставка элемента в позицию p (что с позицией?)
    if (p == NULL){ //вставляем в конец
        if (head == NULL){ //добавляем голову
            head = new node(x.name,x.address);
            p = head;
        }
        else{ //если голова уже есть и вставляем в конец
            position last = gotoend(); //нашли последний элемент
            node* temp = new node(x.name,x.address);
            last->next = temp;
            p = temp;
        }
    }
    else{ //вставляем не в конец
        position c = check(p); //проверяем есть ли такая позиция вообще
        if (c != NULL){ //если позиция для вставки есть
            if (p == head){ //если вставляем в голову
                node* temp = new node(x.name,x.address);
                temp->next = head;
                head = temp;
                p = head;
            }
            else{ //вставлем в список, но не в голову. с - предыдущий элемент
                node* temp = new node(*c->next); //делаем копию смещаемого объекта
                p->object = x; //переписываем объект
                p->next = temp;
            }
        }
    }
}

void List2::list::delete_from_pos(position &p){ //не хотим терять позицию - меняем ее в функции (как? возврщать/ссылка)
    position c = check(p);
    if (c != NULL){ //если есть что удалять, удаляем
        if (p == head){
            position temp = head; //запомнили, что удаляем
            head = head->next; //перенесли голову
            p = head; //перенесли указатель
            delete [] temp; //удалили нужное
        }
        else{ //если удаляем не голову. с->next = то, что удаляем
            position temp = c->next;
            c->next = temp->next;
            p = temp->next;
            delete [] temp;
        }
    }
}

void List2::list::printlist(){ //вывод списка
    node* pointer = head;
    if (pointer == NULL)
        cout<<"Список пуст"<<endl;
    int i = 0;
    while (pointer != NULL) {
        cout<<i<<". Name: "<<pointer->object.name<<" address: "<<pointer->object.address<<endl;
        i++;
        pointer = pointer -> next;
    }
}

void List2::list::printel(position p){
    if (p == NULL)
        cout<<"NULL"<<endl;
    else
        cout<<"Элемент Name: "<<p->object.name<<" address: "<<p->object.address<<endl;
}

///-------------------------------  С   П   И   С   О   К  (1)   -----------------------------///
///-------------------------------  К   О   Н   Е   Ц   !   -----------------------------///



///-------------------------------  С   П   И   С   О   К  (2)   -----------------------------///
///-------------------------------  Н   А   Ч   А   Л   О   -----------------------------///


namespace List3 { //реализация списка на односвязном списке
    
    struct node{ //элемент = объект + адрес
        ad object; //объект (адрес адресата + имя адресата)
        node* next; // (указатель на следующий нод)
        node* prev; //указатель на предыдущий нод
        node(); //конструктор фиктивного элемента
        node(const char n[], const char a[], node* nxt = NULL, node* prv = NULL); //конструктор нода по адресу и имени
        node(node const &); //копия объекта
    };
    
    typedef node*  position; //позиция, теперь это указатель на нод
    
    node error_element; //глобальный фиктивный элемент
    
    class list{
    public:
        list(); //конструктор
        ~list();
        position end(); //возвращаем конец списка (null)
        void insert(ad x, position &p); //вставка элемента в список
        position locate(ad x); //возвращает позицию объекта x в списке. Если несколько x-ов, то возвращаем первый, если x-ов нет, то end()
        ad retrieve(position p); //возвращает объект с места p. Результат не определен, если p не существует или если p = end()
        void delete_from_pos(position &p); //удаление объекта в позиции p
        position next(position p); //позиция следующего элемента
        position previous(position p); //позиция предыдущего элемента
        position makenull(); //делает список пустым, возвращает end()
        position first(); //возвращает первую позицию в списке
        void printlist(); //печать списка
        void printel(position p); //печать одного элемента
        void initialization(){}; //ввод списка
    private:
        node* head;
        node* tail;
        void delete_list();
        int check(position p); //проверка, есть ли такая позиция в списке (ди или нет)
        position gotoend(); //возвращает предпоследний элемент или голову
    };
}

List3::node::node():object("error","error"),next(this){ //конструктор фиктивного элемента
}


List3::node::node(const char n[], const char a[], node* nxt, node* prv){ //конструктор нода по адресу и имени
    strcpy(object.name, n);
    strcpy(object.address, a);
    next = nxt;
    prev = prv;
}

List3::node::node(node const &n){ //копирующий конструктор
    object  = n.object;
    next = n.next;
    prev = n.prev;
}

List3::list::list(){ //конструктор для списка
    head = NULL;
    tail = NULL;
}

List3::list::~list(){ //деструктор для списка
    delete_list();
}


void List3::list::delete_list(){ //функция удаления списка
    node* pointer_1 = head;
    node* pointer_2 = pointer_1;
    while (pointer_1 != NULL){
        pointer_1 = pointer_1 -> next;
        delete [] pointer_2;
        pointer_2 = pointer_1;
    }
}

List3::position List3::list::makenull(){ //очистка списка
    if (head != NULL)
        delete_list();
    head = NULL;
    tail = NULL;
    return head;
}

List3::position List3::list::end(){ //конец списка
    return NULL;
}

List3::position List3::list::first(){ //начало списка
    return head;
}

int List3::list::check(position p){ //проверка позиции в списке
    position x = head;
    if (x == NULL || p == NULL)
        return 0; //если список пустой, то возврщаем NULL
    position y = x;
    while (x != NULL){
        if (x == p){
            return 1;
        }
        y = x;
        x = x->next;
    }
    return 0; //если позиция в списке есть, то голова или предыдущий, иначе NULL
}

List3::position List3::list::locate(ad a){ //возвращает позицию объекта в
    position x = head;
    if (x == NULL)
        return NULL; //если список пустой, то возврщаем конец
    while (x != NULL){
        if (equality(x->object, a)){
            return x;
        }
        x = x->next;
    }
    return NULL; //если адрес в списке есть, вернем его позицию
}

ad List3::list::retrieve(position p){ //возвращем объект с позиции p
    int c = check(p); //проверяем позицию p
    if (c == 0)
        return error_element.object; //если такой позиции нет, возвращаем фиктивный элемент
    return p->object; //если такой элемент есть, возвращем его
}

List3::position List3::list::gotoend(){ //поиск последнего в непустом списке
    return tail;
}

List3::position List3::list::next(position p){ //возвращаем следующий элемент
    int c = check(p);
    if (c == 0) //если такой позиции в списке нет, то возвращаем ошибку
        return error_element.next;
    // если чек не равен нулю, то такая позиция в списке есть
    //тогда c либо голова, либо предыдущий
    return p->next;
}

List3::position List3::list::previous(position p){ //предыдущая позиция
    int c = check(p); //проверяем, есть ли такая позиция
    if (c == 0)
        return error_element.next;
    if (p == head)
        return error_element.next;
    return p->prev;
    
}

void List3::list::insert(ad x, position &p){ //вставка элемента в позицию p (что с позицией?)
    if (p == NULL){ //вставляем в конец
        if (head == NULL){ //добавляем голову
            head = new node(x.name,x.address);
            tail = head;
            p = head;
        }
        else{ //если голова уже есть и вставляем в конец
            position last = gotoend(); //нашли последний элемент
            node* temp = new node(x.name,x.address);
            last->next = temp;
            temp->prev = last;
            tail = temp;
            p = temp;
        }
    }
    else{ //вставляем не в конец
        int c = check(p); //проверяем есть ли такая позиция вообще
        if (c == 1){ //если позиция для вставки есть
            if (p == head){ //если вставляем в голову
                node* temp = new node(x.name,x.address);
                temp->next = head;
                head->prev = temp;
                head = temp;
                p = head;
            }
            else{ //вставлем в список, но не в голову. с - предыдущий элемент
                node* temp = new node(*p); //делаем копию смещаемого объекта
                p->object = x; //переписываем объект
                p->next = temp;
                p->prev = temp->prev;
                temp->prev = p;
            }
        }
    }
}

void List3::list::delete_from_pos(position &p){ //не хотим терять позицию - меняем ее в функции (как? возврщать/ссылка)
    int c = check(p);
    if (c == 1){ //если есть что удалять, удаляем
        if (p == head){
            position temp = head; //запомнили, что удаляем
            head = head->next; //перенесли голову
            if (head != NULL)
                head->prev = NULL;
            p = head; //перенесли указатель
            delete [] temp; //удалили нужное
        }
        else{ //если удаляем не голову. temp = то, что удаляем
            position temp = p;
            temp->prev->next = temp->next;
            if (temp->next != NULL)
                temp->next->prev = temp->prev;
            p = temp->next;
            delete [] temp;
        }
    }
}


void List3::list::printlist(){ //вывод списка
    node* pointer = head;
    if (pointer == NULL)
        cout<<"Список пуст"<<endl;
    int i = 0;
    while (pointer != NULL) {
        cout<<i<<". Name: "<<pointer->object.name<<" address: "<<pointer->object.address<<endl;
        i++;
        pointer = pointer -> next;
    }
}

void List3::list::printel(position p){
    if (p == NULL)
        cout<<"NULL"<<endl;
    else
        cout<<"Элемент Name: "<<p->object.name<<" address: "<<p->object.address<<endl;
}


///-------------------------------  С   П   И   С   О   К  (2)   -----------------------------///
///-------------------------------  К   О   Н   Е   Ц   !   -----------------------------///




///-------------------------------  К   У   Р   С   О   Р   -----------------------------///
///-------------------------------  Н   А   Ч   А   Л   О   -----------------------------///


namespace List4 { //пространство имен для курсоров
    typedef int  position;
    
    struct el{ //один объект = элемент массива
        el(); //конструктор для элемнента
        ad address; //адрес человека
        position next; //позиция (индекс) следующего элемента
    };
    
    struct err_ad{
        ad object;
        position address;
        err_ad(); //конструктор для фиктивного элемента
    };
    
    err_ad error_element;
    
    class list{
    public:
        list(); //конструктор
        position end(); //возвращаем конец списка, а именно первый свободный
        position first(); //указатель на начало списка
        void  insert(const ad x, position p); //вставка элемента в список
        position locate(ad x); //возвращает позицию объекта x в списке. Если несколько x-ов, то возвращаем первый, если x-ов нет, то end()
        ad retrieve(position p); //возвращает объект с места p. Результат не определен, если p не существует или если p = end()
        void delete_from_pos(position &p); //удаление объекта в позиции p (????? ссылка)
        position next(position p); //позиция следующего элемента
        position previous(position p); //позиция предыдущего элемента
        //если p - последняя позиция в списке, то next(p) = end(), если p = end(), то результат не определен
        //если p = 1, то previous(p) - не определен, previous(end()) не определен
        //обе функции не определены, если p нет в списке
        position makenull(); //делает список пустым, возвращает end()
        void printlist(); //печать списка
        void initialization(); //ввод списка
        void print_array(); //печать массива
        void print_el(position i);
    private:
        static const int SIZE = 10; //размер массива
        static el array[SIZE]; //массив адресов
        static position space;
        position begin; //позиция первого
        void move (position& p, position& q); //перемещение элемента (p -> el) ---> (q -> el)
        position search(position p); //поиск нужной позиции
        position search_last(); //поиск последнего элемента списка
        void delete_list(); //удаление листа
    };
}

List4::position List4::list::space = 0; //первая свободная

List4::el List4::list::array[SIZE]; //объявляем массив

List4::list::list(){ //пустой список
    begin = -1;
}

List4::err_ad::err_ad():object("error","error"),address(-101){ //конструктор для фиктивного элемента
}

List4::el::el():address("none", "none"),next(-1){ //конструктор элемента
    
}

List4::position List4::list::end(){ //позиция конца
    return -1;
}

List4::position List4::list::first(){
    return begin; //возвращаем указатель на начало списка
}

void List4::list::initialization(){ //инициалиация списка (ссылки на следующие)
    int i;
    for (i = 0; i < SIZE - 1; i++)
        array[i].next = i + 1;
    array[SIZE-1].next = -1; //конец свободного списка
}

List4::position List4::list::search(position pos){
    position x = begin; //начиная с первой позиции
    position y = x;
    while (x != -1){ //пока не конец списка ищем
        if (x == pos)
            return y; //если нашли нужную, возвращаем предыдущую
        y = x;
        x = array[x].next;
    }
    return x; //если не нашли нужной позиции, возвращаем -1
}

List4::position List4::list::search_last(){ //поиск последнего элемента списка
    position x = begin;
    position y = x;
    while (x != -1) {
        y = x;
        x = array[x].next;
    }
    return y;
}

void List4::list::move(position &p, position &q){ //перемещение элементов между списками.раньше на el указывал p, теперь q
    position temp = q;
    q = p;
    p = array[p].next;
    array[q].next = temp;
}

void List4::list::insert(const ad a, position pos){ //вставка элемента в список в позицию pos = номер ячейки элемента на месте pos в списке
    if (pos == begin){ //если вставляем в начало списка. пустой список тоже здесь // p == -1  тоже тут
        array[space].address = a;
        move(space, begin);
        return;
    } //return
    
    if (pos == -1){ //если вставляем в конец
        position last = search_last();
        array[space].address = a;
        move(space, array[last].next);
        return;
    }
    //если вставляем не в конец
    int c = search(pos); //проверяем позицию
    if (c != -1){ //если такая позиция существует, то вставляем после нее
        array[space].address = a;
        move(space, array[c].next);
    }
}

void List4::list::delete_from_pos(position &pos){ //удаление элемента с позиции
    position c = search(pos);
    position temp = pos;
    pos = array[pos].next;
    ad none("none","none");
    if (c != -1){ //такая позиция есть в списке
        if (temp == begin){
            array[begin].address = none;
            move(begin, space);
        }
        else{
            array[array[c].next].address = none;
            move(array[c].next, space);
        }
    }
}

List4::position List4::list::locate(ad x){ //поиск позиции элемента
    position p = begin;
    while (p != -1) {
        if (equality(array[p].address, x))
            return p;
        p = array[p].next;
    }
    return p;
}

ad List4::list::retrieve(position p){ //возвращаем элемент с позиции p
    position x = begin; //начинаем с начала
    while (x != -1){
        if (x == p)
            return array[x].address;
        x = array[x].next;
    }
    return error_element.object; //если такой позиции в списке нет, то возвращаем фиктивный элемент
}

List4::position List4::list::next(position pos){ //поиск следующего элемента
    if (search(pos) != -1)
        return array[pos].next;
    if (pos == search_last())
        return -1;
    if (pos == -1)
        return -1; // ??????
    return error_element.address;
}

List4::position List4::list::previous(position p){ //поиск предыдущего элемента
    if (p == begin || p == -1) // если начало или конец - ошибка
        return error_element.address;
    position c = search(p);
    if (c != -1)
        return c;
    return error_element.address;
}

List4::position List4::list::makenull(){
    delete_list();
    return -1;
}

void List4::list::printlist(){
    position x = begin;
    if (x == -1)
        cout<<"Список пуст"<<endl;
    int i = 0;
    while (x != -1) {
        cout<<i<<". Name: "<<array[x].address.name<<" address: "<<array[x].address.address<<endl;
        x = array[x].next;
        i++;
    }
}

void List4::list::print_array(){
    for (int i = 0; i < SIZE; i++){
        cout<<i<<": "<<array[i].address.name<<", "<<array[i].address.address<<", "<<array[i].next<<endl;
    }
}

void List4::list::delete_list(){
    while (begin != -1){
        strcpy(array[begin].address.address, "none");
        strcpy(array[begin].address.name, "none");
        move(begin, space);
    }
}

void List4::list::print_el(position i){
    cout<<array[i].address.name<<", "<<array[i].address.address<<endl;
}

///-------------------------------  К   У   Р   С   О   Р   -----------------------------///
///-------------------------------  К   О   Н   Е   Ц   !   -----------------------------///
