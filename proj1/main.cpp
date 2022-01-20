#include "Wordset.hpp"
#include "convert.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void test1() {
    cout <<"Test1: " <<endl;
    unsigned hv = polynomialHashFunction("dbc", 37, 100000);
    unsigned shouldBe = 4*37*37 + 2*37 + 3;
    cout<< hv <<" " << shouldBe <<endl;
}

void test2() {
    cout <<"Test2: " <<endl;
    WordSet ws;
    ws.insert("dbc");
    if(ws.contains("dbc"))
        cout<<"yes"<<endl;
}

void test3() {
    cout <<"Test3: " <<endl;
    WordSet ws;
    ws.insert("sleepy");
    ws.insert("happy");
    if(ws.getCount() == 2)
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;

    ws.insert("dopey");

    if(ws.contains("dopey"))
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;

    ws.insert("sneezy");
    ws.insert("datalink");
    ws.insert("australia");
    ws.insert("guacamole");
    ws.insert("phylum");
    if(ws.getCount() == 8)
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;

    if(ws.contains("guacamole"))
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;

   if(ws.contains("dopey"))
       cout<<"yes"<<endl;
   else
       cout<<"no"<<endl;
}

void test4() {
    cout <<"Test4: " <<endl;
    WordSet ws;
    ws.insert("sleepy");
    ws.insert("happy");
    if(ws.getCount() == 2)
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
    ws.insert("dopey");
    ws.insert("sneezy");
    if(ws.getCount() == 4)
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
    ws.insert("datalink");
    ws.insert("australia");
    if(ws.getCount() == 6)
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
    ws.insert("guacamole");
    ws.insert("phylum");
    if(ws.contains("happy"))
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
    if(ws.contains("dopey"))
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
    ws.insert("salsa");
    ws.insert("sloth");
    ws.insert("colossus");
    ws.insert("synergize");
    std::cout << "*" << std::endl;
    ws.insert("monday");
    std::cout << "*" << std::endl;
    if(ws.getCount() == 13)
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
    std::cout << "*" << std::endl;
}

void test5() {
    cout <<"Test5: " <<endl;
    WordSet words;
    words.insert("abandoning");
    if(words.contains("abandoning"))
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
}

void test6() {
    cout <<"Test6: " <<endl;

    WordSet words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    if(words.contains("dog"))
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;

    std::string r = convert("ant", "art", words);
    cout<< r <<endl;
    if(r == "ant --> art")
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
}

void test7() {
    cout <<"Test7: " <<endl;
    WordSet words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    std::string r = convert("ant", "eat", words);
    cout<< r <<endl;
    if(r == "ant --> aft --> oft --> oat --> eat")
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;

}

void test8() {
    cout <<"Test8: " <<endl;
    WordSet words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    std::string r = convert("man", "ape", words);
    cout<< r <<endl;
    if(r == "man --> mat --> oat --> opt --> apt --> ape")
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
}

void test9() {
    cout <<"Test9: " <<endl;
    WordSet words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    std::string r = convert("steal", "coins", words);
    // steal --> steel --> steep --> sleep --> sleet --> fleet --> flees --> flies --> flips --> clips --> chips --> chins --> coins
    cout<< r <<endl;
}

void test10() {
    cout <<"Test10: " <<endl;
    WordSet words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    std::string r = convert("poor", "rich", words);
    // poor --> boor --> book --> look --> lock --> lick --> lice --> rice --> rich
    cout<< r <<endl;
}

void test11() {
    cout <<"Test11: " <<endl;
    WordSet words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    std::string r = convert("green", "black", words);
    // green --> greed --> breed --> bleed --> blend --> bland --> blank --> black
    cout<< r <<endl;
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
//    test9();
    test10();
    test11();

    return 0;
}
