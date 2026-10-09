struct TrieNode {
	int pi = 0;
	int child[26] = {0};
};
vector<TrieNode> trie;
vector<vector<int>> adj;

int TrieInsert(const string& s) {
	int p = 0;
	for (int i = 0; i < s.size(); i++) {
		if (!trie[p].child[s[i] - 'a']) {
			trie[p].child[s[i] - 'a'] = trie.size();
			trie.pb(TrieNode());
		}
		p = trie[p].child[s[i] - 'a'];
	}
	return p;
}

void AhoCorasickBuild() {
	queue<int> q;
	for (int i = 0; i < 26; i++) {
		if (trie[0].child[i]) {
			q.push(trie[0].child[i]);
		}
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < 26; i++) {
			if (!trie[u].child[i]) continue;
			int j = trie[u].pi;
			while (!trie[j].child[i]) {
				if (!j) break;
				j = trie[j].pi;
			}
			trie[trie[u].child[i]].pi = trie[j].child[i];
			q.push(trie[u].child[i]);
		}
		adj[trie[u].pi].pb(u);
	}
}

signed main() {
	trie.pb(TrieNode());


	adj.resize(trie.size());
	AhoCorasickBuild();
}
