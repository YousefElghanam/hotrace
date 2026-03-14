with open("bigger.txt", "w") as f:
    for i in range(1, 10000001):
        f.write(f"key{i}\nval{i}\n")