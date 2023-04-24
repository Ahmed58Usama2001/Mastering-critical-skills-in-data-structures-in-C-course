#include<iostream>
#include <vector>
#include<cassert>
using namespace std;


int has_num(int value, int n_ = 65407)
{
	long long n = n_;

	return (value % n + n) % n;
}


int hash_string(string str, int n=65407) {
	long long nn = n;
	long long sum = 0;
	for (int i = 0; i < (int)str.size(); ++i)
		sum = (sum * 26 + str[i] - 'a') % nn;
	return sum % nn;
}


int hash_string_lower_upper_digits(string str, int n = 65407)
{
	int base = 26 + 26 + 10;
	long long sum = 0;
	long long n_ = n;

	for (int i = 0; i < str.size(); i++)
	{
		int value = 0;
		if (islower(str[i]))
			value = str[i] - 'a';
		else if (isupper(str[i]))
			value = str[i] - 'A' + 26;
		else if (isdigit(str[i]))
			value = str[i] - '0' + 26 + 10;
		else
			assert(false);

		sum = sum * base + value;
		sum %= n_;
	}
	return sum;
}

int folding_hashing(string str, int n = 65407)
{
	long long n_ = n;
	long long res = 0;
	for (int i = 0; i < str.size(); i += 4)
	{
		res+=hash_string_lower_upper_digits(str.substr(i, 4));
		res %= n_;
	}
	return res ;
}

struct SomeObject
{
	const static int INTERNAL_LIMIT = 65407;
	string str1, str2;
	int number;

	int hash() {
		long long res = hash_string_lower_upper_digits(str1 + str2, INTERNAL_LIMIT);
		res += has_num(number, INTERNAL_LIMIT);
		return res % INTERNAL_LIMIT;
	}

};

struct PhoneEntry {
	const static int INTERNAL_LIMIT = 65407;
	string name;
	string phone_number;

	PhoneEntry(string name, string phome_number) :name(name), phone_number(phone_number) {}
	
	int hash() {
		return hash_string(name, INTERNAL_LIMIT);
	}

	void print() {
		cout << "(" << name << ", " << phone_number << ")  ";
	}

};


class PhoneHashTable {
private:
	int table_size;
	double limit_load_factor;
	int added = 0;
	vector < vector<PhoneEntry>>table;

public:
	PhoneHashTable(int table_size=10,double limit_load_factor=0.75) :
		table_size(table_size) {
		table.resize(table_size);
	}

	bool get(PhoneEntry& phone) {
		int idx = phone.hash() % table_size;

		for (int i = 0; i < (int)table[idx].size(); ++i) {
			if (table[idx][i].name == phone.name) {
				phone = table[idx][i];
				return true;
			}
		}
		return false;
	}


	void put(PhoneEntry phone) {
		int idx = phone.hash() % table_size;

		for (int i = 0; i < (int)table[idx].size(); ++i) {
			if (table[idx][i].name == phone.name) {
				table[idx][i] = phone; 
				return;
			}
		}
		table[idx].push_back(phone);
		added++;
		rehashing();
	}


	bool remove(PhoneEntry phone) {
		int idx = phone.hash() % table_size;
		for (int i = 0; i < (int)table[idx].size(); ++i) {
			if (table[idx][i].name == phone.name) {
				
				swap(table[idx][i], table[idx].back());
				table[idx].pop_back();
				added--;
				return true;
			}
		}
		return false;
	}

	void rehashing()
	{
		double curernt_load_factor = (double)added / table_size;
		if (curernt_load_factor < limit_load_factor)
			return;

		PhoneHashTable new_table(table_size * 2, limit_load_factor);

		for (int hash = 0; hash < table.size(); hash++)
		{
			if (table[hash].size() == 0)
				continue;

			for (int i = 0; i < table[hash].size(); i++)
			{
				new_table.put(table[hash][i]);
			}
		}

		table_size = new_table.table_size;
		table = new_table.table;

		print_all();

	}
	

	void print_all() {
		for (int hash = 0; hash < table_size; ++hash) {
			if (table[hash].size() == 0)
				continue;

			cout << "Hash " << hash << ": ";
			for (int i = 0; i < (int)table[hash].size(); ++i)
				table[hash][i].print();
			cout << "\n";
		}
	}


};

class PhoneHashTable2 {

private:
	struct LinkedHashEntry {
		PhoneEntry item;
		LinkedHashEntry* next{ };

		LinkedHashEntry(PhoneEntry item) : item(item) {
		}
	};

	int table_size;
	vector<LinkedHashEntry*> table{ };

public:
	PhoneHashTable2(int table_size) : table_size(table_size) {
		// vector of linked-lists: initially nulls
		table.resize(table_size);
		// We should destruct too
	}

	void put(PhoneEntry phone) {
		int hash = phone.hash() % table_size;

		if (!table[hash])
			table[hash] = new LinkedHashEntry(phone);
		else {
			LinkedHashEntry* head = table[hash];
			while (head->next) {
				if (head->item.name == phone.name) {
					head->item = phone;	// exist => update
					return;
				}
				head = head->next;
			}
			// head now is tail
			if (head->item.name == phone.name)
				head->item = phone;	// exist => update
			else
				head->next = new LinkedHashEntry(phone);
		}
	}

	void print_all() {
		for (int hash = 0; hash < table_size; ++hash) {
			if (!table[hash])
				continue;

			cout << "Hash " << hash << ": ";
			for (LinkedHashEntry* head = table[hash]; head; head = head->next)
				head->item.print();
			cout << "\n";
		}
	}
};


int main()
{






	return 0;
}