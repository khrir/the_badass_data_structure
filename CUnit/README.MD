```
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
```

gcc -Wall -o unit Huffman_implementacao/freq.c Huffman_implementacao/heap.c CUnit/unity.c -lcunit
