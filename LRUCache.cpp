#include <iostream>
#include <ext/hash_map>
#include <map>
#include <vector>
using namespace std;
using namespace __gnu_cxx;

namespace __gnu_cxx{
	template<> struct hash<const string> {
		size_t operator()(const string& s) const { 
			return hash<const char *>()( s.c_str() );
		}
	};
	template<> struct hash<string> {
		size_t operator()(const string& s) const {
			return hash<const char *>()( s.c_str() );
		}
	};
}

template<class K, class V>
struct LRUEntry {
	K key;
	V value;
	LRUEntry *prev;
	LRUEntry *next;
};

template<class K, class V>
class LRUCache {
private:
	hash_map<K, LRUEntry<K, V> *> m_map;
	vector<LRUEntry<K, V> *> m_freeEntrys;
	LRUEntry<K, V> *m_head;
	LRUEntry<K, V> *m_tail;
	LRUEntry<K, V> *m_entrys;

public:
	LRUCache(size_t size) {
		m_entrys = new LRUEntry<K, V>[size];
		for (int i = 0; i < size; i++) {
			m_freeEntrys.push_back(m_entrys + i);
		}
		m_head = new LRUEntry<K, V>;
		m_tail = new LRUEntry<K, V>;
		m_head->prev = NULL;
		m_head->next = m_tail;
		m_tail->prev = m_head;
		m_tail->next = NULL;
	}
	~LRUCache() {
		delete m_head;
		delete m_tail;
		delete[] m_entrys;
	}
	void put(const K &key, const V &value) {
		LRUEntry<K, V> *node = m_map[key];
		if (node) {
			//cout << "exisit key" << endl;
			detach(node);
			node->value = value;
			attach(node);
		}
		else {
			if (m_freeEntrys.empty()) {
				node = m_tail->prev;
				//cout << "get tail prev key:" << node->key << endl;
				m_map.erase(node->key);
				detach(node);
			}
			else {
				//cout << "pop_back" << endl;
				node = m_freeEntrys.back();
				m_freeEntrys.pop_back();
			}
			node->value = value;
			node->key = key;
			m_map[key] = node;
			attach(node);
			//cout << "tail prev:" << m_tail->prev->key << endl;
		}
	}
	V get(const K &key) {
		LRUEntry<K, V> *node = m_map[key];
		if (node) {
			//cout << "get node value:" << node->value << endl;
			detach(node);
			attach(node);
			return node->value;
		}
		return V();
	}

private:
	void detach(LRUEntry<K, V> *node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	void attach(LRUEntry<K, V> *node) {
		node->prev = m_head;
		node->next = m_head->next;
		m_head->next = node;
		node->next->prev = node;
	}
};

typedef string K;
typedef string V;
int main() {
	cout << "put or get" << endl;
	LRUCache<K, V> lru(3);
	while(true) {
		string method;
		V value;
		K key;
		cin >> method;
		if (method == "exit") break;
		cin >> key;
		if (method == "get") {
			value = lru.get(key);
			if (value == V())
				cout << "no such key" << endl;
			else cout << "value: " << value << endl;
			continue;
		}
		cin >> value;
		lru.put(key, value);
	}
	return 0;
}
