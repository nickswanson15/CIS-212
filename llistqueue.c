#include "ADTs/llistqueue.h"
#include <stdlib.h>

#define UNUSED __attribute__((unused))
extern void doNothing(UNUSED void *x){
}

typedef struct qnode {
	void *value;
	struct qnode *next;
} QNode;

typedef struct q_data {
	long size;
	QNode *head;
	QNode *tail;
	void(*freeValue)(void *v);
} QData;

static void purge(QData *qd, void(*freeV)(void *e)) {
	if (freeV != NULL) {
		QNode *q;
		for (q = qd->head; q!=NULL; q=q->next) {
			(*freeV)(q->value);
		}
	}
}

static void freeList(QData *qd) {
	QNode *q, *p = NULL;
	for (q = qd->head; q!=NULL; q=p) {
		p = q->next;
		free(q);
	}
}

static void q_destroy(const Queue *q) {
	QData *qd = (QData *)q->self;
	purge(qd, qd->freeValue);
	freeList(qd);
	free(qd);
	free((void *)q);
}

static void q_clear(const Queue *q) {
	QData *qd = (QData *)q->self;
	purge(qd, qd->freeValue);
	freeList(qd);
	qd->head = qd->tail = NULL;
	qd->size = 0L;
}

static bool q_enqueue(const Queue *q, void *element) {
	QData *qd = (QData *)q->self;
	QNode *tmp = (QNode *)malloc(sizeof(QNode));
	bool status = (tmp != NULL);

	if (status) {
		tmp->next = NULL;
		tmp->value = element;
		if (qd->head == NULL && qd->tail == NULL) {
			qd->head = tmp;
			qd->tail = tmp;
		}
		else {
			qd->tail->next = tmp;
			qd->tail = tmp;
		}
		qd->size++;
	}
	return status;
}

static bool q_front(const Queue *q, void **element) {
	QData *qd = (QData *)q->self;
	bool status = (qd->size > 0L);

	if (status) {
		*element = qd->head->value;
	}
	return status;
}

static bool q_dequeue(const Queue *q, void **element) {
	QData *qd = (QData *)q->self;
	bool status = (qd->size > 0L);
	if (status) {
		QNode *tmp = qd->head;

		if((qd->head = tmp->next) == NULL) {
			qd->tail = NULL;
		}
		*element = tmp->value;
		qd->size--;
		free(tmp);
	}
	return status;
}

static long q_size(const Queue *q) {
	QData *qd = (QData *)q->self;
	return qd->size;
}

static bool q_isEmpty(const Queue *q) {
	QData *qd = (QData *)q->self;
	return (qd->size == 0L);
}

static void **genArray(QData *qd) {
	void **theArray = NULL;
	if (qd->size > 0L) {
		theArray = (void **)malloc(qd->size*sizeof(void*));
		if (theArray != NULL) {
			long i = 0L;
			QNode *q;
			for(q=qd->head; q!=NULL; q=q->next) {
				theArray[i++] = q->value;
			}
		}
	}
	return theArray;
}

static void **q_toArray(const Queue *q, long *len) {
	QData *qd = (QData *)q->self;
	void **tmp = genArray(qd);
	if (tmp != NULL) {
		*len = qd->size;
	}
	return tmp;
}

static const Iterator *q_itCreate(const Queue *q) { 
	QData *qd = (QData *)q->self;
	const Iterator *it = NULL;
	void **tmp = genArray(qd);
	if (tmp != NULL) {
		it = Iterator_create(qd->size, tmp);
		if(it == NULL) {
			free(tmp);
		}
	}
	return it;
}

static const Queue *q_create(const Queue *q);

static Queue template = {
    NULL, q_create, q_destroy, q_clear, q_enqueue, q_front, q_dequeue, q_size,
    q_isEmpty, q_toArray, q_itCreate
};

static const Queue *newQueue(void(*freeV)(void*)) {

	Queue *q = (Queue *)malloc(sizeof(Queue));

	if (q != NULL) {
		QData *qd = (QData *)malloc(sizeof(QData));

		if (qd != NULL) {
			qd->size = 0L;
			qd->head = NULL;
			qd->tail=NULL;
			qd->freeValue = freeV;
			*q = template;
			q->self = qd;
		} else {
			free(q);
			q = NULL;
		}
	}
	return q;
}

static const Queue *q_create(const Queue *q) {
	QData *qd = (QData *)q->self;
	return newQueue(qd->freeValue);
}

const Queue *LListQueue(void (*freeValue)(void *value)) {
	return newQueue(freeValue);
}

const Queue *Queue_create(void (*freeValue)(void *value)) {
	return newQueue(freeValue);
}
