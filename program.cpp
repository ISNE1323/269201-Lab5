#include <iostream>
#include <sstream>
#include <string>
#include "list.h"
using namespace std;

int passed = 0, failed = 0;

void check(const string& what, bool ok)
{
	if (ok){
		cout << "  [PASS] " << what << endl;
		passed++;
	}else{
		cout << "  [FAIL] " << what << endl;
		failed++;
	}
}

template<class T>
void expectList(const string& what, const List<T>& list, const string& forward, const string& backward){
	ostringstream f, b;
	list.print(f);
	list.printReverse(b);
	if (f.str() == forward && b.str() == backward){
		check(what + "  ->  " + f.str() + "   (backwards: " + b.str() + ")", true);
	}else{
		check(what, false);
		cout << "         expected: " << forward << "   (backwards: " << backward << ")" << endl;
		cout << "         got:      " << f.str() << "   (backwards: " << b.str() << ")" << endl;
	}
}

int main(){
	cout << "Test 1: list of char" << endl;
	
    List<char> mylist;
	mylist.pushToHead('k');
	mylist.pushToHead('e');
	mylist.pushToHead('n');
	expectList("pushToHead k, e, n", mylist, "n e k", "k e n");

	mylist.pushToTail('s');
	expectList("pushToTail s", mylist, "n e k s", "s k e n");

	check("search('e') finds a letter in the middle", mylist.search('e'));
	check("search('n') finds the first letter", mylist.search('n'));
	check("search('s') finds the last letter", mylist.search('s'));
	check("search('z') is false for a letter that is not there", !mylist.search('z'));

	check("popHead() returns 'n'", mylist.popHead() == 'n');
	expectList("list after popHead", mylist, "e k s", "s k e");

	check("popTail() returns 's'", mylist.popTail() == 's');
	expectList("list after popTail", mylist, "e k", "k e");

	check("popTail() returns 'k'", mylist.popTail() == 'k');
	expectList("one node left", mylist, "e", "e");

	check("popHead() on the last node returns 'e'", mylist.popHead() == 'e');
	check("list is empty now", mylist.isEmpty());
	expectList("printing an empty list", mylist, "(empty)", "(empty)");

	cout << endl << "Test 2: empty list and one node (list of int)" << endl;
	
    List<int> nums;
	check("a new list is empty", nums.isEmpty());
	check("search on an empty list is false", !nums.search(5));
	check("popHead on an empty list returns 0 and does not crash", nums.popHead() == 0);
	check("popTail on an empty list returns 0 and does not crash", nums.popTail() == 0);

	nums.pushToTail(7);                 
	expectList("pushToTail 7 on an empty list", nums, "7", "7");
	nums.pushToHead(3);
	expectList("pushToHead 3", nums, "3 7", "7 3");
	nums.pushToTail(9);
	expectList("pushToTail 9", nums, "3 7 9", "9 7 3");

	cout << endl << "Test 3: emptying a list from both ends (list of int)" << endl;
	List<int> line;
	for (int i = 1; i <= 5; i++)
		line.pushToTail(i);
	expectList("pushToTail 1..5", line, "1 2 3 4 5", "5 4 3 2 1");

	check("popHead() returns 1", line.popHead() == 1);
	check("popTail() returns 5", line.popTail() == 5);
	check("popHead() returns 2", line.popHead() == 2);
	check("popTail() returns 4", line.popTail() == 4);
	expectList("only the middle is left", line, "3", "3");
	
    check("popTail() returns 3", line.popTail() == 3);
	check("list is empty again", line.isEmpty());

	line.pushToHead(42);                
	line.pushToTail(43);
	expectList("the list can be used again after it was emptied", line, "42 43", "43 42");

	cout << endl << "Test 4: list of string" << endl;
	
    List<string> words;
	words.pushToTail("apple");
	words.pushToTail("banana");
	words.pushToHead("cherry");
	
    expectList("cherry, apple, banana", words, "cherry apple banana", "banana apple cherry");
	check("search(\"apple\") is true", words.search("apple"));
	check("search(\"grape\") is false", !words.search("grape"));
	check("popTail() returns \"banana\"", words.popTail() == "banana");
	check("popHead() returns \"cherry\"", words.popHead() == "cherry");
	expectList("only apple is left", words, "apple", "apple");

	cout << endl << "Passed: " << passed << "   Failed: " << failed << endl;
	
    if (failed == 0)
		cout << "All tests passed!" << endl;

	return failed == 0 ? 0 : 1;
}