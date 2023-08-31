# IterableMap
An open addressing hash table implementation using quadratic probing, as well as STL style iterators.
templated to accept user define hash function, defaults to the included hashing algorithm
which is a variant of bernstein's hash that add's an internal mixing step using Knuth's 
cyclic shift. The table automatically resizes to shrink and grow to keep balance between load factor
and memory usage in harmony.

# Iterators
IterableMap supplies a begin() and end() method which returns iterators for use with C++'s
enhanced for loop. The result of find() also returns an Iterator to a key/value pair, 
or returns end() on failure. This is an unordered collection.

# Operations
  ```
     put(Key, Value) - add a key/value pair to the table, or updates the value of the associated key if already present.
     find(Key) - determine if a key is present in the table, returns an iterator to the key/value pair if present, or returns end() if not.
     get(Key) - returns a reference to the value associated with the key.
     remove(Key) - erases the key/value pair from the table
     empty() - returns boolean value representing if the table has any values or not.
     size() - returns the number of key/value pairs in the table
     maxsize() - returns the actual size of the underlying table
     begin() - returns a forward iterator to the first value in the table
     end() - returns an iterator to one place past the last value in the table.
     cbegin()/cend() - same as above, but made const
     operator[key] - returns a reference to the value associated with the key, if no record is present it creates one and returns a reference to the empty value for writing.
  ```

# Example usage

```
#include <iostream>
#include "iterable_hashtable.hpp"
using std::cout;
using std::endl;

void printTable(IterableMap<char, int>& ht) {
    for (auto it = ht.begin(); it != ht.end(); ++it) {
        cout<<(*it).first<<" ";
    }
    cout<<endl;
}

int main() {
    IterableMap<char, int> ht;
    string str = "asentencewithalotofrepeatingletters";
    for (char c : str) {
        if (ht.find(c) == ht.end()) {
            ht.put(c, 1);
        } else {
            ht.put(c, (*ht.find(c)).second + 1);
            //or: ht[c]++
        }
    }
    printTable(ht);
    for (char c : str) {
        if (ht.find(c) != ht.end()) {
            ht.remove(c);
        }
    }
}
```
