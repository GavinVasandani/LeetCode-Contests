/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <queue>

struct treeNode {
    int val;
    treeNode* left = nullptr;
    treeNode* right = nullptr;
    int subHighestVal;
};

class Solution {
public:
    
    int subHighestVal (treeNode* t) {
        
        if (!t) {
            return 0;
        }
        else {
            return t->subHighestVal;
        }
        
    }
    
    void listToQueue(ListNode* head, queue<int>& listVals) { //creates vector from linked list node values
        
        if (head) {
            listVals.push(head->val);
            listToQueue(head->next, listVals);
        }
        else {
            return;
        }
    }

    treeNode* treeInsert(treeNode* t, int inpVal) {
        
        //Base Case:
        if(t==nullptr) {
            t = new treeNode; 
            t->val = inpVal;
            t->subHighestVal = inpVal;
            return t;
        }
        
        if (inpVal <= t->val) {
            t->left = treeInsert(t->left, inpVal);
            t->subHighestVal = max(subHighestVal(t->left), subHighestVal(t->right));
        }
        else {
            t->right = treeInsert(t->right, inpVal);
            t->subHighestVal = max(subHighestVal(t->left), subHighestVal(t->right));
        }
        return t;
    } 
    
    treeNode* convertListtoBST(ListNode* head) {
        
        treeNode* t = nullptr;
        queue<int> listVals;
        listToQueue(head, listVals);
        int i;

        while(listVals.size()) {
            i = listVals.front();
            listVals.pop();
            t = treeInsert(t, i);
        }
        return t;
    }
    
    //Function to check parse down right subtree and check if each root has no right subtree then include in LL:
    void checker (treeNode* t, queue<int>& incVal) {
        
        //vector<int> incVal; //vector with values to include in LL
        if(!t) {
            return;
        }
        
        if(t->val >= t->subHighestVal){
            incVal.push(t->val);
        }
        
        if(t->right) {
            checker(t->right, incVal);
        }
        
        if(t->left) {
            checker(t->left, incVal);
        }
    }
    
    ListNode* newLL(queue<int>& incVal) { //outputs address to first node of LL 
        
        //Base Case: if incVal empty:
        if(!incVal.size()) {
            return nullptr; //need to return something, and we have last node on list then next = nullptr so return nullptr in base case
        }
        
        ListNode* l = new ListNode;
        l->val = incVal.front();
        incVal.pop();
        l->next = newLL(incVal);
        return l;
    
    }
    
    ListNode* removeNodes(ListNode* head) {
        
        treeNode* t = convertListtoBST(head);
        queue<int> incVal;
        checker(t, incVal);
        //output incVal has all the nodes to include
        //Parse through LL and deallocate if not incVal:
        //Iterate through list and erase value if in incval:
        return newLL(incVal);
        
    }
    //Should've just done a DP where we iterate through prefix (starting from end and last case is entire array from begin to end) and compare highest value in current array to next val to check. If fine then don't remove
    
};