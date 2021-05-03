//
// Created by Dom on 01.05.2021.
//

#ifndef GOOGLETESTS_BINARYTREE_H
#define GOOGLETESTS_BINARYTREE_H

#include <iostream>
#include <vector>
#include <string>
template<typename T>
class tree_elem{
public:
    T m_data;
    tree_elem* m_left;
    tree_elem* m_right;

    tree_elem(T key){
        m_data = key;
        m_left = NULL;
        m_right = NULL;
    }
    tree_elem(T key,tree_elem<T>* left,tree_elem<T>* right){
        m_data = key;
        m_left = left;
        m_right = right;
    }
};

template<typename T>
void sqr(tree_elem<T>* curr){
    curr->m_data = curr->m_data * curr->m_data;
}

template<typename T>
bool is_more_than_25(tree_elem<T>* curr){
    if(curr->m_data >= 25)
        return true;
    return false;
}

template<typename T>
T sum(tree_elem<T>* curr,T curr_sum){
    return curr_sum + curr->m_data;
}

template<typename T>
class binary_tree{
private:
    tree_elem<T>* m_root;
    int size;
    void Map_help(void(*func)(tree_elem<T>*),tree_elem<T>* curr){//для рекурсивного выполнения Map
        if(curr){
            Map_help(func ,curr->m_left);
            func(curr);
            Map_help(func,curr->m_right);
        }
    }

    void Where_help(bool(*func)(tree_elem<T>*),tree_elem<T>* curr){//для рекурсивного выполнения Where
        if(curr){
            Where_help(func,curr->m_left);

            if(func(curr)){
                delete_elem(curr->m_data);
            }

            Where_help(func,curr->m_right);
        }
    }

    void Reduce_help(T(*func)(tree_elem<T>*,T),tree_elem<T>* curr,T& curr_sum){//для рекурсивного выполнения Reduce
        if(curr){
            Reduce_help(func,curr->m_left,curr_sum);
            curr_sum = func(curr,curr_sum);
            Reduce_help(func,curr->m_right,curr_sum);
        }
    }

    void upgrade_sub_tree(binary_tree<T>* result,tree_elem<T>* curr){//для рекурсивного заполнения нового экземпляра
        if(curr){
            upgrade_sub_tree(result,curr->m_left);
            result->insert(curr->m_data);
            upgrade_sub_tree(result,curr->m_right);
        }
    }

    void tree_to_string_help(tree_elem<T>* curr,std::vector<std::string>& curr_str){
        if(curr){
            tree_to_string_help(curr->m_left,curr_str);
            curr_str.push_back(std::to_string(curr->m_data));
            tree_to_string_help(curr->m_right,curr_str);
        }
    }

    void print_tree(tree_elem<T>* curr){
        if(curr){
            print_tree(curr->m_left);
            std::cout << curr->m_data << " ";
            print_tree(curr->m_right);
        }
    }
public:

    binary_tree(){
        m_root = nullptr;
        size = 0;
    }

    //конструктор с добавлением первого корня
    binary_tree(int key){
        m_root = new tree_elem<T>(key);
        size = 1;
    }
    ~binary_tree(){
        delete_tree(m_root);
        //delete[] this;
        //delete[] m_root;
    }
    int get_size(){return size;}

    //получение поддерева по узлу
    binary_tree<T>* get_sub_tree(T key){
        tree_elem<T>* curr = m_root;
        while(curr && curr->m_data!=key)
            if(curr->m_data < key)
                curr = curr->m_right;
            else
                curr = curr->m_left;
        binary_tree<T>* result = new binary_tree<T>(curr->m_data);
        upgrade_sub_tree(result,curr);

        return result;
    }

    //печать дерева
    void print(){
        print_tree(m_root);
        std::cout << std::endl;
    }

    //удаление дерева
    void delete_tree(tree_elem<T>* curr){
        if(curr){
            delete_tree(curr->m_left);
            delete[] curr;
            delete_tree(curr->m_right);

        }
    }

    //поиск элемента в дереве
    bool find(int key){//поиск значения
        tree_elem<T>* curr = m_root;
        while(curr && curr->m_data != key){
            if(curr->m_data > key)
                curr = curr->m_left;
            else
                curr = curr->m_right;
        }
        return (bool)curr;
    }

    //добавление элемента
    void insert(int key){//добавление нового элемента в дерево
        if(m_root == nullptr){
            m_root = new tree_elem<T>(key);
            size = 1;
        }else{
            tree_elem<T>* curr = m_root;
            while(curr && curr->m_data != key){
                if(curr->m_data > key){//переход в левое поддерево
                    if(curr->m_left)//если есть возможность,то так как добавляемое значение меньше того,
                        //что в узле curr,
                        //то мы спускаемся в левое поддерево ещё раз(переход для следующей итерации)
                        curr = curr->m_left;
                    else{//если же возможность спуститься ещё ниже нет,то мы добавляем новый элемент в дерево
                        //(так как мы уже находимся на том месте,куда нужно добавить новый элемент)
                        curr->m_left = new tree_elem<T>(key);
                        size++;
                        return;
                    }
                }//для правого поддерева аналогично
                else{//переход в правое поддерево
                    if(curr->m_right)
                        curr = curr->m_right;
                    else{
                        curr->m_right = new tree_elem<T>(key);
                        size++;
                        return;
                    }
                }
            }
        }
    }

    //удаление элемента
    void delete_elem(T key){
        tree_elem<T>* curr = m_root;
        tree_elem<T>* prev = nullptr;
        //поиск удаляемого элемента
        while(curr && curr->m_data != key){
            prev = curr;//запоминаем значение curr,которое изменится на следующем действии
            if(curr->m_data > key){
                curr = curr->m_left;
            }
            else
                curr = curr->m_right;
        }
        if(!curr)//проверка на то,существует ли тот элемент,который мы хотим удалить
            return;

        if(prev->m_right == curr){//если удаляемый элемент является правым наследником
            if(curr->m_right == nullptr && curr->m_left == nullptr){//если удаляемый элемент вообще не имеет поддеревьев
                prev->m_right = nullptr;
                delete[] curr;
                size--;
                return;
            }
            if(curr->m_left == nullptr){//если у удаляемого элемента нет левого поддерева
                prev->m_right = curr->m_right;
                delete[] curr;
                size--;
                return;
            }
            if(curr->m_right == nullptr){//если у удаляемого элемента нет правого поддерева
                prev->m_right = curr->m_left;
                delete[] curr;
                size--;
                return;
            }

        }
        if(prev->m_left == curr){//если удаляемый элемент является левым наследником
            if(curr->m_right == nullptr && curr->m_left == nullptr){//если удаляемый элемент вообще не имеет поддеревьев
                prev->m_left = nullptr;
                delete[] curr;
                size--;
                return;
            }
            if(curr->m_left == nullptr){//если у удаляемого элемента нет левого поддерева
                prev->m_left = curr->m_right;
                delete[] curr;
                size--;
                return;
            }
            if(curr->m_right == nullptr){//если у удаляемого элемента нет правого поддерева
                prev->m_left = curr->m_left;
                delete[] curr;
                size--;
                return;
            }
        }

        //если у удаляемого элемента есть оба поддерева,то на место удаляемого
        //мы должны поставить минимальный элемент из его правого поддерева

        tree_elem<T>* tmp = curr->m_right;//временная переменная для поиска минимума в правом поддереве
        while(tmp->m_left)
            tmp = tmp->m_left;

        T minimum = tmp->m_data;//сохранение значения переменной tmp для последующего удаления



        if(prev->m_left == curr){//если удаляемый элемент является левым наследником
            delete_elem(tmp->m_data);//удаление минимального элемента в правом поддереве
            prev->m_left = new tree_elem<T>(minimum,curr->m_left,curr->m_right);
            delete[] curr;
            size--;
            return;
        }
        if(prev->m_right == curr){//если удаляемый элемент является правым наследником
            delete_elem(tmp->m_data);//удаление минимального элемента в правом поддереве
            prev->m_right = new tree_elem<T>(minimum,curr->m_left,curr->m_right);
            delete[] curr;
            size--;
            return;
        }
    }

    //ЗАВИСИТ ОТ ТОГО,ЧТО ЯВЛЯЕТСЯ КОРНЕМ ! ! !
    bool is_equals_nodes(tree_elem<T>* first,tree_elem<T>* second){//обход реализован корректно
        //проверки на разные поддеревья у предположительно
        //совпадающих узлов
        if(second->m_right == nullptr && second->m_left == nullptr && first->m_data == second->m_data){
            //проверка случая,когда в искомом дереве нет возможности идти влево/вправо
            // и значения с узлом дерева,в котором ищем совпадают
            return true;
        }

        if(second->m_left != nullptr && first->m_left == nullptr){//влево нельзя/можно
            return false;
        }

        if(second->m_right != nullptr && first->m_right == nullptr)//вправо нельзя/можно
            return false;
        if(first->m_data != second->m_data)//несовпадающие значения
            return false;

        if(first->m_right != nullptr && second->m_right!= nullptr && second->m_left == nullptr)//в том дереве,которое ищу,могу двигаться только вправо
            return is_equals_nodes(first->m_right,second->m_right);
        if(first->m_left != nullptr && second->m_left!= nullptr && second->m_right == nullptr)//в том дереве,которое ищу,могу двигаться только влево
            return is_equals_nodes(first->m_left,second->m_left);

        //возможность двигаться влево/вправо в случае ненулевых указателей и совпадающих значений
        if(first->m_left != nullptr && second->m_left != nullptr && first->m_data == second->m_data)
            return is_equals_nodes(first->m_left,second->m_left);

        if(first->m_right != nullptr && second->m_right != nullptr && first->m_data == second->m_data)
            return is_equals_nodes(first->m_right,second->m_right);

    }

    //проверка на то,является ли second поддеревом first
    bool is_subtree(binary_tree<T>* first,binary_tree<T>* second){//в первом ищем второе

        tree_elem<T>* curr = first->m_root;//проверка того,что корень искомого дерева находится в том,
        while(curr && curr->m_data != second->m_root->m_data){// в котором мы ищем
            if(curr->m_data > second->m_root->m_data)
                curr = curr->m_left;
            else
                curr = curr->m_right;
        }

        return is_equals_nodes(curr,second->m_root);
    }

    //map,where,reduce
    void Map(void(*func)(tree_elem<T>*)){//необходимо задать curr,поэтому создана вспомогательная функция
        tree_elem<T>* curr = m_root;
        Map_help(func,curr);
    }

    void Where(bool(*func)(tree_elem<T>*)){//необходимо задать curr,поэтому создана вспомогательная функция
        tree_elem<T>* curr = m_root;
        Where_help(func,curr);
    }

    T Reduce(T(*func)(tree_elem<T>*,T)){
        tree_elem<T>* curr = m_root;
        T curr_sum = 0;
        Reduce_help(func,curr,curr_sum);
        return curr_sum;
    }

    //представление дерева в виде строки
    std::string tree_to_string(){

        tree_elem<T>* curr = m_root;
        std::vector<std::string> result;
        tree_to_string_help(curr,result);

        std::string result_str = "";
        for (int i = 0; i < result.size(); ++i) {
            result_str += result[i] + " ";
        }
        return result_str;
    }


};


#endif //GOOGLETESTS_BINARYTREE_H
