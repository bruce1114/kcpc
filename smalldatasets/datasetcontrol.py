import random

cnum=1000
overnum=50000
csizel=3
csizer=12
csizemax=20


cids=[x for x in range(cnum)]

cedgeset=set()

while len(cedgeset)<overnum:
    a=random.randint(0,cnum-1)
    b=random.randint(0,cnum-1)
    if a==b:
        continue
    if a>b:
        temp=a
        a=b
        b=temp
    
    cedgeset.add((a,b))


ctov=[[] for x in range(cnum)]
vcnt=[0,]
def generate_clique(cid,csize,prevlist):
    if len(prevlist)>=csize:
        print("error")
        exit(0)
    
    for v in prevlist:
        ctov[cid].append(v)
    
    for i in range(csize-len(prevlist)):
        ctov[cid].append(vcnt[0])
        vcnt[0]=vcnt[0]+1


skipcnt=0
for cedge in cedgeset:
    ca=cedge[0]
    cb=cedge[1]
    casize=len(ctov[ca])
    cbsize=len(ctov[cb])
    if casize>0 and cbsize>0:
        smallsize=casize
        if smallsize>cbsize:
            smallsize=cbsize
        
        # oversize=random.randint(1,smallsize-1)
        # oldvcnt=vcnt[0]
        # newvcnt=vcnt[0]+oversize
        # for val in range(oldvcnt,newvcnt):
        #     ctov[ca].append(val)
        #     ctov[cb].append(val)
        # vcnt[0]=newvcnt
        oversize=random.randint(1,smallsize-1)
        overlist=random.sample(ctov[ca],oversize)
        for i in range(oversize):
            ctov[cb][-(i+1)]=overlist[i]


        continue

    if casize==0 and cbsize==0:
        generate_clique(ca,random.randint(csizel,csizer),[])
        casize=len(ctov[ca])
    
    if casize==0:
        temp=ca
        ca=cb
        cb=temp
    
    casize=len(ctov[ca])
    cbsize=len(ctov[cb])

    oversize=random.randint(1,casize-1)
    overlist=random.sample(ctov[ca],oversize)

    if oversize+1 > csizer:
        generate_clique(cb,oversize+1,overlist)
    else:
        generate_clique(cb,random.randint(oversize+1,csizer),overlist)
    

edgeset=set()
for ctovlist in ctov:
    for i in range(0,len(ctovlist)):
        for j in range(i+1,len(ctovlist)):
            u=ctovlist[i]
            v=ctovlist[j]

            if u==v:
                # print("errors")
                # exit(0)
                continue

            if u>v:
                temp=u
                u=v
                v=temp

            edgeset.add((u,v))


fout=open("tempdataset.txt","w")
for edge in edgeset:
    fout.write(str(edge[0])+" "+str(edge[1])+"\n")
