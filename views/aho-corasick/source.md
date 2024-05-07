## Introduction
<p>The best way to explain this topic is with a problem:</p>

<blockquote>You are given a text T (1 <= |T| <= 1,000,000) and n (1 <= n <= 1000) patterns, each pattern P<sub>i</sub> has at least 1 and at most 500 characters. Find how many times each pattern occurs in T.</blockquote>

<p>Although we can find the number of occurrences of a pattern in linear time (for example, using the <a href="/z-algorithm" target="_blank">Z Algorithm</a>) , there are many patterns and so this approach will not be fast enough to finish in a reasonably amount of time.</p>

<p>In short and as you probably have already guessed, there exist a more efficient solution to this problem than our first attempt, the string matching algorithm invented by Alfred V. Aho and Margaret J. Corasick. I will not try to explain the algorithm because the authors explain it very well in their paper, I'm only going to provide you with an implementation and some practice problems.</p>

<p>This is the paper [Efficient String Matching: An Aid to Bibliographic Search](/aho-corasick/AhoCorasick.pdf)</p>

<p>Usually these papers are very complex and hard to understand without enough background, but to my surprise, this one is well explained and easy to understand.</p>

## Aho-Corasick implementation in C++

```cpp
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

// Maximum number of states, at least as large as the sum of all key word's length.
const int MAX = 505 * 505;

// Alphabet size, 26 for lower case English letters.
const int ALPHA_SIZE = 26 + 1;
const int FAIL = -1;

// Maximum length of the text.
const int MAX_LENGTH = 1000010;

int g[MAX][ALPHA_SIZE];
int f[MAX];
vector<int> output[MAX];
char text[MAX_LENGTH];
int new_state;

void enter(char *word, int index)
{
    int length = strlen(word);
    int j, state = 0;
    for (j = 0; j < length; j++) {
        int c = word[j] - 'a';
        if (g[state][c] == FAIL)
            break;
        state = g[state][c];
    }

    for ( ; j < length; j++) {
        int c = word[j] - 'a';
        new_state++;
        g[state][c] = new_state;
        state = new_state;
    }

    output[state].push_back(index);
}

int main(int argc, char *argv[])
{
    int  n;
    char word[505];
    int count[505];

    scanf("%d", &n);
    scanf("%s", text);

    // Build goto function
    new_state = 0;
    memset(g, -1, sizeof g);
    memset(f, -1, sizeof f);
    for (int i = 0; i < MAX; i++)
        output[i].clear();

    // Read patterns and build the Trie
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        count[i] = 0;
        enter(word, i);
    }

    for (char c = 'a'; c <= 'z'; c++) {
        int a = c - 'a';
        if (g[0][a] == FAIL)
            g[0][a] = 0;
    }

    // Build failure function
    queue<int> Q;
    for (char c = 'a'; c <= 'z'; c++) {
        int a = c - 'a';
        int s = g[0][a];
        if (s != 0) {
            Q.push(s);
            f[s] = 0;
        }
    }

    while (!Q.empty()) {
        int r = Q.front();
        Q.pop();
        for (char c = 'a'; c <= 'z'; c++) {
            int a = c - 'a';
            int s = g[r][a];
            if (s != FAIL) {
                Q.push(s);
                int state = f[r];
                while (g[state][a] == FAIL)
                    state = f[state];
                f[s] = g[state][a];
                for (unsigned k = 0; k < output[f[s]].size(); k++)
                    output[s].push_back(output[f[s]][k]);
            }
        }
    }

    // Count occurrences
    int state = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        int a = text[i] - 'a';
        while (g[state][a] == FAIL)
            state = f[state];
        state = g[state][a];
        for (unsigned k = 0; k < output[state].size(); k++)
            count[output[state][k]]++;
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", count[i]);

    return 0;
}
```

## Practice problems

<ul>
  <li><a href="http://lightoj.com/volume_showproblem.php?problem=1427" target="_blank">Light OJ 1427 - Substring Frequency (II)</a> | <a href="https://gist.github.com/rendon/042fab740fcb859ca34b" target="_blank">My solution</a></li>
  <li><a href="http://codeforces.com/contest/433/problem/E" target="_blank">Codeforces #248 Div 2 E. Tachibana Kanade's Tofu</a> | <a href="https://gist.github.com/rendon/b12375831e143732cb63" target="_blank">My solution</a></li>
</ul>

## References

<%
add_bib('ac', 'Alfred V. Aho and Margaret J. Corasick', 'Efficient String Matching: An Aid to Bibliographic Search', 'http://dl.acm.org/citation.cfm?id=360855');
add_bib('pk', 'Pekka Kilpel ainen', 'Lecture 4: Set Matching and. Aho-Corasick Algorithm', '//www.cs.uku.fi/~kilpelai/BSA05/lectures/slides04.pdf');
%>
<%= generate_bib_table(:en); %>
