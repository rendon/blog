struct Node {
    char letter;
    int frequency;
    Node *left;
    Node *right;

    Node()
    {
        letter = '\0';
        frequency = 0;
        left = NULL;
        right = NULL;
    }

    Node(char letter, int frequency)
    {
        this->letter = letter;
        this->frequency = frequency;
        left = NULL;
        right = NULL;
    }

    ~Node() { }
};

struct NodeComparator {
    bool operator()(const Node* a, const Node *b)
    {
        return a->frequency > b->frequency;
    }
};

// Maps a character with the sequence of bits of the new representation.
map<char, vector<bool> > codes;

/* Traverse the tree to build the bit sequence of each character.*/
void generate_codes(Node *node, bool path[], int p)
{
    if (node->left == NULL && node->right == NULL) {
        vector<bool> bits;
        for (int i = 0; i < p; i++) {
            bits.push_back(path[i]);
        }
        codes[node->letter] = bits;
    } else {
        path[p] = false;
        generate_codes(node->left, path, p + 1);
        path[p] = true;
        generate_codes(node->right, path, p + 1);
    }
}

/* Construct the Huffman tree given the frequency of each character. */
Node* build_tree(int buckets[])
{
    priority_queue<Node*, vector<Node*>, NodeComparator> Q;
    for (int i = 0; i < 256; i++) {
        if (buckets[i] > 0) {
            Q.push(new Node(char(i), buckets[i]));
        }
    }

    while (Q.size() > 1) {
        Node *left = Q.top();
        Q.pop();
        Node *right = Q.top();
        Q.pop();

        Node *root = new Node();
        root->left = left;
        root->right = right;
        root->frequency = left->frequency + right->frequency;
        Q.push(root);
    }
    
    Node *root = Q.top();
    Q.pop();
    return root;
}

int encode(ifstream &input, ofstream &output)
{
    int buckets[256]; // Used to count the frequency of each character.
    bool path[20]; 

    string line, text = "";
    while (input.good()) {
        char c = input.get();
        if (input.eof()) { break; }
        text += c;
    }

    memset(buckets, 0, sizeof buckets);
    for (unsigned i = 0; i < text.length(); i++) {
        buckets[(int)text[i]]++;
    }

    Node *root = build_tree(buckets);
    generate_codes(root, path, 0);

    // In the worst case the size of the output might not be reduced.
    string compressed_text(text.length(), '\0');
    int bytes = 0;
    int bit = 0;
    int total_bits = 0;
    for (unsigned i = 0; i < text.length(); i++) {
        vector<bool> &bits = codes[text[i]];
        for (unsigned j = 0; j < bits.size(); j++) {
            if (bits[j]) {
                compressed_text[bytes] |= (1 << bit); // Set bit to 1
            }
            bit++;
            if (bit == 8) {
                bytes++;
                bit = 0;
            }
        }
        total_bits += bits.size();
    }

    // Watch out!
    if (total_bits % 8 != 0) {
        bytes++;
    }

    // Store the frequencies in the output so that the decoder can make its job.
    for (int i = 0; i < 256; i++) {
        output << buckets[i] << " ";
    }
    output << endl << bytes << " " << total_bits << endl;

    for (int i = 0; i < bytes; i++) {
        output << compressed_text[i];
    }

    return 0;
}

int decode(ifstream &input, ofstream &output)
{
    int buckets[256];
    for (int i = 0; i < 256; i++) {
        input >> buckets[i];
    }

    Node *root = build_tree(buckets);

    int bytes, b = 0;
    int total_bits, tb = 0;
    input >> bytes >> total_bits;
    input.ignore(); // \n

    Node *node = root;
    while (input.good() && b < bytes) {
        char c = input.get();
        if (input.eof()) { break; }
        b++;

        int i = 0;
        while (i < 8 && tb < total_bits) {
            int bit = (c & (1 << i)) > 0;
            if (bit == 1) {
                node = node->right;
            } else {
                node = node->left;
            }

            i++;
            tb++;
            if (node->left == NULL && node->right == NULL) {
                output << node->letter;
                node = root;
            }
        }
    }

    return 0;
}
