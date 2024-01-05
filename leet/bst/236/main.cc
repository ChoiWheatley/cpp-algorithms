/**
 * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree
 * 배열로 만들어진 이진트리였다면 유튜브 영상에서 본 sqrt(N) 방식을
 * 도입했겠지만, 이미 완성된 트리를 인자로 주니까 직접 DFS 순회를 하면서 각
 * root가 p, q를 모두 자식으로 갖는지 여부를 판단하는 수밖에 없음.
 */

#include <iostream>
#include <stdlib.h>
#include <utility>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void printNodes(const std::vector<TreeNode *> &nodes) {
    std::cout << "[ ";
    for (const auto *e : nodes) {
        std::cout << e->val << ", ";
    }
    std::cout << " ]\n";
}

class Solution {
    std::vector<TreeNode *> pParents;
    std::vector<TreeNode *> qParents;
    const TreeNode *p;
    const TreeNode *q;

    void dfs(TreeNode *cur, std::vector<TreeNode *> &trace) {
        if (!cur) {
            return;
        }

        trace.push_back(cur);

        if (cur == this->p) {
            this->pParents = trace; // copy
        }
        if (cur == this->q) {
            this->qParents = trace; // copy
        }

        dfs(cur->left, trace);
        dfs(cur->right, trace);

        trace.pop_back();
    }

  public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        /**
         * DFS 순회하면서 이동경로를 저장하는데, 이때 p 또는 q를 만나면 그
         * 이동경로를 가지고 가장 마지막으로 일치하는 인덱스를 찾는다.
         */
        this->p = p;
        this->q = q;
        auto trace = std::vector<TreeNode *>();
        this->dfs(root, trace);

        printNodes(this->pParents);
        printNodes(this->qParents);

        // pParents와 qParents가 완성되었다. 이제 앞자리서부터 일치하는 val을
        // 찾아보면 된다.
        const size_t plen = this->pParents.size();
        const size_t qlen = this->qParents.size();
        TreeNode *res = root;
        for (size_t i = 1; i < std::min(plen, qlen); ++i) {
            if (this->pParents[i] == this->qParents[i]) {
                res = this->pParents[i];
            }
        }
        return res;
    }
};

int main(void) { return 0; }