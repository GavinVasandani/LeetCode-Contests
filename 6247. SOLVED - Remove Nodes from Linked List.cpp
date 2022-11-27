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
#include <stack>

class Solution {
public:
    
    void listToStack(ListNode* head, stack<int>& stackVals) {
        
        if (head) {
            stackVals.push(head->val);
            listToStack(head->next, stackVals);
        }
        else {
            return;
        }
    }
    
    ListNode* newLL (ListNode* head, int inpVal) { 
        ListNode* l = new ListNode;
        l->val = inpVal;
        l->next = head;    
        return l;
    }
    
    ListNode* removeNodes(ListNode* head) {
        
        stack<int> stackVals;
        listToStack(head, stackVals);
        int stackVal;
        int maxVal = 0;
        ListNode* remainHead = nullptr;
        
        while (stackVals.size()) { 
            stackVal = stackVals.top();
            stackVals.pop();
            if(stackVal>=maxVal) {
                remainHead = newLL(remainHead, stackVal);
                maxVal = stackVal;
            }
        }
        return remainHead;
        
    }
    
};