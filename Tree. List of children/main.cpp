#include <iostream>
using namespace std;

struct node{ //структура для списка сыновей (храним только номер вершины в массиве и указатель)
    node(); //конструктор по умолчанию
    node(int p); //конструктор по позиции в массиве
    int pos; //позиция в массиве
    node* next; //указатель на правого брата (следующий в списке)
};

node::node():next(NULL),pos(-1){
}

node::node(int p):pos(p),next(NULL){
}

struct element{ //элемент массива
    element();
    element(char c);
    char label; //метка данной вершины
    node* l; //указатель на список сыновей
    int next; //поле для следующего
};

element::element():label('*'),next(-1),l(NULL){
}

element::element(char c){
    label = c;
    next = -1;
    l = NULL;
}

class tree{
public:
    tree();
    ~tree();
    static void initialization(); //размечаем указатели на следующие элементы
    static void print_array(); //печать всего массива
    static void print_list(int n); //печать списка сыновей вершины n
    tree& create0(char c); //создаем лист-корень
    tree& create1(char c, tree& t); //создаем вершину - родителя t
    tree& create2(char c, tree& t1, tree& t2); //создаем вершину - родителя t1,t2
    tree& create3(char c, tree& t1, tree& t2, tree& t3); //создаем вершину - родителя t1,t2
    void postorder(int temp); //обратный обход дерева //может быть сделать закрытую функцию(int) и открытую отдельно?
    void preorder(int temp); //прямой обход дерева
    void inorder(int temp); //симметричный обход
    int return_root(); //возвращаем корень дерева
    int parent(int n); //возвращаем родителя узла n
    int lefmost_child(int n); //возвращаем самого левого ребенка
    int right_sibling(int n); //возвращаем правого брата
    char return_label(int n); //возвращем метку
    void makenull(); //делает дерево пустым
    void print_tree(); //печать дерева (прямой обход)
private:
    static const int T_SIZE = 20;
    static element array[T_SIZE]; //массив под деревья
    static int space; //указатель на список свободных
    void move(int& p, int& q); //перемещение ячейки массива (как в курсорах)
    void delete_tree(int r); //удаление поддерева с корнем r с помощью обратного обхода
    int parent_closed(int n, int temp);
    int root; //место корня
};

int tree::space = 0; //первая свободная

element tree::array[T_SIZE]; //объявляем массив

tree::tree(){
    root = -1;
}

tree::~tree(){
    if (root != -1)
        makenull();
}

void tree::initialization(){
    int i;
    for(i = 0; i < T_SIZE-1; i++){
        array[i].next = i+1;
    }
    array[i].next = -1;
}

void tree::print_list(int n){ //печать списка сыновей вершины n
    node* temp = array[n].l; //взяли указатель на список сыновей
    if (temp == NULL)
        cout<<"no";
    else{
        while (temp != NULL) {
            cout<<temp->pos<<", "; //выводим позиции сыновей
            temp = temp->next;
        }
    }
}

void tree::print_array(){
    for (int i = 0; i < T_SIZE; i++){
        cout<<i<<": label: "; //номер вершины в массиве
        cout<<array[i].label<<" "; //метка данной вершины
        cout<<"next: "<<array[i].next<<" ";
        cout<<"children: ";
        print_list(i); //список сыновей
        cout<<endl;
    }
}

void tree::move(int &p, int &q){ //перемещение элементов между списками.раньше на el указывал p, теперь q
    int temp = q;
    q = p;
    p = array[p].next;
    array[q].next = temp;
}

tree& tree::create0(char c){ //создаем лист-корень
    array[space].label = c;
    move(space, root);
    return *this; //возвращаем ссылку на объект, на котором вызывали функцию
}

tree& tree::create1(char c, tree &t){ //создаем вершину - родителя t
    array[space].label = c;
    move(space, root);
    node* temp = new node(t.root); //создаем нод
    array[root].l = temp; //добавляем вершину в список детей корня
    t.root = -1; //теперь у листа нет корня
    return *this;
}

tree& tree::create2(char c, tree &t1, tree &t2){ //создаем вершину - родителя t1,t2
    array[space].label = c;
    move(space, root);
    node* temp1 = new node(t1.root);
    node* temp2 = new node(t2.root);
    temp1->next = temp2;
    array[root].l = temp1;
    t1.root = -1;
    t2.root = -1;
    return *this;
}

tree& tree::create3(char c, tree &t1, tree &t2, tree &t3){ //создаем вершину - родителя t1,t2
    array[space].label = c;
    move(space, root);
    node* temp1 = new node(t1.root);
    node* temp2 = new node(t2.root);
    node* temp3 = new node(t3.root);
    temp1->next = temp2;
    temp2->next = temp3;
    array[root].l = temp1;
    t1.root = -1;
    t2.root = -1;
    t3.root = -1;
    return *this;
}


int tree::return_root(){ //возвращаем корень дерева
    return root;
}

void tree::postorder(int temp){ //обратный обход дерева
    if (temp != -1){ //если текущая вершина существует, то хотим запустить обход от ее детей
        node* child = array[temp].l; //обращаемся к первому ребенку
        while(child != NULL){
            postorder(child->pos); //запускаем обход от ребенка
            child = child->next;
        }
        cout<<array[temp].label<<" "; //посещаем текущую вершину
    }
}

void tree::preorder(int temp){ //прямой обход дерева
    if (temp != -1){ //если такая вершина существует
        cout<<array[temp].label<<" "; //вывод текущей вершины
        node* child = array[temp].l; //обращаемся к первому ребенку
        while(child != NULL){
            preorder(child->pos); //запускаем обход от ребенка
            child = child->next;
        }
    }
}

int tree::parent_closed(int n, int temp){ //поиск родителя вершины n. используем прямой обход
    if (n == root){
       // cout<<"parent("<<n<<","<<temp<<") вернул "<<-1<<endl;
        return -1;
    }
    if (temp == n){ //если мы ребенок, то передаем себя
      //  cout<<"parent("<<n<<","<<temp<<") вернул "<<temp<<endl;
        return temp;
    }
    node* x = array[temp].l; //если мы не ребенок ищем среди своих потомков
    int p = -1;
    while (x != NULL){
        p = parent_closed(n, x->pos); //запускаем поиск от каждого ребенка
        if (p != -1){ //если от этого ребенка пришла информация, что родитель в его поддереве
            if (x->pos == n){
                //cout<<"parent("<<n<<","<<temp<<") вернул "<<temp<<endl;
                return temp; //если мы родитель, то передаем выше себя
            }
            else{
               // cout<<"parent("<<n<<","<<temp<<") вернул "<<p<<endl;
                return p; //иначе передаем родителя, которого передали нам
            }
        }
        else
            x = x -> next;
    }
    //cout<<"parent("<<n<<","<<temp<<") вернул "<<p<<endl;
    return p;
}

int tree::parent(int n){
    return parent_closed(n, root);
}

void tree::inorder(int temp){ //симметричный обход дерева
    if (temp != -1){ //если такая вершина существует
        node* child = array[temp].l; //обращаемся к первому ребенку
        if (child != NULL){ //если он есть, то обходим его поддерево
            inorder(child->pos);
            child = child->next;
        }
        cout<<array[temp].label<<" "; //вывод текущей вершины
        while(child != NULL){ // обход оставшихся поддеревьев
            inorder(child->pos); //запускаем обход от ребенка
            child = child->next;
        }
    }
    
}

void tree::delete_tree(int r){ //удаление поддерева с корнем r с помощью обратного обхода
    if (r != -1){ //если текущая вершина существует, то хотим запустить обход от ее детей (????)
        node* x = array[r].l; //обращаемся к первому ребенку
        while(x != NULL){
            delete_tree(x->pos); //запускаем обход от ребенка
            x = x->next;
        }
        
        x = array[r].l; //обращаемся к первому ребенку
        node* y = x;
        while(x != NULL){
            y = x;
            x = x->next;
            delete [] y;
        }
        
        array[r].label = '*'; //удаляем лист
        array[r].l = NULL; //NULL, так как больше у него нет сыновей
        move(r, space); //перемещаем его к свободным
    }
}

int tree::lefmost_child(int n){ //самый левый ребенок
    if (array[n].l != NULL)
        return array[n].l->pos;
    return -1;
}

int tree::right_sibling(int n){ //возвращаем правого брата
    if (n == root) //если n - корень, то у него нет родителя
        return -1;
    int p = parent(n); //ищем родителя у n
    node* x = array[p].l; //начинаем с самого левого ребенка
    node* y = x->next;
    while (y != NULL) {
        if (x->pos == n)
            return y->pos;
        x = y;
        y = y->next;
    }
    return -1;
}

char tree::return_label(int n){ //возвращаем метку вершины
    return array[n].label;
}

void tree::makenull(){
    delete_tree(root);
    root = -1;
}

void tree::print_tree(){
    if (root == -1)
        cout<<"Дерево пусто"<<endl;
    preorder(root);
}

void postord(tree& t, int n){
    int child = t.lefmost_child(n);
    while (child != -1) {
        postord(t,child);
        child = t.right_sibling(child);
    }
    cout<<t.return_label(n)<<" ";
}

int main(){
    tree t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12;
    t1.initialization();
    t1 = t1.create0('a');
    t1.print_tree();
    t2.create0('b');
    cout<<endl;
    t2.print_tree();
    t3.create2('c', t1, t2);
    cout<<endl;
    t3.print_tree();
    t4.create0('d');
    t5.create0('e');
    t6.create3('f', t3, t4, t5);
    cout<<endl;
    t6.print_tree();
    cout<<endl;
    t6.postorder(t6.return_root());
    cout<<endl;
    postord(t6, t6.return_root());
}


















