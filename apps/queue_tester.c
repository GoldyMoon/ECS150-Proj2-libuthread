#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <queue.h>

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue/Dequeue simple */
void test_queue_simple(void)
{
	int data = 3, *ptr;
	queue_t q;

	fprintf(stderr, "*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);
}

/* Callback function that increments items */
static void iterator_inc(queue_t q, void *data)
{
    int *a = (int*)data;

    if (*a == 42)
        queue_delete(q, data);
    else
        *a += 1;
}

void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
    size_t i;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Increment every item of the queue, delete item '42' */
    queue_iterate(q, iterator_inc);
    assert(data[0] == 2);
    assert(queue_length(q) == 9);
}

void test_queue_simple2(void) {
	int data = 3, *ptr;
	queue_t q;
	
	fprintf(stderr, "*** TEST queue_simple2 ***\n");
	q = queue_create();
	TEST_ASSERT(queue_enqueue(q, &data) == 0);
	TEST_ASSERT(queue_dequeue(q, (void**)&ptr) == 0);
	TEST_ASSERT(*ptr == 3);
	TEST_ASSERT(queue_length(q) == 0);
	TEST_ASSERT(queue_dequeue(NULL, (void**)&ptr) == -1);
	TEST_ASSERT(queue_dequeue(q, NULL) == -1);
	queue_destroy(q);
	printf("test_queue1 done!\n");
}

void test_delete()
{
	fprintf(stderr, "*** TEST queue_delete ***\n");
	queue_t q;
	int data[] = {1,2,3,4,5,6,7,42};
	size_t i;
	q = queue_create();
	for (i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
		queue_enqueue(q, &data[i]);
	}
	TEST_ASSERT(queue_length(q) == 8);
	TEST_ASSERT(queue_delete(q, &data[0]) == 0);
	TEST_ASSERT(queue_length(q) == 7);
	TEST_ASSERT(queue_delete(q, &data[1]) == 0);
	TEST_ASSERT(queue_length(q) == 6);
	TEST_ASSERT(queue_delete(q, &data[2]) == 0);
	TEST_ASSERT(queue_length(q) == 5);
	TEST_ASSERT(queue_delete(q, &data[7]) == 0);  // delete last element
	TEST_ASSERT(queue_length(q) == 4);
	TEST_ASSERT(queue_delete(q, &data[7]) == 0);  // delete element that non-exist
	TEST_ASSERT(queue_length(q) == 4);  // nothing should be deleted and size should be the same
	printf("test_delete done!\n");
}

int main(void)
{
	test_create();
	test_queue_simple();
	test_iterator();
	test_queue_simple2();
	test_delete();
	printf("All test done! 帅!");
	return 0;
}