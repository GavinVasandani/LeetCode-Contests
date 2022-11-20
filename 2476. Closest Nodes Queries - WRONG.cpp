/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    //Below is a method which takes in root and queries
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        //Assume tree is already built:
        //Must be recursive:
        vector<vector<int>> answer;
        for (int i=0; i<queries.size(); i++) {
            answer.push_back(vector<int>());
            answer[i].push_back(minI(root,queries[i],-1));
            answer[i].push_back(maxI(root,queries[i],-1));
            }//if currentClose stays 0 then no value less than so -1
        return answer; 
        }

    //Go over what currentClose is initially assigned to, maybe 0.
    //CurrentClose must be smaller than i
    int minI (TreeNode* root, int i, int currentClose) {
    //Recursive function
        //Base case is leaf: //If leaf reached then no equivalence
        if (!root) {
            return currentClose;
        }
        
        if (i==root->val) {
            //Follow 1 path down, if reach leaf then no equal but store closest value
            return i; //Return as no better than having exact value
        }
        else if (i < root->val) {
            //currentClose = root->val; //Should be evaluated in a conditional:
            return minI(root->left, i, currentClose);
        }
        //if i>root->val that is when we can have currentClose reassignment in minI
        else { //so val at parent node or child we go to in BST will always be better/closer than child which isnt traversed to
            
            if (i-root->val < i-currentClose) { //So smaller difference:
                currentClose = root->val;
            }
            return minI(root->right, i, currentClose);
        }
    }

    int maxI (TreeNode* root, int i, int currentClose) {
        if (!root) {
            return currentClose;
        }
        
        if (i==root->val) {
            return i;
        }
        
        else if (root->val < i) {
            //currentClose = root->val; //Should be evaluated in a conditional:
            return maxI(root->right, i, currentClose);
        }
        //maxI outputs root->val that is closest but greater than i:
        else { //all root->val after this conditional are greater than i, so whichever is smaller is better
            if (currentClose == -1) { //so if initially 0 then set value to root->val
                currentClose = root->val;
            }
            if (root->val-i < currentClose-i) {
                currentClose = root->val;
            }
            return maxI(root->left, i, currentClose);
        }
    }

};