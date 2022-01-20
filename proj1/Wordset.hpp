#ifndef __WORD_SET___HPP
#define __WORD_SET___HPP


#include <string>

// You may assume, in writing this function, that the given
// string consists solely of lower-case letters.
// The coefficients of the polynomial are the letters in the string,
// and the value at which it is being evaluated is the parameter 'base'.

unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod);


class WordSet
{
public: 
	explicit WordSet();
	~WordSet();

	// adds the given string to the WordSet, so that any 
	// future calls to contains(s) will return true.
	// Note that we are not implementing remove in this
	// project, although I suppose we could. 
	void insert(const std::string & s);

	bool contains(const std::string & s) const;

	// return how many distinct strings are in the set
	unsigned getCount() const; 

private:
	// functions h1 and h2 use the polynomial hash function above,
	// each are mod the table size, but h1 uses base=BASE_H1 and 
	// h2 uses BASE_H2.
	static constexpr unsigned BASE_H1 = 33;
	static constexpr unsigned BASE_H2 = 41;    
	// You may declare additional private functions and member variables here.

	const unsigned ORIGINAL_TABLE_SIZE = 13;
	unsigned int size = 0;  // table size
    std::string** table = nullptr;
    unsigned int count = 0;  // number of strings in table

    // tableID = 1 or 2
    unsigned int hash(const std::string & s, unsigned int tableID, unsigned int tableSize) const;
    void insert2Table(const std::string & s,unsigned int tableID, unsigned int cnt);
    void insert2NewTable(const std::string & s, std::string** hashTable, unsigned int tableID, unsigned newSize);
    bool containsInTable(const std::string & s, unsigned int tableID) const;
    void rehash();
    unsigned getNextTableSize(unsigned num);
    bool isPrime(unsigned num);
};


#endif
