#include <stdio.h>
#include <malloc.h>

typedef struct tasks {
    void (*handler)();
    int time;
} tasks;

int num_tasks = 0;

tasks *task_queue;

void task1() {
    printf("Task 1!\n");
};

void task2() {
    printf("Task 2!\n");
};

void task3() {
    printf("Task 3!\n");
};

void task4() {
    printf("Task 4!\n");
};

void task5() {
    printf("Task 5!\n");
};

void schedule(void (*handler)(), int time) {
    tasks task;
    task.handler = handler;
    task.time = time;

    if(task_queue == NULL) {
        task_queue = malloc(sizeof(task));
    } else {
        task_queue = realloc(task_queue, (num_tasks+1)*sizeof(tasks));
    }
    task_queue[num_tasks] = task;
    num_tasks++;
}

int binary_search(int time) {
    int mid = 0;

    int lo = 0;
    int hi = num_tasks-1;

    while(lo <= hi) {
    	mid = lo + (hi - lo)/2;
       	if(time < task_queue[mid].time) hi = mid-1;
        else if(time > task_queue[mid].time) lo = mid+1;
        else return mid;
    }

    return -1;
}

void abort_task(int time) {

    int task_id = binary_search(time);

    if(num_tasks > 0) {
        if(num_tasks == 1) {
            free(task_queue);
        } else {
            for(int i=task_id; i<num_tasks-1; i++) {
                task_queue[i] = task_queue[i+1];
            }
            task_queue = realloc(task_queue, num_tasks * sizeof(tasks));
        }
        num_tasks--;
    }
}

void run_scheduler(int time) {
    
    int task_id = binary_search(time);

    if(task_id >= 0) {
        if(task_queue[task_id].handler != NULL)
            (*task_queue[task_id].handler)();
    }
}

void main() {
    schedule(&task1,2);
    schedule(&task2,5);
    schedule(&task3,6);
    schedule(&task4,8);
    schedule(&task5,9);
    abort_task(6);
    abort_task(8);
    for(int i=0; i < 10; i++) {
        printf("Time = %d\n", i);
        run_scheduler(i);
    }
}
