#define _CRT_SECURE_NO_WARNINGS 

#include <vector>
#include <fstream>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <cstring>
#include <future>
#include <string>
#include <cctype>

typedef long long ll;

using namespace std;

class student_data {
public:
	char num[11], name[21], sclass[21], tel[12], home[21], hab[101], dom[21];

	friend ostream& operator<<(ostream& out, const student_data& A) {
		out << A.num << " " << A.name << " " << A.sclass << " " << A.tel << " " << A.home << " " << A.hab << " " << A.dom;
		return out;
	}

	~student_data() {}
};
vector<student_data> All_data;

ll numhash(char* goal) {
	int sum = 0, exp = 1;
	for (int i = 0; i < 10; i++) { sum += goal[9 - i] * exp; exp *= 10; }
	return sum;
}

int find_num(char* find) {
	ll num1, num2;
	num1 = numhash(find);
	for (int i = 0; i < All_data.size(); i++) {
		num2 = numhash(All_data[i].num);
		if (num1 == num2) return i;
	}
	return -1;
}

vector<student_data>::iterator itfind_num(char* find) {
	ll num1, num2;
	num1 = numhash(find);
	for (vector<student_data>::iterator i = All_data.begin(); i != All_data.end(); i++) {
		num2 = numhash(i->num);
		if (num1 == num2) return i;
	}
	return All_data.end();
}

namespace CKW {
	vector<student_data> temp_data;
	struct Thread_using_data {
		int lengoal, lendata, begin;
		char* goal;
		int* next;

		Thread_using_data() :begin(0), lengoal(0), lendata(0), next(NULL), goal(NULL) {}

		friend ostream& operator<<(ostream& out, const Thread_using_data& A) {
			out << A.lengoal << " " << A.lendata << " " << A.begin << " " << A.next << " " << A.goal;
			return out;
		}
	};

	void prepare_program() {
		cout << "User data search!" << endl;
		ifstream datain("data.txt");
		if (!datain.is_open()) {
			system("type nul> data.txt");
			system("cls & color F0");
			cout << "Welcome to student information system!" << endl;
		}
		else {
			student_data prepare;
			while (datain >> prepare.num >> prepare.name >> prepare.sclass >> prepare.tel >> prepare.home >> prepare.hab >> prepare.dom) {
				All_data.push_back(prepare);
			}
			cout << "User data read successfully!" << endl;
			system("color F0");
			system("cls");
			cout << "Welcome to student information system!" << endl;
		}
	}

	void KMP_hab(Thread_using_data* p) {
		for (int i = p->begin; i < (p->begin + p->lendata); i++) {
			int len = strlen(All_data[i].hab);
			char*& A = p->goal;
			if (len < p->lengoal - 1) continue;
			int k = 0;
			for (int j = 0; j < len; j++) {
				while (k > 0 && A[k + 1] != All_data[i].hab[j]) {
					k = p->next[k];
				}
				if (A[k + 1] == All_data[i].hab[j]) {
					k++;
				}
				if (p->lengoal - 1 == k) {
					temp_data.push_back(All_data[i]);
					break;
				}
			}
		}

	}

	void KMP_name(Thread_using_data* p) {
		for (int i = p->begin; i < (p->begin + p->lendata); i++) {
			int len = strlen(All_data[i].name);
			char*& A = p->goal;
			if (len < p->lengoal - 1) continue;
			int k = 0;
			for (int j = 0; j < len; j++) {
				while (k > 0 && A[k + 1] != All_data[i].name[j]) {
					k = p->next[k];
				}
				if (A[k + 1] == All_data[i].name[j]) {
					k++;
				}
				if (p->lengoal - 1 == k) {
					temp_data.push_back(All_data[i]);
					break;
				}
			}
		}

	}

	void KMP_dom(Thread_using_data* p) {
		for (int i = p->begin; i < (p->begin + p->lendata); i++) {
			int len = strlen(All_data[i].dom);
			char*& A = p->goal;
			if (len < p->lengoal - 1) continue;
			int k = 0;
			for (int j = 0; j < len; j++) {
				while (k > 0 && A[k + 1] != All_data[i].dom[j]) {
					k = p->next[k];
				}
				if (A[k + 1] == All_data[i].dom[j]) {
					k++;
				}
				if (p->lengoal - 1 == k) {
					temp_data.push_back(All_data[i]);
					break;
				}
			}
		}

	}

	void KMP_class(Thread_using_data* p) {
		for (int i = p->begin; i < (p->begin + p->lendata); i++) {
			int len = strlen(All_data[i].sclass);
			char*& A = p->goal;
			if (len < p->lengoal - 1) continue;
			int k = 0;
			for (int j = 0; j < len; j++) {
				while (k > 0 && A[k + 1] != All_data[i].sclass[j]) {
					k = p->next[k];
				}
				if (A[k + 1] == All_data[i].sclass[j]) {
					k++;
				}
				if (p->lengoal - 1 == k) {
					temp_data.push_back(All_data[i]);
					break;
				}
			}
		}

	}

	void KMP_home(Thread_using_data* p) {
		for (int i = p->begin; i < (p->begin + p->lendata); i++) {
			int len = strlen(All_data[i].home);
			char*& A = p->goal;
			if (len < p->lengoal - 1) continue;
			int k = 0;
			for (int j = 0; j < len; j++) {
				while (k > 0 && A[k + 1] != All_data[i].home[j]) {
					k = p->next[k];
				}
				if (A[k + 1] == All_data[i].home[j]) {
					k++;
				}
				if (p->lengoal - 1 == k) {
					temp_data.push_back(All_data[i]);
					break;
				}
			}
		}

	}

	void KMP_front_array(char* goal, int len, int* next) {
		next[1] = next[0] = 0;
		int m = 0;
		for (int i = 2; i < len; i++) {
			while (m > 0 && goal[m + 1] != goal[i]) {
				m = next[m];
			}
			if (goal[m + 1] == goal[i]) {
				m++;
			}
			next[i] = m;
		}
	}

	void threadsearch_hab(char* goal, int len, int* next) {
		KMP_front_array(goal, len, next);
		int CPU_num = thread::hardware_concurrency();
		Thread_using_data Thread_data[8];
		std::thread using_Thread[8];
		Thread_data[0].lengoal = len;
		Thread_data[0].lendata = (All_data.size() / 8) + All_data.size() % 8;
		Thread_data[0].goal = goal;
		Thread_data[0].next = next;
		for (int i = 1; i < 8; i++) {
			Thread_data[i].lengoal = len;
			Thread_data[i].lendata = (All_data.size() / 8);
			Thread_data[i].goal = goal;
			Thread_data[i].next = next;
			Thread_data[i].begin = (All_data.size() / 8 * i) + All_data.size() % 8;
		}
		for (int i = 0; i < 8; i++) {
			using_Thread[i] = std::thread(KMP_hab, &Thread_data[i]);
		}
		static mutex m;
		for (int i = 0; i < 8; i++) {
			using_Thread[i].join();
		}
		lock_guard<mutex> lusg(m);

		if (temp_data.size() == 0) {
			cout << "No one have this habit" << endl;
		}
		else {
			for (int i = 0; i < temp_data.size(); i++) {
				cout << temp_data[i] << endl;
			}
		}
		temp_data.clear();
	}

	void threadsearch_name(char* goal, int len, int* next) {

		KMP_front_array(goal, len, next);
		int CPU_num = thread::hardware_concurrency();
		Thread_using_data Thread_data[8];
		std::thread using_Thread[8];
		Thread_data[0].lengoal = len;
		Thread_data[0].lendata = (All_data.size() / 8) + All_data.size() % 8;
		Thread_data[0].goal = goal;
		Thread_data[0].next = next;
		for (int i = 1; i < 8; i++) {
			Thread_data[i].lengoal = len;
			Thread_data[i].lendata = (All_data.size() / 8);
			Thread_data[i].goal = goal;
			Thread_data[i].next = next;
			Thread_data[i].begin = (All_data.size() / 8 * i) + All_data.size() % 8;
		}
		for (int i = 0; i < 8; i++) {
			using_Thread[i] = std::thread(KMP_name, &Thread_data[i]);
		}
		static mutex m;
		for (int i = 0; i < 8; i++) {
			using_Thread[i].join();
		}
		lock_guard<mutex> lusg(m);

		if (temp_data.size() == 0) {
			cout << "No one have this name" << endl;
		}
		else {
			cout << "This student's telephone number is" << endl;
			for (int i = 0; i < temp_data.size(); i++) {
				cout << temp_data[i].tel << endl;
			}
		}
		temp_data.clear();
	}

	void threadsearch_dom(char* goal, int len, int* next) {
		KMP_front_array(goal, len, next);
		int CPU_num = thread::hardware_concurrency();
		Thread_using_data Thread_data[8];
		std::thread using_Thread[8];
		Thread_data[0].lengoal = len;
		Thread_data[0].lendata = (All_data.size() / 8) + All_data.size() % 8;
		Thread_data[0].goal = goal;
		Thread_data[0].next = next;
		for (int i = 1; i < 8; i++) {
			Thread_data[i].lengoal = len;
			Thread_data[i].lendata = (All_data.size() / 8);
			Thread_data[i].goal = goal;
			Thread_data[i].next = next;
			Thread_data[i].begin = (All_data.size() / 8 * i) + All_data.size() % 8;
		}
		for (int i = 0; i < 8; i++) {
			using_Thread[i] = std::thread(KMP_dom, &Thread_data[i]);
		}
		static mutex m;
		for (int i = 0; i < 8; i++) {
			using_Thread[i].join();
		}
		lock_guard<mutex> lusg(m);

		if (temp_data.size() == 0) {
			cout << "No one in this dromitory" << endl;
		}
		else {
			cout << "These student live in this dromitory" << endl;
			for (int i = 0; i < temp_data.size(); i++) {
				cout << temp_data[i] << endl;
			}
		}
		temp_data.clear();
	}

	void threadsearch_home(char* goal, int len, int* next) {
		KMP_front_array(goal, len, next);
		int CPU_num = thread::hardware_concurrency();
		Thread_using_data Thread_data[8];
		std::thread using_Thread[8];
		Thread_data[0].lengoal = len;
		Thread_data[0].lendata = (All_data.size() / 8) + All_data.size() % 8;
		Thread_data[0].goal = goal;
		Thread_data[0].next = next;
		for (int i = 1; i < 8; i++) {
			Thread_data[i].lengoal = len;
			Thread_data[i].lendata = (All_data.size() / 8);
			Thread_data[i].goal = goal;
			Thread_data[i].next = next;
			Thread_data[i].begin = (All_data.size() / 8 * i) + All_data.size() % 8;
		}
		for (int i = 0; i < 8; i++) {
			using_Thread[i] = std::thread(KMP_home, &Thread_data[i]);
		}
		static mutex m;
		for (int i = 0; i < 8; i++) {
			using_Thread[i].join();
		}
		lock_guard<mutex> lusg(m);

		if (temp_data.size() == 0) {
			cout << "No student in town" << endl;
		}
		else {
			cout << "This town have these student" << endl;
			for (int i = 0; i < temp_data.size(); i++) {
				cout << temp_data[i] << endl;
			}
		}
		temp_data.clear();
	}

	void threadsearch_class(char* goal, int len, int* next) {
		KMP_front_array(goal, len, next);
		int CPU_num = thread::hardware_concurrency();
		Thread_using_data Thread_data[8];
		std::thread using_Thread[8];
		Thread_data[0].lengoal = len;
		Thread_data[0].lendata = (All_data.size() / 8) + All_data.size() % 8;
		Thread_data[0].goal = goal;
		Thread_data[0].next = next;
		for (int i = 1; i < 8; i++) {
			Thread_data[i].lengoal = len;
			Thread_data[i].lendata = (All_data.size() / 8);
			Thread_data[i].goal = goal;
			Thread_data[i].next = next;
			Thread_data[i].begin = (All_data.size() / 8 * i) + All_data.size() % 8;
		}

		for (int i = 0; i < 8; i++) {
			using_Thread[i] = std::thread(KMP_class, &Thread_data[i]);
		}

		static mutex m;
		for (int i = 0; i < 8; i++) {
			using_Thread[i].join();
		}

		lock_guard<mutex> lusg(m);

		if (temp_data.size() == 0) {
			cout << "No one in class" << endl;
		}
		else {
			cout << "This class's student data" << endl;
			for (int i = 0; i < temp_data.size(); i++) {
				cout << temp_data[i] << endl;
			}
		}
		temp_data.clear();
	}
}

int main() {

	CKW::prepare_program();

	ifstream helpin("help.txt");                           //relate with help.txt
	if (!helpin.is_open()) {
		MessageBoxA(0, "Error", "help.txt file is not found in scope!", 0);
		exit(EXIT_FAILURE);
	}
	else {
		char c[100];
		while (helpin.getline(c, 100)) {
			cout << c << endl;
		}
	}
	helpin.close();

	while (1) {
		string s;
		cin >> s;

		if (s == "exit") {
			ofstream outdata("data.txt");                    //cover the old data.
			for (int i = 0; i < All_data.size(); i++) {
				outdata << All_data[i] << endl;
			}
			outdata.close();
			break;
		}
		if (s == "help") {
			helpin.open("help.txt");
			if (!helpin.is_open()) {
				MessageBoxA(0, "Error", "help.txt file is not found in scope!", 0);
				exit(EXIT_FAILURE);
			}
			else {
				cout << "Welcome to student information system!" << endl;
				char c[100];
				while (helpin.getline(c, 100)) {
					cout << c << endl;
				}
			}
			helpin.close();
		}
		else {
			if (s == "0") {
				cout << "please input the student information in order" << endl;
				cout << "(number)(name)(class)(telephone number)(hometown)(hobby)(dromity)" << endl;
				student_data temp;
				cin >> temp.num;
				if (strlen(temp.num) != 10) {
					MessageBoxA(0, "student number formal incorrect", "Warning", 0);
				}
				else {
					if (find_num(temp.num) == -1 && !All_data.empty()) {
						MessageBoxA(0, "the student number is repeat!", "Warning", 0);
					}
					else {
						cin >> temp.name >> temp.sclass >> temp.tel >> temp.home >> temp.hab >> temp.dom;
						All_data.push_back(temp);
						cout << "student data have been inputed!" << endl;
					}
				}
			}
			if (s == "1") {
				if (All_data.empty()) {
					MessageBoxA(0, "User data is empty!", "Error", 0);
				}
				else {
					cout << "please input the student number:" << endl;
					char fnum[10];
					cin >> fnum;
					if (strlen(fnum) != 10) {
						MessageBoxA(0, "student number formal incorrect", "Warning", 0);
					}
					else {
						int pos = find_num(fnum);
						if (pos == -1) {
							cout << "No student this number" << endl;
						}
						else {
							cout << "please input the new class" << endl;
							memset(All_data[pos].sclass, '\0', sizeof(All_data[pos].sclass));
							cin >> All_data[pos].sclass;
							cout << "class information transfer successfully!" << endl;
						}
					}
				}
			}
			if (s == "2") {
				if (All_data.empty()) {
					MessageBoxA(0, "User data is empty!", "Error", 0);
				}
				else {
					cout << "please input the student number:" << endl;
					char fnum[10];
					cin >> fnum;
					if (strlen(fnum) != 10) {
						MessageBoxA(0, "student number formal incorrect", "Warning", 0);
					}
					else {
						int pos = find_num(fnum);
						if (pos == -1) {
							cout << "No student have this number" << endl;
						}
						else {
							cout << "please input new telephone" << endl;
							memset(All_data[pos].tel, '\0', sizeof(All_data[pos].tel));
							cin >> All_data[pos].tel;
							cout << "student telephone transfer successfully!" << endl;
						}
					}
				}
			}
			if (s == "3") {
				if (All_data.empty()) {
					MessageBoxA(0, "User data is empty!", "Error", 0);
				}
				else {
					cout << "please input the student number:" << endl;
					char fnum[10];
					cin >> fnum;
					if (strlen(fnum) != 10) {
						MessageBoxA(0, "student number formal incorrect", "Warning", 0);
					}
					else {
						int pos = find_num(fnum);
						if (pos == -1) {
							cout << "No student have this number" << endl;
						}
						else {
							cout << "please input the new dromitory" << endl;
							memset(All_data[pos].dom, '\0', sizeof(All_data[pos].dom));
							cin >> All_data[pos].dom;
							cout << "student dromitory information transfer successfully!" << endl;
						}
					}
				}
			}
			if (s == "4") {
				char fhab[22], pre[21];
				int len, next[22];
				fhab[0] = '0';
				cout << "please input dromitory" << endl;
				cin >> pre;
				for (int i = 0; i < strlen(pre); i++) {
					fhab[i + 1] = pre[i];
				}
				fhab[strlen(pre) + 1] = '\0';
				len = strlen(fhab);
				CKW::threadsearch_dom(fhab, len, next);
			}
			if (s == "5") {
				char fhab[22], pre[21];
				int len, next[22];
				fhab[0] = '0';
				cout << "please input class" << endl;
				cin >> pre;
				for (int i = 0; i < strlen(pre); i++) {
					fhab[i + 1] = pre[i];
				}
				fhab[strlen(pre) + 1] = '\0';
				len = strlen(fhab);
				CKW::threadsearch_class(fhab, len, next);
			}
			if (s == "6") {
				char fhab[102], pre[101];
				int len, next[102];
				fhab[0] = '0';
				cout << "please input hobby" << endl;
				cin >> pre;
				for (int i = 0; i < strlen(pre); i++) {
					fhab[i + 1] = pre[i];
				}
				fhab[strlen(pre) + 1] = '\0';
				len = strlen(fhab);
				CKW::threadsearch_hab(fhab, len, next);
			}
			if (s == "7") {
				char fhab[12], pre[11];
				int len, next[12];
				fhab[0] = '0';
				cout << "please input name" << endl;
				cin >> pre;
				for (int i = 0; i < strlen(pre); i++) {
					fhab[i + 1] = pre[i];
				}
				fhab[strlen(pre) + 1] = '\0';
				len = strlen(fhab);
				CKW::threadsearch_name(fhab, len, next);
			}
			if (s == "8") {
				char fhab[22], pre[21];
				int len, next[22];
				fhab[0] = '0';
				cout << "please input hometown" << endl;
				cin >> pre;
				for (int i = 0; i < strlen(pre); i++) {
					fhab[i + 1] = pre[i];
				}
				fhab[strlen(pre) + 1] = '\0';
				len = strlen(fhab);
				CKW::threadsearch_home(fhab, len, next);
			}
			if (s == "9") {
				if (All_data.empty()) {
					MessageBoxA(0, "User data is empty!", "Error", 0);
				}
				else {
					cout << "All students' informations：" << endl;
					for (int i = 0; i < All_data.size(); i++) {
						cout << All_data[i] << endl;
					}
				}
			}
			if (s == "10") {
				if (All_data.empty()) {
					MessageBoxA(0, "User data is empty!", "Error", 0);
				}
				else {
					cout << "please input the student number:" << endl;
					char fnum[10];
					cin >> fnum;
					if (strlen(fnum) != 10) {
						MessageBoxA(0, "student number formal incorrect", "Warning", 0);
					}
					else {
						vector<student_data>::iterator pos = itfind_num(fnum);
						if (pos == All_data.end()) {
							cout << "No student have this number!" << endl;
						}
						else {
							All_data.erase(pos);
							cout << "successfully delete data!" << endl;
						}
					}
				}
			}
		}
	}
	return 0;
}
