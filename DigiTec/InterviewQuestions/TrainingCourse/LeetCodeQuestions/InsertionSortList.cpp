#include "stdafx.h"

namespace InsertionSortList
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
        ListNode *insertionSortList(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr)
            {
                return head;
            }
            
            ListNode* unsorted = head->next;
            ListNode* sortedHead = head;
            head->next = nullptr;

            while (unsorted != nullptr)
            {
                ListNode* seekPtr = sortedHead;
                
                // Insert the value in the head
                if (unsorted->val < sortedHead->val)
                {
                    sortedHead = unsorted;
                    unsorted = unsorted->next;
                    sortedHead->next = seekPtr;
                }
                else
                {
                    while (seekPtr->next != nullptr && seekPtr->next->val < unsorted->val)
                    {
                        seekPtr = seekPtr->next;
                    }
                    
                    if (seekPtr->next == nullptr)
                    {
                        seekPtr->next = unsorted;
                        unsorted = unsorted->next;
                        seekPtr->next->next = nullptr;
                    }
                    else
                    {
                        ListNode* newUnsorted = unsorted->next;
                        unsorted->next = seekPtr->next;
                        seekPtr->next = unsorted;
                        unsorted = newUnsorted;
                    }
                }
            }
            return sortedHead;
        }
        void PrintList(ListNode* head)
        {
            while (head != nullptr)
            {
                wprintf(L"%d ", head->val);
                head = head->next;
            }
            wprintf(L"\n");
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

        ListNode* emptyList = s.insertionSortList(nullptr);
        _ASSERT(emptyList == nullptr);

        a1.next = nullptr;
        ListNode* singleList = s.insertionSortList(&a1);
        s.PrintList(singleList);

        a1.next = &a2;
        a2.next = &a3;
        a3.next = &a4;
        a4.next = &a5;
        a5.next = nullptr;
        ListNode* alreadySorted = s.insertionSortList(&a1);
        s.PrintList(alreadySorted);

        a5.next = &a4;
        a4.next = &a3;
        a3.next = &a2;
        a2.next = &a1;
        a1.next = nullptr;
        ListNode* reverseSort = s.insertionSortList(&a5);
        s.PrintList(reverseSort);

        // Judge failure
        a4.next = &a2;
        a2.next = &a1;
        a1.next = &a3;
        a3.next = nullptr;
        ListNode* judgeSort1 = s.insertionSortList(&a4);
        s.PrintList(judgeSort1);
        getchar();
    }
};