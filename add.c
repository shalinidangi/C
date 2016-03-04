void add(long long *pointer, long long value) {
    long long sum = *pointer + value;
    *pointer = sum;
}

// int opt_yield;

// void add(long long *pointer, long long value) {
//     long long sum = *pointer + value;
//     if (opt_yield)
//         pthread_yield();
//     *pointer = sum;
// }
