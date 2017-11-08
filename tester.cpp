#include <unordered_map>
#include<fstream>
#include <functional> // For hash<string>.
#include <string>
#include <iostream>
#include<vector>
using namespace std;
int main() {


    vector<string> v;
    string s;
    ifstream f("random.txt");
    while(f)
    {
        f>>s;
        v.push_back(s);

    }
    // Hash function for the hashtable.
    auto h = [](const string* s) {
        return hash<string>()(*s);
    };

    // Equality comparer for the hashtable.
    auto eq = [](const string* s1, const string* s2) {
        return s1->compare(*s2) == 0;
    };

    // The hashtable:
    //      Key: Pointer to element of 'v'.
    //      Value: Occurrence count.
    unordered_map<const string*, size_t, decltype(h), decltype(eq)> m(v.size(), h, eq);

    // Count occurances.
    for (auto v_i = v.cbegin(); v_i != v.cend(); ++v_i)
        ++m[&(*v_i)];

    // Print strings that occur more than once:
    for (auto m_i = m.begin(); m_i != m.end(); ++m_i)
        if (m_i->second > 1)
            cout << *m_i->first << ": " << m_i->second << endl;

    return 0;

}
