from random import randint
# 测试集生成
MAX_A = 1000000
MAX_B = 1000000



def _rand(testObj):
    n = randint(2000, 5000)
    m = randint(1000, n-1)
    a = []
    
    for i in range(m-1):
        ca = randint(1, n-1)
        while ca in a:
            ca = randint(1, n-1)
        a.append(ca)
    a.append(n)
    a.sort()
    cnt = 0
    data = []
    segid = []
    for i in range(n):
        if i in a: cnt += 1
        data.append(randint(-MAX_A, MAX_A) / randint(-MAX_B, MAX_B))
        segid.append(cnt)
    # output
    # testObj.write("float data[%d]={" % (n))
    testObj.write("%d\n"% n)
    testObj.write("%d\n"% m)
    for i in range(len(data)):
        testObj.write("%f "%data[i])
        if i == (len(data) - 1):testObj.write("\n")
    # testObj.write("int seg_id[%d]={" % (n))
    for i in range(len(segid)):
        testObj.write("%d "%segid[i])
        if i == (len(segid)-1): testObj.write("\n")
    # testObj.write("int seg_start[%d]={0,"%((m+1)))
    testObj.write("%d "% 0)
    for i in range(len(a)):
        testObj.write("%d "%a[i])
        if i == (len(a)-1): testObj.write("\n")

testObj = open("test.txt","w")
# 修改i的循环次数修改生成集数量
for i in range(1,200):
    _rand(testObj)

testObj.close()