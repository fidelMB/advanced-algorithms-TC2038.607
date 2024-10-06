def compute_prefix_table(P):
    m = len(P)
    pi = [None] * m
    pi[0] = 0

def kmp_matcher(T, P):
    n = len(T)
    m = len(P)

    pi = compute_prefix_table(P)

    q = 0

