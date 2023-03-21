#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

struct NMANAGER;

#define LL_INSERT(item, list) do {  \
    item->prev = NULL;  \
    item->next = list;  \
    if(list) list->prev = item;  \
    list = item;    \
} while(0)

#define LL_REMOVE(item, list) do {  \
    if(item->prev != NULL) item->prev->next = item->next;   \
    if(item->next != NULL) item->next->prev = item->prev;   \
    if(list == item) list = item->next; \
    item->prev = item->next = NULL;     \
} while(0)

/* 工作队列结构体 */
struct NWORKER {
    pthread_t tid;
    int terminate;
    struct NMANAGER *pool;
    struct NWORKER *prev;
    struct NWORKER *next;
};
/* 任务队列结构体 */
struct NTASK {
    void (*task_func)(void *arg);
    void *user_data;
    struct NTASK *prev;
    struct NTASK *next;
};

typedef struct NMANAGER {
    struct NWORKER *workers;
    struct NTASK   *tasks; 
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
} pthreadpool_t;

/* 线程回调函数 */
//pthread_cond_wait()
//pthread_cond_signal()
static void *thread_callback(void *arg)
{
    struct NWORKER *worker = (struct NWORKER *)arg;
    while(1)
    {
        pthread_mutex_lock(&worker->pool->mutex);
            printf("pthread[%ld]\n", worker->tid);
        while(worker->pool->tasks == NULL)
        {
            if(worker->terminate) break;
            /* 如果队列为空就进入条件等待 */

            pthread_cond_wait(&worker->pool->cond, &worker->pool->mutex);
        }
        if(worker->terminate)
        {
            pthread_mutex_unlock(&worker->pool->mutex);
            break;
        }      
        /* 取出一个任务 */
        struct NTASK *task = worker->pool->tasks;
        if(task)
        {
            LL_REMOVE(task, worker->pool->tasks);
        }
        pthread_mutex_unlock(&worker->pool->mutex);

        task->task_func(task);
    }

}

/* 线程的创建 */
int thread_pool_create(struct NMANAGER* pool, int nthread)
{ 
    if(pool == NULL) return -1;
    if(nthread < 1) nthread = 1;

    memset(pool, 0, sizeof(struct NMANAGER));

    pthread_mutex_t blank_mutex = PTHREAD_MUTEX_INITIALIZER;
    memcpy(&pool->mutex, &blank_mutex, sizeof(blank_mutex));
    pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
    memcpy(&pool->cond, &blank_cond, sizeof(blank_cond));

    int idx = 0;
    for(idx = 0; idx < nthread; idx++)
    {
        struct NWORKER *worker = (struct NWORKER*)malloc(sizeof(struct NWORKER));
        if(worker == NULL)
        {
            perror("malloc\n");
            exit(-1);
        }
        memset(worker, 0, sizeof(struct NWORKER));
        worker->pool = pool;
        worker->terminate = 0;
        int ret = pthread_create(&worker->tid, NULL, thread_callback, worker);
        if(ret)
        {
            perror("pthread_create");
            exit(-1);
        }
        // pthread_detach(worker->tid);
        // pthread_join(worker->tid, NULL);
        LL_INSERT(worker, pool->workers);
    }
    return idx;
}

/* 线程的销毁 */
int thread_pool_destroy(struct NMANAGER* pool)
{
    int i = 0;
    struct NWORKER *worker = NULL;
    for(worker = pool->workers; worker != NULL; worker = worker->next)
    {
        worker->terminate = 1;
    }
    pthread_mutex_lock(&worker->pool->mutex);
    pthread_cond_broadcast(&pool->cond);
    pthread_mutex_unlock(&worker->pool->mutex);
}
int thread_pool_push(struct NMANAGER* pool, struct NTASK* task)
{
    pthread_mutex_lock(&pool->mutex);
    LL_INSERT(task, pool->tasks);
    pthread_cond_signal(&pool->cond);

    pthread_mutex_unlock(&pool->mutex);
}

void counter(void *arg)
{
    struct NTASK *task = (struct NTASK *)arg;
    printf("idx = %d\n", *(int *)task->user_data);
    sleep(1);
}

int main(int argc, char *argv[])
{
    struct NMANAGER pool;
    int nthread = 3;
    int ret = thread_pool_create(&pool, nthread);
    sleep(10);
    for(int i = 0; i < nthread * 20; i++)
    {
        struct NTASK* job = (struct NTASK*)malloc(sizeof(struct NTASK));
        if(job == NULL) exit(1);

        job->task_func = counter;
        job->user_data = malloc(sizeof(int));
        *(int *)job->user_data = i;

        thread_pool_push(&pool, job);
    }
    while(pool.tasks != NULL);
    printf("task is finished\n");

    struct  NWORKER *worker = NULL;
    for(worker = pool.workers; worker->next != NULL; worker = worker->next) {
        worker->terminate = 1;
    }
    for(worker = pool.workers; worker->next != NULL; worker = worker->next) {
        pthread_join(worker->tid, NULL);
    }
    return 0;
}