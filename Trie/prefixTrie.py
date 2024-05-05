class Node:
    def __init__(self):
        self.child = {}
        self.is_end = False

class PrefixTrie:
    def __init__(self):
        self.root = Node()

    def insert(self, word):
        for i in range(len(word)):
            self._insert_prefix(word[:i+1])

    def _insert_prefix(self, prefix):
        node = self.root
        for char in prefix:
            if char not in node.child:
                node.child[char] = Node()
            node = node.child[char]
        node.is_end = True  
        
    def search(self, word):
        node = self.root
        for char in word:
            if char not in node.child:
                return False
            node = node.child[char]
        return node.is_end

    def delete(self, word):
        for i in range(len(word)):
            self._delete_prefix(word[:i+1])

    def _delete_prefix(self, prefix):
        self._delete_node(self.root, prefix, 0)

    def _delete_node(self, node, word, depth):
        if depth == len(word):
            if not node.is_end:
                return False
            node.is_end = False
            return len(node.child) == 0

        char = word[depth]
        if char not in node.child:
            return False

        if self._delete_node(node.child[char], word, depth + 1):
            del node.child[char]
            return len(node.child) == 0

        return False


if __name__ == "__main__":
    trie = PrefixTrie()
    trie.insert("laptop")
    trie.insert("lambda")
    trie.insert("function")
    trie.insert("fiction")
    print(trie.search("laptop"))    # True
    print(trie.search("lapto"))     # True
    trie.delete("lambda")
    print(trie.search("lambda"))    # False