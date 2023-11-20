#include <iostream>

#include "CustomString.hxx"

using namespace std;

int main(int argc, const char** argv) {
    const char *str1 = "salam";
    const char *str2 = "inja,onja,saeed,biabani";

    auto len = Length(str2); // return lentgh of string
    auto indx = Find(str2, str2+len, ','); // find first index of given element
    auto slice = Slice(str2, 0, indx); //return a slice of given string
    cout << slice << endl; // Output : inja

    auto cat_sep = Concatenate(str1, str2, ','); // concatenate two string with given seperator [str1 + sep + str1]
    cout << cat_sep << endl; // Output : salam,inja,onja,saeed,biabani

    auto cat = Concatenate(str1, str2); // concatenate two string [str1 + str1]
    cout << cat << endl; // Output : salaminja,onja,saeed,biabani

    auto rev = Reverse(str1); // return reverse of given string
    cout << rev << endl; // Output : malas

    auto tokens = Split(str2, ','); //split string by given delimiter
    for (const char *token : tokens) {
        cout << token << endl;
    }

    auto res = Inject(str1, 3, "INJECTED");
    cout << res << endl; // Output : malinjectedam

    return 0;
}