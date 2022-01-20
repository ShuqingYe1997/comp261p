#include <iostream>
#include "MyRBTree.h"

void test1() {
    MyRBTree<int, std::string> tree;
    tree.insert(5, "foo");
    if(tree.contains(5))
        std::cout<<"test1 ok"<<std::endl;
}
void test2() {
    MyRBTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(10, "bar");
    if(tree.contains(10) && tree.contains(5))
        std::cout<<"test2 ok"<<std::endl;
}
void test3() {
    MyRBTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    bool f1 = tree.contains(10);
    bool f2 = tree.contains(5);
    bool f3 = tree.contains(3);
    bool f4 = tree.contains(12);
    if(f1 && f2 && f3 && f4)
        std::cout<<"test3 ok"<<std::endl;
    else std::cout<<"test3 failed"<<std::endl;
}
void test4() {
    MyRBTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");
    if(tree.size() == 5)
        std::cout<<"test4 ok"<<std::endl;
    else std::cout<<"test4 failed"<<std::endl;

}
void test5() {
    MyRBTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");
    if (tree.find(3) == "sna")
        std::cout<<"test5 ok"<<std::endl;
    else std::cout<<"test5 failed"<<std::endl;
}

void test6() {
    MyRBTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");
    std::vector<int> trav = tree.reportAllInRange(5, 11);
    std::vector<int> expected = {5, 10};
    if(trav.at(0) == 5 && trav.at(1) == 10)
        std::cout<<"test6 ok"<<std::endl;
    else std::cout<<"test6 failed"<<std::endl;
}

void test7() {
    MyRBTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");

    std::vector<int> trav = tree.inOrder();
    std::vector<int> expected = {3, 5, 10, 12, 15};
    for (int i = 0; i < trav.size(); i++) {
        if (trav.at(i) != expected.at(i)) {
            std::cout << "test7 failed" << std::endl;
            return;
        }
    }
    std::cout<<"test7 ok"<<std::endl;
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    return 0;
}
