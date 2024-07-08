#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>

// A Huffman tree node
struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// For comparison of two heap nodes (needed in priority queue)
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq > r->freq);
    }
};

// Print Huffman codes from the root of Huffman Tree
void printCodes(struct MinHeapNode* root, std::string str,
                std::unordered_map<char, std::string> &huffmanCode) {
    if (!root)
        return;

    if (root->data != '$')
        huffmanCode[root->data] = str;

    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

// Build the Huffman Tree and store it in map
void buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    std::unordered_map<char, std::string> huffmanCode;
    printCodes(minHeap.top(), "", huffmanCode);

    std::cout << "Huffman Codes are:\n";
    for (auto pair : huffmanCode)
        std::cout << pair.first << ": " << pair.second << "\n";
}

// Main function to drive the program
int main() {
    // Sample text for compression
    std::string text = "this is an example for huffman encoding";

    // Count frequency of appearance of each character
    std::unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    int size = freq.size();
    char* data = new char[size];
    int* frequencies = new int[size];
    int index = 0;

    for (auto pair : freq) {
        data[index] = pair.first;
        frequencies[index] = pair.second;
        index++;
    }

    buildHuffmanTree(data, frequencies, size);

    delete[] data;
    delete[] frequencies;

    return 0;
}
