#include "stdafx.h"

namespace SortList
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
        ListNode *sortList(ListNode *head)
        {
            MergeSort(&head);
            return head;
        }
        void MergeSort(ListNode** ppHead)
        {
            ListNode* head = *ppHead;
            if (head == nullptr || head->next == nullptr)
            {
                return;
            }

            ListNode* back;
            SplitList(head, &back);

            MergeSort(&head);
            MergeSort(&back);
            *ppHead = MergeList(head, back);
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
        void SplitList(ListNode* head, ListNode** back)
        {
            ListNode* slow = head;
            ListNode* fast = head->next;

            while (fast != nullptr && fast->next != nullptr)
            {
                slow = slow->next;
                fast = fast->next->next;
            }
            *back = slow->next;
            slow->next = nullptr;
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

        ListNode* emptyList = s.sortList(nullptr);
        _ASSERT(emptyList == nullptr);

        a1.next = nullptr;
        ListNode* singleList = s.sortList(&a1);
        s.PrintList(singleList);

        a1.next = &a2;
        a2.next = &a3;
        a3.next = &a4;
        a4.next = &a5;
        a5.next = nullptr;
        ListNode* alreadySorted = s.sortList(&a1);
        s.PrintList(alreadySorted);

        a5.next = &a4;
        a4.next = &a3;
        a3.next = &a2;
        a2.next = &a1;
        a1.next = nullptr;
        ListNode* reverseSort = s.sortList(&a5);
        s.PrintList(reverseSort);
        getchar();
    }
};