#include <bits/stdc++.h>
using namespace std;

vector<string> stream_split(const string& s, char delimiter)
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}


int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        string s{argv[i]};
        auto split { stream_split(s, ' ')};
        for (auto e: split) {
            cout << "elem: '" << e << "'\n";
        }
        cout << '\n';
    }
}
