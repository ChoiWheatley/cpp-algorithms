/**
https://leetcode.com/problems/implement-trie-prefix-tree
*/

#include <assert.h>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

class Trie {
    struct Node {
        using Dict = unordered_map<char, Node *>;
        char ch;
        Dict dict;
        bool end = false;

        Node(char ch) {
            this->ch = ch;
            this->dict = Dict{};
        }
    };

  private:
    Node *root = nullptr;

  public:
    Trie() { this->root = new Node(0); }

    /**
     * 1. prefix가 없을때까지 내려간다
     * 2. 한 글자씩 Node를 생성하고 그 child를 만든다
     * 3. 마지막 글자인 경우, end를 True로 설정한다
     */
    void insert(string word) {
        auto [cur, i] = this->search_prefix(word);

        // 한 글자씩 Node를 생성하고 child를 만든다
        for (auto iter = word.cbegin() + i; iter != word.cend(); ++iter) {
            const char c = *iter;
            cur->dict[c] = new Node(c);
            cur = cur->dict[c];
        }

        // 마지막 글자에 한해서 end를 true로 설정한다.
        cur->end = true;
    }

    bool search(string word) {
        auto [cur, i] = this->search_prefix(word);
        if (i < word.size() || !cur->end) {
            return false;
        }
        return true;
    }

    bool startsWith(string prefix) {
        auto [cur, i] = this->search_prefix(prefix);
        if (i < prefix.size()) {
            return false;
        }
        return true;
    }

  private:
    /// @brief Trie에 등록돼 있는 word의 마지막 접두어를 찾고 그 인덱스를
    /// 리턴한다
    /// @return [Node *, index]
    pair<Node *, size_t> search_prefix(string word) {
        auto *cur = this->root;
        size_t i = 0;
        size_t wordlen = word.size();

        while (i < wordlen && cur->dict.find(word[i]) != cur->dict.end()) {
            cur = cur->dict[word[i]];
            i++;
        }

        return make_pair(cur, i);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main(int argc, char const *argv[]) {
    const string word = "apple";
    const string prefix = "app";
    Trie *obj = new Trie();
    obj->insert(word);
    assert(obj->search(word));
    assert(obj->startsWith(prefix));
}