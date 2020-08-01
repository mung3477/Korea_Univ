import java.util.Scanner;

public class Ch10_D {
    public static void main(String[] args) {
        Queue queue = new Queue();
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();
        for (int i = 0; i < N; i++) {
            int n = sc.nextInt();
            if (n == -1) {
                if (!queue.empty()) queue.dequeue();
            } else {
                queue.enqueue(n);
            }
        }
        while (!queue.empty())
            System.out.println(queue.dequeue());
    }
}

class Queue {
    int[] elements;
    int size;
    int capacity;

    Queue() {
        this.capacity = 10000;
        this.size = 0;
        this.elements = new int[this.capacity];
    }

    void enqueue(int v) {
        this.elements[this.size++] = v;
    }

    int dequeue() {
        int popped = this.elements[0];
        this._moveElements();
        this.size--;
        return popped;
    }

    boolean empty() {
        if (this.size == 0) { return true; }
        else { return false; }
    }

    int getSize() {
        return this.size;
    }

    void _moveElements(){
        for(int i = 0; i < this.size - 1; i++) {
            this.elements[i] = this.elements[i + 1];
        }
    }
}
