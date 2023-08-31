#ifndef iterable_hashtable_hpp
#define iterable_hashtable_hpp
#include "hashfn.hpp"

template <typename K, typename V, class hasher = hashfn<K>>
class hashtable {
    private:
        struct node {
            K key;
            V value;
            bool empty;
            bool tombstone;
            node(K _key, V _value) {
                key = _key; value = _value;
                empty = false;
                tombstone = false;
            }
            node() { empty = true; tombstone = false; }
            node(const node& t) {
                key = t.key;
                value = t.value;
                empty = t.empty;
                tombstone = t.tombstone;
            }
            bool isEmpty() const { return empty; }
            bool tombstoned() const { return tombstone; }
        };
        node *table;
        int maxn;
        int n;
        void growAndRehash() {
            int oldmax = maxn;
            maxn *= 2;
            node* temp = table;
            table = new node[maxn];
            n = 0;
            for (int i = 0; i < oldmax; i++) {
                if (!temp[i].isEmpty() && !temp[i].tombstoned())
                    put(temp[i].key, temp[i].value);
            }
            delete [] temp;
        }
        void shrinkAndRehash() {
            int tmxn = maxn/1.3;
            int oldmax = maxn;
            do { tmxn++; } while (((double)n/tmxn) > 0.36);
            maxn = tmxn;
            node* temp = table;
            table = new node[maxn];
            n = 0;
            for (int i = 0; i < oldmax; i++) {
                if (!temp[i].isEmpty() && !temp[i].tombstoned())
                    put(temp[i].key, temp[i].value);
            }
            delete [] temp;
        }
        double loadfactor() {
            return (double)n/maxn;
        }
    public:
        class Iterator {
            private:
                node* __nodePtr;
            public:
                Iterator(node* c) : __nodePtr(c) {
                    while (__nodePtr->isEmpty() || __nodePtr->tombstoned()) {
                        __nodePtr++;
                    }
                }
                pair<K,V> operator*() {
                    return make_pair(__nodePtr->key, __nodePtr->value);
                }
                Iterator operator++() {
                    do {
                            __nodePtr++;
                    } while (__nodePtr->isEmpty() || __nodePtr->tombstoned());
                    return *this;
                }
                Iterator operator++(int) {
                    Iterator tmp = *this;
                    ++*this;
                    return tmp;
                }
                bool operator==(const Iterator& o) const {
                    return __nodePtr == o.__nodePtr;
                }
                bool operator!=(const Iterator& o) const {
                    return !(*this==o);
                }
        };
    public:
        hashtable(int max = 113) {
            maxn = max;
            n = 0;
            table = new node[maxn];
        }
        void put(K key, V value) {
            if (loadfactor() > 0.46) growAndRehash();
            int idx = hasher()(key) % maxn;
            int m = 1;
            while (!table[idx].isEmpty()) {
                if (key == table[idx].key && !table[idx].tombstoned()) {
                    table[idx].value = value;
                    return;
                }
                idx = (idx + (m*m)) % maxn;
                m++;
            }
            table[idx].key = key;
            table[idx].value = value;
            table[idx].empty = false;
            n++;
        }
        int size() const {
            return n;
        }
        int maxsize() const {
            return maxn;
        }
        Iterator find(K key) {
            int idx = hashfn<K>()(key) % maxn;
            int m = 1;
            while (!table[idx].isEmpty()) {
                if (key == table[idx].key)
                    return  table[idx].tombstoned() ? end():Iterator(table+idx);
                idx = (idx + (m*m)) % maxn;
                m++;
            }
            return end();
        }
        void remove(K key) {
            int idx = hashfn<K>()(key) % maxn;
            int m = 1;
            bool found = false;
            while (!table[idx].isEmpty()) {
                if (key == table[idx].key && !table[idx].tombstoned()) {
                    found = true;
                    break;
                }
                idx = (idx + (m*m)) % maxn;
                m++;
            }
            if (found) {
                table[idx].tombstone = true;
                n--;
                if (loadfactor() > .3) shrinkAndRehash();
            }
        }
        Iterator begin() {
            return Iterator(table);
        }
        Iterator end() {
            return Iterator(table+maxn);
        }
        V& operator[](K key) {
            if (find(key) == end()) {
                put(key, (V)0);
            }
            int idx = hasher()(key) % maxn;
            int m = 1;
            while (!table[idx].isEmpty()) {
                if (key == table[idx].key)
                    break;
                idx = (idx + (m*m)) % maxn;
                m++;
            }
            return table[idx].value;
        }
};

#endif