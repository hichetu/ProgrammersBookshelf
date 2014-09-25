#include "stdafx.h"

namespace MergeKSortedLists
{
    struct ListNode
    {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr)
        {
        }
    };
    /**
    * Definition for singly-linked list.
    * struct ListNode {
    *     int val;
    *     ListNode *next;
    *     ListNode(int x) : val(x), next(NULL) {}
    * };
    */
    class Solution
    {
    public:
        ListNode *mergeKLists(vector<ListNode *> &lists)
        {
            while (lists.size() >= 2)
            {
                ListNode* l1 = lists[0];
                ListNode* l2 = lists[1];
                lists.erase(lists.begin(), lists.begin() + 2);
                if (l1 == nullptr || l2 == nullptr)
                {
                    if (l1 != nullptr)
                    {
                        lists.push_back(l1);
                    }
                    else if (l2 != nullptr)
                    {
                        lists.push_back(l2);
                    }
                }
                else
                {
                    lists.push_back(MergeList(l1, l2));
                }
            }
            if (lists.size() == 0)
            {
                return nullptr;
            }
            else
            {
                return lists[0];
            }
        }

        ListNode* MergeList(ListNode* head, ListNode* back)
        {
            ListNode* curList;
            if (head->val <= back->val)
            {
                curList = head;
                head = head->next;
            }
            else
            {
                curList = back;
                back = back->next;
            }

            ListNode* listFront = curList;
            while (head != nullptr && back != nullptr)
            {
                if (head->val <= back->val)
                {
                    curList->next = head;
                    head = head->next;
                }
                else
                {
                    curList->next = back;
                    back = back->next;
                }
                curList = curList->next;
            }
            while (head != nullptr)
            {
                curList->next = head;
                head = head->next;
                curList = curList->next;
            }
            while (back != nullptr)
            {
                curList->next = back;
                back = back->next;
                curList = curList->next;
            }
            curList->next = nullptr;
            return listFront;
        }
    };

    void RunTests()
    {
        Solution s;
        ListNode a1(1);
        ListNode a2(2);
        ListNode a3(3);
        ListNode a4(4);
        ListNode a5(5);
        ListNode a6(6);
        ListNode a7(7);
        ListNode a8(8);
        ListNode a9(9);

        // Empty vector
        vector<ListNode*> emptyVector;
        ListNode* emptyVectorResult = s.mergeKLists(emptyVector);
        _ASSERT(emptyVectorResult == nullptr);

        // Empty lists in vector
        vector<ListNode*> emptyLists;
        emptyLists.push_back(nullptr);
        emptyLists.push_back(nullptr);
        ListNode* emptyListsResult = s.mergeKLists(emptyLists);
        _ASSERT(emptyListsResult == nullptr);

        // Two simple lists
        vector<ListNode*> twoSimple;
        a1.next = nullptr;
        a2.next = nullptr;
        twoSimple.push_back(&a1);
        twoSimple.push_back(&a2);
        ListNode* twoSimpleResult = s.mergeKLists(twoSimple);
        _ASSERT(twoSimpleResult == &a1);
        _ASSERT(twoSimpleResult->next == &a2);
    }
};