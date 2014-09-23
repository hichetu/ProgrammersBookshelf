#include "stdafx.h"

namespace ReorderList
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
        void reorderList(ListNode *head)
        {
            // Don't bother reversing unless we have 3 entries
            if (head != nullptr && head->next != nullptr && head->next->next != nullptr)
            {
                ListNode* mid = splitList(head);
                ListNode* secondHalf = mid->next;
                mid->next = nullptr;

                secondHalf = reverseList(secondHalf);
                mergeLists(head, secondHalf);
            }
        }
        ListNode* splitList(ListNode* head)
        {
            ListNode* slow = head;
            ListNode* fast = head->next;

            while (fast != nullptr && fast->next != nullptr)
            {
                fast = fast->next->next;
                slow = slow->next;
            }
            return slow;
        }
        ListNode* reverseList(ListNode* head)
        {
            ListNode* prev = nullptr;
            ListNode* current = head;
            ListNode* next = nullptr;
            while (current != nullptr)
            {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            return prev;
        }
        ListNode* mergeLists(ListNode* list1, ListNode* list2)
        {
            ListNode* head = list1;
            ListNode* current = head;
            list1 = list1->next;

            while (list1 != nullptr || list2 != nullptr)
            {
                if (list2 != nullptr)
                {
                    current->next = list2;
                    current = current->next;
                    list2 = list2->next;
                }
                if (list1 != nullptr)
                {
                    current->next = list1;
                    current = current->next;
                    list1 = list1->next;
                }
            }
            return head;
        }
    };

    void RunTests()
    {
        Solution s;
        ListNode l1(1);
        ListNode l2(2);
        ListNode l3(3);
        ListNode l4(4);
        ListNode l5(5);

        // Make sure empty lists work
        s.reorderList(nullptr);

        // Single lists
        l1.next = nullptr;
        s.reorderList(&l1);

        // Two entry lists
        l1.next = &l2;
        l2.next = nullptr;
        s.reorderList(&l1);
        _ASSERT(l1.next == &l2);
        _ASSERT(l2.next == nullptr);

        // Three entry lists
        l1.next = &l2;
        l2.next = &l3;
        l3.next = nullptr;

        s.reorderList(&l1);
        _ASSERT(l1.next == &l3);
        _ASSERT(l3.next == &l2);

        // Five entry lists
        l1.next = &l2;
        l2.next = &l3;
        l3.next = &l4;
        l4.next = &l5;

        s.reorderList(&l1);
        _ASSERT(l1.next == &l5);
        _ASSERT(l2.next == &l4);
        _ASSERT(l3.next == nullptr);
        _ASSERT(l5.next == &l2);
        _ASSERT(l4.next == &l3);
    }
};