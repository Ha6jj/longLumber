with open("pi.txt", "r") as file:
    real_pi = file.readline()

output = input().rstrip()
last = min(len(real_pi), len(output))
flag = True
for i in range(last):
    if real_pi[i] != output[i]:
        print(i + 1)
        flag = False
        break
if flag:
    print("Exact")