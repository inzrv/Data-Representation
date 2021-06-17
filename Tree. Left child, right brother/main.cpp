#include <iostream>
using namespace std;

struct element{ //элемент массива
    int left_child; //позиция левого сына
    int right_sibling; //позиция правого брата
    char label; //метка текущей вершины
    element(); //конструктор по умолчанию
    element(char c); //конструктор с меткой
};

element::element():left_child(-1),right_sibling(-1),label('*'){};

element::element(char c):left_child(-1),right_sibling(-1),label(c){};

class tree{ //класс дерева (левые сыновья + правые братья)
public:
    tree(); //конструктор по умолчанию
    static void initialization(); //размечаем указатели на братьев и сыновей
    void makenull(); //делаем дерево пустым
    void postorder(int); //обратный обход дерева
    void inorder(int); //симметричный обход дерева
    void preorder(int); //прямой обход дерева
    tree& create0(char c); //создаем вершину-лист
    tree& create1(char c, tree& t); //создаем вершину-родителя t
    tree& create2(char c, tree& t1, tree& t2); //создаем вершину-родителя t1 и t2
    tree& create3(char c, tree& t1, tree& t2, tree& t3); //вершина-родитель трех
    static void print_array(); //печать массива
    int return_root(){return root;} //возвращаем корень
    void print_tree(); //печать дерева
    char return_label(int n); //вернуть метку
    int lefmost_child(int n); //вернуть левого ребенка
    int right_sibling(int n); //вернуть правого брата
    int parent(int n); //родитель n
private:
    int root; //корень данного дерева
    static const int T_SIZE = 10;
    static element array[T_SIZE]; //массив под деревья
    static int space; //указатель на список свободных
    void move(int& p, int& q); //перемещение ячейки массива (как в курсорах)
    void delete_tree(int temp); //удаляем поддерево с корнем temp
    int parent_closed(int n, int temp); //закрытая функция поиска родителя. вызывается рекурсивно
};

int tree::space = 0; //первая свободная

element tree::array[T_SIZE]; //объявляем массив

tree::tree(){
    root = -1;
}

void tree::initialization(){
    int i;
    for(i = 0; i < T_SIZE-1; i++){
        array[i].left_child = i+1; //в левом сыне адрес следующего пустого
    }
    array[i].left_child = -1;
}

void tree::move(int &p, int &q){ //перемещение элементов между списками.раньше на el указывал p, теперь q
    int temp = q;
    q = p;
    p = array[p].left_child;
    array[q].left_child = temp;
}

void tree::postorder(int temp){ //обратный обход дерева
    int child = array[temp].left_child; //берем первого ребенка
    while (child != -1) {
        postorder(child);
        child = array[child].right_sibling; //переходим к сыну правее
    }
    cout<<array[temp].label<<" ";
}

void tree::inorder(int temp){ //симметричный обход дерева
    int child = array[temp].left_child; //берем левого ребенка
    if (child != -1){ //если он существует, то запускаем обход с него
        inorder(child);
        child = array[child].right_sibling; //переходим к правому брату
    }
    cout<<array[temp].label<<" ";
    while (child != -1) {
        inorder(child);
        child = array[child].right_sibling;
    }
}

void tree::preorder(int temp){ //прямой обход дерева
    cout<<array[temp].label<<" ";
    int child = array[temp].left_child;
    while (child != -1) {
        preorder(child);
        child = array[child].right_sibling;
    }
}

void tree::delete_tree(int temp){
    int child = array[temp].left_child; //берем первого ребенка
    while (child != -1) {
        delete_tree(child);
        child = array[child].right_sibling; //переходим к сыну правее
    }
    array[temp].label = '*';
    array[temp].right_sibling = -1;
    move(temp, space);
}

void tree::makenull(){
    delete_tree(root);
    root = -1;
}

char tree::return_label(int n){ //возвращаем метку вершины
    return array[n].label;
}

void tree::print_array(){
    for (int i = 0; i < T_SIZE; i++){
        cout<<i<<". "<<"lc = "<<array[i].left_child<<", label = "<<array[i].label<<", rs = "<<array[i].right_sibling<<endl;
    }
}

tree& tree::create0(char c){ //создание листа
    array[space].label = c;
    move(space, root);
   // cout<<root<<endl;
    return *this;
}

tree& tree::create1(char c, tree &t){ //создание вершины-родителя t
    move(space, root);
    array[root].label = c;
    array[root].left_child = t.root;
    t.root = -1;
    return *this;
}


tree& tree::create2(char c, tree &t1, tree &t2){ //создаем вершину-родителя t1 и t2
    move(space, root);
    array[root].label = c;
    array[root].left_child = t1.root;
    array[t1.root].right_sibling = t2.return_root();
    t1.root = -1;
    t2.root = -1;
    return *this;
}

tree& tree::create3(char c, tree &t1, tree &t2, tree &t3){ //родитель 3х
    move(space, root);
    array[root].label = c;
    array[root].left_child = t1.root;
    array[t1.root].right_sibling = t2.return_root();
    array[t2.root].right_sibling = t3.return_root();
    t1.root = -1;
    t2.root = -1;
    t3.root = -1;
    return *this;
}

void tree::print_tree(){
    if (root == -1)
        cout<<"Дерево пусто"<<endl;
    else
        preorder(root);
}

int tree::lefmost_child(int n){ //левый ребенок вершины n
    return array[n].left_child;
}

int tree::right_sibling(int n){ //правый брат вершины n
    return array[n].right_sibling;
}

int tree::parent(int n){ //родитель вершины n
    return parent_closed(n, root);
}

int tree::parent_closed(int n, int temp){ //закрытая поиск родителя
    if (n == root)
        return -1; //у корня нет родителя
    if (n == temp)
        return n; //нашли ребенка
    int child  = array[temp].left_child; //если мы не корень и не ребенок, то ищем среди своих детей
    int p = -1;
    while (child != -1){ //пока есть дети запускам от каждого из них
        p = parent_closed(n, child); //проверяем данного ребенка
        if (p != -1){ //если вершина n в поддереве данного ребенка
            if (child == n)
                return temp; //если сам ребенок это n, то возвращаем себя
            else
                return p; //иначе то, что передали
        }
        else
            child = array[child].right_sibling; //идем дальше по братьям
    }
    return p; //если ничего не нашли вернется p == -1
}

int main(){
    tree t0,t1,t2,t3,t4,t5,t6,t7,t8;
    t0.initialization();
    t0.create0('a');
    t1.create0('b');
    t2.create2('c', t0, t1);
    t3.create0('d');
    t4.create1('e',t3);
    t5.create0('f');
    t6.create3('g', t2, t4, t5);
    t6.print_array();
    cout<<endl;
    t6.print_tree();
    
    
    
    
    
}

















