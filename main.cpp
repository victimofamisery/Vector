#include <iostream>
#include "vector.h"

int main(){
    Vector a;
    a.pushBack(3);
    a.pushBack(4);
    a.pushBack(6);
    a.pushBack(8);
    a.pushBack(1);
    std::cout << a << std::endl;
    Vector::Iterator it = a.begin();
    std::cout << *it << std::endl;
    it++;
    std::cout << *it << std::endl;
    ++it;
    std::cout << *it << std::endl;
    --it;
    std::cout << *it << std::endl;
    it--;
    std::cout << *it << std::endl;
    it += 2;
    std::cout << *it << std::endl;
    it -= 1;
    std::cout << *it << std::endl;
    if(*it==*it){
        std::cout << "good" << std::endl;
    }
    if(*it!=*it){
        std::cout << "bad" << std::endl;
    }
    a.pushFront(10);
    std::cout << a << std::endl;
    a.popBack();
    std::cout << a << std::endl;
    a.popFront();
    std::cout << a << std::endl;
    a.pushBack(7);
    a.pushBack(4);
    a.pushBack(6);
    a.pushBack(8);
    a.pushBack(1);
    std::cout << a << std::endl;
    a.erase(4);
    std::cout << a << std::endl;
    a.eraseBetween(2,5);
    std::cout << a << std::endl;
    std::cout << a.size() << std::endl;
    std::cout << a.capacity() << std::endl;
    std::cout << a.loadFactor() << std::endl;
    a.shrinkToFit();
    std::cout << a.size() << std::endl;
    std::cout << a.capacity() << std::endl;

    std::cout << "insert" << std::endl;
    Vector b;
    b.pushBack(15);
    b.pushBack(40);
    b.pushBack(80);
    b.pushBack(27);
    b.pushBack(100);
    b.insert(1, 1);
    std::cout << b << std::endl;
    std::cout << a << std::endl;
    b.insert(a, 2);
    std::cout << b << std::endl;
    double* c = new double[10] { 1,2,3,4,5,6,7,8,9,10 };
    b.insert(c, 8, 3);
    std::cout << b << std::endl;
    return 0;
}