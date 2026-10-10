void apply_lazy(int b) {
    for (int i = b * S; i < (b + 1) * S; i++) {
        // ...
    }

    lazy[b] = 0;
}

void manual_update(int l, int r, int x) {
    int b = l / S;
    for (int i = l; i <= r; i++) {
        /// ...
    }
}

void update(int l, int r, int x) {
    int block_l = l / S;
    int block_r = r / S;

    if (block_l == block_r) {
        apply_lazy(block_l);
        manual_update(l, r, x);
    } else {
        update_block(block_l, block_r, x);

        apply_lazy(block_l);
        apply_lazy(block_r);

        manual_update(l, (block_l + 1) * S - 1, x);
        manual_update(block_r * S, r, x);
    }
}
