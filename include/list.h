#ifndef __LIST_H__
#define __LIST_H__

template <class T>
class list_node_t;

template <class T>
list_node_t<T> *list_merge(list_node_t<T> *l1, list_node_t<T> *l2);

template <class T>
list_node_t<T> *list_merge_sort(list_node_t<T> *head);

template <class T>
class list_node_t
{
protected:
    list_node_t *next;
    list_node_t *prev;
    T data;

    friend list_node_t<T> *list_merge<T>(list_node_t<T> *l1,
                                         list_node_t<T> *l2);
    friend list_node_t<T> *list_merge_sort<T>(list_node_t<T> *head);

public:
    virtual T getData() { return data; }

    list_node_t(T data)
    {
        next = nullptr;
        prev = nullptr;
        this->data = data;
    }

    list_node_t()
    {
        next = nullptr;
        prev = nullptr;
    }

    virtual ~list_node_t()
    {
        next = nullptr;
        prev = nullptr;
    }

    void reset() { next = prev = nullptr; }

    void setNext(list_node_t *next)
    {
        this->next = next;
        if (next != nullptr) {
            next->prev = this;
        }
    }

    void setPrev(list_node_t *prev)
    {
        this->prev = prev;
        if (prev != nullptr) {
            prev->next = this;
        }
    }

    list_node_t<T> *getNext() { return next; }

    list_node_t<T> *getPrev() { return prev; }
};

template <class T>
list_node_t<T> *list_merge(list_node_t<T> *l1, list_node_t<T> *l2)
{
    if (!l1) {
        return l2;
    }
    if (!l2) {
        return l1;
    }

    list_node_t<T> *result, *result_iter;

    T val1 = l1->getData();
    T val2 = l2->getData();
    if (val1 < val2) {
        result = l1;
        l1 = l1->next;
    } else {
        result = l2;
        l2 = l2->next;
    }

    result_iter = result;
    while (l1 && l2) {
        if (l1->getData() < l2->getData()) {
            result_iter->setNext(l1);
            l1 = l1->next;
        } else {
            result_iter->setNext(l2);
            l2 = l2->next;
        }
        result_iter = result_iter->next;
    }

    if (l1) {
        result_iter->setNext(l1);
    } else if (l2) {
        result_iter->setNext(l2);
    }
    return result;
}

template <class T>
list_node_t<T> *list_merge_sort(list_node_t<T> *head)
{
    if (!head || !head->next) {
        return head;
    } else {
        list_node_t<T> *fast = head->next;
        list_node_t<T> *slow = head;

        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = slow->next;
        fast->prev = nullptr;
        slow->next = nullptr;

        list_node_t<T> *lhs = list_merge_sort(head);
        list_node_t<T> *rhs = list_merge_sort(fast);

        return list_merge(lhs, rhs);
    }
}

#endif