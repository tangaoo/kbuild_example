/*
 * Copyright 2006, Red Hat, Inc., Dave Jones
 * Released under the General Public License (GPL).
 *
 * This file contains the linked list implementations for
 * DEBUG_LIST.
 */

#include <log.h>
#include <list.h>

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */

void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	if (next->prev != prev)
		print_warn("list_add corruption. next->prev should be "
			"prev (%p), but was %p. (next=%p).\n",
			prev, next->prev, next);
	if (prev->next != next)
		print_warn("list_add corruption. prev->next should be "
			"next (%p), but was %p. (prev=%p).\n",
			next, prev->next, prev);
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

void __list_del_entry(struct list_head *entry)
{
	struct list_head *prev, *next;

	prev = entry->prev;
	next = entry->next;

	if (next == LIST_POISON1)
		print_warn("list_del corruption, %p->next is LIST_POISON1 (%p)\n",
			entry, LIST_POISON1);
	if (prev == LIST_POISON2)
		print_warn("list_del corruption, %p->prev is LIST_POISON2 (%p)\n",
			entry, LIST_POISON2);
	if (prev->next != entry)
		print_warn("list_del corruption. prev->next should be %p, "
			"but was %p\n", entry, prev->next);
	if (next->prev != entry)
		print_warn("list_del corruption. next->prev should be %p, "
			"but was %p\n", entry, next->prev);

	__list_del(prev, next);
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is
 * in an undefined state.
 */
void list_del(struct list_head *entry)
{
	__list_del_entry(entry);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}
