#include "../Map.h"

using namespace std;

int main()
{
    cout << endl << "-- Test 1: Construct default map --" << endl;
    Map<string, string> mappu;

    cout << endl << "-- Test 2: Insert --" << endl;
    Map<string, string> nami(2);
    cout << "Insert Greetings:Hello World";
    nami.Insert("Greetings", "Hello World");

    cout << endl << "-- Test 3: Search for key --" << endl;
    cout << "Greetings key exist: " << nami.Search("Greetings") << endl;

    cout << endl << "-- Test 4: Get Value --" << endl;
    const string* tempstr = nami.GetValue("Greetings");
    cout << "Greetings:" << *tempstr << endl;

    cout << endl << "-- Test 5: ReplaceValue --" << endl;
    nami.ReplaceValue("Greetings", "Hi");
    const string* tempstr2 = nami.GetValue("Greetings");
    cout << "Greetings: " << *tempstr2 << endl;



    return 0;
}
