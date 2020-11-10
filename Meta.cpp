#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

/*---Policy---*/
class setting {
public:
    static const int iterations = 55;
    static double get(vector<double>& v) { //Линейная комбинация с рандомными коэффициентами
        vector<double > coefs(v.size());
        for(auto &i:coefs)
            i = (double)rand()/RAND_MAX;

        double counter = 0;
        for(int i = 0; i != v.size(); i++)
            counter += coefs[i]*v[i];
        return counter;
    }
};

template <class T>
class stream : public T {
public:
    void get(vector<double>& v) {
        ofstream output("output.txt");
        for(int i = 0; i < T::iterations; i++)
        output << T::get(v) << endl;
    }
};
/*~~~Policy~~~*/



/*---find_first_of---*/

template<typename, typename, bool> class ffo;

template <typename InputIt ,typename ForwardIt>
class ffo<InputIt, ForwardIt, true> {
public:
    static int find_first_of(InputIt first1, InputIt last1, ForwardIt first2, ForwardIt last2) {
        cout << "True ";
        for(int counter = 0; first2 != last2; ++first2, ++counter) {
            auto *pos = (InputIt)memchr(&*first1, *first2, &*last1 - &*first1);
            if (pos != nullptr)
                return (pos - first1);
        }
        return -1;
    };
};

template <typename InputIt ,typename ForwardIt>
class ffo<InputIt, ForwardIt, false> {
public:
    static int find_first_of(InputIt first1, InputIt last1, ForwardIt first2, ForwardIt last2){
        cout << "False ";
        auto it = first2;
        for (int counter = 0; first1 != last1; ++first1, ++counter){
            for(;first2 != last2; ++first2) {
                if (*first1 == *first2)
                    return counter;
            }
            first2 = it;
        }
        return -1;
    }
};


template <typename InputIt ,typename ForwardIt>
int do_find_first_of(InputIt first1, InputIt last1, ForwardIt first2, ForwardIt last2) {
    static_assert(is_same< decltype(*declval<InputIt>()), decltype(*declval<ForwardIt>())>::value, "type error!");

    cout
    <<"\nis_trivially_assignable<decltype(*declval<InputIt>()), decltype(*declval<InputIt>())>::value->  "
    << is_trivially_assignable<decltype(*declval<InputIt>()), decltype(*declval<InputIt>())>::value
    << "\nis_trivially_assignable<decltype(*declval<ForwardIt>()), decltype(*declval<ForwardIt>())>::value->  "
    << is_trivially_assignable<decltype(*declval<ForwardIt>()), decltype(*declval<ForwardIt>())>::value
    << "\nis_pointer<InputIt>::value->  "
    << is_pointer<InputIt>::value
    << "\nis_pointer<ForwardIt>::value->  "
    << is_pointer<ForwardIt>::value <<"\n";

    return ffo<InputIt, ForwardIt,
            (is_trivially_assignable<decltype(*declval<InputIt>()), decltype(*declval<InputIt>())>::value &&
             is_trivially_assignable<decltype(*declval<ForwardIt>()), decltype(*declval<ForwardIt>())>::value &&
             is_pointer<InputIt>::value && is_pointer<ForwardIt>::value)>::find_first_of(first1, last1, first2, last2);

}

/*~~~find_first_of~~~*/

int main()
{
    cout << endl;

    /*---Policy---*/

    vector<double> v{ 1.0, 2.0, 3.0, 4.0, 5.0 };
    stream<setting> str;
    str.get(v);

    /*~~~Policy~~~*/

    cout << endl;
    
    /*---find_first_of---*/
    string s("Text!");
    string pat("!");

    char s2[] = "Text!";
    char pat2[] = "T";

    vector<char> s3{'T','e','x','t','!'};
    vector<char> pat3{'e'};

    char *s4 = "Text!";
    char *pat4 = "x";

    string s5("Text!");
    char * pat5 = "t";

    int found1 = do_find_first_of(s.begin(), s.end(), pat.begin(), pat.end());
    if(found1 != -1) {
        cout << s << "   ->   ";
        s.replace(found1, 1, "*");
        cout << s << endl;
    }
    int found2 = do_find_first_of(s2, s2 + strlen(s2), pat2, pat2 + strlen(pat2));
    if(found2 != -1) {
        cout << s2 << "   ->   ";
        s2[found2] = '&';
        cout << s2 << endl;
    }
    int found3 = do_find_first_of(s3.begin(), s3.end(), pat3.begin(), pat3.end());
    if(found3 != -1) {
        for (auto &i : s3) cout << i;
        cout <<"   ->   ";
        s3[found3] = '^';
        for (auto &i : s3) cout << i;
        cout << endl;
    }
    int found4 = do_find_first_of(s4, s4 + strlen(s4), pat4, pat4 + strlen(pat4));
    if(found4 != -1) {
        cout << s4 << "   ->   ";
        string str(s4,s4 + strlen(s4));
        str.replace(found4,1,"!");
        cout << str << endl;
    }

    int found5 = do_find_first_of(s5.begin(), s5.end(), pat5, pat5 + strlen(pat5));
    if(found5 != -1) {
        cout << s5 << "   ->   ";
        s5.replace(found5, 1, "@");
        cout << s5 << endl;
    }

    cout << found1 << "\n" << found2 << "\n" <<  found3 << "\n" <<  found4 << "\n" <<  found5 << endl;

    /*~~~find_first_of~~~*/

    return EXIT_SUCCESS;
}


