with open("pairs.txt", "w") as f:
    for i in range(1, 100001):
        f.write(f"key{i}\nval{i}\n")