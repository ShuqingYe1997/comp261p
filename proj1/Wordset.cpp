#include "Wordset.hpp"
#include <cmath>	// you may want this for log2 and/or ceil.
#include <string>


//////////////////////////////////////////////////////////////////
//////////////////     My functions             //////////////////
//////////////////////////////////////////////////////////////////

unsigned power(unsigned int base, unsigned int n, unsigned int mod) {
    unsigned int res = 1;
    for (int i = 1; i <= n; i++) {
        res *= base;
        res %= mod;
    }
    return res;
}

unsigned int WordSet::hash(const std::string & s, unsigned int tableID, unsigned int tableSize) const
{
    if (tableID == 1)
        return polynomialHashFunction(s, BASE_H1, tableSize);
    else
        return polynomialHashFunction(s, BASE_H2, tableSize);
}

bool WordSet::containsInTable(const std::string &s, unsigned int tableID) const{
    unsigned index = hash(s, tableID, size);
    if (table[tableID - 1][index] == s)
            return true;
    return false;
}

// called in public func insert()
void WordSet::insert2Table(const std::string & s, unsigned int tableID, unsigned cnt) {
    if (cnt >= 3 * log2(size)) {
        rehash();
        // this.table and this.size have been changed
    }

    unsigned int index = hash(s, tableID, size);
    if (!table[tableID - 1][index].empty()) {      // if the position is occupied
        std::string tmp = table[tableID - 1][index];  // move it to the other table
        table[tableID - 1][index] = s;  // do what cuckoo do
        insert2Table(tmp, 3 - tableID, cnt + 1);
    } else
        table[tableID - 1][index] = s;
}

// called in rehash()
// no worry about resizing
void WordSet::insert2NewTable(const std::string & s, std::string** hashTable,
                           unsigned int tableID, unsigned int newSize) {

    unsigned int index = hash(s, tableID, newSize);
    if (!hashTable[tableID - 1][index].empty()) {      // if the position is occupied
        std::string tmp = hashTable[tableID - 1][index];  // move it to the other table
        hashTable[tableID - 1][index] = s;  // do what cuckoo do
        insert2NewTable(tmp, hashTable, 3 - tableID, newSize);
    } else
        hashTable[tableID - 1][index] = s;
}


void WordSet::rehash() {
    // resize
    unsigned int newSize = getNextTableSize(size);
    std::string** newTable = new std::string*[2];
    for (int i = 0; i < 2; i++) {
        std::string *subTable = new std::string[newSize];
        newTable[i] = subTable;
    }

    // rehash
    for(int tableID = 1; tableID <= 2; tableID++) {
        for (int i = 0; i < size; i++) {
            std::string& s = table[tableID - 1][i];
            if(!s.empty())
                insert2NewTable(s, newTable, 1, newSize);
        }
        delete[] table[tableID - 1];   // attention: use delete[] to delete an array
    }

    // re-assign
    delete[] table;
    this->table = newTable;
    this->size = newSize;
}


bool WordSet::isPrime(unsigned num) {
    if (num == 2)
        return true;
    else if (num % 2 == 0)
        return false;

    for (int i = 2; i <= (int)sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

// next table size should be the smallest prime
//number that is no smaller than twice the current table size
unsigned WordSet::getNextTableSize(unsigned num) {
    for (unsigned int i = num * 2 + 1; i < num * 3; i++) {
        if (isPrime(i))
            return i;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////
//////////////////    End of My functions       //////////////////
//////////////////////////////////////////////////////////////////



// returns s, as a number in the given base, mod the given modulus
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod)
{
    unsigned int res = 0;
    unsigned int n = s.size() - 1;
    for (char c : s) {
        res += power(base, n--, mod) * (c - 'a' + 1);
        res %= mod;
    }
    return res;
}

WordSet::WordSet()
{
    size = ORIGINAL_TABLE_SIZE;
    table = new std::string*[2];
    for (int i = 0; i < 2; i++) {
        std::string *subTable = new std::string[size];
        table[i] = subTable;
    }
}

WordSet::~WordSet()
{
    if(table != nullptr){
        for (int i = 0; i < 2; i++)
            delete [] table[i];
        delete [] table;
    }
}

void WordSet::insert(const std::string & s)
{
    if (contains(s))
        return;
    insert2Table(s, 1, 0);
    count++;
}


bool WordSet::contains(const std::string & s) const
{
    return containsInTable(s, 1) || containsInTable(s, 2);
}

// return how many distinct strings are in the set
unsigned WordSet::getCount() const
{
    return count;
}
