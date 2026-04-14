#include <stdio.h>
#define N 10

typedef struct queue {
    int a[N];
    int front, rear;
} queue;

int balance = 1000;   // Initial balance

// Initialize queue
void init(queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check empty
int isempty(queue *q) {
    return (q->front == -1);
}

// Check full (circular condition)
int isfull(queue *q) {
    return ((q->rear + 1) % N == q->front);
}

// Enqueue (Add transaction)
void enqueue(queue *q, int x) {
    if (isfull(q)) {
        printf("\nQueue Overflow");
        return;
    }

    if (isempty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % N;
    }

    q->a[q->rear] = x;
    printf("\nTransaction added: %d", x);
}

// Dequeue (Process transaction)
int dequeue(queue *q) {
    int x;

    if (isempty(q)) {
        return -1;
    }

    x = q->a[q->front];

    if (q->front == q->rear) {
        // Only one element
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % N;
    }

    return x;
}

// Display transactions
void display(queue *q) {
    if (isempty(q)) {
        printf("\nNo pending transactions");
        return;
    }

    printf("\nPending transactions: ");
    int i = q->front;

    while (1) {
        printf("%d ", q->a[i]);
        if (i == q->rear)
            break;
        i = (i + 1) % N;
    }
}

int main() {
    queue q;
    int ch, x;

    init(&q);

    do {
        printf("\n\n--- Banking Transaction System (Circular Queue) ---");
        printf("\n1. Add Transaction (+deposit / -withdraw)");
        printf("\n2. Process Transaction");
        printf("\n3. Display Transactions");
        printf("\n4. Show Balance");
        printf("\n5. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter amount (+/-): ");
                scanf("%d", &x);
                enqueue(&q, x);
                break;

            case 2:
                x = dequeue(&q);
                if (x == -1) {
                    printf("\nNo transactions to process");
                } else {
                    if (x < 0 && balance + x < 0) {
                        printf("\nTransaction failed! Insufficient balance");
                        enqueue(&q, x); // re-add failed transaction
                    } else {
                        balance += x;
                        printf("\nProcessed transaction: %d", x);
                        printf("\nUpdated Balance: %d", balance);
                    }
                }
                break;

            case 3:
                display(&q);
                break;

            case 4:
                printf("\nCurrent Balance: %d", balance);
                break;

            case 5:
                printf("\nExiting...");
                break;

            default:
                printf("\nInvalid choice");
        }

    } while (ch != 5);

    return 0;
}